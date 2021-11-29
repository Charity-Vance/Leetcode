/**
  ******************************************************************************
  * @file    fm32l0xx_iwdg.c
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    21-SEPT-2016
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of....:
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 


/** @addtogroup fm385_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG 
  * @brief IWDG driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup IWDG_Private_Functions
  * @{
  */ 

void IWDT_Clr(void)
{
	IWDT->IWDTSERV = WDTSERV_key;
}

void IWDT_Set(uint32_t period)
{
	RCC_PERIPH_clk_enable(IWDT_num);
	
	IWDT->IWDTCFG &= ~IWDT_IWDTOVP_Msk;
	IWDT->IWDTCFG |= period;

}


uint32_t IWDT_Read_Counter(void)
{
	uint32_t  temp;

	temp = IWDT->IWDTCNT;
	return temp;


}



/******END OF FILE****/



