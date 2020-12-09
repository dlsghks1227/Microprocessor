/* 
* CLCD.cpp
*
* Created: 2020-11-23 오후 4:08:21
* Author: 이인환
*/

#include "CLCD.h"

/*	Command
 *
 *	function					D7		D6		D5		D4		D3		D2		D1		D0		설명
 * 
 *	Clear Display				0		0		0		0		0		0		0		1		LCD 클리어 후, 커서 홈 위치
 *	Return Home					0		0		0		0		0		0		1		-		커서를 홈 위치로 이동
 *	Entry Mode Set				0		0		0		0		0		1		I/D		S		커서 진행 방향 결정(1: 오른쪽, 0: 왼쪽)
 *	Display ON/OFF Control		0		0		0		0		1		D		C		B		D : LCD, C : Cursor, B : Blink 온오프 결정
 *	Cursor or Display Shift		0		0		0		1		S/C		R/L		-		-		화면(S, 1) / 커서(C, 0) 시프트 왼쪽(L, 0) / 오른쪽(R, 1) 결정
 *	Function Set				0		0		1		DL		N		F		-		-		데이터 길이(DL, 1: 8비트 / 0: 4비트), 표시 행수(N, 1: 2행 / 0: 1행), 문자 폰트(F, 1: 5x10 / 0: 5x8) 설정
 *	Set CG RAM Address			0		1		|		CG RAM Address					|		CG RAM Address set, 이후 전송되는 데이터는 CG RAM 데이터로 취급
 *	Set DD RAM Address			1		|				DD RAM Address					|		DD RAM Address set, 이후 전송되는 데이터는 DD RAM 데이터로 취급
 *	Read Busy Flag and Address	BF		|					Address						|		Busy Flag Check 및 주소를 읽음, CG / DD RAM에서 모두 사용가능
 *	Data W to CG or DD			|					Write Data (ASCII Code)				|		CG/DD RAM으로 데이터 쓰기
 *	Data R from CG or DD		|						Read Data						|		CG/DD RAM에서 데이터 읽기
 */

// default constructor
CLCD::CLCD()
{
} //CLCD

// default destructor
CLCD::~CLCD()
{
} //~CLCD


void CLCD::Init(bool isCursor, bool isBlink)
{	
	DDRA	= 0xFF;
	PORTA	= 0xFF;
		
	DDRG	= 0xFF;
	PORTG	= 0x00;
	
	PORTG  &= 0xFE;
	
	m_Delay.Delay_ms(200);
	
	// 0b 0011 1011
	// DL = 1(8 Bit), N = 1(2 Row), F = 0(5x8 Matrix)
	this->Command(0x38);
	
	// 0b 0000 1111
	// D = 1(LCD On), C = 1(Cursor On), B = 1(Blink On, 커서 깜빡임)
	unsigned char cmd = 0x0C;
	cmd |= isCursor ? 0x02 : 0x00;
	cmd |= isBlink  ? 0x01 : 0x00;
	this->Command(cmd);
	
	// 0b 0000 0001
	// Clear Display
	this->Command(0x01);
	
	m_Delay.Delay_ms(100);
}

void CLCD::Enable()
{
	// 0b 0000 0100
	// Rs = 0(Command), R/W = 0(Write, CPU -> LCD), E = 1
	PORTG |= 0x04;
	
	// 0b 1111 1011
	// Rs = 0(Data), R/W = 1(Read, LCD -> CPU), E = 0
	PORTG &= 0xFB;
}

void CLCD::Command(unsigned char c)
{
	PORTG &= 0xFE;
	PORTA = c;
	
	this->Enable();
	m_Delay.Delay_ms(1);
}

void CLCD::Clear()
{
	// Rs = 0(Command), 명령어 쓰기 설정
	PORTG &= 0xFE;
	
	m_Delay.Delay_us(1);
	
	// 0b 0000 0001
	// Clear Display
	this->Command(0x01);
	
	m_Delay.Delay_us(250);
}

/*	DD RAM Address
 *
 *	80	81	82	83	84	85	86	87	88	89	8A	8C	8D	8E	8F
 *	C0	C1	C2	C3	C4	C5	C6	C7	C8	C9	CA	CC	CD	CE	CF
 *
 */

void CLCD::PrintLine_1(char* str)
{
	// Rs = 0(Command), 명령어 쓰기 설정
	PORTG &= 0xFE;
	
	// DD RAM Address Write 0x80 이동
	this->Command(0x80);
	while(*str) this->Putch(*str++);
	m_Delay.Delay_us(250);
	
}

void CLCD::PrintLine_2(char* str)
{
	// Rs = 0(Command), 명령어 쓰기 설정
	PORTG &= 0xFE;
	
	// DD RAM Address Write 0xC0 이동
	this->Command(0xC0);
	while(*str) this->Putch(*str++);
	m_Delay.Delay_us(250);
	
}

void CLCD::Putch(char c)
{
	// Rs = 1(Data), 데이터 읽기 / 쓰기
	PORTG |= 0x01;
	PORTA = c;
	
	this->Enable();
	m_Delay.Delay_ms(1);
}

void CLCD::CursorPos(unsigned char x, unsigned char y)
{
	// Rs = 0(Command), 명령어 쓰기 설정
	PORTG &= 0xFE;
	
	if (y == 0) this->Command(0x80 + x);
	else this->Command(0xC0 + x);
}


void CLCD::SaveCharacter(int size, const char* cs)
{
	for (unsigned char i = 0; i < size; i++) {
		this->Command(i | 0x40);
		this->Putch(cs[i]);
	}
}