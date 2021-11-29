#ifndef	__DEFINE_H__
#define __DEFINE_H__

//���峣��, ����
#include "bintohex.h"
#include "FM32L0XX.h"

#if   defined (__CC_ARM)  

#define ecode   
#define bdata
#define idata
#define near
#define code    
#define xdata
#define reentrant
#define bit unsigned char
#define huge
#else

#endif

#define	ESAMON			1	  //�Ƿ���ESAM��  0:�ޣ�1:��

#define	CHINT_Mode 1	///*��̩ģʽ�������ڸ���΢ԭʼ����Ĳ��ַ���ȶ� 1����̩ 0������΢*///	

#define CHINT_TemperatureMode 1	///*0 ���Ժ     1  ����*///

//uart ������˳����
#define CHHW	0
#define CH485	1
#define CHZB	2
#define CHBLE	3
#define	CHNum	4

#define	NEWCLOCKADJ	0	  //ʱ�ӵ�У��0:�ɱ�׼ʱ�ӵ�У; 1:��ʱ�ӵ�У(�������β�������)

//��0x811800��ʼ�ᱣ��������Ϣ
#define HXVAR(object, addr)   (*((object ecode *) (addr)))
#define const_tx_flag  		HXVAR( uint16, 0x1ffffa20 ) //��У��־(0x3cc3Ϊ��̵�У)
#define const_rtc_adj_top 	HXVAR( int16,  0x1ffffa36 ) //�������ppm,0.01ppm
#define const_temp_TestA 	HXVAR( uint08, 0x1FFFFC90 )	//����ʱ�¶�����λ
#define const_temp_TestB 	HXVAR( uint08, 0x1FFFFC91 )	//����ʱ�¶�С��λ
#define const_adc_Test	 	HXVAR( uint16, 0x1FFFFC92 )	//����ʱPTAT ADCֵ
#define const_rchf_Trim8 	HXVAR( uint32, 0x1FFFFD40 )	//RC8M У׼ֵ
#define const_rchf_Trim16 	HXVAR( uint32, 0x1FFFFD3C )	//RC16M У׼ֵ
#define const_adc_Slope 	HXVAR( uint16, 0x1FFFFC54 )	//ADCб�ʣ�Լ2.2mV/lsb
#define const_adc_Offset 	HXVAR( int16,  0x1FFFFC56 )	//ADC�ؾ�
#define const_ptat_Offset3V	HXVAR( uint08, 0x1FFFFC94 )	//ptat 5v3v��ֵ
#define const_mark404		HXVAR( uint16, 0x1FFFFC0E )	//404���

#define LCDLEDON	GPIO_ResetBits(GPIOE, GPIO_Pin_2)
#define LCDLEDOFF	GPIO_SetBits(GPIOE, GPIO_Pin_2)
#define LCDLEDTOG	GPIO_ToggleBits(GPIOE, GPIO_Pin_2)

#define SHIDUANCTRL_ON	GPIO_SetBits(GPIOG, GPIO_Pin_6)
#define SHIDUANCTRL_OFF GPIO_ResetBits(GPIOG, GPIO_Pin_6)

#define RELAYON2 	GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define RELAYOFF2 	GPIO_ResetBits(GPIOD, GPIO_Pin_4)
#define RELAYON1 	GPIO_SetBits(GPIOD, GPIO_Pin_5)
#define RELAYOFF1 	GPIO_ResetBits(GPIOD, GPIO_Pin_5)

#define RELAYON3 	GPIO_SetBits(GPIOD, GPIO_Pin_4)		//����
#define RELAYOFF3 	GPIO_ResetBits(GPIOD, GPIO_Pin_4)	

#define PULSELED_ON	GPIO_ResetBits(GPIOB, GPIO_Pin_6)	//Ԥ��	
#define PULSELED_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_6)		//Ԥ��
#define PULSELED_TOG	GPIO_ToggleBits(GPIOB, GPIO_Pin_6)	//Ԥ��	

#define EVENOUTOFF 	GPIO_ResetBits(GPIOE, GPIO_Pin_5)	//���¼��ϱ�
#define EVENOUTON 	GPIO_SetBits(GPIOE, GPIO_Pin_5)		//���¼��ϱ�
#define PLC_RST0 	GPIO_ResetBits(GPIOF, GPIO_Pin_5)
#define PLC_RST1 	GPIO_SetBits(GPIOF, GPIO_Pin_5)

#define ESAMVCC_P 	(GPIOD->ODR&GPIO_Pin_7) == GPIO_Pin_7
#define ESAMVCC_N 	(GPIOD->ODR&GPIO_Pin_7) != GPIO_Pin_7
#define ESAMPOWERON	GPIO_ResetBits(GPIOD, GPIO_Pin_7)
#define ESAMPOWEROFF	GPIO_SetBits(GPIOD, GPIO_Pin_7)

#define FLASHVCC_P 	    (GPIOE->ODR&GPIO_Pin_4) == GPIO_Pin_4
#define FLASHVCC_N 	    (GPIOE->ODR&GPIO_Pin_4) != GPIO_Pin_4
#define FLASHPOWERON    GPIO_ResetBits(GPIOE, GPIO_Pin_4)
#define FLASHPOWEROFF   GPIO_SetBits(GPIOE, GPIO_Pin_4)

#define RELAYLEDON	GPIO_ResetBits(GPIOG, GPIO_Pin_8) 
#define RELAYLEDOFF	GPIO_SetBits(GPIOG, GPIO_Pin_8) 
#define R485CTRLS	GPIO_ResetBits(GPIOE, GPIO_Pin_3) 
#define R485CTRLR	GPIO_SetBits(GPIOE, GPIO_Pin_3)

#define SVDCHKPHIG	((ANAC->SVDSIF&ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD) == ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD)//δ����
#define SVDCHKPLOW	((ANAC->SVDSIF&ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD) != ANAC_SVDSIF_SVDO_HIGHER_THAN_SVD)//����

#define RELAYCTRLON	GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define RELAYCTRLOFF	GPIO_ResetBits(GPIOB, GPIO_Pin_11) 
#define EEVCCON 	GPIO_SetBits(GPIOB, GPIO_Pin_11)
#define EEVCCOFF 	GPIO_ResetBits(GPIOB, GPIO_Pin_11) 

#define RELAYTEST_P	(GPIOB->IDR&GPIO_Pin_12) == GPIO_Pin_12
#define RELAYTEST_N	(GPIOB->IDR&GPIO_Pin_12) != GPIO_Pin_12

#define DISKEY_P 	(GPIOD->IDR&GPIO_Pin_6) == GPIO_Pin_6
#define DISKEY_N 	(GPIOD->IDR&GPIO_Pin_6) != GPIO_Pin_6
#define COVKEY_N 	(GPIOB->IDR&GPIO_Pin_5) == GPIO_Pin_5
#define COVKEY_P 	(GPIOB->IDR&GPIO_Pin_5) != GPIO_Pin_5
#define RXHW_P		(GPIOC->IDR&GPIO_Pin_4) == GPIO_Pin_4
#define RXHW_N		(GPIOC->IDR&GPIO_Pin_4) != GPIO_Pin_4

#define ACTIVEP_P	(GPIOB->IDR&GPIO_Pin_4) == GPIO_Pin_4
#define ACTIVEP_N	(GPIOB->IDR&GPIO_Pin_4) != GPIO_Pin_4

#define REACTIVEP_P	(GPIOA->IDR&GPIO_Pin_9) == GPIO_Pin_9
#define REACTIVEP_N	(GPIOA->IDR&GPIO_Pin_9) != GPIO_Pin_9

#define RX485_P		(GPIOB->IDR&GPIO_Pin_2) == GPIO_Pin_2
#define RX485_N		(GPIOB->IDR&GPIO_Pin_2) != GPIO_Pin_2

#define METER_RST1	GPIO_SetBits(GPIOD, GPIO_Pin_1)//����оƬ��λ��
#define METER_RST0	GPIO_ResetBits(GPIOD, GPIO_Pin_1)

#define RST_ESAM_H	GPIO_SetBits(GPIOG, GPIO_Pin_7)
#define RST_ESAM_L	GPIO_ResetBits(GPIOG, GPIO_Pin_7)	

#define BLEVCC_P 	    (GPIOB->ODR&GPIO_Pin_7) == GPIO_Pin_7
#define BLEVCC_N 	    (GPIOB->ODR&GPIO_Pin_7) != GPIO_Pin_7
#define BLEPOWERON		GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define BLEPOWEROFF		GPIO_SetBits(GPIOB, GPIO_Pin_7)

#define CFOUT_ON		GPIO_SetBits(GPIOG, GPIO_Pin_6)
#define CFOUT_OFF		GPIO_ResetBits(GPIOG, GPIO_Pin_6)

#define COMMMODULE_P 	(GPIOG->IDR&GPIO_Pin_9) == GPIO_Pin_9
#define COMMMODULE_N 	(GPIOG->IDR&GPIO_Pin_9) != GPIO_Pin_9

