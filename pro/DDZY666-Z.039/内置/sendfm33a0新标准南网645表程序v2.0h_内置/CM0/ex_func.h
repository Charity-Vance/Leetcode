//定义全局函数
#ifndef	__EX_FUNC_H__
#define __EX_FUNC_H__

#include "define4.h"

__inline uint32_t Enter_Critical( void )    
{
  uint32_t reg;
  reg=__get_PRIMASK();
  __set_PRIMASK(1);
  return reg;
} 
__inline void Exit_Critical( uint32_t reg )    
{
  __set_PRIMASK(reg);
   return ;
} 
#define START_CRITICAL()    unsigned int reg;
#define ENTER_CRITICAL()    reg = Enter_Critical()
#define EXIT_CRITICAL()     Exit_Critical(reg)


//iic
extern unsigned char I2C_Write_Eeprom( unsigned int Page, unsigned char offset, unsigned char *IIC_Buf, unsigned char Len );
extern unsigned char I2C_Read_Eeprom( unsigned int Page, unsigned char offset, unsigned char *IIC_Buf, unsigned char Len );
extern unsigned char ReadE2WithBackup( unsigned int Page, uint08 inpage, uint08 *Buf, uint08 Len );
extern unsigned char WriteE2WithBackup( unsigned int Page, uint08 inpage, uint08 *Buf, uint08 Len );
extern unsigned char I2C_Read_Eeprom44( unsigned int Page, uint08 *Buf, uint08 Len );
extern unsigned char I2C_Write_Eeprom44( unsigned int Page, uint08 *Buf, uint08 Len );
extern unsigned char I2C_Write_Bottom(unsigned int Page, unsigned char offset, unsigned char *Buf, unsigned char h);
extern unsigned char I2C_Read_Bottom(unsigned int Page, unsigned char offset, unsigned char *Buf, unsigned char h);

//rtc
extern int32 Byte2Int(uint08* byte);
extern int16 Byte2Short(uint08* byte);
extern uint32 Byte2uInt(uint08* byte);
extern uint16 Byte2uShort(uint08* byte);
extern void Int2Byte(uint32 datatemp,uint08* Buff);
extern void Short2Byte(uint16 datatemp,uint08* Buff);
extern void Add_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len );
extern void Sub_Bcd( unsigned char *BufA, unsigned char *BufB, unsigned char Len );
extern void Bcd2Hex( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len );
extern void Bcd2Hex_SS( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len );
extern void Bcd2Hex_LS( unsigned char *BCDopt, unsigned char *HEXopt, unsigned char Len );
extern void Hex2Bcd( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len );
extern void Hex2Bcd_SS( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len );
extern void Hex2Bcd_LS( unsigned char *Hexop, unsigned char *BCDopt, unsigned char Len );	
extern unsigned char Hex_To_Bcd( unsigned char value );
extern unsigned char Bcd_To_Hex( unsigned char value );
extern unsigned char ChkBufZero( unsigned char *Buf,unsigned char Len );
extern unsigned char Cmp_Data( unsigned char *BufA, unsigned char *BufB, unsigned char Len );
extern unsigned char Cmp_Bcd_Inv( uint08 *BcdA, uint08 *BcdB, uint08 Len );
extern unsigned char Cmp_Clock( unsigned char *Buf, unsigned char Len );
extern unsigned char Judge_Clock( uint08 Start, uint08 *Ck, uint08 Len );
extern unsigned char JudgeClockNoWeek( uint08 Start, uint08 *Ck, uint08 Len );
extern unsigned char Read_Rtc( unsigned char *RTC_Buf );
extern unsigned char Set_Rtc( unsigned char Start, unsigned char *Ck, unsigned char Len );
extern void Syn_Clock( void );
extern void Read_Sysclock( void );

