//����ȫ�ֺ������������Ҫ��עΪextern

#ifndef __EX_VAR_H__
#define __EX_VAR_H__
#include "define4.h"

#if(1 == CHINT_Mode)
extern const unsigned char ecode C_ucSoftVerForFactory[];   //�ڲ��汾��
#endif

extern const float ecode const_KL;
extern const float ecode const_KH;
extern const float ecode const_xtl_top;
extern const float ecode const_TmpsL;
extern const float ecode const_TmpsH;
extern const uint08 ecode constF_Volt;
extern const uint16 ecode const_adc_TrimB;
extern const uint16 ecode const_adc_TrimT;
extern const uint16 ecode const_KHKL_TrimRange;
extern const float ecode const_T_OffsetRun;
extern const float ecode const_T_OffsetSlp;
extern const uint08 ecode const_TopNoTrim;
extern const uint08 ecode const_TopNTRange;
extern const float ecode const_T_CL;
extern const float ecode const_T_CH;
extern const uint08 ecode const_C_Mode;
extern const int16 ecode const_TR_LSTART;
extern const int16 ecode const_TR_HSTART;
extern const uint08 ecode const_TR_GAP;
extern const uint08 ecode const_TR_Mode;
extern const uint08 ecode RTC_Trim_Ctrl;

extern const uint16 ecode BPS_SPBRGL1[];
extern const struct HisEvent_STR ecode EventTable[];

extern const uint08 ecode clkmode;
extern const uint32 ecode rchfcfgreg;
extern const uint32 ecode runwdtcon;
extern const uint08 ecode rtcosccfg;
extern const uint32 ecode SleepBorCfg;
extern const uint32 ecode SleepPdrCfg;
extern const uint32 ecode RunBorCfg;
extern const uint32 ecode RunPdrCfg;
extern const uint08 ecode Compile_LvdLvCfg;
extern const uint32 ecode Runet1Outcnt;
extern const uint08 ecode Runrtctmls;

extern const uint08 ecode Relay_Mode;
extern const uint08 ecode Correction_Mode;
extern const uint08 ecode Compile_Polar_485;
extern const uint08 ecode FlashPowerOff_Ctrl;
extern const uint08 ecode EsamPowerOff_Ctrl;
extern const uint08 ecode Memoryerr_Ctrl;	
extern const uint08 ecode Wwdt_Lcd_Ctrl;
extern const uint32 ecode IRDutyCycleCfg;
extern const uint08 ecode SleepPtatOffsetCfg;
extern const uint08 ecode Extbattery;
extern const uint08 ecode ExtVoltage;
extern const uint16 code MaxRecNum[];
extern const uint08 ecode Def_Erase_Times;
extern const uint08 code LoadOffset[max_casecount];
extern const uint08 code LoadLen[max_casecount];

extern const unsigned char ecode Verdate[24];
extern const unsigned char ecode RatedVolt[6];
extern const unsigned char ecode RatedCurr[6];
extern const unsigned char ecode MaxCurr[6];
extern const unsigned char ecode MinCurr[6];
extern const unsigned char ecode TrtCurr[6];
extern const unsigned char ecode ActiveClass[4];
extern const unsigned char ecode ReActiveClass[4];
extern const unsigned char ecode MaterType[32];
extern const unsigned char ecode Facdate[10];
extern const unsigned char ecode ProtocolVer[16];
extern const unsigned char ecode SoftwareVer1[32];
extern const unsigned char ecode HardwareVer1[32];
extern const unsigned char ecode FactoryNum[32];
extern const unsigned char ecode Softbk[8];
extern const unsigned char ecode DispVer[3];
extern const unsigned long ecode Def_Meterconst_Bcd;
extern const unsigned char ecode Def_Meterconst_Hex;
extern const unsigned char ecode Def_Plusevalidtimer;

extern const unsigned char ecode resetworking_timer_delay;
extern const unsigned short ecode Zb_Comm_Timer_delay;
extern const unsigned char ecode Bps_9600;
extern const unsigned short ecode Mod_Comm_Timer_delay1;
extern const unsigned char ecode Mod_Comm_Timer_delay2;

