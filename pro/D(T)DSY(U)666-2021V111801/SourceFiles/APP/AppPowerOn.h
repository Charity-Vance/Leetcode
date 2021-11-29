/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    AppPowerOn.h                                                                         
**** Brief:       上电系统配置                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019年3月14日                                                                         
****                                                                                                 
**** note:修改历史记录列表，每条修改记录应包括修改日期、修改者                                          
**** 1.  Author:                                                                                     
****     Version:                                                                                    
****     Date :                                                                                      
**** 2.  Author:                                                                                     
****     Version:                                                                                       
****     Date:
****                                                                                        
****  addtogroup:Library                                                             
**********************************************************************************************************/

#ifndef   _APPPOWERON_H
#define   _APPPOWERON_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
*/

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/

#define	WDT_Clr()		do{ RSTSTAT = 0x00; } while(0);		// 清硬件看门狗，看门狗定时周期我4s 
#define	MCU_RST()		do{ RSTSTAT = 0x07; (*((void(code*)(void))0x0000))(); }  while(0);// 单片机软复位
#define	DIS_ALL_INT()	do{ IEN0 = 0x00; IEN1 = 0x00; } while(0);	
#define	ENTER_POWERDWN()	do{	SUSLO = 0X55;	PCON |= _BIT1; NOP();NOP();NOP(); } while(0);

#define DI()		{ EA=0; }
#define EI()		{ EA=1; }
#define NOP()		{ _nop_(); }

#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define	UART0_IOCFG_RXD()	{ GPIO_IOCFG_P2_DIR_I(6);	GPIO_IOCFG_P2_PUP_F(6); }	// 485RXD 设置成输入，开启上拉
	#define	UART0_IOCFG_TXD()	{ GPIO_IOCFG_P2_DIR_O(7);	GPIO_IOCFG_P2_SET_1(7); }	// 485TXD 设置成输出，初始输出高

	#define	UART1_IOCFG_RXD()	{ GPIO_IOCFG_P3_DIR_I(0);	GPIO_IOCFG_P3_PUP_F(0); }	// BT_RXD 设置成输入，开启上拉
	#define	UART1_IOCFG_TXD()	{ GPIO_IOCFG_P3_DIR_O(1);	GPIO_IOCFG_P3_SET_1(1); }	// BT_TXD 设置成输出，初始输出高
#endif
	
#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	UART0_IOCFG_RXD()	{ GPIO_IOCFG_P2_DIR_I(6);	GPIO_IOCFG_P2_PUP_F(6); }	// 485RXD 设置成输入，开启上拉
	#define	UART0_IOCFG_TXD()	{ GPIO_IOCFG_P2_DIR_O(7);	GPIO_IOCFG_P2_SET_1(7); }	// 485TXD 设置成输出，初始输出高

	#define	UART1_IOCFG_RXD()	{ GPIO_IOCFG_P3_DIR_I(0);	GPIO_IOCFG_P3_PUP_F(0); }	// BT_RXD 设置成输入，开启上拉
	#define	UART1_IOCFG_TXD()	{ GPIO_IOCFG_P3_DIR_O(1);	GPIO_IOCFG_P3_SET_1(1); }	// BT_TXD 设置成输出，初始输出高
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	UART0_IOCFG_RXD()	{ GPIO_IOCFG_P2_DIR_I(6);	GPIO_IOCFG_P2_PUP_F(6); }	// 485RXD 设置成输入，开启上拉
	#define	UART0_IOCFG_TXD()	{ GPIO_IOCFG_P2_DIR_O(7);	GPIO_IOCFG_P2_SET_1(7); }	// 485TXD 设置成输出，初始输出高

	#define	UART1_IOCFG_RXD()	{ GPIO_IOCFG_P3_DIR_I(0);	GPIO_IOCFG_P3_PUP_F(0); }	// BT_RXD 设置成输入，开启上拉
	#define	UART1_IOCFG_TXD()	{ GPIO_IOCFG_P3_DIR_O(1);	GPIO_IOCFG_P3_SET_1(1); }	// BT_TXD 设置成输出，初始输出高