#define EA_OFF		( Powerd_Flag == 0x12345678 )
#define EA_ON		( Powerd_Flag != 0x12345678 )
//#define EA_OFF	((__get_PRIMASK()&0x00000001) == 0x00000001)
//#define EA_ON		((__get_PRIMASK()&0x00000001) == 0x00000000)

#define LCD_SOFF	((DISP->DISPCTRL & BIT6) != BIT6)
#define LCD_SON		((DISP->DISPCTRL & BIT6) == BIT6)

#define APIE_DISABLE	BTIMER1->BTxIE = 0x00000000;	//ʹ����չ��ʱ����λ�ȽϷ����ж�
#define APIE_ENABLE	BTIMER1->BTxIE = 0x00000008;

//;============================EEPROM�洢����==========================================
//------------------�Զ�crcУ������������	
#define		ee_emupara_page			0x00		//����оƬ����ҳ��ַ
	#define		ee_emupara_inpage		0
	#define		ee_emupara_lenth		20	
#define		ee_esampara_page		0x00		//esam�ﱨ���������֤ʱЧ����ҳ��ַ
	#define		ee_esampara_inpage		ee_emupara_inpage+ee_emupara_lenth+2
	#define		ee_esampara_lenth		26	
#define		ee_temperature_page		0x00		//�¶Ȳ���ϵ��
	#define		ee_temperature_inpage		ee_esampara_inpage+ee_esampara_lenth+2
	#define		ee_temperature_lenth		11	
				
#define		ee_fwdl_page			0x02		//�����������ҳ��ַ
	#define		ee_fwdl_inpage			0
	#define		ee_fwdl_lenth			(max_feilvcount+2)*4

//------------------
#define		ee_event_point_page		0x04		//������¼��ܴ���(3)����Ч����(2)ҳ��ÿҳ12������
	#define		ee_eventpoint_inpage		0x00
	#define		ee_eventpoint_lenth		60
	#define		FreezeNum			12	//�����¼֧�ֵ��¼�����
	#define		EventNum			37	//�¼���¼֧�ֵ��¼�����
	
	#define		ee_timingf_inpage  		0x01	//��ʱ����
	#define		ee_immedf_inpage   		0x02	//˲ʱ����
	#define		ee_agreesqf_inpage 		0x03	//Լ������, ʱ�����л�
	#define		ee_agreesdf_inpage 		0x04	//Լ������, ��ʱ�α��л�
	#define		ee_jtsqswith_inpage		0x05	//Լ������, ����ʱ���л�
	#define		ee_agreejtf_inpage 		0x06	//Լ������, �����л�
	#define		ee_minuten_inpage		0x07	//���Ӷ���
	#define		ee_hourf_inpage    		0x08	//���㶳��
	#define		ee_dayf_inpage     		0x09	//�ն���
	#define		ee_monthn_inpage   		0x0A	//�¶���
	#define		ee_histroyf_inpage 		0x0B	//�����ն���
	#define		ee_year_inpage   		0x0C	//�����(Ԥ��)

	#define		ee_clearn_inpage		0x0D 	//����
	#define		ee_cleareventn_inpage		0x0E 	//���¼�
	#define		ee_powerdownn_inpage		0x0F 	//����
	#define		ee_setclockn_inpage		0x10 	//Уʱ
	#define		ee_covern_inpage		0x11 	//����
	#define		ee_maxi_inpage			0x12	//����
	#define		ee_openrelayn_inpage		0x13	//��բ
	#define		ee_closerelayn_inpage		0x14	//��բ
	#define		ee_programn_inpage		0x15	//���
	#define		ee_shiqun_inpage		0x16	//ʱ������
	#define		ee_shiduann_inpage		0x17	//ʱ�α���
	#define		ee_jieshuann_inpage		0x18	//�����ձ��
	#define		ee_keysetn_inpage		0x19	//��Կ���±��
	#define		ee_combn_inpage			0x1A	//��Ϸ�ʽ���
	#define		ee_rp1combn_inpage		0x1B	//�޹���Ϸ�ʽ1���
	#define		ee_rp2combn_inpage		0x1C	//�޹���Ϸ�ʽ2���
	#define		ee_relayerrn_inpage		0x1D	//���ɿ�������
	#define		ee_powererrn_inpage		0x1E	//��Դ�쳣
	#define		ee_weekdayn_inpage		0x1F	//�����ձ��
	#define		ee_batterlow_inpage		0x20	//���Ƿѹ
	#define		ee_jtpricen_inpage		0x21	//���ݱ���
	#define		ee_clockerrn_inpage		0x22	//ʱ�ӹ���
	#define		ee_calerrn_inpage		0x23	//����оƬ���ϼ�¼
	#define		ee_gbsclockn_inpage		0x24	//�㲥Уʱ��¼(100��)
	#define		ee_nlineerrn_inpage		0x25	//���ߵ����쳣��¼
	#define		ee_lostvn_inpage		0x26	//ʧѹ��¼
	#define		ee_lowervn_inpage		0x27	//�͵�ѹ�¼���¼
	#define		ee_highvn_inpage		0x28	//�ߵ�ѹ�¼���¼
	#define		ee_batchangen_inpage		0x29	//��ظ�����¼
	#define		ee_commerrn_inpage		0x2A	//ͨѶģ���쳣��¼
	#define		ee_commchangen_inpage		0x2B	//ͨѶģ�������¼
	#define		ee_poweroffn_inpage		0x2C 	//�����ϱ��¼���¼
	#define		ee_poweronn_inpage		0x2D 	//�ϵ��ϱ��¼���¼
	#define		ee_dayvolpassn_inpage		0x2E	//�յ�ѹ�ϸ���
	#define		ee_monvolpassn_inpage		0x2F	//�µ�ѹ�ϸ���
	#define		ee_monpowerdownn_inpage		0x30	//��ͣ��ͳ��
	#define		ee_yearpowerdownn_inpage	0x31	//��ͣ��ͳ��

#define		ee_shiqu1_page			0x0e		//��һ��ʱ��ҳ��ַ
#define		ee_shiqu2_page			0x0f		//�ڶ���ʱ��ҳ��ַ
	#define		ee_shiqu_lenth			42
//------------------
#define		ee_commaddr_page		0x0e		//ͨѶ��ַҳ��ַ
	#define		ee_commaddr_inpage		44
	#define		ee_commaddr_lenth		6
#define		ee_meterconst_page		0x0e		//���峣��ҳ��ַ
	#define		ee_meterconst_inpage		ee_commaddr_inpage+ee_commaddr_lenth+2
	#define		ee_meterconst_lenth		4
#define		ee_jtshiqu1_page		0x10		//��ǰ�׽���ʱ����
#define		ee_jtshiqu2_page		0x11		//�����׽���ʱ����
	#define		ee_jtshiqu_inpage		44
	#define		ee_jtshiqu_len			12		
#define		ee_curyearjs_page		0x12		//��ǰ��1~6�������
	#define		ee_curyearjs_inpage		44
	#define		ee_curyearjs_len		18
//------------------		
#define		ee_shiduantable1_1_page		0x10		//��һ�׵�1ʱ�α�ҳ��ַ
#define		ee_shiduantable1_2_page		0x11		//��һ�׵�2ʱ�α�ҳ��ַ
#define		ee_shiduantable1_3_page		0x12		//��һ�׵�3ʱ�α�ҳ��ַ
#define		ee_shiduantable1_4_page		0x13		//��һ�׵�4ʱ�α�ҳ��ַ
#define		ee_shiduantable1_5_page		0x14		//��һ�׵�5ʱ�α�ҳ��ַ
#define		ee_shiduantable1_6_page		0x15		//��һ�׵�6ʱ�α�ҳ��ַ
#define		ee_shiduantable1_7_page		0x16		//��һ�׵�7ʱ�α�ҳ��ַ
#define		ee_shiduantable1_8_page		0x17		//��һ�׵�8ʱ�α�ҳ��ַ
#define		ee_shiduantable2_1_page		0x18		//�ڶ��׵�1ʱ�α�ҳ��ַ
#define		ee_shiduantable2_2_page		0x19		//�ڶ��׵�2ʱ�α�ҳ��ַ
#define		ee_shiduantable2_3_page		0x1a		//�ڶ��׵�3ʱ�α�ҳ��ַ
#define		ee_shiduantable2_4_page		0x1b		//�ڶ��׵�4ʱ�α�ҳ��ַ
#define		ee_shiduantable2_5_page		0x1c		//�ڶ��׵�5ʱ�α�ҳ��ַ
#define		ee_shiduantable2_6_page		0x1d		//�ڶ��׵�6ʱ�α�ҳ��ַ
#define		ee_shiduantable2_7_page		0x1e		//�ڶ��׵�7ʱ�α�ҳ��ַ
#define		ee_shiduantable2_8_page		0x1f		//�ڶ��׵�8ʱ�α�ҳ��ַ
	#define		ee_shiduantable_lenth		42