extern const uint08 ecode Relaytimer_Delay_N;
extern const uint08 ecode Relaytimer_Delay_W;
extern const uint08 ecode Defaultspacetimer;
extern const uint08 ecode Defrelayerrorcnt_s;
extern const uint08 ecode Defrelayerrorcount;
extern const uint08 ecode Defrelayerrorcount_r;

extern const uint08 ecode Def_Dl_Difference;
extern const uint08 ecode Def_Plusefiltertimer;
extern const uint08 ecode Def_Plusefiltertimer2;
extern const uint08 ecode Adjclk_timer_delay_s;
extern const uint08 ecode Adjclk_timer_delay;
extern const uint16 ecode Defendenergyvoltage;
extern const uint08 ecode Def_Shielding_I1;
extern const uint08 ecode Def_Shielding_I2;
extern const uint08 ecode Def_Shielding_Cos;
extern const uint08 ecode Defcurrovercount;
extern const uint16 ecode Defaultpdvoltage;
extern const uint08 ecode Defaultpddelay;
extern const uint08 ecode Deflowvoltagecount_s;
extern const uint08 ecode Deflowvoltagecount;
extern const int16 ecode Uoffset;
extern const uint08 ecode Def_Powerdetcnt2;
extern const uint08 ecode ht7017_mclk;
extern const uint32 ecode Def_SelfHeat_I;
extern const uint08 ecode Def_SelfHeat_Cancel;
extern const uint32 ecode Def_Device_Id;

extern const uint08 ecode Fulllcdbias;
extern const uint08 ecode Runlcdbias;
extern const uint08 ecode RunlLCDSET;
extern const uint08 ecode RunlLCDDRV;
extern const uint08 ecode Sleeplcdfreq;
extern const uint08 ecode SleepLCDSET;
extern const uint08 ecode SleepLCDDRV;
extern const uint16 ecode Sleepvthreshold[];
extern const uint08 ecode Sleeplcdbias[];
extern const uint08 ecode def_powerdown_timer;
extern const uint08 ecode def_meterrun_timer;
extern const uint08 ecode def_coverdelaytimer;

extern const uint16 ecode Defaultauthtimer;
extern const uint08 ecode Defaultstartup;
extern const uint16 ecode Defaultpdcurrent;
extern const uint08 ecode MAX_PSW_NUM;
extern const uint08 ecode Defpassworderrcnt;
extern const uint16 ecode Def_Vthreshold;
extern const uint16 ecode Def_Vthreshold_H;
extern const uint16 ecode Def_Relay_ActL;
extern const uint16 ecode Def_Relay_ActH;
extern const uint16 ecode Def_Relay_Det;

extern const unsigned long ecode disp_table[];
extern const unsigned char ecode Def_Limitmenory_table[];
extern const unsigned char ecode Def_DisplayPara_table[];
extern const unsigned char ecode Def_SleepDisplayPara_table[8];
extern const unsigned short ecode Def_Sleepdisp_table[16];
extern const unsigned char ecode Def_featureword_table[];
extern const unsigned char ecode Def_weekloadpara_table[];
extern const unsigned char ecode Def_vollmtpara_table[];
extern const unsigned char ecode Def_feik_table[];
extern const unsigned short ecode Def_Autodisp_table[31];
extern const unsigned short ecode Def_Keydisp_table[62];

extern const unsigned char ecode Def_Password3_table[];
extern const unsigned char ecode Def_Password4_table[];
extern const unsigned char ecode Def_histroyparameter_table[];
extern const unsigned char ecode Def_freezeparameter_table[];
extern const unsigned char ecode Def_sqb_table1[];
extern const unsigned char ecode Def_sqb_table2[];
extern const unsigned char ecode Def_sdb_table1[];
extern const unsigned char ecode Def_sdb_table2[];
extern const unsigned char ecode Def_sdb_table2[];
extern const unsigned char ecode Def_jtshiqu_table[];
extern const unsigned char ecode Def_jtshiqu_table2[];

