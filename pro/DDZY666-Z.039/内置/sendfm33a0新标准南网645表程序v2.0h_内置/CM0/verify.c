#include "ex_func.h"
#include "ex_var.h"
#include "FM32L0XX.h" 
#include <string.h>
#include "Cpu_card.h"


//У��Ĵ���
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

//��ѯNVIC�Ĵ�����Ӧ�������ж��Ƿ��
//1 ��
//0 �ر�
unsigned char CheckNvicIrqEn( IRQn_Type IRQn )
{
	if( 0 == ( NVIC->ISER[0U] & ((uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL)))) )
		return 0;
	else
		return 1;
}

//ģ�⹦������:LCD/ADC
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

//����IO������ type 0 = ��ͨ type 1 = ����
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

//���IO������ type 0 = ��ͨ type 1 = OD
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
//�������⹦�ܿ� 
//type 0 = ��ͨ type 1 = OD (OD���ܽ��������⹦��֧��)
//type 2 = ��ͨ+���� type 3 = OD+����
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
//�ر�IO��od����ߣ�
//������ʹ����Чʱ������ⲿ�źŸ��գ�Ҳ���ܵ���FM385�ܽ�©�磻
//���Խ�FCR����Ϊ01��GPIO�������ODEN����Ϊ1����α��©������ر�����ʹ�ܣ��������������Ϊ1
//ע��SWD�ӿڵ�PG8,9�������ı����ǵ����ý��޷�����
void CloseeIO( GPIOx_Type* GPIOx, uint32 PinNum )
{
	OutputIO( GPIOx, PinNum, 1 );
	GPIO_SetBits(GPIOx, PinNum);
}

void Close_None_GPIO(void)
{
	//�ر�80��оƬ����ʹ�õ�IO
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
	CheckSysReg( &GPIO_common->HDSEL	, 0x00000001 );//PE2ǿ����ʹ��
	CheckSysReg( &GPIO_common->FOUTSEL	, GPIO_FOUTSEL_RTCTM );
	CheckSysReg( &GPIO_common->ANASEL	, 0x3F );	//ģ���Һ����AD����ѡ��	
	CheckSysReg( &GPIO_common->IOFIN	, BIT4|BIT1 );//����������������˲�����
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
	AltFunIO( GPIOB, GPIO_Pin_1, 1 );	//PB1;//BLE-TXD(OD���)
	AltFunIO( GPIOB, GPIO_Pin_2, 0 );	//PB2;//RX485, RXD2
	AltFunIO( GPIOB, GPIO_Pin_3, 0 );	//PB3;//TX485, TXD2
	AltFunIO( GPIOB, GPIO_Pin_4, 0 );	//PB4;//ACTIVEP
	InputtIO( GPIOB, GPIO_Pin_5, 0 );	//PB5;//TAIL
//	AltFunIO( GPIOB, GPIO_Pin_6, 0 );	//PB6;//PULSELED
	OutputIO( GPIOB, GPIO_Pin_7, 0 );	//PB7;//VBLE
	AnalogIO( GPIOB, GPIO_Pin_8  );		//PB8;//SEG7
	AnalogIO( GPIOB, GPIO_Pin_9  );		//PB9;//SEG8
	AnalogIO( GPIOB, GPIO_Pin_10 );		//PB10;//SEG9
	OutputIO( GPIOB, GPIO_Pin_11, 0 );//PB11;//RelayCtrl//EE_V@�������
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
	OutputIO( GPIOD, GPIO_Pin_4, 0 );	//PD4;//RelayOn, �̵������ƽ�
	OutputIO( GPIOD, GPIO_Pin_5, 0 );	//PD5;//RelayOff,	�̵������ƽ� 
	InputtIO( GPIOD, GPIO_Pin_6, 1 );	//PD6;//DISPKEY,������
	OutputIO( GPIOD, GPIO_Pin_7, 0 );	//PD7;//EsamVcc
	
	OutputIO( GPIOE, GPIO_Pin_2, 0 );	//PE2;//LCDLED 	
	OutputIO( GPIOE, GPIO_Pin_3, 0 );	//PE3;//485Ctrl
	OutputIO( GPIOE, GPIO_Pin_4, 0 );	//PE4;//VFLASH
	OutputIO( GPIOE, GPIO_Pin_5, 1 );	//PE5;//PLCEVT(OD���)
	
	AltFunIO( GPIOF, GPIO_Pin_3, 0 );	//PF3;//RXZB RXD0 
	AltFunIO( GPIOF, GPIO_Pin_4, 1 );	//PF4;//TXZB TXD0 (OD���)
	OutputIO( GPIOF, GPIO_Pin_5, 1 );	//PF5;//PLCRST(OD���)
	AnalogIO( GPIOF, GPIO_Pin_6 );		//PF6;//VBATCHK
	if( ExtVoltage != 0x55 )
	{
		CloseeIO( GPIOF, GPIO_Pin_11 );	
	}
	else
	{
		AnalogIO( GPIOF, GPIO_Pin_11 );		//PF11;//SVS�ⲿ������
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
		OutputIO( GPIOG, GPIO_Pin_6, 0 );//PG6;//�޹���ʱ�����
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
		InputtIO( GPIOG, GPIO_Pin_9, 1 );	//PG9;//COM_RQ(�ڲ�����)
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
	EEVCCOFF;		//�ر�EE��Դ	
}

void Enable_I2C_IO(void)
{
	OutputIO( GPIOB, GPIO_Pin_11, 0 );	//PB8;//RelayCtrl//EE_V@�������
	EEVCCON;	//��EE��Դ	
	AltFunIO( GPIOA, GPIO_Pin_14, 1 );	//PA14;//SCL
	AltFunIO( GPIOA, GPIO_Pin_15, 1 );	//PA15;//SDA	
}

void Enable_Led_IO(void)
{
	#ifndef __DEBUG
	OutputIO( GPIOG, GPIO_Pin_8, 0 );	//PG8;//LEDRelay
	#endif
}

void Veri_Clk_Gen( void )				//ʱ��ѡ�����
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
	
	if( EA_ON )//��λ�������ʱ�����·����Ȼ���л�С����
	{
		CheckSysReg( &RCC->XTLFIPW	, rtcosccfg );
	}
					
	CheckSysReg( &RCC->PERRCCCON1	, set_PERRCCCON1 );	
	CheckSysReg( &RCC->PERRCCCON2	, set_PERRCCCON2 );
	CheckSysReg( &RCC->PERRCCCON3	, set_PERRCCCON3 );	
	CheckSysReg( &RCC->PERRCCCON4	, set_PERRCCCON4 );		
	CheckSysReg( &RCC->MPRIL	, set_MPRIL );
	CheckSysReg( &ANAC->BORCON	, RunBorCfg );//��BOR
	CheckSysReg( &ANAC->PDRCON	, RunPdrCfg );//��PDR
	
	#ifdef __DEBUG
	CheckSysReg( &SCU->DBGCFG	, 0x00000003 ); //����ʱ���ж�ʱ��
	#else
	CheckSysReg( &SCU->DBGCFG	, 0 );
	#endif
}

