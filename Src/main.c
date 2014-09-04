#define SET_CONFIGURATION_BIT_ONCE
#include <p18cxxx.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "HardwareProfile.h"
#include "LCDBlocking.h"
#include "UART.h"
#include "Delay.h"
void initBoard()
{
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
	BUMPER1_TRIS = 1;							
	BUMPER2_TRIS = 1;								
	BUMPER3_TRIS = 1;									
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
	}
}
