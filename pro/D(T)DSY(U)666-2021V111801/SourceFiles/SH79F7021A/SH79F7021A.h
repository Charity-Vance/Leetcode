/*--------------------------------------------------------------------------
REG79F7011.H

Header file for generic SH79xx series microcontroller.
Copyright (c) 1996-2009 Sionwealth Electronic and Sinowealth Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __SH79F7011_H__
#define __SH79F7011_H__

/* ------------------- BYTE Register-------------------- */
/* CPU */
sfr PSW = 0xD0;            
sfr ACC = 0xE0;
sfr B = 0xF0;
sfr AUXC = 0xF1;
sfr SP = 0x81;
sfr DPL = 0x82;
sfr DPH = 0x83;
sfr DPL1 = 0x84;
sfr DPH1 = 0x85;
sfr INSCON = 0x86;
sfr XPAGE = 0xF7;

/* POWER Control  */
sfr PCON = 0x87;
sfr SUSLO = 0x8E;
sfr PASLO = 0xE7;
sfr PWRCON1 = 0xB3;
sfr PWRCON2 = 0xB4;
sfr LDOCON = 0xB5;

/* FLASH */
sfr IB_DATA = 0xEF;
sfr IB_OFFSET = 0xEE;
sfr IB_CON1 = 0xF2;
sfr IB_CON2 = 0xF3;
sfr IB_CON3 = 0xF4;
sfr IB_CON4 = 0xF5;
sfr IB_CON5 = 0xF6;
sfr PBANK = 0xB6;
sfr PBANKLO = 0xB7;
sfr FLASHCON = 0xA7;

/* WDT */
sfr RSTSTAT = 0xB1;

/* CLOCK */
sfr CLKCON = 0xB2;
sfr OSCLO = 0xFE;

/* INTERRUPT */
sfr IEN0 = 0xA8;
sfr IEN1 = 0xA9;
sfr IENX = 0xAA;
sfr EXCON1 = 0xAB;
sfr EXCON2 = 0xAC; 
sfr EXF0 = 0xE8;
sfr IPL0 = 0xB8;
sfr IPH0 = 0xBA;
sfr IPL1 = 0xB9;
sfr IPH1 = 0xBB;


/* PORT */
sfr P0 = 0x80;
sfr P1 = 0x90;
sfr P2 = 0xA0;
sfr P3 = 0xB0;
sfr P4 = 0xC0;
sfr P5 = 0xE9;
sfr P6 = 0xEA;
sfr P7 = 0xEB;
sfr P8 = 0xEC;
sfr P9 = 0xED;


/* TIMER */
sfr TCON = 0x88;
sfr TMOD = 0x89;
sfr TL0 = 0x8A;
sfr TH0 = 0x8C;
sfr TL1 = 0x8B;
sfr TH1 = 0x8D;
sfr T2CON = 0xC8;
sfr T2MOD = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2 = 0xCC;
sfr TH2 = 0xCD;
sfr TCON1 = 0x8F;

/* EUART0 */
sfr SCON = 0x98;
sfr SBUF = 0x99;
sfr SADDR = 0x9A;
sfr SADEN = 0x9B;
sfr SBRTH = 0x9C;
sfr SBRTL = 0x9D;
sfr SFINE = 0x9E;

/* EUART1 */
sfr SCON1 = 0xD8;
sfr SBUF1 = 0xD9;
sfr SADDR1 = 0xDA;
sfr SADEN1 = 0xDB;
sfr SBRT1H = 0xDC;
sfr SBRT1L = 0xDD;

/* EUART2 */
sfr SCON2 = 0xF8;
sfr SBUF2 = 0xF9;
sfr SADDR2 = 0xFA;
sfr SADEN2 = 0xFB;
sfr SBRT2H = 0xFC;
sfr SBRT2L = 0xFD;
sfr SFINE2 = 0xDE;	



/* IR */
sfr IRCON1 = 0xAD;
sfr IRDAT = 0xAE;
sfr IRCON2 = 0xAF;


/* ADC */
sfr ADCON = 0xC1;
sfr ADT = 0xC2;
sfr ADCH = 0xC3;
sfr ADCDL = 0xC4;
sfr ADCDH = 0xC5;

/*SPI*/
sfr SPCON = 0xA1;
sfr SPSTA = 0xA2;
sfr SPDAT = 0xA3;

/*PWM*/
sfr PWMCON = 0x9F;

