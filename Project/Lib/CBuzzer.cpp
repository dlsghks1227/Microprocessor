/* 
* CBuzzer.cpp
*
* Created: 2020-12-10 오후 9:58:08
* Author: lh122
*/


#include "CBuzzer.h"

CBuzzer CBuzzer::m_Instance;

// default constructor
CBuzzer::CBuzzer()
{
} //CBuzzer

// default destructor
CBuzzer::~CBuzzer()
{
} //~CBuzzer

void CBuzzer::Init()
{
	DDRG = 0xFF;
	PORTG = 0x00;
}

void CBuzzer::On()
{
	PORTG |= 0x08;
}

void CBuzzer::Off()
{
	PORTG &= 0xF7;
}