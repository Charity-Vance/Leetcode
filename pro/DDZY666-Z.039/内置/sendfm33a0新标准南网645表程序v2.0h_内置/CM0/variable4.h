#include "FM32L0XX.h"  
#include "define4.h"
#include "stdarg.h"

const uint16 ecode BPS_SPBRGL1[9] = { 13332, 6666, 3332, 1666, 832, 417, 208, 139, 69 };		//����������16M��0��ʼ��8M��1��ʼ
//1200,2400,4800,9600,19200,38400,57600,115200

//---------------------- bit variable --------------------
B08_Bit			bdata				Meter_Status_S;			//(�ı���Ҫ����)
B08_Bit			bdata				Meter_Status1_S;		//(�ı���Ҫ����)
B08_Bit			bdata				Meter_Status2_S;		//(�ı���Ҫ����)
B08_Bit			bdata				System_Status_S;		//(ͣ�粻��)
B08_Bit			bdata				System_Status1_S;		//(ͣ������)
B08_Bit			bdata				System_Status2_S;
B08_Bit			bdata				System_Status3_S;
B08_Bit			bdata				System_Status4_S;
B08_Bit			bdata				System_Status5_S;
B08_Bit			bdata				AT7051_Flag_S;
B08_Bit			bdata				AT7051_Flag2_S;

//;=============================< IDATA �洢���� >================================
uint08			idata	run_readrtc_flag;	//��ȡʵʱʱ�ӱ�־
uint08			idata	run_display_flag;	//ˢ��LCD��ʾ��־
uint08			idata	run_relaychk_flag;	//�̵�������־
uint08			idata	reg_veri_flag;		//�Ĵ���У���־
uint08			bdata	DisKeySamp;		//��ʾ����ȥ���Ĵ���
uint08			bdata	Uart1KeySamp;		//485���Լ��ȥ���Ĵ���
uint08			idata	VectorTimer;		//���붨ʱ��
struct 	SYS_CLOCK_FRM	idata	Sclock;			//ʱ������
uint08			idata	Key_Status;		//��Կ״̬,00��ʾȫ����Կ,01��ʾȫ��˽Կ,FF���й���˽


#define NOINIT(x) __attribute__ ((at(x)))
#pragma push

#pragma O0
//#pragma arm section rwdata = "NotInit", zidata = "NotInit"


NoInit_t NoInit NOINIT(0x20000000);

//#pragma arm section 

#pragma pop


uint08			near 	Outputtype;	//0-������,1-����,2-ʱ��Ͷ���ź�,0x50-FOUT���
struct  TIMER_FRM	near	Successled,Shiduanctrl,Relayctrl;
struct  TMR_STS_FRM	near	Adcctrl;	//adcת��ʱ������ʱ��
uint16			near	Lcdled;		//���ⶨʱ��
uint32			near	Identitytimer;	//��ȫ��֤��ʱ��
uint32			near 	IR_EnTimer;	//������֤��ʱ��
uint32			near	Opendelaytimer;//��բ��ʱ��ʱ��
uint32			near	CurrentTimer;	//����բ������ʱ��
uint08			near	Relayerror_Count,Relayerror_Count1,Relayerror_Count2;//�̵������������
uint08			near	Relay_Space_Timer;//�ϵ���ʱ���Ƽ̵�����ʱ��
uint08			near	Keyclose_timer;//�����պϼ̵�����ʱ��
uint08			near	Display_Space_Timer;//���������ʾ�����ʱ��
uint16			near	Stop_Disptimer;//ͣ����ʾʱ�䶨ʱ
signed char		near	Temperature_Hex;//�����¶�(hex��)
uint16	 		near	Temperature_Adc;//��ǰ�¶�ADCֵ(hex��)
float			near	Rtcadj_Offset;//�¶Ȳ�����Уֵ
float			near	Rtcadj_Offset2;//�¶Ȳ�����Уֵ
uint08			near	RtcStopProcFlag;//ֹͣ�²���־
unsigned int		near	Hw_Lcdled_Timer;//�����������ʱ��
uint16			near	Ext_Disp_Cnt;	//��չLCD��ѯ����
uint08			near	Init_Led_Timer;//����ָʾ�ƶ�ʱ��
uint08			near	Cover_Space_Timer;//������ʱ��ʱ��
uint08			near	RdLoadPara[CHNum][34]; //���ݱ�ʶ(4)+ʣ���¼����(1)+����֡���(1)+��ʼ��ַ(4)+ʣ����Ч��¼��(2)+����ʱ��(5)+��һ�ε���(16)
uint08			near	PowerDetCnt0,PowerDetCnt1,PowerDetCnt2,PowerDetCnt3;	//��Դ��������
uint08			near	Resetworking_Timer;//�ز���λʱ�䶨ʱ��
uint08			near	Current_Over_Count;//����բ������ֵʱ�������
uint08			near	Current_Over_Count2,Current_Over_Count3;//����/ʧѹ����ʱ�������
uint08			near	Current_Over_Count4,Current_Over_Count5;//�͵�ѹ/�ߵ�ѹ����ʱ�������(������ȥ��)
uint16			near	Current_Over_Count41,Current_Over_Count51;//�͵�ѹ/�ߵ�ѹ����ʱ�������
uint08			near	Voltage_Low_Count;//��ѹ����ʱ�������
union   B32_B08		near	Loadtime;	//�ܹ����ۼ�ʱ��(��3�ֽ���Ч)
uint08			near	Adj_Clk_Timer_S;//��ʱ8Mʱ�ӵ�У��ʱ��(����uartר��)
uint08			near	Adj_Clk_Timer;	//��ʱ8Mʱ�ӵ�У��ʱ��

