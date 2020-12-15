/* 
* CAlarmCheck.cpp
*
* Created: 2020-12-10 오전 6:52:45
* Author: lh122
*/


#include "CAlarmCheck.h"

CAlarmCheck CAlarmCheck::m_Instance;

// default constructor
CAlarmCheck::CAlarmCheck()
{
} //CAlarmCheck

// default destructor
CAlarmCheck::~CAlarmCheck()
{
} //~CAlarmCheck

void CAlarmCheck::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_TimePrintText1, "Cur: %02d:%02d:%02d",
			CState::GetInstance().m_CurrentTime.GetHour(),
			CState::GetInstance().m_CurrentTime.GetMinute(),
			CState::GetInstance().m_CurrentTime.GetSecond());

		if (CState::GetInstance().m_SetAlarm == true)
		{
			sprintf(m_TimePrintText2, "Alm: %02d:%02d:%02d",
				CState::GetInstance().m_AlarmTime.GetHour(),
				CState::GetInstance().m_AlarmTime.GetMinute(),
				CState::GetInstance().m_AlarmTime.GetSecond());
		}
		else
		{
			sprintf(m_TimePrintText2, "    No Alarm");
		}
		
		lcd.PrintLine_1(m_TimePrintText1);
		lcd.PrintLine_2(m_TimePrintText2);
	}
}

void CAlarmCheck::Update()
{
}

void CAlarmCheck::OnClickSwitch01()
{
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CAlarmCheck::OnClickSwitch02()
{
	CState::GetInstance().m_SetAlarm = false;
	CState::GetInstance().m_AlarmTime.SetTime(0, 0, 0, 0);
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CAlarmCheck::OnClickSwitch03()
{
}

void CAlarmCheck::OnClickSwitch04()
{
}

void CAlarmCheck::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText1, ' ', sizeof(m_TimePrintText1));
	memset(m_TimePrintText2, ' ', sizeof(m_TimePrintText2));
	
	lcd.Clear();
}

void CAlarmCheck::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText1, ' ', sizeof(m_TimePrintText1));
	memset(m_TimePrintText2, ' ', sizeof(m_TimePrintText2));
	
	lcd.Clear();
}