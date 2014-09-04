/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.00 or higher
 *					Microchip C30 v3.01 or higher
 *					Microchip C18 v3.13 or higher
 *					HI-TECH PICC-18 STD 9.50PL3 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2008 Microchip Technology Inc.  All rights 
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
 * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product ("Device") which is 
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and 
 *      ENC28J60.h ported to a non-Microchip device used in 
 *      conjunction with a Microchip ethernet controller for the 
 *      sole purpose of interfacing with the ethernet controller. 
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL 
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS 
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT 
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		10/03/06	Original, copied from Compiler.h
 ********************************************************************/
#include "Compiler.h"
#include "GenericTypeDefs.h"

#ifndef __HARDWARE_PROFILE_H
	#define __HARDWARE_PROFILE_H

// Choose which hardware profile to compile for here.  See 
// the hardware profiles below for meaning of various options.  
//#define PICDEMNET2

extern char dummy;
	
#define OLIMEX_MAXI
#define OLIMEX_HW
	#if defined(SET_CONFIGURATION_BIT_ONCE)
		#if defined(__18CXX)
			#if defined(__EXTENDED18__)
				#pragma config XINST=ON
			#elif !defined(HI_TECH_C)
				#pragma config XINST=OFF
			#endif
			#if defined(__18F97J60) || defined(__18F96J65) || defined(__18F96J60) || defined(__18F87J60) || defined(__18F86J65) || defined(__18F86J60) || defined(__18F67J60) || defined(__18F66J65) || defined(__18F66J60) 
			// PICDEM.net 2 or any other PIC18F97J60 family device
			#pragma config WDT=OFF, FOSC2=ON, FOSC=HSPLL, ETHLED=ON
			#elif defined(_18F97J60) || defined(_18F96J65) || defined(_18F96J60) || defined(_18F87J60) || defined(_18F86J65) || defined(_18F86J60) || defined(_18F67J60) || defined(_18F66J65) || defined(_18F66J60) 
			// PICDEM.net 2 board with HI-TECH PICC-18 compiler
			__CONFIG(1, WDTDIS & XINSTDIS);
			__CONFIG(2, HSPLL);
			__CONFIG(3, ETHLEDEN);
			#endif
		#endif
	#endif

// If no hardware profiles are defined, assume that we are using 
// a Microchip demo board and try to auto-select the correct profile
// based on processor selected in MPLAB

	#if defined(__18F97J60) || defined(_18F97J60)
		//#define PICDEMNET2
	#endif

// Clock frequency value.
// This value is used to calculate Tick Counter value
	#if defined(__18CXX)
		// All PIC18 processors
		#if defined(PICDEMNET2) || defined(INTERNET_RADIO) || defined(OLIMEX_MAXI)
			#define GetSystemClock()		(25000000ul)      // Hz
			#define GetInstructionClock()	(GetSystemClock()/4)
			#define GetPeripheralClock()	GetInstructionClock()
		#endif
	#endif


	#if defined(OLIMEX_MAXI) && !defined(HI_TECH_C)
// PIC18F97J60 based, atmel dataflash, 2 buttons, 3 LED's+2 relays, UART, LCD

	// We have an early revision sillicon for now
		#define	ETH_18Fx7J60_ERRATA
		
		// I/O pins
		#define LED0_TRIS			(TRISJbits.TRISJ0)
		#define LED0_IO				(PORTJbits.RJ0)
		#define LED1_TRIS			(TRISJbits.TRISJ1)
		#define LED1_IO				(PORTJbits.RJ1)
		#define LED2_TRIS			(TRISJbits.TRISJ2)
		#define LED2_IO				(PORTJbits.RJ2)
		#define	LCD_BL_TRIS			(TRISGbits.TRISG5) // AKA LIGHT_LCD
		#define LCD_BL_IO				(PORTGbits.RG5)
		#define	LED5_TRIS			
		#define	LED5_IO				
	
		
		#define CH_PUMP_TRIS						(TRISGbits.TRISG7)
		#define CH_PUMP								(PORTGbits.RG7) // AKA REL1
		#define PH_PUMP_TRIS						(TRISGbits.TRISG6)
		#define PH_PUMP								(PORTGbits.RG6) // AKA REL1
		
		#define ON									1
		#define OFF									0

//input from robot
		#define L_MOTOR_FB1_TRIS					(TRISJbits.TRISJ7)
		#define L_MOTOR_FB1							(PORTJbits.RJ7)  // EXT-3
		#define R_MOTOR_FB1_TRIS					(TRISJbits.TRISJ6)
		#define R_MOTOR_FB1							(PORTJbits.RJ6)  // EXT-4

		#define BUMPER1_TRIS						(TRISJbits.TRISJ5)
		#define BUMPER1								(PORTJbits.RJ5)  // EXT-5
		#define BUMPER2_TRIS						(TRISJbits.TRISJ4)
		#define BUMPER2								(PORTJbits.RJ4)	 // EXT-6
		#define BUMPER3_TRIS						(TRISJbits.TRISJ3)
		#define BUMPER3								(PORTJbits.RJ3)	 // EXT-7

		//#define R_MOTOR_FB2_TRIS					(TRISDbits.TRISD1)
		//#define R_MOTOR_FB2						 	(PORTDbits.RD1)	 // EXT-22
	
	
		#define L_WHITE_LINE_SENSE_TRIS				(TRISHbits.TRISH3)
		#define L_WHITE_LINE_SENSE					(PORTHbits.RH3)	 // EXT-11
		#define R_WHITE_LINE_SENSE_TRIS				(TRISDbits.TRISD0)
		#define R_WHITE_LINE_SENSE				 	(PORTDbits.RD0)	 // EXT-23