//---------------------- bit variable ------------------------------------------------------------------------
extern 	B08_Bit bdata			Meter_Status_S;			//(�ı���Ҫ����)
#define	Meter_Status			Meter_Status_S.B08
#define	commmodule_open_flag  		Meter_Status_S.Bit.bit0		//ͨ��ģ��γ�״̬��־
#define	commmodule_failed_flag		Meter_Status_S.Bit.bit1		//ͨ��ģ��ͨѶʧ�ܱ�־
#define	lower_v_event_flag		Meter_Status_S.Bit.bit2		//�͵�ѹ�¼���־
#define	high_v_event_flag		Meter_Status_S.Bit.bit3		//�ߵ�ѹ�¼���־
#define	low_voltage_flag		Meter_Status_S.Bit.bit4		//��ص�ѹ��־
#define	change_batt_flag		Meter_Status_S.Bit.bit5		//�����ظ�����־
#define	relay_success2_flag		Meter_Status_S.Bit.bit6		//�̵��������ɹ���־
#define	relay_commu_close2_flag		Meter_Status_S.Bit.bit7		//��������־(��������)

extern 	B08_Bit bdata			Meter_Status1_S;		//(�ı���Ҫ����)
#define	Meter_Status1			Meter_Status1_S.B08
#define	relay_status_flag		Meter_Status1_S.Bit.bit0	//�̵���״̬(0��ʾ�պ�1��ʾ�Ͽ�)
#define	relay_commu_alarm_flag		Meter_Status1_S.Bit.bit4	//ͨѶ�����̵���
#define	relay_commu_open_flag		Meter_Status1_S.Bit.bit5	//ͨѶ�Ͽ��̵���
#define relay_commu_disable_close_flag	Meter_Status1_S.Bit.bit6	//������պϼ̵�����־
#define	relay_commu_close_flag		Meter_Status1_S.Bit.bit7	//ͨѶ�պϼ̵���

extern 	B08_Bit bdata			Meter_Status2_S;		//(�ı���Ҫ����)
#define	Meter_Status2			Meter_Status2_S.B08
#define	relay_success_flag		Meter_Status2_S.Bit.bit0	//�̵��������ɹ���־
#define	relay_failed_flag		Meter_Status2_S.Bit.bit1	//�̵��������־(�ϱ�)
#define	relay_commu_open_1a_flag	Meter_Status2_S.Bit.bit2	//ͨѶ��բ�����־
#define	relay_commu_open_1d_flag	Meter_Status2_S.Bit.bit3	//ͨѶԤ��բ�����־
#define	relay_commu_open_1e_flag	Meter_Status2_S.Bit.bit4	//ͨѶԤ��բ�����־
#define	relay_cleardl_flag		Meter_Status2_S.Bit.bit5	//���ñ������־
#define	commmodule_start_flag		Meter_Status2_S.Bit.bit7	//ͨ��ģ������״�������־

extern 	B08_Bit bdata			System_Status_S;		//(ͣ�粻��)
#define	System_Status			System_Status_S.B08
#define	real_relaystatus_flag		System_Status_S.Bit.bit0	//�̵���ʵ��״̬��־
#define	clock_error			System_Status_S.Bit.bit2	//ʱ�Ӵ����־
#define	esam_error			System_Status_S.Bit.bit4	//esam�����־
#define	eeprom_error_flag		System_Status_S.Bit.bit5	//�洢�����ϱ�־
#define	hangup_comm_flag		System_Status_S.Bit.bit6	//����ͨѶ��־
#define	already_setclock_flag		System_Status_S.Bit.bit7	//�Ѿ�Уʱ��־

extern 	B08_Bit bdata			System_Status1_S;		//
#define	System_Status1			System_Status1_S.B08
#define	identity_prog_flag		System_Status1_S.Bit.bit0	//��֤��̱�־
#define identity_ir_flag		System_Status1_S.Bit.bit1	//���������־
#define	display_zaibo_flag		System_Status1_S.Bit.bit2	//��ʾ�ز���־
#define	display_ble_flag		System_Status1_S.Bit.bit3	//��ʾ������־
#define	first_prog_flag			System_Status1_S.Bit.bit4	//�״α�̱�־
#define	progenable			System_Status1_S.Bit.bit5	//���ʹ��
#define	comm_relaystatus_flag		System_Status1_S.Bit.bit6	//�̵���ʵ��״̬��־(ͨѶר��)
#define	relay_error			System_Status1_S.Bit.bit7	//�̵��������־