//------------------
#define		ee_histroyparameter_page	0x14		//����ʱ�����ҳ��ַ
	#define		ee_histroyparameter_inpage	44
	#define		ee_histroyparameter_lenth	6
#define		ee_feik_number_page		0x14		//ʱ��ʱ�η��ʽ�����ҳ��ַ
	#define		ee_feiknumber_inpage		ee_histroyparameter_inpage+ee_histroyparameter_lenth+2
	#define		ee_feiknumber_lenth		8				
#define		ee_freezeparameter_page		0x16		//����ʱ�����ҳ��ַ
	#define		ee_freezeparameter_inpage	44
	#define		ee_freezeparameter_lenth	12
	
#if(1 == CHINT_Mode)
	#define		ee_softij_page				0x17	//����ģʽ��Чʱ��ҳ��ַ
	#define		ee_softij_inpage				44
	#define		ee_softij_lenth					4	
	#define		ee_softID_inpage				50 ///*�ڲ�ID 2�ֽ�*///	
#endif		
	
#define		ee_rtcadj_time_page		0x18		//д���¶����Уֵʱʱ���¼ҳ��ַ(ʼ�ղ���)
	#define		ee_rtcadjtime_inpage		44
	#define		ee_rtcadjtime_lenth		10
#define		ee_pre_history_page		0x19		//ר�������ϵ粹�����һ�ν���ʱ��ҳ��ַ
	#define		ee_prehistory_inpage		44
	#define		ee_prehistory_lenth		5	
#define		ee_pre_dayfreeze_page		0x19		//ר�������ϵ粹�����һ���ն���ʱ��ҳ��ַ
	#define		ee_predayfreeze_inpage		ee_prehistory_inpage+ee_prehistory_lenth+2
	#define		ee_predayfreeze_lenth		5			
#define		ee_changecontrol_page		0x1a		//ʱ��ʱ������������ҳ��ַ
	#define		ee_changecontrol_inpage		44
	#define		ee_changecontrol_lenth		2
#define 	ee_operatorcode_page		0x1a		//�����ߴ���ҳ��ַ
	#define		ee_operatorcode_inpage		ee_changecontrol_inpage+ee_changecontrol_lenth+2
	#define		ee_operatorcode_lenth		4	
#define		ee_keystatus_page		0x1b		//��Կ״̬ҳ��ַ
	#define		ee_keystatus_inpage		44
	#define		ee_keystatus_lenth		18	
#define		ee_meterstatus1_page		0x1c		//���״̬��1ҳ��ַ
	#define		ee_meterstatus1_inpage		44
	#define		ee_meterstatus1_lenth		3
#define		ee_keystatus1_page		0x1c		//��Կ״̬ҳ1��ַ
	#define		ee_keystatus1_inpage		ee_meterstatus1_inpage+ee_meterstatus1_lenth+2
	#define		ee_keystatus1_lenth		9	
#define		ee_xtlfstop_time_page		0x1d		//����ͣ����ʼʱ��ҳ��ַ
	#define		ee_xtlfstoptime_inpage		44
	#define		ee_xtlfstoptime_lenth		7		
#define		ee_wdt_page			0x1e		//�ϵ縴λ�Ϳ��Ź���λ����ҳ��ַ
	#define		ee_wdt_inpage			44	
	#define		ee_wdt_lenth			12
#define		ee_factoryinit_page		0x1f		//������ʼ����־ҳ
	#define		ee_factoryinit_inpage		44
	#define		ee_factoryinit_len		8		
#define		ee_hardfault_page		0x1f		//hardfault��λʱ��ʹ���ҳ��ַ
	#define		ee_hardfault_inpage		ee_factoryinit_inpage+ee_factoryinit_len+2
	#define		ee_hardfault_lenth		8
	
#define		ee_featureword_page		0x20		//����ģʽ��ҳ��ַ
	#define		ee_featureword_inpage		0
	#define		ee_featureword_lenth		32
#define		ee_weekholiday_page		0x20		//�����պ�������ʱ�α��ҳ��ַ
	#define		ee_weekholiday_inpage		ee_featureword_inpage+ee_featureword_lenth+2
	#define		ee_weekholiday_lenth		27
	
#define		ee_7051_page			0x22		//����оƬ��Уҳ��ַ
#define		ee_7051adj_page			0x24		//��ѹ����ҳ
#define		ee_reportdata_page		0x26		//ͣ���¼��ϱ����ݴ洢ҳ(״̬��1,�ϱ�״̬��,����������,��λ��ʱ��)
	#define		ee_reportdata_lenth		60	
#define		ee_power_down_page		0x27		//����ҳ����ҳ��ַ
	#define		ee_powerdown_inpage		0
	#define		ee_powerdown_lenth		62
	#define		ee_loadpoint_lenth		5*max_casecount	

#define		ee_starttimer_page		0x28		//ʱ��ʱ�η��ʵ�۽׺��ݵ������ʱ��ҳ��ַ
	#define		ee_starttimer_inpage		0
	#define		ee_starttimer_lenth		20
#define		ee_displaypara_page		0x28		//��ʾ����ҳ��ַ
	#define		ee_displaypara_inpage		ee_starttimer_inpage+ee_starttimer_lenth+2		
	#define		ee_displaypara_lenth		29		
//------------------		
#define		ee_ptatvalue_page		0x2a		//����¶�ADCҳ��ַ
	#define		ee_ptatvalue_inpage		0
	#define		ee_ptatvalue_lenth		42
#define		ee_trimvalue_page		0x2b		//�����ֵҳ��ַ
	#define		ee_trimvalue_inpage		0
	#define		ee_trimvalue_lenth		42
	
#define		ee_loop_displayitem_page	0x2c		//ѭ����ʾ��Ŀҳ��ַ
#define		ee_key_displayitem_page		0x2d		//������ʾ��Ŀҳ��ַ
	#define		ee_displayitem_lenth		62	
#define		ee_loop_displayitem_page1 	0x32		//ѭ����ʾ��Ŀҳ��ַ
#define		ee_key_displayitem_page1	0x33		//������ʾ��Ŀҳ��ַ
	#define		ee_displayitem_inpage1		0		
	#define		ee_displayitem_lenth1		12

#define		ee_vollimit_page		0x32		//��ѹ�ϸ��ʵ���ز���ҳ
	#define		ee_vollimit_inpage		ee_displayitem_inpage1+ee_displayitem_lenth1+2
	#define		ee_vollimit_lenth		26	
#define		ee_password_page		0x32		//03����04������ҳ��ַ
	#define		ee_password_inpage		ee_vollimit_inpage+ee_vollimit_lenth+2
	#define		ee_password4_inpage		ee_password_inpage+ee_password_lenth+2
	#define		ee_password_lenth		4		

#if(1 == CHINT_Mode) 
#define		ee_7051_page2		0x32		//У������ҳ2   4�ֽ�GPhs2+2�ֽ�crc
   #define  ee_7051_inpage2    ee_password4_inpage + ee_password_lenth + 2   
#endif


#define		ee_rpdl_page			0x34		//�������޹�����ҳ��ַ
	#define		ee_rpdl_inpage			0
	#define		ee_rpdl_lenth			(max_feilvcount+1)*4
	
#define		ee_synflash_page		0x3c		//ʱ��������ݼ�¼ҳ
	#define		ee_synflash_inpage		0
	#define		ee_synflash_len			max_casecount*4+4
#define		ee_validnum_page		0x3d		//���Ӷ�����ʼ��Чҳ������max_casecount��������ÿ��������EE��ʼ����(3)+Flash��ʼ����(3)
	#define		ee_validnum_inpage		0
	#define		ee_validnum_len			max_casecount*6

#define		ee_monthvolrun_page		0x3f		//�պ��µ�ѹ�ϸ�������״̬
	#define		ee_monthvolrun_inpage		0
	#define		ee_monthvolrun_lenth		60					
	
#define		ee_bkdl_page			0x40		//�����������ҳ��ַ
	#define		ee_bkdl_inpage			0
	#define		ee_bkdl_lenth			(max_feilvcount+2)*4						
	
//------------------���Զ�crcУ����
//------------------�ߵ���RTC����� ǰ32�ֽڵ���+crc����32�ֽڸ���+crc
#if( NEWCLOCKADJ == 0 ) //�ɱ�׼ʱ�ӵ�У
#define		ee_ptatvalue_lt_page		0x46		//����¶�ADCҳ��ַ��
	#define		ee_ptatvalue_lt_inpage		0
	#define		ee_ptatvalue_lt_lenth		30
#define		ee_ptatvalue_ht_page		0x46		//����¶�ADCҳ��ַ��
	#define		ee_ptatvalue_ht_inpage		32
	#define		ee_ptatvalue_ht_lenth		30
#define		ee_trimvalue_lt_page		0x47		//�����ֵҳ��ַ
	#define		ee_trimvalue_lt_inpage		0
	#define		ee_trimvalue_lt_lenth		30
#define		ee_trimvalue_ht_page		0x47		//�����ֵҳ��ַ
	#define		ee_trimvalue_ht_inpage		32
	#define		ee_trimvalue_ht_lenth		30
