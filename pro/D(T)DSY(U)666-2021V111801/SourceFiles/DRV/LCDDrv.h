/*******************************************************************************************************
**** Copyright：  (c)Copyright 2019,浙江正泰仪器仪表有限责任公司,电能表应用研发                       
****                            All rights reserved.                                                 
**** FileName:    LCDDrv.h                                                                          
**** Brief:       LCD驱动头文件                                                                     
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

#ifndef   _LCDDRV_H
#define   _LCDDRV_H

/*-------------------------------- H文件使用说明 -------------------------------------------------------*/
/*
 *  该文件宏定义的前缀为:
 *
 */

 
/*----------------< 包含文件 >----------------------------------*/


/*----------------< 宏定义区 >----------------------------------*/

// LCD显示相关寄存器
// LCDCON1 LCD控制寄存器
#define	LCDCON1_LCDON		_BIT7	// LCD 开关控制位 0： 禁止LCD驱动器 1： 允许LCD驱动器
#define	LCDCON1_DUTY2		_BIT6	// LCD 占空比驱动器
#define	LCDCON1_DUTY1		_BIT5	// LCD 占空比驱动器
#define	LCDCON1_DUTY0		_BIT4	// LCD 占空比驱动器
#define	LCDCON1_BIAS		_BIT3	// LCD BIAS选择位
#define	LCDCON1_CONTR2		_BIT2	// LCD LCD对比度控制位
#define	LCDCON1_CONTR1		_BIT1	// LCD LCD对比度控制位
#define	LCDCON1_CONTR0		_BIT0	// LCD LCD对比度控制位
// 占空比说明
#define	LCDCON1_D14_B13_P4		(~(LCDCON1_DUTY2 | LCDCON1_DUTY1 | LCDCON1_DUTY0 ) )	// 000： 1/4占空比， 推荐1/3偏置， P4.4-P4.7作为COM1-4
#define	LCDCON1_D14_B13_P9		LCDCON1_DUTY0											// 001： 1/4占空比， 推荐1/3偏置， P9.7-P9.4作为COM1-4
#define	LCDCON1_D16_B13_P4		LCDCON1_DUTY1											// 010： 1/6占空比， 推荐1/3偏置， P4.4-P4.7、 P5.0-P5.1作为COM1-6
#define	LCDCON1_D16_B13_P9		( LCDCON1_DUTY1 | LCDCON1_DUTY0 ) 						// 011： 1/6占空比， 推荐1/3偏置， P9.7-P9.2作为COM1-6
#define	LCDCON1_D18_B14_P4		LCDCON1_DUTY2											// 100： 1/8占空比， 推荐1/4偏置， P4.4-P4.7、 P5.0-P5.3作为COM1-8
#define	LCDCON1_D18_B14_P9		( LCDCON1_DUTY2 | LCDCON1_DUTY0 )						// 101： 1/8占空比， 推荐1/4偏置， P9.7-P9.0作为COM1-8
#define	LCDCON1_DBP_ALL			( LCDCON1_DUTY2 | LCDCON1_DUTY1 | LCDCON1_DUTY0 )		// 所有位
#define	LCDCON1_DBP_CLR			(~(LCDCON1_DUTY2 | LCDCON1_DUTY1 | LCDCON1_DUTY0 ) )	// 所有位清零，注意要用&操作符

// 对比对说明
#define	LCDCON1_VOUT600		(~(LCDCON1_CONTR2 | LCDCON1_CONTR1 | LCDCON1_CONTR0 ) )	// 000： VLCD = 0.600 VOUT
#define	LCDCON1_VOUT660		LCDCON1_CONTR0											// 001： VLCD = 0.660 VOUT
#define	LCDCON1_VOUT720		LCDCON1_CONTR1 											// 010： VLCD = 0.720 VOUT
#define	LCDCON1_VOUT780		( LCDCON1_CONTR1 | LCDCON1_CONTR0 )						// 011： VLCD = 0.780 VOUT
#define	LCDCON1_VOUT840		LCDCON1_CONTR2 											// 100： VLCD = 0.840 VOUT
#define	LCDCON1_VOUT900		( LCDCON1_CONTR2 | LCDCON1_CONTR0 )						// 101： VLCD = 0.900 VOUT
#define	LCDCON1_VOUT960		( LCDCON1_CONTR2 | LCDCON1_CONTR1 )						// 110： VLCD = 0.960 VOUT
#define	LCDCON1_VOUT1000	( LCDCON1_CONTR2 | LCDCON1_CONTR1 | LCDCON1_CONTR0 )	// 111： VLCD = 1.000 VOUT
#define	LCDCON1_VOUT_ALL	( LCDCON1_CONTR2 | LCDCON1_CONTR1 | LCDCON1_CONTR0 )	// 所有位
#define	LCDCON1_VOUT_CLR	(~(LCDCON1_CONTR2 | LCDCON1_CONTR1 | LCDCON1_CONTR0 ) )	// 所有位清零，注意要用&操作符