extern 	B08_Bit bdata			System_Status2_S;		//
#define	System_Status2			System_Status2_S.B08
#define	esam_biaohao_flag		System_Status2_S.Bit.bit0	//�Ѳ���esam��ű�־
#define	display_rtc_flag		System_Status2_S.Bit.bit1	//��ʾʱ���־
#define	disp_0_flag			System_Status2_S.Bit.bit2	//��Ҫ���㴦���־
#define	freeze_display_flag		System_Status2_S.Bit.bit3	//�����յ�����ʾ��־
#define	below_60u_flag			System_Status2_S.Bit.bit4	//����60%��ѹ��־
#define	below_70u_flag			System_Status2_S.Bit.bit5	//����70%��ѹ��־
#define	relay_direct_flag		System_Status2_S.Bit.bit6	//�̵���ֱ�Ӷ�����־
#define	relay_delay_flag		System_Status2_S.Bit.bit7	//�������ʱ��բ��־

extern 	B08_Bit bdata			System_Status3_S;
#define	System_Status3			System_Status3_S.B08
#define	run_freeze_flag			System_Status3_S.Bit.bit3	//����ͽ����־
#define	run_loadchk_flag		System_Status3_S.Bit.bit4	//���ɼ�¼��־
#define	run_timezone_flag		System_Status3_S.Bit.bit5	//ʱ��ʱ�α��־
#define	run_price_flag			System_Status3_S.Bit.bit6	//��۸��±�־
#define	run_alarm_flag			System_Status3_S.Bit.bit7	//����״̬��־

extern 	B08_Bit bdata			System_Status4_S;
#define	System_Status4			System_Status4_S.B08
#define	fwdl_veri_flag			System_Status4_S.Bit.bit0	//�������У���־
#define	bkdl_veri_flag			System_Status4_S.Bit.bit1	//�������У���־
#define	rpdl_veri_flag			System_Status4_S.Bit.bit2	//�޹�����У���־
#define	mode_veri_flag			System_Status4_S.Bit.bit3	//����ģʽ��У���־
#define	addr_veri_flag			System_Status4_S.Bit.bit4	//ͨ�ŵ�ַУ���־
#define	disppm_veri_flag		System_Status4_S.Bit.bit5	//��ʾ����У���־
#define	dispitem_veri_flag		System_Status4_S.Bit.bit6	//��ʾ��ĿУ���־
#define	temperpara_veri_flag		System_Status4_S.Bit.bit7	//�¶�ϵ��У���־

extern 	B08_Bit bdata			System_Status5_S;
#define System_Status5			System_Status5_S.B08
#define	month_change_flag		System_Status5_S.Bit.bit0	//�¸ı��־
#define	year_change_flag		System_Status5_S.Bit.bit1	//��ı��־
#define	year_change_flag2		System_Status5_S.Bit.bit2	//��ı��־(�����ڸߵ�ѹ�¼�)

extern	B08_Bit	bdata			AT7051_Flag_S;
#define AT7051_Flag			AT7051_Flag_S.B08
#define read_back_flag			AT7051_Flag_S.Bit.bit0		//�����������־
#define	init_7051_flag1			AT7051_Flag_S.Bit.bit1		//��ʼ��AT7051��־1
#define	read_uip_flag1			AT7051_Flag_S.Bit.bit2		//��AT7051˲ʱֵ��־1
#define	check_7051_flag1		AT7051_Flag_S.Bit.bit3		//У��AT7051����ֵ��־1
#define	load_over_flag			AT7051_Flag_S.Bit.bit4		//������־
#define	over_xxx_flag			AT7051_Flag_S.Bit.bit5		//��բ��������־
#define	power_zero_flag			AT7051_Flag_S.Bit.bit6		//���ʵ���0��־
#define	ble_inter_flag			AT7051_Flag_S.Bit.bit7		//�����ڲ������־

