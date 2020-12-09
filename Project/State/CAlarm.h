/* 
* CAlarm.h
*
* Created: 2020-12-10 오전 6:43:19
* Author: lh122
*/


#ifndef __CALARM_H__
#define __CALARM_H__

#include "CStateBase.h"
#include "CState.h"

class CAlarm : public CStateBase
{
public:
	static CAlarm& GetInstance() { return m_Instance;}

	CAlarm();
	~CAlarm();

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
	static CAlarm m_Instance;
}; //CAlarm

#endif //__CALARM_H__