#endif 	
// CLKCON 具体操作要看数据手册
#define	CLKCON_32K_SPDUP		_BIT7
#define	CLKCON_CLKS6			_BIT6
#define	CLKCON_CLKS5			_BIT5
#define	CLKCON_SCMF				_BIT4
#define	CLKCON_HFON				_BIT3
#define	CLKCON_CLKSEL			_BIT2
#define	CLKCON_CLKS2			_BIT1
#define	CLKCON_HFSEL			_BIT0
// 系统时钟预分频器选择
#define	CLKCON_FSYS_FOSCS		0x00				// 00： fSYS = fOSCS
#define	CLKCON_FSYS_FOSCS_2		_BIT5				// 01： fSYS = fOSCS/2
#define	CLKCON_FSYS_FOSCS_4		_BIT6				// 10： fSYS = fOSCS/4
#define	CLKCON_FSYS_FOSCS_8		(_BIT6 | _BIT5)		// 11： fSYS = fOSCS/12
#define	CLKCON_FSYS_FOSCS_ALL	(_BIT6 | _BIT5)	
#define	CLKCON_FSYS_FOSCS_CLR	(~(_BIT6 | _BIT5))

#define	CLKCON_WR_ENABLE()	{ OSCLO = 0x55 ;}	

#define	PASLO_POWER_SWITCH_ON()		{ PASLO = 0X55; }		// 电源切换控制

// PWRCON1 电源控制寄存器1 
#define	PWRCON1_VOUTS2		_BIT2	
#define	PWRCON1_VOUTS1		_BIT1
#define	PWRCON1_AUTOS		_BIT0
// 供电电源状态
#define	PWRCON1_VDD2VOUT	0x00
#define	PWRCON1_VBAT2VOUT	(PWRCON1_VOUTS2 | PWRCON1_VOUTS1) // 非0都可以
#define	PWRCON1_VFCAP2VOUT	(PWRCON1_VOUTS1 ) //  

// PWRCON2 电源控制寄存器2 
#define	PWRCON2_LDO28ON		_BIT7 		// 2.8V LDO电路开关控制，0： 关闭 1： 打开
#define	PWRCON2_LCDLDO1		_BIT6 		// LCDLDO电压调节
#define	PWRCON2_LCDLDO0		_BIT5		// LCDLDO电压调节
#define	PWRCON2_VDDDISC		_BIT4		// VDD 负载开关控制
//LCDLDO电压调节
#define	PWRCON2_LCDLDO_300	0x00
#define	PWRCON2_LCDLDO_295	_BIT5
#define	PWRCON2_LCDLDO_305	_BIT6
#define	PWRCON2_LCDLDO_301	( _BIT6 | _BIT5 )

// LPDCON1
#define	LPDCON1_LPD1EN		_BIT7
#define	LPDCON1_FVIN		_BIT6
#define	LPDCON1_LPD1IF		_BIT5
#define	LPDCON1_FVDD		_BIT4
#define	LPDCON1_LPD1SF		_BIT3
#define	LPDCON1_VINITM2		_BIT2 
#define	LPDCON1_VINITM1		_BIT1

// LPDCON2
#define	LPDCON2_LPD2EN		_BIT7
#define	LPDCON2_LPD2F		_BIT6
#define	LPDCON2_LPD3EN		_BIT5
#define	LPDCON2_LPDS3		_BIT3
#define	LPDCON2_LPDS2		_BIT2
#define	LPDCON2_LPDS1		_BIT1
#define	LPDCON2_LPDS0		_BIT0
// LPD2电压检测等级

#define	LPDCON2_LPDS_255	(~(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS1 | LPDCON2_LPDS0) )	// 0000: 2.55 V
#define	LPDCON2_LPDS_270	LPDCON2_LPDS0														// 0001: 2.70 V
#define	LPDCON2_LPDS_285	LPDCON2_LPDS1														// 0010: 2.85 V
#define	LPDCON2_LPDS_300	(LPDCON2_LPDS1 | LPDCON2_LPDS0)										// 0011: 3.00 V
#define	LPDCON2_LPDS_315	LPDCON2_LPDS2														// 0100: 3.15 V
#define	LPDCON2_LPDS_330	(LPDCON2_LPDS2 | LPDCON2_LPDS0)										// 0101: 3.30 V
#define	LPDCON2_LPDS_345	(LPDCON2_LPDS2 | LPDCON2_LPDS1)										// 0110: 3.45 V
#define	LPDCON2_LPDS_360	(LPDCON2_LPDS2 | LPDCON2_LPDS1 | LPDCON2_LPDS0)						// 0111: 3.60 V
#define	LPDCON2_LPDS_375	LPDCON2_LPDS3														// 1000: 3.75 V
#define	LPDCON2_LPDS_390	(LPDCON2_LPDS3 | LPDCON2_LPDS0)										// 1001: 3.90 V
#define	LPDCON2_LPDS_405	(LPDCON2_LPDS3 | LPDCON2_LPDS1)										// 1010: 4.05 V
#define	LPDCON2_LPDS_420	(LPDCON2_LPDS3 | LPDCON2_LPDS1 | LPDCON2_LPDS0)						// 1011: 4.20 V
#define	LPDCON2_LPDS_435	(LPDCON2_LPDS3 | LPDCON2_LPDS2)										// 1100: 4.35 V
#define	LPDCON2_LPDS_450	(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS0)						// 1101: 4.50 V
#define	LPDCON2_LPDS_465	(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS1)						// 111X: 4.65 V
#define	LPDCON2_LPDS_ALL	(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS1 | LPDCON2_LPDS0)		// 所有位
#define	LPDCON2_LPDS_CLR	(~(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS1 | LPDCON2_LPDS0) )	// 所有位 清零，注意使用&操作符

