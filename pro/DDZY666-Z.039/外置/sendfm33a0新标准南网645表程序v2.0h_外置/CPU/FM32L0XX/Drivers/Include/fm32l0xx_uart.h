/**
******************************************************************************
* @file    fm32l0xx_uart.h
* @author  
* @version V0.0.1
* @date    04-Dec-2016
* @brief   This file contains all the functions prototypes for the UART firmware     
******************************************************************************
*/ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FM32L0xx_UART_H
#define __FM32L0xx_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "FM32L0XX.h"
	 
/** @addtogroup FM32L0xx_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */ 

/* Exported types ------------------------------------------------------------*/ 

/** 
  * @brief  USART type definition  
  */ 
 
/** 
  * @brief  USART Init Structure definition  
  */ 
  
typedef struct
{
  uint32_t UART_BaudRate;            /*!< This member configures the USART communication baud rate. */

  uint16_t UART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref USART_Word_Length */

  uint16_t UART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref USART_Stop_Bits */

  uint16_t UART_Mode_TX;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref USART_Mode */
										   	
  uint16_t UART_Mode_RX;

} UART_InitType;


/* UART_IE_definition */

#define UART_RX_IE5                         ((uint32_t)0x00000800)
#define UART_TX_IE5                         ((uint32_t)0x00000400)
#define UART_RX_IE4                         ((uint32_t)0x00000200)
#define UART_TX_IE4                        	((uint32_t)0x00000100)
#define UART_RX_IE3                      		((uint32_t)0x00000080)
#define UART_TX_IE3                        	((uint32_t)0x00000040)
#define UART_RX_IE2                         ((uint32_t)0x00000020)
#define UART_TX_IE2                         ((uint32_t)0x00000010)
#define UART_RX_IE1                         ((uint32_t)0x00000008)
#define UART_TX_IE1                      		((uint32_t)0x00000004) 
#define UART_RX_IE0                         ((uint32_t)0x00000002)
#define UART_TX_IE0                         ((uint32_t)0x00000001)

/* UART_IF_definition */
#define UART_RX_IF5                         ((uint32_t)0x00000800)
#define UART_TX_IF5                         ((uint32_t)0x00000400)
#define UART_RX_IF4                         ((uint32_t)0x00000200)
#define UART_TX_IF4                        	((uint32_t)0x00000100)
#define UART_RX_IF3                      		((uint32_t)0x00000080)
#define UART_TX_IF3                        	((uint32_t)0x00000040)
#define UART_RX_IF2                         ((uint32_t)0x00000020)
#define UART_TX_IF2                         ((uint32_t)0x00000010)
#define UART_RX_IF1                         ((uint32_t)0x00000008)
#define UART_TX_IF1                      		((uint32_t)0x00000004) 
#define UART_RX_IF0                         ((uint32_t)0x00000002)
#define UART_TX_IF0                         ((uint32_t)0x00000001)

/* UART_infrared control_definition */

#define UART_TZBRG_irflag_Pos							15
#define UART_TZBRG_irflag_Msk							((uint32_t)0x00008000)
#define UART_TZBRG_irflag_0								((uint32_t)0x00000000)	
#define UART_TZBRG_irflag_1								((uint32_t)0x00008000)

#define UART_TZBRG_th_Pos								11
#define UART_TZBRG_th_Msk								((uint32_t)0x00007800)

#define UART_TZBRG_tzbrg_Pos							0
#define UART_TZBRG_tzbrg_Msk							((uint32_t)0x000007FF)

/*RXSTAx*/
#define UART_RXSTA_pdsel_Pos							6
#define UART_RXSTA_pdsel_Msk							((uint32_t)0x000000C0)
#define UART_RXSTA_pdsel_8_none						((uint32_t)0x00000000)
#define UART_RXSTA_pdsel_8_even						((uint32_t)0x00000040)
#define UART_RXSTA_pdsel_8_odd							((uint32_t)0x00000080)
#define UART_RXSTA_pdsel_9_none						((uint32_t)0x000000C0)

#define UART_RXSTA_errie								((uint32_t)0x00000020)