uint08			near	ReportList[2];	//�ϱ�����������ϱ�����Bit[1:0]=ͣ��, Bit[3:2]=�ϵ�, Bit[5:4]=״̬
uint08			near	BkupReport[2];	//�ϱ���־
uint08			near	Meter_Run_Timer3;//�ϱ�״̬����ʱ
uint32			near	Lost_Aver_I,Lost_V_Timer;//ʧѹ�ڼ�ƽ�������ʹ˴�ʧѹ�ۼ�ʱ��
uint08			near	Commmodule_Space_Timer;//ͨѶģ�������ʱ��
uint16			near	Zb_Comm_Timer;	//�ز�ͨѶ�����ʻָ���ʱ��
uint08			near	Zbbps;		//�ز�ͨѶ������
uint16			near	Mod_Comm_Timer1;//ͨ��ģ�鳬ʱ��ʱ��
uint08			near	Mod_Comm_Timer2;//ͨ��ģ���쳣��ʱ��ʱ��
uint08  		near	Bat_Delay_Timer;//���Ƿѹ��ʱ60s
uint08  		near	Bat_Change_Timer;//��ظ�����ʱ��ʱ��
uint32			near 	HardFault_Flag;//HardFault��־
uint08			near	Nline_Err_Count;//���ߵ����쳣ʱ�������
uint08			near	Plusefiltertimer;//�������ȥ����ʱ��
uint08			near	Plusefiltertimer2;//�޹��������ȥ����ʱ��
uint08			near	UpdateBps;	//���²�����
uint08 			near	EmuErrCnt;	//����оƬͨ�Ŵ��������
uint08			near 	FlashTimer;	//falsh��Դ��Ч��ʱ�붨ʱ��
uint08 			near	FreezeBuf[8];	//��ʾ�����յ���������
uint32			near 	Powerd_Flag;	//�����־
uint32 			near	DispBuf[10];	//��ʾ������
uint08			near	LoadBuf[ee_ploadrec_lenth]; //���ɼ�¼������
uint08			near	Plusevalidtimer;//�޹����嶨ʱ��
uint32			near	SleepDisp_Timer;//ͣ����ʾ��ʱ��

uint16			near	Ble_CF;			//����֡���
uint08			near	Ble_Step;		//������ʼ������
uint08			near  Ble_Buf[8];	//����͸������ͷ
uint16			near	Ble_RstTimer;//������λ��ʱ��
uint08			near  Ble_Reset;	//������λ��־

