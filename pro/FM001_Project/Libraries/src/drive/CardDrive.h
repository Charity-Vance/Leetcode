
///*****************************************************************************************///
///*Copyright£º    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__CardDrive_H
#define	__CardDrive_H


#include "IO.h"
#include "Timer.h"

//static	ulong32	SV_ulTemp_CARD;





#define	SwitchOn_CardPower()	{ulong32 i;\
								IO_CARDPOWER->OTYPER &= CARDPOWER_OUTPUT_PP;\
								IO_CARDPOWER->BSRR = CARDPOWERRESET;\
								i = IO_CARDPOWER->MODER;\
								i &= CARDPOWER_IN_MODE;\
								i |= CARDPOWER_OUT_MODE;\
								IO_CARDPOWER->MODER = i;\
								IO_CARDPOWER->BSRR = CARDPOWERRESET;}
								
#define	SwitchOff_CardPower()	{ulong32 i;\
								IO_CARDPOWER->OTYPER &= CARDPOWER_OUTPUT_PP;\
								IO_CARDPOWER->BSETH = CARDPOWERSET;\
								i = IO_CARDPOWER->MODER;\
								i &= CARDPOWER_IN_MODE;\
								i |= CARDPOWER_OUT_MODE;\
								IO_CARDPOWER->MODER = i;\
								IO_CARDPOWER->BSETH = CARDPOWERSET;}
								
#define	SwitchOn_CardSck()		{ulong32 i;\
								IO_CARDSCK->OTYPER &= CARDSCK_OUTPUT_PP;\
								IO_CARDSCK->BSRR = CARDSCKRESET;\
								i = IO_CARDSCK->MODER;\
								i &= CARDSCK_IN_MODE;\
								i |= CARDSCK_OUT_MODE;\
								IO_CARDSCK->MODER = i;\
								IO_CARDSCK->BSRR = CARDSCKRESET;}
								
#define	SwitchOff_CardSck()		{ulong32 i;\
								IO_CARDSCK->OTYPER &= CARDSCK_OUTPUT_PP;\
								IO_CARDSCK->BSETH = CARDSCKSET;\
								i = IO_CARDSCK->MODER;\
								i &= CARDSCK_IN_MODE;\
								i |= CARDSCK_OUT_MODE;\
								IO_CARDSCK->MODER = i;\
								IO_CARDSCK->BSETH = CARDSCKSET;}

#define	Card_EN()				{ulong32 i;\
								IO_CARDRESET->OTYPER &= CARDRESET_OUTPUT_PP;\
								IO_CARDRESET->BSRR = CARDRESETRESET;\
								i = IO_CARDRESET->MODER;\
								i &= CARDRESET_IN_MODE;\
								i |= CARDRESET_OUT_MODE;\
								IO_CARDRESET->MODER = i;\
								IO_CARDRESET->BSRR = CARDRESETRESET;}
								
#define	Card_Reset()			{ulong32 i;\
								IO_CARDRESET->OTYPER &= CARDRESET_OUTPUT_PP;\
								IO_CARDRESET->BSETH = CARDRESETSET;\
								i = IO_CARDRESET->MODER;\
								i &= CARDRESET_IN_MODE;\
								i |= CARDRESET_OUT_MODE;\
								IO_CARDRESET->MODER = i;\
								IO_CARDRESET->BSETH = CARDRESETSET;}

								
//#define	CardIO_Init()			{ulong32 i;\
//								IO_CARDDATA->PUPDR &= CARDDATA_NOPUPD;\
//								IO_CARDDATA->OTYPER |= CARDDATA_OUTPUT_OD;\
//								IO_CARDDATA->BSETH = CARDDATASET;\
//								i = IO_CARDDATA->MODER;\
//								i &= CARDDATA_IN_MODE;\
//								i |= CARDDATA_OUT_MODE;\
//								IO_CARDDATA->MODER = i;\
//								IO_CARDDATA->BSETH = CARDDATASET;}

#define	CardDataIO_T_1()		{ulong32 i;\
								IO_CARDDATA->BSETH = CARDDATASET;\
								i = IO_CARDDATA->MODER;\
								i &= CARDDATA_IN_MODE;\
								i |= CARDDATA_OUT_MODE;\
								IO_CARDDATA->MODER = i;\
								IO_CARDDATA->BSETH = CARDDATASET;}

#define	CardDataIO_T_0()		{ulong32 i;\
								IO_CARDDATA->BSRR = CARDDATARESET;\
								i = IO_CARDDATA->MODER;\
								i &= CARDDATA_IN_MODE;\
								i |= CARDDATA_OUT_MODE;\
								IO_CARDDATA->MODER = i;}

#define	CardDataIO_R()			{ulong32 i;\
								i = IO_CARDDATA->MODER;\
								i &= CARDDATA_IN_MODE;\
								IO_CARDDATA->MODER = i;\
								IO_CARDDATA->INEN |= CARDDATA_INOn;}


#define	READ_CARD_DATA		(IO_CARDDATA->IDR & CARDDATA_SELECT)




extern void DF_Switch_CardPower(uchar8 Act);
extern void DF_Switch_CardSck(uchar8 Act);
extern void DF_Switch_CardEn(uchar8 Act);
void DisIRQ_ExceptETIM4(void);
void EnIRQ_ExceptETIM4(void);
#endif
