/* 
* CTimeManager.cpp
*
* Created: 2020-11-30 오후 11:42:29
* Author: lh122
*/


#include "CState.h"

CState		CState::m_Instance;

CState::CState()
{
	m_CurrentState = nullptr;
	m_Lcd.Init();
	
	m_SetTimer = false;
	m_SetAlarm = false;
	
	CTimeSetting::GetInstance().SetTimeSetting("Set Current Time", &m_CurrentTime, TIMESETTINGSTATE::CURRENT);
	ChangeState(CTimeSetting::GetInstance());
}

CState::~CState()
{
} 

void CState::ChangeState(CStateBase& state)
{
	if (m_CurrentState != nullptr)
	{
		m_CurrentState->OnExitState(m_Lcd);
	}
	m_CurrentState = &state;
	m_CurrentState->OnEnterState(m_Lcd);
}

void CState::Update()
{
	m_CurrentState->Update();
	
	if (m_TimeCount >= 200)
	{
		m_TimeCount = 0;
		m_CurrentTime++;
		
		if (m_SetTimer == true)
		{
			m_TimerTime--;
		}
	}
	
	if (m_SetTimer == true)
	{
		if (m_TimerTime == CTime(0, 0, 0, 0))
		{
			m_SetTimer = false;
			CBuzzer::GetInstance().On();
			ChangeState(CTimer::GetInstance());
		}
	}
	
	m_TimeCount++;
}