//verify
extern void Close_None_GPIO(void);
extern void AnalogIO( GPIOx_Type* GPIOx, uint32 PinNum );
extern void InputtIO( GPIOx_Type* GPIOx, uint32 PinNum, uint08 Type );
extern void OutputIO( GPIOx_Type* GPIOx, uint32 PinNum, uint08 Type );
extern void AltFunIO( GPIOx_Type* GPIOx, uint32 PinNum, uint08 Type );
extern void CloseeIO( GPIOx_Type* GPIOx, uint32 PinNum );
extern void Veri_Btmr1_Pcount(unsigned char Result);
extern void Veri_Btmr2_Pcount(unsigned char Result);
extern void Veri_Etmr2(void);
extern void Veri_Clk_Gen(void);
extern void Veri_Pad(void);
extern void MeterIC_RST0(void);
extern void MeterIC_RST1(void);
extern void Disable_Pulse(void);
extern void Enable_Pulse(void);
extern void Disable_I2C_IO(void);
extern void Enable_I2C_IO(void);
extern void Enable_Led_IO(void);
extern void Veri_Disp( uint08 Mode );
extern void Veri_Sys_Reg(void);
extern void Veri_Uart_All(void);
extern void Starttimer_Verify(void);
extern void Remainmoney_Verify(void);
extern void Esam_Para_Verify(void);
extern void Money_Para_Verify(void);
extern unsigned char Fwdl_Verify(void);
extern unsigned char Bkdl_Verify(void);
extern unsigned char Rpdl_Verify( unsigned char i );
extern void Mode_Verify(void);
extern void Commaddr_Verify(void);
extern void Display_Para_Verify(void);
extern void Displayitem_Verify(void);
extern void Week_Holiday_Verify(void);
extern void Fill_RTC_RT_TAdc(void);
extern void Fill_RTC_RT_TVal(void);
extern void Temperpara_Verify(void);
extern unsigned char Verify_para(unsigned char Page, unsigned char Inpage, unsigned char *Buf, unsigned char Len );
extern unsigned short Crc_16Bits(unsigned char *buf,unsigned char len) ;
extern void Crc_16Bits_Add2( unsigned char *buf, unsigned char len ); 
extern unsigned char Crc_Check( unsigned char *buf, unsigned char len ); 
extern unsigned char GetBps( unsigned char Type, unsigned char Bps );
extern void feik_Num_Verify( void ); 
extern void RdMeterMode( void );

//tariff
extern void Sequence( unsigned char *Buf, unsigned char Num );
extern void Timezone_Judge(void);
extern void Price_Judge(void);
extern unsigned char JudgeYearClock(unsigned char *YearLadder);
extern unsigned char Freeze_Change_Judge( unsigned char Change );
extern unsigned char Year_Ladder_Judge(unsigned char status);
extern void ReadE2WithJieti( uint08 Ch, uint08 *Buf );
extern void WriteE2WithJieti( uint08 Ch, uint08 *Buf );

//event
extern void Exchange(unsigned char *BufA, unsigned char *BufB, unsigned char Len );
extern void Inverse( unsigned char *Buf, unsigned char Len );
extern void Number_Add1_Direct(unsigned char *BufA);
extern void Number_Add1(unsigned char Offset);
extern unsigned char Read_Event_Number( unsigned char *BufA, unsigned char Offset );
extern unsigned char Read_Event_Point( unsigned char Inpage );
extern unsigned char Write_Event_Point( unsigned char Inpage );
extern unsigned char RdRecTimes( unsigned char Inpage );
extern void Note_Powerd_Event(void);
extern void Note_Relay_Event(void);
extern void ClrRecTimes( unsigned char Inpage, unsigned char mode );
extern void Note_Run_Event( unsigned char Type );
extern unsigned char ReadLoadRec( unsigned char Ch, unsigned char *InBuf, unsigned char *OutBuf );
extern void ClearPloadRec( unsigned char *Clock );
extern uint16 CalcAbsDay(unsigned char * psTm);
extern uint16 CalcAbsMin(unsigned char * psTm);
extern unsigned long int CalcTime(unsigned char* psTm);
extern void Load_Judge(void);
extern unsigned char Event_Record( unsigned char Inpage );
extern void DltoEepromBuf( unsigned char st );
extern void Four_RpdltoEepromBuf( unsigned char st );
extern void Comp_RpdltoEepromBuf( unsigned char st );

