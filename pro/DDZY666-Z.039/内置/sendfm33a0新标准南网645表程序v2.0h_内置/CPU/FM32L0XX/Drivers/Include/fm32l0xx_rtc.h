/**
  ******************************************************************************
  * @file    fm32l0xx_rtc.h
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    7-MAR-2017
  * @brief   This file contains all the functions prototypes for the RTC firmware library.  
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_RTC_H
#define __FM32L0xx_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM385_StdPeriph_Driver
  * @{
  */

/** @addtogroup RTC
  * @{
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTC_Exported_Constants
  * @{
  */
  
	 
/* Exported types ------------------------------------------------------------*/	 

/** 
  * @brief  RTC Time structure definition  
  */
typedef struct
{
  uint8_t RTC_Hours;    /*!< Specifies the RTC Time Hour (in BCD format).
                        This parameter must be set to a value in the 0-23 range */

  uint8_t RTC_Minutes;  /*!< Specifies the RTC Time Minutes (in BCD format).
                        This parameter must be set to a value in the 0-59 range. */
  
  uint8_t RTC_Seconds;  /*!< Specifies the RTC Time Seconds (in BCD format).
                        This parameter must be set to a value in the 0-59 range. */

}RTC_TimeType; 

/** 
  * @brief  RTC Date structure definition  
  */
typedef struct
{
  uint8_t RTC_WeekDay; /*!< Specifies the RTC Date WeekDay. */
  
  uint8_t RTC_Month;   /*!< Specifies the RTC Date Month (in BCD format).  */

  uint8_t RTC_Date;     /*!< Specifies the RTC Date (in BCD format).  */
  
  uint8_t RTC_Year;     /*!< Specifies the RTC Date Year (in BCD format).
                        This parameter must be set to a value in the 0-99 range. */
}RTC_DateType;

/** 
  * @brief  RTC Adjust Date structure definition  
  */
typedef struct
{
  uint8_t RTC_Common; 	/*!< Specifies the RTC Common adjust data. */
  
  uint8_t RTC_Diff;   	/*!< Specifies the RTC Differential adjust Date. */

}RTC_AdjustType;	 


/**
* @}RTC_RTCWE
*/ 

/** @defgroup RTC_RTCWE_RTCWE
  * @{
  */
#define RTC_RTCWE_RTCWE_Pos		               					  0                                            
#define RTC_RTCWE_RTCWE_Msk               						  (0x01UL << RTC_RTCWE_RTCWE_Pos) 
#define RTC_RTCWE_RTCWE_DISABLE     									  ((uint32_t)0x00000000)
#define RTC_RTCWE_RTCWE_ENABLE     									    ((uint32_t)0x00000001)


/**
* @}RTC_RTCIE
*/ 

/** @defgroup RTC_RTCIE_DATE_IE
  * @{
  */
#define RTC_RTCIE_DATE_IE_Pos		               					0                                            
#define RTC_RTCIE_DATE_IE_Msk               						(0x01UL << RTC_RTCIE_DATE_IE_Pos) 
#define RTC_RTCIE_DATE_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_DATE_IE_ENABLE     									  ((uint32_t)0x00000001)

/** @defgroup RTC_RTCIE_HOUR_IE
  * @{
  */
#define RTC_RTCIE_HOUR_IE_Pos		               					1                                            
#define RTC_RTCIE_HOUR_IE_Msk               						(0x01UL << RTC_RTCIE_HOUR_IE_Pos) 
#define RTC_RTCIE_HOUR_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_HOUR_IE_ENABLE     									  ((uint32_t)0x00000002)

/** @defgroup RTC_RTCIE_MIN_IE
  * @{
  */
#define RTC_RTCIE_MIN_IE_Pos		               					2                                            
#define RTC_RTCIE_MIN_IE_Msk               							(0x01UL << RTC_RTCIE_MIN_IE_Pos) 
#define RTC_RTCIE_MIN_IE_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIE_MIN_IE_ENABLE     									  ((uint32_t)0x00000004)

/** @defgroup RTC_RTCIE_SEC_IE
  * @{
  */
#define RTC_RTCIE_SEC_IE_Pos		               					3                                            
#define RTC_RTCIE_SEC_IE_Msk               							(0x01UL << RTC_RTCIE_SEC_IE_Pos) 
#define RTC_RTCIE_SEC_IE_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIE_SEC_IE_ENABLE     									  ((uint32_t)0x00000008)

/** @defgroup RTC_RTCIE_2HZ_IE
  * @{
  */