// 定时器
// TMOD
#define	TMOD_GATE1			_BIT7
#define	TMOD_CT1			_BIT6
#define	TMOD_M11			_BIT5
#define	TMOD_M10			_BIT4
#define	TMOD_GATE0			_BIT3
#define	TMOD_CT0			_BIT2
#define	TMOD_M01			_BIT1
#define	TMOD_M00			_BIT0

#define	TMOD_T0_MODE0		(~(_BIT1 | _BIT0))	// 00： 方式0， 13位向上计数计数器/定时器， 忽略TLx的第7-5位
#define	TMOD_T0_MODE1		_BIT0				// 01： 方式1， 16位向上计数计数器/定时器
#define	TMOD_T0_MODE2		_BIT1				// 10： 方式2， 8位自动重载向上计数计数器/定时器
#define	TMOD_T0_MODE3		(_BIT1 | _BIT0)		// 11： 方式3（只用于定时器0） ， 两个8位向上计数定时器
#define	TMOD_T0_MODE_ALL	(_BIT1 | _BIT0)		// 11:  所有位
#define	TMOD_T0_MODE_CLR	(~(_BIT1 | _BIT0))	// 00 所有位清零，注意要用&操作符

#define	TMOD_T1_MODE0		0x00 			// 00： 方式0， 13位向上计数计数器/定时器， 忽略TLx的第7-5位
#define	TMOD_T1_MODE1		_BIT4			// 01： 方式1， 16位向上计数计数器/定时器
#define	TMOD_T1_MODE2		_BIT5			// 10： 方式2， 8位自动重载向上计数计数器/定时器
#define	TMOD_T1_MODE_ALL	(  TMOD_T1_MODE1 | TMOD_T1_MODE2))	// 11: 所有位
#define	TMOD_T1_MODE_CLR	(~(TMOD_T1_MODE1 | TMOD_T1_MODE2))	// 00: 所有位清零，注意要用&操作符

// TCON
#define	TCON_TF1		_BIT7
#define	TCON_TR1		_BIT6
#define	TCON_TF0		_BIT5
#define	TCON_TR0		_BIT4

// TCON1
#define	TCON1_TCLKS1	_BIT6
#define	TCON1_TCLKS0	_BIT5
#define	TCON1_TCLKP1	_BIT3
#define	TCON1_TCLKP0	_BIT2
#define	TCON1_TC1		_BIT1
#define	TCON1_TC0		_BIT0

// 定时器0 模式1 定时节拍宏定义 Xms @8Mhz
//#define	T_Xms_TL0		0x80	// 65536-8000000*0.002=49536
//#define	T_Xms_TH0		0xC1
#define	T_Xms_TL0		0xC0	// 65536-8000000*0.001=57536
#define	T_Xms_TH0		0xE0
// IEN0
#define IEN0_EA			_BIT7
#define IEN0_EADTP		_BIT6
#define IEN0_ET2		_BIT5
#define IEN0_ES0		_BIT4
#define IEN0_ET1		_BIT3 
#define IEN0_ET0		_BIT1
#define IEN0_EX4		_BIT0 

#define START_TR0()		do{ if( TCON_TR0 != (TCON & TCON_TR0) ) {TCON |= TCON_TR0;} }while(0);
#define STOP_TR0()		do{ if( 0x00 != (TCON & TCON_TR0) )   { TCON &= ~TCON_TR0;} }while(0);