struct	PARA_ESAM_FRM		near	Esam_Para;	//���(6)�����(6)+�ͻ����(6)+�����֤ʱЧ(2)+Crc(2)
struct	PARA_DISPLAY_FRM	near	Display_Para;	//ѭ������(1)��ÿ����ʾʱ��(1)����ʾ����С��λ��(1) ��������(1)+ ��բ��ʱʱ�䣨2����crc��2��
struct 	COMM_ADDRESS_FRM	near	Comm_Addr;	//ͨ�ŵ�ַ(6) ��crc��2��
struct 	STARTTIME_FRM		near	Starttime;	//����ʱ�����л�ʱ�䣨5����������ʱ�α��л�ʱ�䣨5�������׷��ʵ���л�ʱ�䣨5�������׽����л�ʱ�䣨5����crc��2��
struct 	EMU_FRM			near	Emu_Para;	//����1(2)����λ1(1)������2(2)����λ2(1)+����2����(2)+����(2)����ѹϵ��(4)������ϵ��(4)������ϵ��(4)��Crc(2)
struct	PRICE_FRM		near	Price;		//��ǰ���ݵ�����16����crc��2������ǰ���ݵ�ۣ�20����crc��2������ǰ���ʵ�۱�16����crc��2��
struct 	TARIFF_FRM		near	Tariff;		//��ǰ����ʱ�α�3*14����crc��2��
struct 	ITEM_FRM		near	Item[2];	//ѭ��/������ʾ��Ŀ��1*99����crc��2��
struct	UIP_FRM			near	Emu_Data;	//��ѹ��3��+����1��3������2��3��+����1��3��+����2��3��+����������2��
struct  FUNCTION_FRM		near	Fun_Para;	//���ܲ���
struct	DECIMAL_FRM		near	Decimal;	//����β������
struct 	DISPALY_FRM		near	Display;
struct 	EEPROM_FRM		near	Eeprom;
struct 	COMMUNICATION_FRM	near	Uart[CHNum];
struct	WEEK_FRM		near	Week_Holiday;
struct	TEMPERATURE_FRM		near	Tpara;
struct 	METERCONST_FRM		near	Meter;
struct 	PARA_FEATUREWORD_FRM	near	Mode;
struct	ADCDATA_FRM		near	ADCResultArr;
struct	RTC_TRIM_FRM		near	RTC_RT;
struct	FEIK_FRM		near	Feik;		//��ʱ����+��ʱ�α���+��ʱ����+������+����������+г������+������+��Կ������+CRC(2)
struct  TIMER2_FRM		near	Keeptime;	//���ߵ�����ƽ�����ʱ�䣬��������ʱ�䣬���Ƿѹ�ۼ�ʱ�䣬�����ۼ�ʱ�䣬��ع���ʱ��
struct	VOLLMT_FRM		near	VolLimit;	//��ѹ�ϸ��ʵ���ز���
struct	VOLPASS_FRM		near	VolStatus[2];	//��ѹ�ϸ����������
struct	BLEDEVICE_FRM		near	Ble_Connect[5];	//��������״̬��A2+A3+sta+MAC[6]

//uart-u7816
unsigned char 	near	Ic_Comm_RxBuf[u7816_buf_size]	;	//7816���ջ�����
unsigned char 	near	Ic_Comm_RxPtr			;	//7816����ָ��
unsigned char 	near	Ic_Comm_TxBuf[u7816_buf_size]	;	//7816���ͻ�����
unsigned char 	near	Ic_Comm_TxPtr			;	//7816����ָ��

unsigned char 	near	Err_Sw12[2]			;	//�ݴ��������ص�SW1��SW2
unsigned char	near	PcRst8B[8]			;	//PCԶ���·��� ��ɢ���� 8�ֽ�
unsigned char	near	PcRand[8]			;	//PCԶ���·��� �����1  8�ֽ�
unsigned char	near	EsamRst8B[8]			;	//ESAM��λ��Ϣ�к�8�ֽ�
unsigned char	near	EsamRand[8]			;	//ESAM 8�ֽ������
unsigned char	near	Esam_Timer			;	//ESAM�ϵ���ʱ��λ��ʱ��

RtRecord near SynFlash; //ʱ�����ָ��
MoveRec  near MvFlash; //��¼���Ʋ���
SynRec   near SynEe; //ͬ��EE��¼

#if(1 == CHINT_Mode)
///*�����Լ���չ�Ĺ��ܱ��������嵽����*///
struct	Ijtimer_FRM		near	Ijtimer_Para;
//uint08 near Relay_Mode;				///*�̵���ģʽ 0x55-���ü̵�����,����-���ü̵�����*///
#endif
