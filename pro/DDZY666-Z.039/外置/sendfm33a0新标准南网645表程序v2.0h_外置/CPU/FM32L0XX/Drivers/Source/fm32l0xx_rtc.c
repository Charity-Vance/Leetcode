/**
  ******************************************************************************
  * @file    fm32l0xx_rtc.c
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    21-march-2017
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of realtime clock control (RCC) peripheral:
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 

/** @addtogroup fm385_StdPeriph_Driver
  * @{
  */

/** @defgroup RTC 
  * @brief RCC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RTC_WRITR_PROTECT_WORD  							((uint32_t)0x53535353)
#define RTC_WRITR_UNPROTECT_WORD  						((uint32_t)0xACACACAC)

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/




/** @defgroup RTC_Private_Functions
  * @{
  */
/** RTC_WRProtect
  * 
  */
void RTC_WRProtect(void)
{
	RTC->RTCWE = RTC_WRITR_PROTECT_WORD;
}

/** RTC_WRUNProtect
  * 
  */
void RTC_WRUNProtect(void)
{
	RTC->RTCWE = RTC_WRITR_UNPROTECT_WORD;
}

/** RTC_ITEnable
  * 
  */
void RTC_ITEnable(uint32_t EnableBit)
{
		RTC->RTCIE |= EnableBit;
}

/** RTC_ITDisable
  * 
  */
void RTC_ITDisable(uint32_t DisableBit)
{
		RTC->RTCIE &= ~DisableBit;

}

/** RTC_GetFlagSta
  * 
  */
ITStatus RTC_GetFlagSta(uint32_t RTC_IT)
{
	ITStatus bitstatus = RESET; 
	if ((RTC->RTCIF & RTC_IT)== RESET)
	{
		bitstatus = RESET;
	}
	else
	{
		bitstatus = SET;
	}
	return bitstatus; 
}

/** RTC_ClrITStatus
  * 
  */
void RTC_ClrITStatus(uint32_t RTC_IT)
{
		RTC->RTCIF  |= RTC_IT;

}

/** RTC_SetTime
  * 
  */
void RTC_SetTime(RTC_TimeType* RTC_TimeStruct,RTC_DateType* RTC_DateStruct)
{
	RTC_WRUNProtect();
	
	RTC->BCDYEAR = RTC_DateStruct->RTC_Year;
	RTC->BCDDATE = RTC_DateStruct->RTC_Date;
	RTC->BCDMONTH = RTC_DateStruct->RTC_Month;
	RTC->BCDWEEK = RTC_DateStruct->RTC_WeekDay;
	
	RTC->BCDHOUR = RTC_TimeStruct->RTC_Hours;
	RTC->BCDMIN = RTC_TimeStruct->RTC_Minutes;
	RTC->BCDSEC = RTC_TimeStruct->RTC_Seconds;

	RTC_WRProtect();
}

/** RTC_GetTime
  * 
  */
void RTC_GetTime(RTC_TimeType* RTC_TimeStruct,RTC_DateType* RTC_DateStruct)
{
	
	RTC_DateStruct->RTC_Year = RTC->BCDYEAR;
	RTC_DateStruct->RTC_Date = RTC->BCDDATE;
	RTC_DateStruct->RTC_Month = RTC->BCDMONTH;
	RTC_DateStruct->RTC_WeekDay = RTC->BCDWEEK;
	
	RTC_TimeStruct->RTC_Hours = RTC->BCDHOUR;
	RTC_TimeStruct->RTC_Minutes = RTC->BCDMIN;
	RTC_TimeStruct->RTC_Seconds = RTC->BCDSEC;

}

/** RTC_SetAlarm
  * 
  */
void RTC_SetAlarm(RTC_TimeType* RTC_TimeStruct)
{
	uint32_t tmpreg = 0;
	
	tmpreg = (((uint32_t)RTC_TimeStruct->RTC_Hours)<<24)|\
						(((uint32_t)RTC_TimeStruct->RTC_Minutes)<<24)|\
						(((uint32_t)RTC_TimeStruct->RTC_Seconds)<<24);

	RTC->ALARM = tmpreg;

}
/******END OF FILE****/



