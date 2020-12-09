/* 
* CFND.h
*
* Created: 2020-11-24 오전 3:10:12
* Author: lh122
*/


#ifndef __CFND_H__
#define __CFND_H__

#include <avr/io.h>

#include "CDelay.h"

const char FND_TABLE[11] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x00 };
	
class CFND
{
public:
	CFND();
	~CFND();
	
public:
	void Init();

	void Display();
	
	int  GetData()				{ return m_Data; }
	void SetData(int index)		{ m_Data = index; }
	
private:
	bool IsValid(int data);
	void DisplaySplit(int d1, int d2, int d3, int d4);
	
private:
	CDelay	m_Delay;
	int		m_Data;

}; //CFND

#endif //__CFND_H__