#define RTC_RTCIE_2HZ_IE_Pos		               					4                                            
#define RTC_RTCIE_2HZ_IE_Msk               							(0x01UL << RTC_RTCIE_2HZ_IE_Pos) 
#define RTC_RTCIE_2HZ_IE_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIE_2HZ_IE_ENABLE     									  ((uint32_t)0x00000010)

/** @defgroup RTC_RTCIE_4HZ_IE
  * @{
  */
#define RTC_RTCIE_4HZ_IE_Pos		               					5                                            
#define RTC_RTCIE_4HZ_IE_Msk               							(0x01UL << RTC_RTCIE_4HZ_IE_Pos) 
#define RTC_RTCIE_4HZ_IE_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIE_4HZ_IE_ENABLE     									  ((uint32_t)0x00000020)

/** @defgroup RTC_RTCIE_8HZ_IE
  * @{
  */
#define RTC_RTCIE_8HZ_IE_Pos		               					6                                            
#define RTC_RTCIE_8HZ_IE_Msk               							(0x01UL << RTC_RTCIE_8HZ_IE_Pos) 
#define RTC_RTCIE_8HZ_IE_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIE_8HZ_IE_ENABLE     									  ((uint32_t)0x00000040)

/** @defgroup RTC_RTCIE_16HZ_IE
  * @{
  */
#define RTC_RTCIE_16HZ_IE_Pos		               					7                                            
#define RTC_RTCIE_16HZ_IE_Msk               						(0x01UL << RTC_RTCIE_16HZ_IE_Pos) 
#define RTC_RTCIE_16HZ_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_16HZ_IE_ENABLE     									  ((uint32_t)0x00000080)

/** @defgroup RTC_RTCIE_64HZ_IE
  * @{
  */
#define RTC_RTCIE_64HZ_IE_Pos		               					8                                            
#define RTC_RTCIE_64HZ_IE_Msk               						(0x01UL << RTC_RTCIE_64HZ_IE_Pos) 
#define RTC_RTCIE_64HZ_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_64HZ_IE_ENABLE     									  ((uint32_t)0x00000100)

/** @defgroup RTC_RTCIE_256HZ_IE
  * @{
  */
#define RTC_RTCIE_256HZ_IE_Pos		               				9                                            
#define RTC_RTCIE_256HZ_IE_Msk               						(0x01UL << RTC_RTCIE_256HZ_IE_Pos) 
#define RTC_RTCIE_256HZ_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_256HZ_IE_ENABLE     									((uint32_t)0x00000200)

/** @defgroup RTC_RTCIE_1KHZ_IE
  * @{
  */
#define RTC_RTCIE_1KHZ_IE_Pos		               					10                                            
#define RTC_RTCIE_1KHZ_IE_Msk               						(0x01UL << RTC_RTCIE_1KHZ_IE_Pos) 
#define RTC_RTCIE_1KHZ_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_1KHZ_IE_ENABLE     										((uint32_t)0x00000400)

/** @defgroup RTC_RTCIE_ALARM_IE
  * @{
  */
#define RTC_RTCIE_ALARM_IE_Pos		               				11                                            
#define RTC_RTCIE_ALARM_IE_Msk               						(0x01UL << RTC_RTCIE_ALARM_IE_Pos) 
#define RTC_RTCIE_ALARM_IE_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIE_ALARM_IE_ENABLE     									((uint32_t)0x00000800)

/** @defgroup RTC_RTCIE_ADJ128_IE
  * @{
  */
#define RTC_RTCIE_ADJ128_IE_Pos		               				12                                            
#define RTC_RTCIE_ADJ128_IE_Msk               					(0x01UL << RTC_RTCIE_ADJ128_IE_Pos) 
#define RTC_RTCIE_ADJ128_IE_DISABLE     								((uint32_t)0x00000000)
#define RTC_RTCIE_ADJ128_IE_ENABLE     									((uint32_t)0x00001000)

/** @defgroup RTC_RTCIE_STPF0IE
  * @{
  */
#define RTC_RTCIE_STPF0IE_Pos		               				  13                                            
#define RTC_RTCIE_STPF0IE_Msk               					  (0x01UL << RTC_RTCIE_STPF0IE_Pos) 
#define RTC_RTCIE_STPF0IE_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIE_STPF0IE_ENABLE     									  ((uint32_t)0x00002000)

/** @defgroup RTC_RTCIE_STPR0IE
  * @{
  */
#define RTC_RTCIE_STPR0IE_Pos		               				  14                                            
#define RTC_RTCIE_STPR0IE_Msk               					  (0x01UL << RTC_RTCIE_STPR0IE_Pos) 
#define RTC_RTCIE_STPR0IE_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIE_STPR0IE_ENABLE     									  ((uint32_t)0x00004000)

