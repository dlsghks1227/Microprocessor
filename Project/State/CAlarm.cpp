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
	m_TextShiftCount = 0;
	
	m_ShuffleTime = 0;
	m_TimeCount = 0;
	
	m_ButtonClickCount = 0;
	
	m_Blink = false;
} //CAlarm

// default destructor
CAlarm::~CAlarm()
{
} //~CAlarm

void CAlarm::Display(CLCD& lcd)
{
	if (m_Enable == true)
	{
		//sprintf(m_AlarmPrintText1, "Press Button");
		for (int i = 0; i < 16; i++)
		{
			m_AlarmPrintText1[i] = m_HelpText[(m_TextShiftCount + i) % 23];
		}
		sprintf(m_AlarmPrintText2, "Input: %d%d%d%d",
			m_ButtonClick[0],
			m_ButtonClick[1],
			m_ButtonClick[2],
			m_ButtonClick[3]);
		
		lcd.PrintLine_1(m_AlarmPrintText1);
		lcd.PrintLine_2(m_AlarmPrintText2);
	}
}

void CAlarm::Update()
{
	if (m_ButtonClickCount >= 4)
	{
		CBuzzer::GetInstance().Off();
		CState::GetInstance().ChangeState(CEnglishPrint::GetInstance());
	}
	
	if (m_Blink == true)
	{
		m_AlarmPrintText2[7 + m_ButtonClickCount] = 0xFF;
	}
	
	if (m_TimeCount > 100)
	{
		m_TimeCount = 0;
		m_Blink = !m_Blink;
		if (++m_TextShiftCount >= 23) m_TextShiftCount = 0;
		if (++m_ShuffleTime > 40)
		{
			m_ShuffleTime = 0;
			this->ResetButtonClick();
		}
	}
	
	m_TimeCount++;
	
	CFND::GetInstance().DisplaySplit(m_Order[0], m_Order[1], m_Order[2], m_Order[3]);
}

void CAlarm::OnClickSwitch01()
{
	if (m_Order[m_ButtonClickCount] == 1)
	{
		m_ButtonClick[m_ButtonClickCount] = 1;
		m_ButtonClickCount++;
	}
	else
	{
		this->ResetButtonClick();
	}
}

void CAlarm::OnClickSwitch02()
{
	if (m_Order[m_ButtonClickCount] == 2)
	{
		m_ButtonClick[m_ButtonClickCount] = 2;
		m_ButtonClickCount++;
	}
	else
	{
		this->ResetButtonClick();
	}
}

void CAlarm::OnClickSwitch03()
{
	if (m_Order[m_ButtonClickCount] == 3)
	{
		m_ButtonClick[m_ButtonClickCount] = 3;
		m_ButtonClickCount++;
	}
	else
	{
		this->ResetButtonClick();
	}
}

void CAlarm::OnClickSwitch04()
{
	if (m_Order[m_ButtonClickCount] == 4)
	{
		m_ButtonClick[m_ButtonClickCount] = 4;
		m_ButtonClickCount++;
	}
	else
	{
		this->ResetButtonClick();
	}
}

void CAlarm::OnEnterState(CLCD& lcd)
{
	m_Enable = true;
	
	// LCD 메시지 초기화
	memset(m_AlarmPrintText1, ' ', sizeof(m_AlarmPrintText1));
	memset(m_AlarmPrintText2, ' ', sizeof(m_AlarmPrintText2));
	
	this->Shuffle(10);
	
	lcd.Clear();
}

void CAlarm::OnExitState(CLCD& lcd)
{
	m_Enable = false;
	
	// LCD 메시지 초기화
	memset(m_AlarmPrintText1, ' ', sizeof(m_AlarmPrintText1));
	memset(m_AlarmPrintText2, ' ', sizeof(m_AlarmPrintText2));
	
	m_TextShiftCount = 0;
		
	m_ShuffleTime = 0;
	m_TimeCount = 0;
		
	m_ButtonClickCount = 0;
		
	m_Blink = false;
	
	ResetButtonClick();
	
	lcd.Clear();
}

void CAlarm::Shuffle(int count)
{
	for (int i = 0; i < count; i++)
	{
		int pos1 = rand() % 4;
		int pos2 = rand() % 4;
		int temp = m_Order[pos1];
		m_Order[pos1] = m_Order[pos2];
		m_Order[pos2] = temp;
	}
}

void CAlarm::ResetButtonClick()
{
	for (int i = 0; i < 4; i++)
	{
		m_ButtonClick[i] = 0;
	}
	m_ButtonClickCount = 0;
	
	this->Shuffle(10);
}