/*******************************************************************************************************
**** Copyright��  (c)Copyright 2019,�㽭��̩�����Ǳ��������ι�˾,���ܱ�Ӧ���з�                       
****                            All rights reserved.                                                 
**** FileName:    AppPowerOn.h                                                                         
**** Brief:       �ϵ�ϵͳ����                                                                      
**** Author:      peter.he@chint.com                                                                 
**** Version:     V1.0                                                                               
**** Date:        2019��3��14��                                                                         
****                                                                                                 
**** note:�޸���ʷ��¼�б�ÿ���޸ļ�¼Ӧ�����޸����ڡ��޸���                                          
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

/*-------------------------------- H�ļ�ʹ��˵�� -------------------------------------------------------*/
/*
 *  ���ļ��궨���ǰ׺Ϊ:
 *
*/

 
/*----------------< �����ļ� >----------------------------------*/


/*----------------< �궨���� >----------------------------------*/

#define	WDT_Clr()		do{ RSTSTAT = 0x00; } while(0);		// ��Ӳ�����Ź������Ź���ʱ������4s 
#define	MCU_RST()		do{ RSTSTAT = 0x07; (*((void(code*)(void))0x0000))(); }  while(0);// ��Ƭ����λ
#define	DIS_ALL_INT()	do{ IEN0 = 0x00; IEN1 = 0x00; } while(0);	
#define	ENTER_POWERDWN()	do{	SUSLO = 0X55;	PCON |= _BIT1; NOP();NOP();NOP(); } while(0);

#define DI()		{ EA=0; }
#define EI()		{ EA=1; }
#define NOP()		{ _nop_(); }

#if( METER_TYPE == METER_TYPE_DDSY666 )
	#define	UART0_IOCFG_RXD()	{ GPIO_IOCFG_P2_DIR_I(6);	GPIO_IOCFG_P2_PUP_F(6); }	// 485RXD ���ó����룬��������
	#define	UART0_IOCFG_TXD()	{ GPIO_IOCFG_P2_DIR_O(7);	GPIO_IOCFG_P2_SET_1(7); }	// 485TXD ���ó��������ʼ�����

	#define	UART1_IOCFG_RXD()	{ GPIO_IOCFG_P3_DIR_I(0);	GPIO_IOCFG_P3_PUP_F(0); }	// BT_RXD ���ó����룬��������
	#define	UART1_IOCFG_TXD()	{ GPIO_IOCFG_P3_DIR_O(1);	GPIO_IOCFG_P3_SET_1(1); }	// BT_TXD ���ó��������ʼ�����
#endif
	
#if( METER_TYPE == METER_TYPE_DTSY666 )
	#define	UART0_IOCFG_RXD()	{ GPIO_IOCFG_P2_DIR_I(6);	GPIO_IOCFG_P2_PUP_F(6); }	// 485RXD ���ó����룬��������
	#define	UART0_IOCFG_TXD()	{ GPIO_IOCFG_P2_DIR_O(7);	GPIO_IOCFG_P2_SET_1(7); }	// 485TXD ���ó��������ʼ�����

	#define	UART1_IOCFG_RXD()	{ GPIO_IOCFG_P3_DIR_I(0);	GPIO_IOCFG_P3_PUP_F(0); }	// BT_RXD ���ó����룬��������
	#define	UART1_IOCFG_TXD()	{ GPIO_IOCFG_P3_DIR_O(1);	GPIO_IOCFG_P3_SET_1(1); }	// BT_TXD ���ó��������ʼ�����
#endif
	
#if( METER_TYPE == METER_TYPE_DDSYU666 )
	#define	UART0_IOCFG_RXD()	{ GPIO_IOCFG_P2_DIR_I(6);	GPIO_IOCFG_P2_PUP_F(6); }	// 485RXD ���ó����룬��������
	#define	UART0_IOCFG_TXD()	{ GPIO_IOCFG_P2_DIR_O(7);	GPIO_IOCFG_P2_SET_1(7); }	// 485TXD ���ó��������ʼ�����

	#define	UART1_IOCFG_RXD()	{ GPIO_IOCFG_P3_DIR_I(0);	GPIO_IOCFG_P3_PUP_F(0); }	// BT_RXD ���ó����룬��������
	#define	UART1_IOCFG_TXD()	{ GPIO_IOCFG_P3_DIR_O(1);	GPIO_IOCFG_P3_SET_1(1); }	// BT_TXD ���ó��������ʼ�����
