
/*****************************************************************************************
*Copyright��    ZHEJIANG CHINT INSTRUMENT&METER CO.,LTD HANGZHOU R&D CENTER
*File name:     Public_CBB.h
*Version:       V1
Author:       	G.G
*Date:          2021-3-1
*Description:
*Function List:
*****************************************************************************************/
#ifndef	__Public_CBB_H
#define	__Public_CBB_H


#include <math.h>
#include <stdio.h>
#include <string.h>
#include "FM33A0XX.h"
#include "system_FM33A0XX.h"
#include "fm32l0xx_anac.h"
#include "fm32l0xx_rcc.h"


/* �������Ͷ��� */
#define	char8		signed char			/*8bit*/
#define uchar8		unsigned char			/*8bit*/
#define short16		signed short			/*16bit*/
#define ushort16	unsigned short			/*16bit*/
#define long32		signed long			/*32bit*/
#define ulong32		unsigned long			/*32bit*/
#define ulong64		unsigned long long		/*64bit*/
#define long64		long long				/*64bit*/


/********macro ����ֵ********/
#define	C_DecodeFlay		        0x68	/*��֡���������������־*/
#define	C_OK						0x00	/*�ɹ�              */
#define	C_IDError               	0xE1    /*���ݱ�ʶ��        */
#define	C_CRCError              	0xE2    /*CRC��             */
#define	C_CrcErr_DataZero       	0xE3    /*CRC��������Ϊȫ0*/
#define	C_DataLenError          	0xE4    /*���ݳ��ȴ�        */
#define	C_NoAccess              	0xE5    /*��Ȩ��            */
#define	C_SafeFlagError         	0xE6    /*��ȫ��־��        */
#define	C_ProgOpClockIsZero     	0xE7    /*��̼�¼ʱ��Ϊȫ0 */
#define	C_Error                 	0xE8    /*��������          */
#define	C_SPIError              	0xE9    /*SPI���ߴ�         */
#define	C_IICError              	0xEa    /*IIC��             */
#define C_NoData                    0x83    /*����������        */
#define	C_CY		              	0x01    /*�н�λ���߽�λ    */
#define	C_NoCY		              	0x00    /*û�н�λ�ͽ�λ    */
#define	C_NULL						0x00	/*��*/
#define	C_BCDERR					0xEb	/*��BCD��*/
#define	C_TIMEERR                   0xEc    /*ʱ��Ƿ�*/
#define	C_CommNum_Err				0xEd	/*�ŵ���*/
#define	C_EventError				0xEe	/*�¼���*/
#define	C_EventOK					0x00	/*�¼���*/
#define	C_MaxResponseLen_ERR		0xF0	/*���̶Ȳ�����*/
#define	C_NotLessThanZero			0xF1	/*���ݲ�С��0*/
#define	C_LessThanZero				0xF2	/*����С��0*/
#define C_Zero						0x00	/*����0*/
#define C_CalDataError				0xF3	/*У�����ݴ���*/
#define C_NOStartCalibration		0xF4	/*δ������������״̬*/
#define C_DataError					0xF5	/*���ݴ���*/
#define C_StartCalibrationOK		0xF6	/*����У��ɹ�*/
#define C_CalibrationOK				0xF7	/*����У��ɹ�*/
#define C_IDNumError                0xF8    /*��ʶ���Ӧ����ʾ��Ŵ�*/

#define	C_StatusError				0xF9	/*״̬����				*/
#define	C_CSError					0xFA	/*У��ʹ���(����7022E)   */
#define	C_CS0Error					0xFB	/*У���0����(����90E36)  */
#define	C_CS1Error					0xFC	/*У���1����(����90E36)  */
#define	C_CS2Error					0xFD	/*У���2����(����90E36)  */
#define	C_CS3Error					0xFE	/*У���3����(����90E36)  */
#define	C_NoStartCalibration		0xFF	/*δ��ʼУ��              */
#define	C_ClearCalRegOK				0xE0	/*��У������Ĵ����ɹ�    */
#define C_AbnormalError				0xDF	/*����������*/

#define C_DT_Start_ss               0x00    /*��s��ʼ�ж�*/
#define C_DT_Start_mm               0x01    /*��min��ʼ�ж�*/
#define C_DT_Start_hh               0x02    /*��hour�����ж�*/
#define C_DT_Start_DD               0x03    /*��date��ʼ�ж�*/
#define C_DT_Start_MM               0x04    /*���¿�ʼ�ж�*/
#define C_DT_Start_NN               0x05    /*���꿪ʼ�ж�*/
#define C_DT_Start_NN_H             0x06    /*��ĸ��ֽ�*/