//ģ���·�ӿ� 
//��ѹ��� Mode 1 = ��ʼ������	Mode 0 = ����ǰ����
void Veri_SVD_Ctrl( uint08 Mode )				
{
	SVD_InitType	SVD_InitStructure;

	SVD_Disable();
	
	SVD_InitStructure.Interval = ANAC_SVDCFG_SVDITVL_62_5ms;
	SVD_InitStructure.DFEN = ANAC_SVDCFG_DFEN_ENABLE;
	
	if( ExtVoltage != 0x55 )//�ڲ���ѹ���
	{
		SVD_InitStructure.LEVEL = Compile_LvdLvCfg;	
	}
	else//SVS�ⲿ������
	{
		SVD_InitStructure.LEVEL = ANAC_SVDCFG_SVDLVL_SVS;	
	}
	
	NVIC_SetPriority(SVD_IRQn,2);
	if( Mode != 0 )
	{
		SVD_InitStructure.MODE = ANAC_SVDCFG_SVDMOD_ALWAYS_ON;
		NVIC_DisableIRQ(SVD_IRQn);
		ANAC->SVDCFG &= ((~ANAC_SVDCFG_PRIE_Msk)|(~ANAC_SVDCFG_PFIE_Msk));//��svd�ж�
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

void Veri_Btmr1(void)			//�������
{	
	CheckSysReg( &BTIMER1->BTxCFG2	, 0x00000000 );	//EXSEL2 = IN0 EXSEL1 =IN0
	CheckSysReg( &BTIMER1->BTxCFG1	, 0x00000003 );	//Group1�ź�=EXSEL1
	CheckSysReg( &BTIMER1->BTxCR2	, 0x00000020 );	//����Դ=Group1,��λ������Դѡ��10,diren=0��ʹ�÷�������(stdir�ڲ�����������)
//	CheckSysReg( &BTIMER1->BTxCR1	, 0x00000000 );	//
	CheckSysReg( &BTIMER1->BTxIE	, 0x00000008 );	//�򿪵�λ�Ƚ�ƥ���ж�
	
	CheckSysReg( &BTIMER1->BTxOUTCNT, Runet1Outcnt );//
	CheckSysReg( &BTIMER1->BTxOCR	, B0001_0010 );	//���Gropu1�ź�
	CheckSysReg( &BTIMER1->BTxPRES	, 0x00000000 );	//Group1�ź�Ԥ��Ƶ�Ĵ���,00��ʾ1��Ƶ
	
	if( 0 == CheckNvicIrqEn(BT1_IRQn) )//�жϹر�
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
		Decimal.Add = 0;		//����������
	}
	if( BTIMER1->BTxLOADL 	!= 1	)	Result  = 1;
	if( BTIMER1->BTxLOADH 	!= 1	)	Result  = 1;
	if( BTIMER1->BTxPRESET 	!= 0	)	Result  = 1;
	if( Result) 
	{
		BTIMER1->BTxLOADL  = 1;
		BTIMER1->BTxLOADH  = 1;
		BTIMER1->BTxPRESET = 0;
		BTIMER1->BTxLOADCR = 0x00000011;//��λ���غ͵�λ����
	}	
}

void Veri_Btmr2(void)			//�޹��������
{	
	CheckSysReg( &BTIMER2->BTxCFG2	, 0x00000020 );	//EXSEL2 = IN0 EXSEL1 =IN2
	CheckSysReg( &BTIMER2->BTxCFG1	, 0x00000003 );	//Group1�ź�=EXSEL1
	CheckSysReg( &BTIMER2->BTxCR2	, 0x00000020 );	//����Դ=Group1,��λ������Դѡ��10,diren=0��ʹ�÷�������(stdir�ڲ�����������)
//	CheckSysReg( &BTIMER2->BTxCR1	, 0x00000000 );	//
	CheckSysReg( &BTIMER2->BTxIE	, 0x00000008 );	//�򿪵�λ�Ƚ�ƥ���ж�
	
	CheckSysReg( &BTIMER2->BTxOUTCNT	, Runet1Outcnt );	//
	CheckSysReg( &BTIMER2->BTxOCR	, B0001_0010 );//0x0000000A;	//���Gropu1�ź�
	CheckSysReg( &BTIMER2->BTxPRES	, 0x00000000 );	//Group1�ź�Ԥ��Ƶ�Ĵ���,00��ʾ1��Ƶ
	
	if( 0 == CheckNvicIrqEn(BT2_IRQn) )//�жϹر�
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
		Decimal.Add_Rp = 0;		//����������
	}
	if( BTIMER2->BTxLOADL 	!= 1	)	Result  = 1;
	if( BTIMER2->BTxLOADH 	!= 1	)	Result  = 1;
	if( BTIMER2->BTxPRESET 	!= 0	)	Result  = 1;
	if( Result) 
	{
		BTIMER2->BTxLOADL  = 1;
		BTIMER2->BTxLOADH  = 1;
		BTIMER2->BTxPRESET = 0;
		BTIMER2->BTxLOADCR = 0x00000001;//��λ����
	}	
}