extern B08_Bit bdata			AT7051_Flag2_S;	
#define AT7017_Flag			AT7051_Flag2_S.B08
#define	dln_back_flag		        AT7051_Flag2_S.Bit.bit0		//���ߵ��������־
#define	nline_err_flag		        AT7051_Flag2_S.Bit.bit1		//���ߵ����쳣��־
#define	dl_back_flag			AT7051_Flag2_S.Bit.bit2		//��������
#define	dl_back_flag2			AT7051_Flag2_S.Bit.bit3		//���������־2(��־1�ͱ�־2���ȷ���������޹�)
#define	lost_v_flag			AT7051_Flag2_S.Bit.bit4		//ʧѹ��־
#define	lower_v_flag			AT7051_Flag2_S.Bit.bit5		//�͵�ѹ��־
#define	high_v_flag			AT7051_Flag2_S.Bit.bit6		//�ߵ�ѹ��־
#define	cal_err_flag		        AT7051_Flag2_S.Bit.bit7		//�������ϱ�־

//;=============================< IDATA �洢���� >================================
extern 	uint08			idata	run_readrtc_flag;		//��ȡʵʱʱ�ӱ�־
extern 	uint08			idata	run_display_flag;		//ˢ��LCD��ʾ��־
extern 	uint08			idata	run_relaychk_flag;		//�̵�������־
extern 	uint08			idata	reg_veri_flag;			//�Ĵ���У���־
extern 	uint08			bdata	DisKeySamp;			//��ʾ����ȥ���Ĵ���
extern 	uint08			bdata	Uart1KeySamp;			//485���Լ��ȥ���Ĵ���
extern 	uint08			idata	VectorTimer;			//���붨ʱ��
extern 	struct 	SYS_CLOCK_FRM	idata	Sclock;				//ʱ������
extern 	uint08			idata	Key_Status;			//��Կ״̬,00��ʾȫ����Կ,01��ʾȫ��˽Կ,FF���й���˽

//;=============================< XDATA �洢���� >================================
extern NoInit_t 			NoInit;
#define	Progkey				NoInit.Progkey			//240min���(ͣ������)
#define	Cover				NoInit.Cover			//���ǲ���(ͣ�籣��) 
#define Mac_Err_Times			NoInit.Mac_Err_Times		//MACУ��ʧ�ܴ���
#define	G_Clockerr_Times		NoInit.G_Clockerr_Times		//���Ĺ㲥Уʱ��¼���ϴ���
#define System_St_Bk			NoInit.System_St_Bk		//ϵͳ״̬�ֱ���(ͣ������)
#define Report_Data			NoInit.Report_Data		//��Ч�ϱ�״̬��
#define Report_Data2			NoInit.Report_Data2		//��Ч�ϱ�״̬�ֱ���
#define Report_Num			NoInit.Report_Num		//�¼��ϱ���������
#define RReport_Status			NoInit.RReport_Status		//֮ǰ�Ѷ��ϱ�״̬����λ�ϱ�״̬
#define	Meter_Run_Timer4		NoInit.Meter_Run_Timer4		//
#define Reset_Rep_Timer			NoInit.Reset_Rep_Timer		//��λ�ϱ�״̬�ֶ�ʱ��
#define	Password_Err			NoInit.Password_Err		//����������
#define	Load				NoInit.Load			//����ָ�빲22�ֽ�
#define	Meter_Run_Timer1		NoInit.Meter_Run_Timer1		//
#define	Meter_Run_Timer2		NoInit.Meter_Run_Timer2		//	
#define	Wr_Ext_Number			NoInit.Wr_Ext_Number		//�ڲ���չ����дee�������
#define	Fwdl		  		NoInit.Fwdl			//����������					
#define	Bkdl		  		NoInit.Bkdl			//����������
#define	Rpdl				NoInit.Rpdl			//�������޹�������
#define	RAMREG0				NoInit.RAMREG0			//��������Ĵ���
#define	RAMREG1				NoInit.RAMREG1			//
#define	RAMREG2				NoInit.RAMREG2			//
#define	RAMREG3				NoInit.RAMREG3			//
#define	RAMREG4				NoInit.RAMREG4			//
#define	RAMREG5				NoInit.RAMREG5			//
#define	RAMREG6				NoInit.RAMREG6			//
#define	RAMREG7				NoInit.RAMREG7			//
#define	RAMREG8				NoInit.RAMREG8			//
#define	RAMREG9				NoInit.RAMREG9			//
#define	RAMREG10			NoInit.RAMREG10			//
#define	RAMREG11			NoInit.RAMREG11			//
#define	RAMREG12			NoInit.RAMREG12			//
#define	RAMREG13			NoInit.RAMREG13			//
#define	RAMREG14			NoInit.RAMREG14			//
#define	RAMREG15			NoInit.RAMREG15			//
#define	RAMBUF				NoInit.RAMBUF			//

