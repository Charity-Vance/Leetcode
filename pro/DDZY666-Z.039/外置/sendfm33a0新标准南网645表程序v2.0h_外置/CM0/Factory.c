#include "ex_var.h"
#include "ex_func.h"
#include <string.h>


#pragma push
#pragma O0
#pragma arm section rodata = "Protected"

//��Ƶѡ��
#define	MAINCLOCK	8	//ϵͳ��Ƶ,��λM

//8MHz
#if( MAINCLOCK == 8 )
const uint08 ecode clkmode  = 0x01;
const uint32 ecode rchfcfgreg = RCC_RCHFCON_FSEL_8M;//RCHF����Ƶ��8MHz
#else//16MHz
const uint08 ecode clkmode  = 0x02;
const uint32 ecode rchfcfgreg = RCC_RCHFCON_FSEL_16M;//RCHF����Ƶ��16MHz
#endif

//�Ĵ�������
const uint32 ecode runwdtcon = IWDT_IWDTOVP_2s;//iwdt����2s
const uint08 ecode rtcosccfg = RCC_XTLFIPW_450NA;//xtlf�����������ã�Ĭ��450nA
const uint32 ecode SleepBorCfg = 0x00000001;//�ر�BOR	
const uint32 ecode SleepPdrCfg = 0x00000007;//��PDR 1.4V	
const uint32 ecode RunBorCfg = 0x00000002;//��BOR 1.6V
const uint32 ecode RunPdrCfg = 0x00000007;//��PDR 1.4V	
const uint08 ecode Compile_LvdLvCfg = ANAC_SVDCFG_SVDLVL_4_157v;//ANAC_SVDCFG_SVDLVL_4_371v;
const uint32 ecode Runet1Outcnt = 0x00000a3e;//80ms������������üĴ���(�ݲ�֧��)
const uint08 ecode Runrtctmls = RTC_FSEL_FSEL_PLL_1S;	//ʹ����ʱ�����,�������л��ź�
const uint32 ecode IRDutyCycleCfg = BIT14|BIT13;//Mclk=8Mʱ38k���� ռ�ձ�Y(73.9%) = (TZBRG[10:4]*TH)/(TZBRG+1)=(13*12)/��210+1��,���������ܷ�����Ϊ26.1% 

//���ܱ���
#define RELAYTYPE 	0x55 	//0x55:���ü̵���������:���ü̵���
#if( RELAYTYPE == 0x55 )
const uint08 ecode Relay_Mode = 0x55;		//0x55-���ü̵�����(�������޸ĳ�80A),����-���ü̵�����(�������޸ĳ�60A)
#else
const uint08 ecode Relay_Mode = 0x00;		//0x55-���ü̵�����(�������޸ĳ�80A),����-���ü̵�����(�������޸ĳ�60A)
#endif

#if(1 == CHINT_Mode)
///*ͨ��Э����ַ������޸ģ����ձ���ͺ�����*///
//				01		//Զ�� ���ü̵��� ���õ��

//				02		//���� ���ü̵��� ���õ��

//				03		//Զ�� ���ü̵��� ���õ��

//				04		//���� ���ü̵��� ���õ��

//				05		//Զ�� ���ü̵��� ���õ��
 
//				06		//���� ���ü̵��� ���õ��

//				07		//Զ�� ���ü̵��� ���õ��

//				08		//���� ���ü̵��� ���õ��
const unsigned char ecode C_ucSoftVerForFactory[] = {
			0x11,		
			0x20,		///*����汾��3���ַ�*///	
			0x99,												
			0x31,		///*��·���5���ַ�*///	
			0x3F, 		///*ͨ�ŷ�ʽ2���ַ���3F���ز���485�����⡢΢���ʡ�GPRS*///										
			0x07, 		///*ͨ�Ź�Լ1���ַ���02��֧��DL/T645-2007*///											
			0xF0, 													
			0xFF		///*�г�����4���ַ�*///													
};
#endif