/** @defgroup RTC_RTCIE_STPF1IE
  * @{
  */
#define RTC_RTCIE_STPF1IE_Pos		               				  15                                            
#define RTC_RTCIE_STPF1IE_Msk               					  (0x01UL << RTC_RTCIE_STPF1IE_Pos) 
#define RTC_RTCIE_STPF1IE_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIE_STPF1IE_ENABLE     									  ((uint32_t)0x00008000)

/** @defgroup RTC_RTCIE_STPR1IE
  * @{
  */
#define RTC_RTCIE_STPR1IE_Pos		               				  16                                            
#define RTC_RTCIE_STPR1IE_Msk               					  (0x01UL << RTC_RTCIE_STPR1IE_Pos) 
#define RTC_RTCIE_STPR1IE_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIE_STPR1IE_ENABLE     									  ((uint32_t)0x00010000)


/**
* @}RTC_RTCIF
*/ 

/** @defgroup RTC_RTCIF_DATE_IF
  * @{
  */
#define RTC_RTCIF_DATE_IF_Pos		               					0                                            
#define RTC_RTCIF_DATE_IF_Msk               						(0x01UL << RTC_RTCIF_DATE_IF_Pos) 
#define RTC_RTCIF_DATE_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_DATE_IF_ENABLE     									  ((uint32_t)0x00000001)

/** @defgroup RTC_RTCIF_HOUR_IF
  * @{
  */
#define RTC_RTCIF_HOUR_IF_Pos		               					1                                            
#define RTC_RTCIF_HOUR_IF_Msk               						(0x01UL << RTC_RTCIF_HOUR_IF_Pos) 
#define RTC_RTCIF_HOUR_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_HOUR_IF_ENABLE     									  ((uint32_t)0x00000002)

/** @defgroup RTC_RTCIF_MIN_IF
  * @{
  */
#define RTC_RTCIF_MIN_IF_Pos		               					2                                            
#define RTC_RTCIF_MIN_IF_Msk               							(0x01UL << RTC_RTCIF_MIN_IF_Pos) 
#define RTC_RTCIF_MIN_IF_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIF_MIN_IF_ENABLE     									  ((uint32_t)0x00000004)

/** @defgroup RTC_RTCIF_SEC_IF
  * @{
  */
#define RTC_RTCIF_SEC_IF_Pos		               					3                                            
#define RTC_RTCIF_SEC_IF_Msk               							(0x01UL << RTC_RTCIF_SEC_IF_Pos) 
#define RTC_RTCIF_SEC_IF_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIF_SEC_IF_ENABLE     									  ((uint32_t)0x00000008)

/** @defgroup RTC_RTCIF_2HZ_IF
  * @{
  */
#define RTC_RTCIF_2HZ_IF_Pos		               					4                                            
#define RTC_RTCIF_2HZ_IF_Msk               							(0x01UL << RTC_RTCIF_2HZ_IF_Pos) 
#define RTC_RTCIF_2HZ_IF_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIF_2HZ_IF_ENABLE     									  ((uint32_t)0x00000010)

/** @defgroup RTC_RTCIF_4HZ_IF
  * @{
  */
#define RTC_RTCIF_4HZ_IF_Pos		               					5                                            
#define RTC_RTCIF_4HZ_IF_Msk               							(0x01UL << RTC_RTCIF_4HZ_IF_Pos) 
#define RTC_RTCIF_4HZ_IF_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIF_4HZ_IF_ENABLE     									  ((uint32_t)0x00000020)

/** @defgroup RTC_RTCIF_8HZ_IF
  * @{
  */
#define RTC_RTCIF_8HZ_IF_Pos		               					6                                            
#define RTC_RTCIF_8HZ_IF_Msk               							(0x01UL << RTC_RTCIF_8HZ_IF_Pos) 
#define RTC_RTCIF_8HZ_IF_DISABLE     										((uint32_t)0x00000000)
#define RTC_RTCIF_8HZ_IF_ENABLE     									  ((uint32_t)0x00000040)

/** @defgroup RTC_RTCIF_16HZ_IF
  * @{
  */
#define RTC_RTCIF_16HZ_IF_Pos		               					7                                            
#define RTC_RTCIF_16HZ_IF_Msk               						(0x01UL << RTC_RTCIF_16HZ_IF_Pos) 
#define RTC_RTCIF_16HZ_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_16HZ_IF_ENABLE     									  ((uint32_t)0x00000080)