#define C_DT_Len_ss                 0x06    /*��s��ʼ�жϵĳ���*/
#define C_DT_Len_mm                 0x05    /*��min��ʼ�жϵĳ���*/
#define C_DT_Len_hh                 0x04    /*��hour�����жϵĳ���*/
#define C_DT_Len_DD                 0x03    /*��date��ʼ�жϵĳ���*/
#define C_DT_Len_MM                 0x02    /*���¿�ʼ�жϵĳ���*/
#define C_DT_Len_NN                 0x01    /*���꿪ʼ�жϵĳ���*/

#define C_DT_Len_ss_698             0x07    /*��s��ʼ�жϵĳ���*/
#define C_DT_Len_mm_698             0x06    /*��min��ʼ�жϵĳ���*/
#define C_DT_Len_hh_698             0x05    /*��hour�����жϵĳ���*/
#define C_DT_Len_DD_698             0x04    /*��date��ʼ�жϵĳ���*/
#define C_DT_Len_MM_698             0x03    /*���¿�ʼ�жϵĳ���*/
#define C_DT_Len_NN_698             0x02    /*���꿪ʼ�жϵĳ���*/


typedef struct
{
	uchar8 sec;
	uchar8 min;
	uchar8 hour;
	uchar8 day;
	uchar8 month;
	uchar8 year;
}Str_Data_Type;

/********�ܴ�**********/
#define	C_Weekday  				0x00		/*������              */
#define	C_Monday  				0x01		/*����4               */
#define	C_Tuesday  				0x02		/*����1               */
#define	C_Wednesday				0x03		/*����2               */
#define	C_Thursday 				0x04		/*����3               */
#define	C_Friday  				0x05		/*����5               */
#define	C_Saturday 				0x06		/*����6               */

/********ʱ��Ϸ����ж���ʼ��ַ**********/
#define	C_SecondStart  			0x00		/*���뿪ʼ�ж�		*/
#define	C_MinStart  			0x01		/*��min��ʼ�ж�		*/
#define	C_HourStart  			0x02		/*��ʱ��ʼ�ж�		*/
#define	C_DayStart				0x03		/*���տ�ʼ�ж�		*/
#define	C_MonStart 				0x04		/*���¿�ʼ�ж�		*/
/********��С��ϵ�궨��********/
#define	C_GreaterThan  			0x81		/*����             */
#define	C_LessThan  			0x82		/*С��             */
#define	C_Equal       			0x00		/*����             */
#define	C_NotGreaterThan  		0x01		/*������           */
#define	C_NotLessThan  			0x02		/*��С��           */