#else
//Ԥ��
#endif

#define		ee_holiday_page			0x42		//�ڼ���ʱ�α�ҳ��ַ,֧��60����������(��4ҳ)
#define		ee_holiday_lenth			60

//------------------�����
#define		ee_zichannum_page		0x48		//�ʲ��������ҳ��ַ
	#define		ee_zichannum_inpage		0
	#define		ee_zichannum_lenth		32
#define		ee_meterpos_page		0x48		//���ܱ�λ����Ϣ
	#define		ee_meterpos_inpage		32
	#define		ee_meterpos_lenth		11		
#define		ee_meterdate_page		0x48		//��������
	#define		ee_meterdate_inpage		43
	#define		ee_meterdate_lenth		10
#define		ee_softbk_page			0x48		//���������ҳ��ַ
	#define		ee_softbk_inpage		53
	#define		ee_softbk_lenth			8
	
#define		ee_softver_page			0x49		//����汾��ҳ��ַ
	#define		ee_softver_inpage		0
	#define		ee_softver_lenth		32
#define		ee_hardver_page			0x49		//Ӳ���汾��ҳ��ַ
	#define		ee_hardver_inpage		32
	#define		ee_hardver_lenth		32
#define		ee_factorynum_page		0x4a		//���ұ���ҳ��ַ
	#define		ee_factorynum_inpage		0
	#define		ee_factorynum_lenth		32
#define		ee_matertype_page		0x4a		//����ͺ�ҳ��ַ
	#define		ee_matertype_inpage		32
	#define		ee_matertype_lenth		32				

#define		ee_bleslamac_page		0x4b		//�����ӻ�MAC��ַ��HEX��ʽ��
	#define		ee_bleslamac_inpage		0
	#define		ee_bleslamac_lenth		18
#define		ee_blerefer_page		0x4b		//��������ҳ
	#define		ee_blerefer_inpage		ee_bleslamac_lenth
	#define		ee_blerefer_lenth		13
	#define		ee_blegbtime_inpage		ee_blerefer_inpage+ee_blerefer_lenth
	#define		ee_blegbtime_lenth		2
#define		ee_buymessage_page		0x4c		//�۵���Ϣҳ��ַ
	#define		ee_buymessage_inpage		0
	#define		ee_buymessage_lenth		24
#define		ee_zbid_bk_page			0x4c		//ԭ�ز�id����(ͨѶ����ר��)ҳ��ַ
	#define		ee_zbid_bk_inpage		ee_buymessage_inpage+ee_buymessage_lenth
	#define		ee_zbid_bk_lenth		6	
	
//------------------�¼���¼��1		
#define         ee_maxi_note_page             	0x5e		//�������ؼ�¼ҳ��ַ
	#define		ee_maxinote_inpage		0
	#define		ee_maxinote_lenth		57	//���ݳ���57�ֽ�		
	
//------------------����ͳ������	
#define		ee_powerdown_month_page		0x68		//�¼�����Ԫ�����¼���¼ҳ��ַ
	#define		ee_powerdownmonth_inpage	0
	#define		ee_powerdownmonth_lenth		8
	#define		max_powerdownmonth_p		36	
#define		ee_powerdown_year_page		0x6d		//�������Ԫ�����¼���¼ҳ��ַ
	#define		ee_powerdownyear_inpage		0
	#define		ee_powerdownyear_lenth		8
	#define		max_powerdownyear_p		3

//------------------�¼���¼��1	
#define		ee_clockerrrecord_page		0x6e		//ʱ�ӹ��ϼ�¼
	#define		ee_clockerrrecord_inpage	0
	#define		ee_clockerrrecord_len		60	
#define		ee_nlineerrrecord_page		0x78		//���ߵ����쳣��¼
	#define   ee_nlineerrrecord_inpage		0
	#define	  ee_nlineerrrecord_len			60
#define		ee_poweroff_note_page		0x78		//�ϵ��ϱ���¼ҳ��ַ(����)
	#define		ee_poweroffnote_inpage		ee_nlineerrrecord_inpage+ee_nlineerrrecord_len
	#define		ee_poweroffnote_lenth		25
#define		ee_poweron_note_page		0x78		//�ϵ��ϱ���¼ҳ��ַ(����)
	#define		ee_poweronnote_inpage		ee_nlineerrrecord_inpage+ee_nlineerrrecord_len
	#define		ee_poweronnote_lenth		22	
#define         ee_lostv_note_page             	0x82		//ʧѹ��¼ҳ��ַ
	#define		ee_lostvnote_inpage		0
	#define		ee_lostvnote_len		61	
#define		ee_opencover_note_page		0x8c		//���Ǽ�¼ҳ��ַ
	#define		ee_opencovernote_inpage		0
	#define		ee_opencovernote_lenth		60	
#define		ee_powerdown_note_page		0x96		//�����¼���¼ҳ��ַ
	#define		ee_powerdownnote_inpage		0
	#define		ee_powerdownnote_lenth		47		
#define		ee_jieshuanrecord_page		0x96		//�����ձ�̼�¼ҳ��ַ
	#define		ee_jieshuanrecord_inpage	ee_powerdownnote_inpage+ee_powerdownnote_lenth
	#define		ee_jieshuanrecord_lenth		16
#define		ee_setclock_note_page		0xa0		//����ʱ�Ӽ�¼ҳ��ַ
	#define		ee_setclocknote_inpage		0
	#define		ee_setclocknote_lenth		40
#define         ee_lowerv_note_page		0xa0		//�͵�ѹ�¼�ҳ��ַ
	#define		ee_lowervnote_inpage		ee_setclocknote_inpage+ee_setclocknote_lenth
	#define		ee_lowervnote_len		16	
#define         ee_batchange_note_page		0xaa		//ʱ�ӵ�ظ���ҳ��ַ
	#define		ee_batchangenote_inpage		0
	#define		ee_batchangenote_len		28
#define		ee_commerr_note_page		0xaa		//ͨѶģ���쳣��¼
	#define		ee_commerrnote_inpage		ee_batchangenote_inpage+ee_batchangenote_len
	#define		ee_commerrnote_len		34	
#define		ee_calerr_note_page		0xb4		//����оƬ���ϼ�¼
	#define		ee_calerrnote_inpage		0
	#define		ee_calerrnote_len		28
#define		ee_commchange_note_page		0xb4		//ͨѶģ�������¼
	#define		ee_commchangenote_inpage	ee_calerrnote_inpage+ee_calerrnote_len
	#define		ee_commchangenote_len		28	
#define		ee_cleardl_note_page		0xbe		//������¼�ҳ��ַ
	#define		ee_cleardlnote_inpage		0
	#define		ee_cleardlnote_lenth		34
#define		ee_combstatusrecord_page	0xbe		//�й����״̬�ּ�¼ҳ��ַ
	#define		ee_combstatusrecord_inpage	ee_cleardlnote_inpage+ee_cleardlnote_lenth
	#define		ee_combstatusrecord_lenth	11	
#define		ee_rp2combstatusrecord_page	0xbe		//�޹����״̬��2��¼ҳ��ַ
	#define	 	ee_rp2combstatusrecord_inpage	ee_combstatusrecord_inpage+ee_combstatusrecord_lenth
	#define	 	ee_rp2combstatusrecord_lenth	11				
#define		ee_closerelay_note_page		0xc8		//��բ�¼���¼ҳ��ַ
	#define		ee_closerelaynote_inpage	0
	#define		ee_closerelaynote_lenth		34
#define		ee_batterlow_note_page		0xc8		//���Ƿѹ��¼ҳ
	#define		ee_batterlownote_inpage		ee_closerelaynote_inpage+ee_closerelaynote_lenth
	#define		ee_batterlownote_len		22	
#define		ee_openrelay_note_page		0xd2		//��բ�¼���¼ҳ��ַ
	#define		ee_openrelaynote_inpage		0		
	#define		ee_openrelaynote_lenth		34
#define		ee_powererr_note_page		0xd2		//��Դ�쳣��¼ҳ��ַ
	#define		ee_powererrnote_inpage		ee_openrelaynote_inpage+ee_openrelaynote_lenth
	#define		ee_powererrnote_lenth		20
#define		ee_relayerr_note_page		0xdc		//���ɿ����쳣��¼ҳ��ַ
	#define		ee_relayerrnote_inpage		0
	#define		ee_relayerrnote_lenth		29
#define		ee_rp1combstatusrecord_page	0xdc		//�޹����״̬��1��¼ҳ��ַ
	#define		ee_rp1combstatusrecord_inpage	ee_relayerrnote_inpage+ee_relayerrnote_lenth
	#define		ee_rp1combstatusrecord_lenth	11
#define         ee_highv_note_page		0xdc		//�ߵ�ѹ�¼�ҳ��ַ
	#define		ee_highvnote_inpage		ee_rp1combstatusrecord_inpage+ee_rp1combstatusrecord_lenth
	#define		ee_highvnote_len		16						