/*TOUCH KEY*/
sfr TKCON = 0xA4;
sfr TKF0 = 0xA6;
sfr TK0L = 0xE1;
sfr TK0H = 0xE2;
sfr TK1L = 0xE3;
sfr TK1H = 0xE4;
sfr TK2L = 0xE5;
sfr TK2H = 0xE6;
sfr TK0BASEL = 0xD3;
sfr TK0BASEH = 0xD4;
sfr TK1BASEL = 0xD5;
sfr TK1BASEH = 0xD6;
sfr TK2BASEL = 0xD7;
sfr TK2BASEH = 0xDF;
sfr TK0DIFL = 0xCF;
sfr TK0DIFH = 0xBC;
sfr TK1DIFL = 0xBD;
sfr TK1DIFH = 0xBE;
sfr TK2DIFL = 0xBF;
sfr TK2DIFH = 0xA5;

/*EMU*/
sfr EADR = 0x91;
sfr EDTAH = 0x92;
sfr EDTAM = 0x93;
sfr EDTAL = 0x94;
sfr EMUSR = 0x95;
sfr EMUIE = 0x96;
sfr EMUIF = 0x97;

/*LCD*/
sfr LCDCON1 = 0xD1;
sfr LCDCON2 = 0xD2;

/*LPD*/
sfr LPDCON1 = 0xC6;
sfr LPDCON2 = 0xC7;


/* PORT */
extern volatile unsigned char xdata P0CR;                       
extern volatile unsigned char xdata P1CR;                       
extern volatile unsigned char xdata P2CR;                       
extern volatile unsigned char xdata P3CR;                       
extern volatile unsigned char xdata P4CR;                       
extern volatile unsigned char xdata P5CR;                       
extern volatile unsigned char xdata P6CR;                       
extern volatile unsigned char xdata P7CR;                       
extern volatile unsigned char xdata P8CR;                       
extern volatile unsigned char xdata P9CR;                       
extern volatile unsigned char xdata P0PCR;                      
extern volatile unsigned char xdata P1PCR;                      
extern volatile unsigned char xdata P2PCR;                       
extern volatile unsigned char xdata P3PCR;                      
extern volatile unsigned char xdata P4PCR;                       
extern volatile unsigned char xdata P5PCR;                       
extern volatile unsigned char xdata P6PCR;                       
extern volatile unsigned char xdata P7PCR;                       
extern volatile unsigned char xdata P8PCR;                       
extern volatile unsigned char xdata P9PCR;                       
extern volatile unsigned char xdata P0OS;                        
extern volatile unsigned char xdata P2OS;                        
extern volatile unsigned char xdata P3OS;                        
extern volatile unsigned char xdata P0DRVH;                      
extern volatile unsigned char xdata P1DRVL;                      
extern volatile unsigned char xdata P2DRVH;                     
extern volatile unsigned char xdata P0PHM;                       
extern volatile unsigned char xdata P2PHM;                       
extern volatile unsigned char xdata P0INM;
extern volatile unsigned char xdata P2INM;

/*EUART3*/
extern volatile unsigned char xdata SCON3;                       
extern volatile unsigned char xdata SBUF3;                       
extern volatile unsigned char xdata SADDR3;                      
extern volatile unsigned char xdata SADEN3;                      
extern volatile unsigned char xdata SBRT3H;                      
extern volatile unsigned char xdata SBRT3L;                      

/* LCD */
extern volatile unsigned char xdata P4SS;                        
extern volatile unsigned char xdata P5SS;                        
extern volatile unsigned char xdata P6SS;                        
extern volatile unsigned char xdata P7SS;                       
extern volatile unsigned char xdata P8SS;                        
extern volatile unsigned char xdata P9SS;                        

/*TOUCH KEY*/
extern volatile unsigned char xdata TKST;                       
extern volatile unsigned char xdata TKRANDOM;                    
extern volatile unsigned char xdata TKDIV01;                    
extern volatile unsigned char xdata TKDIV02;                     
extern volatile unsigned char xdata TKDIV03;                     
extern volatile unsigned char xdata TKDIV04;                     
extern volatile unsigned char xdata TKCH;                        
extern volatile unsigned char xdata TKVREF;                      
extern volatile unsigned char xdata TK0THRL;                    
extern volatile unsigned char xdata TK0THRH;                    
extern volatile unsigned char xdata TK1THRL;                     
extern volatile unsigned char xdata TK1THRH;                     
extern volatile unsigned char xdata TK2THRL;                    
extern volatile unsigned char xdata TK2THRH;                     

