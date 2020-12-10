/* 
* CStopwatch.cpp
*
* Created: 2020-12-10 오전 6:43:31
* Author: lh122
*/


#include "CStopwatch.h"

CStopwatch CStopwatch::m_Instance;

// default constructor
CStopwatch::CStopwatch()
{
	m_RecordCount = 0;
	m_TimeCount = 0;
	m_IsStarted = false;
} //CStopwatch

// default destructor
CStopwatch::~CStopwatch()
{
} //~CStopwatch

void CStopwatch::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_TimePrintText1, "SW  %02d:%02d:%02d.%02d",
			CState::GetInstance().m_StopwatchTime.GetHour(),
			CState::GetInstance().m_StopwatchTime.GetMinute(),
			CState::GetInstance().m_StopwatchTime.GetSecond(),
			CState::GetInstance().m_StopwatchTime.GetCentiSecond());
		
		int CountTemp = m_RecordCount == 0 ? 9 : m_RecordCount - 1;
		sprintf(m_TimePrintText2, "REC %02d:%02d:%02d.%02d",
			CState::GetInstance().m_RecordList[CountTemp].GetHour(),
			CState::GetInstance().m_RecordList[CountTemp].GetMinute(),
			CState::GetInstance().m_RecordList[CountTemp].GetSecond(),
			CState::GetInstance().m_RecordList[CountTemp].GetCentiSecond());
		
		lcd.PrintLine_1(m_TimePrintText1);
		lcd.PrintLine_2(m_TimePrintText2);
	}
}

void CStopwatch::Update()
{
	if (m_IsStarted == true)
	{
		if (m_TimeCount > 200)
		{
			m_TimeCount = 0;
			CState::GetInstance().m_StopwatchTime++;
		}
		m_TimeCount++;
		CState::GetInstance().m_StopwatchTime.SetCentiSecond((m_TimeCount / 2) % 100);
	}
}

void CStopwatch::OnClickSwitch01()
{
	// 기록 보기
	CState::GetInstance().ChangeState(CRecordList::GetInstance());
}

void CStopwatch::OnClickSwitch02()
{
	// 돌아가기
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CStopwatch::OnClickSwitch03()
{
	// 기록 및 재설정
	if (m_IsStarted == true)
	{
		CState::GetInstance().m_RecordList[m_RecordCount].SetTime(CState::GetInstance().m_StopwatchTime);
		if (++m_RecordCount >= (int)(sizeof(CState::GetInstance().m_RecordList) / sizeof(CTime)))
		{
			m_RecordCount = 0;
		}
	}
	else
	{
		m_TimeCount = 0;
		m_RecordCount = 0;
		CState::GetInstance().ResetRecordList();
		CState::GetInstance().m_StopwatchTime.SetTime(0, 0, 0, 0);

	}
}

void CStopwatch::OnClickSwitch04()
{
	// 시작 또는 중단
	m_IsStarted = !m_IsStarted;
}

void CStopwatch::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText1, ' ', sizeof(m_TimePrintText1));
	memset(m_TimePrintText2, ' ', sizeof(m_TimePrintText2));
	
	lcd.Clear();
}

void CStopwatch::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText1, ' ', sizeof(m_TimePrintText1));
	memset(m_TimePrintText2, ' ', sizeof(m_TimePrintText2));
	
	lcd.Clear();
}