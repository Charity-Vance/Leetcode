/**
  ******************************************************************************
  * @file    fm32l0xx_anac.c
  * @author  FM385 Application Team
  * @version V1.0.0
  * @date    8-march-2017
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of....:
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h" 


/** @addtogroup fm385_StdPeriph_Driver
  * @{
  */

/** @defgroup ANAC 
  * @brief ANAC driver modules
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup ANAC_Private_Functions
  * @{
  */ 
	
/** @defgroup PDR_Private_Functions
  * @{
  */

/**  PDR_Enable
  * 
  */
void PDR_Enable(void)
{
	ANAC->PDRCON |= ANAC_PDRCFG_PDREN_ENABLE;
}

/**  PDR_Disable
  * 
  */
void PDR_Disable(void)
{
	ANAC->PDRCON &= ~ANAC_PDRCFG_PDREN_ENABLE;
}

/**  PDR_Config
  * 
  */
void PDR_Config(uint32_t cfg_data)
{
	ANAC->PDRCON &= ~ANAC_PDRCFG_PDRCFG_Msk;
	ANAC->PDRCON |= cfg_data;
}

/** PDR_GetConfig
  * 
  */
uint32_t PDR_GetConfig(void)
{
	uint32_t  cfg_data;

	cfg_data = ANAC->PDRCON;
	return cfg_data;
}


/** @defgroup BOR_Private_Functions
  * @{
  */

/** BOR_Enable
  * 
  */
void BOR_Enable(void)
{
	ANAC->BORCON &= ~ANAC_BORCFG_OFF_BOR_ENABLE;
}

/** BOR_Disable
  * 
  */
void BOR_Disable(void)
{
	ANAC->BORCON |= ANAC_BORCFG_OFF_BOR_ENABLE;
}

/** BOR_PDRConfig
  * 
  */
void BOR_PDRConfig(uint32_t cfg_data)
{
	ANAC->BORCON &= ~ANAC_BORCFG_BOR_PDRCFG_Msk;
	ANAC->BORCON |= cfg_data;
}

/** BOR_GetConfig
  * 
  */
uint32_t BOR_GetConfig(void)
{
	uint32_t  cfg_data;

	cfg_data = ANAC->BORCON;
	return cfg_data;
}

/** @defgroup LDO15_Private_Functions
  * @{
  */
/** LDO15_GetTrimData
  * 
  */
uint32_t LDO15_GetTrimData(void)
{
	uint32_t  trim_data;

	trim_data = ANAC->LDO15CON;
	return trim_data;
}

/** @defgroup VREF_Private_Functions
  * @{
  */
/** VREF_GetTrimdata
  * 
  */
uint32_t VREF_GetTrimdata(void)
{
	uint32_t  trim_data;

	trim_data = ANAC->VREFTRIM;
	return trim_data;
}

/** @defgroup ULPLDO_Private_Functions
  * @{
  */
/** ULPLDO_GetRHVTrimdata
  * 
  */
uint32_t ULPLDO_GetRHVTrimdata(void)
{
	uint32_t  trim_data;

	trim_data = ANAC->ULPRCON;
	return trim_data;
}

/** ULPLDO_GetRLVTrimdata
  * 
  */
uint32_t ULPLDO_GetRLVTrimdata(void)
{
	uint32_t  trim_data;

	trim_data = ANAC->ULPRCON;
	return trim_data;
}

/** @defgroup SVD_Private_Functions
  * @{
  */
/** SVD_Init
  * 
  */
void SVD_Init(SVD_InitType* SVD_InitStruct)
{
	uint32_t tmpreg = 0;
	
	tmpreg = ANAC->SVDCFG;
	
	tmpreg &= ~(ANAC_SVDCFG_SVDLVL_Msk|ANAC_SVDCFG_DFEN_Msk|\
							ANAC_SVDCFG_SVDMOD_Msk|ANAC_SVDCFG_SVDITVL_Msk);
	
	tmpreg |= SVD_InitStruct->MODE|SVD_InitStruct->Interval|
						SVD_InitStruct->DFEN|SVD_InitStruct->LEVEL;
	
	ANAC->SVDCFG = tmpreg;

}

/** SVD_Enable
  * 
  */
void SVD_Enable(void)
{
	ANAC->SVDCON |=ANAC_SVDCON_SVDEN_ENABLE;
}

/** SVD_Disable
  * 
  */
void SVD_Disable(void)
{
	ANAC->SVDCON &= ~ANAC_SVDCON_SVDEN_ENABLE;
}

/** SVD_ITEnable
  * 
  */
void SVD_ITEnable(uint16_t EnableBit)
{
	ANAC->SVDCFG |= EnableBit;
}

/** SVD_ITEnable
  * 
  */
void SVD_ITDisable(uint16_t DisableBit)
{
	ANAC->SVDCFG &= ~DisableBit;
}

/** SVD_GetFlagSta
  * 
  */