#endif 	
// CLKCON �������Ҫ�������ֲ�
#define	CLKCON_32K_SPDUP		_BIT7
#define	CLKCON_CLKS6			_BIT6
#define	CLKCON_CLKS5			_BIT5
#define	CLKCON_SCMF				_BIT4
#define	CLKCON_HFON				_BIT3
#define	CLKCON_CLKSEL			_BIT2
#define	CLKCON_CLKS2			_BIT1
#define	CLKCON_HFSEL			_BIT0
// ϵͳʱ��Ԥ��Ƶ��ѡ��
#define	CLKCON_FSYS_FOSCS		0x00				// 00�� fSYS = fOSCS
#define	CLKCON_FSYS_FOSCS_2		_BIT5				// 01�� fSYS = fOSCS/2
#define	CLKCON_FSYS_FOSCS_4		_BIT6				// 10�� fSYS = fOSCS/4
#define	CLKCON_FSYS_FOSCS_8		(_BIT6 | _BIT5)		// 11�� fSYS = fOSCS/12
#define	CLKCON_FSYS_FOSCS_ALL	(_BIT6 | _BIT5)	
#define	CLKCON_FSYS_FOSCS_CLR	(~(_BIT6 | _BIT5))

#define	CLKCON_WR_ENABLE()	{ OSCLO = 0x55 ;}	

#define	PASLO_POWER_SWITCH_ON()		{ PASLO = 0X55; }		// ��Դ�л�����

// PWRCON1 ��Դ���ƼĴ���1 
#define	PWRCON1_VOUTS2		_BIT2	
#define	PWRCON1_VOUTS1		_BIT1
#define	PWRCON1_AUTOS		_BIT0
// �����Դ״̬
#define	PWRCON1_VDD2VOUT	0x00
#define	PWRCON1_VBAT2VOUT	(PWRCON1_VOUTS2 | PWRCON1_VOUTS1) // ��0������
#define	PWRCON1_VFCAP2VOUT	(PWRCON1_VOUTS1 ) //  

// PWRCON2 ��Դ���ƼĴ���2 
#define	PWRCON2_LDO28ON		_BIT7 		// 2.8V LDO��·���ؿ��ƣ�0�� �ر� 1�� ��
#define	PWRCON2_LCDLDO1		_BIT6 		// LCDLDO��ѹ����
#define	PWRCON2_LCDLDO0		_BIT5		// LCDLDO��ѹ����
#define	PWRCON2_VDDDISC		_BIT4		// VDD ���ؿ��ؿ���
//LCDLDO��ѹ����
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
// LPD2��ѹ���ȼ�

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
#define	LPDCON2_LPDS_ALL	(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS1 | LPDCON2_LPDS0)		// ����λ
#define	LPDCON2_LPDS_CLR	(~(LPDCON2_LPDS3 | LPDCON2_LPDS2 | LPDCON2_LPDS1 | LPDCON2_LPDS0) )	// ����λ ���㣬ע��ʹ��&������

// ��ʱ��
// TMOD
#define	TMOD_GATE1			_BIT7
#define	TMOD_CT1			_BIT6
#define	TMOD_M11			_BIT5
#define	TMOD_M10			_BIT4
#define	TMOD_GATE0			_BIT3
#define	TMOD_CT0			_BIT2
#define	TMOD_M01			_BIT1
#define	TMOD_M00			_BIT0

#define	TMOD_T0_MODE0		(~(_BIT1 | _BIT0))	// 00�� ��ʽ0�� 13λ���ϼ���������/��ʱ���� ����TLx�ĵ�7-5λ
#define	TMOD_T0_MODE1		_BIT0				// 01�� ��ʽ1�� 16λ���ϼ���������/��ʱ��
#define	TMOD_T0_MODE2		_BIT1				// 10�� ��ʽ2�� 8λ�Զ��������ϼ���������/��ʱ��
#define	TMOD_T0_MODE3		(_BIT1 | _BIT0)		// 11�� ��ʽ3��ֻ���ڶ�ʱ��0�� �� ����8λ���ϼ�����ʱ��
#define	TMOD_T0_MODE_ALL	(_BIT1 | _BIT0)		// 11:  ����λ
#define	TMOD_T0_MODE_CLR	(~(_BIT1 | _BIT0))	// 00 ����λ���㣬ע��Ҫ��&������

