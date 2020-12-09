/* 
* CLCD.h
*
* Created: 2020-11-23 오후 4:08:21
* Author: 이인환
*/


#ifndef __CLCD_H__
#define __CLCD_H__

#include <avr/io.h>

#include "CDelay.h"

class CLCD
{
public:
	CLCD();
	~CLCD();

public:
	void Init(bool isCursor = false, bool isBlink = false);		// 초기화, isCursor : 커서 On/Off, isBlink : 깜빡임 On/Off
	void Command(unsigned char c);								// 명령어
	void Clear();												// 화면 초기화

	void Putch(char c);											// 문자 출력
	void PrintLine_1(char* str);								// LCD 1행에 출력
	void PrintLine_2(char* str);								// LCD 2행에 출력
	void CursorPos(unsigned char x, unsigned char y);			// 커서 위치 설정
		
	void SaveCharacter(int size, const char* cs);				// 패턴 CG RAM에 저장 (최대 8개 패턴 저장 가능)

private:
	void Enable();
	
private:
	CDelay m_Delay;
	

}; //CLCD

#endif //__CLCD_H__