/** @defgroup RTC_RTCIF_64HZ_IF
  * @{
  */
#define RTC_RTCIF_64HZ_IF_Pos		               					8                                            
#define RTC_RTCIF_64HZ_IF_Msk               						(0x01UL << RTC_RTCIF_64HZ_IF_Pos) 
#define RTC_RTCIF_64HZ_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_64HZ_IF_ENABLE     									  ((uint32_t)0x00000100)

/** @defgroup RTC_RTCIF_256HZ_IF
  * @{
  */
#define RTC_RTCIF_256HZ_IF_Pos		               				9                                            
#define RTC_RTCIF_256HZ_IF_Msk               						(0x01UL << RTC_RTCIF_256HZ_IF_Pos) 
#define RTC_RTCIF_256HZ_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_256HZ_IF_ENABLE     									((uint32_t)0x00000200)

/** @defgroup RTC_RTCIF_1KHZ_IF
  * @{
  */
#define RTC_RTCIF_1KHZ_IF_Pos		               					10                                            
#define RTC_RTCIF_1KHZ_IF_Msk               						(0x01UL << RTC_RTCIF_1KHZ_IF_Pos) 
#define RTC_RTCIF_1KHZ_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_1KHZ_IF_ENABLE     										((uint32_t)0x00000400)

/** @defgroup RTC_RTCIF_ALARM_IF
  * @{
  */
#define RTC_RTCIF_ALARM_IF_Pos		               				11                                            
#define RTC_RTCIF_ALARM_IF_Msk               						(0x01UL << RTC_RTCIF_ALARM_IF_Pos) 
#define RTC_RTCIF_ALARM_IF_DISABLE     									((uint32_t)0x00000000)
#define RTC_RTCIF_ALARM_IF_ENABLE     									((uint32_t)0x00000800)

/** @defgroup RTC_RTCIF_ADJ128_IF
  * @{
  */
#define RTC_RTCIF_ADJ128_IF_Pos		               				12                                            
#define RTC_RTCIF_ADJ128_IF_Msk               					(0x01UL << RTC_RTCIF_ADJ128_IF_Pos) 
#define RTC_RTCIF_ADJ128_IF_DISABLE     								((uint32_t)0x00000000)
#define RTC_RTCIF_ADJ128_IF_ENABLE     									((uint32_t)0x00001000)

/** @defgroup RTC_RTCIF_STPF0IF
  * @{
  */
#define RTC_RTCIF_STPF0IF_Pos		               				  13                                            
#define RTC_RTCIF_STPF0IF_Msk               					  (0x01UL << RTC_RTCIF_STPF0IF_Pos) 
#define RTC_RTCIF_STPF0IF_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIF_STPF0IF_ENABLE     									  ((uint32_t)0x00002000)

/** @defgroup RTC_RTCIF_STPR0IF
  * @{
  */
#define RTC_RTCIF_STPR0IF_Pos		               				  14                                            
#define RTC_RTCIF_STPR0IF_Msk               					  (0x01UL << RTC_RTCIF_STPR0IF_Pos) 
#define RTC_RTCIF_STPR0IF_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIF_STPR0IF_ENABLE     									  ((uint32_t)0x00004000)

/** @defgroup RTC_RTCIF_STPF1IF
  * @{
  */
#define RTC_RTCIF_STPF1IF_Pos		               				  15                                            
#define RTC_RTCIF_STPF1IF_Msk               					  (0x01UL << RTC_RTCIF_STPF1IF_Pos) 
#define RTC_RTCIF_STPF1IF_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIF_STPF1IF_ENABLE     									  ((uint32_t)0x00008000)

/** @defgroup RTC_RTCIF_STPR1IF
  * @{
  */
#define RTC_RTCIF_STPR1IF_Pos		               				  16                                            
#define RTC_RTCIF_STPR1IF_Msk               					  (0x01UL << RTC_RTCIF_STPR1IF_Pos) 
#define RTC_RTCIF_STPR1IF_DISABLE     								  ((uint32_t)0x00000000)
#define RTC_RTCIF_STPR1IF_ENABLE     									  ((uint32_t)0x00010000)


/**
* @}RTC_FSEL
*/ 

/** @defgroup RTC_FSEL_FSEL
  * @{
  */
