#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h" 
#include <string.h>
#include "Cpu_card.h"


//校验寄存器
unsigned char CheckSysReg( __IO uint32_t *RegAddr, uint32 Value )
{
	if( *RegAddr != Value ) 
	{
		*RegAddr = Value;
		return 1;
	}
	else
	{
		return 0;
	}
}

//查询NVIC寄存器对应向量号中断是否打开
//1 打开
//0 关闭
unsigned char CheckNvicIrqEn( IRQn_Type IRQn )
{
	if( 0 == ( NVIC->ISER[0U] & ((uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL)))) )
		return 0;
	else
		return 1;
}

//模拟功能配置:LCD/ADC
void AnalogIO( GPIOx_Type* GPIOx, uint32 PinNum )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructureRun;
	
	GPIO_Get_InitParam(GPIOx, PinNum, &GPIO_InitStructureRun);
	
	if( (GPIO_InitStructureRun.GPIO_Pin		!= PinNum) ||
		(GPIO_InitStructureRun.GPIO_In		!= GPIO_In_DIS) ||
		(GPIO_InitStructureRun.GPIO_OType	!= GPIO_OType_OD) ||
		(GPIO_InitStructureRun.GPIO_Pu		!= GPIO_PuPd_NOPULL) ||
		(GPIO_InitStructureRun.GPIO_Mode	!= GPIO_Mode_ANA) )
	{
		GPIO_InitStructure.GPIO_Pin = PinNum;
		GPIO_InitStructure.GPIO_In = GPIO_In_DIS;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Pu = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_ANA;
		
		GPIO_Init(GPIOx, &GPIO_InitStructure);		
	}	
}

//输入IO口配置 type 0 = 普通 type 1 = 上拉
void InputtIO( GPIOx_Type* GPIOx, uint32 PinNum, uint08 Type )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructureRun;
	
	GPIO_Get_InitParam(GPIOx, PinNum, &GPIO_InitStructureRun);
		
	if( (GPIO_InitStructureRun.GPIO_Pin		!= PinNum) ||
		(GPIO_InitStructureRun.GPIO_In		!= GPIO_In_EN) ||
		(GPIO_InitStructureRun.GPIO_OType	!= GPIO_OType_OD) ||
		((Type == 0)&&(GPIO_InitStructureRun.GPIO_Pu != GPIO_PuPd_NOPULL)) ||
		((Type == 1)&&(GPIO_InitStructureRun.GPIO_Pu != GPIO_PuPd_UP)) ||
		(GPIO_InitStructureRun.GPIO_Mode	!= GPIO_Mode_IN) )
	{
		GPIO_InitStructure.GPIO_Pin = PinNum;	
		GPIO_InitStructure.GPIO_In = GPIO_In_EN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		if( Type == 0 )		GPIO_InitStructure.GPIO_Pu = GPIO_PuPd_NOPULL;
		else				GPIO_InitStructure.GPIO_Pu = GPIO_PuPd_UP;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		
		GPIO_Init(GPIOx, &GPIO_InitStructure);	
	}	
}

//输出IO口配置 type 0 = 普通 type 1 = OD
void OutputIO( GPIOx_Type* GPIOx, uint32 PinNum, uint08 Type )
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructureRun;
	
	GPIO_Get_InitParam(GPIOx, PinNum, &GPIO_InitStructureRun);
	
	if( (GPIO_InitStructureRun.GPIO_Pin		!= PinNum) ||
		(GPIO_InitStructureRun.GPIO_In		!= GPIO_In_DIS) ||
		((Type == 0)&&(GPIO_InitStructureRun.GPIO_OType	!= GPIO_OType_PP)) ||
		((Type == 1)&&(GPIO_InitStructureRun.GPIO_OType	!= GPIO_OType_OD)) ||
		(GPIO_InitStructureRun.GPIO_Pu		!= GPIO_PuPd_NOPULL) ||
		(GPIO_InitStructureRun.GPIO_Mode	!= GPIO_Mode_OUT) )
	{
		GPIO_InitStructure.GPIO_Pin = PinNum;
		GPIO_InitStructure.GPIO_In = GPIO_In_DIS;
		if( Type == 0 )		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		else				GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Pu = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		 
		GPIO_Init(GPIOx, &GPIO_InitStructure);		
	}
}
//数字特殊功能口 
//type 0 = 普通 type 1 = OD (OD功能仅部分特殊功能支持)
//type 2 = 普通+上拉 type 3 = OD+上拉
void AltFunIO( GPIOx_Type* GPIOx, uint32 PinNum, uint08 Type  )
{																
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructureRun;
	
	GPIO_Get_InitParam(GPIOx, PinNum, &GPIO_InitStructureRun);
	
	if( (GPIO_InitStructureRun.GPIO_Pin		!= PinNum) ||
		(GPIO_InitStructureRun.GPIO_In		!= GPIO_In_DIS) ||
		(((Type & 0x01) == 0)&&(GPIO_InitStructureRun.GPIO_OType	!= GPIO_OType_PP)) ||
		(((Type & 0x01) != 0)&&(GPIO_InitStructureRun.GPIO_OType	!= GPIO_OType_OD)) ||
		(((Type & 0x02) == 0)&&(GPIO_InitStructureRun.GPIO_Pu		!= GPIO_PuPd_NOPULL)) ||
		(((Type & 0x02) != 0)&&(GPIO_InitStructureRun.GPIO_Pu		!= GPIO_PuPd_UP)) ||
		(GPIO_InitStructureRun.GPIO_Mode	!= GPIO_Mode_DIG) )
	{
		GPIO_InitStructure.GPIO_Pin = PinNum;
		GPIO_InitStructure.GPIO_In = GPIO_In_DIS;
		if( (Type & 0x01) == 0 )	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		else						GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		if( (Type & 0x02) == 0 )	GPIO_InitStructure.GPIO_Pu = GPIO_PuPd_NOPULL;
		else						GPIO_InitStructure.GPIO_Pu = GPIO_PuPd_UP;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_DIG;
		 
		GPIO_Init(GPIOx, &GPIO_InitStructure);		
	}
}
//关闭IO（od输出高）
//当输入使能有效时，如果外部信号浮空，也可能导致FM385管脚漏电；
//可以将FCR配置为01（GPIO输出），ODEN配置为1，即伪开漏输出，关闭上拉使能，并将输出数据设为1
//注意SWD接口的PG8,9如果程序改变它们的配置将无法仿真
void CloseeIO( GPIOx_Type* GPIOx, uint32 PinNum )
{
	OutputIO( GPIOx, PinNum, 1 );
	GPIO_SetBits(GPIOx, PinNum);
}

void Close_None_GPIO(void)
{
	//关闭80脚芯片不可使用的IO
	CloseeIO( GPIOC, GPIO_Pin_0 );
	CloseeIO( GPIOC, GPIO_Pin_1 );

	CloseeIO( GPIOD, GPIO_Pin_8 );
	CloseeIO( GPIOD, GPIO_Pin_9 );
	CloseeIO( GPIOD, GPIO_Pin_10 );	
	CloseeIO( GPIOD, GPIO_Pin_11 );	
	CloseeIO( GPIOD, GPIO_Pin_12 );	
	CloseeIO( GPIOD, GPIO_Pin_13 );	
	CloseeIO( GPIOD, GPIO_Pin_14 );	
	CloseeIO( GPIOD, GPIO_Pin_15 );	


	CloseeIO( GPIOE, GPIO_Pin_0 );
	CloseeIO( GPIOE, GPIO_Pin_1 );

	CloseeIO( GPIOE, GPIO_Pin_6 );
	CloseeIO( GPIOE, GPIO_Pin_7 );
	CloseeIO( GPIOE, GPIO_Pin_8 );
	CloseeIO( GPIOE, GPIO_Pin_9 );
	CloseeIO( GPIOE, GPIO_Pin_10 );
	CloseeIO( GPIOE, GPIO_Pin_11 );
	CloseeIO( GPIOE, GPIO_Pin_12 );
	CloseeIO( GPIOE, GPIO_Pin_13 );
	CloseeIO( GPIOE, GPIO_Pin_14 );
	CloseeIO( GPIOE, GPIO_Pin_15 );

	CloseeIO( GPIOF, GPIO_Pin_0 );
	CloseeIO( GPIOF, GPIO_Pin_1 );
	CloseeIO( GPIOF, GPIO_Pin_2 );
	
	CloseeIO( GPIOF, GPIO_Pin_7 );
	CloseeIO( GPIOF, GPIO_Pin_8 );
	CloseeIO( GPIOF, GPIO_Pin_9 );
	CloseeIO( GPIOF, GPIO_Pin_10 );


	CloseeIO( GPIOG, GPIO_Pin_0 );
	CloseeIO( GPIOG, GPIO_Pin_1 );

	CloseeIO( GPIOG, GPIO_Pin_4 );
	CloseeIO( GPIOG, GPIO_Pin_5 );

	CloseeIO( GPIOG, GPIO_Pin_10 );
	CloseeIO( GPIOG, GPIO_Pin_11 );
	CloseeIO( GPIOG, GPIO_Pin_12 );
	CloseeIO( GPIOG, GPIO_Pin_13 );
	CloseeIO( GPIOG, GPIO_Pin_14 );
	CloseeIO( GPIOG, GPIO_Pin_15 );
}

