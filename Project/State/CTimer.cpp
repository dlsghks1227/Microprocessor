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
		sprintf(msg, "Time: %02d:%02d:%02d", CState::GetInstance().m_CurrentTime.GetHour(), CState::GetInstance().m_CurrentTime.GetMinute(),CState::GetInstance().m_CurrentTime.GetSecond());
		lcd.PrintLine_1(msg);
	}
}

void CTimer::Update()
{
}

void CTimer::OnClickSwitch01()
{
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CTimer::OnClickSwitch02()
{
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
	
	memset(msg, ' ', sizeof(msg));
	
	lcd.Clear();
}

void CTimer::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	memset(msg, ' ', sizeof(msg));
	
	lcd.Clear();
}