#define RTC_FSEL_FSEL_Pos		               							0                                            
#define RTC_FSEL_FSEL_Msk               								(0x0FUL << RTC_FSEL_FSEL_Pos) 
#define RTC_FSEL_FSEL_PLL_1S    												((uint32_t)0x00000000)
#define RTC_FSEL_FSEL_PLL_80ms    									  	((uint32_t)0x00000001)
#define RTC_FSEL_FSEL_SEC_CIN_1s												((uint32_t)0x00000002)
#define RTC_FSEL_FSEL_MIN_CIN_1s    									  ((uint32_t)0x00000003)
#define RTC_FSEL_FSEL_HOUR_CIN_1s												((uint32_t)0x00000004)
#define RTC_FSEL_FSEL_DATE_CIN_1s    									  ((uint32_t)0x00000005)
#define RTC_FSEL_FSEL_ALARM    													((uint32_t)0x00000006)
#define RTC_FSEL_FSEL_128s    									  			((uint32_t)0x00000007)
#define RTC_FSEL_FSEL_REV_PLL_80ms 											((uint32_t)0x00000008)
#define RTC_FSEL_FSEL_REV_SEC_CIN								  			((uint32_t)0x00000009)
#define RTC_FSEL_FSEL_REV_MIN_CIN												((uint32_t)0x0000000A)
#define RTC_FSEL_FSEL_REV_HOUR_CIN    				  				((uint32_t)0x0000000B)
#define RTC_FSEL_FSEL_REV_DATA_CIN  										((uint32_t)0x0000000C)
#define RTC_FSEL_FSEL_REV_ALARM   							  			((uint32_t)0x0000000D)
#define RTC_FSEL_FSEL_REV_PLL_1s  											((uint32_t)0x0000000E)
#define RTC_FSEL_FSEL_TimeScale_1s    				  		    ((uint32_t)0x0000000F)


/**
* @}RTC_ADSIGN
*/ 

/** @defgroup RTC_ADSIGN_ADSIGN
  * @{
  */
#define RTC_ADSIGN_ADSIGN_Pos		               					0                                            
#define RTC_ADSIGN_ADSIGN_Msk               						(0x01UL << RTC_ADSIGN_ADSIGN_Pos) 
#define RTC_ADSIGN_ADSIGN_INCREASE     									((uint32_t)0x00000000)
#define RTC_ADSIGN_ADSIGN_DECREASE     									((uint32_t)0x00000001)


/**
* @}RTC_PR1SEN
*/ 

/** @defgroup RTC_PR1SEN_PR1SEN
  * @{
  */
#define RTC_PR1SEN_PR1SEN_Pos		               					0                                            
#define RTC_PR1SEN_PR1SEN_Msk               						(0x01UL << RTC_PR1SEN_PR1SEN_Pos) 
#define RTC_PR1SEN_PR1SEN_DISABLE     									((uint32_t)0x00000000)
#define RTC_PR1SEN_PR1SEN_ENABLE	     									((uint32_t)0x00000001)


/**
* @}RTC_STAMPEN
*/ 

/** @defgroup RTC_STAMPEN_STAMP0EN
  * @{
  */
#define RTC_STAMPEN_STAMP0EN_Pos		               	 		0                                            
#define RTC_STAMPEN_STAMP0EN_Msk               					(0x01UL << RTC_STAMPEN_STAMP0EN_Pos) 
#define RTC_STAMPEN_STAMP0EN_DISABLE     								((uint32_t)0x00000000)
#define RTC_STAMPEN_STAMP0EN_ENABLE	     								((uint32_t)0x00000001)

/** @defgroup RTC_STAMPEN_STAMP1EN
  * @{
  */
#define RTC_STAMPEN_STAMP1EN_Pos		               			1                                            
#define RTC_STAMPEN_STAMP1EN_Msk               					(0x01UL << RTC_STAMPEN_STAMP1EN_Pos) 
#define RTC_STAMPEN_STAMP1EN_DISABLE     								((uint32_t)0x00000000)
#define RTC_STAMPEN_STAMP1EN_ENABLE	     								((uint32_t)0x00000002)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 
extern void RTC_WRProtect(void);
extern void RTC_WRUNProtect(void);
extern void RTC_ITEnable(uint32_t EnableBit);
extern void RTC_ITDisable(uint32_t DisableBit);
extern ITStatus RTC_GetFlagSta(uint32_t RTC_IT);
extern void RTC_ClrITStatus(uint32_t RTC_IT);
extern void RTC_SetTime(RTC_TimeType* RTC_TimeStruct,RTC_DateType* RTC_DateStruct);
extern void RTC_GetTime(RTC_TimeType* RTC_TimeStruct,RTC_DateType* RTC_DateStruct);



#ifdef __cplusplus
}
#endif

#endif /* __FM32L0xx_RTC_H */



/************************ (C) COPYRIGHT FMSHelectronics *****END OF FILE****/



