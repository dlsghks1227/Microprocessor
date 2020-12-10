/* 
* CCurrentTime.cpp
*
* Created: 2020-12-10 오전 6:24:31
* Author: lh122
*/


#include "CCurrentTime.h"

CCurrentTime CCurrentTime::m_Instance;

// default constructor
CCurrentTime::CCurrentTime()
{
} //CCurrentTime

// default destructor
CCurrentTime::~CCurrentTime()
{
} //~CCurrentTime

void CCurrentTime::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_TimePrintText, "    %02d:%02d:%02d",
			CState::GetInstance().m_CurrentTime.GetHour(),
			CState::GetInstance().m_CurrentTime.GetMinute(),
			CState::GetInstance().m_CurrentTime.GetSecond());
		
		lcd.PrintLine_1("  Current Time");
		lcd.PrintLine_2(m_TimePrintText);
	}
}

void CCurrentTime::Update()
{
}

void CCurrentTime::OnClickSwitch01()
{
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CCurrentTime::OnClickSwitch02()
{
}

void CCurrentTime::OnClickSwitch03()
{
}

void CCurrentTime::OnClickSwitch04()
{
}

void CCurrentTime::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText, ' ', sizeof(m_TimePrintText));
	
	lcd.Clear();
}

void CCurrentTime::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText, ' ', sizeof(m_TimePrintText));
	
	lcd.Clear();
}