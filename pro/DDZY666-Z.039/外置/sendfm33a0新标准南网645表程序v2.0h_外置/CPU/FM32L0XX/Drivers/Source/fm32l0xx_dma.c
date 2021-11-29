/**
  ******************************************************************************
  * @file    fm32l0xx_dma.c
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

/** @defgroup DMA 
  * @brief DMA driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//static __I uint8_t APBAHBPrescTable[16] = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup DMA_Private_Functions
  * @{
  */ 


/** 
 *  reset DMA register to initial state
 *
 */
void DMA_Globle_Disable(void)
{
	DMA->GLOBALCTRL &= ~DMA_GLOBALCTRL_DMAEN_Msk;
	
}

void DMA_Globle_Ensable(void)
{
	DMA->GLOBALCTRL |= DMA_GLOBALCTRL_DMAEN_Msk;
	
}

void DMA_Init(DMA_InitType* DMA_InitStruct)
{
	RCC_PERIPH_clk_enable(DMA_num);
	
	switch(DMA_InitStruct->CHANNEL_num)
	{
		case DmaChannel_0:
			//size
			DMA->CH0CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH0CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH0CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH0CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH0CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH0CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH0CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH0CTRL |= DMA_InitStruct->CHselect;
			
			//ram addr
			DMA->CH0RAMAD = DMA_InitStruct->Ram_Addr;
		
		break;
		
		case DmaChannel_1:
			//size
			DMA->CH1CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH1CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH1CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH1CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH1CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH1CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH1CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH1CTRL |= DMA_InitStruct->CHselect;
		
			//ram addr
			DMA->CH1RAMAD = DMA_InitStruct->Ram_Addr;
		break;
		
		case DmaChannel_2:
			//size
			DMA->CH2CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH2CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH2CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH2CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH2CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH2CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH2CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH2CTRL |= DMA_InitStruct->CHselect;	
		
			//ram addr
			DMA->CH2RAMAD = DMA_InitStruct->Ram_Addr;
		break;
				
		case DmaChannel_3:
			//size
			DMA->CH3CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH3CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH3CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH3CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH3CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH3CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH3CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH3CTRL |= DMA_InitStruct->CHselect;

			//ram addr
			DMA->CH3RAMAD = DMA_InitStruct->Ram_Addr;
		break;
				
		case DmaChannel_4:
			//size
			DMA->CH4CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH4CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH4CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH4CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH4CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH4CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH4CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH4CTRL |= DMA_InitStruct->CHselect;	
		
			//ram addr
			DMA->CH4RAMAD = DMA_InitStruct->Ram_Addr;
		break;
				
		case DmaChannel_5:
			//size
			DMA->CH5CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH5CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH5CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH5CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH5CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH5CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH5CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH5CTRL |= DMA_InitStruct->CHselect;	
		
			//ram addr
			DMA->CH5RAMAD = DMA_InitStruct->Ram_Addr;
		break;
		
		case DmaChannel_6:
			//size
			DMA->CH6CTRL &= ~DMA_CHxCTRL_CHxTSIZE_Msk;
			DMA->CH6CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CHxCTRL_CHxTSIZE_Pos;
		
			//priority
			DMA->CH6CTRL &= ~DMA_CHxCTRL_CHxPRI_Msk;
			DMA->CH6CTRL |= DMA_InitStruct->CHPriority;
		
			//increase or decrease
			DMA->CH6CTRL &= ~DMA_CHxCTRL_CHxINC_Msk;
			DMA->CH6CTRL |= DMA_InitStruct->ram_addrincrease;
		
			// periph channel select
			DMA->CH6CTRL &= ~DMA_CHxCTRL_CHxSSEL_Msk;
			DMA->CH6CTRL |= DMA_InitStruct->CHselect;	
		
			//ram addr
			DMA->CH6RAMAD = DMA_InitStruct->Ram_Addr;
		break;
		
		case DmaChannel_7:
			//size
			DMA->CH7CTRL &= ~DMA_CH7CTRL_CH7TSIZE_Msk;
			DMA->CH7CTRL |= (DMA_InitStruct->Trans_Sizes)<<DMA_CH7CTRL_CH7TSIZE_Pos;
		
			//priority
			DMA->CH7CTRL &= ~DMA_CH7CTRL_CH7PRI_Msk;
			DMA->CH7CTRL |= DMA_InitStruct->CHPriority;
		
			//ram increase or decrease
			DMA->CH7CTRL &= ~DMA_CH7CTRL_CH7RI_Msk;
			DMA->CH7CTRL |= DMA_InitStruct->ram_addrincrease;
		
			//flash increase or decrease
			DMA->CH7CTRL &= ~DMA_CH7CTRL_CH7FI_Msk;
			DMA->CH7CTRL |= DMA_InitStruct->flash_addrincrease;
		
			// periph channel select
			DMA->CH7CTRL &= ~DMA_CH7CTRL_CH7DIR_Msk;
			DMA->CH7CTRL |= DMA_InitStruct->CHselect;	
		
			//ram addr
			DMA->CH7RAMAD = (DMA_InitStruct->Ram_Addr & 0x00003FFF)>>2;
			//flash addr
			DMA->CH7FLSAD = (DMA_InitStruct->Flash_Addr & 0x0001FFFF)>>2;
			
		break;
	
	}
}