#define	TMOD_T1_MODE0		0x00 			// 00�� ��ʽ0�� 13λ���ϼ���������/��ʱ���� ����TLx�ĵ�7-5λ
#define	TMOD_T1_MODE1		_BIT4			// 01�� ��ʽ1�� 16λ���ϼ���������/��ʱ��
#define	TMOD_T1_MODE2		_BIT5			// 10�� ��ʽ2�� 8λ�Զ��������ϼ���������/��ʱ��
#define	TMOD_T1_MODE_ALL	(  TMOD_T1_MODE1 | TMOD_T1_MODE2))	// 11: ����λ
#define	TMOD_T1_MODE_CLR	(~(TMOD_T1_MODE1 | TMOD_T1_MODE2))	// 00: ����λ���㣬ע��Ҫ��&������

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

// ��ʱ��0 ģʽ1 ��ʱ���ĺ궨�� Xms @8Mhz
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



// EUART0 �Ĵ���
// PCON ��Դ���ƼĴ���
#define	PCON_SMOD			_BIT7
#define	PCON_SSTAT			_BIT6
#define	PCON_SSTAT1			_BIT5
#define	PCON_SSTAT2			_BIT4
#define	PCON_GF1			_BIT3
#define	PCON_GF0			_BIT2
#define	PCON_PD				_BIT1
#define	PCON_IDL			_BIT0

// SCON EUART0���Ƽ�״̬�Ĵ���
#define	SCON_SM0_FE			_BIT7
#define	SCON_SM1_RXOV		_BIT6
#define	SCON_SM2_TXCOL		_BIT5
#define	SCON_REN			_BIT4
#define	SCON_TB8			_BIT3
#define	SCON_RB8			_BIT2
#define	SCON_TI				_BIT1
#define	SCON_RI				_BIT0 

// SCON1 EUART1���Ƽ�״̬�Ĵ��� 
#define	SCON1_SM10_FE		_BIT7
#define	SCON1_SM11_RXOV		_BIT6
#define	SCON1_SM12_TXCOL	_BIT5
#define	SCON1_REN1			_BIT4
#define	SCON1_TB81			_BIT3
#define	SCON1_RB81			_BIT2
#define	SCON1_TI1			_BIT1
#define	SCON1_RI1			_BIT0 

// SCON3 EUART3���Ƽ�״̬�Ĵ���
#define	SCON3_SM30			_BIT7
#define	SCON3_SM31			_BIT6
#define	SCON3_SM33			_BIT5
#define	SCON3_REN3			_BIT4
#define	SCON3_TB83			_BIT3
#define	SCON3_RB38			_BIT2
#define	SCON3_TI3			_BIT1
#define	SCON3_RI3			_BIT0 


// ������ؼĴ���
// EMUSR EMU״̬/���ƼĴ���
// ע�� DSPEN = 0ʱ�� �����ʣ� ��Чֵ���㲿�����㣬 �������ã� �Լ������ۼӲ��ֱ��ֲ��䡣
#define	EMUSR_DSPEN			_BIT7	// ����ģ�����ʹ�� 0�� ��ֹ 1�� ����
#define	EMUSR_EMUCLKS1		_BIT6	// EMUģ��ʱ�ӿ����ź�
#define	EMUSR_EMUCLKS0		_BIT5
	// emuʱ������
	#define	EMUSR_CLK_OFF		(~(_BIT6|_BIT5) )	//	00�� �ر�EMU��ʱ������
	#define	EMUSR_CLK_32K		_BIT5				//	01�� ѡ��32Kʱ����ΪEMUģ�鹤��ʱ��
	#define	EMUSR_CLK_RC8M		_BIT6				//	10�� ѡ��ʹ��RC8Mʱ����ΪEMUģ�鹤��ʱ��
	#define	EMUSR_CLK_PLL		  (_BIT6|_BIT5)		//	11�� ѡ��ʹ��PLLʱ����ΪEMUģ�鹤��ʱ��
	#define	EMUSR_CLK_CLR		(~(_BIT6|_BIT5) )
	