//ET2, 4ms��ʱ���ж�
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
		ETIMER2->ETxCR |= 0x00000080;   //������ʱ��
	
	if( 0 == CheckNvicIrqEn(ETIMER2_IRQn) )//�жϹر�
	{
		NVIC_DisableIRQ(ETIMER2_IRQn);
		NVIC_SetPriority(ETIMER2_IRQn,2);
		NVIC_EnableIRQ(ETIMER2_IRQn);		
	}
}

//ET4, 80ms��ʱ���ж�
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
//		ETIMER4->ETxCR |= 0x00000080;   //������ʱ��
	
	if( 0 == CheckNvicIrqEn(ETIMER4_IRQn) )//�жϹر�
	{
		NVIC_DisableIRQ(ETIMER4_IRQn);
		NVIC_SetPriority(ETIMER4_IRQn,1);
		NVIC_EnableIRQ(ETIMER4_IRQn);		
	}
}

unsigned char GetBps( unsigned char Type, unsigned char Bps )
//Type =0:645, 1:698; Bps = 645������ֵ
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
	
	//UART0	//�ز�
	if( Zb_Comm_Timer==0 ) Zbbps = Mode.Zbbps;
	else Zbbps = Mode.Zbbps_Ram;
	Result = GetBps( 0, Zbbps ); //�ز�ͨ��
	CheckSysReg( &UART0->RXSTA		, B0101_0000 );		//8λ����,żУ��,RXEN=1
	CheckSysReg( &UART0->TXSTA		, B0011_0000 );		//1λֹͣλ,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART0->RXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART0->TXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART0->RTXCON		, B0000_0000 );		//�������ݲ�ȡ��,�������ݲ�ȡ��
	if( UpdateBps!=1 ) CheckSysReg( &UART0->SPBRG		, BPS_SPBRGL1[ Result + clkmode%2 ] );
	
	//UART1	//BLE
	if( Ble_Reset == 0xAA )
	{
		Ble_Rst();
		Ble_Reset = 0;
	}
//	Result = GetBps( 0, Mode.blebps ); //����ͨ��
	Result = 7;																			//Ĭ��115200
	CheckSysReg( &UART1->RXSTA		, B0001_0000 );		//8λ����,��У��,RXEN=1
	CheckSysReg( &UART1->TXSTA		, B0011_0000 );		//1λֹͣλ,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART1->RXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART1->TXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART1->RTXCON		, B0000_0000 );		//�������ݲ�ȡ��,�������ݲ�ȡ��
	if( UpdateBps!=1 ) CheckSysReg( &UART1->SPBRG		, BPS_SPBRGL1[ Result + clkmode%2 ] );	
	
	//UART2	//485
	Result = GetBps( 0, Mode.Bps[0] ); //RS485ͨ��
	CheckSysReg( &UART2->RXSTA		, B0101_0000 );		//8λ����,żУ��,RXEN=1
	CheckSysReg( &UART2->TXSTA		, B0011_0000 );		//1λֹͣλ,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART2->RXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART2->TXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
