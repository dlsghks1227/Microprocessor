/* 
* CTimeManager.h
*
* Created: 2020-11-30 오후 11:42:29
* Author: lh122
*/


#ifndef __CTIMEMANAGER_H__
#define __CTIMEMANAGER_H__

#include <stdlib.h>

#include "../Lib/CLCD.h"
#include "../Lib/CDelay.h"

#include "CStateBase.h"
#include "CCurrentTime.h"
#include "CTimer.h"
#include "CTimeSetting.h"
#include "CAlarm.h"
#include "CAlarmCheck.h"
#include "CStopwatch.h"
#include "CRecordList.h"
#include "CMenu.h"

class CState
{
public:
	CState();
	~CState();

public:
	static CState& GetInstance() { return m_Instance;}

	void ChangeState(CStateBase& state);

	void Display()
	{
		m_CurrentState->Display(m_Lcd);
	}
	void Update()
	{
		m_CurrentState->Update();
		
		if (m_TimeCount >= 200) {
			m_TimeCount = 0;
			m_CurrentTime++;
		}
				
		m_TimeCount++;
	}
	
	void OnClickSwitch01()	{ m_CurrentState->OnClickSwitch01(); }
	void OnClickSwitch02()	{ m_CurrentState->OnClickSwitch02(); }
	void OnClickSwitch03()	{ m_CurrentState->OnClickSwitch03(); }
	void OnClickSwitch04()	{ m_CurrentState->OnClickSwitch04(); }
		
	void* operator new(size_t objsize)
	{
		return malloc(objsize);
	}
	
	void operator delete(void* obj) 
	{
		return free(obj);
	}
	
	void ResetRecordList()
	{
		for (int i = 0 ; i < (int)(sizeof(m_RecordList) / sizeof(CTime)); i++) {
			m_RecordList[i].SetTime(0, 0, 0, 0);
		}
	}
	

private:
	static CState	m_Instance;
	CStateBase*		m_CurrentState;
	
	// Libaray
	CLCD			m_Lcd;
	CDelay			m_Delay;

	int				m_TimeCount;

public:
	CTime			m_CurrentTime;
	CTime			m_AlarmTime;
	CTime			m_TimerTime;
	CTime			m_StopwatchTime;
	CTime			m_RecordList[10] = {};
	
	bool			m_SetTimer;
	bool			m_SetAlarm;
	

}; //CTimeManager

#endif //__CTIMEMANAGER_H__