// LCDCON2 LCD对比度寄存器
#define	LCDCON2_FCMOD		_BIT7 
#define	LCDCON2_FCCTL1		_BIT5
#define	LCDCON2_FCCTL0		_BIT4
#define	LCDCON2_LCDLDOEN	_BIT3
#define	LCDCON2_MOD2		_BIT2	// 驱动模式选择位
#define	LCDCON2_MOD1		_BIT1	// 驱动模式选择位
#define	LCDCON2_MOD0		_BIT0	// 驱动模式选择位
// 驱动模式选择位
#define LCDCON2_MOD1o5M		~(_BIT2|_BIT1|_BIT0)	// 000： 传统模式， 偏置电阻总和为1.5Mk
#define LCDCON2_MOD90k		_BIT0					// 001： 传统模式，偏置电阻总和为900k
#define LCDCON2_MOD60k		_BIT1					// 010： 传统模式，偏置电阻总和为60k
#define LCDCON2_MOD60_90k	(_BIT1|_BIT0)			// 011： 快速充电模式，偏置电阻总和自动在60k和900k之间切换
#define LCDCON2_MOD60_1o5	(_BIT2|_BIT1|_BIT0)		// 1xx： 快速充电模式，偏置电阻总和自动在60k和1.5M之间切换
#define LCDCON2_MOD_ALL		(_BIT2|_BIT1|_BIT0)		// 所有位
#define LCDCON2_MOD_CLR		~(_BIT2|_BIT1|_BIT0)	// 所有位清零，注意要用&操作符
// P4SS P4模式选择寄存器 是否作为seg，1作为seg 0作为IO，复位0-IO
#define	P4SS_P4S7			_BIT7
#define	P4SS_P4S6			_BIT6
#define	P4SS_P4S5			_BIT5
#define	P4SS_P4S4			_BIT4
#define	P4SS_ALL			0xF0
// P5SS P5模式选择寄存器 是否作为seg，1作为seg 0作为IO，复位0-IO
#define	P5SS_P5S7			_BIT7
#define	P5SS_P5S6			_BIT6
#define	P5SS_P5S5			_BIT5
#define	P5SS_P5S4			_BIT4
#define	P5SS_P5S3			_BIT3
#define	P5SS_P5S2			_BIT2
#define	P5SS_P5S1			_BIT1
#define	P5SS_P5S0			_BIT0
#define	P5SS_ALL			0xFF
// P6SS P6模式选择寄存器 是否作为seg，1作为seg 0作为IO，复位0-IO
#define	P6SS_P6S7			_BIT7
#define	P6SS_P6S6			_BIT6
#define	P6SS_P6S5			_BIT5
#define	P6SS_P6S4			_BIT4
#define	P6SS_P6S3			_BIT3
#define	P6SS_P6S2			_BIT2
#define	P6SS_P6S1			_BIT1 
#define	P6SS_ALL			0xFE
// P7SS P7模式选择寄存器 是否作为seg，1作为seg 0作为IO，复位0-IO
#define	P7SS_P7S7			_BIT7
#define	P7SS_P7S6			_BIT6
#define	P7SS_P7S5			_BIT5
#define	P7SS_P7S4			_BIT4
#define	P7SS_P7S3			_BIT3
#define	P7SS_P7S2			_BIT2
#define	P7SS_P7S1			_BIT1
#define	P7SS_P7S0			_BIT0
#define	P7SS_ALL			0x23
// P8SS P8模式选择寄存器 是否作为seg，1作为seg 0作为IO，复位0-IO
#define	P8SS_P8S7			_BIT7
#define	P8SS_P8S6			_BIT6
#define	P8SS_P8S5			_BIT5
#define	P8SS_P8S4			_BIT4
#define	P8SS_P8S3			_BIT3
#define	P8SS_P8S2			_BIT2
#define	P8SS_P8S1			_BIT1
#define	P8SS_P8S0			_BIT0
#define	P8SS_ALL			0xC0
// P9SS P9模式选择寄存器 是否作为seg，1作为seg 0作为IO，复位0-IO
#define	P9SS_P9S7			_BIT7
#define	P9SS_P9S6			_BIT6
#define	P9SS_P9S5			_BIT5
#define	P9SS_P9S4			_BIT4
#define	P9SS_P9S3			_BIT3
#define	P9SS_P9S2			_BIT2
#define	P9SS_P9S1			_BIT1
#define	P9SS_P9S0			_BIT0
#define	P9SS_ALL			0xFF


#define	LCD_OFF()			( LCDCON1 &= ~LCDCON1_LCDON );	// 关闭显示
#define	LCD_ON()			( LCDCON1 |=  LCDCON1_LCDON );	// 打开显示
/*----------------< 变量声明 >----------------------------------*/
extern void LCDDrv_Init( uchar8 v_ucPowerStatus );

/*----------------< 函数声明 >----------------------------------*/






#endif