void Veri_Pad( void )
{	
	CheckSysReg( &GPIO_common->EXTI0_SEL	, 0xFFFF0000 );
	CheckSysReg( &GPIO_common->EXTI1_SEL	, 0xFFFF0000 );
	CheckSysReg( &GPIO_common->EXTI2_SEL	, 0xFFFF0000 );
	CheckSysReg( &GPIO_common->HDSEL	, 0x00000001 );//PE2强驱动使能
	CheckSysReg( &GPIO_common->FOUTSEL	, GPIO_FOUTSEL_RTCTM );
	CheckSysReg( &GPIO_common->ANASEL	, 0x3F );	//模拟口液晶、AD功能选择	
	CheckSysReg( &GPIO_common->IOFIN	, BIT4|BIT1 );//打开脉冲输入口数字滤波功能
	CheckSysReg( &GPIO_common->PINWKEN	, 0 );
	
	AnalogIO( GPIOA, GPIO_Pin_0 );		//PA0; //COM0
	AnalogIO( GPIOA, GPIO_Pin_1 );		//PA1; //COM1
	AnalogIO( GPIOA, GPIO_Pin_2 );		//PA2; //COM2
	AnalogIO( GPIOA, GPIO_Pin_3 );		//PA3; //COM3
	AnalogIO( GPIOA, GPIO_Pin_4 );		//PA4; //COM4
	AnalogIO( GPIOA, GPIO_Pin_5 );		//PA5; //COM5
	AnalogIO( GPIOA, GPIO_Pin_6 );		//PA6;//SEG0
	AnalogIO( GPIOA, GPIO_Pin_7 );		//PA7;//SEG1
	AnalogIO( GPIOA, GPIO_Pin_8 );		//PA8;//SEG2
	AltFunIO( GPIOA, GPIO_Pin_9, 0 );	//PA9;//QF_CF
	AnalogIO( GPIOA, GPIO_Pin_10 );		//PA10;//SEG3
	AnalogIO( GPIOA, GPIO_Pin_11 );		//PA11;//SEG4
	AnalogIO( GPIOA, GPIO_Pin_12 );		//PA12;//SEG5
	AnalogIO( GPIOA, GPIO_Pin_13 );		//PA13;//SEG6
	AltFunIO( GPIOA, GPIO_Pin_14, 1 );	//PA14;//SCL
	AltFunIO( GPIOA, GPIO_Pin_15, 1 );	//PA15;//SDA

	AltFunIO( GPIOB, GPIO_Pin_0, 0 );	//PB0;//BLE-RXD
	AltFunIO( GPIOB, GPIO_Pin_1, 1 );	//PB1;//BLE-TXD(OD输出)
	AltFunIO( GPIOB, GPIO_Pin_2, 0 );	//PB2;//RX485, RXD2
	AltFunIO( GPIOB, GPIO_Pin_3, 0 );	//PB3;//TX485, TXD2
	AltFunIO( GPIOB, GPIO_Pin_4, 0 );	//PB4;//ACTIVEP
	InputtIO( GPIOB, GPIO_Pin_5, 0 );	//PB5;//TAIL
//	AltFunIO( GPIOB, GPIO_Pin_6, 0 );	//PB6;//PULSELED
	OutputIO( GPIOB, GPIO_Pin_7, 0 );	//PB7;//VBLE
	AnalogIO( GPIOB, GPIO_Pin_8  );		//PB8;//SEG7
	AnalogIO( GPIOB, GPIO_Pin_9  );		//PB9;//SEG8
	AnalogIO( GPIOB, GPIO_Pin_10 );		//PB10;//SEG9
	OutputIO( GPIOB, GPIO_Pin_11, 0 );//PB11;//RelayCtrl//EE_V@电池外置
	InputtIO( GPIOB, GPIO_Pin_12, 0 );//PB12;//RelayTest
	AnalogIO( GPIOB, GPIO_Pin_13 );		//PB13;//SEG10
	AnalogIO( GPIOB, GPIO_Pin_14 );		//PB14;//SEG11
	AnalogIO( GPIOB, GPIO_Pin_15 );		//PB15;//SEG12
	
	AnalogIO( GPIOC, GPIO_Pin_2 );		//PC2;//SEG13
	AnalogIO( GPIOC, GPIO_Pin_3 );		//PC3;//SEG14
	AltFunIO( GPIOC, GPIO_Pin_4, 0 );	//PC4;//RXHW, RXD5
	AltFunIO( GPIOC, GPIO_Pin_5, 0 );	//PC5;//TXHW, TXD5
	AnalogIO( GPIOC, GPIO_Pin_6 );		//PC6;//SEG15
	AnalogIO( GPIOC, GPIO_Pin_7 );		//PC7;//SEG16
	AnalogIO( GPIOC, GPIO_Pin_8 );		//PC8;//SEG17
	AnalogIO( GPIOC, GPIO_Pin_9 );		//PC9;//SEG18
	AnalogIO( GPIOC, GPIO_Pin_10 );		//PC10;//SEG19
	AnalogIO( GPIOC, GPIO_Pin_11 );		//PC11;//SEG20
	AnalogIO( GPIOC, GPIO_Pin_12 );		//PC12;//SEG21
	AnalogIO( GPIOC, GPIO_Pin_13 );		//PC13;//SEG22
	AnalogIO( GPIOC, GPIO_Pin_14 );		//PC14;//SEG23
	AnalogIO( GPIOC, GPIO_Pin_15 );		//PC15;//SEG24
	
	AltFunIO( GPIOD, GPIO_Pin_0, 0 );	//PD0;//METERIC_RX RXD4
	AltFunIO( GPIOD, GPIO_Pin_1, 0 );	//PD1;//METERIC_TX TXD4
	AnalogIO( GPIOD, GPIO_Pin_2 );		//PD2;//SEG25
	AnalogIO( GPIOD, GPIO_Pin_3 );		//PD3;//SEG26
	OutputIO( GPIOD, GPIO_Pin_4, 0 );	//PD4;//RelayOn, 继电器控制脚
	OutputIO( GPIOD, GPIO_Pin_5, 0 );	//PD5;//RelayOff,	继电器控制脚 
	InputtIO( GPIOD, GPIO_Pin_6, 1 );	//PD6;//DISPKEY,带上拉
	OutputIO( GPIOD, GPIO_Pin_7, 0 );	//PD7;//EsamVcc
	
	OutputIO( GPIOE, GPIO_Pin_2, 0 );	//PE2;//LCDLED 	
	OutputIO( GPIOE, GPIO_Pin_3, 0 );	//PE3;//485Ctrl
	OutputIO( GPIOE, GPIO_Pin_4, 0 );	//PE4;//VFLASH
	OutputIO( GPIOE, GPIO_Pin_5, 1 );	//PE5;//PLCEVT(OD输出)
	
	AltFunIO( GPIOF, GPIO_Pin_3, 0 );	//PF3;//RXZB RXD0 
	AltFunIO( GPIOF, GPIO_Pin_4, 1 );	//PF4;//TXZB TXD0 (OD输出)
	OutputIO( GPIOF, GPIO_Pin_5, 1 );	//PF5;//PLCRST(OD输出)
	AnalogIO( GPIOF, GPIO_Pin_6 );		//PF6;//VBATCHK
	if( ExtVoltage != 0x55 )
	{
		CloseeIO( GPIOF, GPIO_Pin_11 );	
	}
	else
	{
		AnalogIO( GPIOF, GPIO_Pin_11 );		//PF11;//SVS外部掉电检测
	}
//	OutputIO( GPIOF, GPIO_Pin_12, 0 );	//PF12;//F_CS		
//	AltFunIO( GPIOF, GPIO_Pin_13, 0 );	//PF13;//F_CLK		
//	AltFunIO( GPIOF, GPIO_Pin_14, 0 );	//PF14;//F_DI		
//	AltFunIO( GPIOF, GPIO_Pin_15, 0 );	//PF15;//F_DO	

	AltFunIO( GPIOG, GPIO_Pin_2, 0 );	//PG2;//ESAMCLK
	AltFunIO( GPIOG, GPIO_Pin_3, 0 );	//PG3;//ESAMIO
	if( (Outputtype ==0) || EA_OFF )
	{
		AltFunIO( GPIOG, GPIO_Pin_6, 0 );//PG6;//TM
	}
	else
	{
		OutputIO( GPIOG, GPIO_Pin_6, 0 );//PG6;//无功或时段输出
	}	
	OutputIO( GPIOG, GPIO_Pin_7, 0);		//PG7;//ESAMRST
	
	
	#ifdef __DEBUG
	AltFunIO( GPIOG, GPIO_Pin_8, 0 );	//PG8;//SWDTCK/LEDRelay
	AltFunIO( GPIOG, GPIO_Pin_9, 0 );	//PG9;//SWDTDO/COM_RQ	
	#else
	if(EA_OFF)
	{
		AltFunIO( GPIOG, GPIO_Pin_8, 0 );	//PG8;//SWDTCK/LEDRelay
		AltFunIO( GPIOG, GPIO_Pin_9, 0 );	//PG9;//SWDTDO/COM_RQ	
	}
	else
	{
		OutputIO( GPIOG, GPIO_Pin_8, 0 );	//PG8;//LEDRelay
		InputtIO( GPIOG, GPIO_Pin_9, 1 );	//PG9;//COM_RQ(内部上拉)
	}
	#endif
}