#define		ee_program_note_page		0xe6		//����¼�ҳ��ַ
	#define		ee_programnote_inpage		0
	#define		ee_programnote_lenth		50
	#define		max_eventrecord_p		10	//�¼�ָ�����ֵ(10��)	
#define		ee_clearevent_note_page		0xe6		//���¼���¼ҳ��ַ
	#define		ee_cleareventknote_inpage	ee_programnote_inpage+ee_programnote_lenth
	#define		ee_cleareventnote_lenth		14
//------------------��Կ��
#define		ee_keydata_1_page		0xf0		//���0 ��32�ֽ���Կ+���1 ��32�ֽ���Կ����������ÿҳ2��		

//------------------�¼���¼��2
#define		ee_gbsetclock_note_page		0x100		//�㲥����ʱ�Ӽ�¼ҳ��ַ��100����
	#define		ee_gbsetclocknote_inpage	0
	#define		ee_gbsetclocknote_lenth		36
	#define		max_gbsetclock_p		100	//�㲥Уʱ����¼��

//------------------��ѹ�ϸ��ʼ�¼��		
#define         ee_monvolpass_note_page	        0x122		//�µ�ѹ�ϸ���ҳ��ַ
	#define		ee_monvolpassnote_inpage	0
	#define		ee_monvolpassnote_len		(29-2)	//Ŀǰ645��Լ����27�ֽ�
	#define		max_monvolpass_p		12	
#define         ee_dayvolpass_note_page	        0x125		//�յ�ѹ�ϸ���ҳ��ַ
	#define		ee_dayvolpassnote_inpage	0
	#define		ee_dayvolpassnote_len		29
	#define		max_dayvolpass_p		92
											
//------------------�õ���������
#define		ee_pre1_histroyusedl_page	0x13d		//��1-25������ʷ�õ���ҳ��ַ	
#define		ee_pre1_mhistroyusedl_page	0x13e		//��1-25����ʷ�õ���ҳ��ַ
	#define		ee_histroyusedl_lenth		100
#define		ee_pre1_yhistroyusedl_page	0x13f		//��1-7����ʷ�õ���ҳ��ַ	
	#define		ee_yhistroyusedl_lenth		56	
#define		ee_illegalcardnum_page		0x13f		//�ۼ�ʱ��(����ʱ��)ҳ
#define		ee_illegalcardnum_inpage		56
#define		ee_illegalcardnum_len			48

//------------------���ݲ����ͽ��ݱ�̼�¼
#define		ee_jtpricerecord2_page		0x140		//���ݱ��̼�¼(Ŀǰ����ʵ�ʰ���2�ż�¼�¼�)
	#define		ee_jtpricerecord2_inpage	0	
	#define		ee_jtpricerecord2_len		70		
#define		ee_ladder1_page			0x148		//��ǰ�׽��ݱ����/��ۣ�4�ű�ÿҳһ�ű�
#define		ee_ladder2_page			0x14c		//�����׽��ݱ����/��ۣ�4�ű�ÿҳһ�ű�
	#define		ee_ladder_lenth			70
	
#define		ee_shiqurecord_page		0x140		//ʱ�����̼�¼ҳ��ַ
	#define		ee_shiqurecord_lenth		57
#define		ee_shiduanrecord_page		0x142		//ʱ�α��̼�¼ҳ��ַ
	#define		ee_shiduanrecord_lenth		57
#define		ee_jtpricerecord_page		0x144		//���ݱ��̼�¼(����ʱ��6�Ͳ����ߴ���4)
	#define		ee_jtpricerecord_inpage		70	
	#define		ee_jtpricerecord_len		10
#define		ee_keysetrecord_page		0x144		//��Կ���¼�¼ҳ
	#define		ee_keysetrecord_inpage		ee_jtpricerecord_inpage+ee_jtpricerecord_len
	#define		ee_keysetrecord_len		15	
#define		ee_week_note_page		0x144		//�����ձ�̼�¼
	#define		ee_week_note_inpage		ee_keysetrecord_inpage+ee_keysetrecord_len
	#define		ee_week_note_len		11		
	
//------------------�����¼��
#define		ee_timingfreeze_dl_page		0x150		//��ʱ��������ҳ��ַ
	#define		max_timingfreeze_p		60	//Լ���������ָ�����ֵ(���60��)
#define		ee_dayfreezedl_page		0x153		//�ն�������ҳ��ַ
	#define		max_dayfreeze_p			254	//�ն������ָ�����ֵ(���254��), EEֻ�洢���һ��
#define		ee_realtimefreeze1_page		0x156		//˲ʱ���ᶳ��ҳ��ַ
#define		ee_appointfreeze1_page		0x15f		//ʱ��ת��Լ������ҳ��ַ
#define		ee_appointfreeze2_page		0x165		//ʱ��ת��Լ������ҳ��ַ
#define		ee_appointfreeze3_page		0x16b		//����ʱ��ת��Լ������ҳ��ַ
#define		ee_appointfreeze4_page		0x171		//����ת��Լ������ҳ��ַ
	#define		ee_freezedl_lenth		(5+max_dl_lenth*6+8)
#define         ee_monthfreeze_page             0x177		//�¶������ҳ��ַ
#define         ee_histroy_dl_page              0x17a		//�����յ���ҳ��ַ
	#define		ee_histroydl_lenth		(5+max_dl_lenth*6+8)
	#define		max_histroy_p			24	//�������ָ�����ֵ(���24��), EEֻ�洢���һ��
//------------------���ɼ�¼��
#define		ee_ploadrec_page		0x17d
	#define		ee_ploadrec1_inpage		0	//ʱ��(5)+��ѹ(2)+����(3)+Ƶ��(2)
	#define		ee_ploadrec1_len		12
	#define		ee_ploadrec2_inpage		ee_ploadrec1_inpage+ee_ploadrec1_len	//ʱ��(5)+�й�����(3)+�޹�����(3)
	#define		ee_ploadrec2_len		11
	#define		ee_ploadrec3_inpage		ee_ploadrec2_inpage+ee_ploadrec2_len	//ʱ��(5)+��������(2)
	#define		ee_ploadrec3_len		7
	#define		ee_ploadrec4_inpage		ee_ploadrec3_inpage+ee_ploadrec3_len	//ʱ��(5)+�������ܵ���(8)+����޹�(4+4)
	#define		ee_ploadrec4_len		21
	#define		ee_ploadrec5_inpage		ee_ploadrec4_inpage+ee_ploadrec4_len	//ʱ��(5)+�������޹�(4��4)
	#define		ee_ploadrec5_len		21
	#define		ee_ploadrec6_inpage		ee_ploadrec5_inpage+ee_ploadrec5_len	//ʱ��(5)+����й�����1~4����(5��4)
	#define		ee_ploadrec6_len		25
	#define		ee_ploadrec_lenth		97
	#define		max_ploadrec_p			365*96	//���ɼ�¼ָ�����ֵ(���35040��), EEֻ�洢���һ��

//------------------���㶳���¼��	
#define         ee_hourfreezedl_page	        0x17e		//���㶳�����ҳ��ַ
	#define		ee_hourfreezedl_inpage		0
	#define		ee_hourfreezedl_lenth		13
	#define		max_hourfreeze_p		254	//���㶳�����ָ�����ֵ(254����), EEֻ�洢���һ��			

//;=============================��س������壽==========================================
#define		maxtimes			6		//������屶��,96Aʱ,7������/s
#define		max_maxholiday			60		//��󹫹�������
#define		ms_timer_delay			115		//460msʱ�궨ʱ,ˢ����ʾ
#define		comm_led_timer_delay		5		//5sͨѶָʾ��
#define		shiduanctrl_timer_delay		20		//80msʱ�θı������ʱ����ʱ
#define		max_shiduancount		14		//���ʱ��14�ֽ�ʱ�α�
#define		default_loopdisplaytimer	5		//Ĭ�ϵ�ѭ��ʱ��5s
#define		default_keydisplaytimer		60		//Ĭ�ϰ�����ʾʱ��Ϊ60s
#define		lcdled_timer_delay		60		//60s������
#define	 	disp_num			42		//��ʾ�б��е���Ŀ��
#define		max_casecount			6		//���Ӷ������֧����
#define		max_feilvcount			12		//��������
#define		max_dl_lenth		((max_feilvcount+1)*4)	//�ܺͷ��ʵ������ֽ���
#define		max_disploop		((max_feilvcount+1)*13)	//��֧�ֵ�ǰ����1~12�µ�����ʾ

#define 	ESAM				0		//esam
#define 	CARD				1		//IC card
#define 	u7816_buf_size			250		//

//;==============================�������Ͷ��壽============================================
typedef unsigned char	uint08; 		//unsigned 8 bit data
typedef unsigned short	uint16;
typedef	unsigned long int uint32;

typedef signed char	int08; 			//unsigned 8 bit data
typedef signed short	int16;
typedef	signed long int	int32;

