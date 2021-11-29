/*--------------------------------------------------------------------------
REG79F7011E.H

Header file for generic SH79xx series microcontroller.
Copyright (c) 1996-2009 Sionwealth Electronic and Sinowealth Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/
#ifndef __SH79F7011E_H__
#define __SH79F7011E_H__

/* PORT */
volatile unsigned char xdata P0CR                        _at_ 0xFFE0;
volatile unsigned char xdata P1CR                        _at_ 0xFFE1;
volatile unsigned char xdata P2CR                        _at_ 0xFFE2;
volatile unsigned char xdata P3CR                        _at_ 0xFFE3;
volatile unsigned char xdata P4CR                        _at_ 0xFFE4;
volatile unsigned char xdata P5CR                        _at_ 0xFFE5;
volatile unsigned char xdata P6CR                        _at_ 0xFFE6;
volatile unsigned char xdata P7CR                        _at_ 0xFFE7;
volatile unsigned char xdata P8CR                        _at_ 0xFFE8;
volatile unsigned char xdata P9CR                        _at_ 0xFFE9;
volatile unsigned char xdata P0PCR                       _at_ 0xFFF0;
volatile unsigned char xdata P1PCR                       _at_ 0xFFF1;
volatile unsigned char xdata P2PCR                       _at_ 0xFFF2;
volatile unsigned char xdata P3PCR                       _at_ 0xFFF3;
volatile unsigned char xdata P4PCR                       _at_ 0xFFF4;
volatile unsigned char xdata P5PCR                       _at_ 0xFFF5;
volatile unsigned char xdata P6PCR                       _at_ 0xFFF6;
volatile unsigned char xdata P7PCR                       _at_ 0xFFF7;
volatile unsigned char xdata P8PCR                       _at_ 0xFFF8;
volatile unsigned char xdata P9PCR                       _at_ 0xFFF9;
volatile unsigned char xdata P0OS                        _at_ 0xFF88;
volatile unsigned char xdata P2OS                        _at_ 0xFF89;
volatile unsigned char xdata P3OS                        _at_ 0xFF8A;
volatile unsigned char xdata P0DRVH                      _at_ 0xFF8B;
volatile unsigned char xdata P1DRVL                      _at_ 0xFF8C;
volatile unsigned char xdata P2DRVH                      _at_ 0xFF8D;
volatile unsigned char xdata P0PHM                       _at_ 0xFF8E;
volatile unsigned char xdata P2PHM                       _at_ 0xFF8F;

volatile unsigned char xdata P0INM                       _at_ 0xFFFA;
volatile unsigned char xdata P2INM                       _at_ 0xFFFB;


/*EUART3*/
volatile unsigned char xdata SCON3                       _at_ 0xFFD0;
volatile unsigned char xdata SBUF3                       _at_ 0xFFD1;
volatile unsigned char xdata SADDR3                      _at_ 0xFFD2;
volatile unsigned char xdata SADEN3                      _at_ 0xFFD3;
volatile unsigned char xdata SBRT3H                      _at_ 0xFFD4;
volatile unsigned char xdata SBRT3L                      _at_ 0xFFD5;

/* LCD */
volatile unsigned char xdata P4SS                        _at_ 0xFF80;
volatile unsigned char xdata P5SS                        _at_ 0xFF81;
volatile unsigned char xdata P6SS                        _at_ 0xFF82;
volatile unsigned char xdata P7SS                        _at_ 0xFF83;
volatile unsigned char xdata P8SS                        _at_ 0xFF84;
volatile unsigned char xdata P9SS                        _at_ 0xFF85;

