/* 
* CRecordList.cpp
*
* Created: 2020-12-10 오후 3:41:50
* Author: 이인환
*/


#include "CRecordList.h"

CRecordList CRecordList::m_Instance;

CRecordList::CRecordList()
{
	m_RecordState = 0;
}

CRecordList::~CRecordList()
{
	
}

void CRecordList::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_RecordPrintText1, "%d. %02d:%02d:%02d.%02d ", ((m_RecordState / 2) * 2),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2)].GetHour(),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2)].GetMinute(),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2)].GetSecond(),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2)].GetCentiSecond());
		sprintf(m_RecordPrintText2, "%d. %02d:%02d:%02d.%02d ", ((m_RecordState / 2) * 2) + 1,
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2) + 1].GetHour(),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2) + 1].GetMinute(),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2) + 1].GetSecond(),
			CState::GetInstance().m_RecordList[((m_RecordState / 2) * 2) + 1].GetCentiSecond());
		
		lcd.PrintLine_1(m_RecordPrintText1);
		lcd.PrintLine_2(m_RecordPrintText2);
	}
}

void CRecordList::Update()
{
	if (m_Blink == true)
	{
		if (m_RecordState % 2 == 0)
		{
			m_RecordPrintText1[14] = '<';
		}
		else
		{
			m_RecordPrintText2[14] = '<';
		}
	}
	
	if (m_TimeCount >= 100)
	{
		m_TimeCount = 0;
		m_Blink = !m_Blink;
	}
	
	m_TimeCount++;
}

void CRecordList::OnClickSwitch01()
{
	CState::GetInstance().ChangeState(CStopwatch::GetInstance());
}

void CRecordList::OnClickSwitch02()
{
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CRecordList::OnClickSwitch03()
{
	memset(m_RecordPrintText1, ' ', sizeof(m_RecordPrintText1));
	memset(m_RecordPrintText2, ' ', sizeof(m_RecordPrintText2));
	if (--m_RecordState < 0) m_RecordState = 0;
}

void CRecordList::OnClickSwitch04()
{
	memset(m_RecordPrintText1, ' ', sizeof(m_RecordPrintText1));
	memset(m_RecordPrintText2, ' ', sizeof(m_RecordPrintText2));
	if (++m_RecordState >= (int)(sizeof(CState::GetInstance().m_RecordList) / sizeof(CTime))) m_RecordState = (int)(sizeof(CState::GetInstance().m_RecordList) / sizeof(CTime)) - 1;
}

void CRecordList::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	memset(m_RecordPrintText1, ' ', sizeof(m_RecordPrintText1));
	memset(m_RecordPrintText2, ' ', sizeof(m_RecordPrintText2));
	
	m_RecordState = 0;
	
	lcd.Clear();
}

void CRecordList::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	memset(m_RecordPrintText1, ' ', sizeof(m_RecordPrintText1));
	memset(m_RecordPrintText2, ' ', sizeof(m_RecordPrintText2));
	
	m_RecordState = 0;
	
	lcd.Clear();
}