/********extern for public********/
extern	void PF_Print(uchar8 ModuleNo,uchar8 *p,uchar8 Len);
extern uchar8 PF_BCDAddBytes(uchar8 *Add1,uchar8 *Add2,uchar8 *AddResult,uchar8 Len);
extern uchar8 PF_BCDDECBytes(uchar8 *Dec1,uchar8 *Dec2,uchar8 *DecResult,uchar8 Len );
extern void PF_BCDtoHexBytes(uchar8 *BCDBuffer,ulong32 *HexBuffer,uchar8 BCDLen);
extern void PF_HextoBCDBytes(ulong32 *HexBuffer,uchar8 *BCDBuffer,uchar8 *Len);
extern void PF_CopyDataBytes(uchar8 *SourceAddr,uchar8 *DerictAddr,uchar8 Len);
extern void PF_Ushort16ToBuffer2(uchar8 *BytesBuffer,ushort16 *Short16Buufer);
extern void PF_Buffer2ToUshort16(uchar8 *BytesBuffer,ushort16 *Short16Buufer);
extern void PF_Ulong32ToBuffer4(uchar8 *BytesBuffer,ulong32 *DoubleWordBuufer,uchar8 Len);
extern void PF_Buffer4ToUlong32(uchar8 *BytesBuffer,ulong32 *DoubleWordBuufer,uchar8 Len);
extern ulong32 PF_Buffer4ToUlong32_698(uchar8 *BytesBuffer);
extern ushort16 PF_Buffer2ToLong16_698(uchar8 *BytesBuffer);
extern void PF_Ulong64ToBuffer8(uchar8 *BytesBuffer,ulong64 *DoubleWordBuufer,uchar8 Len);
extern void PF_Buffer8ToUlong64(uchar8 *BytesBuffer,ulong64 *DoubleWordBuufer,uchar8 Len);
extern uchar8 PF_WeekCompute(uchar8 *DateBuffer);
extern uchar8 PF_Judge_BCD(uchar8 V_ucJudgeTimes,uchar8 *P_ucdata);
extern uchar8 PF_DataTimeActive(uchar8 *TimeBuffer,uchar8 StartByte,uchar8 Len);
extern uchar8 PF_TimeSub_Min(uchar8 *TimeBuffer1,uchar8 *TimeBuffer2,ulong32 *SubMins);
extern uchar8 PF_TimeSub_Hour(uchar8 *TimeBuffer1,uchar8 *TimeBuffer2,ulong32 *SubHours);
extern uchar8 PF_TimeSub_Day(uchar8 *TimeBuffer1,uchar8 *TimeBuffer2,ushort16 *SubDays);
extern ushort16 PF_Cal_CRC(uchar8 *P_ucBuffer,ushort16 V_usDataLen);
extern void Crc_16Bits_Add2(uchar8 *buf, uchar8 len );
extern uchar8 PF_Check_CRC(uchar8 *P_ucBuffer,ushort16 V_usDataLen);
/*extern uchar8 PF_Check_CRC1(uchar8 *P_ucBuffer,ushort16 V_usDataLen);*/
extern uchar8 PF_Campare_Data(uchar8 *P_ucBuffer1,uchar8 *P_ucBuffer2,uchar8 V_ucLen);
extern uchar8 PF_Campare_Data_698(uchar8 *P_ucBuffer1, uchar8 *P_ucBuffer2, ushort16 V_usLen);
extern uchar8 PF_Get_MsgParmLen(uchar8 MsgPT_No,uchar8 *pMsgParmLen);
extern uchar8 PF_Cal_Week(uchar8 *ucAdd);
extern void PF_Ushort16ToBuffer2_698(uchar8 *BytesBuffer,ushort16 *Short16Buufer);
extern const uchar8 C_Meter_Type;
extern uchar8 PF_Check_CRC_698(uchar8 *P_ucBuffer,ushort16 V_usDataLen);
extern uchar8 PF_Check_CRC_698_CommRec(uchar8 *P_ucBuffer,ushort16 V_usDataLen);
extern ushort16 PF_Cal_CRC_698(uchar8 *P_ucBuffer,ushort16 V_usDataLen);
extern void PF_Ulong32ToBuffer4_698(uchar8 *BytesBuffer,ulong32 *DoubleWordBuufer,uchar8 Len);
extern void PF_CopyDataBytes_698(uchar8 *SourceAddr,uchar8 *DerictAddr,ushort16 Len);
extern uchar8 PF_TimeSub_Second(uchar8 *TimeBuffer1,uchar8 *TimeBuffer2,ulong32 *SubSeconds);
extern const uchar8 C_MonthNum[12];
extern const uchar8  Day[13];
extern uchar8 PF_BCDtoHexOneByte(uchar8 BCDBuffer);

extern void PF_Hex64toBCDBytes(ulong64 *HexBuffer,uchar8 *BCDBuffer,uchar8 *Len);
extern void PF_BCDtoHex64Bytes(uchar8 *BCDBuffer,ulong64 *HexBuffer,uchar8 BCDLen);

extern void PF_Ulong32ToBufferX(uchar8 *BytesBuffer, ulong32 *DoubleWordBuufer, uchar8 Len);
extern void PF_BufferXToUlong32(uchar8 *BytesBuffer, ulong32 *DoubleWordBuufer, uchar8 Len);
extern void PF_OneDataReversed(uchar8 *pSBuf, uchar8 *pDBuf,uchar8 Len);