typedef union
{
  unsigned char B08;
  struct
  {
    unsigned char bit0:1;
    unsigned char bit1:1;
    unsigned char bit2:1;
    unsigned char bit3:1;
    unsigned char bit4:1;
    unsigned char bit5:1;
    unsigned char bit6:1;
    unsigned char bit7:1;
  }Bit;
}B08_Bit;

union B16_B08_2						//С�˴洢(51Ϊ���)
{
	unsigned short	B16;
	unsigned char	B08[2];
};

union S16_B08_2						//С�˴洢(51Ϊ���)
{
	unsigned char	B08[2];
	signed short	S16;
};

union B32_B08_2						//С�˴洢(51Ϊ���)
{
	unsigned long int B32;
	unsigned char	B08[4];
};

union S32_B08_2						//С�˴洢(51Ϊ���)
{
	signed long int B32;
	signed char	B08[4];
};

union B64_B08_2						//С�˴洢(51Ϊ���)
{
	unsigned long long B64;
	unsigned char     B08[8];
};

union S64_B08_2						//С�˴洢(51Ϊ���)
{
	signed long long S64;
	signed char     B08[8];
};

union B16_B08
{
	unsigned char	B08[2];
  //unsigned int B16;
};

union S16_B08
{
	unsigned char	B08[2];
  //unsigned int S16;
};

union B32_B08
{
	unsigned char	B08[4];
  //unsigned long int B32;
};


struct PLUSE_FRM								//С�˴洢(51Ϊ���)
{
	union B32_B08_2	Pluse[max_feilvcount+1];	//�ܺ͸���������β��
	union B32_B08_2	UPluse;				//�����õ���(������)
	union B16_B08	Crc16;		
};

struct RPLUSE_FRM								//С�˴洢(51Ϊ���)
{
	union B32_B08_2	Pluse[max_feilvcount+1];	//�ܺ͸���������β��(�������޹�)
	union B16_B08	Crc16;		
};


struct LOADREC_FRM
{
	unsigned char Point[5*max_casecount]; 			//�ܴ���(3)+��ͬ����(2)
	union B16_B08_2	Crc16;   			//CRCУ����
};


struct METERCONST_FRM
{
	union B32_B08	Const;				//���峣��bcd��,4�ֽ�,���ֽ���ǰ
	union B16_B08 	Crc16;				//CRCУ����
	uint08		Const_H;			//0.01kwh��������
};

struct PARA_ESAM_FRM
{
	uint08		Current_Ratio[3];		//�������
	uint08		Voltage_Ratio[3];		//��ѹ���
	uint08		Meter_Id[6];			//���
	uint08		User_Id[6];			//�û���
	uint08		Zb_Id[6];			//ģ��
	union B16_B08	Identity_Delay;			//�����֤ʱЧ
	union B16_B08 	Crc16;				//CRCУ����
};


struct PARA_DISPLAY_FRM
{
	uint08		S_Number;			//��ʾ����
	uint08		Loop_Time;			//ѭ��ʱ��
	uint08		Dl_Dot;				//����С��λ��
	uint08		P_Dot;				//����С��λ��
	uint08		K_Number;			//������ʾ����
	uint08		Temp;				//Ԥ��
	uint08		Temp2;				//Ԥ��
	uint08		A_Time;				//�ϵ�ȫ��ʱ��
	uint08		Lstarttimer[5];			//���ɼ�¼��ʼʱ��,�ڲ���չ��,��5�ֽ�(����ǰ)
	union B16_B08	Lspacetimer[8];			//��1~5�ฺ�ɼ�¼���ʱ��,��16�ֽ�(���ֽ���ǰ)	
	union B16_B08 	Crc16;				//CRCУ����
	uint08		Dl_Dot_Auto;			//��������Ӧ��ʾС��λ��
};

struct COMM_ADDRESS_FRM
{
	uint08		Comm_Id[6];			//ͨѶ��ַ
	union B16_B08 	Crc16;				//CRCУ����
};

struct RTC_TRIMA_FRM
{
	uint16		PTAT_Value[21];			//�¶�ADC
	union B16_B08 	Crc16;				//CRCУ����
};

struct RTC_TRIMV_FRM
{
	int16		Trim_Value[21];			//����ֵ
	union B16_B08 	Crc16;				//CRCУ����
};

struct RTC_TRIM_FRM
{
	struct RTC_TRIMA_FRM	TAdc;
	struct RTC_TRIMV_FRM	TVal;
	int16		TestTrim;
	uint08		TempFlag;			//������¶ȱ�־ 0=���£�1=���£�2=����
	float		CFixTrim;			//����������
};

struct STARTTIME_FRM
{
	uint08		Shiqu[5];			//��ʱ������ʱ��
	uint08		Shiduan[5];			//��ʱ�α�����ʱ��
	uint08		LadSQ[5];			//����ʱ���л�ʱ��
	uint08		Ladder[5];			//��������ʱ��
	union B16_B08 	Crc16;				//CRCУ����
};

struct EMU_FRM
{
	union B32_B08_2	rate[5];						//С�˴洢(51Ϊ���)
	union B16_B08_2	Crc16;				//CRCУ����
};


struct WEEK_FRM
{
	uint08		Status;				//������
	uint08		Shiduan_N;			//ʱ�α��(��Χ0~7)	
	union B16_B08	Freeze[7];			//����/��ʱ/˲ʱ/Լ��/����/�ն���/�¶���ģʽ��	
	uint08		Temp[1];			//Ԥ��1	
	union B16_B08	Max_I;				//�����¼�������������
	uint08		Max_I_Period;			//�����¼�������ʱʱ��	
	union B32_B08	NLine_I;			//������������	
	union B16_B08	NLine_Limit;			//������ƽ������ֵ
	uint08		NLine_Period;			//��ʱ�ж�ʱ��	bcd					
	union B16_B08 	Crc16;				//CRCУ����	
};


struct VOLLMT_FRM
{
	union B16_B08	MaxVolLmt;			//�ϸ��ʵ�ѹ����ֵ
	union B16_B08	MinVolLmt;			//�ϸ��ʵ�ѹ����ֵ
	union B16_B08	ChkMaxVol;			//�ϸ��ʵ�ѹ��������
	union B16_B08	ChkMinVol;			//�ϸ��ʵ�ѹ��������
	
	union B16_B08	Lost_V_Min;			//ʧѹ�¼���ѹ��������
	union B16_B08	Lost_V_Max;			//ʧѹ�¼���ѹ�ָ�����	
	union B32_B08	Lost_V_I;			//ʧѹ�¼�������������
	uint08		Lost_V_Period;			//ʧѹ�¼���ʱ�ж�ʱ��	bcd
	
	union B16_B08	Lower_V;			//�͵�ѹ�¼���ѹ��������
	union B16_B08	Lower_V_Period;			//�͵�ѹ�¼���ʱ�ж�ʱ��	bcd	
	union B16_B08	High_V;				//�ߵ�ѹ�¼���ѹ��������
	union B16_B08	High_V_Period;			//�ߵ�ѹ�¼��¼���ʱ�ж�ʱ��	bcd
	
	uint08		Cal_Err_Period;			//���������ж���ʱ bcd
	union B16_B08 	Crc16;				//CRC-16
};

struct VOLPASS_FRM					//�ýṹ�������4�ֽڵı���,�������֧��
{
	union B32_B08_2	Total;				//��ѹ���ʱ��
	union B32_B08_2	HighTime;			//��ѹ������ʱ��
	union B32_B08_2	LowTime;			//��ѹ������ʱ��
	union B16_B08_2	MaxVol;				//��ߵ�ѹ
	union B16_B08_2	MinVol;				//��͵�ѹ
	unsigned char	MaxMoment[4];			//��ߵ�ѹ����ʱ��
	unsigned char	MinMoment[4];			//��͵�ѹ����ʱ��
	union B32_B08_2	AverVol_Cnt;			//ƽ����ѹ�ۼƴ���
	union B16_B08_2	AverVol;			//ƽ����ѹ
};


struct PARA_FEATUREWORD_FRM
{
	uint08		Bps[1];				//ͨ�ſ�1
	uint08		Comp_B;				//�й������
	uint08		Temp[4];			//Ԥ��4
	uint08		Powerd_Period;			//ͣ���¼��ж���ʱ bcd
	uint08		Report_Period;			//�����ϱ�ʱ��(bcd��)��λ����
	uint08		Feature1;			//������1
	uint08		Report[8];			//�ϱ�ģʽ��
	uint08		Limit_I[3];			//�̵�����բ���Ƶ�������ֵ
	uint08		Exp_Timer[6];			//��չ���Ӷ�ʱbcd��,�ֱ�Ϊ��բ��ʱ2,�������բ��ʱ2,������֤ʱ��1,�ϱ��Զ���λʱ��1
	uint08		Wz_Clocerelay;			//�̵�����բ����ʽ(0x55���ñ�ʾ�Զ���բ,0x55���ñ�ʾ�ֶ���բ)
	uint08		Plc;				//��չģʽ��,bit7=1ÿ��20:00��λ�ز�һ��(��Ҫ�����˹���ز�),bit2=1����ң������������,bit1=1Ƿѹ��������,bit0=1�����������
	uint08		Rpcomp[2];			//�޹������1��2
	uint08		Zbbps;				//�ز�ͨ�ſ�
	uint08		Chblebps;			//����ͨ�ſ�(Ԥ��)
	union B16_B08 	Crc16;				//CRCУ����
	uint16		Report_Timer;			//�����ϱ�ʱ��(hex��)��λ��
	uint08		Zbbps_Ram;			//�ز�ͨ�ſ�(Э�̻������õĲ�����)
};