ITStatus SVD_GetFlagSta(uint16_t FlagBit)
{
	ITStatus bitstatus = RESET;  
	if ((ANAC->SVDSIF & FlagBit)== RESET)
	{
			bitstatus = RESET;
	}
	else
	{
			bitstatus = SET;
	}
	return bitstatus; 

}

/** SVD_ClrITStatus
  * 
  */
void SVD_ClrITStatus(uint16_t FlagBit)
{
	ANAC->SVDSIF |= FlagBit;
}

/** @defgroup FDET_Private_Functions
  * @{
  */
/** FDET_ITEnable
  * 
  */
void FDET_ITEnable(void)
{
	ANAC->FDETIE |= ANAC_FDETIE_LFDET_IE_ENABLE;
}

/** FDET_ITEnable
  * 
  */
void FDET_ITDisable(void)
{
	ANAC->FDETIE &= ~ANAC_FDETIE_LFDET_IE_ENABLE;
}

/** FDET_GetFlagSta
  * 
  */
ITStatus FDET_GetFlagSta(void)
{
	ITStatus bitstatus = RESET;  
	if ((ANAC->FDETIF & ANAC_FDETIF_LFDET_IF_ENABLE)== RESET)
	{
			bitstatus = RESET;
	}
	else
	{
			bitstatus = SET;
	}
	return bitstatus; 

}

/** FDET_ClrITStatus
  * 
  */
void FDET_ClrITStatus(void)
{
	ANAC->FDETIF |= ANAC_FDETIF_LFDET_IF_ENABLE;
}

/** @defgroup BUF4TST_Private_Functions
  * @{
  */
/** BUF4TST_Enable
  * 
  */
void BUF4TST_Enable(void)
{
	ANAC->ANATESTSEL |= ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;

}

/** BUF4TST_Disable
  * 
  */
void BUF4TST_Disable(void)
{
	ANAC->ANATESTSEL &= ~ANAC_ANATESTSEL_BUF4TST_EN_ENABLE;

}

/** BUF4TST_BypassEn
  * 
  */
void BUF4TST_BypassEn(void)
{
	ANAC->ANATESTSEL |= ANAC_ANATESTSEL_BUF4TST_BYPASS_ENABLE;

}

/** BUF4TST_BypassDisable
  * 
  */
void BUF4TST_BypassDisable(void)
{
	ANAC->ANATESTSEL &= ~ANAC_ANATESTSEL_BUF4TST_BYPASS_ENABLE;

}

/** BUF4TST_ChannelSel
  * 
  */
void BUF4TST_ChannelSel(uint32_t ChannelNUM)
{
	ANAC->ANATESTSEL &= ~ANAC_ANATESTSEL_BUF4TST_SEL_Msk;
	ANAC->ANATESTSEL |= ChannelNUM;

}

/** @defgroup ADC_Private_Functions
  * @{
  */
/** ADC_Enable
  * 
  */
void ADC_Enable(void)
{
	ANAC->ADCCON |= ANAC_ADCCON_ADC_EN_ENABLE;

}

/** ADC_Disable
  * 
  */
void ADC_Disable(void)
{
	ANAC->ADCCON &= ~ANAC_ADCCON_ADC_EN_ENABLE;

}

/** ADC_ITEnable
  * 
  */
void ADC_ITEnable(void)
{
	ANAC->ADCCON |= ANAC_ADCCON_ADC_IE_ENABLE;
}

/** ADC_ITEnable
  * 
  */
void ADC_ITDisable(void)
{
	ANAC->ADCCON &= ~ANAC_ADCCON_ADC_IE_ENABLE;
}

/** ADC_GetFlagSta
  * 
  */
ITStatus ADC_GetFlagSta(void)
{
	ITStatus bitstatus = RESET;  
	if ((ANAC->ADCIF & ANAC_ADCIF_ADC_IF_SET)== RESET)
	{
			bitstatus = RESET;
	}
	else
	{
			bitstatus = SET;
	}
	return bitstatus; 

}

/** ADC_ClrITStatus
  * 
  */
void ADC_ClrITStatus(void)
{
	ANAC->ADCIF |= ANAC_ADCIF_ADC_IF_SET;
}

/** ADC_SetTrim
  * 
  */
void ADC_SetTrim(uint32_t TrimData)
{
	ANAC->ADCTRIM = TrimData;
}

/** ADC_GetData
  * 
  */
uint32_t ADC_GetData(void)
{
	return ANAC->ADCDATA;
}

/** ADC_ChannelSel
  * 
  */
void ADC_ChannelSel(uint32_t channelsel)
{
	ANAC->ADCCON &= ~ANAC_ADCCON_ADC_VANA_EN_Msk;
	ANAC->ADCCON |= channelsel;
}

/** @defgroup TNG_Private_Functions
  * @{
  */
/** TNG_Enable
  * 
  */
void TNG_Enable(void)
{
	ANAC->TRNGEN |= ANAC_TRNGEN_trng_en_ENABLE;

}

/** TNG_Disable
  * 
  */