extern 	uint08			near	Outputtype;	//0-������,1-����,2-ʱ��Ͷ���ź�,0x50-FOUT���
extern 	struct  TIMER_FRM	near	Successled,Shiduanctrl,Relayctrl;
extern 	struct  TMR_STS_FRM	near	Adcctrl;
extern 	uint16			near	Lcdled;//���ⶨʱ��
extern 	uint32			near	Identitytimer;	//��ȫ��֤��ʱ��
extern 	uint32			near	IR_EnTimer;	//������֤��ʱ��
extern 	uint32			near	Opendelaytimer;	//��բ��ʱ��ʱ��
extern 	uint32			near	CurrentTimer;	//����բ������ʱ��
extern 	uint08			near	Relayerror_Count,Relayerror_Count1,Relayerror_Count2;//�̵������������
extern 	uint08			near	Relay_Space_Timer;//�ϵ���ʱ���Ƽ̵�����ʱ��
extern 	uint08			near	Keyclose_timer;//�����պϼ̵�����ʱ��
extern 	uint08			near	Display_Space_Timer;//���������ʾ�����ʱ��
extern 	uint16		  	near	Stop_Disptimer;//ͣ����ʾʱ�䶨ʱ
extern 	signed char		near	Temperature_Hex;//�����¶�(hex��)
extern	uint16		 	near	Temperature_Adc;//��ǰ�¶�ADCֵ(hex��)
extern	float			near	Rtcadj_Offset;//�¶Ȳ�����Уֵ
extern	float			near	Rtcadj_Offset2;//�¶Ȳ�����Уֵ
extern	uint08			near	RtcStopProcFlag;//ֹͣ�²���־
extern 	unsigned int		near	Hw_Lcdled_Timer;//�����������ʱ��
extern 	uint16			near	Ext_Disp_Cnt;//��չLCD��ѯ����
extern 	uint08			near	Init_Led_Timer;//����ָʾ�ƶ�ʱ��
extern 	uint08			near	Cover_Space_Timer;//������ʱ��ʱ��
extern 	uint08			near	RdLoadPara[CHNum][34]; //���ݱ�ʶ(4)+ʣ���¼����(1)+����֡���(1)+��ʼ��ַ(4)+ʣ����Ч��¼��(2)+����ʱ��(5)+��һ�ε���(16)
extern  uint08			near	PowerDetCnt0,PowerDetCnt1,PowerDetCnt2,PowerDetCnt3;//��Դ��������
extern	uint08			near	Resetworking_Timer;//�ز���λʱ�䶨ʱ��
extern	uint08			near	Current_Over_Count;//����բ������ֵʱ�������
extern	uint08			near	Current_Over_Count2,Current_Over_Count3;//����/ʧѹ����ʱ�������
extern	uint08			near	Current_Over_Count4,Current_Over_Count5;//�͵�ѹ/�ߵ�ѹ����ʱ�������(������ȥ��)
extern	uint16			near	Current_Over_Count41,Current_Over_Count51;//�͵�ѹ/�ߵ�ѹ����ʱ�������
extern	uint08			near	Voltage_Low_Count;//��ѹ����ʱ�������
extern	union	B32_B08		near	Loadtime;	//�ܹ����ۼ�ʱ��(��3�ֽ���Ч)
extern	uint08			near	Adj_Clk_Timer_S;//��ʱ8Mʱ�ӵ�У��ʱ��(����uartר��)
extern	uint08			near	Adj_Clk_Timer;	//��ʱ8Mʱ�ӵ�У��ʱ��

extern	uint08			near	ReportList[2];	//�ϱ�����������ϱ�����Bit[1:0]=ͣ��, Bit[3:2]=�ϵ�, Bit[5:4]=״̬
extern	uint08			near	BkupReport[2];	//�ϱ���־
extern	uint08			near	Meter_Run_Timer3;//�ϱ�״̬����ʱ
extern	uint32			near	Lost_Aver_I,Lost_V_Timer;//ʧѹ�ڼ�ƽ�������ʹ˴�ʧѹ�ۼ�ʱ��
extern 	uint08			near	Commmodule_Space_Timer;//ͨѶģ�������ʱ��
extern	uint16			near	Zb_Comm_Timer;	//�ز�ͨѶ�����ʻָ���ʱ��
extern	uint08			near	Zbbps;		//�ز�ͨѶ������
extern	uint16			near	Mod_Comm_Timer1;//ͨ��ģ�鳬ʱ��ʱ��
extern	uint08			near	Mod_Comm_Timer2;//ͨ��ģ���쳣��ʱ��ʱ��
extern  uint08  		near	Bat_Delay_Timer;//���Ƿѹ��ʱ60s
extern  uint08  		near	Bat_Change_Timer;//��ظ�����ʱ��ʱ��
extern  uint32			near 	HardFault_Flag;//HardFault��־
extern	uint08			near	Nline_Err_Count;//���ߵ����쳣ʱ�������
extern	uint08			near	Plusefiltertimer;//�������ȥ����ʱ��
extern	uint08			near	Plusefiltertimer2;//�޹��������ȥ����ʱ��
extern	uint08			near	UpdateBps;	//���²�����
extern	uint08 			near	EmuErrCnt;	//����оƬͨ�Ŵ��������
extern  uint08			near 	FlashTimer;	//falsh��Դ��Ч��ʱ�붨ʱ��
extern  uint08 			near	FreezeBuf[8];	//��ʾ�����յ���������
extern  uint32			near 	Powerd_Flag;	//�����־
extern  uint32 			near	DispBuf[10];	//��ʾ������
extern	uint08			near	LoadBuf[ee_ploadrec_lenth]; //���ɼ�¼������
extern  uint08			near	Plusevalidtimer;//�޹����嶨ʱ��
extern  uint32			near	SleepDisp_Timer;//ͣ����ʾ��ʱ��

extern  uint16			near	Ble_CF;			//����֡���
extern  uint08			near	Ble_Step;		//������ʼ������
extern  uint08			near  Ble_Buf[8];	//����͸������ͷ
extern  uint16			near	Ble_RstTimer;//������λ��ʱ��
extern  uint08			near  Ble_Reset;	//������λ��־