void MeterIC_RST0(void)
{
	METER_RST0;
	OutputIO( GPIOD, GPIO_Pin_1, 0 );
}

void MeterIC_RST1(void)
{
	METER_RST1;
	AltFunIO( GPIOD, GPIO_Pin_1, 0 );	//PF4;//TX485, TXD0
}

//#define DISABLEPULSE	
//#define ENABLEPULSE	
void Disable_Pulse(void)
{
//	CloseeIO(GPIOB, GPIO_Pin_6);	//PB6;//PULSELED
	InputtIO(GPIOB, GPIO_Pin_6, 1 );	//PB6;//PULSELED
	BTIMER1->BTxCR1 = 0; 
	BTIMER2->BTxCR1 = 0; 
}
void Enable_Pulse(void)
{	
	AltFunIO( GPIOB, GPIO_Pin_6, 0 ); //PB6;//PULSELED
	CheckSysReg( &BTIMER1->BTxCR1 , (BTIM_BTxCR1_CHEN_ENABLE|BTIM_BTxCR1_CLEN_ENABLE) ); 	
	CheckSysReg( &BTIMER2->BTxCR1 , (BTIM_BTxCR1_CHEN_ENABLE|BTIM_BTxCR1_CLEN_ENABLE) ); 	
}

void Disable_I2C_IO(void)
{
	CloseeIO( GPIOA, GPIO_Pin_14 );		//SCL
	CloseeIO( GPIOA, GPIO_Pin_15 );		//SDA
	EEVCCOFF;		//关闭EE电源	
}

void Enable_I2C_IO(void)
{
	OutputIO( GPIOB, GPIO_Pin_11, 0 );	//PB8;//RelayCtrl//EE_V@电池外置
	EEVCCON;	//打开EE电源	
	AltFunIO( GPIOA, GPIO_Pin_14, 1 );	//PA14;//SCL
	AltFunIO( GPIOA, GPIO_Pin_15, 1 );	//PA15;//SDA	
}

void Enable_Led_IO(void)
{
	#ifndef __DEBUG
	OutputIO( GPIOG, GPIO_Pin_8, 0 );	//PG8;//LEDRelay
	#endif
}

void Veri_Clk_Gen( void )				//时钟选择相关
{
	const uint32 set_SYSRCCSEL = (RCC_SYSRCCSEL_RCHF |
								RCC_SYSRCCSEL_AHBPRES_NONE |
								RCC_SYSRCCSEL_APBPRES_NONE |
								RCC_SYSRCCSEL_EXTICKSEL_AHBRCC |
								RCC_SYSRCCSEL_SLP_ENEXTI_LSRCC |
//								RCC_SYSRCCSEL_WKUPRCC_RCHF |
								RCC_SYSRCCSEL_WKUPRCC_RCLP |
								RCC_SYSRCCSEL_LPM_RCLP_OFF);
	
	const uint32 set_RCHFCON = (rchfcfgreg | 
								RCC_RCHFCON_RCHFEN_ON);
	
	const uint32 set_PLLCON = (RCC_PLLCON_PLLEN_ON |
								RCC_PLLCON_PLLINSEL_XTLF|
								0x01F30000);
								//IS_PLL_PLLDB(VALUE));
	
	const uint32 set_RCLPCON = (RCC_RCLPCON_RCLP_EN_B_ON);
		
	const uint32 set_PERRCCCON1 = (RCC_PERRCCCON1_LPTRCCEN_ON |
								RCC_PERRCCCON1_LPTFCCEN_ON |
								RCC_PERRCCCON1_RTCRCCEN_ON |
								RCC_PERRCCCON1_PMURCCEN_ON |
								RCC_PERRCCCON1_SCUCKEN_ON |
								RCC_PERRCCCON1_IWDTCKEN_ON |
								RCC_PERRCCCON1_ANACKEN_ON |
								RCC_PERRCCCON1_PDCCKEN_ON |
								RCC_PERRCCCON1_EXTICKEN0_ON |
								RCC_PERRCCCON1_EXTICKEN1_ON |
								RCC_PERRCCCON1_EXTICKEN2_ON |
								RCC_PERRCCCON1_DCUCKEN_ON );
		
	const uint32 set_PERRCCCON2 = (RCC_PERRCCCON2_CRCCKE_OFF |
								RCC_PERRCCCON2_RNGCKE_OFF |
								RCC_PERRCCCON2_AESCKE_OFF |
								RCC_PERRCCCON2_LCDCKE_ON |
								RCC_PERRCCCON2_DMACKE_OFF |
								RCC_PERRCCCON2_FLSCKE_OFF |
								RCC_PERRCCCON2_RAMBISTCKE_OFF |
								RCC_PERRCCCON2_WWDTCKE_ON |
								RCC_PERRCCCON2_ADCCKE_ON |
								RCC_PERRCCCON2_ADCCKSEL_RCHFDIV16);
		
	const uint32 set_PERRCCCON3 = (RCC_PERRCCCON3_SPI1CKE_OFF |
								RCC_PERRCCCON3_SPI2CKE_OFF |
								RCC_PERRCCCON3_HSPICKE_ON |
								RCC_PERRCCCON3_UART0CKE_ON |
								RCC_PERRCCCON3_UART1CKE_ON |
								RCC_PERRCCCON3_UART2CKE_ON |
								RCC_PERRCCCON3_UART3CKE_ON |
								RCC_PERRCCCON3_UART4CKE_ON |
								RCC_PERRCCCON3_UART5CKE_ON |
								RCC_PERRCCCON3_UARTCCKE_ON |
								RCC_PERRCCCON3_USART0CKE_ON |
								RCC_PERRCCCON3_USART1CKE_ON |
								RCC_PERRCCCON3_I2CCKE_ON);
		
	const uint32 set_PERRCCCON4 = (RCC_PERRCCCON4_BT12CKE_ON |
								RCC_PERRCCCON4_BT34CKE_ON |
								RCC_PERRCCCON4_ET1CKE_ON |
								RCC_PERRCCCON4_ET2CKE_ON |
								RCC_PERRCCCON4_ET3CKE_ON |
								RCC_PERRCCCON4_ET4CKE_ON);
	
	const uint32 set_MPRIL = (RCC_MPRIL_MPRIL_DMA);
		
	
	CheckSysReg( &RCC->SYSRCCSEL	, set_SYSRCCSEL );	
	CheckSysReg( &RCC->RCHFCON	, set_RCHFCON );	
//	CheckSysReg( &RCC->RCHFTRIM	, 0X40 );					
	CheckSysReg( &RCC->PLLCON	, set_PLLCON );
	CheckSysReg( &RCC->RCLPCON	, set_RCLPCON );  							
//	CheckSysReg( &RCC->RCLPTRIM	, {} );		
	
	if( EA_ON )//复位后多留点时间给电路起振，然后切回小电流
	{
		CheckSysReg( &RCC->XTLFIPW	, rtcosccfg );
	}
					
	CheckSysReg( &RCC->PERRCCCON1	, set_PERRCCCON1 );	
	CheckSysReg( &RCC->PERRCCCON2	, set_PERRCCCON2 );
	CheckSysReg( &RCC->PERRCCCON3	, set_PERRCCCON3 );	
	CheckSysReg( &RCC->PERRCCCON4	, set_PERRCCCON4 );		
	CheckSysReg( &RCC->MPRIL	, set_MPRIL );
	CheckSysReg( &ANAC->BORCON	, RunBorCfg );//打开BOR
	CheckSysReg( &ANAC->PDRCON	, RunPdrCfg );//打开PDR
	
	#ifdef __DEBUG
	CheckSysReg( &SCU->DBGCFG	, 0x00000003 ); //仿真时运行定时器
	#else
	CheckSysReg( &SCU->DBGCFG	, 0 );
	#endif
}

