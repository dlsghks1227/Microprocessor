/* 
* CEnglishPrint.cpp
*
* Created: 2020-12-11 오전 1:20:20
* Author: lh122
*/


#include "CEnglishPrint.h"

const char* TodayEnglishList[6] = {
	"Seeing is believing. ",
	"Whatever you do, make it pay. ",
	"You will never know until you try. ",
	"No sweat, no sweet. ",
	"Do not be afraid to give up the good to go for the great. ",
	"I never dreamed about success, I worked for it. "
};

CEnglishPrint CEnglishPrint::m_Instance;

// default constructor
CEnglishPrint::CEnglishPrint()
{
	m_TextShiftCount = 0;
	m_TimeCount = 0;
	m_RandomIndex = rand() % 6;
} //CEnglishPrint

// default destructor
CEnglishPrint::~CEnglishPrint()
{
} //~CEnglishPrint

void CEnglishPrint::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		sprintf(m_EnglishPrintText1, "Today's English");
		for (int i = 0; i < 16; i++)
		{
			m_EnglishPrintText2[i] = TodayEnglishList[m_RandomIndex][(m_TextShiftCount + i) % strlen(TodayEnglishList[m_RandomIndex])];
		}
		
		lcd.PrintLine_1(m_EnglishPrintText1);
		lcd.PrintLine_2(m_EnglishPrintText2);
	}
}

void CEnglishPrint::Update()
{
	if (m_TimeCount > 100)
	{
		m_TimeCount = 0;
		if (++m_TextShiftCount >= strlen(TodayEnglishList[m_RandomIndex])) m_TextShiftCount = 0;
	}
	m_TimeCount++;
}

void CEnglishPrint::OnClickSwitch01()
{
	CState::GetInstance().ChangeState(CMenu::GetInstance());
}

void CEnglishPrint::OnClickSwitch02()
{
}

void CEnglishPrint::OnClickSwitch03()
{
}

void CEnglishPrint::OnClickSwitch04()
{
}

void CEnglishPrint::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_EnglishPrintText1, ' ', sizeof(m_EnglishPrintText1));
	memset(m_EnglishPrintText2, ' ', sizeof(m_EnglishPrintText2));
	
	m_TextShiftCount = 0;
	m_TimeCount = 0;
	
	m_RandomIndex = rand() % 6;

	lcd.Clear();
}

void CEnglishPrint::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_EnglishPrintText1, ' ', sizeof(m_EnglishPrintText1));
	memset(m_EnglishPrintText2, ' ', sizeof(m_EnglishPrintText2));
	
	m_TextShiftCount = 0;
	m_TimeCount = 0;
	
	lcd.Clear();
}