extern 	struct	PARA_ESAM_FRM		near	Esam_Para;	//���(6)�����(6)+�ͻ����(6)+�����֤ʱЧ(2)+Crc(2)
extern 	struct	PARA_DISPLAY_FRM	near	Display_Para;	//ѭ������(1)��ÿ����ʾʱ��(1)����ʾ����С��λ��(1) ��������(1)+ ��բ��ʱʱ�䣨2����crc��2��
extern 	struct 	COMM_ADDRESS_FRM	near	Comm_Addr;	//ͨ�ŵ�ַ(6) ��crc��2��
extern 	struct 	STARTTIME_FRM		near	Starttime;	//����ʱ�����л�ʱ�䣨5����������ʱ�α��л�ʱ�䣨5�������׷��ʵ���л�ʱ�䣨5�������׽����л�ʱ�䣨5����crc��2��
extern 	struct 	EMU_FRM			near	Emu_Para;	//����1(2)����λ1(1)������2(2)����λ2(1)+����2����(2)+����(2)����ѹϵ��(4)������ϵ��(4)������ϵ��(4)��Crc(2)
extern 	struct	PRICE_FRM		near	Price;		//��ǰ���ݵ�����16����crc��2������ǰ���ݵ�ۣ�20����crc��2������ǰ���ʵ�۱�16����crc��2��
extern 	struct 	TARIFF_FRM		near	Tariff;		//��ǰ����ʱ�α�3*14����crc��2��
extern 	struct 	ITEM_FRM		near	Item[2];	//ѭ��/������ʾ��Ŀ��1*99����crc��2��
extern 	struct	UIP_FRM			near	Emu_Data;	//��ѹ��3��+����1��3������2��3��+����1��3��+����2��3��+����������2��
extern 	struct  FUNCTION_FRM		near	Fun_Para;	//���ܲ���
extern 	struct	DECIMAL_FRM		near	Decimal;	//����β������
extern 	struct 	DISPALY_FRM		near	Display;
extern 	struct 	EEPROM_FRM		near	Eeprom;
extern 	struct 	COMMUNICATION_FRM	near	Uart[CHNum];
extern 	struct	WEEK_FRM		near	Week_Holiday;
extern 	struct	TEMPERATURE_FRM		near	Tpara;
extern 	struct 	METERCONST_FRM		near	Meter;
extern 	struct 	PARA_FEATUREWORD_FRM	near	Mode;
extern	struct	ADCDATA_FRM		near	ADCResultArr;
extern	struct	RTC_TRIM_FRM		near	RTC_RT;
extern 	struct	FEIK_FRM		near	Feik;
extern  struct  TIMER2_FRM		near  	Keeptime;	//���ߵ�����ƽ�����ʱ�䣬��������ʱ�䣬���Ƿѹ�ۼ�ʱ�䣬�����ۼ�ʱ�䣬��ع���ʱ��
extern struct	VOLLMT_FRM		near	VolLimit;	//��ѹ�ϸ��ʵ���ز���
extern struct	VOLPASS_FRM		near	VolStatus[2];	//��ѹ�ϸ����������
extern struct	BLEDEVICE_FRM		near	Ble_Connect[5];	//��������״̬��A2+A3+sta+MAC[6]

//uart-u7816
extern 	unsigned char 	near	Ic_Comm_RxBuf[u7816_buf_size]	;	//7816���ջ�����
extern 	unsigned char 	near	Ic_Comm_RxPtr			;	//7816����ָ��
extern 	unsigned char 	near	Ic_Comm_TxBuf[u7816_buf_size]	;	//7816���ͻ�����
extern 	unsigned char 	near	Ic_Comm_TxPtr			;	//7816����ָ��

extern  unsigned char 	near	Err_Sw12[2]			;	//�ݴ��������ص�SW1��SW2
extern 	unsigned char	near	PcRst8B[8]			;	//PCԶ���·��� ��ɢ���� 8�ֽ�
extern 	unsigned char	near	PcRand[8]			;	//PCԶ���·��� �����1  8�ֽ�
extern 	unsigned char	near	EsamRst8B[8]			;	//ESAM��λ��Ϣ�к�8�ֽ�
extern 	unsigned char	near	EsamRand[8]			;	//ESAM 8�ֽ������
extern 	unsigned char	near	Esam_Timer			;	//ESAM�ϵ���ʱ��λ��ʱ��

extern	RtRecord near   SynFlash; //ʱ�����ָ��
extern  MoveRec  near   MvFlash;  //��¼���Ʋ���
extern  SynRec   near	SynEe; //ͬ��EE��¼

#if(1 == CHINT_Mode)
///*�����Լ���չ�Ĺ��ܱ��������嵽����*///
extern 	struct	Ijtimer_FRM		near	Ijtimer_Para;
//extern  uint08 near Relay_Mode;	///*�̵���ģʽ 0x55-���ü̵�����,����-���ü̵�����*///
#endif

#endif


