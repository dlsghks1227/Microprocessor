/* 
* CRecordList.h
*
* Created: 2020-12-10 오후 3:41:51
* Author: 이인환
*/


#ifndef __CRECORDLIST_H__
#define __CRECORDLIST_H__

#include "CStateBase.h"
#include "CState.h"

class CRecordList : public CStateBase
{
public:
	static CRecordList& GetInstance() { return m_Instance;}

	CRecordList();
	~CRecordList();

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
	int		m_RecordState;
	char	m_RecordPrintText1[16] = { 0x00 };
	char	m_RecordPrintText2[16] = { 0x00 };
		
	int		m_TimeCount;
	bool	m_Blink;

private:
	static CRecordList m_Instance;
}; //CRecordList

#endif //__CRECORDLIST_H__