//模拟电路接口 
//低压检测 Mode 1 = 初始化调用	Mode 0 = 休眠前调用
void Veri_SVD_Ctrl( uint08 Mode )				
{
	SVD_InitType	SVD_InitStructure;

	SVD_Disable();
	
	SVD_InitStructure.Interval = ANAC_SVDCFG_SVDITVL_62_5ms;
	SVD_InitStructure.DFEN = ANAC_SVDCFG_DFEN_ENABLE;
	
	if( ExtVoltage != 0x55 )//内部电压检测
	{
		SVD_InitStructure.LEVEL = Compile_LvdLvCfg;	
	}
	else//SVS外部掉电检测
	{
		SVD_InitStructure.LEVEL = ANAC_SVDCFG_SVDLVL_SVS;	
	}
	
	NVIC_SetPriority(SVD_IRQn,2);
	if( Mode != 0 )
	{
		SVD_InitStructure.MODE = ANAC_SVDCFG_SVDMOD_ALWAYS_ON;
		NVIC_DisableIRQ(SVD_IRQn);
		ANAC->SVDCFG &= ((~ANAC_SVDCFG_PRIE_Msk)|(~ANAC_SVDCFG_PFIE_Msk));//关svd中断
	}
//	else
//	{
//		SVD_InitStructure.MODE = ANAC_SVDCFG_SVDMOD_INTERVAL;
//		NVIC_EnableIRQ(SVD_IRQn);	
//		ANAC->SVDCFG |= ANAC_SVDCFG_PRIE_Msk;		
//	}
	
	SVD_Init(&SVD_InitStructure);
	
	SVD_Enable();
	
}

void Veri_Btmr1(void)			//脉冲计数
{	
	CheckSysReg( &BTIMER1->BTxCFG2	, 0x00000000 );	//EXSEL2 = IN0 EXSEL1 =IN0
	CheckSysReg( &BTIMER1->BTxCFG1	, 0x00000003 );	//Group1信号=EXSEL1
	CheckSysReg( &BTIMER1->BTxCR2	, 0x00000020 );	//计数源=Group1,高位计数器源选择10,diren=0不使用方向输入(stdir内部控制正方向)
//	CheckSysReg( &BTIMER1->BTxCR1	, 0x00000000 );	//
	CheckSysReg( &BTIMER1->BTxIE	, 0x00000008 );	//打开低位比较匹配中断
	
	CheckSysReg( &BTIMER1->BTxOUTCNT, Runet1Outcnt );//
	CheckSysReg( &BTIMER1->BTxOCR	, B0001_0010 );	//输出Gropu1信号
	CheckSysReg( &BTIMER1->BTxPRES	, 0x00000000 );	//Group1信号预分频寄存器,00表示1分频
	
	if( 0 == CheckNvicIrqEn(BT1_IRQn) )//中断关闭
	{	
		NVIC_DisableIRQ(BT1_IRQn);
		NVIC_SetPriority(BT1_IRQn,2);
		NVIC_EnableIRQ(BT1_IRQn);	
	}
}


void Veri_Btmr1_Pcount(unsigned char Result)
{
	if( Result) 
	{
		Decimal.Add = 0;		//清脉冲增量
	}
	if( BTIMER1->BTxLOADL 	!= 1	)	Result  = 1;
	if( BTIMER1->BTxLOADH 	!= 1	)	Result  = 1;
	if( BTIMER1->BTxPRESET 	!= 0	)	Result  = 1;
	if( Result) 
	{
		BTIMER1->BTxLOADL  = 1;
		BTIMER1->BTxLOADH  = 1;
		BTIMER1->BTxPRESET = 0;
		BTIMER1->BTxLOADCR = 0x00000011;//高位加载和低位加载
	}	
}

void Veri_Btmr2(void)			//无功脉冲计数
{	
	CheckSysReg( &BTIMER2->BTxCFG2	, 0x00000020 );	//EXSEL2 = IN0 EXSEL1 =IN2
	CheckSysReg( &BTIMER2->BTxCFG1	, 0x00000003 );	//Group1信号=EXSEL1
	CheckSysReg( &BTIMER2->BTxCR2	, 0x00000020 );	//计数源=Group1,高位计数器源选择10,diren=0不使用方向输入(stdir内部控制正方向)
//	CheckSysReg( &BTIMER2->BTxCR1	, 0x00000000 );	//
	CheckSysReg( &BTIMER2->BTxIE	, 0x00000008 );	//打开低位比较匹配中断
	
	CheckSysReg( &BTIMER2->BTxOUTCNT	, Runet1Outcnt );	//
	CheckSysReg( &BTIMER2->BTxOCR	, B0001_0010 );//0x0000000A;	//输出Gropu1信号
	CheckSysReg( &BTIMER2->BTxPRES	, 0x00000000 );	//Group1信号预分频寄存器,00表示1分频
	
	if( 0 == CheckNvicIrqEn(BT2_IRQn) )//中断关闭
	{	
		NVIC_DisableIRQ(BT2_IRQn);
		NVIC_SetPriority(BT2_IRQn,2);
		NVIC_EnableIRQ(BT2_IRQn);	
	}
}

void Veri_Btmr2_Pcount(unsigned char Result)
{
	if( Result) 
	{
		Decimal.Add_Rp = 0;		//清脉冲增量
	}
	if( BTIMER2->BTxLOADL 	!= 1	)	Result  = 1;
	if( BTIMER2->BTxLOADH 	!= 1	)	Result  = 1;
	if( BTIMER2->BTxPRESET 	!= 0	)	Result  = 1;
	if( Result) 
	{
		BTIMER2->BTxLOADL  = 1;
		BTIMER2->BTxLOADH  = 1;
		BTIMER2->BTxPRESET = 0;
		BTIMER2->BTxLOADCR = 0x00000001;//低位加载
	}	
}

//ET2, 4ms定时器中断
void Veri_Etmr2(void)
{
	if( !(ETIMER2->ETxCR & 0x00000080) ) 
		ETIMER2->ETxCR = 0x00000000;   
	
	CheckSysReg( &ETIMER2->ETxINSEL	, 0x00000000 );   			
	CheckSysReg( &ETIMER2->ETxPESCALE1	, clkmode - 1 );  		
	CheckSysReg( &ETIMER2->ETxPESCALE2	, clkmode - 1 );	
	CheckSysReg( &ETIMER2->ETxIVR	, 0xffff-0x7d00 );						
	CheckSysReg( &ETIMER2->ETxCMP	, 0x00000000 );						
	CheckSysReg( &ETIMER2->ETxIE	, 0x00000001 );					
//	CheckSysReg( &ETIMER2->ETxETxIF	,  );		

	if( !(ETIMER2->ETxCR & 0x00000080) ) 
		ETIMER2->ETxCR |= 0x00000080;   //启动定时器
	
	if( 0 == CheckNvicIrqEn(ETIMER2_IRQn) )//中断关闭
	{
		NVIC_DisableIRQ(ETIMER2_IRQn);
		NVIC_SetPriority(ETIMER2_IRQn,2);
		NVIC_EnableIRQ(ETIMER2_IRQn);		
	}
}

