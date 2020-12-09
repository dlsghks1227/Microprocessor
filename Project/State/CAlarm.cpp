/* 
* CAlarm.cpp
*
* Created: 2020-12-10 오전 6:43:18
* Author: lh122
*/


#include "CAlarm.h"

CAlarm CAlarm::m_Instance;

// default constructor
CAlarm::CAlarm()
{
} //CAlarm

// default destructor
CAlarm::~CAlarm()
{
} //~CAlarm

void CAlarm::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_TimePrintText, "    %02d:%02d:%02d", CState::GetInstance().m_CurrentTime.GetHour(), CState::GetInstance().m_CurrentTime.GetMinute(),CState::GetInstance().m_CurrentTime.GetSecond());
		
		lcd.PrintLine_1("Alarm");
		lcd.PrintLine_2(m_TimePrintText);
	}
}

void CAlarm::Update()
{
}

void CAlarm::OnClickSwitch01()
{
}

void CAlarm::OnClickSwitch02()
{
}

void CAlarm::OnClickSwitch03()
{
}

void CAlarm::OnClickSwitch04()
{
}

void CAlarm::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText, ' ', sizeof(m_TimePrintText));
	
	lcd.Clear();
}

void CAlarm::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText, ' ', sizeof(m_TimePrintText));
	
	lcd.Clear();
}