//	CheckSysReg( &UART2->RTXCON		, B0000_0000 );		//�������ݲ�ȡ��,�������ݲ�ȡ��
	if( UpdateBps!=1 ) CheckSysReg( &UART2->SPBRG		, BPS_SPBRGL1[ Result + clkmode%2 ] );	
	
	//UART4	//����
	CheckSysReg( &UART4->RXSTA		, B0101_0000 );		//8λ����,żУ��,RXEN=1
	CheckSysReg( &UART4->TXSTA		, B0011_0000 );		//1λֹͣλ,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART4->RXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART4->TXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART4->RTXCON		, B0000_0000 );		//�������ݲ�ȡ��,�������ݲ�ȡ��
	CheckSysReg( &UART4->SPBRG		, BPS_SPBRGL1[ 2 + clkmode%2 ] );	//4800
	
	//UART5	//����
	CheckSysReg( &UART5->RXSTA		, B0101_0000 );		//1λֹͣλ,TXIS=1,TXEN=1,BRGH=1
	CheckSysReg( &UART5->TXSTA		, B0011_1000 );		//1λֹͣλ,TXIS=1,TXEN=1,BRGH=1,�������ʹ��
	CheckSysReg( &UART5->RXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART5->TXFIFOSTA	, B0000_0000 );	//(����ԭ�ж�)
	CheckSysReg( &UART5->RTXCON		, B0000_0000 );		//�������ݲ�ȡ��,�������ݲ�ȡ��
	CheckSysReg( &UART5->SPBRG		, BPS_SPBRGL1[ clkmode%2 ] );		//1200	
	CheckSysReg( &UART_common->TZBRG , (210*clkmode|(IRDutyCycleCfg)) );//Mclk=8Mʱ38k���� ռ�ձ�Y(73.9%) = (TZBRG[10:4]*TH)/(TZBRG+1)=(13*12)/��210+1��,���������ܷ�����Ϊ26.1%  //������PNP,��TH=4'b0000ʱ,(X[10:1]+1)/(X+1)=106/211
	
	//���������䣺0=���⣬ 1=485�� 2=�ز�
	if ( ((Uart[CHHW].Flag == 0)&&(Uart[CHBLE].Flag == 0)&&(Uart[CH485].Flag == 0)&&(Uart[CHZB].Flag == 0)) || (EA_OFF) )
	{
		CheckSysReg( &UART_common->UARTIE , UART_RX_IE0|UART_RX_IE2|UART_RX_IE5|UART_TX_IE0|UART_RX_IE1 );//ʹ��RXIE2,RXIE1��RXIE0
		R485CTRLR;		//�������
//		if(EA_OFF)
//		{
//			{RXSTA0 = 0;RXSTA0 = B0101_0000;}//��λ���յ�·
//			{RXSTA1 = 0;RXSTA1 = B0101_0000;}//��λ���յ�·
//			{RXSTA2 = 0;RXSTA2 = B0101_0000;}//��λ���յ�·
//			{RXSTA3 = 0;RXSTA3 = B0101_0000;}//��λ���յ�·
//		}
	}

	if( 0 == CheckNvicIrqEn(UART2_IRQn) )//�жϹر�
	{
		NVIC_DisableIRQ(UART2_IRQn);
		NVIC_SetPriority(UART2_IRQn,2);
		NVIC_EnableIRQ(UART2_IRQn);
	}
	if( 0 == CheckNvicIrqEn(UART1_IRQn) )//�жϹر�
	{	
		NVIC_DisableIRQ(UART1_IRQn);
		NVIC_SetPriority(UART1_IRQn,2);
		NVIC_EnableIRQ(UART1_IRQn);	
	}
	if( 0 == CheckNvicIrqEn(UART0_IRQn) )//�жϹر�
	{	
		NVIC_DisableIRQ(UART0_IRQn);
		NVIC_SetPriority(UART0_IRQn,2);
		NVIC_EnableIRQ(UART0_IRQn);	
	}
	if( 0 == CheckNvicIrqEn(UART5_IRQn) )//�жϹر�
	{		
		NVIC_DisableIRQ(UART5_IRQn);
		NVIC_SetPriority(UART5_IRQn,2);
		NVIC_EnableIRQ(UART5_IRQn);		
	}
	
}

void Veri_I2c( void )
{
	CheckSysReg( &I2C->I2CBRG	, 9 );    //I2C������: I2C������: 200K@8MHz, 400k@16MHz
	CheckSysReg( &I2C->I2CIR	, 0 );	//��ֹI2C�ж�
}

void Veri_Spi( void )
{
//	if( (SPCR&B1000_0000) != B0000_0000 ) 	SPCR 	&= B0111_1111;	//��ֹSPI�ж�
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
	CheckSysReg( &RTC->PR1SEN	, RTC_PR1SEN_PR1SEN_ENABLE );	//ʹ�������У���ܣ�ʹ��pll������ȷ1Hz
	CheckSysReg( &RTC->STAMPEN	, RTC_STAMPEN_STAMP0EN_DISABLE | RTC_STAMPEN_STAMP1EN_DISABLE );//�ر�ʱ�������
	
	if( 0 == CheckNvicIrqEn(RTC_IRQn) )//�жϹر�
	{
		NVIC_DisableIRQ(RTC_IRQn);
		NVIC_SetPriority(RTC_IRQn,2);
		NVIC_EnableIRQ(RTC_IRQn);	
	}
}

