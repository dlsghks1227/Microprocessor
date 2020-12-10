/* 
* CEnglishPrint.h
*
* Created: 2020-12-11 오전 1:20:20
* Author: lh122
*/


#ifndef __CENGLISHPRINT_H__
#define __CENGLISHPRINT_H__

#include "CStateBase.h"
#include "CState.h"

class CEnglishPrint : public CStateBase
{
public:
	static CEnglishPrint& GetInstance() { return m_Instance;}

	CEnglishPrint();
	~CEnglishPrint();

public:
	void Display(CLCD& lcd) override;

	void Update()			override;

	void OnClickSwitch01()	override;
	void OnClickSwitch02()	override;
	void OnClickSwitch03()	override;
	void OnClickSwitch04()	override;

	void OnEnterState(CLCD& lcd)	override;
	void OnExitState(CLCD& lcd)		override;

public:
	char	m_EnglishPrintText1[16] = { 0x00 };
	char	m_EnglishPrintText2[16] = { 0x00 };
		
	int		m_TextShiftCount;
	int		m_TimeCount;
	int		m_RandomIndex;

private:
	static CEnglishPrint m_Instance;
}; //CEnglishPrint

#endif //__CENGLISHPRINT_H__