//ET4, 80ms定时器中断
void Veri_Etmr4(void)
{
	if( !(ETIMER4->ETxCR & 0x00000080) ) 
		ETIMER4->ETxCR = 0x00000000;   
	
	CheckSysReg( &ETIMER4->ETxINSEL	, 0x00000000 );   			
	CheckSysReg( &ETIMER4->ETxPESCALE1	, clkmode - 1 );  		
	CheckSysReg( &ETIMER4->ETxPESCALE2	, clkmode - 1 );	
	CheckSysReg( &ETIMER4->ETxIVR	, 0xffff-0x7d00 );						
	CheckSysReg( &ETIMER4->ETxCMP	, 0x00000000 );						
	CheckSysReg( &ETIMER4->ETxIE	, 0x00000001 );					
//	CheckSysReg( &ETIMER2->ETxETxIF	,  );		

//	if( !(ETIMER4->ETxCR & 0x00000080) ) 
//		ETIMER4->ETxCR |= 0x00000080;   //启动定时器
	
	if( 0 == CheckNvicIrqEn(ETIMER4_IRQn) )//中断关闭
	{
		NVIC_DisableIRQ(ETIMER4_IRQn);
		NVIC_SetPriority(ETIMER4_IRQn,1);
		NVIC_EnableIRQ(ETIMER4_IRQn);		
	}
}

unsigned char GetBps( unsigned char Type, unsigned char Bps )
//Type =0:645, 1:698; Bps = 645的设置值
{
	unsigned char i, k;
	
//	if( Bps == B0000_0001 )//115200bps
//	{
//		return 5;
//	}
	
	k = 0x04;
	for( i=0; i<6; i++ )
	{
		if( (Bps&B1111_1110) == k ) break;
		k <<= 1;
	}
	
	if( i >= 6 ) i = 3; //9600bps
	
	if( Type == 0 ) return i;
	return 3; //9600bps
}


void Veri_Uart_All( void )
{
	unsigned char Result;
	
	//UART0	//载波
	if( Zb_Comm_Timer==0 ) Zbbps = Mode.Zbbps;
	else Zbbps = Mode.Zbbps_Ram;
	Result = GetBps( 0, Zbbps ); //载波通道
	CheckSysReg( &UART0->RXSTA		, B0101_0000 );		//8位数据,偶校验,RXEN=1
	CheckSysReg( &UART0->TXSTA		, B0011_0000 );		//1位停止位,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART0->RXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART0->TXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART0->RTXCON		, B0000_0000 );		//接收数据不取反,发送数据不取反
	if( UpdateBps!=1 ) CheckSysReg( &UART0->SPBRG		, BPS_SPBRGL1[ Result + clkmode%2 ] );
	
	//UART1	//BLE
	if( Ble_Reset == 0xAA )
	{
		Ble_Rst();
		Ble_Reset = 0;
	}
//	Result = GetBps( 0, Mode.blebps ); //蓝牙通道
	Result = 7;																			//默认115200
	CheckSysReg( &UART1->RXSTA		, B0001_0000 );		//8位数据,无校验,RXEN=1
	CheckSysReg( &UART1->TXSTA		, B0011_0000 );		//1位停止位,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART1->RXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART1->TXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART1->RTXCON		, B0000_0000 );		//接收数据不取反,发送数据不取反
	if( UpdateBps!=1 ) CheckSysReg( &UART1->SPBRG		, BPS_SPBRGL1[ Result + clkmode%2 ] );	
	
	//UART2	//485
	Result = GetBps( 0, Mode.Bps[0] ); //RS485通道
	CheckSysReg( &UART2->RXSTA		, B0101_0000 );		//8位数据,偶校验,RXEN=1
	CheckSysReg( &UART2->TXSTA		, B0011_0000 );		//1位停止位,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART2->RXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART2->TXFIFOSTA	, B0000_0000 );	//(兼容原中断)
//	CheckSysReg( &UART2->RTXCON		, B0000_0000 );		//接收数据不取反,发送数据不取反
	if( UpdateBps!=1 ) CheckSysReg( &UART2->SPBRG		, BPS_SPBRGL1[ Result + clkmode%2 ] );	
	
	//UART4	//计量
	CheckSysReg( &UART4->RXSTA		, B0101_0000 );		//8位数据,偶校验,RXEN=1
	CheckSysReg( &UART4->TXSTA		, B0011_0000 );		//1位停止位,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART4->RXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART4->TXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART4->RTXCON		, B0000_0000 );		//接收数据不取反,发送数据不取反
	CheckSysReg( &UART4->SPBRG		, BPS_SPBRGL1[ 2 + clkmode%2 ] );	//4800
	
	//UART5	//红外
	CheckSysReg( &UART5->RXSTA		, B0101_0000 );		//1位停止位,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART5->TXSTA		, B0011_1000 );		//1位停止位,TXIS=1,TXEN=1,BRGH=1,红外调制使能
	CheckSysReg( &UART5->RXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART5->TXFIFOSTA	, B0000_0000 );	//(兼容原中断)
	CheckSysReg( &UART5->RTXCON		, B0000_0000 );		//接收数据不取反,发送数据不取反
	CheckSysReg( &UART5->SPBRG		, BPS_SPBRGL1[ clkmode%2 ] );		//1200	
	CheckSysReg( &UART_common->TZBRG , (210*clkmode|(IRDutyCycleCfg)) );//Mclk=8M时38k调制 占空比Y(73.9%) = (TZBRG[10:4]*TH)/(TZBRG+1)=(13*12)/（210+1）,经过三极管反相后变为26.1%  //正极性PNP,当TH=4'b0000时,(X[10:1]+1)/(X+1)=106/211
	
	//缓冲区分配：0=红外， 1=485， 2=载波
	if ( ((Uart[CHHW].Flag == 0)&&(Uart[CHBLE].Flag == 0)&&(Uart[CH485].Flag == 0)&&(Uart[CHZB].Flag == 0)) || (EA_OFF) )
	{
		CheckSysReg( &UART_common->UARTIE , UART_RX_IE0|UART_RX_IE2|UART_RX_IE5|UART_TX_IE0|UART_RX_IE1 );//使能RXIE2,RXIE1和RXIE0
		R485CTRLR;		//允许接收
//		if(EA_OFF)
//		{
//			{RXSTA0 = 0;RXSTA0 = B0101_0000;}//复位接收电路
//			{RXSTA1 = 0;RXSTA1 = B0101_0000;}//复位接收电路
//			{RXSTA2 = 0;RXSTA2 = B0101_0000;}//复位接收电路
//			{RXSTA3 = 0;RXSTA3 = B0101_0000;}//复位接收电路
//		}
	}

	if( 0 == CheckNvicIrqEn(UART2_IRQn) )//中断关闭
	{
		NVIC_DisableIRQ(UART2_IRQn);
		NVIC_SetPriority(UART2_IRQn,2);
		NVIC_EnableIRQ(UART2_IRQn);
	}
	if( 0 == CheckNvicIrqEn(UART1_IRQn) )//中断关闭
	{	
		NVIC_DisableIRQ(UART1_IRQn);
		NVIC_SetPriority(UART1_IRQn,2);
		NVIC_EnableIRQ(UART1_IRQn);	
	}
	if( 0 == CheckNvicIrqEn(UART0_IRQn) )//中断关闭
	{	
		NVIC_DisableIRQ(UART0_IRQn);
		NVIC_SetPriority(UART0_IRQn,2);
		NVIC_EnableIRQ(UART0_IRQn);	
	}
	if( 0 == CheckNvicIrqEn(UART5_IRQn) )//中断关闭
	{		
		NVIC_DisableIRQ(UART5_IRQn);
		NVIC_SetPriority(UART5_IRQn,2);
		NVIC_EnableIRQ(UART5_IRQn);		
	}
	
}