/* RTC */ 
extern volatile unsigned char xdata SBSC;                        
extern volatile unsigned char xdata SEC;                         
extern volatile unsigned char xdata MIN;                         
extern volatile unsigned char xdata HR;                          
extern volatile unsigned char xdata DAY;                         
extern volatile unsigned char xdata MTH;                         
extern volatile unsigned char xdata YR;                          
extern volatile unsigned char xdata DOW;                         
extern volatile unsigned char xdata RTCDATH;                     
extern volatile unsigned char xdata RTCDATL;                     
extern volatile unsigned char xdata RTCALM;                      
extern volatile unsigned char xdata A0SEC;                      
extern volatile unsigned char xdata A0MIN;                      
extern volatile unsigned char xdata A0HR;                       
extern volatile unsigned char xdata A0DAY;                       
extern volatile unsigned char xdata A0DOW;                       
extern volatile unsigned char xdata A1SEC;                       
extern volatile unsigned char xdata A1MIN;                       
extern volatile unsigned char xdata A1HR;                        
extern volatile unsigned char xdata RTCCON;                      
extern volatile unsigned char xdata RTCWR;                       
extern volatile unsigned char xdata RTCPSW;                      
extern volatile unsigned char xdata RTCIE;                       
extern volatile unsigned char xdata RTCIF;                       
extern volatile unsigned char xdata RTCECL;                      
extern volatile unsigned char xdata RTCECH;                      
extern volatile unsigned char xdata RTCTMR;                      

/*7816*/
extern volatile unsigned char xdata S7816EN;                     
extern volatile unsigned char xdata S7816CON;                    
extern volatile unsigned char xdata EGTSET;                      
extern volatile unsigned char xdata S7816WTH;                    
extern volatile unsigned char xdata S7816WTL;                    
extern volatile unsigned char xdata S7816CLKDIV;                 
extern volatile unsigned char xdata S7816ETUH;                  
extern volatile unsigned char xdata S7816ETUL;                   
extern volatile unsigned char xdata RXBUF;                       
extern volatile unsigned char xdata TXBUF;                       
extern volatile unsigned char xdata S7816IE;                     
extern volatile unsigned char xdata S7816STA;                    
extern volatile unsigned char xdata S7816ERRSTA;                 
extern volatile unsigned char xdata EGTRSEND;                    


/*--------------------------  BIT Register -------------------- */
/*  PSW   */
sbit CY = 0xD7;
sbit AC = 0xD6;
sbit F0 = 0xD5;
sbit RS1 = 0xD4;
sbit RS0 = 0xD3;
sbit OV = 0xD2;
sbit F1 = 0xD1;
sbit P = 0xD0;

/*  TCON  */
sbit TF1 = 0x8F;
sbit TR1 = 0x8E;
sbit TF0 = 0x8D;
sbit TR0 = 0x8C;

/*  T2CON  */
sbit TF2 = 0xCF;
sbit EXF2 = 0xCE;
sbit EXEN2 = 0xCB;
sbit TR2 = 0xCA;
sbit C_T2 = 0xC9;
sbit CP_RL2 = 0xC8;

/*  SCON  */
sbit SM0_FE = 0x9F;
sbit SM1_RXOV = 0x9E;
sbit SM2_TXCOL = 0x9D;
sbit REN = 0x9C;
sbit TB8 = 0x9B;
sbit RB8 = 0x9A;
sbit TI = 0x99;
sbit RI = 0x98;

/*  IEN0   */
sbit EA = 0xAF;
sbit EADTP = 0xAE;
sbit ET2 = 0xAD;
sbit ES0  = 0xAC;
sbit ET1 = 0xAB;
sbit E7816 = 0xAA;
sbit ET0 = 0xA9;
sbit EX4 = 0xA8;

/*  IPL0   */ 
sbit PADCL = 0xBE;
sbit PT2L = 0xBD;
sbit PS0L = 0xBC;
sbit PT1L = 0xBB;
sbit P7816L = 0xBA;
sbit PT0L = 0xB9;
sbit PX4L = 0xB8;

/*  SCON1   */
sbit SM10_FE1 = 0xDF;
sbit SM11_RXOV1 = 0xDE;
sbit SM12_TXCOL1 = 0xDD;
sbit REN1  = 0xDC;
sbit TB81 = 0xDB;
sbit RB81 = 0xDA;
sbit TI1 = 0xD9;
sbit RI1 = 0xD8;


/* P0 */
sbit P0_0 = P0^0;
sbit P0_1 = P0^1;
sbit P0_2 = P0^2;
sbit P0_3 = P0^3;
sbit P0_4 = P0^4;
sbit P0_5 = P0^5;
sbit P0_6 = P0^6;
sbit P0_7 = P0^7;

/* P1 */
sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;

/* P2 */
sbit P2_0 = P2^0;
sbit P2_1 = P2^1;
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P2_5 = P2^5;
sbit P2_6 = P2^6;
sbit P2_7 = P2^7;

/* P3 */
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;

/* P4 */
sbit P4_0 = P4^0;
sbit P4_1 = P4^1;
sbit P4_2 = P4^2;
sbit P4_3 = P4^3;
sbit P4_4 = P4^4;
sbit P4_5 = P4^5;
sbit P4_6 = P4^6;
sbit P4_7 = P4^7;



#endif