extern uchar8 PF_DataTimeActive_698(uchar8 *TimeBuffer, uchar8 StartByte, uchar8 Len);
extern uchar8 PF_Cal_DayNum_698(const Str_Data_Type *str_date, ulong32* const p_daynum);
extern uchar8 PF_TimeSub_Second_698(uchar8 *TimeBuffer1, uchar8 *TimeBuffer2, ulong32 *SubSeconds);
extern uchar8 PF_TimeSub_Min_698(uchar8 *TimeBuffer1, uchar8 *TimeBuffer2, ulong32 *SubMins);
extern uchar8 PF_TimeSub_Hour_698(uchar8 *TimeBuffer1, uchar8 *TimeBuffer2, ulong32 *SubHours);
extern uchar8 PF_TimeSub_Day_698(uchar8 *TimeBuffer1, uchar8 *TimeBuffer2, ulong32 *SubDays);
extern uchar8 PF_Cal_Week_698(uchar8 *ucAdd);
extern uchar8 PF_HextoBCDOneByte(uchar8 HexBuffer);
extern ulong32 PF_DateTime_to_Second(uchar8 *pV_ucDateTime);					/*������ǰ698��ʽʱ������Ӧ1970.1.1 0:0:0��������*/
extern void PF_Second_to_dateTime(ulong32 V_ulSecond, uchar8 *pV_ucDateTime);	/*����1970.1.1 0:0:0��������ת��Ϊ��Ӧ��698��ʽʱ��*/
extern uchar8 PF_Is_Leap_Year(ushort16 V_usyear);

typedef union B32_B08
{
     uchar8     B08[4];
	 ushort16   B16[2];
     ulong32    B32;
}GU_B32_B08_Type;

#define B0000_0000 0x00
#define B0000_0001 0x01
#define B0000_0010 0x02
#define B0000_0011 0x03
#define B0000_0100 0x04
#define B0000_0101 0x05
#define B0000_0110 0x06
#define B0000_0111 0x07
#define B0000_1000 0x08
#define B0000_1001 0x09
#define B0000_1010 0x0A
#define B0000_1011 0x0B
#define B0000_1100 0x0C
#define B0000_1101 0x0D
#define B0000_1110 0x0E
#define B0000_1111 0x0F

#define B0001_0000 0x10
#define B0001_0001 0x11
#define B0001_0010 0x12
#define B0001_0011 0x13
#define B0001_0100 0x14
#define B0001_0101 0x15
#define B0001_0110 0x16
#define B0001_0111 0x17
#define B0001_1000 0x18
#define B0001_1001 0x19
#define B0001_1010 0x1A
#define B0001_1011 0x1B
#define B0001_1100 0x1C
#define B0001_1101 0x1D
#define B0001_1110 0x1E
#define B0001_1111 0x1F

#define B0010_0000 0x20
#define B0010_0001 0x21
#define B0010_0010 0x22
#define B0010_0011 0x23
#define B0010_0100 0x24
#define B0010_0101 0x25
#define B0010_0110 0x26
#define B0010_0111 0x27
#define B0010_1000 0x28
#define B0010_1001 0x29
#define B0010_1010 0x2A
#define B0010_1011 0x2B
#define B0010_1100 0x2C
#define B0010_1101 0x2D
#define B0010_1110 0x2E
#define B0010_1111 0x2F

#define B0011_0000 0x30
#define B0011_0001 0x31
#define B0011_0010 0x32
#define B0011_0011 0x33
#define B0011_0100 0x34
#define B0011_0101 0x35
#define B0011_0110 0x36
#define B0011_0111 0x37
#define B0011_1000 0x38
#define B0011_1001 0x39
#define B0011_1010 0x3A
#define B0011_1011 0x3B
#define B0011_1100 0x3C
#define B0011_1101 0x3D
#define B0011_1110 0x3E
#define B0011_1111 0x3F

#define B0100_0000 0x40
#define B0100_0001 0x41
#define B0100_0010 0x42
#define B0100_0011 0x43
#define B0100_0100 0x44
#define B0100_0101 0x45
#define B0100_0110 0x46
#define B0100_0111 0x47
#define B0100_1000 0x48
#define B0100_1001 0x49
#define B0100_1010 0x4A
#define B0100_1011 0x4B
#define B0100_1100 0x4C
#define B0100_1101 0x4D
#define B0100_1110 0x4E
#define B0100_1111 0x4F

#define B0101_0000 0x50
#define B0101_0001 0x51
#define B0101_0010 0x52
#define B0101_0011 0x53
#define B0101_0100 0x54
#define B0101_0101 0x55
#define B0101_0110 0x56
#define B0101_0111 0x57
#define B0101_1000 0x58
#define B0101_1001 0x59
#define B0101_1010 0x5A
#define B0101_1011 0x5B
#define B0101_1100 0x5C
#define B0101_1101 0x5D
#define B0101_1110 0x5E
#define B0101_1111 0x5F