void Veri_U7816( void )
{
	CheckSysReg( &U7816CTRL0	, DEF_USART0CTRL );
	CheckSysReg( &U7816FRMCTRL0	, DEF_USART0FRC );	//�ط�1��,żУ��,�ȷ�lsb
	CheckSysReg( &U7816EGTCTRL0	, DEF_USART0EGT );
	CheckSysReg( &U7816CLKDIV0	, DEF_USART0CLKDIV+2*(clkmode-1) );	//mclk=16Mʱ7816=4M,mclk=8Mʱ7816=4M
	CheckSysReg( &U7816PREDIV0	, DEF_USART0CLKPDIV );	//1ETU=1/372
	CheckSysReg( &U7816INTEN0	, DEF_USART0IE );	//��ֹ�ж�
	
	CheckSysReg( &U7816CTRL1	, DEF_USART0CTRL );
	CheckSysReg( &U7816FRMCTRL1	, DEF_USART0FRC );	//�ط�1��,żУ��,�ȷ�lsb
	CheckSysReg( &U7816EGTCTRL1	, DEF_USART0EGT );
	CheckSysReg( &U7816CLKDIV1	, DEF_USART0CLKDIV+2*(clkmode-1) );	//mclk=16Mʱ7816=4M,mclk=8Mʱ7816=4M
	CheckSysReg( &U7816PREDIV1	, DEF_USART0CLKPDIV );	//1ETU=1/372
	CheckSysReg( &U7816INTEN1	, DEF_USART0IE );	//��ֹ�ж�
}

//Mode 1 = ��ʼ������	Mode 0 = ���ߵ���
void Veri_Disp( uint08 Mode )
{	
	unsigned char i;
	
	CheckSysReg( &DISP->LCDTEST 	, B0000_0000 );//��ֹ����	
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
			if( Fun_Para.Voltage_P < Sleepvthreshold[i] ) //Ŀǰ����֧��6��̨��
			{
				if( Extbattery == 0x55 ) DISP->LCDBIAS  = Sleeplcdbias[i];
				else DISP->LCDBIAS  = Sleeplcdbias[0];
//				DISP->LCDBIAS  = Sleeplcdbias[0];
				break;
			}
		}
		if( i == 6 ) DISP->LCDBIAS  = Sleeplcdbias[0];
		
//		disp_sleep_flag = 1;//��ͣ����ʾ��־
	}
	
	CheckSysReg( &DISP->COM_EN , 0x0000000F );
	CheckSysReg( &DISP->SEG_EN0 , 0xCC339C3D );
	CheckSysReg( &DISP->SEG_EN1 , 0x00000FFF );
	
	if( Mode != 0 )
		CheckSysReg( &DISP->DISPCTRL ,B1100_0000 );//������ʹ��,����ʾ
	else
		DISP->DISPCTRL |= BIT7;//������ʹ��	
}

void Veri_Wwdt( void )
{
	CheckSysReg( &WWDT->WWDTIE	, 0x01 );  //wwdt�ж�ʹ�ܴ� 			
	
	if( 0 == CheckNvicIrqEn(WWDT_IRQn) )//�жϹر�
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
	Veri_Btmr1();			//�������	
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


////*��Ӧ��ֱ�ӽ���Bit�����ǵ�λ�ȴ��ķ�ʽ(��"���ɶ���ʽ" = 0x8408), ����λ�ȴ�("���ɶ���ʽ" = 0x1021)���±��ʺ�.
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
	buf[len] = Result;		//���ֽ�
	buf[len+1] = Result>>8;		//���ֽ�
}


unsigned char Crc_Check( unsigned char *buf, unsigned char len ) 
{
	if( ChkBufZero(buf,len)==0 ) return 1;	//�������ݾ�Ϊ0,��ΪУ���

	if( Crc_16Bits( buf, len ) ) return 1;	//crcУ�����
	
	return 0;				//У����ȷ
}


unsigned char Verify_para(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len )//һ�ж�����У�麯��
{
	if( Crc_Check( Buf, Len+2 ) == 0 ) return 0;	//ram����crc��ȷ
	
	if( I2C_Read_Eeprom( Page, Inpage, Buf, Len ) == 0 ) return 0;//�Ѿ�������ee���ָ�
	
	if( I2C_Read_Eeprom( Page+1, Inpage, Buf, Len ) != 0 ) return 1;//����ȫ��
	
	I2C_Write_Eeprom( Page, Inpage, Buf, Len );	//������ee���ݻָ�,ͬʱд��
	
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
		memcpy( Temp64_T.B08, buf+i*4, 4 ); //������������
		Temp64.B64 += Temp64_T.B64;//�������������ۼӺ�
	}
	memcpy( Temp64_T.B08, buf, 4 ); //��������
	
	if( Temp64_T.B64 < Temp64.B64 ) return 1; //�ܵ��� < (�����ʺ�), ����
	if( Temp64_T.B64 - Temp64.B64 > Def_Dl_Difference ) return 1; //�ܵ��� > (�����ʺ�+0.xx), ����
	
	return 0;//У����ȷ
}