//iokey
extern void Enable_Closerelay(void);
extern void Store_Meterstatus(void);
extern void Displaykey_Process(void);
extern void Displaykey_Check(void);
extern void Cover_Check(void);
extern void Commmodule_Check(void);
extern void Relaystatus_Check(void);

//init
//extern void Init_Int();
extern void I2c_Wait_5ms( void );
extern void Delay_Initial(unsigned char Num);
extern void Clear_Wdt(void);
extern void Clear_W_Wdt(void);
extern void Init_Arm0(void);
extern void Clk_Adj_Proc(void);
extern void Adc_Proc(void);
extern void Init_System(void);
extern uint08 Call_Get_PRIMASK( void );
extern void Veri_SVD_Ctrl( uint08 Mode );
extern int isPowerOff(void);
extern unsigned char AddNClock( unsigned char Start, unsigned char *Clock, unsigned int Num );

//money
extern void Calculate_Overflow( unsigned char *Buf, unsigned char Num );
extern void Calculate_Dl( unsigned char *Buf, unsigned char Style );
extern void Calculate_Dl_G( unsigned char *Buf );
extern void Hex2Bcd_Dl( unsigned char *Buf, unsigned char Di );
extern void Hex2Bcd_Dl_G( unsigned char *Buf, unsigned char Di );
extern void Calc_Pwr_Proc(void);
extern void Process_Usedl( unsigned char offset );
extern void Freeze_Judge(void);
extern void Histroy_Freeze_Dl(unsigned char status);
extern void Freeze_Usedl(unsigned char type);
extern void Freeze_Dl(unsigned int page, unsigned char offset);
extern void Pd_Hourfreeze_Judge(void);
extern void Pd_Histroyfreeze_Judge(void);
extern void Pd_Calculate_Judge(void);
extern void Init_Dayfreeze_Judge(void);
extern void Wr_Pretime_Hisfreeze(void);
extern void Wr_Pretime_Dayfreeze(void);
extern void Freeze_Pddata(void);
extern void Judge_Relay_Delay(void);
extern void Init_Metererrstatus(void);
extern void Alarmstatus_Judge(void);
extern void Mt_Alarmstatus_Judge(void);
extern void InitVolSts( unsigned char Mode );
extern void VolPassRate( void );
extern void CalLoad( unsigned char *Buf, unsigned char Mode );

//interrupt
extern void Judge_645_Frame( uint08 CH, uint08 RcvData );
extern void Tx_645_Frame( uint08 CH );
extern void Lcdled_Control(void);
extern void Sleep( uint08 status );
extern void Wr_Powerdown_Data( unsigned char mode );
extern void Save_Keep_Timer( unsigned char Store );
extern void Get_Keep_Timer(unsigned char Ch, unsigned char *Buf);

//7816
extern unsigned char EsamReset( void );
extern void CloseEsam( void );
extern unsigned char Clear_Rand_Gene( void );
extern unsigned char ReadRecFile( unsigned char P1 );
extern unsigned char ReadBinFile( unsigned char CH, unsigned char P1, unsigned char P2, unsigned char Len );
extern unsigned char Cal_Mac_Pro(unsigned char P2, unsigned char *BufA , unsigned char Len);
extern unsigned char SelectFile( unsigned char CH, unsigned char F1, unsigned char F2 );
extern void UpdataRunFile(void);
extern unsigned char Update_ESAM_Bin_Mac( unsigned char P1, unsigned char P2, unsigned char *Buf, unsigned char Len );
extern void Mac_Err_Proc( void );
extern unsigned char UpdateEepromKey( unsigned char Ch );
extern unsigned char UpdateEsamKey( void );
extern void GetKeyStatus(void);
extern void FailKey( void );
extern void Clear_Meter(unsigned char Ch, unsigned char *Opt);

//factory
extern void Factory_Init( void );

//lcd_disiplay
extern void Lcd_Display( void );
extern void Lcd_LCDEN_On(void);
extern void Lcd_LCDEN_Off(void);

