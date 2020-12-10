/* 
* CStopwatch.h
*
* Created: 2020-12-10 오전 6:43:31
* Author: lh122
*/


#ifndef __CSTOPWATCH_H__
#define __CSTOPWATCH_H__

#include "CStateBase.h"
#include "CState.h"

class CStopwatch : public CStateBase
{
public:
	static CStopwatch& GetInstance() { return m_Instance;}

	CStopwatch();
	~CStopwatch();

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
	char	m_TimePrintText1[16] = { 0x00 };
	char	m_TimePrintText2[16] = { 0x00 };

	int		m_RecordCount;
	int		m_TimeCount;
	bool	m_IsStarted;

private:
	static CStopwatch m_Instance;
}; //CStopwatch

#endif //__CSTOPWATCH_H__