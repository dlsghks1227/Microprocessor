/* 
* CMenu.h
*
* Created: 2020-12-10 오전 4:41:42
* Author: lh122
*/


#ifndef __CMENU_H__
#define __CMENU_H__

#include <avr/io.h>
#include <stdio.h>

#include "CStateBase.h"
#include "CState.h"

class CMenu : public CStateBase
{
public:
	static CMenu& GetInstance() { return m_Instance;}
	
	CMenu();
	~CMenu();

public:
	void Display(CLCD& lcd) override;
	
	void Update()			override;
	
	void OnClickSwitch01()	override;
	void OnClickSwitch02()	override;
	void OnClickSwitch03()	override;
	void OnClickSwitch04()	override;
	
	void OnEnterState(CLCD& lcd)	override;
	void OnExitState(CLCD& lcd)		override;

private:
	typedef enum _MENUSTATE
	{
		CURRENTTIME,
		CURRENTTIMESET,
		ALARMSET,
		ALARMCHECK,
		TIMER,
		STOPWATCH,
	} MENUSTATE;
	
	const char	m_MenuText[6][16] = { "1. Curr Time   ", "2. Time Set    ", "3. Alarm Set   ", "4. Alm check   ", "5. Timer       ", "6. Stopwatch   "};

private:
	int			m_MenuState;
	char		m_MenuPrintText1[16] = { 0x00 };
	char		m_MenuPrintText2[16] = { 0x00 };
	
	int			m_TimeCount;
	int			m_StandingCount;
	bool		m_Blink;
	

private:
	static CMenu m_Instance;
};

#endif //__CMENU_H__
