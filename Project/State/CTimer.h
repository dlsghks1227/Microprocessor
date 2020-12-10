/* 
* CTimer.h
*
* Created: 2020-11-30 오후 11:38:33
* Author: lh122
*/


#ifndef __CTIMER_H__
#define __CTIMER_H__

#include <avr/io.h>
#include <stdio.h>

#include "CStateBase.h"
#include "CState.h"

class CTimer : public CStateBase
{
public:
	static CTimer& GetInstance() { return m_Instance;}

	CTimer();
	~CTimer();
	
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
	char m_TimerPrintText1[16] = { 0x00 };
	char m_TimerPrintText2[16] = { 0x00 };
	
private:
	static CTimer m_Instance;
}; //CTimer

#endif //__CTIMER_H__
