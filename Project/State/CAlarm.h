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
	void Shuffle(int count);
	void ResetButtonClick();

private:
	char		m_HelpText[24] = "Press Button in order. ";
	int			m_TextShiftCount;
	
	char		m_AlarmPrintText1[16] = { 0x00 };
	char		m_AlarmPrintText2[16] = { 0x00 };

	int			m_Order[4] = {1, 2, 3, 4};
	int			m_ShuffleTime;
	int			m_TimeCount;
	
	int			m_ButtonClick[4] = {0, 0, 0, 0};
	int			m_ButtonClickCount;
	
	bool		m_Blink;

private:
	static CAlarm m_Instance;
}; //CAlarm

#endif //__CALARM_H__
