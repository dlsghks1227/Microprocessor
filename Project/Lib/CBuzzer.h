/* 
* CBuzzer.h
*
* Created: 2020-12-10 오후 9:58:08
* Author: lh122
*/


#ifndef __CBUZZER_H__
#define __CBUZZER_H__

#include <avr/io.h>

#include "CDelay.h"

class CBuzzer
{
public:
	static CBuzzer& GetInstance() { return m_Instance; }

	CBuzzer();
	~CBuzzer();
	
public:
	void Init();
	
	void On();
	void Off();
	
private:
	static CBuzzer m_Instance;
}; //CBuzzer

#endif //__CBUZZER_H__