#define B0110_0000 0x60
#define B0110_0001 0x61
#define B0110_0010 0x62
#define B0110_0011 0x63
#define B0110_0100 0x64
#define B0110_0101 0x65
#define B0110_0110 0x66
#define B0110_0111 0x67
#define B0110_1000 0x68
#define B0110_1001 0x69
#define B0110_1010 0x6A
#define B0110_1011 0x6B
#define B0110_1100 0x6C
#define B0110_1101 0x6D
#define B0110_1110 0x6E
#define B0110_1111 0x6F

#define B0111_0000 0x70
#define B0111_0001 0x71
#define B0111_0010 0x72
#define B0111_0011 0x73
#define B0111_0100 0x74
#define B0111_0101 0x75
#define B0111_0110 0x76
#define B0111_0111 0x77
#define B0111_1000 0x78
#define B0111_1001 0x79
#define B0111_1010 0x7A
#define B0111_1011 0x7B
#define B0111_1100 0x7C
#define B0111_1101 0x7D
#define B0111_1110 0x7E
#define B0111_1111 0x7F

#define B1000_0000 0x80
#define B1000_0001 0x81
#define B1000_0010 0x82
#define B1000_0011 0x83
#define B1000_0100 0x84
#define B1000_0101 0x85
#define B1000_0110 0x86
#define B1000_0111 0x87
#define B1000_1000 0x88
#define B1000_1001 0x89
#define B1000_1010 0x8A
#define B1000_1011 0x8B
#define B1000_1100 0x8C
#define B1000_1101 0x8D
#define B1000_1110 0x8E
#define B1000_1111 0x8F

#define B1001_0000 0x90
#define B1001_0001 0x91
#define B1001_0010 0x92
#define B1001_0011 0x93
#define B1001_0100 0x94
#define B1001_0101 0x95
#define B1001_0110 0x96
#define B1001_0111 0x97
#define B1001_1000 0x98
#define B1001_1001 0x99
#define B1001_1010 0x9A
#define B1001_1011 0x9B
#define B1001_1100 0x9C
#define B1001_1101 0x9D
#define B1001_1110 0x9E
#define B1001_1111 0x9F

#define B1010_0000 0xA0
#define B1010_0001 0xA1
#define B1010_0010 0xA2
#define B1010_0011 0xA3
#define B1010_0100 0xA4
#define B1010_0101 0xA5
#define B1010_0110 0xA6
#define B1010_0111 0xA7
#define B1010_1000 0xA8
#define B1010_1001 0xA9
#define B1010_1010 0xAA
#define B1010_1011 0xAB
#define B1010_1100 0xAC
#define B1010_1101 0xAD
#define B1010_1110 0xAE
#define B1010_1111 0xAF

#define B1011_0000 0xB0
#define B1011_0001 0xB1
#define B1011_0010 0xB2
#define B1011_0011 0xB3
#define B1011_0100 0xB4
#define B1011_0101 0xB5
#define B1011_0110 0xB6
#define B1011_0111 0xB7
#define B1011_1000 0xB8
#define B1011_1001 0xB9
#define B1011_1010 0xBA
#define B1011_1011 0xBB
#define B1011_1100 0xBC
#define B1011_1101 0xBD
#define B1011_1110 0xBE
#define B1011_1111 0xBF

#define B1100_0000 0xC0
#define B1100_0001 0xC1
#define B1100_0010 0xC2
#define B1100_0011 0xC3
#define B1100_0100 0xC4
#define B1100_0101 0xC5
#define B1100_0110 0xC6
#define B1100_0111 0xC7
#define B1100_1000 0xC8
#define B1100_1001 0xC9
#define B1100_1010 0xCA
#define B1100_1011 0xCB
#define B1100_1100 0xCC
#define B1100_1101 0xCD
#define B1100_1110 0xCE
#define B1100_1111 0xCF

#define B1101_0000 0xD0
#define B1101_0001 0xD1
#define B1101_0010 0xD2
#define B1101_0011 0xD3
#define B1101_0100 0xD4
#define B1101_0101 0xD5
#define B1101_0110 0xD6
#define B1101_0111 0xD7
#define B1101_1000 0xD8
#define B1101_1001 0xD9
#define B1101_1010 0xDA
#define B1101_1011 0xDB
#define B1101_1100 0xDC
#define B1101_1101 0xDD
#define B1101_1110 0xDE
#define B1101_1111 0xDF