// IEN1
#define IEN1_ES3		_BIT7
#define IEN1_ELPD		_BIT5
#define IEN1_ES1		_BIT2
#define IEN1_ERTC		_BIT1 
#define IEN1_EEMU		_BIT0 

#define	EN_LPD_INT()	( IEN1 |=  IEN1_ELPD )
#define	DIS_LPD_INT()	( IEN1 &= ~IEN1_ELPD )
// T2CON
#define T2CON_TF2			_BIT7
#define T2CON_EXF2			_BIT6
#define T2CON_EXEN2			_BIT3
#define T2CON_TR2			_BIT2
#define T2CON_CT2			_BIT1
#define T2CON_CP_RL2		_BIT0 

// ADCON
#define	ADCON_ADON			_BIT7
#define	ADCON_ADCIF			_BIT6
#define	ADCON_TPSCON		_BIT5
#define	ADCON_SCH3			_BIT4
#define	ADCON_SCH2			_BIT3
#define	ADCON_SCH1			_BIT2
#define	ADCON_SCH0			_BIT1
#define	ADCON_GO_DONE		_BIT0 



// EUART0 寄存器
// PCON 电源控制寄存器
#define	PCON_SMOD			_BIT7
#define	PCON_SSTAT			_BIT6
#define	PCON_SSTAT1			_BIT5
#define	PCON_SSTAT2			_BIT4
#define	PCON_GF1			_BIT3
#define	PCON_GF0			_BIT2
#define	PCON_PD				_BIT1
#define	PCON_IDL			_BIT0

// SCON EUART0控制及状态寄存器
#define	SCON_SM0_FE			_BIT7
#define	SCON_SM1_RXOV		_BIT6
#define	SCON_SM2_TXCOL		_BIT5
#define	SCON_REN			_BIT4
#define	SCON_TB8			_BIT3
#define	SCON_RB8			_BIT2
#define	SCON_TI				_BIT1
#define	SCON_RI				_BIT0 

// SCON1 EUART1控制及状态寄存器 
#define	SCON1_SM10_FE		_BIT7
#define	SCON1_SM11_RXOV		_BIT6
#define	SCON1_SM12_TXCOL	_BIT5
#define	SCON1_REN1			_BIT4
#define	SCON1_TB81			_BIT3
#define	SCON1_RB81			_BIT2
#define	SCON1_TI1			_BIT1
#define	SCON1_RI1			_BIT0 

// SCON3 EUART3控制及状态寄存器
#define	SCON3_SM30			_BIT7
#define	SCON3_SM31			_BIT6
#define	SCON3_SM33			_BIT5
#define	SCON3_REN3			_BIT4
#define	SCON3_TB83			_BIT3
#define	SCON3_RB38			_BIT2
#define	SCON3_TI3			_BIT1
#define	SCON3_RI3			_BIT0 


// 计量相关寄存器
// EMUSR EMU状态/控制寄存器
// 注： DSPEN = 0时， 将功率， 有效值计算部份清零， 参数配置， 以及电能累加部分保持不变。
#define	EMUSR_DSPEN			_BIT7	// 计量模块计算使能 0： 禁止 1： 允许
#define	EMUSR_EMUCLKS1		_BIT6	// EMU模块时钟控制信号
#define	EMUSR_EMUCLKS0		_BIT5
	// emu时钟配置
	#define	EMUSR_CLK_OFF		(~(_BIT6|_BIT5) )	//	00： 关闭EMU的时钟输入
	#define	EMUSR_CLK_32K		_BIT5				//	01： 选择32K时钟作为EMU模块工作时钟
	#define	EMUSR_CLK_RC8M		_BIT6				//	10： 选择并使能RC8M时钟作为EMU模块工作时钟
	#define	EMUSR_CLK_PLL		  (_BIT6|_BIT5)		//	11： 选择并使能PLL时钟作为EMU模块工作时钟
	#define	EMUSR_CLK_CLR		(~(_BIT6|_BIT5) )
	
