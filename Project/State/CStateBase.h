/*
 * CTimeStateBase.h
 *
 * Created: 2020-11-30 오후 11:36:50
 *  Author: lh122
 */ 


#ifndef CSTATEBASE_H_
#define CSTATEBASE_H_

#include <string.h>
#include <stdlib.h>

#include "../Lib/CLCD.h"
#include "../Lib/CADC.h"
#include "../Lib/CDelay.h"

class CTime
{
public:
	CTime() : m_hour(0), m_minute(0), m_second(0), m_centiSecond(0) {}
	CTime(int _hour, int _minute, int _second) : m_hour(_hour % 24), m_minute(_minute % 60), m_second(_second % 60), m_centiSecond(0) {}
	CTime(int _hour, int _minute, int _second, int _cs) : m_hour(_hour % 24), m_minute(_minute % 60), m_second(_second % 60), m_centiSecond(_cs % 100) {}
	~CTime() {}
	
public:
	void SetTime(int _hour, int _minute, int _second)
	{
		m_hour = _hour % 24;
		m_minute = _minute % 60;
		m_second = _second % 60;
	}
	void SetTime(int _hour, int _minute, int _second, int _cs)
	{
		m_hour = _hour % 24;
		m_minute = _minute % 60;
		m_second = _second % 60;
		m_centiSecond = _cs % 100;
	}
	void SetTime(CTime t)
	{
		SetTime(t.m_hour, t.m_minute, t.m_second, t.m_centiSecond);
	}
	
	void	SetHour(int value)			{ m_hour = value; }
	int		GetHour()					{ return m_hour % 24; }
	
	void	SetMinute(int value)		{ m_minute = value; }
	int		GetMinute()					{ return m_minute % 60; }
	
	void	SetSecond(int value)		{ m_second = value; }
	int		GetSecond()					{ return m_second % 60; }
	
	void	SetCentiSecond(int value)	{ m_centiSecond = value; }
	int		GetCentiSecond()			{ return m_centiSecond % 100; }
		
public:
	bool	operator==(const CTime& ref) const
	{
		return ((m_hour == ref.m_hour) && (m_minute == ref.m_minute) && (m_second == ref.m_second));
	}
	
	// 전위 증감 연산
	CTime operator++()
	{
		if (++m_second >= 60) {
			m_second = 0;
			if (++m_minute >= 60) {
				m_minute = 0;
				if (++m_hour >= 24) {
					m_hour = 0;
				}
			}
			
		}
		return *this;
	}
	
	CTime operator--()
	{
		if (--m_second < 0) {
			m_second = 59;
			if (--m_minute < 0) {
				m_minute = 59;
				if (--m_hour < 0) {
					m_hour = 23;
				}
			}
		}
		return *this;
	}
	
	// 후위 증감 연산
	CTime operator++(int)
	{
		if (++m_second >= 60) {
			m_second = 0;
			if (++m_minute >= 60) {
				m_minute = 0;
				if (++m_hour >= 24) {
					m_hour = 0;
				}
			}
			
		}
		return *this;
	}
	
	CTime operator--(int)
	{
		if (--m_second < 0) {
			m_second = 59;
			if (--m_minute < 0) {
				m_minute = 59;
				if (--m_hour < 0) {
					m_hour = 23;
				}
			}
		}
		return *this;
	}
private:
	int m_hour;
	int m_minute;
	int m_second;
	int m_centiSecond;
};

typedef enum _TIMESETTINGSTATE
{
	CURRENT,
	ALARM,
	TIMER,
} TIMESETTINGSTATE;

class CStateBase
{
public:
	CStateBase()
	{
		m_Enable = false;
	};
	~CStateBase()	{};
	
public:
	virtual	void Display(CLCD& lcd) = 0;
	
	virtual void Update() = 0;

	virtual void OnClickSwitch01() = 0;
	virtual void OnClickSwitch02() = 0;
	virtual void OnClickSwitch03() = 0;
	virtual void OnClickSwitch04() = 0;
	
	virtual void OnEnterState(CLCD& lcd) = 0;
	virtual void OnExitState(CLCD& lcd) = 0;
	
public:
	CDelay	m_Delay;
	
	bool	m_Enable;
}; //CTimeState

#endif /* CSTATEBASE_H_ */