//outputs to robot
		#define R_MOTOR_PWM_TRIS					(TRISGbits.TRISG3)
		#define R_MOTOR_PWM							(PORTGbits.RG3)	 // EXT-12
		#define R_MOTOR_PHASE_TRIS					(TRISGbits.TRISG2)
		#define R_MOTOR_PHASE						(PORTGbits.RG2)	 // EXT-13
		#define R_MOTOR_BREAK_TRIS					(TRISGbits.TRISG1)
		#define R_MOTOR_BREAK					 	(PORTGbits.RG1)	 // EXT-14

		#define L_MOTOR_PWM_TRIS					(TRISGbits.TRISG0)
		#define L_MOTOR_PWM							(PORTGbits.RG0)	 // EXT-15
		#define L_MOTOR_PHASE_TRIS					(TRISFbits.TRISF7)
		#define L_MOTOR_PHASE						(PORTFbits.RF7)	 // EXT-16
		#define L_MOTOR_BREAK_TRIS					(TRISDbits.TRISD4)
		#define L_MOTOR_BREAK					 	(PORTDbits.RD4)	 // EXT-19

		#define MOTOR_CARD_GREEN_LED_TRIS			(TRISDbits.TRISD3)
		#define MOTOR_CARD_GREEN_LED			 	(PORTDbits.RD3)	 // EXT-20
		#define MOTOR_CARD_RELAY_TRIS				(TRISDbits.TRISD2)
		#define MOTOR_CARD_RELAY				 	(PORTDbits.RD2)	 // EXT-21


		
		#define LED_GET()			(LATJ)
		#define LED_PUT(a)			(LATJ = (a))
	
		#define BUTTON0_TRIS		(TRISBbits.TRISB3)
		#define	BUTTON0_IO			(PORTBbits.RB3)
		#define BUTTON1_TRIS		(TRISBbits.TRISB1)
		#define	BUTTON1_IO			(PORTBbits.RB1)
		
		#define MAIN_VALVE_TRIS		(TRISCbits.TRISC2)	// AKA IN1

		
		// spi dataflash
		#define EEPROM_CS_TRIS		(TRISDbits.TRISD7)
		#define EEPROM_CS_IO		(LATDbits.LATD7)
		#define EEPROM_SCK_TRIS		(TRISCbits.TRISC3)
		#define EEPROM_SDI_TRIS		(TRISCbits.TRISC4)
		#define EEPROM_SDO_TRIS		(TRISCbits.TRISC5)
		#define EEPROM_SPI_IF		(PIR1bits.SSPIF)
		#define EEPROM_SSPBUF		(SSPBUF)
		#define EEPROM_SPICON1		(SSP1CON1)
		#define EEPROM_SPICON1bits	(SSP1CON1bits)
		#define EEPROM_SPICON2		(SSP1CON2)
		#define EEPROM_SPISTAT		(SSP1STAT)
		#define EEPROM_SPISTATbits	(SSP1STATbits)
	
	
		// LCD module
		#define LCD_DATA_TRIS		(*((volatile BYTE*)&TRISE))
		#define LCD_DATA_IO			(*((volatile BYTE*)&LATE))
		#define LCD_RD_WR_TRIS		(TRISHbits.TRISH1)
		#define LCD_RD_WR_IO		(LATHbits.LATH1)
		#define LCD_RS_TRIS			(TRISHbits.TRISH2)
		#define LCD_RS_IO			(LATHbits.LATH2)
		#define LCD_E_TRIS			(TRISHbits.TRISH0)
		#define LCD_E_IO			(LATHbits.LATH0)
#else
	#error "Hardware profile not defined.  See available profiles in HardwareProfile.h.  Add the appropriate macro definition to your application configuration file ('TCPIPConfig.h', etc.)"
#endif


	#if defined(__18CXX)	// PIC18
		// UART mapping functions for consistent API names across 8-bit and 16 or 
		// 32 bit compilers.  For simplicity, everything will use "UART" instead 
		// of USART/EUSART/etc.
		#define BusyUART()				BusyUSART()
		#define CloseUART()				CloseUSART()
		#define ConfigIntUART(a)		ConfigIntUSART(a)
		#define DataRdyUART()			DataRdyUSART()
		#define OpenUART(a,b,c)			OpenUSART(a,b,c)
		#define ReadUART()				ReadUSART()
		#define WriteUART(a)			WriteUSART(a)
		#define getsUART(a,b,c)			getsUSART(b,a)
		#define putsUART(a)				putsUSART(a)
		#define getcUART()				ReadUSART()
		#define putcUART(a)				WriteUSART(a)
		#define putrsUART(a)			putrsUSART((far rom char*)a)
	#endif
#endif