// ֻ��
#define	EMUSR_SAGF			_BIT4	// ʧѹ״̬��־0�� ����״̬ 1�� ʧѹ״̬
#define	EMUSR_NoQLd         _BIT3	// �޹����ʲ��ۼƱ�־0�� �޹����ʴ��ڵ����𶯹��� 1�� �޹�����С���𶯹���
#define	EMUSR_NoPLd         _BIT2	// �й����ʲ��ۼƱ�־0�� �й����ʴ��ڵ����𶯹��� 1�� �й�����С���𶯹���
#define	EMUSR_REVQ          _BIT1	// �����޹����ܱ�־ 0�� ���޹����� 1�� ���޹�����
#define	EMUSR_REVP          _BIT0	// �����й����ܱ�־ 0�� ���й����� 1�� ���й�����
// EMUIE  EMU�ж�ϵͳ
#define	EMUIE_DIMIE			_BIT6	// DIMMER ����ж�����λ
#define	EMUIE_DSPIE			_BIT5	// DSPִ�н����ж�����λ
#define	EMUIE_QFIE			_BIT4	// �޹���������ж�����λ
#define	EMUIE_PFIE			_BIT3	// �й���������ж�����λ
#define	EMUIE_SAMPIE		_BIT2	// ���β����ж�����λ
#define	EMUIE_SAGIE			_BIT1	// ʧѹ�ж�����λ
#define	EMUIE_ZXIE			_BIT0	// �����ж�����λ
// EMUIF  EMU�ж�����Ĵ���
#define	EMUIF_DIMIF			_BIT6	// DIMMER ����жϱ�־
#define	EMUIF_DSPIF			_BIT5	// DSPִ�н����жϱ�־
#define	EMUIF_QFIF			_BIT4	// �޹���������жϱ�־
#define	EMUIF_PFIF			_BIT3	// �й���������жϱ�־
#define	EMUIF_SAMPIF		_BIT2	// ���β����жϱ�־
#define	EMUIF_SAGIF			_BIT1	// ʧѹ�жϱ�־
#define	EMUIF_ZXIEF			_BIT0	// �����жϱ�־
// EMUAFR �ж�����Ĵ���2 
#define	EMUAFR_SUMIE		_BIT7	// �ۼ������ж�����λ
#define	EMUAFR_SUMIF		_BIT3	// �ۼ������ж������־

// EMUCFG0 EMU�������üĴ���0��3�ֽڣ� ���Ѱַ 
#define	EMUCFG0_ADCCKSEL1	_BIT20	// ADC����ʱ�ӷ�Ƶѡ�� EMUCLKS=01ʱ�� �̶�Ϊ32K
#define	EMUCFG0_ADCCKSEL0	_BIT19	
	#define EMUCFG0_ADCCK_32K	0x00 // ADCѡ��32K
#define	EMUCFG0_APGAU0		_BIT8	// ��ѹͨ��0ģ��PGA����ѡ�� 0�� 2������(Ĭ��) 1�� 4������
#define	EMUCFG0_APGAI21		_BIT7	// ����ͨ��2ģ��PGA����ѡ��
#define	EMUCFG0_APGAI20		_BIT6
	#define EMUCFG0_APGAI_16 ( _BIT7 | _BIT6 ) // 16��
#define	EMUCFG0_APGAI11		_BIT5	// ����ͨ��1ģ��PGA����ѡ��
#define	EMUCFG0_APGAI10		_BIT4
#define	EMUCFG0_INPUTSHORT	_BIT3	// ͨ�����������ڲ��̽ӵ���
#define	EMUCFG0_ADCUON		_BIT2	// ��ѹͨ����ADCʹ�ܿ���  0�� �ر�ADC(Ĭ��) 1�� ��ADC
#define	EMUCFG0_ADCI2ON		_BIT1	// ����ͨ��2��ADCʹ�ܿ��� 0�� �ر�ADC(Ĭ��) 1�� ��ADC
#define	EMUCFG0_ADCI1ON		_BIT0	// ����ͨ��1��ADCʹ�ܿ��� 0�� �ر�ADC(Ĭ��) 1�� ��ADC


