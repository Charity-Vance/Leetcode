/**
  ******************************************************************************
  * @file    fm32l0xx_scu.c
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    21-JUN-2016
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the system control unit (scu) peripheral:
  *           + debug control unit (scu) peripheral
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 

/** @addtogroup fm385_StdPeriph_Driver
  * @{
  */

/** @defgroup SCU 
  * @brief SCU driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SCU_Private_Functions
  * @{
  */
	
FlagStatus SCU_Get_VERIFAIL(void)
{
	FlagStatus bitstatus = RESET;
	
	if((SCU->SYSCON & SCU_SYSCON_VERIFAIL_Msk) != (uint32_t)RESET)
	{
			bitstatus = SET;
	}
	else
	{
		  bitstatus = RESET;
	}	

	/* Return the VERIFAIL status */
  return  bitstatus;
}

void SCU_Set_DBGCFG(uint32_t set_bit)
{
	SCU->DBGCFG |= set_bit;

}

void SCU_Clr_DBGCFG(uint32_t clr_bit)
{
	SCU->DBGCFG &= ~clr_bit;

}

/******END OF FILE****/