void TNG_Disable(void)
{
	ANAC->TRNGEN &= ~ANAC_TRNGEN_trng_en_ENABLE;

}

/** @defgroup CMP_Private_Functions
  * @{
  */
/** CMP_Enable
  * 
  */
void CMP_Enable(uint32_t CmpNum)
{
	if(CmpNum == CMP1_num )
	{	
		ANAC->COMP1CR |= ANAC_COMP1CR_CMP1EN_ENABLE;
	}
	else
	{
		ANAC->COMP2CR |= ANAC_COMP2CR_CMP2EN_ENABLE;
	}

}

/** CMP_Disable
  * 
  */
void CMP_Disable(uint32_t CmpNum)
{
		if(CmpNum == CMP1_num )
	{	
		ANAC->COMP1CR &= ~ANAC_COMP1CR_CMP1EN_ENABLE;
	}
	else
	{
		ANAC->COMP2CR &= ~ANAC_COMP2CR_CMP2EN_ENABLE;
	}

}

/** CMP_Init
  * 
  */
void CMP_Init(uint32_t CmpNum,uint32_t PSELNum,uint32_t NSELNum)
{
	uint32_t temp_reg = 0;
	
	if(CmpNum == CMP1_num )
	{	
		temp_reg = ANAC->COMP1CR;
		temp_reg &= ~ANAC_COMP1CR_V1NSEL_Msk;
		temp_reg &= ~ANAC_COMP1CR_V1PSEL_Msk;
		temp_reg |= PSELNum | NSELNum;
		ANAC->COMP1CR = temp_reg;
	}
	else
	{
		temp_reg = ANAC->COMP2CR;
		temp_reg &= ~ANAC_COMP2CR_V2NSEL_Msk;
		temp_reg &= ~ANAC_COMP2CR_V2PSEL_Msk;
		temp_reg |= PSELNum | NSELNum;
		ANAC->COMP2CR = temp_reg;
	}

}


/** CMP_ITEnable
  * 
  */
void CMP_ITEnable(uint32_t CmpNum)
{
	if(CmpNum == CMP1_num )
	{
		ANAC->COMPICR |= ANAC_COMPICR_CMP1IE_ENABLE;
	}
	else
	{
		ANAC->COMPICR |= ANAC_COMPICR_CMP2IE_ENABLE;
	}
}

/** CMP_ITDisable
  * 
  */
void CMP_ITDisable(uint32_t CmpNum)
{
	if(CmpNum == CMP1_num )
	{
		ANAC->COMPICR &= ~ANAC_COMPICR_CMP1IE_ENABLE;
	}
	else
	{
		ANAC->COMPICR &= ~ANAC_COMPICR_CMP2IE_ENABLE;
	}
}

/** CMP_GetFlagSta
  * 
  */
ITStatus CMP_GetFlagSta(uint32_t CmpNum)
{
	ITStatus bitstatus = RESET; 
	if(CmpNum == CMP1_num )
	{
		if ((ANAC->COMPIF & ANAC_COMPIF_CMP1IF_SET)== RESET)
		{
			bitstatus = RESET;
		}
		else
		{
			bitstatus = SET;
		}
	}
	else
	{
		if ((ANAC->COMPIF & ANAC_COMPIF_CMP2IF_SET)== RESET)
		{
			bitstatus = RESET;
		}
		else
		{
			bitstatus = SET;
		}
	
	}
	return bitstatus; 

}

/** CMP_ClrITStatus
  * 
  */
void CMP_ClrITStatus(uint32_t CmpNum)
{
	if(CmpNum == CMP1_num )
	{
		ANAC->COMPIF |= ANAC_COMPIF_CMP1IF_SET;
	}
	else
	{
		ANAC->COMPIF |= ANAC_COMPIF_CMP2IF_SET;
	}

}

/** CMP_GetOutSta
  * 
  */
ITStatus CMP_GetOutSta(uint32_t CmpNum)
{
	ITStatus bitstatus = RESET; 
	if(CmpNum == CMP1_num )
	{
		if ((ANAC->COMP1CR & ANAC_COMP1CR_CMP1O_Msk)== RESET)
		{
			bitstatus = RESET;
		}
		else
		{
			bitstatus = SET;
		}
	}
	else
	{
		if ((ANAC->COMP2CR & ANAC_COMP2CR_CMP2O_Msk)== RESET)
		{
			bitstatus = RESET;
		}
		else
		{
			bitstatus = SET;
		}
	
	}
	return bitstatus; 
}

/** CMP_ISSel
  * 
  */
void CMP_ISSel(uint32_t CmpNum,uint32_t SelNum)
{

	if(CmpNum == CMP1_num )
	{
		ANAC->COMPICR &= ~ANAC_COMPICR_CMP1SEL_Msk;		
	}
	else
	{
		ANAC->COMPICR &= ~ANAC_COMPICR_CMP2SEL_Msk;	
	}
	
	ANAC->COMPICR |= SelNum;
}


/******END OF FILE****/



