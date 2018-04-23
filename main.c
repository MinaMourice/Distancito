// main.c
// Runs on LM4F120 or TM4C123
// C2_Toggle_PF1, toggles PF1 (red LED) at 5 Hz
// Daniel Valvano, Jonathan Valvano, and Ramesh Yerraballi
// January 18, 2016

// LaunchPad built-in hardware
// SW1 left switch is negative logic PF4 on the Launchpad
// SW2 right switch is negative logic PF0 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad

#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "foo.h"
// Ultrasonic
#define ECHO (1<<6) //PB6(input)
#define TRIGGER (1<<4) //PA4(OUTPUT)

//first segment
#define PB0 (1<<0) // a
#define PB1 (1<<1) // b
#define PB2 (1<<2) // c
#define PB3 (1<<3) // d
#define PB4 (1<<4) // e
#define PB5 (1<<5) // f
#define PB7 (1<<7) // g

//second segment
#define PC4 (1<<4)
#define PC5 (1<<5)
#define PC6 (1<<6)
#define PC7 (1<<7)
#define PD6 (1<<6)
#define PD7 (1<<7)
#define PA2 (1<<2)
#define PA7 (1<<7)

//third segment
#define PD2 (1<<2)
#define PD3 (1<<3)
#define PE3 (1<<3)
#define PE2 (1<<2)
#define PE1 (1<<1)
#define PD1 (1<<1)
#define PD0 (1<<0)


#define BLUE_LED (1<<2)//PF3 onboard Blue LED 
uint32_t highEdge,lowEdge;
uint32_t cdistance; /*Distance in centimeters*/
uint32_t counter =0; 
//Global Variable

void delay_Microsecond(uint32_t time);
void Timer0_init(void);
uint32_t measureD(void);
 
const double _16MHz_1clock = 62.5e-9; /*Value of 1clock cycle in nanoseconds*/
const uint32_t MULTIPLIER  = 5882;  /*Derived from speed of sound*/
 
void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= (1<<5);     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R |= 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
 // GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}
void PortA_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= (1<<0);     // 1) activate clock for Port A
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTA_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTA_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTA_DIR_R |=(TRIGGER)|(PA2)|(PA7);          // 5) Trigger out
  GPIO_PORTA_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  //GPIO_PORTA_PUR_R = 0x11;          // enable pull-up on PF0 and PF4          
  GPIO_PORTA_DEN_R |=(ECHO)|(TRIGGER)|(PA2)|(PA7);// 7) enable digital I/O on ECHO , TRIGGER
}

void PortB_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= (1<<1);     // 1) activate clock for Port B
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTB_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTB_DIR_R |=(PB0)|(PB1)|(PB2)|(PB3)|(PB4)|(PB5)|(PB7);          // 5) Output pin
	GPIO_PORTB_DIR_R &=~ECHO;
  GPIO_PORTB_AFSEL_R |=ECHO;        // 6) disable alt funct on PF7-0
  //GPIO_PORTB_PUR_R = 0x11;          // enable pull-up on PF0 and PF4          
  GPIO_PORTB_DEN_R |=(PB0)|(PB1)|(PB2)|(PB3)|(PB4)|(PB5)|(PB7)|ECHO;// 7) enable digital I/O 
    GPIO_PORTB_PCTL_R &=~0x0F000000;
    GPIO_PORTB_PCTL_R |= 0x07000000;
}

void PortCDE(void){ volatile unsigned long delay1,delay2,delay3;
  SYSCTL_RCGC2_R |= (1<<2)|(1<<3)|(1<<4);
  delay1 = SYSCTL_RCGC2_R;
	delay2 = SYSCTL_RCGC2_R;
	delay3 = SYSCTL_RCGC2_R;
  GPIO_PORTC_DIR_R |=(PC4)|(PC5)|(PC6)|(PC7);
  GPIO_PORTD_DIR_R |=(PD0)|(PD1)|(PD2)|(PD3)|(PD6)|(PD7); 
	GPIO_PORTE_DIR_R |=(PE1)|(PE2)|(PE3);
	GPIO_PORTC_DEN_R |=(PC4)|(PC5)|(PC6)|(PC7);
  GPIO_PORTD_DEN_R |=(PD0)|(PD1)|(PD2)|(PD3)|(PD6)|(PD7); 
	GPIO_PORTE_DEN_R |=(PE1)|(PE2)|(PE3);
}
uint32_t measureD(void) { 
		GPIO_PORTA_DATA_R  &=~TRIGGER;	//set trig bit to zero
    delay_Microsecond(12);
    GPIO_PORTA_DATA_R |= TRIGGER;		//set trig bit to one
    delay_Microsecond(12);
    GPIO_PORTA_DATA_R &=~TRIGGER;		//set trig bit to zero
    /*Capture firstEgde i.e. rising edge*/
    TIMER0_ICR_R =4;								// GPTM Timer A Capture Mode Event Interrupt Clear
		// clears the CAERIS bit in the GPTMRIS register
		
		// if CAERIS bit in the GPTMRIS is set to 1 , A capture mode event has occurred for Timer A.
		// wait until 
    while((TIMER0_RIS_R & 4)==0){};	//Wait till captured
        highEdge =  TIMER0_TAR_R;		// return the count saved in Timer A Register
				//In the InputEdge Count mode, this register contains the number of edges that have occurred.
        /*Capture secondEdge i.e. falling edge */
        TIMER0_ICR_R =4; //clear timer capture flag
        while((TIMER0_RIS_R & 4)  ==0){};//Wait till captured
				lowEdge = TIMER0_TAR_R;
        cdistance = lowEdge -highEdge;
        cdistance = _16MHz_1clock *(double) MULTIPLIER *(double)cdistance*2.6;
            return cdistance;
 
}


int main(void){
	PortF_Init();
	PortA_Init();
	PortB_Init();
	PortCDE();
	Timer0_init();
  while(1)
	{
		uint32_t distance = measureD();
		if(distance>600)
		{
			first_seven_segment(0);
			second_seven_segment(0);
			third_seven_segment(0);
		}
		else
		{
			first_seven_segment((distance%11)+'0');
			second_seven_segment((distance/10)%11);
			third_seven_segment((distance/100)%11);
		}
	/*	first_seven_segment(1);
		first_seven_segment(2);first_seven_segment(3);first_seven_segment(4);first_seven_segment(5);first_seven_segment(6);first_seven_segment(7);
		first_seven_segment(8);
		first_seven_segment(9);
    if(measureD() < 15) 
		{
			GPIO_PORTF_DATA_R  |=BLUE_LED;
		}
			
		else{
			GPIO_PORTF_DATA_R  &=~BLUE_LED;
		delay_Microsecond(100);
		}*/
  }
}



void Timer0_init(void)
{
		// Input Edge-Time Mode
    
		SYSCTL_RCGCTIMER_R |=(1U<<0); // enable timer 0
    TIMER0_CTL_R &=~1;				// 1- Ensure the timer is disabled
    TIMER0_CFG_R =4;					// 2- Write the GPTM Configuration (GPTMCFG) register with a value of 0x0000.0004.
    TIMER0_TAMR_R = 0x17;			// 3- In the GPTM Timer Mode (GPTMTnMR) register, write the TnCMR field to 0x0 and the TnMR field to 0x3.
    TIMER0_CTL_R |=0x0C;			// 4- Set Event Bits
    TIMER0_CTL_R |=1;					// 5- Set the TnEN bit in the GPTM Control (GPTMCTL) register to enable the timer and start counting.
}