#define UART_RXSTA_rxen_Pos							4
#define UART_RXSTA_rxen_Msk 							((uint32_t)0x00000010)
#define UART_RXSTA_rxen_enable							((uint32_t)0x00000010)
#define UART_RXSTA_rxen_disable						((uint32_t)0x00000000)


#define UART_RXSTA_perr 								((uint32_t)0x00000008)
#define UART_RXSTA_ferr 								((uint32_t)0x00000004)
#define UART_RXSTA_oerr 								((uint32_t)0x00000002)
#define UART_RXSTA_rx9d 								((uint32_t)0x00000001)
	 
/*TXSTAx*/
#define UART_TXSTA_stopsel_Pos 							6	
#define UART_TXSTA_stopsel_Msk							((uint32_t)0x00000040)	
#define UART_TXSTA_stopsel_1  							((uint32_t)0x00000000)	
#define UART_TXSTA_stopsel_2  							((uint32_t)0x00000040)

#define UART_TXSTA_txis_Pos 							5
#define UART_TXSTA_txis_Msk							((uint32_t)0x00000020)
#define UART_TXSTA_txis_txbuf_empty 					((uint32_t)0x00000000)
#define UART_TXSTA_txis_shifbuf_empty  					((uint32_t)0x00000020)

#define UART_TXSTA_txen_Pos 							4
#define UART_TXSTA_txen_Msk							((uint32_t)0x00000010)
#define UART_TXSTA_txen_disable							((uint32_t)0x00000000)
#define UART_TXSTA_txen_enable 						((uint32_t)0x00000010)

#define UART_TXSTA_iren_Pos 							3
#define UART_TXSTA_iren_Msk 							((uint32_t)0x00000008)
#define UART_TXSTA_iren_disable							((uint32_t)0x00000000)
#define UART_TXSTA_iren_enable  						((uint32_t)0x00000008)

#define UART_TXSTA_tsrf 									((uint32_t)0x00000002)
#define UART_TXSTA_tx9d								((uint32_t)0x00000001)

/*TXFIFOSTAx*/
#define UART_TXFIFOSTA_intsel_Pos   							2
#define UART_TXFIFOSTA_intsel_Msk   							((uint32_t)0x0000000C)	
#define UART_TXFIFOSTA_intsel_none						((uint32_t)0x0000000C)	
#define UART_TXFIFOSTA_intsel_txbuf						((uint32_t)0x00000008)	
#define UART_TXFIFOSTA_intsel_allbuf						((uint32_t)0x00000004)	
#define UART_TXFIFOSTA_intsel_shiftbuf   					((uint32_t)0x00000000)	

#define UART_TXFIFOSTA_txff  									((uint32_t)0x00000001)

/*RXFIFOSTAx*/
#define UART_RXFIFOSTA_REV  								((uint32_t)0x00000070)	

#define UART_RXFIFOSTA_intsel_Pos							2
#define UART_RXFIFOSTA_intsel_Msk							((uint32_t)0x00000004)
#define UART_RXFIFOSTA_intsel_rxbuf							((uint32_t)0x00000004)
#define UART_RXFIFOSTA_intsel_shiftbuf						((uint32_t)0x00000000)

#define UART_RXFIFOSTA_rxff 								((uint32_t)0x00000001)

/*RTXCONx*/
#define UART_RTXCON_rtx7en  								((uint32_t)0x00000004)	
#define UART_RTXCON_rxdflag									((uint32_t)0x00000002)
#define UART_RTXCON_txdflag									((uint32_t)0x00000001)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/ 

extern void UART_Init(Uartx_Type* UARTx, UART_InitType* UART_InitStruct);
extern void UART_SendData(Uartx_Type* UARTx, uint32_t Data);
extern uint32_t UART_ReceiveData(Uartx_Type* UARTx);
extern FlagStatus UART_GetFlagStatus(Uartx_Type* UARTx);
extern FlagStatus UART_GetINTStatus(uint32_t IF_addr);
//extern void UART_ClrINTStatus(uint32_t IF_addr);
extern void UartSendInfo(Uartx_Type* UARTx,uint32_t len, uint32_t *ptr);
extern void Uart_IE_Enable(uint32_t IEbit);
extern void Uart_IE_Disable(uint32_t IEbit);
#ifdef __cplusplus
}
#endif

#endif /* __FM32L0xx_UART_H */