void Veri_I2c( void )
{
	CheckSysReg( &I2C->I2CBRG	, 9 );    //I2C波特率: I2C波特率: 200K@8MHz, 400k@16MHz
	CheckSysReg( &I2C->I2CIR	, 0 );	//禁止I2C中断
}

void Veri_Spi( void )
{
//	if( (SPCR&B1000_0000) != B0000_0000 ) 	SPCR 	&= B0111_1111;	//禁止SPI中断
}

void Veri_Rtc( void)
{
	if(const_mark404 == 0x0404)
	{
		CheckSysReg( (__IO uint32_t *)0x40011064, 0x00000000 );//AUTOCAL
		CheckSysReg( (__IO uint32_t *)0x40011068, 0x00000000 );//ADOFFSET
		if(RTC_Trim_Ctrl == 0x55)
			CheckSysReg( (__IO uint32_t *)0x4001106C, 0x00000001 );//CALSTEP 0.119
		else
			CheckSysReg( (__IO uint32_t *)0x4001106C, 0x00000000 );//CALSTEP 0.238
	}
	
	CheckSysReg( &RTC->RTCIE	, RTC_RTCIE_SEC_IE_ENABLE );
//	CheckSysReg( &RTC->ALARM	,  );
	CheckSysReg( &RTC->FSEL		, Runrtctmls );//RTC_FSEL_FSEL_PLL_1S;
	CheckSysReg( &RTC->PR1SEN	, RTC_PR1SEN_PR1SEN_ENABLE );	//使能虚拟调校功能，使用pll产生精确1Hz
	CheckSysReg( &RTC->STAMPEN	, RTC_STAMPEN_STAMP0EN_DISABLE | RTC_STAMPEN_STAMP1EN_DISABLE );//关闭时间戳功能
	
	if( 0 == CheckNvicIrqEn(RTC_IRQn) )//中断关闭
	{
		NVIC_DisableIRQ(RTC_IRQn);
		NVIC_SetPriority(RTC_IRQn,2);
		NVIC_EnableIRQ(RTC_IRQn);	
	}
}

void Veri_U7816( void )
{
	CheckSysReg( &U7816CTRL0	, DEF_USART0CTRL );
	CheckSysReg( &U7816FRMCTRL0	, DEF_USART0FRC );	//重发1次,偶校验,先发lsb
	CheckSysReg( &U7816EGTCTRL0	, DEF_USART0EGT );
	CheckSysReg( &U7816CLKDIV0	, DEF_USART0CLKDIV+2*(clkmode-1) );	//mclk=16M时7816=4M,mclk=8M时7816=4M
	CheckSysReg( &U7816PREDIV0	, DEF_USART0CLKPDIV );	//1ETU=1/372
	CheckSysReg( &U7816INTEN0	, DEF_USART0IE );	//禁止中断
	
	CheckSysReg( &U7816CTRL1	, DEF_USART0CTRL );
	CheckSysReg( &U7816FRMCTRL1	, DEF_USART0FRC );	//重发1次,偶校验,先发lsb
	CheckSysReg( &U7816EGTCTRL1	, DEF_USART0EGT );
	CheckSysReg( &U7816CLKDIV1	, DEF_USART0CLKDIV+2*(clkmode-1) );	//mclk=16M时7816=4M,mclk=8M时7816=4M
	CheckSysReg( &U7816PREDIV1	, DEF_USART0CLKPDIV );	//1ETU=1/372
	CheckSysReg( &U7816INTEN1	, DEF_USART0IE );	//禁止中断
}

//Mode 1 = 初始化调用	Mode 0 = 休眠调用
void Veri_Disp( uint08 Mode )
{	
	unsigned char i;
	
	CheckSysReg( &DISP->LCDTEST 	, B0000_0000 );//禁止测试	
	CheckSysReg( &DISP->TON 		, B0000_0000 );
	CheckSysReg( &DISP->TOFF 		, B0000_0000 );
	CheckSysReg( &DISP->DISPIE		, B0000_0000 );
	CheckSysReg( &DISP->LCDBSTCON	, B0000_0000 );	
	
	if( Mode != 0 )
	{
		CheckSysReg( &DISP->DF 		, 32 );		 //85Hz@6com
		CheckSysReg( &DISP->LCDSET 	, RunlLCDSET );
		CheckSysReg( &DISP->LCDDRV 	, RunlLCDDRV );
//		CheckSysReg( &DISP->LCDBIAS , Runlcdbias );
	}
	else
	{
		CheckSysReg( &DISP->DF 		, Sleeplcdfreq );		 //
		CheckSysReg( &DISP->LCDSET 	, SleepLCDSET );
		CheckSysReg( &DISP->LCDDRV 	, SleepLCDDRV );
		
		for( i=0; i<6; i++ )
		{
			if( Fun_Para.Voltage_P < Sleepvthreshold[i] ) //目前程序支持6级台阶
			{
				if( Extbattery == 0x55 ) DISP->LCDBIAS  = Sleeplcdbias[i];
				else DISP->LCDBIAS  = Sleeplcdbias[0];
//				DISP->LCDBIAS  = Sleeplcdbias[0];
				break;
			}
		}
		if( i == 6 ) DISP->LCDBIAS  = Sleeplcdbias[0];
		
//		disp_sleep_flag = 1;//置停电显示标志
	}
	
	CheckSysReg( &DISP->COM_EN , 0x0000000F );
	CheckSysReg( &DISP->SEG_EN0 , 0xCC339C3D );
	CheckSysReg( &DISP->SEG_EN1 , 0x00000FFF );
	
	if( Mode != 0 )
		CheckSysReg( &DISP->DISPCTRL ,B1100_0000 );//防极化使能,打开显示
	else
		DISP->DISPCTRL |= BIT7;//防极化使能	
}

void Veri_Wwdt( void )
{
	CheckSysReg( &WWDT->WWDTIE	, 0x01 );  //wwdt中断使能打开 			
	
	if( 0 == CheckNvicIrqEn(WWDT_IRQn) )//中断关闭
	{
		NVIC_DisableIRQ(WWDT_IRQn);
		NVIC_SetPriority(WWDT_IRQn,1);
		NVIC_EnableIRQ(WWDT_IRQn);		
	}
}

void Veri_Sys_Reg( void )
{
	reg_veri_flag = 0;
	Veri_Pad();
	Veri_Clk_Gen();
//	Veri_Mode_Ctrl();
	Veri_SVD_Ctrl(1);
//	Veri_Adc_Ctrl();
	Veri_Btmr1();			//脉冲计数	
	Veri_Btmr1_Pcount(0);
	Veri_Btmr2();	
	Veri_Btmr2_Pcount(0);
	Veri_Etmr2();
	Veri_Etmr4();
	Veri_Uart_All(); 
	Veri_I2c();
	Veri_Spi();
	Veri_Rtc();
	Veri_U7816();
	Veri_Disp(1);
	Veri_Wwdt();
}


////*对应的直接进行Bit运算是低位先传的方式(即"生成多项式" = 0x8408), 若高位先传("生成多项式" = 0x1021)则下表不适合.
//const unsigned short code crc16_ccitt_table[256] =
//{
//	0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
//	0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
//	0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
//	0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
//	0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
//	0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
//	0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
//	0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
//	0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
//	0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
//	0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
//	0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
//	0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
//	0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
//	0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
//	0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
//	0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
//	0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
//	0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
//	0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
//	0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
//	0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
//	0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
//	0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
//	0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
//	0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
//	0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
//	0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
//	0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
//	0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
//	0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
//	0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
//};


unsigned short Crc_16Bits( unsigned char *buf, unsigned char len ) 
{
	unsigned char i, j;
	unsigned short current,CRC16;
			
	CRC16 = 0x0000;

	for( i=0; i<len; i++ )
	{
	    current = buf[i];
	    for (j = 0; j < 8; j++) 
	    { 
	        if ((CRC16 ^ current) & 0x0001)
	            CRC16 = (CRC16 >> 1) ^ 0x8408;
	        else 
	            CRC16 >>= 1; 
	        current >>= 1;            
	    }
	}
	
	return CRC16;
}

void Crc_16Bits_Add2( unsigned char *buf, unsigned char len ) 
{
	unsigned short Result;
	
	Result  = Crc_16Bits( buf, len );
	buf[len] = Result;		//低字节
	buf[len+1] = Result>>8;		//高字节
}