struct TEMPERATURE_FRM
{
	uint08		Offset[8];			//�¶ȵ���ϵ��8�ֽ�
	uint08		RtcTMode;			//RTC��������ģʽ��0x55:����ģʽ��0xAA���²���ֵģʽ����������ͨģʽ
	uint08		krh;				//����ϵ�������޵�ֵ
	uint08		krl;
	union B16_B08 	Crc16;				//CRCУ����
};


struct PRICE_FRM
{
	union B32_B08	Ladder_Dl[6];			//��ǰ���ݵ���
	union B32_B08	Ladder[7];			//��ǰ���ݵ��
	uint08		Year_Ladder[18];		//��ǰ����ݽ�����1~6
	union B16_B08 	Crc16a;				//CRCУ����
	union B32_B08   Current_L;			//��ǰ���ݵ��
//	union B32_B08   Current_F;			//��ǰ���ʵ��
	union B32_B08   Current;			//��ǰ���
	union B32_B08   Current_X;			//��ǰ��۳��Ա�Ⱥ���
	uint08		Ladder_Mode;			//����ģʽ��,0x00Ϊ�½���,0x55Ϊ�����
};

struct TARIFF_FRM
{
	uint08		Table[42];			//��ǰ����ʱ�α�,3*14��42�ֽ�
	union B16_B08 	Crc16;				//CRCУ����
	uint08		Current;			//��ǰ����(��Χ0~11)
	uint08		Current_Ladder;			//��ǰ����(��Χ0~4)
	uint08		Current_N;			//��ǰʱ�α��(��Χ0~7)
	uint08		Period_N;			//��ǰʱ�κ�(��Χ0~13)
	uint08		CurLad_N;			//��ǰ���ݱ��(��Χ0~3)
	uint08		Status;				//bit3ʱ��/bit2ʱ�α�/bit1����/bit0����(0:��һ�ף�1:�ڶ���)
		
};


struct ITEM_FRM
{
	uint16		 Display[99];			//��ʾ��Ŀ1*62�����1ҳ,��4ҳ
	union B16_B08 	 Crc16;
};

struct SYS_CLOCK_FRM
{
	uint08   	Clockmain[7];			//ϵͳʱ��,[0]��[1]��[2]ʱ[3]��[4]��[5]��[6]��
	uint08   	Clockbackup[7];			//ϵͳʱ��,[0]��[1]��[2]ʱ[3]��[4]��[5]��[6]��
//	uint08   	Status;				//ʱ��״̬��
};

struct UIP_FRM
{
	union B32_B08_2   U;				//��ѹxxxxxxx.x				С�˴洢(51Ϊ���)
	union B32_B08_2   I1;				//����xxxxx.xxx
	union B32_B08_2   P1;				//�й�����xxxx.xxxx
	union B32_B08_2   I2;				//���ߵ���xxxxx.xxx	
	union B32_B08_2   P2;				//���ڹ���xxxx.xxxx
	union B32_B08_2   Cosa;				//��������xxxxx.xxx
	union B32_B08_2   Pav;				//һ����ƽ������xxxx.xxxx
	union B32_B08_2   Freq;				//����Ƶ��
	union B32_B08_2   Q1;				//�޹�����xxxx.xxxx
	union B32_B08_2   Iav[3];			//һ����ƽ������xxxxx.xxx(����3����)
	union B32_B08_2   Qav;				//һ����ƽ���޹�����xxxx.xxxx
	union B32_B08_2   Uav;				//һ����ƽ����ѹxxxxxxx.x	
};

struct FUNCTION_FRM
{
	uint16		Temper_M;			//��ǰ����¶�xxx.x
	uint16		Voltage_B;			//��ǰ��ص�ѹxx.xx
	uint16		Voltage_P;			//��ǰ��Դ��ѹxx.xx
	uint32		Voltage_B_T;			//��ص�ѹ����ʱ��xxxxxxxx(hex����)
};

struct TMR_STS_FRM
{
	uint08		Timer;				//��ʱ��
	uint08		Status;				//״̬
};

struct TIMER_FRM
{
	uint08		Timer;				//��ʱ��
};

struct STATUS_FRM
{
	uint08		Status;				//״̬
};

struct DECIMAL_FRM
{
	uint08		Add;				//��������
	uint08		Add_Rp;				//�޹���������
	uint08		Status;				//bit4��������ı�,bit5��������ı�,bit0~3�������޹�����ı�
};

struct DISPALY_FRM
{
	uint08		Number;				//��ʾ��
	uint08		Timer;				//��ʾʱ��
	uint08		Status;				//״̬
};

struct EEPROM_FRM
{
	uint08		Buffer[128*3];			//����ee������/lcd��ʾ���帴��
	uint08		Status;				//״̬�ֽ�
};

struct HisEvent_STR
{
	unsigned short 	DI21;	
	unsigned short 	page;
	unsigned char  	offset;
	unsigned char  	len;
	unsigned char  	offset2;
};

struct ADCDATA_FRM
{
	uint16		Buffer[32];			//ADC���
	uint08		ReadCount;			//����
};

struct FEIK_FRM
{
	unsigned char Num[8];
	union B16_B08 Crc16;
};

struct TIMER2_FRM
{
	//0���ߵ�����ƽ�����ʱ��(4)
	//1��������ʱ��(4)
	//2���Ƿѹ���ۼ�ʱ��(4)
	//3�������ۼ�ʱ��(4)
	//4��ع���ʱ��(4) 
	//5ʧѹ����ʱ��(4) 
	//6��ѹ���ۼ�ʱ��(4)
	//7��ѹ���ۼ�ʱ��(4)
	//8��ͣ���ۼƴ���(4)---
	//9��ͣ���ۼ�ʱ��(4)
	//10��ͣ���ۼƴ���(4)---
	//11��ͣ���ۼ�ʱ��(4)
	uint32	Times[12];
};

struct BLEDEVICE_FRM
{
	uint08	Ble_A2;
	uint08	Ble_A3;
	uint08	Ble_Sta;
	uint08	Ble_Mac[6];	//2��+3��
};

//�ýṹ�岻Ҫ���׵���
typedef struct
{
//nw
struct  TIMER_FRM	near	Progkey;	//240min���(ͣ������)
struct  STATUS_FRM	near	Cover;	//���ǲ���(ͣ�籣��) 
uint08			near 	Mac_Err_Times;	//MACУ��ʧ�ܴ���
uint08			near 	G_Clockerr_Times;//���Ĺ㲥Уʱ��¼���ϴ���
uint08			near 	System_St_Bk;	//ϵͳ״̬�ֱ���(ͣ������)--������ʼ��ַ����ʧ4�ı���
uint08			near 	Report_Data[5];	//��Ч�ϱ�״̬��
uint08			near 	Report_Data2[5];	//��Ч�ϱ�״̬�ֱ���
uint08			near 	Report_Num[40];	//�¼��ϱ���������
uint08			near 	RReport_Status;	//֮ǰ�Ѷ��ϱ�״̬����λ�ϱ�״̬
uint32			near	Meter_Run_Timer4;//�ϵ�������ʱ��
uint16			near 	Reset_Rep_Timer;	//��λ�ϱ�״̬�ֶ�ʱ��
uint08			near	Password_Err[2];	//����������
struct	LOADREC_FRM	near	Load;			//����ָ��
uint16			near 	Meter_Run_Timer1;//����ϵ�����ʱ��1(ʱ�䲻��1Сʱ,�����󲻽��е��緢���ϱ�)
uint16			near 	Meter_Run_Timer2;//����ϵ�����ʱ��2(ʱ�䲻��1Сʱ,�����󲻽��е�������ϱ�)
uint08			near	Wr_Ext_Number;	//�ڲ���չ����дee�������
struct	PLUSE_FRM	near	Fwdl;		//�����й���������У��
struct	PLUSE_FRM	near	Bkdl;		//�����й���������У��
struct	RPLUSE_FRM	near	Rpdl[4];	//�������޹���������У��
uint08			near	RAMREG0;	//��������Ĵ���
uint08			near	RAMREG1;	//
uint08			near	RAMREG2;	//
uint08			near	RAMREG3;	//
uint08			near	RAMREG4;	//
uint08			near	RAMREG5;	//
uint08			near	RAMREG6;	//
uint08			near	RAMREG7;	//
uint08			near	RAMREG8;	//
uint08			near	RAMREG9;	//
uint08			near	RAMREG10;	//
uint08			near	RAMREG11;	//
uint08			near	RAMREG12;	//
uint08			near	RAMREG13;
uint08			near	RAMREG14;
uint08			near	RAMREG15;
uint08			near	RAMBUF[32];
}NoInit_t ;

