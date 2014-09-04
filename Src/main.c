#define SET_CONFIGURATION_BIT_ONCE
#include <p18cxxx.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "HardwareProfile.h"
#include "LCDBlocking.h"
#include "UART.h"
#include "Delay.h"


#if defined(__18CXX)
	#pragma interruptlow LowISR
	void LowISR(void)
	{
	    if (INTCONbits.TMR0IF && INTCONbits.TMR0IE)		// TMR0 Interrupt
	 	{
	 		INTCONbits.TMR0IF = 0;						// clear flag
	 		TMR0H = 0xFC;								//0x30d = 781 = 1ms   0xffff-0x30d = 0xFCF2
			TMR0L = 0xf2;
			updateMiliTick();
		}
	}
	
	#pragma interruptlow HighISR
	void HighISR(void)
	{
		if (INTCONbits.TMR0IF && INTCONbits.TMR0IE)		// TMR0 Interrupt
	 	{
	 		INTCONbits.TMR0IF = 0;						// clear flag
	 		TMR0H = 0xE7;								//0x30d = 781 = 1ms   0xffff-0x30d = 0xFCF2
			TMR0L = 0x96;
			updateMiliTick();
		}
	}
	#pragma code lowVector=0x18
	void LowVector(void){_asm goto LowISR _endasm}
	#pragma code highVector=0x8
	void HighVector(void){_asm goto HighISR _endasm}
	#pragma code // Return to default code section


void initBoard()
{

	T0CONbits.T0PS = 4;  	//1:32 25Mhz/32 = ~ 1Mhz   clocks in second 781250
	T0CONbits.PSA = 1;   	//timer0 prescaler assigned
	T0CONbits.T0SE = 0;	 	//increment low to high;
	T0CONbits.T0CS = 0;	//internal clock
	T0CONbits.T0SE = 1;
	T0CONbits.T08BIT = 0;	//16 bit timer
	T0CONbits.TMR0ON = 1;
	TMR0H = 0xE7;			//0x30d = 781 = 1ms   0xffff-0x30d = 0xFCF2    59286
	TMR0L = 0x96;
	INTCONbits.TMR0IF = 0;
	INTCONbits.TMR0IE = 1;
	INTCONbits.GIE = 1;
	//INTCONbits.PEIE	= 1;			//Interrupts// Peripheral Interrupts Enable (RCON<6>)

	LED0_TRIS = 0;
	LED0_IO = 0; 
	LED1_TRIS = 0;
	LED1_IO = 0;
	BUTTON0_TRIS = 1;
	BUTTON1_TRIS = 1;
	LCD_BL_TRIS = 0;
	LCD_BL_IO = 0;

	T3CONbits.T3CCP1 = 0; T3CONbits.T3CCP1 = 0;   	//register named T3CCP sets TMR2 as source of all pwm
	PR2 = 255; 										//tmr2 period
	TMR2 = 0;
	T2CONbits.T2CKPS = 3; 							//prescale
	T2CONbits.TOUTPS = 0; 							//postscale
	T2CONbits.TMR2ON = 1;
	
	
	CCP4CONbits.DC4B = 0;							//duty cycle lsb  1:0
	CCPR4L = 0;										//duty cycle bits 9:2
	R_MOTOR_PWM_TRIS = 0;
	CCP4CONbits.CCP4M = 0xc; 						//pwm mode
					
	R_MOTOR_PHASE_TRIS = 0;		
	R_MOTOR_PHASE = 0;			
	R_MOTOR_BREAK_TRIS = 0;		
	R_MOTOR_BREAK = 0;			
	
	
	CCP3CONbits.P3M = 0;							//eccp3 single output
	CCP3CONbits.DC3B = 0;							//duty cycle lsb  1:0
	CCPR3L = 0;										//duty cycle bits 9:2	 
	L_MOTOR_PWM_TRIS = 0;
	CCP3CONbits.CCP3M = 0xc;						//pwm mode

	L_MOTOR_PHASE_TRIS = 0;		
	L_MOTOR_PHASE = 0;			
	L_MOTOR_BREAK_TRIS = 0;		
	L_MOTOR_BREAK = 0;			

	MOTOR_CARD_GREEN_LED_TRIS = 0;
	MOTOR_CARD_GREEN_LED = 0;	
	MOTOR_CARD_RELAY_TRIS = 0;	
	MOTOR_CARD_RELAY = 0;

	L_MOTOR_FB1_TRIS = 1;					
	R_MOTOR_FB1_TRIS = 1;						
	R_BACK_BUMPER_TRIS = 1;	
	FRONT_BUMPER_TRIS = 1;						
	L_BACK_BUMPER_TRIS = 1;								
										
	L_WHITE_LINE_SENSE_TRIS = 1;
	R_WHITE_LINE_SENSE_TRIS = 1;
	LCDInit();
}

void main (void)
{
    initBoard();
	memcpypgm2ram((void*)GetLcdBuffer(), "I am Alive",10);
	LCDUpdate();
	
	while (1)
	{

		StateMachine();
		sprintf(GetLcdBuffer(),"%d %d %d %d %d %d %d ",L_MOTOR_FB1,L_WHITE_LINE_SENSE,R_BACK_BUMPER,FRONT_BUMPER,L_BACK_BUMPER,R_WHITE_LINE_SENSE,R_MOTOR_FB1);
		LCDUpdate();










#if 0
		if( !BUTTON0_IO ) 
		{
			LED0_IO =1;
			CCPR3L += 1;
			CCPR4L += 1;
			sprintf(GetLcdBuffer(),"%d %d %d %d %d %d %d ",L_MOTOR_FB1,L_WHITE_LINE_SENSE,BUMPER1,BUMPER2,BUMPER3,R_WHITE_LINE_SENSE,R_MOTOR_FB1);
			sprintf(GetLcdBuffer()+16,"val: %d",CCPR3L);
			LCDUpdate();
			MOTOR_CARD_RELAY = 1;
			//L_MOTOR_BREAK = 1;
			R_MOTOR_BREAK = 1;
			DelayMs(100);	
		}
		else
		{
			LED0_IO = 0;
			sprintf(GetLcdBuffer(),"%d %d %d %d %d %d %d ",L_MOTOR_FB1,L_WHITE_LINE_SENSE,BUMPER1,BUMPER2,BUMPER3,R_WHITE_LINE_SENSE,R_MOTOR_FB1);
			LCDUpdate();
			
		}
		if( !BUTTON1_IO )
		{
			MOTOR_CARD_RELAY = 0;
			L_MOTOR_BREAK = 0;
			R_MOTOR_BREAK = 0;
			CCPR3L = 0;
			CCPR4L = 0;
		}
#endif
	}

}
