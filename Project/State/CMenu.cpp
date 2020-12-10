/* 
* CMenu.cpp
*
* Created: 2020-12-10 오전 4:41:41
* Author: lh122
*/


#include "CMenu.h"

CMenu CMenu::m_Instance;

// default constructor
CMenu::CMenu()
{
	m_MenuState = MENUSTATE::CURRENTTIME;
	m_TimeCount = 0;
	m_StandingCount = 0;
	m_Blink = false;
} //CMenu

// default destructor
CMenu::~CMenu()
{
} //~CMenu

void CMenu::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_MenuPrintText1, "%s", m_MenuText[((m_MenuState / 2) * 2)]);
		sprintf(m_MenuPrintText2, "%s", m_MenuText[((m_MenuState / 2) * 2) + 1]);
		
		lcd.PrintLine_1(m_MenuPrintText1);
		lcd.PrintLine_2(m_MenuPrintText2);
	}
}

void CMenu::Update()
{
	if (CState::GetInstance().m_SetAlarm == true)
	{
		m_MenuPrintText1[15] = 'A';
	}
	if (CState::GetInstance().m_SetTimer == true)
	{
		m_MenuPrintText2[15] = 'T';
	}
	
	if (m_Blink == true)
	{
		if (m_MenuState % 2 == 0)
		{
			m_MenuPrintText1[12] = '<';
			m_MenuPrintText1[13] = '-';
		}
		else
		{
			m_MenuPrintText2[12] = '<';
			m_MenuPrintText2[13] = '-';
		}
	}
	
	if (m_TimeCount >= 100)
	{
		m_TimeCount = 0;
		m_Blink = !m_Blink;
		
		if (++m_StandingCount >= 10)
		{
			m_StandingCount = 0;
			CState::GetInstance().ChangeState(CCurrentTime::GetInstance());
		}
	}
	
	m_TimeCount++;
}

void CMenu::OnClickSwitch01()
{
	m_StandingCount = 0;
	
	if (m_MenuState == MENUSTATE::CURRENTTIME)
	{
		CState::GetInstance().ChangeState(CCurrentTime::GetInstance());
	}
	else if (m_MenuState == MENUSTATE::CURRENTTIMESET)
	{
		CTimeSetting::GetInstance().SetTimeSetting(
		"Current Time Set",
		&CState::GetInstance().m_CurrentTime, TIMESETTINGSTATE::CURRENT);
		CState::GetInstance().ChangeState(CTimeSetting::GetInstance());
	}
	else if (m_MenuState == MENUSTATE::ALARMSET)
	{
		CTimeSetting::GetInstance().SetTimeSetting(
		"   Alarm  Set",
		&CState::GetInstance().m_AlarmTime, TIMESETTINGSTATE::ALARM);
		CState::GetInstance().ChangeState(CTimeSetting::GetInstance());
	}
	else if (m_MenuState == MENUSTATE::ALARMCHECK)
	{
		CState::GetInstance().ChangeState(CAlarmCheck::GetInstance());	
	}
	else if (m_MenuState == MENUSTATE::TIMER)
	{
		if (CState::GetInstance().m_SetTimer == true)
		{
			CState::GetInstance().ChangeState(CTimer::GetInstance());
		}
		else
		{
			CTimeSetting::GetInstance().SetTimeSetting(
			"   Set  Timer",
			&CState::GetInstance().m_TimerTime, TIMESETTINGSTATE::TIMER);
			CState::GetInstance().ChangeState(CTimeSetting::GetInstance());
		}
	}
	else if (m_MenuState == MENUSTATE::STOPWATCH)
	{
		CState::GetInstance().ChangeState(CStopwatch::GetInstance());
	}
}

void CMenu::OnClickSwitch02()
{
	m_StandingCount = 0;
}

void CMenu::OnClickSwitch03()
{
	m_StandingCount = 0;
	
	memset(m_MenuPrintText1, ' ', sizeof(m_MenuPrintText1));
	memset(m_MenuPrintText2, ' ', sizeof(m_MenuPrintText2));
	if (--m_MenuState < MENUSTATE::CURRENTTIME) m_MenuState = MENUSTATE::CURRENTTIME;
}

void CMenu::OnClickSwitch04()
{
	m_StandingCount = 0;
	
	memset(m_MenuPrintText1, ' ', sizeof(m_MenuPrintText1));
	memset(m_MenuPrintText2, ' ', sizeof(m_MenuPrintText2));
	if (++m_MenuState > MENUSTATE::STOPWATCH) m_MenuState = MENUSTATE::STOPWATCH;
}

void CMenu::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_MenuPrintText1, ' ', sizeof(m_MenuPrintText1));
	memset(m_MenuPrintText2, ' ', sizeof(m_MenuPrintText2));
	
	m_TimeCount = 0;
	m_StandingCount = 0;
	
	lcd.Clear();
}

void CMenu::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_MenuPrintText1, ' ', sizeof(m_MenuPrintText1));
	memset(m_MenuPrintText2, ' ', sizeof(m_MenuPrintText2));
	
	m_TimeCount = 0;
	m_StandingCount = 0;
	
	lcd.Clear();
}