//energy
extern void ATT7051AInitial(void);
extern void ATT7051_Check(void);
extern void Read_UIP(void);
extern void Judge_Uip_Data(void);
extern void Init_Meter_Chip(void);
extern unsigned char Check_Err_Pro(unsigned char Ch, unsigned char DI0);
extern unsigned char Comm_Read_Reg(unsigned char *Buf);
extern unsigned char Comm_Write_Reg(unsigned char *Buf);
extern unsigned char ChkPdRcdTime(void);
#if(1 == CHINT_Mode)
extern unsigned char CommReadCalData(unsigned char Ch);
extern unsigned char CommWriteCalData(unsigned char Ch);
#endif

//uart
extern unsigned char Add_Min_Clock( unsigned char *Clock, unsigned char Min );
extern unsigned long int Calculate_Timer(unsigned char Offset);
extern void Calculate_Ah( unsigned char *Inbuf );
extern void Clr_Commu_Preparerelay(void);
extern void Clr_Commu_Relaydata(void);
extern void Clr_Reportnum( unsigned char i );
extern void Clr_Reportdata( unsigned char i );
extern void Set_Reportdata( unsigned char Offset );
extern void Clr_Zero_Data(void);
extern void Clr_Otherdata( unsigned char Type );
extern unsigned char ChkLastclockerrRcdTime( void );
extern void Uart_Proc( unsigned char Ch );
extern unsigned char IsBCD( uint08 Value );
extern unsigned char IsMultiBcd( unsigned char *Buf, unsigned char Len );
extern void Xor_Data( unsigned char *BufA, unsigned char *BufB, unsigned char Num );
extern void Calculate_Program_Cs( unsigned char *Buf );
extern unsigned char Cal_Comb( unsigned char DI2, unsigned char DI1, unsigned char DI0, unsigned char *ReturnBuf );
extern unsigned char JudgeSwitch( unsigned char *Buf, unsigned char Inv );
extern void ProgramRecord( unsigned char *Dix, unsigned char *Opt );
extern void CalZhuhe( const unsigned char *ZhuBuf, unsigned char *RtBuf, unsigned char Mode, unsigned char Offset );
extern void Cal_Comb_Usedl( unsigned char DI1, unsigned char DI0, unsigned char *ReturnBuf );
extern void FLRecord( unsigned char *InOpt );
extern void JTRecord( unsigned char *InOpt );
extern unsigned char  Cal_ChkSum(unsigned char *Buf,unsigned char Len);
//extern void Send2Uart( unsigned char *Buf, unsigned char Len );
extern void Ble_Init(void);
extern void Ble_Rst(void);

extern void LoopExchange( unsigned char *Drc, unsigned char *Src, unsigned char Times, unsigned char Spec );
extern void LoopInverse( unsigned char *Inv, unsigned char Times, unsigned char Spec );
extern unsigned char WriteBinWithMac( uint08 CH, unsigned char P1, unsigned char P2, unsigned char Len );
extern unsigned char Relay_Ctrl(unsigned char Ch);
extern void MacExchange( unsigned char *Drc, unsigned char *Src, unsigned char Len );
extern void GetKey( unsigned char *KeyStatus );
extern unsigned char Cmp_Meter_Id(unsigned char *Buf);
extern unsigned char Comm_Auth_Judge( void );
extern void Pd_Freeze_Judge(unsigned char CH);
extern void RefreshPrice( void );
extern void Report_Response( union B32_B08_2 DI07 );
extern unsigned char ReportEvent( uint08 repmode );
extern unsigned char ReportProc( unsigned char Ch, unsigned char Obj );

//flash
extern void CloseFlash( void );
extern unsigned char Flash_Rd_Bottom ( unsigned long Page, unsigned short offset, unsigned char *RtBuf, unsigned short Len );
extern unsigned char Flash_Write_Bottom( unsigned long Page, unsigned short offset, unsigned char *InBuf, unsigned short Len );
extern RecStore GetRecNum(  unsigned char Obj, unsigned char Case );
extern unsigned short GetValtimes( unsigned char Obj, unsigned char Case );
extern RtFlash GetRecAddr( unsigned char Obj, unsigned char Case, unsigned short Sn, const RecStore *RtRec );
extern unsigned char SynFlashRec( unsigned char RecNum );
extern void SynEeprom( void );
extern unsigned char IsFlashRec( unsigned char Obj );
#endif
