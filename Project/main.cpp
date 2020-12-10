/*
 * Project.cpp
 *
 * Created: 2020-11-23 오후 4:07:48
 * Author : 이인환
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "Lib/CLCD.h"
#include "Lib/CADC.h"
#include "Lib/CDelay.h"

#include "State/CState.h"

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 184;
	CState::GetInstance().Update();
}

ISR(INT4_vect)
{
	CState::GetInstance().OnClickSwitch01();
}

ISR(INT5_vect)
{
	CState::GetInstance().OnClickSwitch02();
}

ISR(INT6_vect)
{
	CState::GetInstance().OnClickSwitch03();
}

ISR(INT7_vect)
{
	CState::GetInstance().OnClickSwitch04();
}

int main(void)
{	
	//const char pattern[64] = {
		//0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,		// 패턴1
		//0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		//0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		//0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
		//0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
		//0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		//0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF,
		//0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00		// 패턴 7
	//};
	
	//CLCD	lcd;
	
	//lcd.Init();
	//lcd.SaveCharacter(sizeof(pattern), pattern);
	//
	
	CADC::GetInstance().Init();
	
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	EICRB	= 0xAA;
	EIMSK	= 0xF0;
	
	TCCR0	= 0x07;
	TIMSK	= 0x01;
	
	TCNT0	= 184;
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		//sprintf(msg, "Count: %d!!", rand());
		//g_timeStateManger.Display();
		//lcd.PrintLine_1(msg);
		
		//lcd.CursorPos(0, 1);
		//
		//if (++count > 7) count = 0;
		//for (int i = 0; i < 10; i++) {
			//lcd.Putch((i + count) % 8);
		//}
		CState::GetInstance().Display();
    }
	
	return 0;
}