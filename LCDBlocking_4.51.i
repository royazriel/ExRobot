#line 1 "Src\LCDBlocking_4.51.c"
#line 1 "Src\LCDBlocking_4.51.c"

#line 54 "Src\LCDBlocking_4.51.c"
 
#line 56 "Src\LCDBlocking_4.51.c"

#line 1 "C:/Users/roy/Desktop/ExRobot/Inc/LCDBlocking.h"

#line 50 "C:/Users/roy/Desktop/ExRobot/Inc/LCDBlocking.h"
 

#line 53 "C:/Users/roy/Desktop/ExRobot/Inc/LCDBlocking.h"




typedef unsigned char BYTE;
extern BYTE LCDText[16*2+1];
void LCDInit(void);
void LCDUpdate(void);
void LCDErase(void);

#line 64 "C:/Users/roy/Desktop/ExRobot/Inc/LCDBlocking.h"

#line 57 "Src\LCDBlocking_4.51.c"


#line 60 "Src\LCDBlocking_4.51.c"
#line 61 "Src\LCDBlocking_4.51.c"



BYTE LCDText[16*2+1];


#line 81 "Src\LCDBlocking_4.51.c"
 
static void LCDWrite(BYTE RS, BYTE Data)
{
#line 85 "Src\LCDBlocking_4.51.c"
#line 87 "Src\LCDBlocking_4.51.c"
		LCD_DATA0_TRIS = 0;
		LCD_DATA1_TRIS = 0;
		LCD_DATA2_TRIS = 0;
		LCD_DATA3_TRIS = 0;
#line 92 "Src\LCDBlocking_4.51.c"
#line 97 "Src\LCDBlocking_4.51.c"
#line 98 "Src\LCDBlocking_4.51.c"
	LCD_RS_TRIS = 0;
	LCD_RD_WR_TRIS = 0;
	LCD_RD_WR_IO = 0;
	LCD_RS_IO = RS;

#line 104 "Src\LCDBlocking_4.51.c"
#line 105 "Src\LCDBlocking_4.51.c"
#line 107 "Src\LCDBlocking_4.51.c"
		LCD_DATA0_IO = Data & 0x10;
		LCD_DATA1_IO = Data & 0x20;
		LCD_DATA2_IO = Data & 0x40;
		LCD_DATA3_IO = Data & 0x80;
#line 112 "Src\LCDBlocking_4.51.c"
	Nop();					
	Nop();
	LCD_E_IO = 1;
	Nop();					
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	LCD_E_IO = 0;
#line 126 "Src\LCDBlocking_4.51.c"

#line 128 "Src\LCDBlocking_4.51.c"
#line 130 "Src\LCDBlocking_4.51.c"
		LCD_DATA0_IO = ((Data & 0x01) == 0x01);
		LCD_DATA1_IO = ((Data & 0x02) == 0x02);
		LCD_DATA2_IO = ((Data & 0x04) == 0x04);
		LCD_DATA3_IO = ((Data & 0x08) == 0x08);
#line 135 "Src\LCDBlocking_4.51.c"
#line 140 "Src\LCDBlocking_4.51.c"
#line 141 "Src\LCDBlocking_4.51.c"
	Nop();					
	Nop();
	LCD_E_IO = 1;
	Nop();					
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	Nop();
	LCD_E_IO = 0;






















}



#line 194 "Src\LCDBlocking_4.51.c"
 
void LCDInit(void)
{
	BYTE i;

	memset(LCDText, ' ', sizeof(LCDText)-1);
	LCDText[sizeof(LCDText)-1] = 0;

	
	LCD_E_IO = 0;
	LCD_RD_WR_IO = 0;


#line 208 "Src\LCDBlocking_4.51.c"
#line 210 "Src\LCDBlocking_4.51.c"
		LCD_DATA0_TRIS = 0;
		LCD_DATA1_TRIS = 0;
		LCD_DATA2_TRIS = 0;
		LCD_DATA3_TRIS = 0;
#line 215 "Src\LCDBlocking_4.51.c"
#line 220 "Src\LCDBlocking_4.51.c"
#line 221 "Src\LCDBlocking_4.51.c"
	LCD_RD_WR_TRIS = 0;
	LCD_RS_TRIS = 0;
	LCD_E_TRIS = 0;


	
	DelayMs(40);

	
	
	
	
	
	
	LCD_RS_IO = 0;
#line 237 "Src\LCDBlocking_4.51.c"
#line 239 "Src\LCDBlocking_4.51.c"
		LCD_DATA0_IO = 1;
		LCD_DATA1_IO = 1;
		LCD_DATA2_IO = 0;
		LCD_DATA3_IO = 0;
#line 244 "Src\LCDBlocking_4.51.c"
#line 249 "Src\LCDBlocking_4.51.c"
#line 250 "Src\LCDBlocking_4.51.c"
	Nop();					
	Nop();
	for(i = 0; i < 3u; i++)
	{
		LCD_E_IO = 1;
		Delay10us(1);			
		LCD_E_IO = 0;
		Delay10us(5);
	}
	
#line 261 "Src\LCDBlocking_4.51.c"
#line 262 "Src\LCDBlocking_4.51.c"
		
#line 264 "Src\LCDBlocking_4.51.c"
#line 266 "Src\LCDBlocking_4.51.c"
			LCD_DATA0_IO = 0;
			LCD_DATA1_IO = 1;
			LCD_DATA2_IO = 0;
			LCD_DATA3_IO = 0;
#line 271 "Src\LCDBlocking_4.51.c"
		Nop();					
		Nop();
		LCD_E_IO = 1;
		Delay10us(1);			
		LCD_E_IO = 0;
#line 277 "Src\LCDBlocking_4.51.c"
#line 280 "Src\LCDBlocking_4.51.c"
#line 281 "Src\LCDBlocking_4.51.c"
#line 284 "Src\LCDBlocking_4.51.c"
	Delay10us(5);
	
	
	LCDWrite(0, 0x06);	
	Delay10us(5);

	
	LCDWrite(0, 0x0C);		
	Delay10us(5);

	
	LCDWrite(0, 0x01);	
	DelayMs(2);
	
}



#line 318 "Src\LCDBlocking_4.51.c"
 
void LCDUpdate(void)
{
	BYTE i, j;

	
	LCDWrite(0, 0x02);
	DelayMs(2);

	
	for(i = 0; i < 16u; i++)
	{
		
		
		if(LCDText[i] == 0u)
		{
			for(j=i; j < 16u; j++)
			{
				LCDText[j] = ' ';
			}
		}
		LCDWrite(1, LCDText[i]);
		Delay10us(5);
	}
	
	
	LCDWrite(0, 0xC0);
	Delay10us(5);

	
	for(i = 16; i < 32u; i++)
	{
		
		
		if(LCDText[i] == 0u)
		{
			for(j=i; j < 32u; j++)
			{
				LCDText[j] = ' ';
			}
		}
		LCDWrite(1, LCDText[i]);
		Delay10us(5);
	}
}


#line 378 "Src\LCDBlocking_4.51.c"
 
void LCDErase(void)
{
	
	LCDWrite(0, 0x01);
	DelayMs(2);

	
	memset(LCDText, ' ', 32);
}

#line 390 "Src\LCDBlocking_4.51.c"