//����ͨ�ų�ʱʱ�䳣��
#define txtimeout_max	125				//500ms�������ַ��������ʱ
#define rxtimeout_max	125  				//500ms 
#define framedelay_mx	15 				//60ms
//ͨ�Ż�������󳤶ȶ���
#define	utx_buf_size	250				//ͨ�Ż�������󳤶ȣ�220
#define	urx_buf_size	250				//ͨ�Ż�������󳤶ȣ�220
#define frm_buf_size	1000			//��֡ͨ������ֽ���=2048

struct COMMUNICATION_FRM
{
	uint08 Buf[ urx_buf_size ];			//���ջ���/���ͻ���
	uint08 Len;					//���ճ����ֽ�/��������
	uint08 Total_Len;				//�����ܳ���/�����ܳ���
	uint08 Step;  					//���ղ���
	uint08 Flag;  					//ͨѶ��־
	uint08 Response_Timer;				//ͨѶ��Ӧ��ʱ��
	uint08 Overtime_Timer;				//ͨѶ���ջ��߷�����ʱ��ʱ��
	
	uint08 TxBuf[ urx_buf_size ];   		//���ͻ���
	uint08 TxLen;					//���ͳ���
	uint08 Total_Tx; 				//�����ܳ���
	uint16 S_Overtime_Timer;			//���ͳ�ʱ(�ز�ר��)
	uint16 RptTimer;  				//�ط���ʱ��
	uint08 Transfer;  				//Ԥ��

	uint08 DI[4];       //��֡ͨ�� ���ݱ�ʶ
	uint08 Sn;          //��֡ͨ�� ���
	uint16 FrmLen;      //��֡ͨ�� ���ݳ���
	uint16 FrmOffset;   //��֡ͨ�� ƫ����
	uint08 FrmBuf[ frm_buf_size ]; //��֡ͨ�� ������, ��ʱ�α��̼�¼ռ�����196+195+195+96=682
};


//------ FLASH ���� ------
typedef struct
{
	unsigned short DataPage;  //����eeҳ��ַ
	unsigned short Offset;    //����eeҳ��ƫ��
	unsigned short AppPage;   //��������ַ
	unsigned short AppPos;    //��������ƫ��
	unsigned char  Clk[16];
} RtFlash;

typedef struct
{
	unsigned char Result;
	unsigned long Addr;
} FindInf;

typedef struct
{
	struct
	{
		unsigned short Page; //���˵�����
		unsigned short Len;  //�������ֽ���
	}HisRec[max_casecount];
	unsigned long Newptr;     //����ָ��
	unsigned short Crc16;     //У����
} RtRecord;

typedef struct
{
	unsigned char  Dir;   //���Ʒ���0x00���У�0x55��ǰ����������, 0xAA����������ǰ��
	unsigned char  Obj;   //����+������
	unsigned short Page;  //
	unsigned short Offset; //
	unsigned short Len;  //�ܳ���
} MoveRec;

typedef struct
{
	unsigned short TotLen;  //��¼���ֽ���
	unsigned short Depth;   //�洢���
	unsigned long  MaxDepth; //���洢���
	unsigned long  CurPoint; //��ǰ��¼��
	unsigned short ValPoint; //��Ч��¼��
}RecStore; 

typedef struct
{
	unsigned short Page;    //��ǰ����������
	unsigned char  RpTimes; //�����������������
	unsigned char  Enable;  //����ͬ����־��0=����; 1=����
}SynRec;


#if(1 == CHINT_Mode)
struct Ijtimer_FRM
{
	union   B32_B08_2		Ijtimer;//����ģʽ��ʱ�� 	
	union 	B16_B08 	Crc16;	//CRCУ����
};
#endif

#define		FPAGE_SIZE    256L  //ҳ  ���ֽ���
#define		SECTOR_SIZE   4096L //�������ֽ���
#define		SECTOR_NUM    1024   //�������ܸ���(32Mλ��flash)
#define		FL_NEW_ADDR    0    //�������� ����ʱ�����ʱ������Ŀ������δ������ϣ��¼�¼��ʱ�洢�ڴ�
#define		FL_OLD_ADDR    1    //�������� ����ʱ�����ʱ������Ŀ���������ݹ����У���ʷ������ʱ�洢����

#define		FL_SECTOR_RECNUM      (SECTOR_SIZE/ee_freezedl_lenth)	//һ�������洢�ļ�¼���� 4096/325 = 12.6

#define		FL_TIMING_SECTORNUM   ((max_timingfreeze_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1) //��ʱ����  6������
#define		FL_TIMING_ADDR	   2	//��ʱ���� Flash�洢��ʼ����

//------- ���ɼ�¼ռ��Flash��� ---------
#define		FL_LOADREC_ADDR	     (FL_TIMING_ADDR+FL_TIMING_SECTORNUM) //���ɼ�¼ Flash�洢��ʼ���� 4+6 = 0x0A
#define		FL_CASE1_RECNUM      (SECTOR_SIZE/ee_ploadrec1_len)  //���ɼ�¼����1 341
#define		FL_CASE2_RECNUM      (SECTOR_SIZE/ee_ploadrec2_len)  //���ɼ�¼����2 372
#define		FL_CASE3_RECNUM      (SECTOR_SIZE/ee_ploadrec3_len)  //���ɼ�¼����3 585
#define		FL_CASE4_RECNUM      (SECTOR_SIZE/ee_ploadrec4_len)  //���ɼ�¼����4 195
#define		FL_CASE5_RECNUM      (SECTOR_SIZE/ee_ploadrec5_len)  //���ɼ�¼����5 195
#define		FL_CASE6_RECNUM      (SECTOR_SIZE/ee_ploadrec6_len)  //���ɼ�¼����6 163
#define		FL_LOADREC1_SECTORNUM  ((max_ploadrec_p+FL_CASE1_RECNUM-1)/FL_CASE1_RECNUM+1)   //104������
#define		FL_LOADREC2_SECTORNUM  ((max_ploadrec_p+FL_CASE2_RECNUM-1)/FL_CASE2_RECNUM+1)   // 96������
#define		FL_LOADREC3_SECTORNUM  ((max_ploadrec_p+FL_CASE3_RECNUM-1)/FL_CASE3_RECNUM+1)   // 61������
#define		FL_LOADREC4_SECTORNUM  ((max_ploadrec_p+FL_CASE4_RECNUM-1)/FL_CASE4_RECNUM+1)   //181������
#define		FL_LOADREC5_SECTORNUM  ((max_ploadrec_p+FL_CASE5_RECNUM-1)/FL_CASE5_RECNUM+1)   //181������ 
#define		FL_LOADREC6_SECTORNUM  ((max_ploadrec_p+FL_CASE6_RECNUM-1)/FL_CASE6_RECNUM+1)   //216������ 
#define		FL_REC_END_ADDR        (FL_LOADREC1_SECTORNUM+FL_LOADREC2_SECTORNUM+FL_LOADREC3_SECTORNUM+FL_LOADREC4_SECTORNUM+FL_LOADREC5_SECTORNUM+FL_LOADREC6_SECTORNUM)

//------- ���㶳��ռ��Flash��� ---------
#define		FL_SECTOR_HOURNUM     (SECTOR_SIZE/ee_hourfreezedl_lenth)	//һ�������洢�ļ�¼����
#define		FL_HOUR_SECOTRNUM     ((max_hourfreeze_p+FL_SECTOR_HOURNUM-1)/FL_SECTOR_HOURNUM+1)	//���㶳��  2������
#define		FL_HOUR_ADDR          (FL_LOADREC_ADDR+FL_REC_END_ADDR) //���㶳�� Flash�洢��ʼ����

//------- �ն���ռ��Flash��� ---------
#define		FL_DAY_SECTORNUM      ((max_dayfreeze_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1)	//�ն���   23������
#define		FL_DAY_ADDR		      (FL_HOUR_ADDR+FL_HOUR_SECOTRNUM) //�ն���   Flash�洢��ʼ����

//------- �¶���ռ��Flash��� ---------
#define		FL_MONTH_SECTORNUM    ((max_histroy_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1)	//�¶���    3������
#define		FL_MONTH_ADDR	      (FL_DAY_ADDR+FL_DAY_SECTORNUM) //�¶���   Flash�洢��ʼ����

//------- ���㶳��ռ��Flash��� ---------
#define		FL_HISTORY_SECTORNUM  ((max_histroy_p+FL_SECTOR_RECNUM-1)/FL_SECTOR_RECNUM+1)	//���㶳��  3������
#define		FL_HISTORY_ADDR	      (FL_MONTH_ADDR+FL_MONTH_SECTORNUM) //���㶳�� Flash�洢��ʼ����
//-------------------------------

#endif




