#include "foo.h"  /* Include the header (not strictly necessary here) */
#include "tm4c123gh6pm.h"
//first segment
#define P0 (1<<0) // a
#define P1 (1<<1) // b
#define P2 (1<<2) // c
#define P3 (1<<3) // d
#define P4 (1<<4) // e
#define P5 (1<<5) // f
#define P7 (1<<7) // g

#define P6 (1<<6)


void delay_Microsecond(uint32_t time)
{
    int i;
    SYSCTL_RCGCTIMER_R|=(1U<<1); 
    TIMER1_CTL_R  =0;
    TIMER1_CFG_R=0x04;
    TIMER1_TAMR_R=0x02;
    TIMER1_TAILR_R = 16-1;
    TIMER1_ICR_R =0x1;
    TIMER1_CTL_R |=0x01;
 
    for(i=0;i<time;i++){ 
       while((TIMER1_RIS_R & 0x1)==0){};
        TIMER1_ICR_R = 0x1;
    }
 
}
void first_seven_segment(char num1)
{

		//--------1
		if(num1=='1')
		{
		GPIO_PORTF_DATA_R|=P1;
		GPIO_PORTB_DATA_R|=(P0)|(P3)|(P4)|(P5);
		GPIO_PORTB_DATA_R&=~(P1)&~(P2);
		delay_Microsecond(100000);
		}
		

		//--------2
		else if(num1=='2')
		{
			GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R|=(P2)|(P5);
		GPIO_PORTB_DATA_R&=~(P0)&~(P1)&~(P3)&~(P4);
		delay_Microsecond(100000);
		}
		
		
		//--------3
		else if(num1=='3')
		{
						GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R|=(P4)|(P5);
		GPIO_PORTB_DATA_R&=~(P0)&~(P1)&~(P2)&~(P3);
		delay_Microsecond(100000);
		}
		//--------4
		else if(num1=='4')
		{
			GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R|=(P0)|(P3)|(P4);
		GPIO_PORTB_DATA_R&=~(P1)&~(P2)&~(P5);
		delay_Microsecond(100000);
		}
		//--------5
		else if(num1=='5')
		{
			GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R|=(P1)|(P4);
		GPIO_PORTB_DATA_R&=~(P0)&~(P2)&~(P3)&~(P5);
		delay_Microsecond(100000);
		}
		
		//--------6
		else if(num1=='6')
		{
			GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R|=(P1);
		GPIO_PORTB_DATA_R&=~(P0)&~(P2)&~(P3)&~(P4)&~(P5);
		delay_Microsecond(100000);
		}
		
		//--------7
		else if(num1=='7')
		{
			GPIO_PORTF_DATA_R|=P1;
		GPIO_PORTB_DATA_R|=(P3)|(P4)|(P5);
		GPIO_PORTB_DATA_R&=~(P0)&~(P1)&~(P2);
		delay_Microsecond(100000);
		}
		
		//--------8
		else if(num1=='8')
		{
			GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R&=~(P0)&~(P1)&~(P2)&~(P3)&~(P4)&~(P5);//8
		delay_Microsecond(100000);
		}
		//--------9
		else if(num1=='9')
		{
			GPIO_PORTF_DATA_R&=~P1;
		GPIO_PORTB_DATA_R|=(P3)|(P4);
		GPIO_PORTB_DATA_R&=~(P0)&~(P1)&~(P2)&~(P5);
		delay_Microsecond(100000);
		}
		//--------0
		else
		{
			GPIO_PORTF_DATA_R|=P1;
			GPIO_PORTB_DATA_R&=~(P0)&~(P1)&~(P2)&~(P3)&~(P4)&~(P5);//0
			delay_Microsecond(100000);
		}
}
	


