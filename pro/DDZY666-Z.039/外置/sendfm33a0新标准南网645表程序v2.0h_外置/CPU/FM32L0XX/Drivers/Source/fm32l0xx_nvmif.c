/**
  ******************************************************************************
  * @file    fm32l0xx_nvmif.c
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    21-SEPT-2016
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the clock control (RCC) peripheral:
  *           + Internal/external clocks, PLL, CSS and MCO configuration
  *           + System, AHB and APB busses clocks configuration
  *           + Peripheral clocks configuration
  *           + Interrupts and flags management
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 


/** @addtogroup fm385_StdPeriph_Driver
  * @{
  */

/** @defgroup NVMIF 
  * @brief NVMIF driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup NVMIF_Private_Functions
  * @{
  */ 
	
//mini delay is 50.25US
void delay_50(uint32_t dlength)     //50US
{
	uint32_t i,j;
	for (i=0;i<dlength;i++)
	{
 		IWDT_Clr();
		for (j=0;j<0x39;j++)
		{
			__NOP();
			
		}
	}
}

void NVMIF_INIT(void)
{
	RCC_PERIPH_clk_enable(FLS_num);

}

void NVMIF_DeINIT(void)
{
	RCC_PERIPH_clk_disable(FLS_num);

}

void NVMIF_SET_waitcycle(uint32_t cycle_num)
{
	NVMIF->FLSRDCON &= ~NVMIF_FLSRDCON_WAIT_Msk;
	NVMIF->FLSRDCON |= cycle_num << NVMIF_FLSRDCON_WAIT_Pos;
}

void NVMIF_PREFATCH_enable(void)
{
	NVMIF->PRFTCON = NVMIF_PRFTCON_PRFTEN_ENABLE;
}

void NVMIF_PREFATCH_disable(void)
{
	NVMIF->PRFTCON &= ~NVMIF_PRFTCON_PRFTEN_ENABLE;
}

void NVMIF_ERASE_sector(uint32_t* erase_addr)
{
	//set to sector erase
	NVMIF->EPCON &= ~NVMIF_EPCON_ERTYPE_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_ERTYPE_SECTOR;
	
	//CLR PREQ,SET EREQ
	NVMIF->EPCON &= ~NVMIF_EPCON_PREQ_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_EREQ_SET;
	
	//write flash key
	NVMIF->FLSKEY = flash_sector_erase_key0;
	NVMIF->FLSKEY = flash_sector_erase_key1;
	
	//start erase
	*erase_addr = flash_erase_data;
	
	//delay 10ms
	delay_50(200);
	
	NVMIF->FLSKEY = 0xBB006600;
}

void NVMIF_ERASE_block(uint32_t* erase_addr)
{
		//set to block erase
	NVMIF->EPCON &= ~NVMIF_EPCON_ERTYPE_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_ERTYPE_BLOCK;
	
	//CLR PREQ,SET EREQ
	NVMIF->EPCON &= ~NVMIF_EPCON_PREQ_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_EREQ_SET;
	
	//write flash key
	NVMIF->FLSKEY = flash_block_erase_key0;
	NVMIF->FLSKEY = flash_block_erase_key1;
	
	//start erase
	*erase_addr = flash_erase_data;
	
	//delay 10ms
	delay_50(200);
	
	NVMIF->FLSKEY = 0xBB006600;
}

void NVMIF_ERASE_chip(void)
{
		uint32_t* erase_addr;
		//set to block erase
	NVMIF->EPCON &= ~NVMIF_EPCON_ERTYPE_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_ERTYPE_CHIP;
	
	//CLR PREQ,SET EREQ
	NVMIF->EPCON &= ~NVMIF_EPCON_PREQ_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_EREQ_SET;
	
	//write flash key
	NVMIF->FLSKEY = flash_chip_erase_key0;
	NVMIF->FLSKEY = flash_chip_erase_key1;
	
	erase_addr = (uint32_t*)0x00000000;
	//start erase
	*erase_addr = (uint32_t)0x00000000;
	
	//delay 10ms
	delay_50(200);
	
	NVMIF->FLSKEY = 0xBB006600;
}

void NVMIF_PROG_single_word(uint32_t* prog_addr,uint32_t prog_data)
{
	//set PREQ,clear EREQ
	NVMIF->EPCON &= ~NVMIF_EPCON_EREQ_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_PREQ_SET;
	
	//write flash key
	NVMIF->FLSKEY = flash_PROG_key0;
	NVMIF->FLSKEY = flash_PROG_key1;
	
	*prog_addr = prog_data;
	
	delay_50(1);
	
	NVMIF->FLSKEY = 0xBB006600;
}

void NVMIF_PROG_half_word(uint16_t* prog_addr,uint16_t prog_data)
{
	//set PREQ,clear EREQ
	NVMIF->EPCON &= ~NVMIF_EPCON_EREQ_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_PREQ_SET;
	
	//write flash key
	NVMIF->FLSKEY = flash_PROG_key0;
	NVMIF->FLSKEY = flash_PROG_key1;
	
	*prog_addr = prog_data;
	
	delay_50(1);
	
//	NVMIF->FLSKEY = 0xBB006600;
}

void NVMIF_PROG_single_byte(uint8_t* prog_addr,uint8_t prog_data)
{
	//set PREQ,clear EREQ
	NVMIF->EPCON &= ~NVMIF_EPCON_EREQ_Msk;
	NVMIF->EPCON |= NVMIF_EPCON_PREQ_SET;
	
	//write flash key
	NVMIF->FLSKEY = flash_PROG_key0;
	NVMIF->FLSKEY = flash_PROG_key1;
	
	*prog_addr = prog_data;
	
	delay_50(1);
	
	NVMIF->FLSKEY = 0xBB006600;
}

/******END OF FILE****/