unsigned char Verify_Dl(unsigned char Page ,unsigned char Inpage, unsigned char *Buf, unsigned char Len )//һ�ж�����У�麯��
{
	if( (Crc_Check( Buf, Len+2 ) == 0) && (Dl_Check( Buf ) == 0) ) return 0;	//ram����crc��ȷ
	
	if( (I2C_Read_Eeprom( Page, Inpage, Buf, Len ) == 0) && (Dl_Check( Buf ) == 0) ) return 0;//�Ѿ�������ee���ָ�
	
	if( (I2C_Read_Eeprom( Page+1, Inpage, Buf, Len ) == 0) && (Dl_Check( Buf ) == 0) )
	{
		I2C_Write_Eeprom( Page, Inpage, Buf, Len );	//������ee���ݻָ�,ͬʱд��
		return 0;
	}
	else  return 1;//����ȫ��
}


void Starttimer_Verify()	//����ʱ��У��
{
	Verify_para( ee_starttimer_page, ee_starttimer_inpage, Starttime.Shiqu, ee_starttimer_lenth );
}

void Esam_Para_Verify()	//�������1,2�Ȳ���(ESAMһ�ಿ�ֲ���)У��
{
#if(ESAMON == 1)	
	unsigned char result;
	unsigned char Buf[32];
	
	if(Verify_para( ee_esampara_page, ee_esampara_inpage, Esam_Para.Current_Ratio, ee_esampara_lenth ))
	{
		memset( Esam_Para.Current_Ratio, 0x00, ee_esampara_lenth );//�Ƿ�Ĭ��
		Esam_Para.Current_Ratio[2] = 1;Esam_Para.Voltage_Ratio[2] = 1;//���1
		Esam_Para.Meter_Id[5] = 0xff;//���0x0000000000ff
		memset( Esam_Para.Zb_Id, 0xff, 6 );//ģ��id(6)
		Esam_Para.Identity_Delay.B08[0] = Defaultauthtimer>>8;//�����֤��Чʱ��
		Esam_Para.Identity_Delay.B08[1] = Defaultauthtimer;//�����֤��Чʱ��
	}
	
	if( EA_OFF ) return;
	if( esam_error ) return;
	if( esam_biaohao_flag ) return;//�Ѳ���esam���
	
	if((identity_prog_flag == 0) && (identity_ir_flag == 0))
	{
		result = EsamReset();//��ȫ��֤��̱�־ʧЧ
		if( result ) return;//��λ����
	}
	
	result = ReadBinFile( ESAM, 0x81, 0x1e, 6 );
	if( result ) return;//�����󷵻�
	
	result = Cmp_Data( Esam_Para.Meter_Id, Ic_Comm_RxBuf, 6 );
	if( result != 3 )
	{
		memcpy( Esam_Para.Meter_Id, Ic_Comm_RxBuf, 6 );//����esam��ŵ�ram
		WriteE2WithBackup(ee_esampara_page, ee_esampara_inpage, Esam_Para.Current_Ratio, ee_esampara_lenth);
	}
	
	result = ReadBinFile( ESAM, 0x85, 0x00, 4 );	//��esam��05�ļ��ظ���Կ״̬
	if( result ) return;//�����󷵻�
	
	Inverse( Ic_Comm_RxBuf, 4 );
	
	I2C_Read_Eeprom44( ee_keystatus_page, Buf, ee_keystatus_lenth );//����Կ״̬
	
	result = Cmp_Data( Buf, Ic_Comm_RxBuf, 4 );
	if( result != 3 )
	{
		memcpy( Buf, Ic_Comm_RxBuf, 4 );//����4�ֽ���Կ״̬
		I2C_Write_Eeprom44( ee_keystatus_page, Buf, ee_keystatus_lenth );//д��Կ״̬
		GetKeyStatus();		//����ǰ��Կ״̬
		FailKey();
	}
	
	esam_biaohao_flag = 1;//���Ѿ�����esam��ű�־
#else
	if(Verify_para( ee_esampara_page, ee_esampara_inpage, Esam_Para.Current_Ratio, ee_esampara_lenth ))
	{
		memset( Esam_Para.Current_Ratio, 0x00, ee_esampara_lenth );//�Ƿ�Ĭ��
		Esam_Para.Current_Ratio[2] = 1;Esam_Para.Voltage_Ratio[2] = 1;//���1
		Esam_Para.Meter_Id[5] = 0xff;//���0x0000000000ff
		Esam_Para.Identity_Delay.B08[0] = Defaultauthtimer>>8;//�����֤��Чʱ��
		Esam_Para.Identity_Delay.B08[1] = Defaultauthtimer;//�����֤��Чʱ��
	}
#endif
}


void Meter_Const_Verify()	//�����У��
{
	Int2Byte( Def_Meterconst_Bcd, Meter.Const.B08);
	Meter.Const_H = Def_Meterconst_Hex;
//	Month_Account_Verify();
}


unsigned char Fwdl_Verify()		//�������У��
{
	fwdl_veri_flag = 0;
	Meter_Const_Verify();
	return(Verify_Dl( ee_fwdl_page, ee_fwdl_inpage, Fwdl.Pluse[0].B08, ee_fwdl_lenth ));//��������β��У��	
}