/*TOUCH KEY*/
volatile unsigned char xdata TKST                        _at_ 0xFF9A;
volatile unsigned char xdata TKRANDOM                    _at_ 0xFF9B;
volatile unsigned char xdata TKDIV01                     _at_ 0xFF9C;
volatile unsigned char xdata TKDIV02                     _at_ 0xFF9D;
volatile unsigned char xdata TKDIV03                     _at_ 0xFF9E;
volatile unsigned char xdata TKDIV04                     _at_ 0xFF9F;
volatile unsigned char xdata TKCH                        _at_ 0xFF91;
volatile unsigned char xdata TKVREF                      _at_ 0xFF90;
volatile unsigned char xdata TK0THRL                     _at_ 0xFF92;
volatile unsigned char xdata TK0THRH                     _at_ 0xFF93;
volatile unsigned char xdata TK1THRL                     _at_ 0xFF94;
volatile unsigned char xdata TK1THRH                     _at_ 0xFF95;
volatile unsigned char xdata TK2THRL                     _at_ 0xFF96;
volatile unsigned char xdata TK2THRH                     _at_ 0xFF97;

/* RTC */ 
volatile unsigned char xdata SBSC                        _at_ 0xFFA0;
volatile unsigned char xdata SEC                         _at_ 0xFFA1;
volatile unsigned char xdata MIN                         _at_ 0xFFA2; 
volatile unsigned char xdata HR                          _at_ 0xFFA3;
volatile unsigned char xdata DAY                         _at_ 0xFFA4;
volatile unsigned char xdata MTH                         _at_ 0xFFA5;
volatile unsigned char xdata YR                          _at_ 0xFFA6;
volatile unsigned char xdata DOW                         _at_ 0xFFA7;
volatile unsigned char xdata RTCDATH                     _at_ 0xFFA8;
volatile unsigned char xdata RTCDATL                     _at_ 0xFFA9;
volatile unsigned char xdata RTCALM                      _at_ 0xFFAA;
volatile unsigned char xdata A0SEC                       _at_ 0xFFAB;
volatile unsigned char xdata A0MIN                       _at_ 0xFFAC;
volatile unsigned char xdata A0HR                        _at_ 0xFFAD;
volatile unsigned char xdata A0DAY                       _at_ 0xFFAE;
volatile unsigned char xdata A0DOW                       _at_ 0xFFAF;
volatile unsigned char xdata A1SEC                       _at_ 0xFFB0;
volatile unsigned char xdata A1MIN                       _at_ 0xFFB1;
volatile unsigned char xdata A1HR                        _at_ 0xFFB2;
volatile unsigned char xdata RTCCON                      _at_ 0xFFB3;
volatile unsigned char xdata RTCWR                       _at_ 0xFFB4;
volatile unsigned char xdata RTCPSW                      _at_ 0xFFB5;
volatile unsigned char xdata RTCIE                       _at_ 0xFFB6;
volatile unsigned char xdata RTCIF                       _at_ 0xFFB7;
volatile unsigned char xdata RTCECL                      _at_ 0xFFB8;
volatile unsigned char xdata RTCECH                      _at_ 0xFFB9;
volatile unsigned char xdata RTCTMR                      _at_ 0xFFBA;

/*7816*/
volatile unsigned char xdata S7816EN                     _at_ 0xFFC0;
volatile unsigned char xdata S7816CON                    _at_ 0xFFC1;
volatile unsigned char xdata EGTSET                      _at_ 0xFFC2;
volatile unsigned char xdata S7816WTH                    _at_ 0xFFC3;
volatile unsigned char xdata S7816WTL                    _at_ 0xFFC4;
volatile unsigned char xdata S7816CLKDIV                 _at_ 0xFFC5;
volatile unsigned char xdata S7816ETUH                   _at_ 0xFFC6;
volatile unsigned char xdata S7816ETUL                   _at_ 0xFFC7;
volatile unsigned char xdata RXBUF                       _at_ 0xFFC8;
volatile unsigned char xdata TXBUF                       _at_ 0xFFC9;
volatile unsigned char xdata S7816IE                     _at_ 0xFFCA;
volatile unsigned char xdata S7816STA                    _at_ 0xFFCB;
volatile unsigned char xdata S7816ERRSTA                 _at_ 0xFFCC;
volatile unsigned char xdata EGTRSEND                    _at_ 0xFFCD;





#endif
