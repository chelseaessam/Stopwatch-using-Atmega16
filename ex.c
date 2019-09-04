#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
unsigned char seconds1=0;
unsigned char seconds2=0;
unsigned char min1=0;
unsigned char min2=0;
unsigned char hour1=0;
unsigned char hour2=0;
unsigned char flag=0;
void Timer1_init(void);
int main()
{
	DDRC|=0x0f;
	PORTC&=~(0x0f);

	DDRD|=0xf3;
	PORTD|=0xf3;

	DDRA&=~(1<<0);


	Timer1_init();
	for(;;)
	{
		if(PINA&(1<<0))
		{
			seconds1=0;seconds2=0;min1=0;min2=0;hour1=0;hour2=0;
		}
		else if(flag==1)
		{
			flag=0;
			seconds1++;
			if(seconds1==10)
			{
				seconds2++;
				seconds1=0;
			}
			if(seconds1==0 && seconds2==6)
			{
				seconds2=0;
				min1++;
			}
			if(min1==10)
			{
				min2++;
				min1=0;
			}
			if(min1==0 &&min2==6)
			{
				min2=0;
				hour1++;
			}
			if(hour1==10)
			{
				hour2++;
				hour1=0;
			}

		}


		PORTD&=~0xf3;
		PORTD|=(1<<6);
		PORTC=(PORTC&0xf0)|(seconds1&0x0f);
		_delay_ms(20);

		PORTD&=~0xf3;
		PORTD|=(1<<7);
		PORTC=(PORTC&0xf0)|(seconds2&0x0f);
		_delay_ms(20);

		PORTD&=~0xf3;
		PORTD|=(1<<5);
		PORTC=(PORTC&0xf0)|(min1&0x0f);
		_delay_ms(20);

		PORTD&=~0xf3;
		PORTD|=(1<<4);
		PORTC=(PORTC&0xf0)|(min2&0x0f);
		_delay_ms(20);


		PORTD&=~0xf3;
		PORTD|=(1<<3);
		PORTC=(PORTC&0xf0)|(hour1&0x0f);
		_delay_ms(20);

		PORTD&=~0xf3;
		PORTD|=(1<<2);
		PORTC=(PORTC&0xf0)|(hour2&0x0f);
		_delay_ms(20);



	}

}
void Timer1_init(void)
{
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);//non pwm
	TCCR1B=(1<<WGM12)|(1<<CS10)|(1<<CS12);// CTC + prescalar 1024
	TCNT1=0;
	OCR1A=1000;
	TIMSK|=(1<<OCIE1A);
	SREG|=(1<<7);
}
ISR(TIMER1_COMPA_vect)
{
	flag=1;
}
