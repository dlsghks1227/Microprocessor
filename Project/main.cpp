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
	srand(time(NULL));
	
	CFND::GetInstance().Init();
	CADC::GetInstance().Init();
	CBuzzer::GetInstance().Init();
	
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
		CState::GetInstance().Display();
    }
	
	return 0;
}