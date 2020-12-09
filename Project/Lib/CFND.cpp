/* 
* CFND.cpp
*
* Created: 2020-11-24 오전 3:10:11
* Author: lh122
*/


#include "CFND.h"

// default constructor
CFND::CFND()
{
} //CFND

// default destructor
CFND::~CFND()
{
} //~CFND

void CFND::Init()
{
	DDRC	= 0xFF;
	PORTC	= 0xFF;
	
	DDRD	= 0xFF;
	PORTD	= 0x0F;
}

void CFND::Display()
{
	this->DisplaySplit(
	(m_Data / 1000),
	((m_Data % 1000) / 100),
	((m_Data % 100)  / 10),
	(m_Data % 10));
}

void CFND::DisplaySplit(int d1, int d2, int d3, int d4)
{
	int number[4] = { d1, d2, d3, d4 };
	
	for (int i = 0; i < 4; i++) {
		if (this->IsValid(number[i]) == false)
		number[i] %= 10;
	}
	
	for (int i = 0; i < 4; i++) {
		PORTD &= 0x0F;
		PORTC = ~FND_TABLE[number[i]];
		PORTD |= (0x10 << i);
		m_Delay.Delay_ms(1);
	}
}

bool CFND::IsValid(int data)
{
	if (0 > data || data >= 10)
		return false;
	return true;
}