unsigned char Bkdl_Verify()		//�������У��
{
	bkdl_veri_flag = 0;
	Meter_Const_Verify();
	return(Verify_Dl( ee_bkdl_page, ee_bkdl_inpage, Bkdl.Pluse[0].B08, ee_bkdl_lenth ));//��������β��У��
}

unsigned char Rpdl_Verify( unsigned char i )		//�������޹�����У��
{
	rpdl_veri_flag = 0;
	Meter_Const_Verify();
	return(Verify_Dl( ee_rpdl_page+2*i, ee_rpdl_inpage, Rpdl[i].Pluse[0].B08, ee_rpdl_lenth ));
}

void Mode_Verify()			//����ģʽ��У��
{
	unsigned char Buf[ee_featureword_lenth+2];
	
	mode_veri_flag = 0;
	if( Verify_para( ee_featureword_page, ee_featureword_inpage, Mode.Bps, ee_featureword_lenth ) )
	{
		memcpy( Mode.Bps, Def_featureword_table, ee_featureword_lenth );
	}
	
	if( Mode.Report_Period < 5 )//С��5min��Ĭ��60min
		Mode.Report_Timer = def_meterrun_timer*60;
	else 
		Mode.Report_Timer = Bcd_To_Hex(Mode.Report_Period)*60;
		
	if( (Memoryerr_Ctrl == 0x55) &&	//�洢�������ϱ�����ʹ��
	    ((I2C_Read_Eeprom(ee_featureword_page, ee_featureword_inpage, Buf, ee_featureword_lenth) 
		&& I2C_Read_Eeprom(ee_featureword_page+1, ee_featureword_inpage, Buf, ee_featureword_lenth)) 
		|| (ChkBufZero( Buf, ee_featureword_lenth ) == 0)) )
	{
		if( eeprom_error_flag == 0 )
		{
			Set_Reportdata(0*8+5);//�ô洢�������ϱ���־
		}
		eeprom_error_flag = 1; //�ô洢�����ϱ�־
	}
	else	eeprom_error_flag = 0; //��洢�����ϱ�־
}



void Week_Holiday_Verify()	//�����պ͸��ɲ���У��
{
	if(Verify_para( ee_weekholiday_page, ee_weekholiday_inpage, &Week_Holiday.Status, ee_weekholiday_lenth ))
	{
		memcpy( &Week_Holiday.Status, Def_weekloadpara_table, ee_weekholiday_lenth );
	}
}

void feik_Num_Verify( void ) //ʱ�����Ȳ���У��
{
	if(Verify_para( ee_feik_number_page, ee_feiknumber_inpage, Feik.Num, ee_feiknumber_lenth )) //��ʱ����
	{
		memcpy( Feik.Num, Def_feik_table, ee_feiknumber_lenth );
	}
}

#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У
void Fill_RTC_RT_TAdc(void)//��ȡ���adc����
{
	//�����¶��Զ��ж�д�����ݵĵ�ַ
	uint16 Page;
	uint08 offset;
	uint08 Len;
	uint08 i;

	if( RTC_RT.TempFlag == 0 )//���²��
	{
		Page = ee_ptatvalue_page;
		offset = ee_ptatvalue_inpage;
		Len = ee_ptatvalue_lenth;
		
		if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TAdc.PTAT_Value, Len ))
		{
			memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
		}
		
		return;
	}
	else if( RTC_RT.TempFlag == 1 )//���²��
	{
		Page = ee_ptatvalue_lt_page;
		offset = ee_ptatvalue_lt_inpage;
		Len = ee_ptatvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//���²��
	{
		Page = ee_ptatvalue_ht_page;
		offset = ee_ptatvalue_ht_inpage;
		Len = ee_ptatvalue_ht_lenth+2;
	}
	else
	{
		memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
		return;
	}
	
	I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TAdc.PTAT_Value, Len );
	if( 0 == Crc_Check( (uint08*)RTC_RT.TAdc.PTAT_Value, Len ) )//ee crc��ȷ�����β�����ݲ����¼���crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TAdc.PTAT_Value[i/2] = RTC_RT.TAdc.PTAT_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uint08*)RTC_RT.TAdc.PTAT_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc�������ݷǷ������ff
	{
		memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
	}
}