//��������
const uint08 ecode Correction_Mode = 0x55;	//0x55-������ѹ��������,����-�ر�(Ŀǰrn8209c��ht7017֧��)
const uint08 ecode Rn8209c_Mode = 0x55;		//0x55-RN8209C����Ӳ�����Ȳ�������,����-�ر�
const uint08 ecode Compile_Polar_485 = 0x00;	//0x55-�����޼���485,����-ֻ֧���м���485
const uint08 ecode Memoryerr_Ctrl = 0x00;	//0x55-����洢���ϱ�,����-��ֹ�洢���ϱ�(����ر�)
const uint08 ecode FlashPowerOff_Ctrl = 0x55;	//0x55-����ʱflash��Դ�ر�,����-����ʱflash��Դ��
const uint08 ecode EsamPowerOff_Ctrl = 0x55;	//0x55-����ʱesam��Դ�ر�,����-����ʱesam��Դ��
const uint08 ecode Wwdt_Lcd_Ctrl = 0x00;	//0x55-HardFault_Flag����wwdt��λ���⴦��,����-��׼���
const uint08 ecode RTC_Trim_Ctrl = 0x55;	//0x55-��������0.119ppm������-��������0.238ppm(��404ģʽ�¿ɿ���0.119)
const uint08 ecode SleepPtatOffsetCfg = 0x55;	//0x55-����3Vƫ��(3V��Դptatƫ�ÿ��ƿ���)������-�ر� 
const uint08 ecode Extbattery = 0x55;		//0x55-������ã�����-�������
const uint08 ecode ExtVoltage = 0x55;		//0x55-�ⲿ������(������û��dataflash��)������-�ڲ�������

//�汾�͹��
const unsigned char ecode Verdate[24] =  "NWXXXX-M02021-211009-H20";   //����,�汾�ż��汾���� 
const unsigned char ecode RatedVolt[6] = "220.0V";	//���ѹ
const unsigned char ecode RatedCurr[6] = "5.0A";		//�����/��������
#if( RELAYTYPE == 0x55 )
const unsigned char ecode MaxCurr[6] = "80.0A";	//������
#else
const unsigned char ecode MaxCurr[6] = "60.0A";	//������
#endif
const unsigned char ecode MinCurr[6]  = "0.25A";   //��С����
const unsigned char ecode TrtCurr[6]  = "0.5A";    //ת�۵���
const unsigned char ecode ActiveClass[4] = "A";	//�й�׼ȷ�ȵȼ�
const unsigned char ecode ReActiveClass[4] = "2.0";//�޹�׼ȷ�ȵȼ�
const unsigned char ecode MaterType[32] = "";	//����ͺ�
const unsigned char ecode ProtocolVer[16] = "DL/T645-2007-21";//Э��汾��
const unsigned char ecode SoftwareVer1[32] = "00000000000000000000000000000000";	//��������汾��
const unsigned char ecode HardwareVer1[32] = "00000000000000000000000000000000";	//����Ӳ���汾��
const unsigned char ecode FactoryNum[32] = "00000000000000000000000000000000"; //���ұ��
const unsigned char ecode Softbk[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	//���������
const unsigned char ecode Facdate[10] = "";	//��������
#if( RELAYTYPE == 0x55 )
const unsigned long ecode Def_Meterconst_Bcd = 0x2000;	//���峣��Ĭ��2000
const unsigned char ecode Def_Meterconst_Hex = 20;	//���峣��Ĭ��2000
#else
const unsigned long ecode Def_Meterconst_Bcd = 0x2000;	//���峣��Ĭ��2000
const unsigned char ecode Def_Meterconst_Hex = 20;	//���峣��Ĭ��2000
#endif
const unsigned char ecode Def_Plusevalidtimer = 20;	//80ms������(ͬ��ͨѶ)
const unsigned char ecode resetworking_timer_delay=60;	//240ms��λ�ز�оƬʱ��
const unsigned char ecode Bps_9600 = 0x20;		//Ĭ���ز�ͨѶ������9600
const unsigned short ecode Zb_Comm_Timer_delay = 2160;	//36h�ز�ͨѶ�����ʻָ���ʱ�� 
const unsigned short ecode Mod_Comm_Timer_delay1= 2160;	//36hͨ��ģ�鳬ʱ��ʱ�� 
const unsigned char ecode Mod_Comm_Timer_delay2 = 5;	//5minͨ��ģ���쳣��ʱ��ʱ��
const unsigned char ecode Def_Erase_Times = 5; 		//���������ظ������Ĵ���

//�¶�������ز���
const float ecode const_xtl_top	= 25.0;		//�����¶�����ʹ�õĶ���
#if((CHINT_TemperatureMode == 1))
const float ecode const_KL	= 0.02919;		//�����¶Ȳ���ϵ��
const float ecode const_KH	= 0.03525;
#else
const float ecode const_KL	= 0.0300;		//���Ժ�¶Ȳ���ϵ��
const float ecode const_KH	= 0.0382;
#endif
const float ecode const_TmpsL	= 5.0379;	//�¶�ADCб��
const float ecode const_TmpsH	= 5.0379;
const uint08 ecode constF_Volt	= 0;		//��ѹ������(������Ӳ��������Ӷ�����),3��ʾ0.03v/10��ʾ0.1v
const uint16 ecode const_adc_TrimB = 0x3ff;
const uint16 ecode const_adc_TrimT = 0x640;
const uint16 ecode const_KHKL_TrimRange = 36;//���������޵����ֽܷ緶Χ��25�ȡ�7����ʹ�ó����޵�ֵkrh��krl����Χ��ʹ�øߵ����޵�ֵkh��kl
const float ecode const_T_OffsetRun	= -3.0;	//оƬ��������-������
const float ecode const_T_OffsetSlp	= -2.0;	//оƬ��������-������
const uint08 ecode const_TopNoTrim = 0x55;  //�����x�ȸ��������� 0x55:�������� 0x00:��������
const uint08 ecode const_TopNTRange = 8;	//���㸽���ر��Զ������¶�adc��Χ����x/5.0379=�¶ȷ�Χ
#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У	
const float ecode const_T_CL	= -23.0;	//���²�������¶�
const float ecode const_T_CH	= 62.0;		//���²�������¶�(����57.0)
const uint08 ecode const_C_Mode = 0x55;		//0x55:�����ߵ��¸߾��Ȳ���ܣ����������������¸߾��Ȳ��
#else
const uint16 ecode const_adc_Min  = 900; 	//�¶�adc��С��Чֵ
#endif

//�̵������
const uint08 ecode Relaytimer_Delay_N = 30;	//120ms���ü̵�����ƽ��ʱ
const uint08 ecode Relaytimer_Delay_W = 98;	//400ms�����ü̵�����ƽ��ʱ
const uint08 ecode Defaultspacetimer = 5;	//Ĭ��Ԥ��բ���ʱ��(5min)
const uint08 ecode Defrelayerrorcnt_s = 0;	//�̵��������ʾȥ����ʼ����
const uint08 ecode Defrelayerrorcount = 3;	//�̵��������ʾȥ������(ÿ��0.5s)
const uint08 ecode Defrelayerrorcount_r = 10;	//�̵��������ϼ�¼ȥ������(ÿ��0.5s)

//energy
const uint08 ecode Def_Dl_Difference = 100;	//��������-����������ֵ����������ֵ,Ĭ��100������
const uint08 ecode Def_Plusefiltertimer = 6;	//20ms��������˲�(Ϊ0��ʾ��֧��Ӳ���˲�)
const uint08 ecode Def_Plusefiltertimer2 = 6;	//20ms��������˲�(Ϊ0��ʾ��֧��Ӳ���˲�)(�޹�)
const uint08 ecode Adjclk_timer_delay_s = 90;	//�޼���ͨѶ90s������8Mʱ�ӵ�У����,���Ϊ0��رն�ʱ8Mʱ�ӵ�У����
const uint08 ecode Adjclk_timer_delay =  6;	//��ͨѶ6h������8Mʱ�ӵ�У����,���Ϊ0��رն�ʱ8Mʱ�ӵ�У����
const uint16 ecode Defendenergyvoltage = 0;	//���Ϊ0x1250��ʾ125v�رռ���,���Ϊ0���ֹ�رռ���(�������ó�0)
const uint08 ecode Def_Shielding_I1 = 0x15;	//��������������ֵ15mA
const uint08 ecode Def_Shielding_I2 = 0x20;	//���������������ֵ20mA
const uint08 ecode Def_Shielding_Cos = 0x50;	//������������λ��Сֵ0.05
const uint08 ecode Defcurrovercount = 3;	//��բ�����жϳ�������ȥ��ʱ��
const uint16 ecode Defaultpdvoltage = 0x1320;	//Ĭ�ϵ����ѹֵ(60%Un)
const uint08 ecode Defaultpddelay = 3;		//����ȥ��ʱ�䣬Ĭ��3s
const uint08 ecode Deflowvoltagecount_s = 1;	//Ĭ�ϵ����¼�ϵ�ȥ��ʱ��
const uint08 ecode Deflowvoltagecount = 3;	//Ĭ�ϵ����¼�ϵ�ȥ��ʱ��(���߸���60%ȥ��ʱ��)
const int16  ecode Uoffset = 0;			//Ĭ�ϵ�ѹϵ��ƫ����
const uint08 ecode Def_Powerdetcnt2 = 11;	//����170v��8s���ڲŽ��е�Դ�쳣���,�ϵ�Ĭ�ϵ���170vԼ11s
const uint08 ecode ht7017_mclk = 2;		//ht7017��Ƶ:1��ʾ1M,2��ʾ2M (2Mʱ��λ���·���hfconstҲ��Ҫ*2)
const uint32 ecode Def_SelfHeat_I = 0x59000; 	//���Ȳ�������Ĭ��ֵ��59A
const uint08 ecode Def_SelfHeat_Cancel = 60; 	//�����������Ȳ����������60s�󣬲��˳�����
const uint32 ecode Def_Device_Id = 0x7f820900;	//Ŀǰ��֧��rn8208cоƬ�Ķ������ڹ����ж�

//interrupt
const uint08 ecode Fulllcdbias = 0x06;		//ȫ����ʾƫ�õ�ѹ
const uint08 ecode Runlcdbias = 0x04;		//����Һ����ʾƫ�õ�ѹ
const uint08 ecode RunlLCDSET 	= B0001_0001;//1/3bias�� A���Σ� 6com
const uint08 ecode RunlLCDDRV 	= B0000_0001;//�������Ƭ�ڵ�������
const uint08 ecode Sleeplcdfreq = 54;		//25Hz@6com;	
const uint08 ecode SleepLCDSET = B0001_0101;//1/3bias�� B���Σ� 6com
const uint08 ecode SleepLCDDRV = B0000_0011;//�����δ�Ƭ�ڵ�������
const uint16 ecode Sleepvthreshold[6] = {0x540,0x600,0x680,0x760,0x840,0x920};//ͣ��Һ����ʾ��ѹ̨��,����0x600��ʾ3.00v
const uint08 ecode Sleeplcdbias[6] = {0x0f,0x0e,0x0d,0x0b,0x08,0x05};//ͣ��Һ����ʾƫ�õ�ѹ(����3vҺ������)
const uint08 ecode def_powerdown_timer = 2+1; //ͣ���ϱ�Ĭ��������ʱ��(���ڼ�⵽�����ÿ�뷢һ��,����3��),��λ��
const uint08 ecode def_meterrun_timer = 60;//����ϵ�����ʱ��,��λ����(�������1Сʱֹͣͣ����ϵ��ϱ�)
const uint08 ecode def_coverdelaytimer = 3;//Ĭ�Ͽ���ȥ��ʱ��

//����
const uint16 ecode Defaultauthtimer = 0x30;	//Ĭ�������֤ʱЧ(30min)
const uint08 ecode Defaultstartup = 0x00;	//Ĭ������ʱ��ȫ0x00����ȫ0x99
const uint08 ecode MAX_PSW_NUM = 32;		//�����Կ��Ĭ��32��
const uint08 ecode Defpassworderrcnt = 5;	//�������5�α���
const uint16 ecode Def_Vthreshold = 0x300;	//���Ƿѹ��ֵ,����0x300��ʾ3.00v
const uint16 ecode Def_Vthreshold_H = 0x340;	//���Ƿѹ�ָ���ֵ,����0x340��ʾ3.40v
const uint16 ecode Def_Relay_ActL = 0x1500;	//�̵���������ѹ��ֵL
const uint16 ecode Def_Relay_ActH = 0x2750;	//�̵���������ѹ��ֵH
const uint16 ecode Def_Relay_Det = 0x1500;	//�̵�������ѹ��ֵ

//lcd
const unsigned long ecode disp_table[disp_num]=
{
	//0x200/0x800��1~169��	��ǰ����12����ϵ���
	//0x200/0x800��170��	��ǰ����12���������
	//0x200/0x800��339��	��ǰ����12�·������
	//0x200/0x800��508��	��ǰ����12������޹�1����
	//0x200/0x800��677��	��ǰ����12������޹�2����
	//0x200/0x800��846��	��ǰ����12�µ�һ�����޹�����
	//0x200/0x800��1015��	��ǰ����12�µڶ������޹�����
	//0x200/0x800��1184��	��ǰ����12�µ��������޹�����
	//0x200/0x800��1353��	��ǰ����12�µ��������޹�����
	0xffffffff,		//ȫ��200
	0x00000c00,		//�����õ���201
	0x01000c00,		//�����õ���202
	0x03070004,		//485ͨ�Ų�����
	0x00010102,		//��ѹ(A��)204
	0x00010202,		//����(A��)205
	0x00000302,		//����(��)206
	0x00010302,		//����(A��)207
	0x00000602,		//��������(��)208	
	0x00010602,		//��������(A��)209
	0x01008002,		//���ߵ���210
	0x09040004,		//����211
	0x010b0004,		//��1������212
	0x020b0004,		//��2������213
	0x030b0004,		//��3������214
	0x0e040004,		//���ŵ�215
	0x0e040004,		//���Ÿ�216
	0x02040004,		//��ŵ�217
	0x02040004,		//��Ÿ�218
	0x01040004,		//ͨѶ��ַ��219
	0x01040004,		//ͨѶ��ַ��220
	0x01010004,		//����221
	0x02010004,		//ʱ��222
	0x01003003,		//���һ�α������223
	0x01003003,		//���һ�α��ʱ��224
	0x01013003,		//���һ����������225
	0x01013003,		//���һ������ʱ��226
	0x00000d00,		//��ǰ���õ���227
	0x01000d00,		//�ϴ����õ���228
	0xcccccccc,		//Ԥ��229
	0x02008002,		//Ƶ��230
	0x00000402,		//�޹�����(��)231
	0x00010402,		//�޹�����(A��)232
	0x00007000,		//��ǰ��ϵ���(�߾���)233
	0x00007100,		//��ǰ�������(�߾���)234
	0x00007200,		//��ǰ�������(�߾���)235
	0x00007300,		//��ǰ����޹�1����(�߾���)236
	0x00007400,		//��ǰ����޹�2����(�߾���)237
	0x00007500,		//��ǰ��ϵ�һ�����޹�����(�߾���)238
	0x00007600,		//��ǰ��ϵڶ������޹�����(�߾���)239
	0x00007700,		//��ǰ��ϵ��������޹�����(�߾���)240
	0x00007800,		//��ǰ��ϵ��������޹�����(�߾���)241
};


//factory
const unsigned char ecode  Def_Limitmenory_table[]=
{
	0x00,0x00,0x10,0x00,		//͸֧�����ֵxxxxxx.xx
	0x00,0x20,0x00,0x00,		//�ڻ������ֵxxxxxx.xx
	0x00,0x00,0x02,0x00,		//��բ��������ֵxxxxxx.xx
};

const unsigned char ecode Def_DisplayPara_table[ee_displaypara_lenth]=
{
	7,			//�Զ�ѭ����ʾ����
	5, 			//ÿ����ʾʱ��    
	2, 			//��ʾ����С��λ��
	4, 			//��ʾ����С��λ��
	25,			//����ѭ����ʾ����
	0,			//Ԥ��
	0,			//Ԥ��
	5,			//�ϵ�ȫ��5s   
	0x13,0x01,0x01,0x00,0x00,//���ɼ�¼��ʼʱ��(������ʱ��)
	0x00,0x15,		//��1~5�ฺ�ɼ�¼���ʱ��	
	0x00,0x15,
	0x00,0x15,
	0x00,0x15, 
	0x00,0x15, 
	0x00,0x15,		//����й����ʵ��ܸ��ɼ�¼���ʱ��  
	0x00,0x15, 
	0x00,0x15,    
};

const unsigned char ecode Def_SleepDisplayPara_table[8]=	//ͣ����ʾ����
{
	4,	//�Զ�ѭ����ʾ����
	5, 	//ÿ����ʾʱ��    
	2, 	//��ʾ����С��λ��
	4, 	//��ʾ����С��λ��
	4,	//����ѭ����ʾ����
	0,	//Ԥ��
	0,	//Ԥ��
	5,	//�ϵ�ȫ��5s   
};

const unsigned short ecode Def_Sleepdisp_table[16]=	//ͣ����ʾ��
{    
	0x2AA,	 // �����й��ܵ���
	0x353,	 // �����й��ܵ���
	215,	 // ���ŵ�8λ
	216,	 // ���Ÿ�4λ
	1,	 // Ԥ��5
	1,	 // Ԥ��6      
	1,	 // Ԥ��7      
	1,	 // Ԥ��8      
	1,	 // Ԥ��9
	1,	 // Ԥ��10      
	1,	 // Ԥ��11      
	1,	 // Ԥ��12      
	1,	 // Ԥ��13      
	1,	 // Ԥ��14      
	1,	 // Ԥ��15      
	1,	 // Ԥ��16     
};


const unsigned char ecode Def_featureword_table[]=
{
	0x20,		//ͨ�ſ�1 ������������	04000703	20H��9600bps��        
	0x05,		//�й���Ϸ�ʽ������	04000601	05H�������й�+�����й�)
	0,0,0,0, 	//Ԥ��4�ֽ�
	0x03,		//ͣ���¼��ж���ʱ(bcd��) Ĭ��3s
	0x60,		//�����ϱ��ϱ�ʱ��(bcd��) Ĭ��60min
	0x08,		//�������������1,04Ϊ���ú���֡,08Ϊ���������ϱ�
	0xbb,		//�ϱ�ģʽ��1/���ڿ���ʼ������	
	0x04,		//�ϱ�ģʽ��2/����
	0x00,		//�ϱ�ģʽ��3/null
	0x00,		//�ϱ�ģʽ��4/null
	0x20,		//�ϱ�ģʽ��5/����
	0x00,		//�ϱ�ģʽ��6/null
	0x00,		//�ϱ�ģʽ��7/null
	0x00,		//�ϱ�ģʽ��8/null
	0x03,0x00,0x00,	//�̵�����բ���Ƶ�������ֵ(XXX.XXX)
	0x00,0x00,  	//��բ��ʱʱ��(bcd��)
	0x14,0x40,	//�������բ��ʱ(bcd��)
	0x30,		//������֤(bcd��)
	0x30,		//�ϱ���λ��ʱ(bcd��)
	0x00,		//���ü̵���0x55��ʾ�Զ���բ,���ü̵���0x55��ʾ�ֶ���բ
	0x80,		//��չģʽ��,bit7=1����λ�ز�(��Ҫ�����˹���ز�),bit2=1����ң������������,bit1=1Ƿѹ��������,bit0=1�����������
	0x41,		//�޹���Ϸ�ʽ������1	04000602	1+4
	0x14,		//�޹���Ϸ�ʽ������2	04000603	2+3
	0x20,		//ͨ�ſ�3 ������������	04000705	20H��9600bps�� (�ز�) 
	0x00,		//Ԥ��
};


const unsigned char ecode Def_weekloadpara_table[]=
{
	0x7F,				//������������7F����������������Ϣ��
	0x01,				//�����ղ��õ���ʱ�α��1����һ�׵�1��ʱ�α�
	0x01,0x1f,			//����ģʽ��
	0x00,0x83,			//��ʱ��������ģʽ�֣���ʱ���������й����ܡ������й����ܡ�����޹�1������޹�2���������޹���������
	0x00,0x83,			//˲ʱ��������ģʽ�֣�˲ʱ���������й����ܡ������й����ܡ�����޹�1������޹�2���������޹���������
	0x00,0x83,			//Լ����������ģʽ�֣�Լ�����������й����ܡ������й����ܡ�����޹�1������޹�2���������޹���������
	0x00,0x03,			//���㶳������ģʽ�֣����㶳�������й��ܵ��ܡ������й��ܵ��ܣ� 
	0x00,0x83,			//�ն�������ģʽ�֣��ն��������й����ܡ������й����ܡ�����޹�1������޹�2���������޹���������
	0x00,0x83,			//�¶�������ģʽ�֣��¶��������й����ܡ������й����ܡ�����޹�1������޹�2���������޹���������
	0x00,				//Ԥ��1�ֽ�
#if(RELAYTYPE == 0x55)
	0x09,0x60,   			//������������1.2Imax,96.0A
#else
	0x07,0x20,   			//������������1.2Imax,72.0A
#endif
	0x60,				//������ʱʱ��,60s   
	0x00,0x01,0x00,0x00,		//������������,1.0A NNNN.NNNN(698Э��)(20%Ib)
	0x50, 0x00, 			//���ߵ�����ƽ����ֵ, 50.00%
	0x60,         			//���ߵ�����ʱ, 60s       
};


//��ѹ�ϸ��ʲ���
const unsigned char ecode Def_vollmtpara_table[]=
{
	0x23, 0x54,			//��ѹ����ֵ   107%Un = 235.4V
	0x19, 0x80,			//��ѹ����ֵ    90%Un = 198.0V
	0x26, 0x40,			//��ѹ�������� 120%Un = 264.0V
	0x15, 0x40,			//��ѹ��������  70%Un = 154.0V
	
	0x17, 0x16,			//ʧѹ�¼���ѹ��������   78%Un = 171.6V
	0x18, 0x70,			//ʧѹ�¼���ѹ�ָ�����    85%Un = 187.0V
	0x00,0x00,0x02,0x50,		//ʧѹ�¼�������������,25mA NNNN.NNNN(698Э��)(0.5%Ib)
	0x60,         			//ʧѹ�¼���ʱ�ж�ʱ��, 60s 
	
	0x19, 0x80,			//�͵�ѹ�¼���ѹ��������    90%Un = 198.0V
	0x06, 0x00,			//�͵�ѹ�¼���ʱ�ж�ʱ��, 10h = 600min
	0x23, 0x54,			//�ߵ�ѹ�¼��¼���ʱ�ж�ʱ��   107%Un = 235.4V
	0x12, 0x00,			//�ߵ�ѹ�¼���ʱ�ж�ʱ��, 20h = 1200min
	
	0x60,				//���������ж���ʱ,Ĭ��60s
};

//ѭ����ʾĬ��֧��31���ʼ��,������������޸ı��ʵ��,ֻ��ͨѶ����ʵ��
const unsigned short ecode Def_Autodisp_table[31]=
{    
	221, 	// ����
	222, 	// ʱ��
	0x201,	// ����ܵ���
	0x54E,	// ��ǰ��һ�����޹��ܵ���
	0x5F7,	// ��ǰ�ڶ������޹��ܵ���
	0x6A0,	// ��ǰ���������޹��ܵ���
	0x749,	// ��ǰ���������޹��ܵ���
	0x201,	// Ԥ��8
	0x201,	// Ԥ��9
	0x201,	// Ԥ��10      
	0x201,	// Ԥ��11      
	0x201,	// Ԥ��12      
	0x201,	// Ԥ��13      
	0x201,	// Ԥ��14      
	0x201,	// Ԥ��15      
	0x201,	// Ԥ��16 
	0x201,	// Ԥ��17
	0x201,	// Ԥ��18
	0x201,	// Ԥ��19
	0x201,	// Ԥ��20
	0x201,	// Ԥ��21
	0x201,	// Ԥ��22
	0x201,	// Ԥ��23
	0x201,	// Ԥ��24
	0x201,	// Ԥ��25
	0x201,	// Ԥ��26
	0x201,	// Ԥ��27
	0x201,	// Ԥ��28
	0x201,	// Ԥ��29
	0x201,	// Ԥ��30
	0x201,	// Ԥ��31     
};

//������ʾĬ��֧��62���ʼ��,������������޸ı��ʵ��,ֻ��ͨѶ����ʵ��
const unsigned short ecode Def_Keydisp_table[62]=
{
	219, 	// ͨѶ��ַ��8λ    
	220, 	// ͨѶ��ַ��4λ
	221, 	// ����             
	222, 	// ʱ�� 
	204, 	// ��ѹ
	205, 	// ����
	207, 	// ����A��
	232, 	// ����A��
	209, 	// ��������A��  
	215, 	// ���ŵ�8λ
	216, 	// ���Ÿ�4λ
	0x201,	// ��ʾ����ܵ���
	0x202,	// ��ʾ��ϼ����
	0x203,	// ��ʾ��Ϸ����
	0x204,	// ��ʾ���ƽ����
	0x205,	// ��ʾ��Ϲȵ���
	0x54E,	// ��ǰ��һ�����޹��ܵ���
	0x5F7,	// ��ǰ�ڶ������޹��ܵ���
	0x6A0,	// ��ǰ���������޹��ܵ���
	0x749,	// ��ǰ���������޹��ܵ���
	0x20E,	// ��ʾ����ܵ���  ��1��
	0x20F,	// ��ʾ��ϼ����  ��1��
	0x210,	// ��ʾ��Ϸ����  ��1��
	0x211,	// ��ʾ���ƽ����  ��1��
	0x212,	// ��ʾ��Ϲȵ���  ��1��
	0x201,	// Ԥ��26
	0x201,	// Ԥ��27
	0x201,	// Ԥ��28
	0x201,	// Ԥ��29
	0x201,	// Ԥ��30
	0x201,	// Ԥ��31
	0x201,	// Ԥ��32
	0x201,	// Ԥ��33
	0x201,	// Ԥ��34
	0x201,	// Ԥ��35
	0x201,	// Ԥ��36
	0x201,	// Ԥ��37
	0x201,	// Ԥ��38
	0x201,	// Ԥ��39
	0x201,	// Ԥ��40
	0x201,	// Ԥ��41
	0x201,	// Ԥ��42
	0x201,	// Ԥ��43
	0x201,	// Ԥ��44
	0x201,	// Ԥ��45
	0x201,	// Ԥ��46
	0x201,	// Ԥ��47
	0x201,	// Ԥ��48
	0x201,	// Ԥ��49
	0x201,	// Ԥ��50
	0x201,	// Ԥ��51
	0x201,	// Ԥ��52
	0x201,	// Ԥ��53
	0x201,	// Ԥ��54
	0x201,	// Ԥ��55
	0x201,	// Ԥ��56
	0x201,	// Ԥ��57
	0x201,	// Ԥ��58
	0x201,	// Ԥ��59
	0x201,	// Ԥ��60
	0x201,	// Ԥ��61
	0x201,	// Ԥ��62  
};

const unsigned char ecode Def_freezeparameter_table[]=
{
	0x10,0x01,0x01,0x00,0x00,	//���㶳����ʼʱ��	10��01��01��00ʱ00��
	0x60,				//���㶳��ʱ����	60����
	0x00,0x00,			//�ն���ʱ��		00ʱ00��
	0x99,0x99,0x12,0x00,		//��ʱ����ʱ��		12ʱ00��
};

const unsigned char ecode Def_feik_table[]=
{
	0x02,  //��ʱ����	2                                               
	0x02,  //��ʱ�α���	2                                               
	0x08,  //��ʱ���� 	8                                               
	0x04,  //������	4                                               
	0x00,  //����������	0�������ã�����ʱ���ٿ�����1��14�չ������ղ�����
	0x00,  //г����������	0                                               
	0x02,  //������	2        
	0x11,	//��Կ�������õ�����                                
};

//������
const unsigned char ecode Def_histroyparameter_table[]=
{
	0x00,0x01,	//01��00��
	0x99,0x99,
	0x99,0x99,
};

//����
const unsigned char ecode Def_Password3_table[]=
{
	0x03,0x00,0x00,0x33,
};

const unsigned char ecode Def_Password4_table[]=
{
	0x04,0x11,0x11,0x11,
};

//ʱ����1
const unsigned char ecode Def_sqb_table1[]=
{
	0x01,0x22,0x06,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
};

//ʱ����2
const unsigned char ecode Def_sqb_table2[]=
{
	0x01,0x22,0x06,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
	0x02,0x28,0x12,	   //ʱ�α�š��ա���
};


//ʱ�α�1
const unsigned char ecode Def_sdb_table1[]=
{										//���ʺ�,��,ʱ,���14��
	0x01,0x00,0x00,        
	0x02,0x00,0x08,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
	0x03,0x00,0x16,
};

//ʱ�α�2
const unsigned char ecode Def_sdb_table2[]=
{										//���ʺ�,��,ʱ,���14��
	0x01,0x00,0x00,        
	0x02,0x00,0x06,
	0x03,0x00,0x12,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
	0x04,0x00,0x18,
};

//��ǰ����ʱ����
const unsigned char ecode Def_jtshiqu_table[]=
{										//���ݱ��ź�+��+��
	0x01,0x01,0x01,        
	0x02,0x01,0x05,
	0x01,0x01,0x11,
	0x01,0x01,0x11,
};

//���ý���ʱ����
const unsigned char ecode Def_jtshiqu_table2[]=
{										//���ݱ��ź�+��+��
	0x01,0x01,0x01,        
	0x02,0x01,0x05,
	0x01,0x01,0x11,
	0x01,0x01,0x11,
};
#pragma arm section 
#pragma pop


