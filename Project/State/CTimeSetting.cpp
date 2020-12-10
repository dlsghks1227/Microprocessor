/*
* CTimeSet.cpp
*
* Created: 2020-12-01 오전 1:22:22
* Author: lh122
*/


#include "CTimeSetting.h"

CTimeSetting CTimeSetting::m_Instance;

CTimeSetting::CTimeSetting()
{
	m_TimeState = TIMESTATE::SECOND;
	m_TimeCount = 0;
	m_Blink = false;
}

CTimeSetting::~CTimeSetting()
{
	
}

void CTimeSetting::SetTimeSetting(const char* msg, CTime* t)
{
	strcpy(this->m_Title, msg);
	m_pSetTime = t;
}

void CTimeSetting::Display(CLCD& lcd)
{	
	if (m_Enable == true)
	{
		//CState::GetInstance().SetCurrentTime(CTime(60, 10, 10));
		sprintf(m_SetTimeText, "    %02d:%02d:%02d", m_Time.GetHour(), m_Time.GetMinute(), m_Time.GetSecond());
		
		lcd.PrintLine_1(m_Title);
		lcd.PrintLine_2(m_SetTimeText);
	}
}

void CTimeSetting::Update()
{
	if (m_TimeState == TIMESTATE::SECOND)
	{
		m_Time.SetSecond(CADC::GetInstance().GetPercentValue() * 59 / 100);
		m_BlinkPos = 10;
	}
	else if (m_TimeState == TIMESTATE::MINUTE)
	{
		m_Time.SetMinute(CADC::GetInstance().GetPercentValue() * 59 / 100);
		m_BlinkPos = 7;
	}
	else if (m_TimeState == TIMESTATE::HOUR)
	{
		m_Time.SetHour(CADC::GetInstance().GetPercentValue() * 23 / 100);
		m_BlinkPos = 4;
	}
	
	if (m_Blink == true)
	{
		m_SetTimeText[m_BlinkPos] = 0xFF;
		m_SetTimeText[m_BlinkPos + 1] = 0xFF;
	}
	
	if (m_TimeCount >= 100)
	{
		m_TimeCount = 0;
		m_Blink = !m_Blink;
	}
	
	m_TimeCount++;
}

void CTimeSetting::OnClickSwitch01()
{
	m_pSetTime->SetTime(m_Time);
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CTimeSetting::OnClickSwitch02()
{
	m_pSetTime->SetTime(m_Time);
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CTimeSetting::OnClickSwitch03()
{
	if (--m_TimeState < TIMESTATE::HOUR) m_TimeState = TIMESTATE::HOUR;
}

void CTimeSetting::OnClickSwitch04()
{
	if (++m_TimeState > TIMESTATE::SECOND) m_TimeState = TIMESTATE::SECOND;
}

void CTimeSetting::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	memset(m_SetTimeText, ' ', sizeof(m_SetTimeText));
	
	lcd.Clear();
}

void CTimeSetting::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	memset(m_Title, ' ', sizeof(m_Title));
	memset(m_SetTimeText, ' ', sizeof(m_SetTimeText));
	
	lcd.Clear();
}