void Fill_RTC_RT_TVal(void)//��ȡ�����ֵ����
{
	//�����¶��Զ��ж�д�����ݵĵ�ַ
	uint16 Page;
	uint08 offset;
	uint08 Len;
	uint08 i;

	if( RTC_RT.TempFlag == 0 )//���²��
	{
		Page = ee_ptatvalue_page+1;
		offset = ee_ptatvalue_inpage;
		Len = ee_ptatvalue_lenth;
		
		if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TVal.Trim_Value, Len ))
		{
			memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�����
		}
		
		return;
	}
	else if( RTC_RT.TempFlag == 1 )//���²��
	{
		Page = ee_ptatvalue_lt_page+1;
		offset = ee_ptatvalue_lt_inpage;
		Len = ee_ptatvalue_lt_lenth+2;
	}
	else if( RTC_RT.TempFlag == 2 )//���²��
	{
		Page = ee_ptatvalue_ht_page+1;
		offset = ee_ptatvalue_ht_inpage;
		Len = ee_ptatvalue_ht_lenth+2;
	}
	else
	{
		memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�
		return;
	}
	
	I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TVal.Trim_Value, Len );
	if( 0 == Crc_Check( (uint08*)RTC_RT.TVal.Trim_Value, Len ) )//ee crc��ȷ�����β�����ݲ����¼���crc
	{
		for(i=Len-2;i<ee_ptatvalue_lenth;i=i+2)
		{
			RTC_RT.TVal.Trim_Value[i/2] = RTC_RT.TVal.Trim_Value[(Len-2)/2 - 1];
		}
		Crc_16Bits_Add2((uint08*)RTC_RT.TVal.Trim_Value, ee_ptatvalue_lenth);
	}
	else				//ee crc�������ݷǷ������ff
	{
		memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�����ff
	}
}
#else
void Fill_RTC_RT_TAdc(void)//��ȡ���adc����
{
	//�����¶��Զ��ж�д�����ݵĵ�ַ
	uint16 Page;
	uint08 offset;
	uint08 Len;

	Page = ee_ptatvalue_page;
	offset = ee_ptatvalue_inpage;
	Len = ee_ptatvalue_lenth;
		
	if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TAdc.PTAT_Value, Len ))
	{
		memset( (uint08*)RTC_RT.TAdc.PTAT_Value, 0xff, ee_ptatvalue_lenth );//�Ƿ�����ff
	}
		
	return;
}

void Fill_RTC_RT_TVal(void)//��ȡ�����ֵ����
{
	//�����¶��Զ��ж�д�����ݵĵ�ַ
	uint16 Page;
	uint08 offset;
	uint08 Len;

	Page = ee_ptatvalue_page+1;
	offset = ee_ptatvalue_inpage;
	Len = ee_ptatvalue_lenth;
		
	if(I2C_Read_Eeprom( Page, offset, (uint08*)RTC_RT.TVal.Trim_Value, Len ))
	{
		memset( (uint08*)RTC_RT.TVal.Trim_Value, 0x00, ee_ptatvalue_lenth );//�Ƿ�����
	}
		
	return;
}
#endif

void Temperpara_Verify()	//�¶�ϵ��У��
{
	temperpara_veri_flag = 0;
	if(Verify_para( ee_temperature_page, ee_temperature_inpage, Tpara.Offset, ee_temperature_lenth ))
	{
		memset( Tpara.Offset, 0x00, ee_temperature_lenth );//Ĭ��Ϊ0 
		Tpara.Offset[0]	= 0x80;
	}
	if( Tpara.RtcTMode == 0xAA )//0xAA���²���ֵģʽ
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


void Commaddr_Verify()		//ͨѶ��ַУ��
{
	addr_veri_flag = 0;
	if( Verify_para( ee_commaddr_page, ee_commaddr_inpage, Comm_Addr.Comm_Id, ee_commaddr_lenth ) )
	{
		memset( Comm_Addr.Comm_Id, 0x00, 6 );//ͨѶ��ַĬ��Ϊ01
		Comm_Addr.Comm_Id[5] = 0x01;
	}
	
	//��ѹ�ϸ��ʵ���ز���У��
	if( Verify_para( ee_vollimit_page, ee_vollimit_inpage, VolLimit.MaxVolLmt.B08, ee_vollimit_lenth ) )
	{
		memcpy( VolLimit.MaxVolLmt.B08, Def_vollmtpara_table, ee_vollimit_lenth );
	}
}


void Display_Para_Verify()	//��ʾ����У��
{
	disppm_veri_flag = 0;
	if( Verify_para( ee_displaypara_page, ee_displaypara_inpage, &Display_Para.S_Number, ee_displaypara_lenth ) )
	{
		memcpy( &Display_Para.S_Number, Def_DisplayPara_table, ee_displaypara_lenth );
	}
	Hw_Lcdled_Timer = Display_Para.Loop_Time*Display_Para.S_Number*2;
}


void Displayitem_Verify()	//��ʾ��ĿУ��(һ��һ)
{
	unsigned char i,j,result,len;
	
	dispitem_veri_flag = 0;
	
	for( i=0; i<2; i++ )
	{		
		if( Crc_Check( (unsigned char*)Item[i].Display, ee_displayitem_lenth*3+ee_displayitem_lenth1+2 ) == 0 ) continue;//ram����crc��ȷ
		
		//��ѭ����ʾ��Ż��߰�����ʾ���
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
		
		if( result || (ChkBufZero( (unsigned char*)Item[i].Display, ee_displayitem_lenth*3+ee_displayitem_lenth1 ) == 0) ) //���ݷǷ�����Ĭ�ϵ���ʾ
		{
		    	for( j=0; j<20; j++ )
			{
				Item[i].Display[j] = j+0x201;	//512+1(0x201)��ʾ��ͨ��ϵ���  1024+1(0x401)��ʾ�߾�����ϵ���(Ԥ��)
			}
		}
		else
		{
			Crc_16Bits_Add2( (unsigned char*)Item[i].Display, ee_displayitem_lenth*3+ee_displayitem_lenth1 );	 //CRC����
		}
	}
}