// 只读
#define	EMUSR_SAGF			_BIT4	// 失压状态标志0： 正常状态 1： 失压状态
#define	EMUSR_NoQLd         _BIT3	// 无功功率不累计标志0： 无功功率大于等于起动功率 1： 无功功率小于起动功率
#define	EMUSR_NoPLd         _BIT2	// 有功功率不累计标志0： 有功功率大于等于起动功率 1： 有功功率小于起动功率
#define	EMUSR_REVQ          _BIT1	// 反向无功电能标志 0： 正无功电能 1： 负无功电能
#define	EMUSR_REVP          _BIT0	// 反向有功电能标志 0： 正有功电能 1： 负有功电能
// EMUIE  EMU中断系统
#define	EMUIE_DIMIE			_BIT6	// DIMMER 检测中断允许位
#define	EMUIE_DSPIE			_BIT5	// DSP执行结束中断允许位
#define	EMUIE_QFIE			_BIT4	// 无功脉冲溢出中断允许位
#define	EMUIE_PFIE			_BIT3	// 有功脉冲溢出中断允许位
#define	EMUIE_SAMPIE		_BIT2	// 波形采样中断允许位
#define	EMUIE_SAGIE			_BIT1	// 失压中断允许位
#define	EMUIE_ZXIE			_BIT0	// 过零中断允许位
// EMUIF  EMU中断请求寄存器
#define	EMUIF_DIMIF			_BIT6	// DIMMER 检测中断标志
#define	EMUIF_DSPIF			_BIT5	// DSP执行结束中断标志
#define	EMUIF_QFIF			_BIT4	// 无功脉冲溢出中断标志
#define	EMUIF_PFIF			_BIT3	// 有功脉冲溢出中断标志
#define	EMUIF_SAMPIF		_BIT2	// 波形采样中断标志
#define	EMUIF_SAGIF			_BIT1	// 失压中断标志
#define	EMUIF_ZXIEF			_BIT0	// 过零中断标志
// EMUAFR 中断请求寄存器2 
#define	EMUAFR_SUMIE		_BIT7	// 累加周期中断允许位
#define	EMUAFR_SUMIF		_BIT3	// 累加周期中断请求标志

// EMUCFG0 EMU计量配置寄存器0（3字节） 间接寻址 
#define	EMUCFG0_ADCCKSEL1	_BIT20	// ADC工作时钟分频选择 EMUCLKS=01时： 固定为32K
#define	EMUCFG0_ADCCKSEL0	_BIT19	
	#define EMUCFG0_ADCCK_32K	0x00 // ADC选择32K
#define	EMUCFG0_APGAU0		_BIT8	// 电压通道0模拟PGA增益选择 0： 2倍增益(默认) 1： 4倍增益
#define	EMUCFG0_APGAI21		_BIT7	// 电流通道2模拟PGA增益选择
#define	EMUCFG0_APGAI20		_BIT6
	#define EMUCFG0_APGAI_16 ( _BIT7 | _BIT6 ) // 16倍
#define	EMUCFG0_APGAI11		_BIT5	// 电流通道1模拟PGA增益选择
#define	EMUCFG0_APGAI10		_BIT4
#define	EMUCFG0_INPUTSHORT	_BIT3	// 通道输入引脚内部短接到地
#define	EMUCFG0_ADCUON		_BIT2	// 电压通道的ADC使能控制  0： 关闭ADC(默认) 1： 打开ADC
#define	EMUCFG0_ADCI2ON		_BIT1	// 电流通道2的ADC使能控制 0： 关闭ADC(默认) 1： 打开ADC
#define	EMUCFG0_ADCI1ON		_BIT0	// 电流通道1的ADC使能控制 0： 关闭ADC(默认) 1： 打开ADC


// EMUCFG1 EMU计量配置寄存器1（3字节） 间接寻址 
#define	EMUCFG1_POL				_BIT23	// PF/QF输出极性控制 0： 高电平有效(默认) 1： 低电平有效
#define	EMUCFG1_QFEN			_BIT22	// 无功脉冲QF引脚输出控制 0：禁止  1：允许
#define	EMUCFG1_PFEN			_BIT21	// 有功脉冲PF引脚输出控制 0：禁止  1：允许
#define	EMUCFG1_MNL				_BIT20	// 掉零线模式使能控制 0：关闭 1：允许
#define	EMUCFG1_DCCON1			_BIT19	// 直流将控制
#define	EMUCFG1_DCCON0			_BIT18
#define	EMUCFG1_HPFON			_BIT17	// 通道高通滤波器选择 0:打开（默认） 1：关闭
#define	EMUCFG1_PWidth1			_BIT16	// 输出脉冲宽度:
#define	EMUCFG1_PWidth0			_BIT15
	#define EMUCFG1_PWidth_45ms _BIT15	// 45ms
