/*
 * CDelay.h
 *
 * Created: 2020-11-23 오후 4:33:00
 *  Author: 이인환
 */ 


#ifndef DELAY_H_
#define DELAY_H_


class CDelay
{
public:
	CDelay()  {}
	~CDelay() {}
	
	void Delay_us(char time_us)
	{
		char i;
		
		for(i = 0; i < time_us; i++)
		{
			asm volatile(" PUSH R0");
			asm volatile(" POP R0");
			asm volatile(" PUSH R0");
			asm volatile(" POP R0");
			asm volatile(" PUSH R0");
			asm volatile(" POP R0");
		}
	}
	
	void Delay_ms(unsigned int time_ms)
	{
			unsigned int i;
			
			for(i = 0; i < time_ms; i++)
			{
				this->Delay_us(250);
				this->Delay_us(250);
				this->Delay_us(250);
				this->Delay_us(250);
			}
	}
};

#endif /* CDELAY_H_ */