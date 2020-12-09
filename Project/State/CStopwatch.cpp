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
} //CStopwatch

// default destructor
CStopwatch::~CStopwatch()
{
} //~CStopwatch

void CStopwatch::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_TimePrintText, "    %02d:%02d:%02d", CState::GetInstance().m_CurrentTime.GetHour(), CState::GetInstance().m_CurrentTime.GetMinute(),CState::GetInstance().m_CurrentTime.GetSecond());
		
		lcd.PrintLine_1("Stopwatch");
		lcd.PrintLine_2(m_TimePrintText);
	}
}

void CStopwatch::Update()
{
}

void CStopwatch::OnClickSwitch01()
{
}

void CStopwatch::OnClickSwitch02()
{
}

void CStopwatch::OnClickSwitch03()
{
}

void CStopwatch::OnClickSwitch04()
{
}

void CStopwatch::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText, ' ', sizeof(m_TimePrintText));
	
	lcd.Clear();
}

void CStopwatch::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_TimePrintText, ' ', sizeof(m_TimePrintText));
	
	lcd.Clear();
}