// EMUCFG1 EMU�������üĴ���1��3�ֽڣ� ���Ѱַ 
#define	EMUCFG1_POL				_BIT23	// PF/QF������Կ��� 0�� �ߵ�ƽ��Ч(Ĭ��) 1�� �͵�ƽ��Ч
#define	EMUCFG1_QFEN			_BIT22	// �޹�����QF����������� 0����ֹ  1������
#define	EMUCFG1_PFEN			_BIT21	// �й�����PF����������� 0����ֹ  1������
#define	EMUCFG1_MNL				_BIT20	// ������ģʽʹ�ܿ��� 0���ر� 1������
#define	EMUCFG1_DCCON1			_BIT19	// ֱ��������
#define	EMUCFG1_DCCON0			_BIT18
#define	EMUCFG1_HPFON			_BIT17	// ͨ����ͨ�˲���ѡ�� 0:�򿪣�Ĭ�ϣ� 1���ر�
#define	EMUCFG1_PWidth1			_BIT16	// ���������:
#define	EMUCFG1_PWidth0			_BIT15
	#define EMUCFG1_PWidth_45ms _BIT15	// 45ms
#define	EMUCFG1_PFAST1			_BIT14	// С�ź��������ѡ��
#define	EMUCFG1_PFAST0			_BIT13
#define	EMUCFG1_QMOD1			_BIT12	// �޹������ۼӷ�ʽѡ��
#define	EMUCFG1_QMOD0			_BIT11
#define	EMUCFG1_PMOD1			_BIT10	// �й������ۼӷ�ʽѡ��
#define	EMUCFG1_PMOD0			_BIT9
#define	EMUCFG1_RMSLPFENB		_BIT8	// ��Чֵ���ݾ�����ͨʹ�� 0��ʹ�� 1����ֹ
#define	EMUCFG1_QRUN			_BIT7	// �޹������ۼ�ʹ�� 0�� ֹͣ 1������
#define	EMUCFG1_PRUN			_BIT6	// �й������ۼ�ʹ�� 0�� ֹͣ 1������
#define	EMUCFG1_PWRSEL1			_BIT5	// ����ͨ��ѡ��:
#define	EMUCFG1_PWRSEL0			_BIT4	// 
#define	EMUCFG1_CONST_EN		_BIT3	// ��������ģʽ���� 0���ر� 1����
#define	EMUCFG1_CmodeFreq1		_BIT2	// �ۼ�Ƶ��ѡ��
#define	EMUCFG1_CmodeFreq0		_BIT1	// 
#define	EMUCFG1_Cmodeen			_BIT0	// �ۼ�ģ����ʹ��: 0 �رգ�Ĭ�ϣ� 1����

// EMUCFG2 EMU�������üĴ���1��3�ֽڣ� ���Ѱַ 
#define	EMUCFG2_ADCRST_U			_BIT14	// ��ѹͨ��ģ��ADC��λ����
#define	EMUCFG2_ADCRST_I2			_BIT13	// ����ͨ��2ģ��ADC��λ����
#define	EMUCFG2_ADCRST_I1			_BIT12	// ����ͨ��1ģ��ADC��λ����
#define	EMUCFG2_VREF_BUFFER_CURS1	_BIT11	// VREF Buffer��������
#define	EMUCFG2_VREF_BUFFER_CURS0	_BIT10	// 
#define	EMUCFG2_PGA_CURS4			_BIT9	//  PGA��������
#define	EMUCFG2_PGA_CURS3			_BIT8	// 
#define	EMUCFG2_PGA_CURS2			_BIT7	// 
#define	EMUCFG2_PGA_CURS1			_BIT6	// 
#define	EMUCFG2_PGA_CURS0			_BIT5	// 
#define	EMUCFG2_ADC_CURS4			_BIT4	// ADC��������
#define	EMUCFG2_ADC_CURS3			_BIT3	// 
#define	EMUCFG2_ADC_CURS2			_BIT2	// 
#define	EMUCFG2_ADC_CURS1			_BIT1	// 
#define	EMUCFG2_ADC_CURS0			_BIT0	// 

// EMUCFG3 EMU�������üĴ���1��3�ֽڣ� ���Ѱַ 
#define	EMUCFG3_PD_BG				_BIT8
#define	EMUCFG3_EN_BG_CHOP			_BIT7
#define	EMUCFG3_BG_CHOPCK_SEL1		_BIT5
#define	EMUCFG3_BG_CHOPCK_SEL0		_BIT4
/*----------------< �������� >----------------------------------*/


/*----------------< �������� >----------------------------------*/
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

