/* 
* CADC.h
*
* Created: 2020-12-01 오전 2:30:00
* Author: lh122
*/


#ifndef __CADC_H__
#define __CADC_H__

#include <avr/io.h>

class CADC
{
public:
	static CADC& GetInstance() { return m_Instance; }

	CADC();
	~CADC();
public:
	void Init();

	int	 GetValue();
	int  GetPercentValue();
	
private:
	static CADC m_Instance;
}; //CADC

#endif //__CADC_H__
