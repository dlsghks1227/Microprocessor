/* 
* CTimeSet.h
*
* Created: 2020-12-01 오전 1:22:22
* Author: lh122
*/


#ifndef __CTIMESETTING_H__
#define __CTIMESETTING_H__

#include "CStateBase.h"
#include "CState.h"

class CTimeSetting : public CStateBase
{
public:
	static CTimeSetting& GetInstance() { return m_Instance;}

	CTimeSetting();
	~CTimeSetting();
	
public:
	void SetTimeSetting(const char* msg, CTime* t, TIMESETTINGSTATE state);

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
	typedef enum _TIMESTATE
	{
		HOUR,
		MINUTE,
		SECOND,
	} TIMESTATE;

private:
	CTime*		m_pSetTime;
	CTime		m_Time;
	int			m_TimeState;
	
	char		m_Title[16] = { 0x00 };
	char		m_SetTimeText[16] = { 0x00 };
		
	int			m_TimeCount;
	int			m_BlinkPos;
	bool		m_Blink;
	
	TIMESETTINGSTATE m_TimeSettingState;
		
private:
	static CTimeSetting m_Instance;
}; //CTimeSet

#endif //__CTIMESETTING_H__