void DMA_Channel_Enable(DmaChannel DMA_num,uint32_t NewSet)
{
	switch(DMA_num)
	{
		case DmaChannel_0:
			DMA->CH0CTRL |= NewSet;		
		break;
		
		case DmaChannel_1:
			DMA->CH1CTRL |= NewSet;
		break;
		
		case DmaChannel_2:
			DMA->CH2CTRL |= NewSet;
		break;
				
		case DmaChannel_3:
			DMA->CH3CTRL |= NewSet;
		break;
				
		case DmaChannel_4:
			DMA->CH4CTRL |= NewSet;
		break;
				
		case DmaChannel_5:
			DMA->CH5CTRL |= NewSet;
		break;
		
		case DmaChannel_6:
			DMA->CH6CTRL |= NewSet;
		break;
		
		case DmaChannel_7:
			DMA->CH7CTRL |= NewSet;			
		break;
	
	}
}

void DMA_Channel_Disable(DmaChannel DMA_num,uint32_t NewSet)
{
	switch(DMA_num)
	{
		case DmaChannel_0:
			DMA->CH0CTRL &= ~NewSet;		
		break;
		
		case DmaChannel_1:
			DMA->CH1CTRL &= ~NewSet;
		break;
		
		case DmaChannel_2:
			DMA->CH2CTRL &= ~NewSet;
		break;
				
		case DmaChannel_3:
			DMA->CH3CTRL &= ~NewSet;
		break;
				
		case DmaChannel_4:
			DMA->CH4CTRL &= ~NewSet;
		break;
				
		case DmaChannel_5:
			DMA->CH5CTRL &= ~NewSet;
		break;
		
		case DmaChannel_6:
			DMA->CH6CTRL &= ~NewSet;
		break;
		
		case DmaChannel_7:
			DMA->CH7CTRL &= ~NewSet;			
		break;
	
	}
}


ITStatus DMA_GetITStatus(uint32_t DMA_IT)
{
	ITStatus bitstatus = RESET;
	
	if((DMA->CHSTATUS & DMA_IT) != (uint32_t)RESET)
	{
			bitstatus = SET;
	}
	else
	{
		  bitstatus = RESET;
	}	

	/* Return the DMA_IT status */
  return  bitstatus;
	
}

void DMA_ClrITStatus(uint32_t DMA_IT)
{
	DMA->CHSTATUS |= DMA_IT;	
}

/** 
 *  translate data from flash to ram (for test)
 *
 */

void DMA_TRANS_FLASH_TO_RAM(uint32_t flash_addr,uint32_t ram_addr,uint32_t len)
{
	DMA_InitType DMA_InitStructure;
	
//from flash to ram
	DMA_InitStructure.CHANNEL_num = DmaChannel_7;
	DMA_InitStructure.Trans_Sizes = len;
	DMA_InitStructure.Ram_Addr = ram_addr;
	DMA_InitStructure.Flash_Addr = flash_addr;
	DMA_InitStructure.CHPriority = DMA_CH7CTRL_CH7PRI_VeryHigh;
	DMA_InitStructure.CHselect = DMA_CH7CTRL_CH7DIR_Flash2Ram;
	DMA_InitStructure.ram_addrincrease = DMA_CH7CTRL_CH7RI_Inc;
	DMA_InitStructure.flash_addrincrease = DMA_CH7CTRL_CH7FI_Inc;
	
	DMA_Init(&DMA_InitStructure);
	
	DMA_Channel_Enable(DmaChannel_7,DMA_CHxCTRL_CHxEN_Enable);
	DMA_Globle_Ensable();

}
/******END OF FILE****/



