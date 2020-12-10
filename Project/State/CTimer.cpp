/* 
* CTimer.cpp
*
* Created: 2020-11-30 오후 11:38:33
* Author: lh122
*/


#include "CTimer.h"

CTimer CTimer::m_Instance;

CTimer::CTimer()
{
}

CTimer::~CTimer()
{
	
}

void CTimer::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_TimerPrintText1, "Time: %02d:%02d:%02d",
			CState::GetInstance().m_TimerTime.GetHour(),
			CState::GetInstance().m_TimerTime.GetMinute(),
			CState::GetInstance().m_TimerTime.GetSecond());
		sprintf(m_TimerPrintText2, "SW2:Cancel/Stop");
		lcd.PrintLine_1(m_TimerPrintText1);
		lcd.PrintLine_2(m_TimerPrintText2);
	}
}

void CTimer::Update()
{
}

void CTimer::OnClickSwitch01()
{
	CBuzzer::GetInstance().Off();
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CTimer::OnClickSwitch02()
{
	CBuzzer::GetInstance().Off();
	CState::GetInstance().m_SetTimer = false;
	CState::GetInstance().m_TimerTime.SetTime(0, 0, 0, 0);
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CTimer::OnClickSwitch03()
{
}

void CTimer::OnClickSwitch04()
{
}

void CTimer::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	memset(m_TimerPrintText1, ' ', sizeof(m_TimerPrintText1));
	memset(m_TimerPrintText2, ' ', sizeof(m_TimerPrintText2));
	
	lcd.Clear();
}

void CTimer::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	memset(m_TimerPrintText1, ' ', sizeof(m_TimerPrintText1));
	memset(m_TimerPrintText2, ' ', sizeof(m_TimerPrintText2));
	
	lcd.Clear();
}