#define B1110_0000 0xE0
#define B1110_0001 0xE1
#define B1110_0010 0xE2
#define B1110_0011 0xE3
#define B1110_0100 0xE4
#define B1110_0101 0xE5
#define B1110_0110 0xE6
#define B1110_0111 0xE7
#define B1110_1000 0xE8
#define B1110_1001 0xE9
#define B1110_1010 0xEA
#define B1110_1011 0xEB
#define B1110_1100 0xEC
#define B1110_1101 0xED
#define B1110_1110 0xEE
#define B1110_1111 0xEF

#define B1111_0000 0xF0
#define B1111_0001 0xF1
#define B1111_0010 0xF2
#define B1111_0011 0xF3
#define B1111_0100 0xF4
#define B1111_0101 0xF5
#define B1111_0110 0xF6
#define B1111_0111 0xF7
#define B1111_1000 0xF8
#define B1111_1001 0xF9
#define B1111_1010 0xFA
#define B1111_1011 0xFB
#define B1111_1100 0xFC
#define B1111_1101 0xFD
#define B1111_1110 0xFE
#define B1111_1111 0xFF

#define		RIGHTSHIFT				1		/*  ���� */
#define		LEFTSHIFT				2		/*  ���� */
#define		DECRYPTION 				1		/*  ���� */
#define		ENCRYPTION				2		/*  ���� */
#define		C_OneDataRev_MaxLen		196



#define C_SafedArea_Size				512				/*��������С*/
#define C_SafedArea_StardAddr			0x0007FC00		/*��������ʼ��ַ*/
#define C_Internal_VersioAddr			0x0007FFF4		/*�ڲ��汾����ʼ��ַ*/
#define C_OtherPara_StartAddr			0x0007FFA0		/*����������С��ʼ��ַ*/

#define C_3DES_KeyLen					8				/*3DES��Կ����*/
#define C_3DES_DataLen					8				/*3DES���ݳ���*/
#define C_EnterBootFlag_Len				0x10			/*����boot��ʶ����*/
#define C_Software_Featurcode_Len		0x20			/*����汾��ʶ����*/
#define C_Software_Version_Len			0x20			/*����汾�ų���*/
#define C_Hardware_Version_Len			0x20			/*Ӳ���汾�ų���*/

#define C_FeaturCode_Len				30				/*����汾��ʶ����*/

#define C_3DESKey1_Offset				0															/*3DES��Կkey1��ַƫ��*/
#define C_3DESKey2_Offset				(C_3DESKey1_Offset + C_3DES_KeyLen)							/*3DES��Կkey2��ַƫ��*/
#define C_3DESKey3_Offset				(C_3DESKey2_Offset + C_3DES_KeyLen)							/*3DES��Կkey3��ַƫ��*/
#define C_FixedData_Offset				(C_3DESKey3_Offset + C_3DES_KeyLen)							/*��֤�й̶����ݵĵ�ַƫ��*/
#define C_EnterBootFlag_Offset			(C_FixedData_Offset + C_3DES_DataLen)						/*����BootLoader��־�ĵ�ַƫ��*/
#define C_Software_Featurcode_Offset	(C_EnterBootFlag_Offset + C_EnterBootFlag_Len)				/*����汾��ʶ*/
#define C_Software_Version_Offset		(C_Software_Featurcode_Offset + C_Software_Featurcode_Len)	/*����汾��*/
#define C_Hardware_Version_Offset		(C_Software_Version_Offset + C_Software_Version_Len)		/*Ӳ���汾��*/

#define C_External_Version_Len			(0x200 - C_Software_Featurcode_Offset)

extern const uchar8 C_3DES_Key1[C_3DES_KeyLen];
extern const uchar8 C_3DES_Key2[C_3DES_KeyLen];
extern const uchar8 C_3DES_Key3[C_3DES_KeyLen];
extern const uchar8 C_3DES_FixedData[C_3DES_DataLen];
extern const uchar8 C_EnterBootFlag[C_EnterBootFlag_Len];
extern const uchar8 C_Software_Featurcode[C_External_Version_Len];
/*extern const uchar8 C_Software_Version[C_External_Version_en];
extern const uchar8 C_Hardware_Version[C_External_Version_en];*/

extern uchar8 PF_3DES_Encode(uchar8 *P_ucDataIn, uchar8 *P_ucDataOut, uchar8 *P_ucKey1, uchar8 *P_ucKey2, uchar8 *P_ucKey3);
extern uchar8 PF_3DES_Decode(uchar8 *P_ucDataIn, uchar8 *P_ucDataOut, uchar8 *P_ucKey1, uchar8 *P_ucKey2, uchar8 *P_ucKey3);

#endif
