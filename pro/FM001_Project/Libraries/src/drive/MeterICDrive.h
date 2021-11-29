
///*****************************************************************************************///
///*Copyright：    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
///*File name:     
///*Version:       V1
///*Date:          2014-3-12
///*Description:   
///*Function List: 
///*****************************************************************************************///
#ifndef	__MeterICDrive_H
#define	__MeterICDrive_H


#include "Public.h"
#include "IO.h"
#include "Timer.h"

//static ulong32 SV_ulTemp_GPIO;

///*****************************************************************************************///
///*io 口线操作的宏定义*///
///*****************************************************************************************///
#define	SET_EMETERDOUT_INPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERDOUT->MODER;\
								SV_ulTemp_GPIO &= EMETERDOUT_IN_MODE;\
								IO_EMETERDOUT->MODER = SV_ulTemp_GPIO;\
								IO_EMETERDOUT->INEN |= EMETERDOUT_INOn;\
								SV_ulTemp_GPIO = IO_EMETERDOUT->PUPDR;\
								SV_ulTemp_GPIO &= EMETERDOUT_NOPUPD;\
								IO_EMETERDOUT->PUPDR = SV_ulTemp_GPIO;}

#define	SET_EMETERDIN_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERDIN->MODER;\
								SV_ulTemp_GPIO &= EMETERDIN_IN_MODE;\
								SV_ulTemp_GPIO |= EMETERDIN_OUT_MODE;\
								IO_EMETERDIN->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERDIN->OTYPER;\
								SV_ulTemp_GPIO &= EMETERDIN_OUTPUT_PP;\
								IO_EMETERDIN->OTYPER = SV_ulTemp_GPIO;}

#define	SET_EMETERCS_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERCS->MODER;\
								SV_ulTemp_GPIO &= EMETERCS_IN_MODE;\
								SV_ulTemp_GPIO |= EMETERCS_OUT_MODE;\
								IO_EMETERCS->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERCS->OTYPER;\
								SV_ulTemp_GPIO &= EMETERCS_OUTPUT_PP;\
								IO_EMETERCS->OTYPER = SV_ulTemp_GPIO;}

#define	SET_EMETERSCK_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERSCK->MODER;\
								SV_ulTemp_GPIO &= EMETERSCK_IN_MODE;\
								SV_ulTemp_GPIO |= EMETERSCK_OUT_MODE;\
								IO_EMETERSCK->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERSCK->OTYPER;\
								SV_ulTemp_GPIO &= EMETERSCK_OUTPUT_PP;\
								IO_EMETERSCK->OTYPER = SV_ulTemp_GPIO;}

#define	SET_EMETERRST_OUTPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERRST->MODER;\
								SV_ulTemp_GPIO &= EMETERRST_IN_MODE;\
								SV_ulTemp_GPIO |= EMETERRST_OUT_MODE;\
								IO_EMETERRST->MODER = SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERRST->OTYPER;\
								SV_ulTemp_GPIO &= EMETERRST_OUTPUT_PP;\
								IO_EMETERRST->OTYPER = SV_ulTemp_GPIO;}

#define	SET_EMETERIRQ_INPUT()	{ulong32 SV_ulTemp_GPIO;\
								SV_ulTemp_GPIO = IO_EMETERIRQ->MODER;\
								SV_ulTemp_GPIO &= EMETERIRQ_IN_MODE;\
								IO_EMETERIRQ->MODER = SV_ulTemp_GPIO;\
								IO_EMETERIRQ->INEN |= EMETERIRQ_INOn;\
								SV_ulTemp_GPIO = IO_EMETERIRQ->PUPDR;\
								SV_ulTemp_GPIO |= EMETERIRQ_PULLUP;\
								IO_EMETERIRQ->PUPDR = SV_ulTemp_GPIO;}

#define	EMETERDIN_OUT_0			(IO_EMETERDIN->BSRR = EMETERDINRESET)
#define	EMETERDIN_OUT_1			(IO_EMETERDIN->BSETH = EMETERDINSET)
#define	EMETERCS_EN				(IO_EMETERCS->BSRR = EMETERCSRESET)
#define	EMETERCS_DIS			(IO_EMETERCS->BSETH = EMETERCSSET)
#define	EMETERSCK_OUT_0			(IO_EMETERSCK->BSRR = EMETERSCKRESET)
#define	EMETERSCK_OUT_1			(IO_EMETERSCK->BSETH = EMETERSCKSET)
#define	EMETERRST_RESET			(IO_EMETERRST->BSETH = EMETERRSTSET)
#define	EMETERRST_WORK			(IO_EMETERRST->BSRR = EMETERRSTRESET)
#define	READ_EMETERDOUT			(IO_EMETERDOUT->IDR & EMETERDOUT_SELECT)
#define	READ_EMETERIRQ			(IO_EMETERIRQ->IDR & EMETERIRQ_SELECT)





#endif
