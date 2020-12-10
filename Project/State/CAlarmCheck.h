/* 
* CAlarmCheck.h
*
* Created: 2020-12-10 오전 6:52:45
* Author: lh122
*/


#ifndef __CALARMCHECK_H__
#define __CALARMCHECK_H__

#include "CStateBase.h"
#include "CState.h"

class CAlarmCheck : public CStateBase
{
public:
	static CAlarmCheck& GetInstance() { return m_Instance;}

	CAlarmCheck();
	~CAlarmCheck();

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
	char		m_TimePrintText1[16] = { 0x00 };
	char		m_TimePrintText2[16] = { 0x00 };

private:
	static CAlarmCheck m_Instance;
}; //CAlarmCheck

#endif //__CALARMCHECK_H__