unsigned char Crc_Check( unsigned char *buf, unsigned char len ) 
{
	if( ChkBufZero(buf,len)==0 ) return 1;	//所有数据均为0,认为校验错

	if( Crc_16Bits( buf, len ) ) return 1;	//crc校验错误
	
	return 0;				//校验正确
}


unsigned char Verify_para(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len )//一托二数据校验函数
{
	if( Crc_Check( Buf, Len+2 ) == 0 ) return 0;	//ram参数crc正确
	
	if( I2C_Read_Eeprom( Page, Inpage, Buf, Len ) == 0 ) return 0;//已经从数据ee主恢复
	
	if( I2C_Read_Eeprom( Page+1, Inpage, Buf, Len ) != 0 ) return 1;//数据全错
	
	I2C_Write_Eeprom( Page, Inpage, Buf, Len );	//从数据ee备份恢复,同时写主
	
	return 0;
}


unsigned char Dl_Check( unsigned char *buf ) 
{
	unsigned char i;
	union B64_B08_2 Temp64_T;
	union B64_B08_2 Temp64;
	
	{Temp64_T.B64 = 0;Temp64.B64 = 0;}
	
	for( i=1; i<(max_feilvcount+1); i++ )
	{
		memcpy( Temp64_T.B08, buf+i*4, 4 ); //各费率脉冲数
		Temp64.B64 += Temp64_T.B64;//各费率脉冲数累加和
	}
	memcpy( Temp64_T.B08, buf, 4 ); //总脉冲数
	
	if( Temp64_T.B64 < Temp64.B64 ) return 1; //总电量 < (各费率和), 错误
	if( Temp64_T.B64 - Temp64.B64 > Def_Dl_Difference ) return 1; //总电量 > (各费率和+0.xx), 错误
	
	return 0;//校验正确
}

unsigned char Verify_Dl(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len )//一托二数据校验函数
{
	if( (Crc_Check( Buf, Len+2 ) == 0) && (Dl_Check( Buf ) == 0) ) return 0;	//ram参数crc正确
	
	if( (I2C_Read_Eeprom( Page, Inpage, Buf, Len ) == 0) && (Dl_Check( Buf ) == 0) ) return 0;//已经从数据ee主恢复
	
	if( (I2C_Read_Eeprom( Page+1, Inpage, Buf, Len ) == 0) && (Dl_Check( Buf ) == 0) )
	{
		I2C_Write_Eeprom( Page, Inpage, Buf, Len );	//从数据ee备份恢复,同时写主
		return 0;
	}
	else  return 1;//数据全错
}


void Starttimer_Verify()	//启动时间校验
{
	Verify_para( ee_starttimer_page, ee_starttimer_inpage, Starttime.Shiqu, ee_starttimer_lenth );
}

void Esam_Para_Verify()	//报警金额1,2等参数(ESAM一类部分参数)校验
{
#if(ESAMON == 1)	
	unsigned char result;
	unsigned char Buf[32];
	
	if(Verify_para( ee_esampara_page, ee_esampara_inpage, Esam_Para.Current_Ratio, ee_esampara_lenth ))
	{
		memset( Esam_Para.Current_Ratio, 0x00, ee_esampara_lenth );//非法默认
		Esam_Para.Current_Ratio[2] = 1;Esam_Para.Voltage_Ratio[2] = 1;//变比1
		Esam_Para.Meter_Id[5] = 0xff;//表号0x0000000000ff
		memset( Esam_Para.Zb_Id, 0xff, 6 );//模块id(6)
		Esam_Para.Identity_Delay.B08[0] = Defaultauthtimer>>8;//身份认证有效时长
		Esam_Para.Identity_Delay.B08[1] = Defaultauthtimer;//身份认证有效时长
	}
	
	if( EA_OFF ) return;
	if( esam_error ) return;
	if( esam_biaohao_flag ) return;//已采用esam表号
	
	if((identity_prog_flag == 0) && (identity_ir_flag == 0))
	{
		result = EsamReset();//安全认证编程标志失效
		if( result ) return;//复位错误
	}
	
	result = ReadBinFile( ESAM, 0x81, 0x1e, 6 );
	if( result ) return;//读错误返回
	
	result = Cmp_Data( Esam_Para.Meter_Id, Ic_Comm_RxBuf, 6 );
	if( result != 3 )
	{
		memcpy( Esam_Para.Meter_Id, Ic_Comm_RxBuf, 6 );//复制esam表号到ram
		WriteE2WithBackup(ee_esampara_page, ee_esampara_inpage, Esam_Para.Current_Ratio, ee_esampara_lenth);
	}
	
	result = ReadBinFile( ESAM, 0x85, 0x00, 4 );	//读esam的05文件回复密钥状态
	if( result ) return;//读错误返回
	
	Inverse( Ic_Comm_RxBuf, 4 );
	
	I2C_Read_Eeprom44( ee_keystatus_page, Buf, ee_keystatus_lenth );//读密钥状态
	
	result = Cmp_Data( Buf, Ic_Comm_RxBuf, 4 );
	if( result != 3 )
	{
		memcpy( Buf, Ic_Comm_RxBuf, 4 );//复制4字节密钥状态
		I2C_Write_Eeprom44( ee_keystatus_page, Buf, ee_keystatus_lenth );//写密钥状态
		GetKeyStatus();		//读当前密钥状态
		FailKey();
	}
	
	esam_biaohao_flag = 1;//置已经采用esam表号标志
#else
	if(Verify_para( ee_esampara_page, ee_esampara_inpage, Esam_Para.Current_Ratio, ee_esampara_lenth ))
	{
		memset( Esam_Para.Current_Ratio, 0x00, ee_esampara_lenth );//非法默认
		Esam_Para.Current_Ratio[2] = 1;Esam_Para.Voltage_Ratio[2] = 1;//变比1
		Esam_Para.Meter_Id[5] = 0xff;//表号0x0000000000ff
		Esam_Para.Identity_Delay.B08[0] = Defaultauthtimer>>8;//身份认证有效时长
		Esam_Para.Identity_Delay.B08[1] = Defaultauthtimer;//身份认证有效时长
	}
#endif
}


void Meter_Const_Verify()	//电表常数校验
{
	Int2Byte( Def_Meterconst_Bcd, Meter.Const.B08);
	Meter.Const_H = Def_Meterconst_Hex;
//	Month_Account_Verify();
}


unsigned char Fwdl_Verify()		//正向电量校验
{
	fwdl_veri_flag = 0;
	Meter_Const_Verify();
	return(Verify_Dl( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth ));//正向脉冲尾数校验	
}

unsigned char Bkdl_Verify()		//反向电量校验
{
	bkdl_veri_flag = 0;
	Meter_Const_Verify();
	return(Verify_Dl( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth ));//反向脉冲尾数校验
}

unsigned char Rpdl_Verify( unsigned char i )		//四象限无功电量校验
{
	rpdl_veri_flag = 0;
	Meter_Const_Verify();
	return(Verify_Dl( ee_rpdl_page+2*i, ee_rpdl_inpage, Rpdl[i].Pluse[0].B08, ee_rpdl_lenth ));
}

void Mode_Verify()			//特征模式字校验
{
	unsigned char Buf[ee_featureword_lenth+2];
	
	mode_veri_flag = 0;
	if( Verify_para( ee_featureword_page, ee_featureword_inpage, Mode.Bps, ee_featureword_lenth ) )
	{
		memcpy( Mode.Bps, Def_featureword_table, ee_featureword_lenth );
	}
	
	if( Mode.Report_Period < 5 )//小于5min则默认60min
		Mode.Report_Timer = def_meterrun_timer*60;
	else 
		Mode.Report_Timer = Bcd_To_Hex(Mode.Report_Period)*60;
		
	if( (Memoryerr_Ctrl == 0x55) &&	//存储器故障上报编译使能
	    ((I2C_Read_Eeprom(ee_featureword_page, ee_featureword_inpage, Buf, ee_featureword_lenth) 
		&& I2C_Read_Eeprom(ee_featureword_page+1, ee_featureword_inpage, Buf, ee_featureword_lenth)) 
		|| (ChkBufZero( Buf, ee_featureword_lenth ) == 0)) )
	{
		if( eeprom_error_flag == 0 )
		{
			Set_Reportdata(0*8+5);//置存储器故障上报标志
		}
		eeprom_error_flag = 1; //置存储器故障标志
	}
	else	eeprom_error_flag = 0; //清存储器故障标志
}



