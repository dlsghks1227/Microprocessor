/* 
* CCurrentTime.h
*
* Created: 2020-12-10 오전 6:24:31
* Author: lh122
*/


#ifndef __CCURRENTTIME_H__
#define __CCURRENTTIME_H__

#include <avr/io.h>
#include <stdio.h>

#include "CStateBase.h"
#include "CState.h"

class CCurrentTime : public CStateBase
{
public:
	static CCurrentTime& GetInstance() { return m_Instance;}
	
	CCurrentTime();
	~CCurrentTime();

public:
	void Display(CLCD& lcd) override;
	
	void Update()			override;
	
	void OnClickSwitch01()	override;
	void OnClickSwitch02()	override;
	void OnClickSwitch03()	override;
	void OnClickSwitch04()	override;
	
	void OnEnterState(CLCD& lcd)	override;
	void OnExitState(CLCD& lcd)		override;
	
private:
	char		m_TimePrintText[16] = { 0x00 };
	
private:
	static CCurrentTime m_Instance;
}; //CCurrentTime

#endif //__CCURRENTTIME_H__
