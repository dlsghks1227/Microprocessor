/* 
* CButton.h
*
* Created: 2020-11-27 오전 12:56:41
* Author: lh122
*/


#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include <avr/io.h>
#include <avr/interrupt.h>

class CButton
{
//variables
public:
protected:
private:

//functions
public:
	CButton();
	~CButton();
	
	friend void INT4_vect();
protected:
private:
	CButton( const CButton &c );
	CButton& operator=( const CButton &c );

}; //CButton

#endif //__CBUTTON_H__