void Week_Holiday_Verify()	//周休日和负荷参数校验
{
	if(Verify_para( ee_weekholiday_page, ee_weekholiday_inpage, &Week_Holiday.Status, ee_weekholiday_lenth ))
	{
		memcpy( &Week_Holiday.Status, Def_weekloadpara_table, ee_weekholiday_lenth );
	}
}

void feik_Num_Verify( void ) //时区数等参数校验
{
	if(Verify_para( ee_feik_number_page, ee_feiknumber_inpage, Feik.Num, ee_feiknumber_lenth )) //读时区数
	{
		memcpy( Feik.Num, Def_feik_table, ee_feiknumber_lenth );
	}
}

#if( NEWCLOCKADJ == 0 ) //旧标准时钟调校
void Fill_RTC_RT_TAdc(void)//读取查表adc数据
{
	//根据温度自动判断写入数据的地址
	uint16 Page;
	uint08 offset;
	uint08 Len;
	uint08 i;

	if( RTC_RT.TempFlag == 0 )//常温查表
	{
		Page = ee_ptatvalue_page;
		offset = ee_ptatvalue_inpage;
		Len = ee_ptatvalue_lenth;
		
		if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TAdc.PTAT_Value, Len ))
		{
			memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
		}
		
		return;
	}
	else if( RTC_RT.TempFlag == 1 )//低温查表
	{
		Page = ee_ptatvalue_lt_page;
		offset = ee_ptatvalue_lt_inpage;
		Len = ee_ptatvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//高温查表
	{
		Page = ee_ptatvalue_ht_page;
		offset = ee_ptatvalue_ht_inpage;
		Len = ee_ptatvalue_ht_lenth+2;
	}
	else
	{
		memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
		return;
	}
	
	I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TAdc.PTAT_Value, Len );
	if( 0 == Crc_Check( (uint08*)RTC_RT.TAdc.PTAT_Value, Len ) )//ee crc正确，填充尾部数据并重新计算crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TAdc.PTAT_Value[i/2] = RTC_RT.TAdc.PTAT_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uint08*)RTC_RT.TAdc.PTAT_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc错误，数据非法，填充ff
	{
		memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
	}
}

void Fill_RTC_RT_TVal(void)//读取查表补偿值数据
{
	//根据温度自动判断写入数据的地址
	uint16 Page;
	uint08 offset;
	uint08 Len;
	uint08 i;

	if( RTC_RT.TempFlag == 0 )//常温查表
	{
		Page = ee_ptatvalue_page+1;
		offset = ee_ptatvalue_inpage;
		Len = ee_ptatvalue_lenth;
		
		if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TVal.Trim_Value, Len ))
		{
			memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法则填
		}
		
		return;
	}
	else if( RTC_RT.TempFlag == 1 )//低温查表
	{
		Page = ee_ptatvalue_lt_page+1;
		offset = ee_ptatvalue_lt_inpage;
		Len = ee_ptatvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//高温查表
	{
		Page = ee_ptatvalue_ht_page+1;
		offset = ee_ptatvalue_ht_inpage;
		Len = ee_ptatvalue_ht_lenth+2;
	}
	else
	{
		memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法
		return;
	}
	
	I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TVal.Trim_Value, Len );
	if( 0 == Crc_Check( (uint08*)RTC_RT.TVal.Trim_Value, Len ) )//ee crc正确，填充尾部数据并重新计算crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TVal.Trim_Value[i/2] = RTC_RT.TVal.Trim_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uint08*)RTC_RT.TVal.Trim_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc错误，数据非法，填充ff
	{
		memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法则填ff
	}
}
#else
void Fill_RTC_RT_TAdc(void)//读取查表adc数据
{
	//根据温度自动判断写入数据的地址
	uint16 Page;
	uint08 offset;
	uint08 Len;

	Page = ee_ptatvalue_page;
	offset = ee_ptatvalue_inpage;
	Len = ee_ptatvalue_lenth;
		
	if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TAdc.PTAT_Value, Len ))
	{
		memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//非法则填ff
	}
		
	return;
}

void Fill_RTC_RT_TVal(void)//读取查表补偿值数据
{
	//根据温度自动判断写入数据的地址
	uint16 Page;
	uint08 offset;
	uint08 Len;

	Page = ee_ptatvalue_page+1;
	offset = ee_ptatvalue_inpage;
	Len = ee_ptatvalue_lenth;
		
	if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TVal.Trim_Value, Len ))
	{
		memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//非法则填
	}
		
	return;
}
#endif

void Temperpara_Verify()	//温度系数校验
{
	temperpara_veri_flag = 0;
	if(Verify_para( ee_temperature_page, ee_temperature_inpage, Tpara.Offset, ee_temperature_lenth ))
	{
		memset( Tpara.Offset, 0x00, ee_temperature_lenth );//默认为0 
		Tpara.Offset[0]	= 0x80;
	}
	if( Tpara.RtcTMode == 0xAA )//0xAA常温查表插值模式
	{
		if( Crc_Check( (uint08 *)RTC_RT.TAdc.PTAT_Value, ee_ptatvalue_lenth+2 ) != 0 ) 
		{
			Fill_RTC_RT_TAdc();
		}
		if( Crc_Check( (uint08*)RTC_RT.TVal.Trim_Value, ee_trimvalue_lenth+2 ) != 0 )
		{
			Fill_RTC_RT_TVal();
		} 		
	}
}


void Commaddr_Verify()		//通讯地址校验
{
	addr_veri_flag = 0;
	if( Verify_para( ee_commaddr_page, ee_commaddr_inpage, Comm_Addr.Comm_Id, ee_commaddr_lenth ) )
	{
		memset( Comm_Addr.Comm_Id, 0x00, 6 );//通讯地址默认为01
		Comm_Addr.Comm_Id[5] = 0x01;
	}
	
	//电压合格率等相关参数校验
	if( Verify_para( ee_vollimit_page, ee_vollimit_inpage, VolLimit.MaxVolLmt.B08, ee_vollimit_lenth ) )
	{
		memcpy( VolLimit.MaxVolLmt.B08, Def_vollmtpara_table, ee_vollimit_lenth );
	}
}


void Display_Para_Verify()	//显示参数校验
{
	disppm_veri_flag = 0;
	if( Verify_para( ee_displaypara_page, ee_displaypara_inpage, &Display_Para.S_Number, ee_displaypara_lenth ) )
	{
		memcpy( &Display_Para.S_Number, Def_DisplayPara_table, ee_displaypara_lenth );
	}
	Hw_Lcdled_Timer = Display_Para.Loop_Time*Display_Para.S_Number*2;
}


void Displayitem_Verify()	//显示项目校验(一托一)
{
	unsigned char i,j,result,len;
	
	dispitem_veri_flag = 0;
	
	for( i=0; i<2; i++ )
	{		
		if( Crc_Check( (unsigned char*)Item[i].Display, ee_displayitem_lenth*3+ee_displayitem_lenth1+2 ) == 0 ) continue;//ram参数crc正确
		
		//读循环显示序号或者按键显示序号
		result = 0;
		for( j=0; j<4; j++ )
		{
			if( j != 3 ) len = ee_displayitem_lenth;
			else len = ee_displayitem_lenth1;
			if( I2C_Read_Eeprom( ee_loop_displayitem_page+2*j+i, 0x00, (unsigned char*)Item[i].Display+ee_displayitem_lenth*j, len ) )
			{
				result = 1;
				break;
			}
		}
		
		if( result || (ChkBufZero( (unsigned char*)Item[i].Display, ee_displayitem_lenth*3+ee_displayitem_lenth1 ) == 0) ) //数据非法采用默认的显示
		{
		    	for( j=0; j<20; j++ )
			{
				Item[i].Display[j] = j+0x201;	//512+1(0x201)表示普通组合电量  1024+1(0x401)表示高精度组合电量(预留)
			}
		}
		else
		{
			Crc_16Bits_Add2( (unsigned char*)Item[i].Display, ee_displayitem_lenth*3+ee_displayitem_lenth1 );	 //CRC计算
		}
	}
}
