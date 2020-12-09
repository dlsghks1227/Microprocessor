/* 
* CADC.cpp
*
* Created: 2020-12-01 오전 2:30:00
* Author: lh122
*/


#include "CADC.h"

CADC CADC::m_Instance;

// default constructor
CADC::CADC()
{
} //CADC

// default destructor
CADC::~CADC()
{
} //~CADC


void CADC::Init()
{
	ADMUX = 0x00;
}

int CADC::GetValue()
{
	ADCSRA = 0xC7;
	while((ADCSRA & 0x10) != 0x10);
	return ADC;
}

int CADC::GetPercentValue()
{
	return (this->GetValue() * 10) / 102;
}