#define	EMUCFG1_PFAST1			_BIT14	// 小信号脉冲加速选择
#define	EMUCFG1_PFAST0			_BIT13
#define	EMUCFG1_QMOD1			_BIT12	// 无功电能累加方式选择
#define	EMUCFG1_QMOD0			_BIT11
#define	EMUCFG1_PMOD1			_BIT10	// 有功电能累加方式选择
#define	EMUCFG1_PMOD0			_BIT9
#define	EMUCFG1_RMSLPFENB		_BIT8	// 有效值数据经过低通使能 0：使能 1：禁止
#define	EMUCFG1_QRUN			_BIT7	// 无功能量累加使能 0： 停止 1：允许
#define	EMUCFG1_PRUN			_BIT6	// 有功能量累加使能 0： 停止 1：允许
#define	EMUCFG1_PWRSEL1			_BIT5	// 计量通道选择:
#define	EMUCFG1_PWRSEL0			_BIT4	// 
#define	EMUCFG1_CONST_EN		_BIT3	// 常数计量模式控制 0：关闭 1：打开
#define	EMUCFG1_CmodeFreq1		_BIT2	// 累加频率选择
#define	EMUCFG1_CmodeFreq0		_BIT1	// 
#define	EMUCFG1_Cmodeen			_BIT0	// 累加模块总使能: 0 关闭（默认） 1：打开

// EMUCFG2 EMU计量配置寄存器1（3字节） 间接寻址 
#define	EMUCFG2_ADCRST_U			_BIT14	// 电压通道模拟ADC复位控制
#define	EMUCFG2_ADCRST_I2			_BIT13	// 电流通道2模拟ADC复位控制
#define	EMUCFG2_ADCRST_I1			_BIT12	// 电流通道1模拟ADC复位控制
#define	EMUCFG2_VREF_BUFFER_CURS1	_BIT11	// VREF Buffer电流调节
#define	EMUCFG2_VREF_BUFFER_CURS0	_BIT10	// 
#define	EMUCFG2_PGA_CURS4			_BIT9	//  PGA电流调节
#define	EMUCFG2_PGA_CURS3			_BIT8	// 
#define	EMUCFG2_PGA_CURS2			_BIT7	// 
#define	EMUCFG2_PGA_CURS1			_BIT6	// 
#define	EMUCFG2_PGA_CURS0			_BIT5	// 
#define	EMUCFG2_ADC_CURS4			_BIT4	// ADC电流调节
#define	EMUCFG2_ADC_CURS3			_BIT3	// 
#define	EMUCFG2_ADC_CURS2			_BIT2	// 
#define	EMUCFG2_ADC_CURS1			_BIT1	// 
#define	EMUCFG2_ADC_CURS0			_BIT0	// 

// EMUCFG3 EMU计量配置寄存器1（3字节） 间接寻址 
#define	EMUCFG3_PD_BG				_BIT8
#define	EMUCFG3_EN_BG_CHOP			_BIT7
#define	EMUCFG3_BG_CHOPCK_SEL1		_BIT5
#define	EMUCFG3_BG_CHOPCK_SEL0		_BIT4
/*----------------< 变量声明 >----------------------------------*/


/*----------------< 函数声明 >----------------------------------*/
extern void    ApiPwOn_BleInit(void);
extern void    ApiPwOn_SysClkInit(void);
extern void    ApiPwOn_McuReset(void);
extern uchar8  ApiPwOn_SysTemInit(void);
extern void    ApiPwOn_UART_SendEn(uchar8 v_ucChID);
extern void    ApiPwOn_McuUartXInit(uchar8 v_ucChID); 
extern void    ApiPwOn_MeterInitInFactory(void);
extern void    ApiPwOn_MeterClear(void);
extern void    ApiPwOn_MeterInfoParaCheck(void);
extern void    ApiPwOn_EventPointCheck(void);
extern void    ApiPwOn_DLXS_READ(GStr_ENERGY_PULSE_Type *p_strEnergyPulse,ushort16 v_usAddrIndex );
extern void    ApiPwOn_EnergyCheck(void);
extern void    ApiPwOn_DisplayParaCheck(void);
extern void    ApiPwOn_MoneyParaCheck(void);
extern void    ApiPwOn_EmuParaCheck(void);
extern uchar8  ApiPwOn_EnergyZSCheck(void);
extern void    ApiPwOn_FunConfigParaCheck(void);
extern uchar8  ApiPwOn_PowerChk( void );
extern void    ApiPwOn_McuTimerInit(void);
extern void    ApiPwOn_KeyStatusCheck(void);
extern void    ApiPwOn_BleParaChk(void);
#endif