void second_seven_segment(int num1)
{
		GPIO_PORTA_DATA_R|=(P2);
		//--------1
		if(num1==1)
		{
			GPIO_PORTF_DATA_R&=~P2;
			GPIO_PORTC_DATA_R&=~(P6)&~(P5)&~(P4);
			GPIO_PORTC_DATA_R|=(P7);
			GPIO_PORTD_DATA_R&=~(P6);
			delay_Microsecond(70000);
		}
		

		//--------2
		else if(num1==2)
		{
			GPIO_PORTF_DATA_R|=P2;
			GPIO_PORTA_DATA_R&=~(P2);
			GPIO_PORTC_DATA_R&=~(P5);
			GPIO_PORTC_DATA_R|=(P6)|(P7)|(P4);
			GPIO_PORTD_DATA_R|=(P6);
			delay_Microsecond(70000);
		}
		
		
		//--------3
		else if(num1==3)
		{
			GPIO_PORTF_DATA_R|=P2;
		GPIO_PORTC_DATA_R&=~(P5);
		GPIO_PORTD_DATA_R&=~(P6);
		GPIO_PORTC_DATA_R|=(P6)|(P7)|(P4);
		GPIO_PORTD_DATA_R|=(P7);
		delay_Microsecond(70000);
		}
		//--------4
		else if(num1==4)
		{
			GPIO_PORTF_DATA_R&=~P2;
		GPIO_PORTC_DATA_R&=~(P6);
		GPIO_PORTD_DATA_R&=~(P6);
		GPIO_PORTC_DATA_R|=(P5)|(P4)|(P7);
		delay_Microsecond(70000);
		}
		//--------5
		else if(num1==5)
		{
			
		GPIO_PORTC_DATA_R&=~(P7);
		GPIO_PORTD_DATA_R&=~(P6);
		GPIO_PORTC_DATA_R|=(P6)|(P4)|(P5);
		GPIO_PORTF_DATA_R|=P2;
		delay_Microsecond(70000);
		}
		
		//--------6
		else if(num1==6)
		{
			GPIO_PORTF_DATA_R|=P2;
		GPIO_PORTC_DATA_R&=~(P7);
		GPIO_PORTC_DATA_R|=(P6)|(P4)|(P5);
		GPIO_PORTD_DATA_R|=(P6);
		delay_Microsecond(70000);
		}
		
		//--------7
		else if(num1==7)
		{
			GPIO_PORTF_DATA_R&=~P2;
		GPIO_PORTC_DATA_R&=~(P4)&~(P5);
		GPIO_PORTD_DATA_R&=~(P6);
		GPIO_PORTC_DATA_R|=(P6)|(P7);
		delay_Microsecond(70000);
		}
		
		//--------8
		else if(num1==8)
		{
			GPIO_PORTF_DATA_R|=P2;
		GPIO_PORTC_DATA_R|=(P6)|(P4)|(P5)|(P7);
		GPIO_PORTD_DATA_R|=(P6);
		delay_Microsecond(70000);
		}
		
		//--------9
		else if(num1==9)
		{
			GPIO_PORTF_DATA_R&=~P2;
		GPIO_PORTC_DATA_R|=(P6)|(P4)|(P5)|(P7);
		GPIO_PORTD_DATA_R&=~(P6);
		delay_Microsecond(70000);
		}
		
		//--------0
		else
		{
			GPIO_PORTF_DATA_R|=P2;
			GPIO_PORTC_DATA_R&=~(P4);
			GPIO_PORTC_DATA_R|=(P6)|(P7)|(P5);
			GPIO_PORTD_DATA_R|=(P6);//0
			delay_Microsecond(70000);
		}
}


// second done
// third tomorrow
void third_seven_segment(int num1)
{
		GPIO_PORTE_DATA_R|=(P3);
		GPIO_PORTF_DATA_R|=(P3);
		//--------1
		if(num1==1)
		{
		GPIO_PORTF_DATA_R&=~(P3);
		GPIO_PORTD_DATA_R&=~(P2)&~(P1);
		GPIO_PORTD_DATA_R|=(P3);
		GPIO_PORTE_DATA_R&=~(P1)&~(P2);
		delay_Microsecond(70000);
		}
		

		//--------2
		else if(num1==2)
		{
		GPIO_PORTD_DATA_R&=~(P1);
		GPIO_PORTD_DATA_R|=(P2)|(P3);
		GPIO_PORTE_DATA_R&=~(P3);
		GPIO_PORTE_DATA_R|=(P2)|(P1);
		delay_Microsecond(70000);
		}
		
		
		//--------3
		else if(num1==3)
		{
		GPIO_PORTD_DATA_R&=~(P1);
		GPIO_PORTD_DATA_R|=(P2)|(P3);
		GPIO_PORTE_DATA_R&=~(P1);
		GPIO_PORTE_DATA_R|=(P2);
		delay_Microsecond(70000);
		}
		//--------4
		else if(num1==4)
		{
		GPIO_PORTD_DATA_R&=~(P2);
		GPIO_PORTD_DATA_R|=(P3)|(P1);
		GPIO_PORTE_DATA_R&=~(P1)&~(P2);
		delay_Microsecond(70000);
		}
		//--------5
		else if(num1==5)
		{
		GPIO_PORTD_DATA_R&=~(P3);
		GPIO_PORTE_DATA_R&=~(P1);
		GPIO_PORTD_DATA_R|=(P1)|(P2);
		GPIO_PORTE_DATA_R|=(P2);
		delay_Microsecond(70000);
		}
		
		//--------6
		else if(num1==6)
		{
		GPIO_PORTD_DATA_R|=(P2)|(P1);
		GPIO_PORTE_DATA_R|=(P1)|(P2);
		GPIO_PORTD_DATA_R&=~(P3);
		delay_Microsecond(700000);
		}
		
		//--------7
		else if(num1==7)
		{
			GPIO_PORTF_DATA_R&=~(P3);
		GPIO_PORTD_DATA_R|=(P2)|(P3);
		GPIO_PORTE_DATA_R&=~(P1)&~(P2);
		GPIO_PORTD_DATA_R&=~(P1);
		delay_Microsecond(70000);
		}
		
		//--------8
		else if(num1==8)
		{
		GPIO_PORTD_DATA_R|=(P2)|(P3)|(P1);//8
		GPIO_PORTE_DATA_R|=(P1)|(P2);
		delay_Microsecond(70000);
		}
		//--------9
		else if(num1==9)
		{
		GPIO_PORTD_DATA_R|=(P2)|(P3)|(P1);
		GPIO_PORTE_DATA_R&=~(P1)&~(P2);
		delay_Microsecond(70000);
		}
		//--------0
		else
		{
			GPIO_PORTF_DATA_R&=~(P3);
			GPIO_PORTD_DATA_R|=(P1)|(P2)|(P3);
			GPIO_PORTE_DATA_R|=(P2)|(P1);//0
			delay_Microsecond(70000);
		}
	}
