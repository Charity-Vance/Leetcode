#ifndef __DI_H
#define __DI_H

/********************************对象标识宏定义********************************/
/******************************电能量类对象******************************/
/*当前组合有功电能*/
#define CCom_Ac_En_FF_0                         0x00000200                      /*当前组合有功电能数据块*/
#define CCom_Ac_Tol_En_0                        0x00000201                      /*当前组合有功总电能*/
#define CCom_Ac_T1_En_0                         0x00000202                      /*当前组合有功费率1电能*/
#define CCom_Ac_T2_En_0                         0x00000203                      /*当前组合有功费率2电能*/
#define CCom_Ac_T3_En_0                         0x00000204                      /*当前组合有功费率3电能*/
#define CCom_Ac_T4_En_0                         0x00000205                      /*当前组合有功费率4电能*/
#define CCom_Ac_T5_En_0                         0x00000206                      /*当前组合有功费率5电能*/
#define CCom_Ac_T6_En_0                         0x00000207                      /*当前组合有功费率6电能*/
#define CCom_Ac_T7_En_0                         0x00000208                      /*当前组合有功费率7电能*/
#define CCom_Ac_T8_En_0                         0x00000209                      /*当前组合有功费率8电能*/
#define CCom_Ac_T9_En_0                         0x0000020A                      /*当前组合有功费率9电能*/
#define CCom_Ac_T10_En_0                        0x0000020B                      /*当前组合有功费率10电能*/
#define CCom_Ac_T11_En_0                        0x0000020C                      /*当前组合有功费率11电能*/
#define CCom_Ac_T12_En_0                        0x0000020D                      /*当前组合有功费率12电能*/

#define CCom_Ac_PreEn_FF_0                      0x00000400                      /*当前组合有功精确电能数据块*/
#define CCom_Ac_Tol_PreEn_0                     0x00000401                      /*当前组合有功总精确电能*/
#define CCom_Ac_T1_PreEn_0                      0x00000402                      /*当前组合有功费率1精确电能*/
#define CCom_Ac_T2_PreEn_0                      0x00000403                      /*当前组合有功费率2精确电能*/
#define CCom_Ac_T3_PreEn_0                      0x00000404                      /*当前组合有功费率3精确电能*/
#define CCom_Ac_T4_PreEn_0                      0x00000405                      /*当前组合有功费率4精确电能*/
#define CCom_Ac_T5_PreEn_0                      0x00000406                      /*当前组合有功费率5精确电能*/
#define CCom_Ac_T6_PreEn_0                      0x00000407                      /*当前组合有功费率6精确电能*/
#define CCom_Ac_T7_PreEn_0                      0x00000408                      /*当前组合有功费率7精确电能*/
#define CCom_Ac_T8_PreEn_0                      0x00000409                      /*当前组合有功费率8精确电能*/
#define CCom_Ac_T9_PreEn_0                      0x0000040A                      /*当前组合有功费率9精确电能*/
#define CCom_Ac_T10_PreEn_0                     0x0000040B                      /*当前组合有功费率10精确电能*/
#define CCom_Ac_T11_PreEn_0                     0x0000040C                      /*当前组合有功费率11精确电能*/
#define CCom_Ac_T12_PreEn_0                     0x0000040D                      /*当前组合有功费率12精确电能*/

#define CCom_Ac_LastPulse_FF_0                  0x00000600                      /*当前组合有功脉冲尾数数据块*/
#define CCom_Ac_Tol_LastPulse_0                 0x00000601                      /*当前组合有功总脉冲尾数*/
#define CCom_Ac_T1_LastPulse_0                  0x00000602                      /*当前组合有功费率1脉冲尾数*/
#define CCom_Ac_T2_LastPulse_0                  0x00000603                      /*当前组合有功费率2脉冲尾数*/
#define CCom_Ac_T3_LastPulse_0                  0x00000604                      /*当前组合有功费率3脉冲尾数*/
#define CCom_Ac_T4_LastPulse_0                  0x00000605                      /*当前组合有功费率4脉冲尾数*/
#define CCom_Ac_T5_LastPulse_0                  0x00000606                      /*当前组合有功费率5脉冲尾数*/
#define CCom_Ac_T6_LastPulse_0                  0x00000607                      /*当前组合有功费率6脉冲尾数*/
#define CCom_Ac_T7_LastPulse_0                  0x00000608                      /*当前组合有功费率7脉冲尾数*/
#define CCom_Ac_T8_LastPulse_0                  0x00000609                      /*当前组合有功费率8脉冲尾数*/
#define CCom_Ac_T9_LastPulse_0                  0x0000060A                      /*当前组合有功费率9脉冲尾数*/
#define CCom_Ac_T10_LastPulse_0                 0x0000060B                      /*当前组合有功费率10脉冲尾数*/
#define CCom_Ac_T11_LastPulse_0                 0x0000060C                      /*当前组合有功费率11脉冲尾数*/
#define CCom_Ac_T12_LastPulse_0                 0x0000060D                      /*当前组合有功费率12脉冲尾数*/
/*当前正向有功电能*/
#define CPos_Ac_En_FF_0                         0x00100200                      /*当前正向有功电能数据块*/
#define CPos_Ac_Tol_En_0                        0x00100201                      /*当前正向有功总电能*/
#define CPos_Ac_T1_En_0                         0x00100202                      /*当前正向有功费率1电能*/
#define CPos_Ac_T2_En_0                         0x00100203                      /*当前正向有功费率2电能*/
#define CPos_Ac_T3_En_0                         0x00100204                      /*当前正向有功费率3电能*/
#define CPos_Ac_T4_En_0                         0x00100205                      /*当前正向有功费率4电能*/
#define CPos_Ac_T5_En_0                         0x00100206                      /*当前正向有功费率5电能*/
#define CPos_Ac_T6_En_0                         0x00100207                      /*当前正向有功费率6电能*/
#define CPos_Ac_T7_En_0                         0x00100208                      /*当前正向有功费率7电能*/
#define CPos_Ac_T8_En_0                         0x00100209                      /*当前正向有功费率8电能*/
#define CPos_Ac_T9_En_0                         0x0010020A                      /*当前正向有功费率9电能*/
#define CPos_Ac_T10_En_0                        0x0010020B                      /*当前正向有功费率10电能*/
#define CPos_Ac_T11_En_0                        0x0010020C                      /*当前正向有功费率11电能*/
#define CPos_Ac_T12_En_0                        0x0010020D                      /*当前正向有功费率12电能*/

#define CPos_Ac_En_PreFF_0                      0x00100400                      /*当前正向有功精确电能数据块*/
#define CPos_Ac_Tol_PreEn_0                     0x00100401                      /*当前正向有功总精确电能*/
#define CPos_Ac_T1_PreEn_0                      0x00100402                      /*当前正向有功费率1精确电能*/
#define CPos_Ac_T2_PreEn_0                      0x00100403                      /*当前正向有功费率2精确电能*/
#define CPos_Ac_T3_PreEn_0                      0x00100404                      /*当前正向有功费率3精确电能*/
#define CPos_Ac_T4_PreEn_0                      0x00100405                      /*当前正向有功费率4精确电能*/
#define CPos_Ac_T5_PreEn_0                      0x00100406                      /*当前正向有功费率5精确电能*/
#define CPos_Ac_T6_PreEn_0                      0x00100407                      /*当前正向有功费率6精确电能*/
#define CPos_Ac_T7_PreEn_0                      0x00100408                      /*当前正向有功费率7精确电能*/
#define CPos_Ac_T8_PreEn_0                      0x00100409                      /*当前正向有功费率8精确电能*/
#define CPos_Ac_T9_PreEn_0                      0x0010040A                      /*当前正向有功费率9精确电能*/
#define CPos_Ac_T10_PreEn_0                     0x0010040B                      /*当前正向有功费率10精确电能*/
#define CPos_Ac_T11_PreEn_0                     0x0010040C                      /*当前正向有功费率11精确电能*/
#define CPos_Ac_T12_PreEn_0                     0x0010040D                      /*当前正向有功费率12精确电能*/

#define CPos_Ac_LastPulse_FF_0                  0x00100600                      /*当前正向有功脉冲尾数数据块*/
#define CPos_Ac_Tol_LastPulse_0                 0x00100601                      /*当前正向有功总脉冲尾数*/
#define CPos_Ac_T1_LastPulse_0                  0x00100602                      /*当前正向有功费率1脉冲尾数*/
#define CPos_Ac_T2_LastPulse_0                  0x00100603                      /*当前正向有功费率2脉冲尾数*/
#define CPos_Ac_T3_LastPulse_0                  0x00100604                      /*当前正向有功费率3脉冲尾数*/
#define CPos_Ac_T4_LastPulse_0                  0x00100605                      /*当前正向有功费率4脉冲尾数*/
#define CPos_Ac_T5_LastPulse_0                  0x00100606                      /*当前正向有功费率5脉冲尾数*/
#define CPos_Ac_T6_LastPulse_0                  0x00100607                      /*当前正向有功费率6脉冲尾数*/
#define CPos_Ac_T7_LastPulse_0                  0x00100608                      /*当前正向有功费率7脉冲尾数*/
#define CPos_Ac_T8_LastPulse_0                  0x00100609                      /*当前正向有功费率8脉冲尾数*/
#define CPos_Ac_T9_LastPulse_0                  0x0010060A                      /*当前正向有功费率9脉冲尾数*/
#define CPos_Ac_T10_LastPulse_0                 0x0010060B                      /*当前正向有功费率10脉冲尾数*/
#define CPos_Ac_T11_LastPulse_0                 0x0010060C                      /*当前正向有功费率11脉冲尾数*/
#define CPos_Ac_T12_LastPulse_0                 0x0010060D                      /*当前正向有功费率12脉冲尾数*/
/*当前反向有功电能*/
#define CRev_Ac_En_FF_0                         0x00200200                      /*当前反向有功电能数据块*/
#define CRev_Ac_Tol_En_0                        0x00200201                      /*当前反向有功总电能*/
#define CRev_Ac_T1_En_0                         0x00200202                      /*当前反向有功费率1电能*/
#define CRev_Ac_T2_En_0                         0x00200203                      /*当前反向有功费率2电能*/
#define CRev_Ac_T3_En_0                         0x00200204                      /*当前反向有功费率3电能*/
#define CRev_Ac_T4_En_0                         0x00200205                      /*当前反向有功费率5电能*/
#define CRev_Ac_T5_En_0                         0x00200206                      /*当前反向有功费率6电能*/
#define CRev_Ac_T6_En_0                         0x00200207                      /*当前反向有功费率7电能*/
#define CRev_Ac_T7_En_0                         0x00200208                      /*当前反向有功费率8电能*/
#define CRev_Ac_T8_En_0                         0x00200209                      /*当前反向有功费率9电能*/
#define CRev_Ac_T9_En_0                         0x0020020A                      /*当前反向有功费率10电能*/
#define CRev_Ac_T10_En_0                        0x0020020B                      /*当前反向有功费率11电能*/
#define CRev_Ac_T11_En_0                        0x0020020C                      /*当前反向有功费率12电能*/
#define CRev_Ac_T12_En_0                        0x0020020D                      /*当前反向有功费率电能*/

#define CRev_Ac_En_PreFF_0                      0x00200400                      /*当前反向有功精确电能数据块*/
#define CRev_Ac_Tol_PreEn_0                     0x00200401                      /*当前反向有功总精确电能*/
#define CRev_Ac_T1_PreEn_0                      0x00200402                      /*当前反向有功费率1精确电能*/
#define CRev_Ac_T2_PreEn_0                      0x00200403                      /*当前反向有功费率2精确电能*/
#define CRev_Ac_T3_PreEn_0                      0x00200404                      /*当前反向有功费率3精确电能*/
#define CRev_Ac_T4_PreEn_0                      0x00200405                      /*当前反向有功费率4精确电能*/
#define CRev_Ac_T5_PreEn_0                      0x00200406                      /*当前反向有功费率5精确电能*/
#define CRev_Ac_T6_PreEn_0                      0x00200407                      /*当前反向有功费率6精确电能*/
#define CRev_Ac_T7_PreEn_0                      0x00200408                      /*当前反向有功费率7精确电能*/
#define CRev_Ac_T8_PreEn_0                      0x00200409                      /*当前反向有功费率8精确电能*/
#define CRev_Ac_T9_PreEn_0                      0x0020040A                      /*当前反向有功费率9精确电能*/
#define CRev_Ac_T10_PreEn_0                     0x0020040B                      /*当前反向有功费率10精确电能*/
#define CRev_Ac_T11_PreEn_0                     0x0020040C                      /*当前反向有功费率11精确电能*/
#define CRev_Ac_T12_PreEn_0                     0x0020040D                      /*当前反向有功费率12精确电能*/

#define CRev_Ac_LastPulse_FF_0                  0x00200600                      /*当前反向有功脉冲尾数数据块*/
#define CRev_Ac_Tol_LastPulse_0                 0x00200601                      /*当前反向有功总脉冲尾数*/
#define CRev_Ac_T1_LastPulse_0                  0x00200602                      /*当前反向有功费率1脉冲尾数*/
#define CRev_Ac_T2_LastPulse_0                  0x00200603                      /*当前反向有功费率2脉冲尾数*/
#define CRev_Ac_T3_LastPulse_0                  0x00200604                      /*当前反向有功费率3脉冲尾数*/
#define CRev_Ac_T4_LastPulse_0                  0x00200605                      /*当前反向有功费率4脉冲尾数*/
#define CRev_Ac_T5_LastPulse_0                  0x00200606                      /*当前反向有功费率5脉冲尾数*/
#define CRev_Ac_T6_LastPulse_0                  0x00200607                      /*当前反向有功费率6脉冲尾数*/
#define CRev_Ac_T7_LastPulse_0                  0x00200608                      /*当前反向有功费率7脉冲尾数*/
#define CRev_Ac_T8_LastPulse_0                  0x00200609                      /*当前反向有功费率8脉冲尾数*/
#define CRev_Ac_T9_LastPulse_0                  0x0020060A                      /*当前反向有功费率9脉冲尾数*/
#define CRev_Ac_T10_LastPulse_0                 0x0020060B                      /*当前反向有功费率10脉冲尾数*/
#define CRev_Ac_T11_LastPulse_0                 0x0020060C                      /*当前反向有功费率11脉冲尾数*/
#define CRev_Ac_T12_LastPulse_0                 0x0020060D                      /*当前反向有功费率12脉冲尾数*/
/*当前组合无功1电能*/
#define CCom_Re1_En_FF_0                        0x00300200                      /*当前组合无功1电能数据块*/
#define CCom_Re1_Tol_En_0                       0x00300201                      /*当前组合无功1总电能*/
#define CCom_Re1_T1_En_0                        0x00300202                      /*当前组合无功1费率1电能*/
#define CCom_Re1_T2_En_0                        0x00300203                      /*当前组合无功1费率2电能*/
#define CCom_Re1_T3_En_0                        0x00300204                      /*当前组合无功1费率3电能*/
#define CCom_Re1_T4_En_0                        0x00300205                      /*当前组合无功1费率4电能*/
#define CCom_Re1_T5_En_0                        0x00300206                      /*当前组合无功1费率5电能*/
#define CCom_Re1_T6_En_0                        0x00300207                      /*当前组合无功1费率6电能*/
#define CCom_Re1_T7_En_0                        0x00300208                      /*当前组合无功1费率7电能*/
#define CCom_Re1_T8_En_0                        0x00300209                      /*当前组合无功1费率8电能*/
#define CCom_Re1_T9_En_0                        0x0030020A                      /*当前组合无功1费率9电能*/
#define CCom_Re1_T10_En_0                       0x0030020B                      /*当前组合无功1费率10电能*/
#define CCom_Re1_T11_En_0                       0x0030020C                      /*当前组合无功1费率11电能*/
#define CCom_Re1_T12_En_0                       0x0030020D                      /*当前组合无功1费率12电能*/

#define CCom_Re1_PreEn_FF_0                     0x00300400                      /*当前组合无功1精确电能数据块*/
#define CCom_Re1_Tol_PreEn_0                    0x00300401                      /*当前组合无功1精确总电能*/
#define CCom_Re1_T1_PreEn_0                     0x00300402                      /*当前组合无功1费率1精确电能*/
#define CCom_Re1_T2_PreEn_0                     0x00300403                      /*当前组合无功1费率2精确电能*/
#define CCom_Re1_T3_PreEn_0                     0x00300404                      /*当前组合无功1费率3精确电能*/
#define CCom_Re1_T4_PreEn_0                     0x00300405                      /*当前组合无功1费率4精确电能*/
#define CCom_Re1_T5_PreEn_0                     0x00300406                      /*当前组合无功1费率5精确电能*/
#define CCom_Re1_T6_PreEn_0                     0x00300407                      /*当前组合无功1费率6精确电能*/
#define CCom_Re1_T7_PreEn_0                     0x00300408                      /*当前组合无功1费率7精确电能*/
#define CCom_Re1_T8_PreEn_0                     0x00300409                      /*当前组合无功1费率8精确电能*/
#define CCom_Re1_T9_PreEn_0                     0x0030040A                      /*当前组合无功1费率9精确电能*/
#define CCom_Re1_T10_PreEn_0                    0x0030040B                      /*当前组合无功1费率10精确电能*/
#define CCom_Re1_T11_PreEn_0                    0x0030040C                      /*当前组合无功1费率11精确电能*/
#define CCom_Re1_T12_PreEn_0                    0x0030040D                      /*当前组合无功1费率12精确电能*/

#define CCom_Re1_LastPulse_FF_0                 0x00300600                      /*当前组合无功1脉冲尾数数据块*/
#define CCom_Re1_Tol_LastPulse_0                0x00300601                      /*当前组合无功1脉冲尾数*/
#define CCom_Re1_T1_LastPulse_0                 0x00300602                      /*当前组合无功1费率1脉冲尾数*/
#define CCom_Re1_T2_LastPulse_0                 0x00300603                      /*当前组合无功1费率2脉冲尾数*/
#define CCom_Re1_T3_LastPulse_0                 0x00300604                      /*当前组合无功1费率3脉冲尾数*/
#define CCom_Re1_T4_LastPulse_0                 0x00300605                      /*当前组合无功1费率4脉冲尾数*/
#define CCom_Re1_T5_LastPulse_0                 0x00300606                      /*当前组合无功1费率5脉冲尾数*/
#define CCom_Re1_T6_LastPulse_0                 0x00300607                      /*当前组合无功1费率6脉冲尾数*/
#define CCom_Re1_T7_LastPulse_0                 0x00300608                      /*当前组合无功1费率7脉冲尾数*/
#define CCom_Re1_T8_LastPulse_0                 0x00300609                      /*当前组合无功1费率8脉冲尾数*/
#define CCom_Re1_T9_LastPulse_0                 0x0030060A                      /*当前组合无功1费率9脉冲尾数*/
#define CCom_Re1_T10_LastPulse_0                0x0030060B                      /*当前组合无功1费率10脉冲尾数*/
#define CCom_Re1_T11_LastPulse_0                0x0030060C                      /*当前组合无功1费率11脉冲尾数*/
#define CCom_Re1_T12_LastPulse_0                0x0030060D                      /*当前组合无功1费率12脉冲尾数*/
/*当前组合无功2电能*/
#define CCom_Re2_En_FF_0                        0x00400200                      /*当前组合无功2电能数据块*/
#define CCom_Re2_Tol_En_0                       0x00400201                      /*当前组合无功2总电能*/
#define CCom_Re2_T1_En_0                        0x00400202                      /*当前组合无功2费率1电能*/
#define CCom_Re2_T2_En_0                        0x00400203                      /*当前组合无功2费率2电能*/
#define CCom_Re2_T3_En_0                        0x00400204                      /*当前组合无功2费率3电能*/
#define CCom_Re2_T4_En_0                        0x00400205                      /*当前组合无功2费率4电能*/
#define CCom_Re2_T5_En_0                        0x00400206                      /*当前组合无功2费率5电能*/
#define CCom_Re2_T6_En_0                        0x00400207                      /*当前组合无功2费率6电能*/
#define CCom_Re2_T7_En_0                        0x00400208                      /*当前组合无功2费率7电能*/
#define CCom_Re2_T8_En_0                        0x00400209                      /*当前组合无功2费率8电能*/
#define CCom_Re2_T9_En_0                        0x0040020A                      /*当前组合无功2费率9电能*/
#define CCom_Re2_T10_En_0                       0x0040020B                      /*当前组合无功2费率10电能*/
#define CCom_Re2_T11_En_0                       0x0040020C                      /*当前组合无功2费率11电能*/
#define CCom_Re2_T12_En_0                       0x0040020D                      /*当前组合无功2费率12电能*/

#define CCom_Re2_PreEn_FF_0                     0x00400400                      /*当前组合无功2精确电能数据块*/
#define CCom_Re2_Tol_PreEn_0                    0x00400401                      /*当前组合无功2总精确电能*/
#define CCom_Re2_T1_PreEn_0                     0x00400402                      /*当前组合无功2费率1精确电能*/
#define CCom_Re2_T2_PreEn_0                     0x00400403                      /*当前组合无功2费率2精确电能*/
#define CCom_Re2_T3_PreEn_0                     0x00400404                      /*当前组合无功2费率3精确电能*/
#define CCom_Re2_T4_PreEn_0                     0x00400405                      /*当前组合无功2费率4精确电能*/
#define CCom_Re2_T5_PreEn_0                     0x00400406                      /*当前组合无功2费率5精确电能*/
#define CCom_Re2_T6_PreEn_0                     0x00400407                      /*当前组合无功2费率6精确电能*/
#define CCom_Re2_T7_PreEn_0                     0x00400408                      /*当前组合无功2费率7精确电能*/
#define CCom_Re2_T8_PreEn_0                     0x00400409                      /*当前组合无功2费率8精确电能*/
#define CCom_Re2_T9_PreEn_0                     0x0040040A                      /*当前组合无功2费率9精确电能*/
#define CCom_Re2_T10_PreEn_0                    0x0040040B                      /*当前组合无功2费率10精确电能*/
#define CCom_Re2_T11_PreEn_0                    0x0040040C                      /*当前组合无功2费率11精确电能*/
#define CCom_Re2_T12_PreEn_0                    0x0040040D                      /*当前组合无功2费率12精确电能*/

#define CCom_Re2_LastPulse_FF_0                 0x00400600                      /*当前组合无功2脉冲尾数数据块*/
#define CCom_Re2_Tol_LastPulse_0                0x00400601                      /*当前组合无功2总脉冲尾数*/
#define CCom_Re2_T1_LastPulse_0                 0x00400602                      /*当前组合无功2费率1脉冲尾数*/
#define CCom_Re2_T2_LastPulse_0                 0x00400603                      /*当前组合无功2费率2脉冲尾数*/
#define CCom_Re2_T3_LastPulse_0                 0x00400604                      /*当前组合无功2费率3脉冲尾数*/
#define CCom_Re2_T4_LastPulse_0                 0x00400605                      /*当前组合无功2费率4脉冲尾数*/
#define CCom_Re2_T5_LastPulse_0                 0x00400606                      /*当前组合无功2费率5脉冲尾数*/
#define CCom_Re2_T6_LastPulse_0                 0x00400607                      /*当前组合无功2费率6脉冲尾数*/
#define CCom_Re2_T7_LastPulse_0                 0x00400608                      /*当前组合无功2费率7脉冲尾数*/
#define CCom_Re2_T8_LastPulse_0                 0x00400609                      /*当前组合无功2费率8脉冲尾数*/
#define CCom_Re2_T9_LastPulse_0                 0x0040060A                      /*当前组合无功2费率9脉冲尾数*/
#define CCom_Re2_T10_LastPulse_0                0x0040060B                      /*当前组合无功2费率10脉冲尾数*/
#define CCom_Re2_T11_LastPulse_0                0x0040060C                      /*当前组合无功2费率11脉冲尾数*/
#define CCom_Re2_T12_LastPulse_0                0x0040060D                      /*当前组合无功2费率12脉冲尾数*/
/*当前第一象限无功电能*/
#define CQua1_Re_En_FF_0                        0x00500200                      /*当前1象限无功电能数据块*/
#define CQua1_Re_Tol_En_0                       0x00500201                      /*当前1象限无功总电能*/
#define CQua1_Re_T1_En_0                        0x00500202                      /*当前1象限无功费率1电能*/
#define CQua1_Re_T2_En_0                        0x00500203                      /*当前1象限无功费率2电能*/
#define CQua1_Re_T3_En_0                        0x00500204                      /*当前1象限无功费率3电能*/
#define CQua1_Re_T4_En_0                        0x00500205                      /*当前1象限无功费率4电能*/
#define CQua1_Re_T5_En_0                        0x00500206                      /*当前1象限无功费率5电能*/
#define CQua1_Re_T6_En_0                        0x00500207                      /*当前1象限无功费率6电能*/
#define CQua1_Re_T7_En_0                        0x00500208                      /*当前1象限无功费率7电能*/
#define CQua1_Re_T8_En_0                        0x00500209                      /*当前1象限无功费率8电能*/
#define CQua1_Re_T9_En_0                        0x0050020A                      /*当前1象限无功费率9电能*/
#define CQua1_Re_T10_En_0                       0x0050020B                      /*当前1象限无功费率10电能*/
#define CQua1_Re_T11_En_0                       0x0050020C                      /*当前1象限无功费率11电能*/
#define CQua1_Re_T12_En_0                       0x0050020D                      /*当前1象限无功费率12电能*/

#define CQua1_Re_PreEn_FF_0                     0x00500400                      /*当前1象限无功精确电能数据块*/
#define CQua1_Re_Tol_PreEn_0                    0x00500401                      /*当前1象限无功总精确电能*/
#define CQua1_Re_T1_PreEn_0                     0x00500402                      /*当前1象限无功费率1精确电能*/
#define CQua1_Re_T2_PreEn_0                     0x00500403                      /*当前1象限无功费率2精确电能*/
#define CQua1_Re_T3_PreEn_0                     0x00500404                      /*当前1象限无功费率3精确电能*/
#define CQua1_Re_T4_PreEn_0                     0x00500405                      /*当前1象限无功费率4精确电能*/
#define CQua1_Re_T5_PreEn_0                     0x00500406                      /*当前1象限无功费率5精确电能*/
#define CQua1_Re_T6_PreEn_0                     0x00500407                      /*当前1象限无功费率6精确电能*/
#define CQua1_Re_T7_PreEn_0                     0x00500408                      /*当前1象限无功费率7精确电能*/
#define CQua1_Re_T8_PreEn_0                     0x00500409                      /*当前1象限无功费率8精确电能*/
#define CQua1_Re_T9_PreEn_0                     0x0050040A                      /*当前1象限无功费率9精确电能*/
#define CQua1_Re_T10_PreEn_0                    0x0050040B                      /*当前1象限无功费率10精确电能*/
#define CQua1_Re_T11_PreEn_0                    0x0050040C                      /*当前1象限无功费率11精确电能*/
#define CQua1_Re_T12_PreEn_0                    0x0050040D                      /*当前1象限无功费率12精确电能*/

#define CQua1_Re_LastPulse_FF_0                 0x00500600                      /*当前1象限无功脉冲尾数数据块*/
#define CQua1_Re_Tol_LastPulse_0                0x00500601                      /*当前1象限无功总脉冲尾数*/
#define CQua1_Re_T1_LastPulse_0                 0x00500602                      /*当前1象限无功费率1脉冲尾数*/
#define CQua1_Re_T2_LastPulse_0                 0x00500603                      /*当前1象限无功费率2脉冲尾数*/
#define CQua1_Re_T3_LastPulse_0                 0x00500604                      /*当前1象限无功费率3脉冲尾数*/
#define CQua1_Re_T4_LastPulse_0                 0x00500605                      /*当前1象限无功费率4脉冲尾数*/
#define CQua1_Re_T5_LastPulse_0                 0x00500606                      /*当前1象限无功费率5脉冲尾数*/
#define CQua1_Re_T6_LastPulse_0                 0x00500607                      /*当前1象限无功费率6脉冲尾数*/
#define CQua1_Re_T7_LastPulse_0                 0x00500608                      /*当前1象限无功费率7脉冲尾数*/
#define CQua1_Re_T8_LastPulse_0                 0x00500609                      /*当前1象限无功费率8脉冲尾数*/
#define CQua1_Re_T9_LastPulse_0                 0x0050060A                      /*当前1象限无功费率9脉冲尾数*/
#define CQua1_Re_T10_LastPulse_0                0x0050060B                      /*当前1象限无功费率10脉冲尾数*/
#define CQua1_Re_T11_LastPulse_0                0x0050060C                      /*当前1象限无功费率11脉冲尾数*/
#define CQua1_Re_T12_LastPulse_0                0x0050060D                      /*当前1象限无功费率12脉冲尾数*/
/*当前第二象限无功电能*/
#define CQua2_Re_En_FF_0                        0x00600200                      /*当前2象限无功电能数据块*/
#define CQua2_Re_Tol_En_0                       0x00600201                      /*当前2象限无功总电能*/
#define CQua2_Re_T1_En_0                        0x00600202                      /*当前2象限无功费率1电能*/
#define CQua2_Re_T2_En_0                        0x00600203                      /*当前2象限无功费率2电能*/
#define CQua2_Re_T3_En_0                        0x00600204                      /*当前2象限无功费率3电能*/
#define CQua2_Re_T4_En_0                        0x00600205                      /*当前2象限无功费率4电能*/
#define CQua2_Re_T5_En_0                        0x00600206                      /*当前2象限无功费率5电能*/
#define CQua2_Re_T6_En_0                        0x00600207                      /*当前2象限无功费率6电能*/
#define CQua2_Re_T7_En_0                        0x00600208                      /*当前2象限无功费率7电能*/
#define CQua2_Re_T8_En_0                        0x00600209                      /*当前2象限无功费率8电能*/
#define CQua2_Re_T9_En_0                        0x0060020A                      /*当前2象限无功费率9电能*/
#define CQua2_Re_T10_En_0                       0x0060020B                      /*当前2象限无功费率10电能*/
#define CQua2_Re_T11_En_0                       0x0060020C                      /*当前2象限无功费率11电能*/
#define CQua2_Re_T12_En_0                       0x0060020D                      /*当前2象限无功费率12电能*/

#define CQua2_Re_PreEn_FF_0                     0x00600400                      /*当前2象限无功精确电能数据块*/
#define CQua2_Re_Tol_PreEn_0                    0x00600401                      /*当前2象限无功总精确电能*/
#define CQua2_Re_T1_PreEn_0                     0x00600402                      /*当前2象限无功费率1精确电能*/
#define CQua2_Re_T2_PreEn_0                     0x00600403                      /*当前2象限无功费率2精确电能*/
#define CQua2_Re_T3_PreEn_0                     0x00600404                      /*当前2象限无功费率3精确电能*/
#define CQua2_Re_T4_PreEn_0                     0x00600405                      /*当前2象限无功费率4精确电能*/
#define CQua2_Re_T5_PreEn_0                     0x00600406                      /*当前2象限无功费率5精确电能*/
#define CQua2_Re_T6_PreEn_0                     0x00600407                      /*当前2象限无功费率6精确电能*/
#define CQua2_Re_T7_PreEn_0                     0x00600408                      /*当前2象限无功费率7精确电能*/
#define CQua2_Re_T8_PreEn_0                     0x00600409                      /*当前2象限无功费率8精确电能*/
#define CQua2_Re_T9_PreEn_0                     0x0060040A                      /*当前2象限无功费率9精确电能*/
#define CQua2_Re_T10_PreEn_0                    0x0060040B                      /*当前2象限无功费率10精确电能*/
#define CQua2_Re_T11_PreEn_0                    0x0060040C                      /*当前2象限无功费率11精确电能*/
#define CQua2_Re_T12_PreEn_0                    0x0060040D                      /*当前2象限无功费率12精确电能*/

#define CQua2_Re_LastPulse_FF_0                 0x00600600                      /*当前2象限无功脉冲尾数数据块*/
#define CQua2_Re_Tol_LastPulse_0                0x00600601                      /*当前2象限无功总脉冲尾数*/
#define CQua2_Re_T1_LastPulse_0                 0x00600602                      /*当前2象限无功费率1脉冲尾数*/
#define CQua2_Re_T2_LastPulse_0                 0x00600603                      /*当前2象限无功费率2脉冲尾数*/
#define CQua2_Re_T3_LastPulse_0                 0x00600604                      /*当前2象限无功费率3脉冲尾数*/
#define CQua2_Re_T4_LastPulse_0                 0x00600605                      /*当前2象限无功费率4脉冲尾数*/
#define CQua2_Re_T5_LastPulse_0                 0x00600606                      /*当前2象限无功费率5脉冲尾数*/
#define CQua2_Re_T6_LastPulse_0                 0x00600607                      /*当前2象限无功费率6脉冲尾数*/
#define CQua2_Re_T7_LastPulse_0                 0x00600608                      /*当前2象限无功费率7脉冲尾数*/
#define CQua2_Re_T8_LastPulse_0                 0x00600609                      /*当前2象限无功费率8脉冲尾数*/
#define CQua2_Re_T9_LastPulse_0                 0x0060060A                      /*当前2象限无功费率9脉冲尾数*/
#define CQua2_Re_T10_LastPulse_0                0x0060060B                      /*当前2象限无功费率10脉冲尾数*/
#define CQua2_Re_T11_LastPulse_0                0x0060060C                      /*当前2象限无功费率11脉冲尾数*/
#define CQua2_Re_T12_LastPulse_0                0x0060060D                      /*当前2象限无功费率12脉冲尾数*/
/*当前第三象限无功电能*/
#define CQua3_Re_En_FF_0                        0x00700200                      /*当前3象限无功电能数据块*/
#define CQua3_Re_Tol_En_0                       0x00700201                      /*当前3象限无功总电能*/
#define CQua3_Re_T1_En_0                        0x00700202                      /*当前3象限无功费率1电能*/
#define CQua3_Re_T2_En_0                        0x00700203                      /*当前3象限无功费率2电能*/
#define CQua3_Re_T3_En_0                        0x00700204                      /*当前3象限无功费率3电能*/
#define CQua3_Re_T4_En_0                        0x00700205                      /*当前3象限无功费率4电能*/
#define CQua3_Re_T5_En_0                        0x00700206                      /*当前3象限无功费率5电能*/
#define CQua3_Re_T6_En_0                        0x00700207                      /*当前3象限无功费率6电能*/
#define CQua3_Re_T7_En_0                        0x00700208                      /*当前3象限无功费率7电能*/
#define CQua3_Re_T8_En_0                        0x00700209                      /*当前3象限无功费率8电能*/
#define CQua3_Re_T9_En_0                        0x0070020A                      /*当前3象限无功费率9电能*/
#define CQua3_Re_T10_En_0                       0x0070020B                      /*当前3象限无功费率10电能*/
#define CQua3_Re_T11_En_0                       0x0070020C                      /*当前3象限无功费率11电能*/
#define CQua3_Re_T12_En_0                       0x0070020D                      /*当前3象限无功费率12电能*/

#define CQua3_Re_PreEn_FF_0                     0x00700400                      /*当前3象限无功精确电能数据块*/
#define CQua3_Re_Tol_PreEn_0                    0x00700401                      /*当前3象限无功总精确电能*/
#define CQua3_Re_T1_PreEn_0                     0x00700402                      /*当前3象限无功费率1精确电能*/
#define CQua3_Re_T2_PreEn_0                     0x00700403                      /*当前3象限无功费率2精确电能*/
#define CQua3_Re_T3_PreEn_0                     0x00700404                      /*当前3象限无功费率3精确电能*/
#define CQua3_Re_T4_PreEn_0                     0x00700405                      /*当前3象限无功费率4精确电能*/
#define CQua3_Re_T5_PreEn_0                     0x00700406                      /*当前3象限无功费率5精确电能*/
#define CQua3_Re_T6_PreEn_0                     0x00700407                      /*当前3象限无功费率6精确电能*/
#define CQua3_Re_T7_PreEn_0                     0x00700408                      /*当前3象限无功费率7精确电能*/
#define CQua3_Re_T8_PreEn_0                     0x00700409                      /*当前3象限无功费率8精确电能*/
#define CQua3_Re_T9_PreEn_0                     0x0070040A                      /*当前3象限无功费率9精确电能*/
#define CQua3_Re_T10_PreEn_0                    0x0070040B                      /*当前3象限无功费率10精确电能*/
#define CQua3_Re_T11_PreEn_0                    0x0070040C                      /*当前3象限无功费率11精确电能*/
#define CQua3_Re_T12_PreEn_0                    0x0070040D                      /*当前3象限无功费率12精确电能*/

#define CQua3_Re_LastPulse_FF_0                 0x00700600                      /*当前3象限无功脉冲尾数数据块*/
#define CQua3_Re_Tol_LastPulse_0                0x00700601                      /*当前3象限无功总脉冲尾数*/
#define CQua3_Re_T1_LastPulse_0                 0x00700602                      /*当前3象限无功费率1脉冲尾数*/
#define CQua3_Re_T2_LastPulse_0                 0x00700603                      /*当前3象限无功费率2脉冲尾数*/
#define CQua3_Re_T3_LastPulse_0                 0x00700604                      /*当前3象限无功费率3脉冲尾数*/
#define CQua3_Re_T4_LastPulse_0                 0x00700605                      /*当前3象限无功费率4脉冲尾数*/
#define CQua3_Re_T5_LastPulse_0                 0x00700606                      /*当前3象限无功费率5脉冲尾数*/
#define CQua3_Re_T6_LastPulse_0                 0x00700607                      /*当前3象限无功费率6脉冲尾数*/
#define CQua3_Re_T7_LastPulse_0                 0x00700608                      /*当前3象限无功费率7脉冲尾数*/
#define CQua3_Re_T8_LastPulse_0                 0x00700609                      /*当前3象限无功费率8脉冲尾数*/
#define CQua3_Re_T9_LastPulse_0                 0x0070060A                      /*当前3象限无功费率9脉冲尾数*/
#define CQua3_Re_T10_LastPulse_0                0x0070060B                      /*当前3象限无功费率10脉冲尾数*/
#define CQua3_Re_T11_LastPulse_0                0x0070060C                      /*当前3象限无功费率11脉冲尾数*/
#define CQua3_Re_T12_LastPulse_0                0x0070060D                      /*当前3象限无功费率12脉冲尾数*/
/*当前第四象限无功电能*/
#define CQua4_Re_En_FF_0                        0x00800200                      /*当前4象限无功电能数据块*/
#define CQua4_Re_Tol_En_0                       0x00800201                      /*当前4象限无功总电能*/
#define CQua4_Re_T1_En_0                        0x00800202                      /*当前4象限无功费率1电能*/
#define CQua4_Re_T2_En_0                        0x00800203                      /*当前4象限无功费率2电能*/
#define CQua4_Re_T3_En_0                        0x00800204                      /*当前4象限无功费率3电能*/
#define CQua4_Re_T4_En_0                        0x00800205                      /*当前4象限无功费率4电能*/
#define CQua4_Re_T5_En_0                        0x00800206                      /*当前4象限无功费率5电能*/
#define CQua4_Re_T6_En_0                        0x00800207                      /*当前4象限无功费率6电能*/
#define CQua4_Re_T7_En_0                        0x00800208                      /*当前4象限无功费率7电能*/
#define CQua4_Re_T8_En_0                        0x00800209                      /*当前4象限无功费率8电能*/
#define CQua4_Re_T9_En_0                        0x0080020A                      /*当前4象限无功费率9电能*/
#define CQua4_Re_T10_En_0                       0x0080020B                      /*当前4象限无功费率10电能*/
#define CQua4_Re_T11_En_0                       0x0080020C                      /*当前4象限无功费率11电能*/
#define CQua4_Re_T12_En_0                       0x0080020D                      /*当前4象限无功费率12电能*/

#define CQua4_Re_PreEn_FF_0                     0x00800400                      /*当前4象限无功精确电能数据块*/
#define CQua4_Re_Tol_PreEn_0                    0x00800401                      /*当前4象限无功总精确电能*/
#define CQua4_Re_T1_PreEn_0                     0x00800402                      /*当前4象限无功费率1精确电能*/
#define CQua4_Re_T2_PreEn_0                     0x00800403                      /*当前4象限无功费率2精确电能*/
#define CQua4_Re_T3_PreEn_0                     0x00800404                      /*当前4象限无功费率3精确电能*/
#define CQua4_Re_T4_PreEn_0                     0x00800405                      /*当前4象限无功费率4精确电能*/
#define CQua4_Re_T5_PreEn_0                     0x00800406                      /*当前4象限无功费率5精确电能*/
#define CQua4_Re_T6_PreEn_0                     0x00800407                      /*当前4象限无功费率6精确电能*/
#define CQua4_Re_T7_PreEn_0                     0x00800408                      /*当前4象限无功费率7精确电能*/
#define CQua4_Re_T8_PreEn_0                     0x00800409                      /*当前4象限无功费率8精确电能*/
#define CQua4_Re_T9_PreEn_0                     0x0080040A                      /*当前4象限无功费率9精确电能*/
#define CQua4_Re_T10_PreEn_0                    0x0080040B                      /*当前4象限无功费率10精确电能*/
#define CQua4_Re_T11_PreEn_0                    0x0080040C                      /*当前4象限无功费率11精确电能*/
#define CQua4_Re_T12_PreEn_0                    0x0080040D                      /*当前4象限无功费率12精确电能*/

#define CQua4_Re_LastPulse_FF_0                 0x00800600                      /*当前4象限无功脉冲尾数数据块*/
#define CQua4_Re_Tol_LastPulse_0                0x00800601                      /*当前4象限无功总脉冲尾数*/
#define CQua4_Re_T1_LastPulse_0                 0x00800602                      /*当前4象限无功费率1脉冲尾数*/
#define CQua4_Re_T2_LastPulse_0                 0x00800603                      /*当前4象限无功费率2脉冲尾数*/
#define CQua4_Re_T3_LastPulse_0                 0x00800604                      /*当前4象限无功费率3脉冲尾数*/
#define CQua4_Re_T4_LastPulse_0                 0x00800605                      /*当前4象限无功费率4脉冲尾数*/
#define CQua4_Re_T5_LastPulse_0                 0x00800606                      /*当前4象限无功费率5脉冲尾数*/
#define CQua4_Re_T6_LastPulse_0                 0x00800607                      /*当前4象限无功费率6脉冲尾数*/
#define CQua4_Re_T7_LastPulse_0                 0x00800608                      /*当前4象限无功费率7脉冲尾数*/
#define CQua4_Re_T8_LastPulse_0                 0x00800609                      /*当前4象限无功费率8脉冲尾数*/
#define CQua4_Re_T9_LastPulse_0                 0x0080060A                      /*当前4象限无功费率9脉冲尾数*/
#define CQua4_Re_T10_LastPulse_0                0x0080060B                      /*当前4象限无功费率10脉冲尾数*/
#define CQua4_Re_T11_LastPulse_0                0x0080060C                      /*当前4象限无功费率11脉冲尾数*/
#define CQua4_Re_T12_LastPulse_0                0x0080060D                      /*当前4象限无功费率12脉冲尾数*/
/*当前A 相正向有功电能*/
#define CPosA_Ac_En_0                           0x00110201                      /*当前A相正向有功电能*/
#define C_Fre_APosAcPreEn                       0x00110400                      /*A相正向有功精确电能*/
#define CPosA_Ac_PreEn_0                        0x00110401                      /*当前A相正向有功精确电能*/
#define C_Fre_APosAcLastPulse                   0x00110600                      /*A相正向有功脉冲尾数*/
#define CPosA_Ac_LastPulse_0                    0x00110601                      /*当前A相正向有功脉冲尾数*/
/*当前A 相反向有功电能*/
#define CRevA_Ac_En_0                           0x00210201                      /*当前A相反向有功电能*/
#define CRevA_Ac_PreEn_0                        0x00210401                      /*当前A相反向有功精确电能*/
#define C_Fre_ARevAcPreEn                       0x00210400                      /*A相反向有功精确电能*/
#define C_Fre_ARevAcLastPulse                   0x00210600                      /*A相反向有功脉冲尾数*/
#define CRevA_Ac_LastPulse_0                    0x00210601                      /*当前A相反向有功脉冲尾数*/
/*当前A 相组合无功 1 电能*/
#define CComA_Re1_En_0                          0x00310201                      /*当前A相组合无功1电能*/
#define C_Fre_AComRe1PreEn                      0x00310400                      /*A相组合无功1总精确电能*/
#define CComA_Re1_PreEn_0                       0x00310401                      /*当前A相组合无功1精确电能*/
#define C_Fre_AComRe1LastPulse                  0x00310600                      /*A相组合无功1总脉冲尾数*/
#define CComA_Re1_LastPulse_0                   0x00310601                      /*当前A相组合无功1脉冲尾数*/
/*当前A 相组合无功 2 电能*/
#define CComA_Re2_En_0                          0x00410201                      /*当前A相组合无功2电能*/
#define C_Fre_AComRe2PreEn                      0x00410400                      /*A相组合无功2总精确电能*/
#define CComA_Re2_PreEn_0                       0x00410401                      /*当前A相组合无功2精确电能*/
#define C_Fre_AComRe2LastPulse                  0x00410600                      /*A相组合无功2总脉冲尾数*/
#define CComA_Re2_LastPulse_0                   0x00410601                      /*当前A相组合无功2脉冲尾数*/
/*当前A 相第一象限无功电能*/
#define CQua1A_Re_En_0                          0x00510201                      /*当前A相1象限无功电能*/
#define C_Fre_AQuadrant1PreEn                   0x00510400                      /*A相第一象限无功总精确电能*/
#define CQua1A_Re_PreEn_0                       0x00510401                      /*当前A相1象限无功精确电能*/
#define C_Fre_AQuadrant1LastPulse               0x00510600                      /*A相第一象限无功总脉冲尾数*/
#define CQua1A_Re_LastPulse_0                   0x00510601                      /*当前A相1象限无功脉冲尾数*/
/*当前A 相第二象限无功电能*/
#define CQua2A_Re_En_0                          0x00610201                      /*当前A相2象限无功电能*/
#define C_Fre_AQuadrant2PreEn                   0x00610400                      /*A相第二象限无功总精确电能*/
#define CQua2A_Re_PreEn_0                       0x00610401                      /*当前A相2象限无功精确电能*/
#define C_Fre_AQuadrant2LastPulse               0x00610600                      /*A相第二象限无功总脉冲尾数*/
#define CQua2A_Re_LastPulse_0                   0x00610601                      /*当前A相2象限无功脉冲尾数*/
/*当前A 相第三象限无功电能*/
#define CQua3A_Re_En_0                          0x00710201                      /*当前A相3象限无功电能*/
#define C_Fre_AQuadrant3PreEn                   0x00710400                      /*A相第三象限无功总精确电能*/
#define CQua3A_Re_PreEn_0                       0x00710401                      /*当前A相3象限无功精确电能*/
#define C_Fre_AQuadrant3LastPulse               0x00710600                      /*A相第三象限无功总脉冲尾数*/
#define CQua3A_Re_LastPulse_0                   0x00710601                      /*当前A相3象限无功脉冲尾数*/
/*当前A 相第四象限无功电能*/
#define CQua4A_Re_En_0                          0x00810201                      /*当前A相4象限无功电能*/
#define C_Fre_AQuadrant4PreEn                   0x00810400                      /*A相第四象限无功总精确电能*/
#define CQua4A_Re_PreEn_0                       0x00810401                      /*当前A相4象限无功精确电能*/
#define C_Fre_AQuadrant4LastPulse               0x00810600                      /*A相第四象限无功总脉冲尾数*/
#define CQua4A_Re_LastPulse_0                   0x00810601                      /*当前A相4象限无功脉冲尾数*/
/*当前B 相正向有功电能*/
#define CPosB_Ac_En_0                           0x00120201                      /*当前B相正向有功电能*/
#define C_Fre_BPosAcPreEn                       0x00120400                      /*B相正向有功精确电能*/
#define CPosB_Ac_PreEn_0                        0x00120401                      /*当前B相正向有功精确电能*/
#define C_Fre_BPosAcLastPulse                   0x00120600                      /*B相正向有功脉冲尾数*/
#define CPosB_Ac_LastPulse_0                    0x00120601                      /*当前B相正向有功脉冲尾数*/
/*当前B 相反向有功电能*/
#define CRevB_Ac_En_0                           0x00220201                      /*当前B相反向有功电能*/
#define C_Fre_BRevAcPreEn                       0x00220400                      /*B相反向有功精确电能*/
#define CRevB_Ac_PreEn_0                        0x00220401                      /*当前B相反向有功精确电能*/
#define C_Fre_BRevAcLastPulse                   0x00220600                      /*B相反向有功脉冲尾数*/
#define CRevB_Ac_LastPulse_0                    0x00220601                      /*当前B相反向有功脉冲尾数*/
/*当前B 相组合无功 1 电能*/
#define CComB_Re1_En_0                          0x00320201                      /*当前B相组合无功1电能*/
#define C_Fre_BComRe1PreEn                      0x00320400                      /*B相组合无功1总精确电能*/
#define CComB_Re1_PreEn_0                       0x00320401                      /*当前B相组合无功1精确电能*/
#define C_Fre_BComRe1LastPulse                  0x00320600                      /*B相组合无功1总脉冲尾数*/
#define CComB_Re1_LastPulse_0                   0x00320601                      /*当前B相组合无功1脉冲尾数*/
/*当前B 相组合无功 2 电能*/
#define CComB_Re2_En_0                          0x00420201                      /*当前B相组合无功2电能*/
#define C_Fre_BComRe2PreEn                      0x00420400                      /*B相组合无功2总精确电能*/
#define CComB_Re2_PreEn_0                       0x00420401                      /*当前B相组合无功2精确电能*/
#define C_Fre_BComRe2LastPulse                  0x00420600                      /*B相组合无功2总脉冲尾数*/
#define CComB_Re2_LastPulse_0                   0x00420601                      /*当前B相组合无功2脉冲尾数*/
/*当前B 相第一象限无功电能*/
#define CQua1B_Re_En_0                          0x00520201                      /*当前B相1象限无功电能*/
#define C_Fre_BQuadrant1PreEn                   0x00520400                      /*B相第一象限无功总精确电能*/
#define CQua1B_Re_PreEn_0                       0x00520401                      /*当前B相1象限无功精确电能*/
#define C_Fre_BQuadrant1LastPulse               0x00520600                      /*B相第一象限无功总脉冲尾数*/
#define CQua1B_Re_LastPulse_0                   0x00520601                      /*当前B相1象限无功脉冲尾数*/
/*当前B 相第二象限无功电能*/
#define CQua2B_Re_En_0                          0x00620201                      /*当前B相2象限无功电能*/
#define C_Fre_BQuadrant2PreEn                   0x00620400                      /*B相第二象限无功总精确电能*/
#define CQua2B_Re_PreEn_0                       0x00620401                      /*当前B相2象限无功精确电能*/
#define C_Fre_BQuadrant2LastPulse               0x00620600                      /*B相第二象限无功总脉冲尾数*/
#define CQua2B_Re_LastPulse_0                   0x00620601                      /*当前B相2象限无功脉冲尾数*/
/*当前B 相第三象限无功电能*/
#define CQua3B_Re_En_0                          0x00720201                      /*当前B相3象限无功电能*/
#define C_Fre_BQuadrant3PreEn                   0x00720400                      /*B相第三象限无功总精确电能*/
#define CQua3B_Re_PreEn_0                       0x00720401                      /*当前B相3象限无功精确电能*/
#define C_Fre_BQuadrant3LastPulse               0x00720600                      /*B相第三象限无功总脉冲尾数*/
#define CQua3B_Re_LastPulse_0                   0x00720601                      /*当前B相3象限无功脉冲尾数*/
/*当前B 相第四象限无功电能*/
#define CQua4B_Re_En_0                          0x00820201                      /*当前B相4象限无功电能*/
#define C_Fre_BQuadrant4PreEn                   0x00820400                      /*B相第四象限无功总精确电能*/
#define CQua4B_Re_PreEn_0                       0x00820401                      /*当前B相4象限无功精确电能*/
#define C_Fre_BQuadrant4LastPulse               0x00820600                      /*B相第四象限无功总脉冲尾数*/
#define CQua4B_Re_LastPulse_0                   0x00820601                      /*当前B相4象限无功脉冲尾数*/
/*当前C 相正向有功电能*/
#define CPosC_Ac_En_0                           0x00130201                      /*当前C相正向有功电能*/
#define C_Fre_CPosAcPreEn                       0x00130400                      /*C相正向有功精确电能*/
#define CPosC_Ac_PreEn_0                        0x00130401                      /*当前C相正向有功精确电能*/
#define C_Fre_CPosAcLastPulse                   0x00130600                      /*C相正向有功脉冲尾数*/
#define CPosC_Ac_LastPulse_0                    0x00130601                      /*当前C相正向有功脉冲尾数*/
/*当前C 相反向有功电能*/
#define CRevC_Ac_En_0                           0x00230201                      /*当前C相反向有功电能*/
#define C_Fre_CRevAcPreEn                       0x00230400                      /*C相反向有功精确电能*/
#define CRevC_Ac_PreEn_0                        0x00230401                      /*当前C相反向有功精确电能*/
#define C_Fre_CRevAcLastPulse                   0x00230600                      /*C相反向有功脉冲尾数*/
#define CRevC_Ac_LastPulse_0                    0x00230601                      /*当前C相反向有功脉冲尾数*/
/*当前C 相组合无功 1 电能*/
#define CComC_Re1_En_0                          0x00330201                      /*当前C相组合无功1电能*/
#define C_Fre_CComRe1PreEn                      0x00330400                      /*C相组合无功1总精确电能*/
#define CComC_Re1_PreEn_0                       0x00330401                      /*当前C相组合无功1精确电能*/
#define C_Fre_CComRe1LastPulse                  0x00330600                      /*C相组合无功1总脉冲尾数*/
#define CComC_Re1_LastPulse_0                   0x00330601                      /*当前C相组合无功1脉冲尾数*/
/*当前C 相组合无功 2 电能*/
#define CComC_Re2_En_0                          0x00430201                      /*当前C相组合无功2电能*/
#define C_Fre_CComRe2PreEn                      0x00430400                      /*C相组合无功2总精确电能*/
#define CComC_Re2_PreEn_0                       0x00430401                      /*当前C相组合无功2精确电能*/
#define C_Fre_CComRe2LastPulse                  0x00430600                      /*C相组合无功2总脉冲尾数*/
#define CComC_Re2_LastPulse_0                   0x00430601                      /*当前C相组合无功2脉冲尾数*/
/*当前C 相第一象限无功电能*/
#define CQua1C_Re_En_0                          0x00530201                      /*当前C相1象限无功电能*/
#define C_Fre_CQuadrant1PreEn                   0x00530400                      /*C相第一象限无功总精确电能*/
#define CQua1C_Re_PreEn_0                       0x00530401                      /*当前C相1象限无功精确电能*/
#define C_Fre_CQuadrant1LastPulse               0x00530600                      /*C相第一象限无功总脉冲尾数*/
#define CQua1C_Re_LastPulse_0                   0x00530601                      /*当前C相1象限无功脉冲尾数*/
/*当前C 相第二象限无功电能*/
#define CQua2C_Re_En_0                          0x00630201                      /*当前C相2象限无功电能*/
#define C_Fre_CQuadrant2PreEn                   0x00630400                      /*C相第二象限无功总精确电能*/
#define CQua2C_Re_PreEn_0                       0x00630401                      /*当前C相2象限无功精确电能*/
#define C_Fre_CQuadrant2LastPulse               0x00630600                      /*C相第二象限无功总脉冲尾数*/
#define CQua2C_Re_LastPulse_0                   0x00630601                      /*当前C相2象限无功脉冲尾数*/
/*当前C相第三象限无功电能*/
#define CQua3C_Re_En_0                          0x00730201                      /*当前C相3象限无功电能*/
#define C_Fre_CQuadrant3PreEn                   0x00730400                      /*C相第三象限无功总精确电能*/
#define CQua3C_Re_PreEn_0                       0x00730401                      /*当前C相3象限无功精确电能*/
#define C_Fre_CQuadrant3LastPulse               0x00730600                      /*C相第三象限无功总脉冲尾数*/
#define CQua3C_Re_LastPulse_0                   0x00730601                      /*当前C相3象限无功脉冲尾数*/
/*当前C 相第四象限无功电能*/
#define CQua4C_Re_En_0                          0x00830201                      /*当前C相4象限无功电能*/
#define C_Fre_CQuadrant4PreEn                   0x00830400                      /*C相第四象限无功总精确电能*/
#define CQua4C_Re_PreEn_0                       0x00830401                      /*当前C相4象限无功精确电能*/
#define C_Fre_CQuadrant4LastPulse               0x00830600                      /*C相第四象限无功总脉冲尾数*/
#define CQua4C_Re_LastPulse_0                   0x00830601                      /*当前C相4象限无功脉冲尾数*/

/******************************最大需量类对象******************************/
/*正向有功最大需量*/
#define CPos_Ac_De_FF_0                         0x10100200                      /*当前正向有功最大需量及发生时刻数据块*/
#define CPos_Ac_Tol_De_0                        0x10100201                      /*当前正向有功总最大需量及发生时刻*/
#define CPos_Ac_T1_De_0                         0x10100202                      /*当前正向有功费率1最大需量及发生时刻*/
#define CPos_Ac_T2_De_0                         0x10100203                      /*当前正向有功费率2最大需量及发生时刻*/
#define CPos_Ac_T3_De_0                         0x10100204                      /*当前正向有功费率3最大需量及发生时刻*/
#define CPos_Ac_T4_De_0                         0x10100205                      /*当前正向有功费率4最大需量及发生时刻*/
#define CPos_Ac_T5_De_0                         0x10100206                      /*当前正向有功费率5最大需量及发生时刻*/
#define CPos_Ac_T6_De_0                         0x10100207                      /*当前正向有功费率6最大需量及发生时刻*/
#define CPos_Ac_T7_De_0                         0x10100208                      /*当前正向有功费率7最大需量及发生时刻*/
#define CPos_Ac_T8_De_0                         0x10100209                      /*当前正向有功费率8最大需量及发生时刻*/
#define CPos_Ac_T9_De_0                         0x1010020A                      /*当前正向有功费率9最大需量及发生时刻*/
#define CPos_Ac_T10_De_0                        0x1010020B                      /*当前正向有功费率10最大需量及发生时刻*/
#define CPos_Ac_T11_De_0                        0x1010020C                      /*当前正向有功费率11最大需量及发生时刻*/
#define CPos_Ac_T12_De_0                        0x1010020D                      /*当前正向有功费率12最大需量及发生时刻*/
/*反向有功最大需量*/
#define CRev_Ac_De_FF_0                         0x10200200                      /*当前反向有功最大需量及发生时刻数据块*/
#define CRev_Ac_Tol_De_0                        0x10200201                      /*当前反向有功总最大需量及发生时刻*/
#define CRev_Ac_T1_De_0                         0x10200202                      /*当前反向有功费率1最大需量及发生时刻*/
#define CRev_Ac_T2_De_0                         0x10200203                      /*当前反向有功费率2最大需量及发生时刻*/
#define CRev_Ac_T3_De_0                         0x10200204                      /*当前反向有功费率3最大需量及发生时刻*/
#define CRev_Ac_T4_De_0                         0x10200205                      /*当前反向有功费率4最大需量及发生时刻*/
#define CRev_Ac_T5_De_0                         0x10200206                      /*当前反向有功费率5最大需量及发生时刻*/
#define CRev_Ac_T6_De_0                         0x10200207                      /*当前反向有功费率6最大需量及发生时刻*/
#define CRev_Ac_T7_De_0                         0x10200208                      /*当前反向有功费率7最大需量及发生时刻*/
#define CRev_Ac_T8_De_0                         0x10200209                      /*当前反向有功费率8最大需量及发生时刻*/
#define CRev_Ac_T9_De_0                         0x1020020A                      /*当前反向有功费率9最大需量及发生时刻*/
#define CRev_Ac_T10_De_0                        0x1020020B                      /*当前反向有功费率10最大需量及发生时刻*/
#define CRev_Ac_T11_De_0                        0x1020020C                      /*当前反向有功费率11最大需量及发生时刻*/
#define CRev_Ac_T12_De_0                        0x1020020D                      /*当前反向有功费率12最大需量及发生时刻*/
/*组合无功 1 最大需量*/
#define CCom_Re1_De_FF_0                        0x10300200                      /*当前组合无功1最大需量及发生时刻数据块*/
#define CCom_Re1_Tol_De_0                       0x10300201                      /*当前组合无功1总最大需量及发生时刻*/
#define CCom_Re1_T1_De_0                        0x10300202                      /*当前组合无功1费率1最大需量及发生时刻*/
#define CCom_Re1_T2_De_0                        0x10300203                      /*当前组合无功1费率2最大需量及发生时刻*/
#define CCom_Re1_T3_De_0                        0x10300204                      /*当前组合无功1费率3最大需量及发生时刻*/
#define CCom_Re1_T4_De_0                        0x10300205                      /*当前组合无功1费率4最大需量及发生时刻*/
#define CCom_Re1_T5_De_0                        0x10300206                      /*当前组合无功1费率5最大需量及发生时刻*/
#define CCom_Re1_T6_De_0                        0x10300207                      /*当前组合无功1费率6最大需量及发生时刻*/
#define CCom_Re1_T7_De_0                        0x10300208                      /*当前组合无功1费率7最大需量及发生时刻*/
#define CCom_Re1_T8_De_0                        0x10300209                      /*当前组合无功1费率8最大需量及发生时刻*/
#define CCom_Re1_T9_De_0                        0x1030020A                      /*当前组合无功1费率9最大需量及发生时刻*/
#define CCom_Re1_T10_De_0                       0x1030020B                      /*当前组合无功1费率10最大需量及发生时刻*/
#define CCom_Re1_T11_De_0                       0x1030020C                      /*当前组合无功1费率11最大需量及发生时刻*/
#define CCom_Re1_T12_De_0                       0x1030020D                      /*当前组合无功1费率12最大需量及发生时刻*/
/*组合无功 2 最大需量*/
#define CCom_Re2_Tol_De_0                       0x10400201                      /*当前组合无功2总最大需量及发生时刻*/
#define CCom_Re2_T1_De_0                        0x10400202                      /*当前组合无功2费率1最大需量及发生时刻*/
#define CCom_Re2_T2_De_0                        0x10400203                      /*当前组合无功2费率2最大需量及发生时刻*/
#define CCom_Re2_T3_De_0                        0x10400204                      /*当前组合无功2费率3最大需量及发生时刻*/
#define CCom_Re2_T4_De_0                        0x10400205                      /*当前组合无功2费率4最大需量及发生时刻*/
#define CCom_Re2_T5_De_0                        0x10400206                      /*当前组合无功2费率5最大需量及发生时刻*/
#define CCom_Re2_T6_De_0                        0x10400207                      /*当前组合无功2费率6最大需量及发生时刻*/
#define CCom_Re2_T7_De_0                        0x10400208                      /*当前组合无功2费率7最大需量及发生时刻*/
#define CCom_Re2_T8_De_0                        0x10400209                      /*当前组合无功2费率8最大需量及发生时刻*/
#define CCom_Re2_T9_De_0                        0x1040020A                      /*当前组合无功2费率9最大需量及发生时刻*/
#define CCom_Re2_T10_De_0                       0x1040020B                      /*当前组合无功2费率10最大需量及发生时刻*/
#define CCom_Re2_T11_De_0                       0x1040020C                      /*当前组合无功2费率11最大需量及发生时刻*/
#define CCom_Re2_T12_De_0                       0x1040020D                      /*当前组合无功2费率12最大需量及发生时刻*/
#define CCom_Re2_De_FF_0                        0x10400200                      /*当前组合无功2最大需量及发生时刻数据块*/
/*第一象限最大需量*/
#define CQua1_Re_De_FF_0                        0x10500200                      /*当前1象限无功最大需量及发生时刻数据块*/
#define CQua1_Re_Tol_De_0                       0x10500201                      /*当前1象限无功总最大需量及发生时刻*/
#define CQua1_Re_T1_De_0                        0x10500202                      /*当前1象限无功费率1最大需量及发生时刻*/
#define CQua1_Re_T2_De_0                        0x10500203                      /*当前1象限无功费率2最大需量及发生时刻*/
#define CQua1_Re_T3_De_0                        0x10500204                      /*当前1象限无功费率3最大需量及发生时刻*/
#define CQua1_Re_T4_De_0                        0x10500205                      /*当前1象限无功费率4最大需量及发生时刻*/
#define CQua1_Re_T5_De_0                        0x10500206                      /*当前1象限无功费率5最大需量及发生时刻*/
#define CQua1_Re_T6_De_0                        0x10500207                      /*当前1象限无功费率6最大需量及发生时刻*/
#define CQua1_Re_T7_De_0                        0x10500208                      /*当前1象限无功费率7最大需量及发生时刻*/
#define CQua1_Re_T8_De_0                        0x10500209                      /*当前1象限无功费率8最大需量及发生时刻*/
#define CQua1_Re_T9_De_0                        0x1050020A                      /*当前1象限无功费率9最大需量及发生时刻*/
#define CQua1_Re_T10_De_0                       0x1050020B                      /*当前1象限无功费率10最大需量及发生时刻*/
#define CQua1_Re_T11_De_0                       0x1050020C                      /*当前1象限无功费率11最大需量及发生时刻*/
#define CQua1_Re_T12_De_0                       0x1050020D                      /*当前1象限无功费率12最大需量及发生时刻*/
/*第二象限最大需量*/
#define CQua2_Re_De_FF_0                        0x10600200                      /*当前2象限无功最大需量及发生时刻数据块*/
#define CQua2_Re_Tol_De_0                       0x10600201                      /*当前2象限无功总最大需量及发生时刻*/
#define CQua2_Re_T1_De_0                        0x10600202                      /*当前2象限无功费率1最大需量及发生时刻*/
#define CQua2_Re_T2_De_0                        0x10600203                      /*当前2象限无功费率2最大需量及发生时刻*/
#define CQua2_Re_T3_De_0                        0x10600204                      /*当前2象限无功费率3最大需量及发生时刻*/
#define CQua2_Re_T4_De_0                        0x10600205                      /*当前2象限无功费率4最大需量及发生时刻*/
#define CQua2_Re_T5_De_0                        0x10600206                      /*当前2象限无功费率5最大需量及发生时刻*/
#define CQua2_Re_T6_De_0                        0x10600207                      /*当前2象限无功费率6最大需量及发生时刻*/
#define CQua2_Re_T7_De_0                        0x10600208                      /*当前2象限无功费率7最大需量及发生时刻*/
#define CQua2_Re_T8_De_0                        0x10600209                      /*当前2象限无功费率8最大需量及发生时刻*/
#define CQua2_Re_T9_De_0                        0x1060020A                      /*当前2象限无功费率9最大需量及发生时刻*/
#define CQua2_Re_T10_De_0                       0x1060020B                      /*当前2象限无功费率10最大需量及发生时刻*/
#define CQua2_Re_T11_De_0                       0x1060020C                      /*当前2象限无功费率11最大需量及发生时刻*/
#define CQua2_Re_T12_De_0                       0x1060020D                      /*当前2象限无功费率12最大需量及发生时刻*/
/*第三象限最大需量*/
#define CQua3_Re_De_FF_0                        0x10700200                      /*当前3象限无功最大需量及发生时刻数据块*/
#define CQua3_Re_Tol_De_0                       0x10700201                      /*当前3象限无功总最大需量及发生时刻*/
#define CQua3_Re_T1_De_0                        0x10700202                      /*当前3象限无功费率1最大需量及发生时刻*/
#define CQua3_Re_T2_De_0                        0x10700203                      /*当前3象限无功费率2最大需量及发生时刻*/
#define CQua3_Re_T3_De_0                        0x10700204                      /*当前3象限无功费率3最大需量及发生时刻*/
#define CQua3_Re_T4_De_0                        0x10700205                      /*当前3象限无功费率4最大需量及发生时刻*/
#define CQua3_Re_T5_De_0                        0x10700206                      /*当前3象限无功费率5最大需量及发生时刻*/
#define CQua3_Re_T6_De_0                        0x10700207                      /*当前3象限无功费率6最大需量及发生时刻*/
#define CQua3_Re_T7_De_0                        0x10700208                      /*当前3象限无功费率7最大需量及发生时刻*/
#define CQua3_Re_T8_De_0                        0x10700209                      /*当前3象限无功费率8最大需量及发生时刻*/
#define CQua3_Re_T9_De_0                        0x1070020A                      /*当前3象限无功费率9最大需量及发生时刻*/
#define CQua3_Re_T10_De_0                       0x1070020B                      /*当前3象限无功费率10最大需量及发生时刻*/
#define CQua3_Re_T11_De_0                       0x1070020C                      /*当前3象限无功费率11最大需量及发生时刻*/
#define CQua3_Re_T12_De_0                       0x1070020D                      /*当前3象限无功费率12最大需量及发生时刻*/
/*第四象限最大需量*/
#define CQua4_Re_De_FF_0                        0x10800200                      /*当前4象限无功最大需量及发生时刻数据块*/
#define CQua4_Re_Tol_De_0                       0x10800201                      /*当前4象限无功总最大需量及发生时刻*/
#define CQua4_Re_T1_De_0                        0x10800202                      /*当前4象限无功费率1最大需量及发生时刻*/
#define CQua4_Re_T2_De_0                        0x10800203                      /*当前4象限无功费率2最大需量及发生时刻*/
#define CQua4_Re_T3_De_0                        0x10800204                      /*当前4象限无功费率3最大需量及发生时刻*/
#define CQua4_Re_T4_De_0                        0x10800205                      /*当前4象限无功费率4最大需量及发生时刻*/
#define CQua4_Re_T5_De_0                        0x10800206                      /*当前4象限无功费率5最大需量及发生时刻*/
#define CQua4_Re_T6_De_0                        0x10800207                      /*当前4象限无功费率6最大需量及发生时刻*/
#define CQua4_Re_T7_De_0                        0x10800208                      /*当前4象限无功费率7最大需量及发生时刻*/
#define CQua4_Re_T8_De_0                        0x10800209                      /*当前4象限无功费率8最大需量及发生时刻*/
#define CQua4_Re_T9_De_0                        0x1080020A                      /*当前4象限无功费率9最大需量及发生时刻*/
#define CQua4_Re_T10_De_0                       0x1080020B                      /*当前4象限无功费率10最大需量及发生时刻*/
#define CQua4_Re_T11_De_0                       0x1080020C                      /*当前4象限无功费率11最大需量及发生时刻*/
#define CQua4_Re_T12_De_0                       0x1080020D                      /*当前4象限无功费率12最大需量及发生时刻*/
/*A 相正向有功最大需量*/
#define CPosA_Ac_De_FF_0                        0x10110200                      /*当前A相正向有功最大需量及发生时刻数据块*/
#define CPosA_Ac_De_0                           0x10110201                      /*当前A相正向有功最大需量及发生时刻*/
#define CRevA_Ac_De_0                           0x10210201                      /*当前A相反向有功最大需量及发生时刻*/
#define CComA_Re1_De_FF_0                       0x10310200                      /*当前A相组合无功1最大需量及发生时刻*/
#define CComA_Re1_De_0                          0x10310201                      /*当前A相组合无功1最大需量及发生时刻*/
#define CComA_Re2_De_FF_0                       0x10410200                      /*当前A相组合无功2最大需量及发生时刻*/
#define CComA_Re2_De_0                          0x10410201                      /*当前A相组合无功2最大需量及发生时刻*/
#define CQua1A_Re_De_FF_0                       0x10510200                      /*当前A相1象限无功最大需量及发生时刻*/
#define CQua1A_Re_De_0                          0x10510201                      /*当前A相1象限无功最大需量及发生时刻*/
#define CQua2A_Re_De_0                          0x10610201                      /*当前A相2象限无功最大需量及发生时刻*/
#define CQua3A_Re_De_0                          0x10710201                      /*当前A相3象限无功最大需量及发生时刻*/
#define CQua4A_Re_De_0                          0x10810201                      /*当前A相4象限无功最大需量及发生时刻*/
/*B 相正向有功最大需量*/
#define CPosB_Ac_De_FF_0                        0x10120200                      /*当前B相正向有功最大需量及发生时刻数据块*/
#define CPosB_Ac_De_0                           0x10120201                      /*当前B相正向有功最大需量及发生时刻*/
#define CRevB_Ac_De_0                           0x10220201                      /*当前B相反向有功最大需量及发生时刻*/
#define CComB_Re1_De_FF_0                       0x10320200                      /*当前B相组合无功1最大需量及发生时刻*/
#define CComB_Re1_De_0                          0x10320201                      /*当前B相组合无功1最大需量及发生时刻*/
#define CComB_Re2_De_FF_0                       0x10420200                      /*当前B相组合无功2最大需量及发生时刻*/
#define CComB_Re2_De_0                          0x10420201                      /*当前B相组合无功2最大需量及发生时刻*/
#define CQua1B_Re_De_FF_0                       0x10520200                      /*当前B相1象限无功最大需量及发生时刻*/
#define CQua1B_Re_De_0                          0x10520201                      /*当前B相1象限无功最大需量及发生时刻*/
#define CQua2B_Re_De_0                          0x10620201                      /*当前B相2象限无功最大需量及发生时刻*/
#define CQua3B_Re_De_0                          0x10720201                      /*当前B相3象限无功最大需量及发生时刻*/
#define CQua4B_Re_De_0                          0x10820201                      /*当前B相4象限无功最大需量及发生时刻*/
/*C 相正向有功最大需量*/
#define CPosC_Ac_De_FF_0                        0x10130200                      /*当前C相正向有功最大需量及发生时刻数据块*/
#define CPosC_Ac_De_0                           0x10130201                      /*当前C相正向有功最大需量及发生时刻*/
#define CRevC_Ac_De_0                           0x10230201                      /*当前C相反向有功最大需量及发生时刻*/
#define CComC_Re1_De_FF_0                       0x10330200                      /*当前C相组合无功1最大需量及发生时刻*/
#define CComC_Re1_De_0                          0x10330201                      /*当前C相组合无功1最大需量及发生时刻*/
#define CComC_Re2_De_FF_0                       0x10430200                      /*当前C相组合无功2最大需量及发生时刻*/
#define CComC_Re2_De_0                          0x10430201                      /*当前C相组合无功2最大需量及发生时刻*/
#define CQua1C_Re_De_FF_0                       0x10530200                      /*当前C相1象限无功最大需量及发生时刻*/
#define CQua1C_Re_De_0                          0x10530201                      /*当前C相1象限无功最大需量及发生时刻*/
#define CQua2C_Re_De_0                          0x10630201                      /*当前C相2象限无功最大需量及发生时刻*/
#define CQua3C_Re_De_0                          0x10730201                      /*当前C相3象限无功最大需量及发生时刻*/
#define CQua4C_Re_De_0                          0x10830201                      /*当前C相4象限无功最大需量及发生时刻*/
/*冻结周期内正向有功最大需量*/
#define CPos_Ac_De_FF_1                         0x11100200                      /*(上1结算日)正向有功最大需量及发生时刻数据块*/
#define CPos_Ac_Tol_De_1                        0x11100201                      /*(上1结算日)正向有功总最大需量及发生时刻*/
#define CPos_Ac_T1_De_1                         0x11100202                      /*(上1结算日)正向有功费率1最大需量及发生时刻*/
#define CPos_Ac_T2_De_1                         0x11100203                      /*(上1结算日)正向有功费率2最大需量及发生时刻*/
#define CPos_Ac_T3_De_1                         0x11100204                      /*(上1结算日)正向有功费率3最大需量及发生时刻*/
#define CPos_Ac_T4_De_1                         0x11100205                      /*(上1结算日)正向有功费率4最大需量及发生时刻*/
/*冻结周期内反向有功最大需量*/
#define CRev_Ac_De_FF_1                         0x11200200                      /*(上1结算日)反向有功最大需量及发生时刻数据块*/
#define CRev_Ac_Tol_De_1                        0x11200201                      /*(上1结算日)反向有功总最大需量及发生时刻*/
#define CRev_Ac_T1_De_1                         0x11200202                      /*(上1结算日)反向有功费率1最大需量及发生时刻*/
#define CRev_Ac_T2_De_1                         0x11200203                      /*(上1结算日)反向有功费率2最大需量及发生时刻*/
#define CRev_Ac_T3_De_1                         0x11200204                      /*(上1结算日)反向有功费率3最大需量及发生时刻*/
#define CRev_Ac_T4_De_1                         0x11200205                      /*(上1结算日)反向有功费率4最大需量及发生时刻*/
/*冻结周期内组合无功 1 最大需量*/
#define CCom_Re1_De_FF_1                        0x11300200                      /*(上1结算日)组合无功1最大需量及发生时刻数据块*/
#define CCom_Re1_Tol_De_1                       0x11300201                      /*(上1结算日)组合无功1总最大需量及发生时刻*/
#define CCom_Re1_T1_De_1                        0x11300202                      /*(上1结算日)组合无功1费率1最大需量及发生时刻*/
#define CCom_Re1_T2_De_1                        0x11300203                      /*(上1结算日)组合无功1费率2最大需量及发生时刻*/
#define CCom_Re1_T3_De_1                        0x11300204                      /*(上1结算日)组合无功1费率3最大需量及发生时刻*/
#define CCom_Re1_T4_De_1                        0x11300205                      /*(上1结算日)组合无功1费率4最大需量及发生时刻*/
/*冻结周期内组合无功 2 最大需量*/
#define CCom_Re2_De_FF_1                        0x11400200                      /*(上1结算日)组合无功2最大需量及发生时刻数据块*/
#define CCom_Re2_Tol_De_1                       0x11400201                      /*(上1结算日)组合无功2总最大需量及发生时刻*/
#define CCom_Re2_T1_De_1                        0x11400202                      /*(上1结算日)组合无功2费率1最大需量及发生时刻*/
#define CCom_Re2_T2_De_1                        0x11400203                      /*(上1结算日)组合无功2费率2最大需量及发生时刻*/
#define CCom_Re2_T3_De_1                        0x11400204                      /*(上1结算日)组合无功2费率3最大需量及发生时刻*/
#define CCom_Re2_T4_De_1                        0x11400205                      /*(上1结算日)组合无功2费率4最大需量及发生时刻*/
/*冻结周期内第一象限最大需量*/
#define CQua1_Re_De_FF_1                        0x11500200                      /*(上1结算日)1象限无功最大需量及发生时刻数据块*/
#define CQua1_Re_Tol_De_1                       0x11500201                      /*(上1结算日)1象限无功总最大需量及发生时刻*/
#define CQua1_Re_T1_De_1                        0x11500202                      /*(上1结算日)1象限无功费率1最大需量及发生时刻*/
#define CQua1_Re_T2_De_1                        0x11500203                      /*(上1结算日)1象限无功费率2最大需量及发生时刻*/
#define CQua1_Re_T3_De_1                        0x11500204                      /*(上1结算日)1象限无功费率3最大需量及发生时刻*/
#define CQua1_Re_T4_De_1                        0x11500205                      /*(上1结算日)1象限无功费率4最大需量及发生时刻*/
/*冻结周期内第二象限最大需量*/
#define CQua2_Re_De_FF_1                        0x11600200                      /*(上1结算日)2象限无功最大需量及发生时刻数据块*/
#define CQua2_Re_Tol_De_1                       0x11600201                      /*(上1结算日)2象限无功总最大需量及发生时刻*/
#define CQua2_Re_T1_De_1                        0x11600202                      /*(上1结算日)2象限无功费率1最大需量及发生时刻*/
#define CQua2_Re_T2_De_1                        0x11600203                      /*(上1结算日)2象限无功费率2最大需量及发生时刻*/
#define CQua2_Re_T3_De_1                        0x11600204                      /*(上1结算日)2象限无功费率3最大需量及发生时刻*/
#define CQua2_Re_T4_De_1                        0x11600205                      /*(上1结算日)2象限无功费率4最大需量及发生时刻*/
/*冻结周期内第三象限最大需量*/
#define CQua3_Re_De_FF_1                        0x11700200                      /*(上1结算日)3象限无功最大需量及发生时刻数据块*/
#define CQua3_Re_Tol_De_1                       0x11700201                      /*(上1结算日)3象限无功总最大需量及发生时刻*/
#define CQua3_Re_T1_De_1                        0x11700202                      /*(上1结算日)3象限无功费率1最大需量及发生时刻*/
#define CQua3_Re_T2_De_1                        0x11700203                      /*(上1结算日)3象限无功费率2最大需量及发生时刻*/
#define CQua3_Re_T3_De_1                        0x11700204                      /*(上1结算日)3象限无功费率3最大需量及发生时刻*/
#define CQua3_Re_T4_De_1                        0x11700205                      /*(上1结算日)3象限无功费率4最大需量及发生时刻*/
/*冻结周期内第四象限最大需量*/
#define CQua4_Re_De_FF_1                        0x11800200                      /*(上1结算日)4象限无功最大需量及发生时刻数据块*/
#define CQua4_Re_Tol_De_1                       0x11800201                      /*(上1结算日)4象限无功总最大需量及发生时刻*/
#define CQua4_Re_T1_De_1                        0x11800202                      /*(上1结算日)4象限无功费率1最大需量及发生时刻*/
#define CQua4_Re_T2_De_1                        0x11800203                      /*(上1结算日)4象限无功费率2最大需量及发生时刻*/
#define CQua4_Re_T3_De_1                        0x11800204                      /*(上1结算日)4象限无功费率3最大需量及发生时刻*/
#define CQua4_Re_T4_De_1                        0x11800205                      /*(上1结算日)4象限无功费率4最大需量及发生时刻*/
/*冻结周期内 A 相正向有功/反向有功/组合无功 1/组合无功 2/第一象限/第二象限/第三象限/第四象限最大需量*/
#define CPosA_Ac_De_1                           0x11110201                      /*(上1结算日)A相正向有功最大需量及发生时刻*/
#define CRevA_Ac_De_1                           0x11210201                      /*(上1结算日)A相反向有功最大需量及发生时刻*/
#define CComA_Re1_De_1                          0x11310201                      /*(上1结算日)A相组合无功1最大需量及发生时刻*/
#define CComA_Re2_De_1                          0x11410201                      /*(上1结算日)A相组合无功2最大需量及发生时刻*/
#define CQua1A_Re_De_1                          0x11510201                      /*(上1结算日)A相1象限无功最大需量及发生时刻*/
#define CQua2A_Re_De_1                          0x11610201                      /*(上1结算日)A相2象限无功最大需量及发生时刻*/
#define CQua3A_Re_De_1                          0x11710201                      /*(上1结算日)A相3象限无功最大需量及发生时刻*/
#define CQua4A_Re_De_1                          0x11810201                      /*(上1结算日)A相4象限无功最大需量及发生时刻*/
 /*冻结周期内 B 相正向有功/反向有功/组合无功 1/组合无功 2/第一象限/第二象限/第三象限/第四象限最大需量*/
#define CPosB_Ac_De_1                           0x11120201                      /*(上1结算日)B相正向有功最大需量及发生时刻*/
#define CRevB_Ac_De_1                           0x11220201                      /*(上1结算日)B相反向有功最大需量及发生时刻*/
#define CComB_Re1_De_1                          0x11320201                      /*(上1结算日)B相组合无功1最大需量及发生时刻*/
#define CComB_Re2_De_1                          0x11420201                      /*(上1结算日)B相组合无功2最大需量及发生时刻*/
#define CQua1B_Re_De_1                          0x11520201                      /*(上1结算日)B相1象限无功最大需量及发生时刻*/
#define CQua2B_Re_De_1                          0x11620201                      /*(上1结算日)B相2象限无功最大需量及发生时刻*/
#define CQua3B_Re_De_1                          0x11720201                      /*(上1结算日)B相3象限无功最大需量及发生时刻*/
#define CQua4B_Re_De_1                          0x11820201                      /*(上1结算日)B相4象限无功最大需量及发生时刻*/
/*冻结周期内 C 相正向有功/反向有功/组合无功 1/组合无功 2/第一象限/第二象限/第三象限/第四象限最大需量*/
#define CPosC_Ac_De_1                           0x11130201                      /*(上1结算日)C相正向有功最大需量及发生时刻*/
#define CRevC_Ac_De_1                           0x11230201                      /*(上1结算日)C相反向有功最大需量及发生时刻*/
#define CComC_Re1_De_1                          0x11330201                      /*(上1结算日)C相组合无功1最大需量及发生时刻*/
#define CComC_Re2_De_1                          0x11430201                      /*(上1结算日)C相组合无功2最大需量及发生时刻*/
#define CQua1C_Re_De_1                          0x11530201                      /*(上1结算日)C相1象限无功最大需量及发生时刻*/
#define CQua2C_Re_De_1                          0x11630201                      /*(上1结算日)C相2象限无功最大需量及发生时刻*/
#define CQua3C_Re_De_1                          0x11730201                      /*(上1结算日)C相3象限无功最大需量及发生时刻*/
#define CQua4C_Re_De_1                          0x11830201                      /*(上1结算日)C相4象限无功最大需量及发生时刻*/

/******************************变量类对象******************************/
#define CPhaseFF_Volage                         0x20000200                      /*电压数据块*/
#define CPhaseA_Volage                          0x20000201                      /*A相电压*/
#define CPhaseB_Volage                          0x20000202                      /*B相电压*/
#define CPhaseC_Volage                          0x20000203                      /*C相电压*/

#define CPhaseFF_Curr                           0x20010200                      /*电流数据块*/
#define CPhaseA_Curr                            0x20010201                      /*A相电流*/
#define CPhaseB_Curr                            0x20010202                      /*B相电流*/
#define CPhaseC_Curr                            0x20010203                      /*C相电流*/
#define CZero_Current                           0x20010400                      /*零线电流*/
#define CVector_Current                         0x20010600                      /*三相电流矢量和*/

#define CVolFF_Phase                            0x20020200                      /*电压相角数据块*/
#define CVolA_Phase                             0x20020201                      /*A相电压相角*/
#define CVolB_Phase                             0x20020202                      /*B相电压相角*/
#define CVolC_Phase                             0x20020203                      /*C相电压流相角*/

#define CPhaseFF_Angle                          0x20030200                      /*相角数据块*/
#define CPhaseA_Angle                           0x20030201                      /*A相相角*/
#define CPhaseB_Angle                           0x20030202                      /*B相相角*/
#define CPhaseC_Angle                           0x20030203                      /*C相相角*/

#define CInstantFF_AcPow                        0x20040200                      /*瞬时有功功率数据块*/
#define CInstant_TolAcPow                       0x20040201                      /*瞬时总有功功率*/
#define CInstantA_AcPow                         0x20040202                      /*A相瞬时有功功率*/
#define CInstantB_AcPow                         0x20040203                      /*B相瞬时有功功率*/
#define CInstantC_AcPow                         0x20040204                      /*C相瞬时有功功率*/

#define CInstantFF_RePow                        0x20050200                      /*瞬时无功功率数据块*/
#define CInstant_TolRePow                       0x20050201                      /*瞬时总无功功率*/
#define CInstantA_RePow                         0x20050202                      /*A相瞬时无功功率*/
#define CInstantB_RePow                         0x20050203                      /*B相瞬时无功功率*/
#define CInstantC_RePow                         0x20050204                      /*C相瞬时无功功率*/

#define CInstantFF_AppaPow                      0x20060200                      /*瞬时视在功率数据块*/
#define CInstant_TolAppaPow                     0x20060201                      /*瞬时总视在功率*/
#define CInstantA_AppaPow                       0x20060202                      /*A相瞬时视在功率*/
#define CInstantB_AppaPow                       0x20060203                      /*B相瞬时视在功率*/
#define CInstantC_AppaPow                       0x20060204                      /*C相瞬时视在功率*/

#define COneMin_AcPower_FF                      0x20070200
#define COneMin_AcPower                         0x20070201                      /*1分钟有功总平均功率*/
#define COneMin_AcPower_A                       0x20070202                      /*1分钟有功总平均功率A*/
#define COneMin_AcPower_B                       0x20070203                      /*1分钟有功总平均功率B*/
#define COneMin_AcPower_C                       0x20070204                      /*1分钟有功总平均功率C*/

#define COneMin_RePower_FF                      0x20080200
#define COneMin_RePower                         0x20080201                      /*1分钟无功总平均功率*/
#define COneMin_RePower_A                       0x20080202                      /*1分钟无功总平均功率A*/
#define COneMin_RePower_B                       0x20080203                      /*1分钟无功总平均功率B*/
#define COneMin_RePower_C                       0x20080204                      /*1分钟无功总平均功率C*/

#define CPhaseFF_PowerFactor                    0x200A0200                      /*功率因数数据块*/
#define CTol_PowerFactor                        0x200A0201                      /*总功率因数*/
#define CPhaseA_PowerFactor                     0x200A0202                      /*A相功率因数*/
#define CPhaseB_PowerFactor                     0x200A0203                      /*B相功率因数*/
#define CPhaseC_PowerFactor                     0x200A0204                      /*C相功率因数*/

#define CElecNet_Freq                           0x200F0200                      /*电网频率*/

#define CMeter_Temp                             0x20100200                      /*表内温度*/

#define CCloc_Batt_Vol                          0x20110200                      /*时钟电池电压*/
#define CReadMeter_Batt_Vol                     0x20120200                      /*抄表电池电压*/
#define CBatt_Work_Time                         0x20130200                      /*内部电池工作时间*/

#define CMeter_Work_StateFF                     0x20140200                      /*电表运行状态字1-7*/
#define CMeter_Work_State1                      0x20140201                      /*电表运行状态字1*/
#define CMeter_Work_State2                      0x20140202                      /*电表运行状态字2*/
#define CMeter_Work_State3                      0x20140203                      /*电表运行状态字3*/
#define CMeter_Work_State4                      0x20140204                      /*电表运行状态字4*/
#define CMeter_Work_State5                      0x20140205                      /*电表运行状态字5*/
#define CMeter_Work_State6                      0x20140206                      /*电表运行状态字6*/
#define CMeter_Work_State7                      0x20140207                      /*电表运行状态字7*/

#define CDrive_Report_State                     0x20150200                      /*主动上报状态字*/
#define CDrive_Report_Mode                      0x20150400                      /*主动上报模式字*/
#define CDrive_Report_Type                      0x20150500                      /*跟随上报状态字上报类型*/
#define CRst_Report_State                       0x20157F00                      /*复位主动上报状态字*/

#define CCurr_AcDemand                          0x20170200                      /*当前有功需量*/
#define CCurr_ReDemand                          0x20180200                      /*当前无功需量*/
#define CCurr_AppaDemand                        0x20190200                      /*当前视在需量*/

#define CCurr_Price                             0x201A0200                      /*当前电价*/
#define CCurr_Rate_Price                        0x201B0200                      /*当前费率电价*/
#define CCurr_Ladder_Price                      0x201C0200                      /*当前阶梯电价*/

#define CEventHPTime                            0x201E0200                      /*事件发生时间*/
#define C_EventStart_Moment                     0x201E0200                      /*事件发生时刻-重复*/
#define CEventEndTime                           0x20200200                      /*事件结束时间*/
#define C_EventEnd_Moment                       0x20200200                      /*事件结束时刻-重复*/
#define CFreeTime                               0x20210200                      /*冻结时间*/
#define CEventNum                               0x20220200                      /*事件记录序号*/
#define C_Event_RecordNO                        0x20220200                      /*事件记录序号-重复*/
#define CFreeNum                                0x20230200                      /*冻结序号*/
#define CEventHPSource                          0x20240200                      /*事件发生源*/
#define C_VolUnbalanceRate                      0x20266201                      /*事件发生期间电压不平衡率*/
#define C_CurUnbalanceRate	                    0x20276201                      /*事件发生期间电流不平衡率*/
#define C_AhNature2                             0x20290200                      /*安时值*/

#define CChargeBal_Hex_Cent                     0x202C0201                      /*当前剩余金额,单位为分*/
#define CPurchasePowTime                        0x202C0202

#define COverDraft_Hex_Cent                     0x202D0200                      /*当前透支金额,单位为分*/
#define CBuyCurr_TMoney                         0x202E0200                      /*累计购电金额*/

#define CM_Com_Ac_Tol_En_0                      0x20310200                      /*当前月度组合有功总累计用电量*/
#define CY_Com_Ac_Tol_En_0                      0x20320200                      /*阶梯结算用电量*/

#define CControl_ExecuteState                   0x20400200                      /*控制命令执行状态字*/
#define CControl_ErrorState                     0x20410200                      /*控制命令错误状态字*/
#define CControl_ExecuteStateUn                 0x20420200                      /*控制命令执行状态字,控制状态字、错误状态字统一*/

#define CVolA_Per_Pass_0_Freeze                 0x21310201                      /*日电压A相合格率统计数据*/
#define CVolA_Per_Pass_0                        0x21310202                      /*本月A相电压合格率统计数据*/
#define CVolB_Per_Pass_0_Freeze                 0x21320201                      /*日电压B相合格率统计数据*/
#define CVolB_Per_Pass_0                        0x21320202                      /*本月B相电压合格率统计数据*/
#define CVolC_Per_Pass_0_Freeze                 0x21330201                      /*日电压C相合格率统计数据*/
#define CVolC_Per_Pass_0                        0x21330202                      /*本月C相电压合格率统计数据*/

/******************************事件类对象******************************/
/*事件类关联属性*/
/*事件结束时刻可以不列*/
/*恒定磁场干扰发生结束/负荷开关发生结束/电源异常发生时，记录表格1的第1/2个数据*/
/*功率因数超限事件发生结束时，记录表格1的4个数据*/
#define C_HP_PosAcTolEn                         0x00102201                      /*事件发生时刻正向有功总电能*/
#define C_HP_RevAcTolEn                         0x00202201                      /*事件发生时刻反向有功总电能*/
#define C_HP_ComRe1TolEn                        0x00302201                      /*事件发生时刻组合无功1总电能*/
#define C_HP_ComRe2TolEn                        0x00402201                      /*事件发生时刻组合无功2总电能*/
#define C_HP_APosAcEn                           0x00112201                      /*事件发生时刻A相正向有功电能*/
#define C_HP_ARevAcEn                           0x00212201                      /*事件发生时刻A相反向有功电能*/
#define C_HP_AComRe1En                          0x00312201                      /*事件发生时刻A相组合无功1总电能*/
#define C_HP_AComRe2En                          0x00412201                      /*事件发生时刻A相组合无功2总电能*/
#define C_HP_BPosAcEn                           0x00122201                      /*事件发生时刻B相正向有功电能*/
#define C_HP_BRevAcEn                           0x00222201                      /*事件发生时刻B相反向有功电能*/
#define C_HP_BComRe1En                          0x00322201                      /*事件发生时刻B相组合无功1总电能*/
#define C_HP_BComRe2En                          0x00422201                      /*事件发生时刻B相组合无功2总电能*/
#define C_HP_CPosAcEn                           0x00132201                      /*事件发生时刻C相正向有功电能*/
#define C_HP_CRevAcEn                           0x00232201                      /*事件发生时刻C相反向有功电能*/
#define C_HP_CComRe1En                          0x00332201                      /*事件发生时刻C相组合无功1总电能*/
#define C_HP_CComRe2En                          0x00432201                      /*事件发生时刻C相组合无功2总电能*/
#define C_Hp_TQuadrant1En                       0x00502201                      /*事件发生时刻第一象限无功总电能*/
#define C_Hp_TQuadrant2En                       0x00602201                      /*事件发生时刻第二象限无功总电能*/
#define C_Hp_TQuadrant3En                       0x00702201                      /*事件发生时刻第三象限无功总电能*/
#define C_Hp_TQuadrant4En                       0x00802201                      /*事件发生时刻第四象限无功总电能*/
#define C_Hp_AQuadrant1En                       0x00512201                      /*事件发生时刻A相第一象限无功总电能*/
#define C_Hp_AQuadrant2En                       0x00612201                      /*事件发生时刻A相第二象限无功总电能*/
#define C_Hp_AQuadrant3En                       0x00712201                      /*事件发生时刻A相第三象限无功总电能*/
#define C_Hp_AQuadrant4En                       0x00812201                      /*事件发生时刻A相第四象限无功总电能*/
#define C_Hp_BQuadrant1En                       0x00522201                      /*事件发生时刻B相第一象限无功总电能*/
#define C_Hp_BQuadrant2En                       0x00622201                      /*事件发生时刻B相第二象限无功总电能*/
#define C_Hp_BQuadrant3En                       0x00722201                      /*事件发生时刻B相第三象限无功总电能*/
#define C_Hp_BQuadrant4En                       0x00822201                      /*事件发生时刻B相第四象限无功总电能*/
#define C_Hp_CQuadrant1En                       0x00532201                      /*事件发生时刻C相第一象限无功总电能*/
#define C_Hp_CQuadrant2En                       0x00632201                      /*事件发生时刻C相第二象限无功总电能*/
#define C_Hp_CQuadrant3En                       0x00732201                      /*事件发生时刻C相第三象限无功总电能*/
#define C_Hp_CQuadrant4En                       0x00832201                      /*事件发生时刻C相第四象限无功总电能*/
#define C_HP_PosAcTolDe                         0x10102201                      /*事件发生时刻正向有功最大需量及发生时间*/
#define C_HP_RevAcTolDe                         0x10202201                      /*事件发生时刻反向有功最大需量及发生时间*/
#define C_HP_APosAcDe                           0x10112201                      /*事件发生时刻A相正向有功最大需量及发生时间*/
#define C_HP_ARevAcDe                           0x10212201                      /*事件发生时刻A相反向有功最大需量及发生时间*/
#define C_HP_BPosAcDe                           0x10122201                      /*事件发生时刻B相正向有功最大需量及发生时间*/
#define C_HP_BRevAcDe                           0x10222201                      /*事件发生时刻B相反向有功最大需量及发生时间*/
#define C_HP_CPosAcDe                           0x10132201                      /*事件发生时刻C相正向有功最大需量及发生时间*/
#define C_HP_CRevAcDe                           0x10232201                      /*事件发生时刻C相反向有功最大需量及发生时间*/
#define C_Hp_TQuadrant1De                       0x10502201                      /*事件发生时刻第一象限无功总最大需量及发生时间*/
#define C_Hp_TQuadrant2De                       0x10602201                      /*事件发生时刻第二象限无功总最大需量及发生时间*/
#define C_Hp_TQuadrant3De                       0x10702201                      /*事件发生时刻第三象限无功总最大需量及发生时间*/
#define C_Hp_TQuadrant4De                       0x10802201                      /*事件发生时刻第四象限无功总最大需量及发生时间*/
#define C_Hp_AQuadrant1De                       0x10512201                      /*事件发生时刻A相第一象限无功总最大需量及发生时间*/
#define C_Hp_AQuadrant2De                       0x10612201                      /*事件发生时刻A相第二象限无功总最大需量及发生时间*/
#define C_Hp_AQuadrant3De                       0x10712201                      /*事件发生时刻A相第三象限无功总最大需量及发生时间*/
#define C_Hp_AQuadrant4De                       0x10812201                      /*事件发生时刻A相第四象限无功总最大需量及发生时间*/
#define C_Hp_BQuadrant1De                       0x10522201                      /*事件发生时刻B相第一象限无功总最大需量及发生时间*/
#define C_Hp_BQuadrant2De                       0x10622201                      /*事件发生时刻B相第二象限无功总最大需量及发生时间*/
#define C_Hp_BQuadrant3De                       0x10722201                      /*事件发生时刻B相第三象限无功总最大需量及发生时间*/
#define C_Hp_BQuadrant4De                       0x10822201                      /*事件发生时刻B相第四象限无功总最大需量及发生时间*/
#define C_Hp_CQuadrant1De                       0x10532201                      /*事件发生时刻C相第一象限无功总最大需量及发生时间*/
#define C_Hp_CQuadrant2De                       0x10632201                      /*事件发生时刻C相第二象限无功总最大需量及发生时间*/
#define C_Hp_CQuadrant3De                       0x10732201                      /*事件发生时刻C相第三象限无功总最大需量及发生时间*/
#define C_Hp_CQuadrant4De                       0x10832201                      /*事件发生时刻C相第四象限无功总最大需量及发生时间*/
#define C_HP_AVol                               0x20002201                      /*事件发生时刻A相电压*/
#define C_HP_BVol                               0x20002202                      /*事件发生时刻B相电压*/
#define C_HP_CVol                               0x20002203                      /*事件发生时刻C相电压*/
#define C_HP_ACurr                              0x20012201                      /*事件发生时刻A相电流*/
#define C_HP_BCurr                              0x20012202                      /*事件发生时刻B相电流*/
#define C_HP_CCurr                              0x20012203                      /*事件发生时刻C相电流*/
#define C_HP_Curr                               0x20012200                      /*事件发生时刻电流*/
#define C_HP_AAcP                               0x20042201                      /*事件发生时刻A相有功功率*/
#define C_HP_BAcP                               0x20042202                      /*事件发生时刻B相有功功率*/
#define C_HP_CAcP                               0x20042203                      /*事件发生时刻C相有功功率*/
#define C_HP_AReP                               0x20052201                      /*事件发生时刻A相无功功率*/
#define C_HP_BReP                               0x20052202                      /*事件发生时刻B相无功功率*/
#define C_HP_CReP                               0x20052203                      /*事件发生时刻C相无功功率*/
#define C_HP_APF                                0x200A2201                      /*事件发生时刻A相功率因数*/
#define C_HP_BPF                                0x200A2202                      /*事件发生时刻B相功率因数*/
#define C_HP_CPF                                0x200A2203                      /*事件发生时刻C相功率因数*/
#define C_SpareBDayTablePrO	                    0x40152200                      /*时区表编程前当前套时区表*/
#define C_SettleDatebeforePro                   0x41162200                      /*编程前结算日*/

#define C_End_PosAcTolEn                        0x00108201                      /*事件结束时刻正向有功总电能*/
#define C_End_RevAcTolEn                        0x00208201                      /*事件结束时刻反向有功总电能*/
#define C_End_ComRe1TolEn                       0x00308201                      /*事件结束时刻组合无功1总电能*/
#define C_End_ComRe2TolEn                       0x00408201                      /*事件结束时刻组合无功2总电能*/
#define C_End_APosAcEn                          0x00118201                      /*事件结束时刻A相正向有功电能*/
#define C_End_ARevAcEn                          0x00218201                      /*事件结束时刻A相反向有功电能*/
#define C_End_AComRe1En                         0x00318201                      /*事件结束时刻A相组合无功1电能*/
#define C_End_AComRe2En                         0x00418201                      /*事件结束时刻A相组合无功2电能*/
#define C_End_BPosAcEn                          0x00128201                      /*事件发生时刻B相正向有功电能*/
#define C_End_BRevAcEn                          0x00228201                      /*事件发生时刻B相反向有功电能*/
#define C_End_BComRe1En                         0x00328201                      /*事件结束时刻B相组合无功1电能*/
#define C_End_BComRe2En                         0x00428201                      /*事件结束时刻B相组合无功2电能*/
#define C_End_CPosAcEn                          0x00138201                      /*事件发生时刻C相正向有功电能*/
#define C_End_CRevAcEn                          0x00238201                      /*事件发生时刻C相反向有功电能*/
#define C_End_CComRe1En                         0x00338201                      /*事件结束时刻C相组合无功1电能*/
#define C_End_CComRe2En                         0x00438201                      /*事件结束时刻C相组合无功2电能*/
#define C_End_TQuadrant1En                      0x00508201                      /*事件结束时刻第一象限无功总电能*/
#define C_End_TQuadrant2En                      0x00608201                      /*事件结束时刻第二象限无功总电能*/
#define C_End_TQuadrant3En                      0x00708201                      /*事件结束时刻第三象限无功总电能*/
#define C_End_TQuadrant4En                      0x00808201                      /*事件结束时刻第四象限无功总电能*/
#define C_End_AQuadrant4En                      0x00818201                      /*事件结束时刻A相第四象限无功总电能*/
#define C_End_BQuadrant4En                      0x00828201                      /*事件结束时刻B相第四象限无功总电能*/
#define C_End_CQuadrant4En                      0x00838201                      /*事件结束时刻C相第四象限无功总电能*/

#define C_VolUnbalanceRate_E                    0x20266200                      /*事件发生期间电压不平衡率*/
#define C_CurUnbalanceRate_E                    0x20276200                      /*事件发生期间电流不平衡率*/
#define C_TolAh                                 0x20296201                      /*事件期间总Ah数*/
#define C_AAh                                   0x20296202                      /*事件期间A相Ah数*/
#define C_BAh                                   0x20296203                      /*事件期间B相Ah数*/
#define C_CAh                                   0x20296204                      /*事件期间C相Ah数*/
/******************************************************************************/
#define CUpdata_Status         					0x33000200                      /*上报状态*/
#define CEventReportStatus_Satand               0x33010500                      /*标准事件上报状态*/
#define CProgOADGather                          0x33020206                      /*编程记录事件单元，编程对象OAD，array格式，目前支持最大10个*/
#define C_OverDemandRenew_Demand                0x33080206                      /*需量超限事件,超限期间需量最大值*/
#define C_OverDemandRenew_HapTime               0x33080207                      /*需量超限事件,超限期间需量最大值发生时间*/
#define CEventReportStatus_OverDemand           0x33080500                      /*需量超限上报状态*/
#define CEventReportStatus_EventClear           0x330C0500                      /*事件清零上报状态*/
#define CAbnormalCard_CareNo			        0x33100206                      /*异常插卡卡序列号*/
#define CAbnormalCard_ErrorStatus		        0x33100207                      /*异常插卡错误状态字*/
#define CAbnormalCard_OrderHead			        0x33100208                      /*异常插卡插卡操作命令头*/
#define CAbnormalCard_ErrorRespondStatus        0x33100209                      /*异常插卡插卡错误响应状态*/
#define CEventReportStatus_ReturnM              0x33110500                      /*退费上报状态*/
#define CRWTimeTable_OAD			            0x33140206                      /*时段表编程OAD*/
#define CRWTimeTable_ForwardData	            0x33140207                      /*时段表编程编程前数据*/
#define C_RWHoliday_OAD				            0x33150206                      /*节假日编程OAD*/
#define CRWHoliday_ForwardData		            0x33150207                     /*节假日编程前节假日数据*/
#define CEventReportStatus_Class24              0x331F0400                      /*分项事件记录上报状态*/
#define CNewReportList                          0x33200200                      /*新增上报列表*/

/******************************************************************************/
#define CUpdata_Status         					0x33000200                      /*上报状态*/
#define CProgram_OADList						0x33020206                      /*编程事件记录编程列表*/
#define CEventClear_OADList						0x330C0206                      /*事件清零记录清零列表*/
#define CReturnMoney_Charge						0x33110206                      /*退费事件记录固定列表中退费金额*/

/******************************************************************************/
/*失压*/
#define CLoss_Vol_OADTab                        0x30000200                      /*失压OAD关联列表，A、B、C共用关联列表*/
#define CLossA_Vol_DegreeCurr                   0x30000302                      /*A相失压总次数,当前值*/
#define CLossB_Vol_DegreeCurr                   0x30000303                      /*B相失压总次数,当前值*/
#define CLossC_Vol_DegreeCurr                   0x30000304                      /*C相失压总次数,当前值*/
#define CLossVolage_Vol_UpLim                   0x30000501                      /*失压事件电压触发上限*/
#define CLossVolage_Vol_LowLim                  0x30000502                      /*失压事件电压恢复下限*/
#define CLossVolage_Curr_LowLim                 0x30000503                      /*失压事件电流触发下限*/
#define CLossVolage_Delay_T                     0x30000504                      /*失压事件判断延时时间*/
#define CLossAVol_FF_1                          0x30000701                      /*上1次A相失压数据块*/
#define CLossBVol_FF_1                          0x30000801                      /*上1次B相失压数据块*/
#define CLossCVol_FF_1                          0x30000901                      /*上1次C相失压数据块*/
#define CLoss_TollVol_Current                   0x30000A01                      /*总失压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossA_Vol_Current                      0x30000A02                      /*A相失压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossB_Vol_Current                      0x30000A03                      /*B相失压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossC_Vol_Current                      0x30000A04                      /*C相失压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossVolage_Report_Mode                 0x30000B00                      /*失压上报模式字*/
#define CLoss_Vol_Gather                        0x30000D00                      /*失压统计集合*/
#define CLoss_Vol_Degree                        0x30000D01                      /*失压总次数*/
#define CLoss_Vol_Time                          0x30000D02                      /*失压累计时间*/
#define CLoss_Vol_Hp                            0x30000D03                      /*最近1次失压发生时刻*/
#define CLoss_Vol_End                           0x30000D04                      /*最近1次失压结束时刻*/
#define CLoss_TollVol_Attri14                   0x30000E01                      /*失压最近1次发生时间、结束时间*/
#define CLossA_Vol_Attri14                      0x30000E02                      /*A相失压*/
#define CLossB_Vol_Attri14                      0x30000E03                      /*B相失压*/
#define CLossC_Vol_Attri14                      0x30000E04                      /*C相失压*/
#define CLossVolage_Report_Type                 0x30000F00                      /*失压上报类型*/
/*失压-645*/
#define C_LossVol_Tol_Dgree_645                 0x10000001                      /*失压总次数*/
#define C_LossVol_Tol_Time_645                  0x10000002                      /*失压总时间*/
#define C_LossVol_Recent_HappenTime_645         0x10000101                      /*最近1次失压发生时刻*/
#define C_LossVol_Recent_EndTime_645            0x10000201                      /*最近1次失压结束时刻*/

#define CLossA_Vol_Degree_645                   0x10010001                      /*A相失压总次数*/
#define CLossB_Vol_Degree_645                   0x10020001                      /*B相失压总次数*/
#define CLossC_Vol_Degree_645                   0x10030001                      /*C相失压总次数*/

#define CLossA_Vol_Hp_1                         0x10010101                      /*上1次A相失压发生时刻*/
#define CLossAVol_TolAh_1                       0x10012101                      /*上1次A相失压期间总Ah数*/
#define CLossAVol_AAh_1                         0x10012201                      /*上1次A相失压期间A相Ah数*/
#define CLossAVol_BAh_1                         0x10012301                      /*上1次A相失压期间B相Ah数*/
#define CLossAVol_CAh_1                         0x10012401                      /*上1次A相失压期间C相Ah数*/
#define CLossAVol_HpData_1                      0x1001FC01                      /*上1次A相失压发生数据*/
#define CLossAVol_EndData_1                     0x1001FD01                      /*上1次A相失压结束数据*/
#define CLossB_Vol_Hp_1	                        0x10020101                      /*上1次B相失压发生时刻*/
#define CLossBVol_TolAh_1                       0x10022101                      /*上1次B相失压期间总Ah数*/
#define CLossBVol_AAh_1                         0x10022201                      /*上1次B相失压期间A相Ah数*/
#define CLossBVol_BAh_1                         0x10022301                      /*上1次B相失压期间B相Ah数*/
#define CLossBVol_CAh_1                         0x10022401                      /*上1次B相失压期间C相Ah数*/
#define CLossBVol_HpData_1                      0x1002FC01                      /*上1次B相失压发生数据*/
#define CLossBVol_EndData_1                     0x1002FD01                      /*上1次B相失压结束数据*/
#define CLossC_Vol_Hp_1	                        0x10030101                      /*上1次C相失压发生时刻*/
#define CLossCVol_TolAh_1                       0x10032101                      /*上1次C相失压期间总Ah数*/
#define CLossCVol_AAh_1                         0x10032201                      /*上1次C相失压期间A相Ah数*/
#define CLossCVol_BAh_1                         0x10032301                      /*上1次C相失压期间B相Ah数*/
#define CLossCVol_CAh_1                         0x10032401                      /*上1次C相失压期间C相Ah数*/
#define CLossCVol_HpData_1                      0x1003FC01                      /*上1次C相失压发生数据*/
#define CLossCVol_EndData_1                     0x1003FD01                      /*上1次C相失压结束数据*/
/******************************************************************************/
/*欠压*/
#define CLow_Vol_OADTab                         0x30010200                      /*欠压OAD关联列表，A、B、C共用关联列表*/
#define CLowA_Vol_DegreeCurr                    0x30010302                      /*A相欠压总次数,当前值*/
#define CLowB_Vol_DegreeCurr                    0x30010303                      /*B相欠压总次数,当前值*/
#define CLowC_Vol_DegreeCurr                    0x30010304                      /*C相欠压总次数,当前值*/
#define CLowVolage_Vol_UpLim                    0x30010501                      /*欠压事件电压触发上限*/
#define CLowVolage_Delay_T                      0x30010502                      /*欠压事件判断延时时间*/
#define CLowAVol_FF_1                           0x30010701                      /*上1次A相欠压数据块*/
#define CLowBVol_FF_1                           0x30010801                      /*上1次B相欠压数据块*/
#define CLowCVol_FF_1                           0x30010901                      /*上1次C相欠压数据块*/
#define CLowA_Vol_Current                       0x30010A02                      /*A相欠压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLowB_Vol_Current                       0x30010A03                      /*B相欠压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLowC_Vol_Current                       0x30010A04                      /*C相欠压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLowVolage_Report_Mode                  0x30010B00	                    /*欠压上报模式字*/
#define CLowA_Vol_Attri14                       0x30010E02                      /*A相失压*/
#define CLowB_Vol_Attri14                       0x30010E03                      /*B相失压*/
#define CLowC_Vol_Attri14                       0x30010E04                      /*C相失压*/
#define CLowVolage_Report_Type                  0x30010F00                      /*欠压上报类型*/
/*欠压-645*/
#define CLowA_Vol_Degree_645                    0x11010001                      /*A相欠压总次数*/
#define CLowB_Vol_Degree_645                    0x11020001                      /*B相欠压总次数*/
#define CLowC_Vol_Degree_645                    0x11030001                      /*C相欠压总次数*/

#define CLowA_Vol_Hp_1                          0x11010101                      /*上1次A相欠压发生时刻*/
#define CLowAVol_TolAh_1                        0x11012101                      /*上1次A相欠压期间总Ah数*/
#define CLowAVol_AAh_1                          0x11012201                      /*上1次A相欠压期间A相Ah数*/
#define CLowAVol_BAh_1                          0x11012301                      /*上1次A相欠压期间B相Ah数*/
#define CLowAVol_CAh_1                          0x11012401                      /*上1次A相欠压期间C相Ah数*/
#define CLowAVol_HpData_1                       0x1101FC01                      /*上1次A相欠压发生数据*/
#define CLowAVol_EndData_1                      0x1101FD01                      /*上1次A相欠压结束数据*/
#define CLowB_Vol_Hp_1                          0x11020101                      /*上1次B相欠压发生时刻*/
#define CLowBVol_TolAh_1                        0x11022101                      /*上1次B相欠压期间总Ah数*/
#define CLowBVol_AAh_1                          0x11022201                      /*上1次B相欠压期间A相Ah数*/
#define CLowBVol_BAh_1                          0x11022301                      /*上1次B相欠压期间B相Ah数*/
#define CLowBVol_CAh_1                          0x11022401                      /*上1次B相欠压期间C相Ah数*/
#define CLowBVol_HpData_1                       0x1102FC01                      /*上1次B相欠压发生数据*/
#define CLowBVol_EndData_1                      0x1102FD01                      /*上1次B相欠压结束数据*/
#define CLowC_Vol_Hp_1                          0x11030101                      /*上1次C相欠压发生时刻*/
#define CLowCVol_TolAh_1                        0x11032101                      /*上1次C相欠压期间总Ah数*/
#define CLowCVol_AAh_1                          0x11032201                      /*上1次C相欠压期间A相Ah数*/
#define CLowCVol_BAh_1                          0x11032301                      /*上1次C相欠压期间B相Ah数*/
#define CLowCVol_CAh_1                          0x11032401                      /*上1次C相欠压期间C相Ah数*/
#define CLowCVol_HpData_1                       0x1103FC01                      /*上1次C相欠压发生数据*/
#define CLowCVol_EndData_1                      0x1103FD01                      /*上1次C相欠压结束数据*/
/******************************************************************************/
/*过压*/
#define COver_Vol_OADTab                        0x30020200                      /*过压OAD关联列表，A、B、C共用关联列表*/
#define COverA_Vol_DegreeCurr                   0x30020302                      /*A相过压总次数,当前值*/
#define COverB_Vol_DegreeCurr                   0x30020303                      /*B相过压总次数,当前值*/
#define COverC_Vol_DegreeCurr                   0x30020304                      /*C相过压总次数,当前值*/
#define COverVolage_Vol_LowLim                  0x30020501                      /*过压事件电压触发下限*/
#define COverVolage_Delay_T                     0x30020502                      /*过压事件判断延时时间*/
#define COverAVol_FF_1                          0x30020701                      /*上1次A相过压数据块*/
#define COverBVol_FF_1                          0x30020801                      /*上1次B相过压数据块*/
#define COverCVol_FF_1                          0x30020901                      /*上1次C相过压数据块*/
#define COverA_Vol_Current                      0x30020A02                      /*A相过压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverB_Vol_Current                      0x30020A03                      /*B相过压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverC_Vol_Current                      0x30020A04                      /*C相过压当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverVolage_Report_Mode                 0x30020B00                      /*过压上报模式字*/
#define COverA_Vol_Attri14                      0x30020E02                      /*A相过压*/
#define COverB_Vol_Attri14                      0x30020E03                      /*B相过压*/
#define COverC_Vol_Attri14                      0x30020E04                      /*C相过压*/
#define COverVolage_Report_Type                 0x30020F00                      /*过压上报类型*/
/*过压-645*/
#define COverA_Vol_Degree_645                   0x12010001                      /*A相过压总次数*/
#define COverB_Vol_Degree_645                   0x12020001                      /*B相过压总次数*/
#define COverC_Vol_Degree_645                   0x12030001                      /*C相过压总次数*/

#define COverA_Vol_Hp_1                         0x12010101                      /*上1次A相过压发生时刻*/
#define COverAVol_TolAh_1                       0x12012101                      /*上1次A相过压期间总Ah数*/
#define COverAVol_AAh_1                         0x12012201                      /*上1次A相过压期间A相Ah数*/
#define COverAVol_BAh_1                         0x12012301                      /*上1次A相过压期间B相Ah数*/
#define COverAVol_CAh_1                         0x12012401                      /*上1次A相过压期间C相Ah数*/
#define COverAVol_HpData_1                      0x1201FC01                      /*上1次A相过压发生数据*/
#define COverAVol_EndData_1                     0x1201FD01                      /*上1次A相过压结束数据*/
#define COverB_Vol_Hp_1	                        0x12020101                      /*上1次B相过压发生时刻*/
#define COverBVol_TolAh_1                       0x12022101                      /*上1次B相过压期间总Ah数*/
#define COverBVol_AAh_1                         0x12022201                      /*上1次B相过压期间A相Ah数*/
#define COverBVol_BAh_1                         0x12022301                      /*上1次B相过压期间B相Ah数*/
#define COverBVol_CAh_1                         0x12022401                      /*上1次B相过压期间C相Ah数*/
#define COverBVol_HpData_1                      0x1202FC01                      /*上1次B相过压发生数据*/
#define COverBVol_EndData_1                     0x1202FD01                      /*上1次B相过压结束数据*/
#define COverC_Vol_Hp_1	                        0x12030101                      /*上1次C相过压发生时刻*/
#define COverCVol_TolAh_1                       0x12032101                      /*上1次C相过压期间总Ah数*/
#define COverCVol_AAh_1                         0x12032201                      /*上1次C相过压期间A相Ah数*/
#define COverCVol_BAh_1                         0x12032301                      /*上1次C相过压期间B相Ah数*/
#define COverCVol_CAh_1                         0x12032401                      /*上1次C相过压期间C相Ah数*/
#define COverCVol_HpData_1                      0x1203FC01                      /*上1次C相过压发生数据*/
#define COverCVol_EndData_1                     0x1203FD01                      /*上1次C相过压结束数据*/
/******************************************************************************/
/*断相*/
#define CBreak_Vol_OADTab                       0x30030200                      /*断相OAD关联列表，A、B、C共用关联列表*/
#define CBreakA_Vol_DegreeCurr                  0x30030302                      /*A相断相总次数,当前值*/
#define CBreakB_Vol_DegreeCurr                  0x30030303                      /*B相断相总次数,当前值*/
#define CBreakC_Vol_DegreeCurr                  0x30030304                      /*C相断相总次数,当前值*/
#define CBreakVol_Vol_UpLim                     0x30030501                      /*断相事件电压触发上限*/
#define CBreakVol_Curr_UpLim                    0x30030502                      /*断相事件电流触发上限*/
#define CBreakVol_Delay_T                       0x30030503                      /*断相事件判定延时时间*/
#define CBreakAVol_FF_1                         0x30030701                      /*上1次A相断相数据块*/
#define CBreakBVol_FF_1                         0x30030801                      /*上1次B相断相数据块*/
#define CBreakCVol_FF_1                         0x30030901                      /*上1次C相断相数据块*/
#define CBreakA_Vol_Current                     0x30030A02                      /*A相断相当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CBreakB_Vol_Current                     0x30030A03                      /*B相断相当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CBreakC_Vol_Current                     0x30030A04                      /*C相断相当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CBreakVol_Report_Mode                   0x30030B00                      /*断相上报模式字*/
#define CBreakA_Vol_Attri14                     0x30030E02                      /*A相断相*/
#define CBreakB_Vol_Attri14                     0x30030E03                      /*B相断相*/
#define CBreakC_Vol_Attri14                     0x30030E04                      /*C相断相*/
#define CBreakVol_Report_Type                   0x30030F00                      /*断相上报类型*/
/*断相-645*/
#define CBreakA_Vol_Degree_645                  0x13010001                      /*A相断相总次数*/
#define CBreakB_Vol_Degree_645                  0x13020001                      /*B相断相总次数*/
#define CBreakC_Vol_Degree_645                  0x13030001                      /*C相断相总次数*/

#define CBreakA_Vol_Hp_1                        0x13010101                      /*上1次A相断相发生时刻*/
#define CBreakAVol_TolAh_1                      0x13012101                      /*上1次A相断相期间总Ah数*/
#define CBreakAVol_AAh_1                        0x13012201                      /*上1次A相断相期间A相Ah数*/
#define CBreakAVol_BAh_1                        0x13012301                      /*上1次A相断相期间B相Ah数*/
#define CBreakAVol_CAh_1                        0x13012401                      /*上1次A相断相期间C相Ah数*/
#define CBreakAVol_HpData_1                     0x1301FC01                      /*上1次A相断相发生数据*/
#define CBreakAVol_EndData_1                    0x1301FD01                      /*上1次A相断相结束数据*/
#define CBreakB_Vol_Hp_1                        0x13020101                      /*上1次B相断相发生时刻*/
#define CBreakBVol_TolAh_1                      0x13022101                      /*上1次B相断相期间总Ah数*/
#define CBreakBVol_AAh_1                        0x13022201                      /*上1次B相断相期间A相Ah数*/
#define CBreakBVol_BAh_1                        0x13022301                      /*上1次B相断相期间B相Ah数*/
#define CBreakBVol_CAh_1                        0x13022401                      /*上1次B相断相期间C相Ah数*/
#define CBreakBVol_HpData_1                     0x1302FC01                      /*上1次B相断相发生数据*/
#define CBreakBVol_EndData_1                    0x1302FD01                      /*上1次B相断相结束数据*/
#define CBreakC_Vol_Hp_1                        0x13030101                      /*上1次C相断相发生时刻*/
#define CBreakCVol_TolAh_1                      0x13032101                      /*上1次C相断相期间总Ah数*/
#define CBreakCVol_AAh_1                        0x13032201                      /*上1次C相断相期间A相Ah数*/
#define CBreakCVol_BAh_1                        0x13032301                      /*上1次C相断相期间B相Ah数*/
#define CBreakCVol_CAh_1                        0x13032401                      /*上1次C相断相期间C相Ah数*/
#define CBreakCVol_HpData_1                     0x1303FC01                      /*上1次C相断相发生数据*/
#define CBreakCVol_EndData_1                    0x1303FD01                      /*上1次C相断相结束数据*/
/******************************************************************************/
/*失流*/
#define CLoss_Curr_OADTab                       0x30040200                      /*失流OAD关联列表，A、B、C共用关联列表*/
#define CLossA_Curr_DegreeCurr                  0x30040302                      /*A相失流总次数,当前值*/
#define CLossB_Curr_DegreeCurr                  0x30040303                      /*B相失流总次数,当前值*/
#define CLossC_Curr_DegreeCurr                  0x30040304                      /*C相失流总次数,当前值*/
#define CLossCurr_Vol_LowLim                    0x30040501                      /*失流事件电压触发下限*/
#define CLossCurr_Curr_UpLim                    0x30040502                      /*失流事件电流触发上限*/
#define CLossCurr_Curr_LowLim                   0x30040503                      /*失流事件电流触发下限*/
#define CLossCurr_Delay_T                       0x30040504                      /*失流事件判断延时时间*/
#define CLossACurr_FF_1                         0x30040701                      /*上1次A相失流数据块*/
#define CLossBCurr_FF_1                         0x30040801                      /*上1次B相失流数据块*/
#define CLossCCurr_FF_1                         0x30040901                      /*上1次C相失流数据块*/
#define CLossA_Curr_Current                     0x30040A02                      /*A相失流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossB_Curr_Current                     0x30040A03                      /*B相失流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossC_Curr_Current                     0x30040A04                      /*C相失流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CLossCurr_Report_Mode                   0x30040B00                      /*失流上报模式字*/
#define CLossA_Curr_Attri14                     0x30040E02                      /*A相失流*/
#define CLossB_Curr_Attri14                     0x30040E03                      /*B相失流*/
#define CLossC_Curr_Attri14                     0x30040E04                      /*C相失流*/
#define CLossCurr_Report_Type                   0x30040F00                      /*失流上报类型*/
/*失流-645*/
#define CLossA_Curr_Degree_645                  0x18010001                      /*A相失流总次数*/
#define CLossB_Curr_Degree_645                  0x18020001                      /*B相失流总次数*/
#define CLossC_Curr_Degree_645                  0x18030001                      /*C相失流总次数*/

#define CLossA_Curr_Hp_1                        0x18010101                      /*上1次A相失流发生时刻*/
#define CLossACurr_HpData_1                     0x1801FC01                      /*上1次A相失流发生数据*/
#define CLossACurr_EndData_1                    0x1801FD01                      /*上1次A相失流结束数据*/
#define CLossA_Curr_FF_1                        0x1801FF01                      /*上1次A相失流数据块*/
#define CLossA_Curr_FF_2                        0x1801FF02                      /*上2次A相失流数据块*/
#define CLossA_Curr_FF_3                        0x1801FF03                      /*上3次A相失流数据块*/
#define CLossA_Curr_FF_4                        0x1801FF04                      /*上4次A相失流数据块*/
#define CLossA_Curr_FF_5                        0x1801FF05                      /*上5次A相失流数据块*/
#define CLossA_Curr_FF_6                        0x1801FF06                      /*上6次A相失流数据块*/
#define CLossA_Curr_FF_7                        0x1801FF07                      /*上7次A相失流数据块*/
#define CLossA_Curr_FF_8                        0x1801FF08                      /*上8次A相失流数据块*/
#define CLossA_Curr_FF_9                        0x1801FF09                      /*上9次A相失流数据块*/
#define CLossA_Curr_FF_10                       0x1801FF0A                      /*上10次A相失流数据块*/
#define CLossA_Curr_FF_FF                       0x1801FFFF                      /*上1-上10次A相失流数据块*/
#define CLossB_Curr_Hp_1                        0x18020101                      /*上1次B相失流发生时刻*/
#define CLossBCurr_HpData_1                     0x1802FC01                      /*上1次B相失流发生数据*/
#define CLossBCurr_EndData_1                    0x1802FD01                      /*上1次B相失流结束数据*/
#define CLossB_Curr_FF_1                        0x1802FF01                      /*上1次B相失流数据块*/
#define CLossB_Curr_FF_2                        0x1802FF02                      /*上2次B相失流数据块*/
#define CLossB_Curr_FF_3                        0x1802FF03                      /*上3次B相失流数据块*/
#define CLossB_Curr_FF_4                        0x1802FF04                      /*上4次B相失流数据块*/
#define CLossB_Curr_FF_5                        0x1802FF05                      /*上5次B相失流数据块*/
#define CLossB_Curr_FF_6                        0x1802FF06                      /*上6次B相失流数据块*/
#define CLossB_Curr_FF_7                        0x1802FF07                      /*上7次B相失流数据块*/
#define CLossB_Curr_FF_8                        0x1802FF08                      /*上8次B相失流数据块*/
#define CLossB_Curr_FF_9                        0x1802FF09                      /*上9次B相失流数据块*/
#define CLossB_Curr_FF_10                       0x1802FF0A                      /*上10次B相失流数据块*/
#define CLossB_Curr_FF_FF                       0x1802FFFF                      /*上1-上10次B相失流数据块*/
#define CLossC_Curr_Hp_1                        0x18030101                      /*上1次C相失流发生时刻*/
#define CLossCCurr_HpData_1                     0x1803FC01                      /*上1次C相失流发生数据*/
#define CLossCCurr_EndData_1                    0x1803FD01                      /*上1次C相失流结束数据*/
#define CLossC_Curr_FF_1                        0x1803FF01                      /*上1次C相失流数据块*/
#define CLossC_Curr_FF_2                        0x1803FF02                      /*上2次C相失流数据块*/
#define CLossC_Curr_FF_3                        0x1803FF03                      /*上3次C相失流数据块*/
#define CLossC_Curr_FF_4                        0x1803FF04                      /*上4次C相失流数据块*/
#define CLossC_Curr_FF_5                        0x1803FF05                      /*上5次C相失流数据块*/
#define CLossC_Curr_FF_6                        0x1803FF06                      /*上6次C相失流数据块*/
#define CLossC_Curr_FF_7                        0x1803FF07                      /*上7次C相失流数据块*/
#define CLossC_Curr_FF_8                        0x1803FF08                      /*上8次C相失流数据块*/
#define CLossC_Curr_FF_9                        0x1803FF09                      /*上9次C相失流数据块*/
#define CLossC_Curr_FF_10                       0x1803FF0A                      /*上10次C相失流数据块*/
#define CLossC_Curr_FF_FF                       0x1803FFFF                      /*上1-上10次C相失流数据块*/
/******************************************************************************/
/*过流*/
#define COver_Curr_OADTab                       0x30050200                      /*过流OAD关联列表，A、B、C共用关联列表*/
#define COverA_Curr_DegreeCurr                  0x30050302                      /*A相过流总次数,当前值*/
#define COverB_Curr_DegreeCurr                  0x30050303                      /*B相过流总次数,当前值*/
#define COverC_Curr_DegreeCurr                  0x30050304                      /*C相过流总次数,当前值*/
#define COverCurr_Curr_LowLim                   0x30050501                      /*过流事件电流触发下限*/
#define COverCurr_Delay_T                       0x30050502                      /*过流事件判断延时时间*/
#define COverACurr_FF_1                         0x30050701                      /*上1次A相过流数据块*/
#define COverBCurr_FF_1                         0x30050801                      /*上1次B相过流数据块*/
#define COverCCurr_FF_1                         0x30050901                      /*上1次C相过流数据块*/
#define COverA_Curr_Current                     0x30050A02                      /*A相过流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverB_Curr_Current                     0x30050A03                      /*B相过流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverC_Curr_Current                     0x30050A04                      /*C相过流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverCurr_Report_Mode                   0x30050B00                      /*过流上报模式字*/
#define COverA_Curr_Attri14                     0x30050E02                      /*A相过流*/
#define COverB_Curr_Attri14                     0x30050E03                      /*B相过流*/
#define COverC_Curr_Attri14                     0x30050E04                      /*C相过流*/
#define COverCurr_Report_Type                   0x30050F00                      /*过流上报类型*/
/*过流-645*/
#define COverA_Curr_Degree_645                  0x19010001                      /*A相过流总次数*/
#define COverB_Curr_Degree_645                  0x19020001                      /*B相过流总次数*/
#define COverC_Curr_Degree_645                  0x19030001                      /*C相过流总次数*/

#define COverA_Curr_Hp_1                        0x19010101                      /*上1次A相过流发生时刻*/
#define COverACurr_HpData_1                     0x1901FC01                      /*上1次A相过流发生数据*/
#define COverACurr_EndData_1                    0x1901FD01                      /*上1次A相过流结束数据*/
#define COverA_Curr_FF_1                        0x1901FF01                      /*上1次A相过流数据块*/
#define COverA_Curr_FF_2                        0x1901FF02                      /*上2次A相过流数据块*/
#define COverA_Curr_FF_3                        0x1901FF03                      /*上3次A相过流数据块*/
#define COverA_Curr_FF_4                        0x1901FF04                      /*上4次A相过流数据块*/
#define COverA_Curr_FF_5                        0x1901FF05                      /*上5次A相过流数据块*/
#define COverA_Curr_FF_6                        0x1901FF06                      /*上6次A相过流数据块*/
#define COverA_Curr_FF_7                        0x1901FF07                      /*上7次A相过流数据块*/
#define COverA_Curr_FF_8                        0x1901FF08                      /*上8次A相过流数据块*/
#define COverA_Curr_FF_9                        0x1901FF09                      /*上9次A相过流数据块*/
#define COverA_Curr_FF_10                       0x1901FF0A                      /*上10次A相过流数据块*/
#define COverA_Curr_FF_FF                       0x1901FFFF                      /*上1次-上10次A相过流数据块*/
#define COverB_Curr_Hp_1                        0x19020101                      /*上1次B相过流发生时刻*/
#define COverBCurr_HpData_1                     0x1902FC01                      /*上1次B相过流发生数据*/
#define COverBCurr_EndData_1                    0x1902FD01                      /*上1次B相过流结束数据*/
#define COverB_Curr_FF_1                        0x1902FF01                      /*上1次B相过流数据块*/
#define COverB_Curr_FF_2                        0x1902FF02                      /*上2次B相过流数据块*/
#define COverB_Curr_FF_3                        0x1902FF03                      /*上3次B相过流数据块*/
#define COverB_Curr_FF_4                        0x1902FF04                      /*上4次B相过流数据块*/
#define COverB_Curr_FF_5                        0x1902FF05                      /*上5次B相过流数据块*/
#define COverB_Curr_FF_6                        0x1902FF06                      /*上6次B相过流数据块*/
#define COverB_Curr_FF_7                        0x1902FF07                      /*上7次B相过流数据块*/
#define COverB_Curr_FF_8                        0x1902FF08                      /*上8次B相过流数据块*/
#define COverB_Curr_FF_9                        0x1902FF09                      /*上9次B相过流数据块*/
#define COverB_Curr_FF_10                       0x1902FF0A                      /*上10次B相过流数据块*/
#define COverB_Curr_FF_FF                       0x1902FFFF                      /*上1次-上10次B相过流数据块*/
#define COverC_Curr_Hp_1                        0x19030101                      /*上1次C相过流发生时刻*/
#define COverCCurr_HpData_1                     0x1903FC01                      /*上1次C相过流发生数据*/
#define COverCCurr_EndData_1                    0x1903FD01                      /*上1次C相过流结束数据*/
#define COverC_Curr_FF_1                        0x1903FF01                      /*上1次C相过流数据块*/
#define COverC_Curr_FF_2                        0x1903FF02                      /*上2次C相过流数据块*/
#define COverC_Curr_FF_3                        0x1903FF03                      /*上3次C相过流数据块*/
#define COverC_Curr_FF_4                        0x1903FF04                      /*上4次C相过流数据块*/
#define COverC_Curr_FF_5                        0x1903FF05                      /*上5次C相过流数据块*/
#define COverC_Curr_FF_6                        0x1903FF06                      /*上6次C相过流数据块*/
#define COverC_Curr_FF_7                        0x1903FF07                      /*上7次C相过流数据块*/
#define COverC_Curr_FF_8                        0x1903FF08                      /*上8次C相过流数据块*/
#define COverC_Curr_FF_9                        0x1903FF09                      /*上9次C相过流数据块*/
#define COverC_Curr_FF_10                       0x1903FF0A                      /*上10次C相过流数据块*/
#define COverC_Curr_FF_FF                       0x1903FFFF                      /*上1次-上10次C相过流数据块*/
/******************************************************************************/
/*断流*/
#define CBreak_Curr_OADTab                      0x30060200                      /*断流OAD关联列表，A、B、C共用关联列表*/
#define CBreakA_Curr_DegreeCurr                 0x30060302                      /*A相断流总次数,当前值*/
#define CBreakB_Curr_DegreeCurr                 0x30060303                      /*B相断流总次数,当前值*/
#define CBreakC_Curr_DegreeCurr                 0x30060304                      /*C相断流总次数,当前值*/
#define CBreakCurr_Vol_LowLim                   0x30060501                      /*断流事件电压触发下限*/
#define CBreakCurr_Curr_UpLim                   0x30060502                      /*断流事件电流触发上限*/
#define CBreakCurr_Delay_T                      0x30060503                      /*断流事件判定延时时间*/
#define CBreakACurr_FF_1                        0x30060701                      /*上1次A相断流数据块*/
#define CBreakBCurr_FF_1                        0x30060801                      /*上1次B相断流数据块*/
#define CBreakCCurr_FF_1                        0x30060901                      /*上1次C相断流数据块*/
#define CBreakA_Curr_Current                    0x30060A02                      /*A相过流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CBreakB_Curr_Current                    0x30060A03                      /*B相过流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CBreakC_Curr_Current                    0x30060A04                      /*C相过流当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CBreakCurr_Report_Mode                  0x30060B00                      /*断流上报模式字*/
#define CBreakA_Curr_Attri14                    0x30060E02                      /*A相断流*/
#define CBreakB_Curr_Attri14                    0x30060E03                      /*B相断流*/
#define CBreakC_Curr_Attri14                    0x30060E04                      /*C相断流*/
#define CBreakCurr_Report_Type                  0x30060F00                      /*断流上报类型*/
/*断流-645*/
#define CBreakA_Curr_Degree_645                 0x1A010001                      /*A相断流总次数*/
#define CBreakB_Curr_Degree_645                 0x1A020001                      /*B相断流总次数*/
#define CBreakC_Curr_Degree_645                 0x1A030001                      /*C相断流总次数*/

#define CBreakA_Curr_Hp_1                       0x1A010101                      /*上1次A相断流发生时刻*/
#define CBreakACurr_HpData_1                    0x1A01FC01                      /*上1次A相断流发生数据*/
#define CBreakACurr_EndData_1                   0x1A01FD01                      /*上1次A相断流结束数据*/
#define CBreakB_Curr_Hp_1                       0x1A020101                      /*上1次B相断流发生时刻*/
#define CBreakBCurr_HpData_1                    0x1A02FC01                      /*上1次B相断流发生数据*/
#define CBreakBCurr_EndData_1                   0x1A02FD01                      /*上1次B相断流结束数据*/
#define CBreakC_Curr_Hp_1                       0x1A030101                      /*上1次C相断流发生时刻*/
#define CBreakCCurr_HpData_1                    0x1A03FC01                      /*上1次C相断流发生数据*/
#define CBreakCCurr_EndData_1                   0x1A03FD01                      /*上1次C相断流结束数据*/
/******************************************************************************/
/*功率反向*/
#define CPower_Rev_OADTab                       0x30070200                      /*功率反向OAD关联列表，A、B、C共用关联列表*/
#define CPowerT_Rev_DegreeCurr                  0x30070301                      /*总相功率反向总次数,当前值*/
#define CPowerA_Rev_DegreeCurr                  0x30070302                      /*A相功率反向总次数,当前值*/
#define CPowerB_Rev_DegreeCurr                  0x30070303                      /*B相功率反向总次数,当前值*/
#define CPowerC_Rev_DegreeCurr                  0x30070304                      /*C相功率反向总次数,当前值*/
#define CTrendRev_AcPower_LowLim                0x30070501                      /*潮流反向事件有功功率触发下限*/
#define CTrendRev_Delay_T                       0x30070502                      /*潮流反向事件判定延时时间*/
#define CPowerRev_AcPower_LowLim                0x30070501                      /*功率反向事件有功功率触发下限*/
#define CPowerRev_Delay_T                       0x30070502                      /*功率反向事件判定延时时间*/
#define CPowerTRev_FF_1                         0x30070601                      /*上1次总功率反向数据块*/
#define CPowerARev_FF_1                         0x30070701                      /*上1次A相功率反向数据块*/
#define CPowerBRev_FF_1                         0x30070801                      /*上1次B相功率反向数据块*/
#define CPowerCRev_FF_1                         0x30070901                      /*上1次C相功率反向数据块*/
#define CPower_Rev_Current                      0x30070A00                      /*功率反向当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPowerT_Rev_Current                     0x30070A01                      /*总相功率反向当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPowerA_Rev_Current                     0x30070A02                      /*A相功率反向当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPowerB_Rev_Current                     0x30070A03                      /*B相功率反向当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPowerC_Rev_Current                     0x30070A04                      /*C相功率反向当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPowerRev_Report_Mode                   0x30070B00                      /*潮流反向上报模式字*/
#define CPowerT_Rev_Attri14                     0x30070E01                      /*总功率反向*/
#define CPowerA_Rev_Attri14                     0x30070E02                      /*A相功率反向*/
#define CPowerB_Rev_Attri14                     0x30070E03                      /*B相功率反向*/
#define CPowerC_Rev_Attri14                     0x30070E04                      /*C相功率反向*/
#define CPowerRev_Report_Type                   0x30070F00                      /*潮流反向上报类型*/
/*功率反向-645*/
#define CPowerT_Rev_Degree_645                  0x1B000001                      /*总相功率反向总次数*/
#define CPowerA_Rev_Degree_645                  0x1B010001                      /*A相功率反向总次数*/
#define CPowerB_Rev_Degree_645                  0x1B020001                      /*B相功率反向总次数*/
#define CPowerC_Rev_Degree_645                  0x1B030001                      /*C相功率反向总次数*/
/*潮流反向-645*/
#define CTrend_Rev_Degree                       0x21000000                      /*潮流反向总次数*/

#define CPowerT_Rev_Hp_1                        0x1B000101	                    /*上1次总功率反向发生时刻*/
#define CPowerTRev_HpData_1                     0x1B00FC01	                    /*上1次总功率反向发生数据*/
#define CPowerTRev_EndData_1                    0x1B00FD01	                    /*上1次总功率反向结束数据*/
#define CPowerA_Rev_Hp_1                        0x1B010101	                    /*上1次A相功率反向发生时刻*/
#define CPowerARev_HpData_1                     0x1B01FC01	                    /*上1次A相功率反向发生数据*/
#define CPowerARev_EndData_1                    0x1B01FD01	                    /*上1次A相功率反向结束数据*/
#define CPowerB_Rev_Hp_1                        0x1B020101	                    /*上1次B相功率反向发生时刻*/
#define CPowerBRev_HpData_1                     0x1B02FC01	                    /*上1次B相功率反向发生数据*/
#define CPowerBRev_EndData_1                    0x1B02FD01	                    /*上1次B相功率反向结束数据*/
#define CPowerC_Rev_Hp_1                        0x1B030101	                    /*上1次C相功率反向发生时刻*/
#define CPowerCRev_HpData_1                     0x1B03FC01	                    /*上1次C相功率反向发生数据*/
#define CPowerCRev_EndData_1                    0x1B03FD01	                    /*上1次C相功率反向结束数据*/
/******************************************************************************/
/*过载*/
#define COver_Lo_OADTab                         0x30080200                      /*过载OAD关联列表，A、B、C共用关联列表*/
#define COverA_Lo_DegreeCurr                    0x30080302                      /*A相过载总次数,当前值*/
#define COverB_Lo_DegreeCurr                    0x30080303                      /*B相过载总次数,当前值*/
#define COverC_Lo_DegreeCurr                    0x30080304                      /*C相过载总次数,当前值*/
#define COverLoad_AcPower_LowLim                0x30080501                      /*过载事件有功功率触发下限*/
#define COverLoad_Delay_T                       0x30080502                      /*过载事件判定延时时间*/
#define COverALo_FF_1                           0x30080701                      /*上1次A相过载数据块*/
#define COverBLo_FF_1                           0x30080801                      /*上1次B相过载数据块*/
#define COverCLo_FF_1                           0x30080901                      /*上1次C相过载数据块*/
#define COverA_Lo_Current                       0x30080A02                      /*A相过载当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverB_Lo_Current                       0x30080A03                      /*B相过载当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverC_Lo_Current                       0x30080A04                      /*C相过载当前值记录表∷=array 当前值,总次数，总累计时间*/
#define COverLoad_Report_Mode                   0x30080B00                      /*过载上报模式字*/
#define COverA_Lo_Attri14                       0x30080E02                      /*A相过载*/
#define COverB_Lo_Attri14                       0x30080E03                      /*B相过载*/
#define COverC_Lo_Attri14                       0x30080E04                      /*C相过载*/
#define COverLoad_Report_Type                   0x30080F00                      /*过载上报类型*/
/*过载-645*/
#define COverA_Lo_Degree_645                    0x1C010001                      /*A相过载总次数*/
#define COverB_Lo_Degree_645                    0x1C020001                      /*B相过载总次数*/
#define COverC_Lo_Degree_645                    0x1C030001                      /*C相过载总次数*/

#define COverA_Lo_Hp_1                          0x1C010101                      /*上1次A相过载发生时刻*/
#define COverALo_HpData_1                       0x1C01FC01                      /*上1次A相过载发生数据*/
#define COverALo_EndData_1                      0x1C01FD01                      /*上1次A相过载结束数据*/
#define COverB_Lo_Hp_1                          0x1C020101                      /*上1次B相过载发生时刻*/
#define COverBLo_HpData_1                       0x1C02FC01                      /*上1次B相过载发生数据*/
#define COverBLo_EndData_1                      0x1C02FD01                      /*上1次B相过载结束数据*/
#define COverC_Lo_Hp_1                          0x1C030101                      /*上1次C相过载发生时刻*/
#define COverCLo_HpData_1                       0x1C03FC01                      /*上1次C相过载发生数据*/
#define COverCLo_EndData_1                      0x1C03FD01                      /*上1次C相过载结束数据*/
/******************************************************************************/
/*正向有功需量超限*/
#define CPos_Ac_De_Over_Note_1                  0x30090201                      /*上1次正向有功需量超限记录*/
#define CPos_Ac_De_Over_OADTab                  0x30090300                      /*正向有功需量超限可变OAD关联列表*/
#define CPos_Ac_De_Over_DegreeCurr              0x30090400                      /*正向有功需量超限总次数，当前值*/
#define CPosAcDemandOv_De_LowLim                0x30090601                      /*有功需量超限事件需量触发下限，用于698正向*/
#define CPosAcDemandOv_Delay_T                  0x30090602                      /*需量超限事件判定延时时间，用于698正向*/
#define CPos_Ac_De_Over_Current                 0x30090700                      /*正向有功需量超限当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CPos_Ac_De_Over                         0x30090702                      /*正向有功需量超限总次数，总累计时间*/
#define CPosAcDemandOv_Report_Mode              0x30090800                      /*正向有功需量超限事件上报模式字*/
#define CPos_Ac_De_Over_Attri7                  0x30090A00                      /*正向有功需量超限*/
#define CPosAcDemandOv_Report_Type              0x30090B00                      /*正向有功需量超限事件上报类型*/
/*正向有功需量超限-645*/
#define CPos_Ac_De_Over_Degree_645              0x0312F900                      /*正向有功需量超限总次数*/

#define CPos_Ac_De_Over_Hp_1                    0x0312F101                      /*上1次正向有功需量超限发生时刻*/
#define CPos_Ac_De_Over_End_1                   0x0312F201                      /*上1次正向有功需量超限结束时刻*/
/******************************************************************************/
/*反向有功需量超限*/
#define CRev_Ac_De_Over_Note_1                  0x300A0201                      /*上1次反向有功需量超限记录*/
#define CRev_Ac_De_Over_OADTab                  0x300A0300                      /*反向有功需量超限可变OAD关联列表*/
#define CRev_Ac_De_Over_DegreeCurr              0x300A0400                      /*反向有功需量超限总次数，当前值*/
#define CRevAcDemandOv_De_LowLim                0x300A0601                      /*反向有功需量超限事件需量触发下限，698新增*/
#define CRevAcDemandOv_Delay_T                  0x300A0602                      /*反向有功需量超限事件判定延时时间，698新增*/
#define CRev_Ac_De_Over_Current                 0x300A0700                      /*反向有功需量超限当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CRev_Ac_De_Over                         0x300A0702                      /*反向有功需量超限总次数，总累计时间*/
#define CRevAcDemandOv_Report_Mode              0x300A0800                      /*反向有功需量超限事件上报模式字*/
#define CRev_Ac_De_Over_Attri7                  0x300A0A00                      /*反向有功需量超限*/
#define CRevAcDemandOv_Report_Type              0x300A0B00                      /*反向有功需量超限事件上报类型*/
/*反向有功需量超限-645*/
#define CRev_Ac_De_Over_Degree_645              0x0312FA00                      /*反向有功需量超限总次数*/

#define CRev_Ac_De_Over_Hp_1                    0x0312E101                      /*上1次反向有功需量超限发生时刻*/
#define CRev_Ac_De_Over_End_1                   0x0312E201                      /*上1次反向有功需量超限结束时刻*/
/******************************************************************************/
/*无功需量超限*/
#define CQua_Re_De_Over_OADTab                  0x300B0200                      /*无功需量超限可变OAD关联列表，1、2、3、4共用关联列表*/
#define CQua1_Re_De_Over_DegreeCurr             0x300B0301                      /*1象限无功需量超限总次数,当前值*/
#define CQua2_Re_De_Over_DegreeCurr             0x300B0302                      /*2象限无功需量超限总次数,当前值*/
#define CQua3_Re_De_Over_DegreeCurr             0x300B0303                      /*3象限无功需量超限总次数,当前值*/
#define CQua4_Re_De_Over_DegreeCurr             0x300B0304                      /*4象限无功需量超限总次数,当前值*/
#define CReDemandOv_De_LowLim                   0x300B0501                      /*无功需量超限事件需量触发下限*/
#define CReDemandOv_Delay_T                     0x300B0502                      /*无功需量超限事件判定延时时间，698新增*/
#define CQua1_Re_De_Over_Note_1                 0x300B0601                      /*上1次1象限无功需量超限记录*/
#define CQua2_Re_De_Over_Note_1                 0x300B0701                      /*上1次2象限无功需量超限记录*/
#define CQua3_Re_De_Over_Note_1                 0x300B0801                      /*上1次3象限无功需量超限记录*/
#define CQua4_Re_De_Over_Note_1                 0x300B0901                      /*上1次4象限无功需量超限记录*/
#define CQua_Re_De_Over_Current                 0x300B0A00                      /*无功需量超限当前值记录表∷=array 当前值,总次数，总累计时间,集合*/
#define CQua1_Re_De_Over_Current                0x300B0A01                      /*1象限无功需量超限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CQua2_Re_De_Over_Current                0x300B0A02                      /*2象限无功需量超限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CQua3_Re_De_Over_Current                0x300B0A03                      /*3象限无功需量超限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CQua4_Re_De_Over_Current                0x300B0A04                      /*4象限无功需量超限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CReDemandOv_Report_Mode                 0x300B0B00                      /*无功需量超限事件上报模式字*/
#define CQua1_Re_De_Over_Attri14                0x300B0E01                      /*I象限无功需量超限*/
#define CQua2_Re_De_Over_Attri14                0x300B0E02                      /*II象限无功需量超限*/
#define CQua3_Re_De_Over_Attri14                0x300B0E03                      /*III象限无功需量超限*/
#define CQua4_Re_De_Over_Attri14                0x300B0E04                      /*IV象限无功需量超限*/
#define CReDemandOv_Report_Type                 0x300B0F00                      /*无功需量超限事件上报类型*/

/*无功需量超限-645*/
#define CDe_Over_Degree                         0x03120000                      /*正、反有功、1-4无功需量超限总次数*/
#define CQua1_Re_De_Over_Degree_645             0x0312FB00                      /*1象限无功需量超限总次数*/
#define CQua2_Re_De_Over_Degree_645             0x0312FC00                      /*2象限无功需量超限总次数*/
#define CQua3_Re_De_Over_Degree_645             0x0312FD00                      /*3象限无功需量超限总次数*/
#define CQua4_Re_De_Over_Degree_645             0x0312FE00                      /*4象限无功需量超限总次数*/

#define CQua1_Re_De_Over_Hp_1                   0x0312D101                      /*上1次1象限无功需量超限发生时刻*/
#define CQua2_Re_De_Over_Hp_1                   0x0312C101                      /*上1次2象限无功需量超限发生时刻*/
#define CQua3_Re_De_Over_Hp_1                   0x0312B101                      /*上1次3象限无功需量超限发生时刻*/
#define CQua4_Re_De_Over_Hp_1                   0x0312A101                      /*上1次4象限无功需量超限发生时刻*/
#define CQua1_Re_De_Over_End_1                  0x0312D201                      /*上1次1象限无功需量超限结束时刻*/
#define CQua2_Re_De_Over_End_1                  0x0312C201                      /*上1次2象限无功需量超限结束时刻*/
#define CQua3_Re_De_Over_End_1                  0x0312B201                      /*上1次3象限无功需量超限结束时刻*/
#define CQua4_Re_De_Over_End_1                  0x0312A201                      /*上1次4象限无功需量超限结束时刻*/

#define CPos_Ac_De_Over_1                       0x0312F301                      /*上1次需量超限期间正向有功最大需量及发生时刻*/
#define CRev_Ac_De_Over_1                       0x0312E301                      /*上1次需量超限期间反向有功最大需量及发生时刻*/
#define CQua1_Re_De_Over_1                      0x0312D301                      /*上1次需量超限期间1象限无功最大需量及发生时刻*/
#define CQua2_Re_De_Over_1                      0x0312C301                      /*上1次需量超限期间2象限无功最大需量及发生时刻*/
#define CQua3_Re_De_Over_1                      0x0312B301                      /*上1次需量超限期间3象限无功最大需量及发生时刻*/
#define CQua4_Re_De_Over_1                      0x0312A301                      /*上1次需量超限期间4象限无功最大需量及发生时刻*/
/******************************************************************************/
/*全失压*/
#define CAll_Loss_Vol_Note_1                    0x300D0201                      /*上1次全失压记录*/
#define CAll_Loss_Vol_OADTab                    0x300D0300                      /*全失压可变OAD关联列表*/
#define CAll_Loss_Vol_DegreeCurr                0x300D0400                      /*全失压总次数，当前值*/
#define CAll_Loss_Vol_Current                   0x300D0700                      /*全失压当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CAll_Loss_Vol                           0x300D0702                      /*全失压总次数，总累计时间*/
#define CAllLossVolage_Report_Mode              0x300D0800                      /*全失压上报模式字*/
#define CAll_Loss_Vol_Attri7                    0x300D0A00                      /*全失压*/
#define CAllLossVolage_Report_Type              0x300D0B00                      /*全失压上报类型*/
/*全失压-645*/
/*03050000*/
#define CAll_Loss_Vol_Degree_645                0x0305FD00                      /*全失压总次数*/
/*03050001*/
#define CAll_Loss_Vol_Hp_1                      0x0305FD01                      /*上1次全失压发生时刻\电流值*/
#define CAll_Loss_Vol_End_1                     0x0305FE01                      /*上1次全失压结束时刻*/
/******************************************************************************/
/*辅助电源掉电*/
#define CAux_Pow_Down_Note_1                    0x300E0201                      /*上1次辅助电源掉电记录*/
#define CAux_Pow_Down_OADTab                    0x300E0300                      /*辅助电源可变OAD关联列表*/
#define CAux_Pow_Down_DegreeCurr                0x300E0400                      /*辅助电源失电总次数，当前值*/
#define CAux_Pow_Down_Delay_T                   0x300E0601                      /*辅助电源掉电判定延时时间*/
#define CAux_Pow_Down_Current                   0x300E0700                      /*辅助电源失电当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CAux_Pow_Down                           0x300E0702                      /*辅助电源失电总次数，总累计时间*/
#define CAuxPowDown_Report_Mode                 0x300E0800                      /*辅助电源失电上报模式字*/
#define CAux_Pow_Down_Attri7                    0x300E0A00                      /*辅助电源失电*/
#define CAuxPowDown_Report_Type                 0x300E0B00                      /*辅助电源失电上报类型*/
/*辅助电源掉电-645*/
#define CAux_Pow_Down_Degree_645                0x0306FD00                      /*总次数*/

#define CAux_Pow_Down_Hp_1                      0x0306FD01                      /*上1次辅助电源掉电发生时刻*/
#define CAux_Pow_Down_End_1                     0x0306FE01                      /*上1次辅助电源掉电结束时刻*/
/******************************************************************************/
/*电压逆相序*/
#define CRevPSVol_FF_1                          0x300F0201                      /*上1次电压逆相序数据块*/
#define CRevPS_Vol_OADTab                       0x300F0300                      /*电压逆相序可变OAD关联列表*/
#define CRevPS_Vol_DegreeCurr                   0x300F0400                      /*电压逆相序总次数,当前值*/
#define CReversedVoltage_Delay_T                0x300F0601                      /*电压逆相序事件判定延时时间*/
#define CRevPS_Vol_Current                      0x300F0700                      /*电压逆相序当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CRevPS_Vol                              0x300F0702                      /*电压逆相序总次数，总累计时间*/
#define CReversedVoltage_Report_Mode            0x300F0800                      /*电压逆相序上报模式字*/
#define CRevPS_Vol_Attri7                       0x300F0A00                      /*电压逆相序*/
#define CReversedVoltage_Report_Type            0x300F0B00                      /*电压逆相序上报类型*/
/*电压逆相序-645*/
#define CRevPS_Vol_Degree_645                   0x14000001                      /*电压逆相序总次数*/

#define CRevPS_Vol_Hp_1                         0x14000101                      /*上1次电压逆相序发生时刻*/
#define CRevPSVol_HpData_1                      0x1400FC01                      /*上1次电压逆相序发生数据*/
#define CRevPSVol_EndData_1                     0x1400FD01                      /*上1次电压逆相序结束数据*/
/******************************************************************************/
/*电流逆相序*/
#define CRevPSCurr_FF_1                         0x30100201                      /*上1次电流逆相序数据块*/
#define CRevPS_Curr_OADTab                      0x30100300                      /*电流逆相序可变OAD关联列表*/
#define CRevPS_Curr_DegreeCurr                  0x30100400                      /*电流逆相序总次数,当前值*/
#define CReversedCurrent_Delay_T                0x30100601                      /*电流逆相序事件判定延时时间*/
#define CRevPS_Curr_Current                     0x30100700                      /*电流逆相序当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CRevPS_Curr                             0x30100702                      /*电流逆相序总次数，总累计时间*/
#define CReversedCurrent_Report_Mode            0x30100800                      /*电流逆相序上报模式字*/
#define CRevPS_Curr_Attri7                      0x30100A00                      /*电流逆相序*/
#define CReversedCurrent_Report_Type            0x30100B00                      /*电流逆相序上报类型*/
/*电流逆相序-645*/
#define CRevPS_Curr_Degree_645                  0x15000001                      /*电流逆相序总次数*/

#define CRevPS_Curr_Hp_1                        0x15000101                      /*上1次电流逆相序发生时刻*/
#define CRevPSCurr_HpData_1                     0x1500FC01                      /*上1次电流逆相序发生数据*/
#define CRevPSCurr_EndData_1                    0x1500FD01                      /*上1次电流逆相序结束数据*/
/******************************************************************************/
/*掉电*/
#define CPow_Down_Note_1                        0x30110201                      /*上1次掉电记录*/
#define CPow_Down_OADTab                        0x30110300                      /*掉电可变OAD关联列表*/
#define CPow_Down_DegreeCurr                    0x30110400                      /*掉电总次数，当前值*/
#define CPowerOff_Delay_T                       0x30110601                      /*掉电事件判定延时时间*/
#define CPow_Down_Current                       0x30110700                      /*掉电当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CPow_Down                               0x30110702                      /*掉电总次数，总累计时间*/
#define CPowerOff_Report_Mode                   0x30110800                      /*掉电上报模式字*/
#define CPow_Down_Attri7                        0x30110A00                      /*掉电*/
#define CPowerOff_Report_Type                   0x30110B00                      /*掉电上报类型*/
/*掉电-645*/
#define CPow_Down_Degree_645                    0x03110000                      /*掉电总次数*/

#define CPow_Down_Hp_1                          0x0311FD01                      /*上1次掉电发生时刻*/
#define CPow_Down_End_1                         0x0311FE01                      /*上1次掉电结束时刻*/
/******************************************************************************/
/*编程记录*/
#define CProgram_Note_1                         0x30120201                      /*上1次编程记录*/
#define CProgram_OADTab                         0x30120300                      /*编程记录可变OAD关联列表*/
#define CProgram_DegreeCurr                     0x30120400                      /*编程记录总次数,当前值*/
#define CProgram_Current                        0x30120700                      /*编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgram                                0x30120702                      /*编程记录总次数，总累计时间*/
#define CProgram_Report_Mode                    0x30120800                      /*编程上报模式字*/
#define CProgram_Attri7                         0x30120A00                      /*编程*/
#define CProgram_Report_Type                    0x30120B00                      /*编程上报类型*/
/*编程记录-645*/
#define CProgram_Degree_645                     0x03300000                      /*编程记录总次数*/
/******************************************************************************/
/*电表总清*/
#define CTol_Clear_Note_MethodOne               0x30130100                      /*电表清零事件，方法1*/
#define CTol_Clear_Note_1                       0x30130201                      /*上1次电表清零记录*/
#define CTol_Clear_OADTab                       0x30130300                      /*总清可变OAD关联列表*/
#define CTol_Clear_DegreeCurr                   0x30130400                      /*电表清零总次数,当前值*/
#define CTol_Clear_Current                      0x30130700                      /*总清当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CTol_Clear                              0x30130702                      /*总清总次数，总累计时间*/
#define CTolClear_Report_Mode                   0x30130800                      /*电表清零上报模式字*/
#define CTol_Clear_Attri7                       0x30130A00                      /*清零*/
#define CTolClear_Report_Type                   0x30130B00                      /*电表清零上报类型*/
/*电表总清-645*/
#define CTol_Clear_Degree_645                   0x03300100                      /*电表清零总次数*/
/******************************************************************************/
/*需量清零*/
#define CDe_Clear_Note_1                        0x30140201                      /*上1次需量清零记录*/
#define CDe_Clear_OADTab                        0x30140300                      /*需清可变OAD关联列表*/
#define CDe_Clear_DegreeCurr                    0x30140400                      /*需量清零总次数,当前值*/
#define CDe_Clear_Current                       0x30140700                      /*需清当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CDe_Clear                               0x30140702                      /*需清总次数，总累计时间*/
#define CDemandClear_Report_Mode                0x30140800                      /*需量清零上报模式字*/
#define CDe_Clear_Attri7                        0x30140A00                      /*需量清零*/
#define CDemandClear_Report_Type                0x30140B00                      /*需量清零上报类型*/
/*需量清零-645*/
#define CDe_Clear_Degree_645                    0x03300200                      /*需量清零总次数*/

#define CDe_Clear_Note_1_645                    0x03300201                      /*645标识上1次需量清零记录,698兼容645增加*/
#define CDe_Clear_NoteE_1                       0x033002E1                      /*上1次需量清零记录自扩E*/
#define CDe_Clear_NoteF_1                       0x033002F1                      /*上1次需量清零记录自扩F*/
/******************************************************************************/
/*事件清零*/
#define CEven_Clear_Note_MethodOne              0x30150100                      /*事件清零记录,方法1*/
#define CEven_Clear_Degree_698                  0x30150200                      /*事件清零,698*/
#define CEven_Clear_Note_1                      0x30150201                      /*上1次事件清零记录*/
#define CEven_Clear_OADTab                      0x30150300                      /*事件清零可变OAD关联列表*/
#define CEven_Clear_DegreeCurr                  0x30150400                      /*事件清零总次数,当前值*/
#define CEven_Clear_Current                     0x30150700                      /*事件清零当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CEven_Clear                             0x30150702                      /*事件清零总次数，总累计时间*/
#define CEventClear_Report_Mode                 0x30150800                      /*事件清零上报模式字*/
#define CEven_Clear_Attri7                      0x30150A00                      /*事件清零*/
#define CEventClear_Report_Type                 0x30150B00                      /*事件清零上报类型*/
/*事件清零-645*/
#define CEven_Clear_Degree_645                  0x03300300                      /*事件清零总次数*/
/******************************************************************************/
/*校时记录*/
#define CAdjTime_Note_1                         0x30160201                      /*上1次校时记录*/
#define CAdjTime_OADTab                         0x30160300                      /*校时记录可变OAD关联列表*/
#define CAdjTime_DegreeCurr                     0x30160400                      /*校时记录总次数,当前值*/
#define CAdjTime_Current                        0x30160700                      /*校时记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CAdjTime                                0x30160702                      /*校时记录总次数，总累计时间*/
#define CAdjTime_Report_Mode                    0x30160800                      /*校时上报模式字*/
#define CAdjTime_Attri7                         0x30160A00                      /*校时*/
#define CAdjTime_Report_Type                    0x30160B00                      /*校时上报类型*/
/*校时记录-645*/
#define CAdjTime_Degree_645                     0x03300400                      /*校时记录总次数*/
/******************************************************************************/
/*时段表编程记录*/
#define CProgPT_Note_1                          0x30170201                      /*上1次时段表编程记录*/
#define CProgPT_OADTab                          0x30170300                      /*时段表记录可变OAD关联列表*/
#define CProgPT_DegreeCurr                      0x30170400                      /*时段表编程记录总次数,当前值*/
#define CProgPT_Current                         0x30170700                      /*时段表记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgPT                                 0x30170702                      /*时段表记录总次数，总累计时间*/
#define CProgPT_Report_Mode                     0x30170800                      /*时段表编程上报模式字*/
#define CProgPT_Attri7                          0x30170A00                      /*时段表编程*/
#define CProgPT_Report_Type                     0x30170B00                      /*时段表编程上报类型*/
/*时段表编程记录-645*/
#define CProgPT_Degree_645                      0x03300500                      /*时段表编程记录总次数*/

#define CProgOAD                                0xFFFF0001                      /*编程对象OAD，类似编程时段表对象 OAD，数据层支持列读*/
/*山东双协议增加,用于645协议存储记录中当前套时段表*/
#define CProgPT_CurrentPart_Note_1              0x03300501                      /*上1次时段表编程记录自扩*/
/******************************************************************************/
/*时区表编程记录*/
#define CProgTZ_Note_1                          0x30180201                      /*上1次时区表编程记录*/
#define CProgTZ_OADTab                          0x30180300                      /*时区表记录可变OAD关联列表*/
#define CProgTZ_DegreeCurr                      0x30180400                      /*时区表编程记录总次数,当前值*/
#define CProgTZ_Current                         0x30180700                      /*时区表记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgTZ                                 0x30180702                      /*时区表记录总次数，总累计时间*/
#define CProgPZ_Report_Mode                     0x30180800                      /*时区表编程上报模式字*/
#define CProgTZ_Attri7                          0x30180A00                      /*时区表编程*/
#define CProgPZ_Report_Type                     0x30180B00                      /*时区表编程上报类型*/
/*时区表编程记录-645*/
#define CProgTZ_Degree_645                      0x03300600                      /*时区表编程记录总次数*/
/******************************************************************************/
/*周休日编程记录*/
#define CProgWRe_Note_1                         0x30190201                      /*上1次周休日编程记录*/
#define CProgWRe_OADTab                         0x30190300                      /*周休日编程记录可变OAD关联列表*/
#define CProgWRe_DegreeCurr                     0x30190400                      /*周休日编程记录总次数,当前值*/
#define CProgWRe_Current                        0x30190700                      /*周休日编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgWRe                                0x30190702                      /*周休日编程记录总次数，总累计时间*/
#define CProgWRe_Report_Mode                    0x30190800                      /*周休日编程上报模式字*/
#define CProgWRe_Attri7                         0x30190A00                      /*周休日编程*/
#define CProgWRe_Report_Type                    0x30190B00                      /*周休日编程上报类型*/
/*周休日编程记录-645*/
#define CProgWRe_Degree_645                     0x03300700                      /*周休日编程记录总次数*/
/******************************************************************************/
/*结算日编程记录*/
#define CProgSettD_Note_1                       0x301A0201                      /*上1次结算日编程记录*/
#define CProgSettD_OADTab                       0x301A0300                      /*结算日编程记录可变OAD关联列表*/
#define CProgSettD_DegreeCurr                   0x301A0400                      /*结算日编程记录总次数,当前值*/
#define CProgSettD_Current                      0x301A0700                      /*结算日编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgSettD                              0x301A0702                      /*结算日编程记录总次数，总累计时间*/
#define CProgSettD_Report_Mode                  0x301A0800                      /*结算日编程上报模式字*/
#define CProgSettD_Attri7                       0x301A0A00                      /*结算日编程*/
#define CProgSettD_Report_Type                  0x301A0B00                      /*结算日编程上报类型*/
/*结算日编程记录-645*/
#define CProgSettD_Degree_645                   0x03300C00                      /*结算日编程记录总次数*/
/******************************************************************************/
/*开表盖记录*/
#define COpenW_Note_1                           0x301B0201                      /*上1次开表盖记录*/
#define COpenW_OADTab                           0x301B0300                      /*开表盖记录可变OAD关联列表*/
#define COpenW_DegreeCurr                       0x301B0400                      /*开表盖记录总次数,当前值*/
#define COpenW_Current                          0x301B0700                      /*开表盖记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define COpenW                                  0x301B0702                      /*开表盖记录总次数，总累计时间*/
#define COpenW_Report_Mode                      0x301B0800                      /*开表盖上报模式字*/
#define COpenW_Attri7                           0x301B0A00                      /*开表盖*/
#define COpenW_Report_Type                      0x301B0B00                      /*开表盖上报类型*/
/*开表盖记录-645*/
#define COpenW_Degree_645                       0x03300D00                      /*开表盖记录总次数*/
/******************************************************************************/
/*开端钮盖记录*/
#define COpenCW_Note_1                          0x301C0201                      /*上1次开端钮盖记录*/
#define COpenCW_OADTab                          0x301C0300                      /*开端钮盖记录可变OAD关联列表*/
#define COpenCW_DegreeCurr                      0x301C0400                      /*开端钮盖记录总次数,当前值*/
#define COpenCW_Current                         0x301C0700                      /*开端钮盖记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define COpenCW                                 0x301C0702                      /*开端钮盖记录总次数，总累计时间*/
#define COpenCW_Report_Mode                     0x301C0800                      /*开端钮盖上报模式字*/
#define COpenCW_Attri7                          0x301C0A00                      /*开端钮盖*/
#define COpenCW_Report_Type                     0x301C0B00                      /*开端钮盖上报类型*/
/*开端钮盖记录-645*/
#define COpenCW_Degree_645                      0x03300E00                      /*开端钮盖记录总次数*/
/******************************************************************************/
/*电压不平衡*/
#define CNoBalVol_FF_1                          0x301D0201                      /*上1次电压不平衡数据块*/
#define CNoBal_Vol_OADTab                       0x301D0300                      /*电压不平衡可变OAD关联列表*/
#define CNoBal_Vol_DegreeCurr                   0x301D0400                      /*电压不平衡总次数,当前值*/
#define CNoBal_Vol_Lim                          0x301D0601                      /*电压不平衡率限值*/
#define CNoBal_Vol_Delay_T                      0x301D0602                      /*电压不平衡率判定延时时间*/
#define CNoBal_Vol_Current                      0x301D0700                      /*电压不平衡当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CNoBal_Vol                              0x301D0702                      /*电压不平衡总次数，总累计时间*/
#define CNoBalVol_Report_Mode                   0x301D0800                      /*电压不平衡上报模式字*/
#define CNoBal_Vol_Attri7                       0x301D0A00                      /*电压不平衡*/
#define CNoBalVol_Report_Type                   0x301D0B00                      /*电压不平衡上报类型*/
/*电压不平衡-645*/
#define CNoBal_Vol_Degree_645                   0x16000001                      /*电压不平衡总次数*/

#define CNoBal_Vol_Hp_1                         0x16000101                      /*上1次电压不平衡发生时刻*/
#define CNoBalRate_Vol_End_1                    0x16001201                      /*上1次电压不平衡最大不平衡率*/
#define CNoBalVol_HpData_1                      0x1600FC01                      /*上1次电压不平衡发生数据*/
#define CNoBalVol_EndData_1                     0x1600FD01                      /*上1次电压不平衡结束数据*/
/******************************************************************************/
/*电流不平衡*/
#define CNoBalCurr_FF_1                         0x301E0201                      /*上1次电流不平衡数据块*/
#define CNoBal_Curr_OADTab                      0x301E0300                      /*电流不平衡可变OAD关联列表*/
#define CNoBal_Curr_DegreeCurr                  0x301E0400                      /*电流不平衡总次数,当前值*/
#define CNoBal_Curr_Lim                         0x301E0601                      /*电流不平衡率限值*/
#define CNoBal_Curr_Delay_T                     0x301E0602                      /*电流不平衡率判定延时时间*/
#define CNoBal_Curr_Current                     0x301E0700                      /*电流不平衡当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CNoBal_Curr                             0x301E0702                      /*电流不平衡总次数，总累计时间*/
#define CNoBalCurr_Report_Mode                  0x301E0800                      /*电流不平衡上报模式字*/
#define CNoBal_Curr_Attri7                      0x301E0A00                      /*电流不平衡*/
#define CNoBalCurr_Report_Type                  0x301E0B00                      /*电流不平衡上报类型*/
/*电流不平衡-645*/
#define CNoBal_Curr_Degree_645                  0x17000001                      /*电流不平衡总次数*/

#define CNoBal_Curr_Hp_1                        0x17000101                      /*上1次电流不平衡发生时刻*/
#define CNoBalRate_Curr_1                       0x17001201                      /*上1次电流不平衡最大不平衡率*/
#define CNoBalCurr_HpData_1                     0x1700FC01                      /*上1次电流不平衡发生数据*/
#define CNoBalCurr_EndData_1                    0x1700FD01                      /*上1次电流不平衡结束数据*/
/******************************************************************************/
/*跳闸记录*/
#define CRelayOpen_FF_1                         0x301F0201                      /*上1次跳闸记录数据块*/
#define CRelayOpen_OADTab                       0x301F0300                      /*跳闸可变OAD关联列表*/
#define CRelayOpen_DegreeCurr                   0x301F0400                      /*跳闸记录总次数,当前值*/
#define CRelayOpen_Current                      0x301F0700                      /*跳闸当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CRelayOpen                              0x301F0702                      /*跳闸总次数，总累计时间*/
#define CRelayOpen_Report_Mode                  0x301F0800                      /*跳闸上报模式字*/
#define CRelayOpen_Attri7                       0x301F0A00                      /*跳闸*/
#define CRelayOpen_Report_Type                  0x301F0B00                      /*跳闸上报类型*/
/*跳闸记录-645*/
#define CRelayOpen_Degree_645                   0x1D000001                      /*跳闸记录总次数*/

#define CRelayOpen_Hp_T_1                       0x1D000101                      /*上1次跳闸发生时刻*/
#define CRelayOpen_OpeCode_1                    0x1D000201                      /*上1次跳闸操作者代码*/
/******************************************************************************/
/*合闸记录*/
#define CRelayClose_FF_1                        0x30200201                      /*上1次合闸记录数据块*/
#define CRelayClose_OADTab                      0x30200300                      /*合闸可变OAD关联列表*/
#define CRelayClose_DegreeCurr                  0x30200400                      /*合闸记录总次数,当前值*/
#define CRelayClose_Current                     0x30200700                      /*合闸当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CRelayClose                             0x30200702                      /*合闸总次数，总累计时间*/
#define CRelayClose_Report_Mode                 0x30200800                      /*合闸上报模式字*/
#define CRelayClose_Attri7                      0x30200A00                      /*合闸*/
#define CRelayClose_Report_Type                 0x30200B00                      /*合闸上报类型*/
/*合闸记录-自扩*/
#define CRelayClose_Degree_645                  0x1E000001                      /*合闸记录总次数*/

#define CRelayClose_Hp_T_1                      0x1E000101                      /*上1次合闸发生时刻*/
/******************************************************************************/
/*节假日编程记录*/
#define CProgHol_Note_1                         0x30210201                      /*上1次节假日编程记录*/
#define CProgHol_OADTab                         0x30210300                      /*节假日编程记录可变OAD关联列表*/
#define CProgHol_DegreeCurr                     0x30210400                      /*节假日编程记录总次数,当前值*/
#define CProgHol_Current                        0x30210700                      /*节假日编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgHol                                0x30210702                      /*节假日编程记录总次数，总累计时间*/
#define CProgHol_Report_Mode                    0x30210800                      /*节假日编程上报模式字*/
#define CProgHol_Attri7                         0x30210A00                      /*节假日编程*/
#define CProgHol_Report_Type                    0x30210B00                      /*节假日编程上报类型*/
/*节假日编程记录-645*/
#define CProgHol_Degree_645                     0x03300800                      /*节假日编程记录总次数*/

#define CProgHol_Note9_1                        0x03300891                      /*上1次节假日编程记录自扩9*/
#define CProgHol_NoteA_1                        0x033008A1                      /*上1次节假日编程记录自扩A*/
#define CProgHol_NoteB_1                        0x033008B1                      /*上1次节假日编程记录自扩B*/
#define CProgHol_NoteC_1                        0x033008C1                      /*上1次节假日编程记录自扩C*/
#define CProgHol_NoteD_1                        0x033008D1                      /*上1次节假日编程记录自扩D*/
#define CProgHol_NoteE_1                        0x033008E1                      /*上1次节假日编程记录自扩E*/
/******************************************************************************/
/*有功组合方式编程记录*/
#define CProgAcC_Note_1                         0x30220201                      /*上1次有功组合方式编程记录*/
#define CProgAcC_OADTab                         0x30220300                      /*有功组合方式编程记录可变OAD关联列表*/
#define CProgAcC_DegreeCurr                     0x30220400                      /*有功组合方式编程记录总次数,当前值*/
#define CProgAcC_Current                        0x30220700                      /*有功组合方式编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgAcC                                0x30220702                      /*有功组合方式编程记录总次数，总累计时间*/
#define CProgAcC_Report_Mode                    0x30220800                      /*有功组合方式编程上报模式字*/
#define CProgAcC_Attri7                         0x30220A00                      /*有功组合方式特征字编程*/
#define CProgAcC_Report_Type                    0x30220B00                      /*有功组合方式编程上报类型*/
/*有功组合方式编程记录-645*/
#define CProgAcC_Degree_645                     0x03300900                      /*有功组合方式编程记录总次数*/
/******************************************************************************/
/*无功组合方式1编程记录*/
#define CProgReC_Note_1                         0x30230201                      /*上1次无功组合方式编程记录*/
#define CProgReC_OADTab                         0x30230300                      /*无功组合方式编程记录可变OAD关联列表*/
#define CProgReC_DegreeCurr                     0x30230400                      /*无功组合方式编程记录总次数,当前值*/
#define CProgReC_Current                        0x30230700                      /*无功组合方式编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgReC                                0x30230702                      /*无功组合方式编程记录总次数，总累计时间*/
#define CProgReC_Report_Mode                    0x30230800                      /*无功组合方式编程上报模式字*/
#define CProgReC_Attri7                         0x30230A00                      /*无功组合方式特征字编程*/
#define CProgReC_Report_Type                    0x30230B00                      /*无功组合方式编程上报类型*/
/*无功组合方式1编程记录-645*/
#define CProgReC_Degree_645                     0x03300A00                      /*无功组合方式编程记录总次数,包括无功1、无功2*/

#define CProgReC698_Note_1                      0x0330FA01                      /*上1次无功组合方式1编程记录*/
/******************************************************************************/
/*费率参数表编程记录*/
#define CProgTPara_Note_1                       0x30240201                      /*上1次费率参数表编程记录*/
#define CProgTPara_OADTab                       0x30240300                      /*费率参数表编程记录可变OAD关联列表*/
#define CProgTPara_DegreeCurr                   0x30240400                      /*费率参数表编程记录总次数,当前值*/
#define CProgTPara_Current                      0x30240700                      /*费率参数表编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgTPara                              0x30240702                      /*费率参数表编程记录总次数，总累计时间*/
#define CProgTPara_Report_Mode                  0x30240800                      /*费率参数表编程上报模式字*/
#define CProgTPara_Attri7                       0x30240A00                      /*费率参数表编程*/
#define CProgTPara_Report_Type                  0x30240B00                      /*费率参数表编程上报类型*/
/*费率参数表编程记录-645*/
#define CProgTPara_Degree_645                   0x03300F00                      /*费率参数表编程记录总次数*/
/******************************************************************************/
/*阶梯表编程记录*/
#define CProgLad_Note_1                         0x30250201                      /*上1次阶梯表编程记录*/
#define CProgLad_OADTab                         0x30250300                      /*阶梯表编程记录可变OAD关联列表*/
#define CProgLad_DegreeCurr                     0x30250400                      /*阶梯表编程记录总次数,当前值*/
#define CProgLad_Current                        0x30250700                      /*阶梯表编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgLad                                0x30250702                      /*阶梯表编程记录总次数，总累计时间*/
#define CProgLad_Report_Mode                    0x30250800                      /*阶梯表编程上报模式字*/
#define CProgLad_Attri7                         0x30250A00                      /*阶梯表编程*/
#define CProgLad_Report_Type                    0x30250B00                      /*阶梯表编程上报类型*/
/*阶梯表编程记录-645*/
#define CProgLad_Degree_645                     0x03301000                      /*阶梯表编程记录总次数*/
/******************************************************************************/
/*密钥编程记录*/
#define CProgKD_Note_1                          0x30260201                      /*上1次密钥编程记录*/
#define CProgKD_OADTab                          0x30260300                      /*密钥编程记录可变OAD关联列表*/
#define CProgKD_DegreeCurr                      0x30260400                      /*密钥编程记录总次数,当前值*/
#define CProgKD_Current                         0x30260700                      /*密钥编程记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CProgKD                                 0x30260702                      /*密钥编程记录总次数，总累计时间*/
#define CKey_Update_Report_Mode                 0x30260800                      /*密钥更新上报模式字*/
#define CProgKD_Attri7                          0x30260A00                      /*密钥更新*/
#define CKey_Update_Report_Type                 0x30260B00                      /*密钥更新上报类型*/
/*密钥编程记录-645*/
#define CProgKD_Degree_645                      0x03301200                      /*密钥编程记录总次数*/
/******************************************************************************/
/*异常插卡记录*/
#define CAbnorC_Note_1                          0x30270201                      /*上1次异常插卡记录*/
#define CAbnorC_OADTab                          0x30270300                      /*异常插卡记录可变OAD关联列表*/
#define CAbnorC_DegreeCurr                      0x30270400                      /*异常插卡记录总次数,当前值*/
#define CAbnorC_Current                         0x30270700                      /*异常插卡记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CAbnorC                                 0x30270702                      /*异常插卡记录总次数，总累计时间*/
#define CAbnorC_Report_Mode                     0x30270800                      /*异常插卡上报模式字*/
#define CAbnorC_Attri7                          0x30270A00                      /*异常插卡*/
#define CAbnorC_Report_Type                     0x30270B00                      /*异常插卡上报类型*/
#define CLawlessC_Degree                        0x30271D00                      /*非法插卡总次数*/
/*异常插卡记录-645*/
#define CAbnorC_Degree_645                      0x03301300                      /*异常插卡记录总次数*/

#define CAbnorC_NoteRelate4                     0xFFFF0004                      /*异常插卡记录相关数据包含：卡序列号、插卡错误信息字、插卡操作命令头、插卡错误响应状态*/
/******************************************************************************/
/*购电记录*/
#define CBuyCurr_T_1                            0x30280201                      /*上1次购电日期*/
#define CBuyCurr_FF_Note_1                      0x30280201                      /*上1次购电记录*/
#define CBuyCurr_OADTab                         0x30280300                      /*购电记录可变OAD关联列表*/
#define CBuyCurr_DegreeCurr                     0x30280400                      /*购电记录总次数,当前值*/
#define CBuyCurr_Current                        0x30280700                      /*购电记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CBuyCurr                                0x30280702                      /*购电记录总次数，总累计时间*/
#define CBuyCurr_Report_Mode                    0x30280800                      /*购电上报模式字*/
#define CBuyCurr_Attri7                         0x30280A00                      /*购电事件*/
#define CBuyCurr_Report_Type                    0x30280B00                      /*购电上报类型*/
/******************************************************************************/
/*退费记录*/
#define CReturn_M_Note_1                        0x30290201                      /*上1次退费记录*/
#define CReturn_M_OADTab                        0x30290300                      /*退费记录可变OAD关联列表*/
#define CReturn_M_DegreeCurr                    0x30290400                      /*退费记录总次数,当前值*/
#define CReturn_M_Current                       0x30290700                      /*退费记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CReturn_M                               0x30290702                      /*退费记录总次数，总累计时间*/
#define CReturnMoney_Report_Mode                0x30290800                      /*退费上报模式字*/
#define CReturn_M_Attri7                        0x30290A00                      /*退费事件*/
#define CReturnMoney_Report_Type                0x30290B00                      /*退费上报类型*/
/*退费记录-645*/
#define CReturn_M_Degree_645                    0x03340000                      /*退费记录总次数*/

#define CReturn_M_Sum3                          0xFFFF0003                      /*退费金额*/
/******************************************************************************/
/*恒定磁场干扰记录*/
#define CConM_Note_1                            0x302A0201                      /*上1次恒定磁场干扰记录*/
#define CConM_OADTab                            0x302A0300                      /*恒定磁场干扰可变OAD关联列表*/
#define CConM_DegreeCurr                        0x302A0400                      /*恒定磁场干扰总次数,当前值*/
#define CConM_Current                           0x302A0700                      /*恒定磁场干扰当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CConM                                   0x302A0702                      /*恒定磁场干扰总次数，总累计时间*/
#define CConMEndEn_Report_Mode                  0x302A0800                      /*恒定磁场干扰上报模式字*/
#define CConM_Attri7                            0x302A0A00                      /*恒定磁场干扰*/
#define CConMEndEn_Report_Type                  0x302A0B00                      /*恒定磁场干扰上报类型*/
/*恒定磁场干扰记录-645*/
#define CConM_Degree_645                        0x03350000                      /*恒定磁场干扰记录总次数*/
/******************************************************************************/
/*负荷开关误动作记录*/
#define CRelayFa_Note_1                         0x302B0201                      /*上1次负荷开关误动作记录*/
#define CRelayFa_OADTab                         0x302B0300                      /*负荷开关误动作可变OAD关联列表*/
#define CRelayFa_DegreeCurr                     0x302B0400                      /*负荷开关误动作总次数,当前值*/
#define CRelayFa_Current                        0x302B0700                      /*负荷开关误动作当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CRelayFa                                0x302B0702                      /*负荷开关误动作总次数，总累计时间*/
#define CRelayFaEndEn_Report_Mode               0x302B0800                      /*负荷开关误动作上报模式字*/
#define CRelayFa_Attri7                         0x302B0A00                      /*负荷开关误动作*/
#define CRelayFaEndEn_Report_Type               0x302B0B00                      /*负荷开关误动作上报类型*/
/*负荷开关误动作记录-645*/
#define CRelayFa_Degree_645                     0x03360000                      /*负荷开关误动作记录总次数*/
/******************************************************************************/
/*电源异常记录*/
#define CPowerFa_Note_1                         0x302C0201                      /*上1次电源异常记录*/
#define CPowerFa_OADTab                         0x302C0300                      /*电源异常可变OAD关联列表*/
#define CPowerFa_DegreeCurr                     0x302C0400                      /*电源异常总次数,当前值*/
#define CPowerFa_Current                        0x302C0700                      /*电源异常当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CPowerFa                                0x302C0702                      /*电源异常总次数，总累计时间*/
#define CPowerFa_EndT_Report_Mode               0x302C0800                      /*电源异常上报模式字*/
#define CPowerFa_Attri7                         0x302C0A00                      /*电源异常*/
#define CPowerFa_EndT_Report_Type               0x302C0B00                      /*电源异常上报类型*/
/*电源异常记录-645*/
#define CPowerFa_Degree_645                     0x03370000                      /*电源异常记录总次数*/
/******************************************************************************/
/*电流严重不平衡*/
#define CSevNoBalCurr_FF_1                      0x302D0201                      /*上1次电流严重不平衡数据块*/
#define CSevNoBal_Curr_OADTab                   0x302D0300                      /*电流严重不平衡可变OAD关联列表*/
#define CSevNoBal_Curr_DegreeCurr               0x302D0400                      /*电流严重不平衡总次数,当前值*/
#define CSeriNoBal_Curr_Lim                     0x302D0601                      /*电流严重不平衡率限值*/
#define CSeriNoBal_Curr_Delay_T                 0x302D0602                      /*电流严重不平衡率判定延时时间*/
#define CSevNoBal_Curr_Current                  0x302D0700                      /*电流严重不平衡当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CSevNoBal_Curr                          0x302D0702                      /*电流严重不平衡总次数，总累计时间*/
#define CSeriNoBalCurr_Report_Mode              0x302D0800                      /*电流严重不平衡上报模式字*/
#define CSevNoBal_Curr_Attri7                   0x302D0A00                      /*电流严重不平衡*/
#define CSeriNoBalCurr_Report_Type              0x302D0B00                      /*电流严重不平衡上报类型*/
/*电流严重不平衡-645*/
#define CSevNoBal_Curr_Degree_645               0x20000001                      /*电流严重不平衡总次数*/

#define CSevNoBal_Curr_Hp_1                     0x20000101                      /*上1次电流严重不平衡发生时刻*/
#define CSevNoBalRate_Curr_1                    0x20001201                      /*上1次电流严重不平衡最大不平衡率*/
/******************************************************************************/
/*时钟故障记录*/
#define CClockFa_Note_1                         0x302E0201                      /*上1次时钟故障记录*/
#define CClockFa_OADTab                         0x302E0300                      /*时钟故障可变OAD关联列表*/
#define CClockFa_DegreeCurr                     0x302E0400                      /*时钟故障总次数,当前值*/
#define CClockFa_Delay_T                        0x302E0601                      /*时钟故障判定延时时间*/
#define CClockFa_Current                        0x302E0700                      /*时钟故障当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CClockFa                                0x302E0702                      /*时钟故障总次数，总累计时间*/
#define CClockFault_Report_Mode                 0x302E0800                      /*时钟故障上报模式字*/
#define CClockFa_Attri7                         0x302E0A00                      /*时钟故障*/
#define CClockFault_Report_Type                 0x302E0B00                      /*时钟故障上报类型*/
/*时钟故障记录-645*/
#define CClockFa_Degree_645                     0x032E0000                      /*时钟故障记录总次数*/
/******************************************************************************/
/*计量芯片故障*/
#define CMeterFa_Note_1                         0x302F0201                      /*上1次计量芯片故障记录*/
#define CMeterFa_OADTab                         0x302F0300                      /*计量芯片故障可变OAD关联列表*/
#define CMeterFa_DegreeCurr                     0x302F0400                      /*计量芯片故障总次数,当前值*/
#define CMeterFa_Delay_T                        0x302F0601                      /*计量芯片故障判定延时时间*/
#define CMeterFa_Current                        0x302F0700                      /*计量芯片故障当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CMeterFa                                0x302F0702                      /*计量芯片故障总次数，总累计时间*/
#define CMeteringChipFault_Report_Mode          0x302F0800                      /*0x04001134计量芯片故障上报模式字*/
#define CMeterFa_Attri7                         0x302F0A00                      /*计量芯片故障*/
#define CMeteringChipFault_Report_Type          0x302F0B00                      /*0x04001134计量芯片故障上报类型*/
/*计量芯片故障-645*/
#define CMeterFa_Degree_645                     0x032F0000                      /*计量芯片故障记录总次数*/
/******************************************************************************/
/*总功率因数超下限*/
#define CPFactorT_Over_OADTab                   0x303B0200                      /*总功率因数超下限可变OAD关联列表*/
#define CPFactorT_Over_DegreeCurr               0x303B0301
#define CPFactorA_Over_DegreeCurr               0x303B0302
#define CPFactorB_Over_DegreeCurr               0x303B0303
#define CPFactorC_Over_DegreeCurr               0x303B0304
#define CPowerFactor_LowLim                     0x303B0501                      /*功率因数超下限阀值*/
#define CPowerFactor_Delay_T                    0x303B0502                      /*功率因素超下限判定延时时间*/
#define CPFactorT_FF_1                          0x303B0601                      /*上1次总功率因数超下限数据块*/
#define CPFactorA_FF_1                          0x303B0701                      /*上1次A功率因数超下限数据块*/
#define CPFactorB_FF_1                          0x303B0801                      /*上1次B功率因数超下限数据块*/
#define CPFactorC_FF_1                          0x303B0901                      /*上1次C功率因数超下限数据块*/
#define CPFactorT_Over_Current                  0x303B0A01                      /*总功率因数超下限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPFactorA_Over_Current                  0x303B0A02                      /*A相功率因数超下限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPFactorB_Over_Current                  0x303B0A03                      /*B相功率因数超下限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPFactorC_Over_Current                  0x303B0A04                      /*C相功率因数超下限当前值记录表∷=array 当前值,总次数，总累计时间*/
#define CPowerFactor_Report_Mode                0x303B0B00                      /*功率因数超下限事件上报模式字*/
#define CPFactorT_Over_Attri14                  0x303B0E01                      /*功率因数超限*/
#define CPFactorA_Over_Attri14                  0x303B0E02                      /*A功率因数超限*/
#define CPFactorB_Over_Attri14                  0x303B0E03                      /*B功率因数超限*/
#define CPFactorC_Over_Attri14                  0x303B0E04                      /*C功率因数超限*/
#define CPowerFactor_Report_Type                0x303B0F00                      /*功率因数超下限事件上报类型*/
/*总功率因数超下限-645*/
#define CPFactorT_Over_Degree_645               0x1F000001                      /*总功率因数超下限总次数*/
#define CPFactorA_Over_Degree_645               0x1F010001                      /*A相总功率因数超下限总次数*/
#define CPFactorB_Over_Degree_645               0x1F020001                      /*B相总功率因数超下限总次数*/
#define CPFactorC_Over_Degree_645               0x1F030001                      /*C相总功率因数超下限总次数*/

#define CPFactorT_Over_Hp_1                     0x1F000101                      /*上1次总功率因数超下限发生时刻*/
#define CPFactorT_HpData_1                      0x1F00FC01                      /*上1次总功率因数超下限发生数据*/
#define CPFactorT_EndData_1                     0x1F00FD01                      /*上1次总功率因数超下限结束数据*/
#define CPFactorA_Over_Hp_1                     0x1F010101                      /*上1次A相功率因数超下限发生时刻*/
#define CPFactorA_HpData_1                      0x1F01FC01                      /*上1次A相功率因数超下限发生数据*/
#define CPFactorA_EndData_1                     0x1F01FD01                      /*上1次A相功率因数超下限结束数据*/
#define CPFactorB_Over_Hp_1                     0x1F020101                      /*上1次B相功率因数超下限发生时刻*/
#define CPFactorB_HpData_1                      0x1F02FC01                      /*上1次B相功率因数超下限发生数据*/
#define CPFactorB_EndData_1                     0x1F02FD01                      /*上1次B相功率因数超下限结束数据*/
#define CPFactorC_Over_Hp_1                     0x1F030101                      /*上1次C相功率因数超下限发生时刻*/
#define CPFactorC_HpData_1                      0x1F03FC01                      /*上1次C相功率因数超下限发生数据*/
#define CPFactorC_EndData_1                     0x1F03FD01                      /*上1次C相功率因数超下限结束数据*/
/******************************************************************************/
/*广播校时记录*/
#define CBroadcastTime_Note_1                   0x303C0201                      /*上1次广播校时记录*/
#define CBroadcastTime_OADTab                   0x303C0300                      /*广播校时记录可变OAD关联列表*/
#define CBroadcastTime_DegreeCurr               0x303C0400                      /*广播校时记录总次数,当前值*/
#define CBroadcastTime_Current                  0x303C0700                      /*广播校时记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CBroadcastTime                          0x303C0702                      /*广播校时记录总次数，总累计时间*/
#define CBroadcastTime_Report_Mode              0x303C0800                      /*广播校时上报模式字*/
#define CBroadcastTime_Attri7                   0x303C0A00                      /*广播校时*/
#define CBroadcastTime_Report_Type              0x303C0B00                      /*广播校时上报类型*/
 /*广播校时记录-645*/
#define CBroadcastTime_Degree_645               0x03FC0000                      /*广播校时记录总次数*/
/******************************************************************************/
/*零线电流异常记录*/
#define CNeutralCurrentAbnormal_Note_1          0x30400201                      /*上1次零线电流异常事件记录*/
#define CNeutralCurrentAbnormal_OADTab          0x30400300                      /*零线电流异常事件记录可变OAD关联列表*/
#define CNeutralCurrentAbnormal_DegreeCurr      0x30400400                      /*零线电流异常事件记录总次数,当前值*/
#define CNeutralAbnormal_Curr_LowLim            0x30400601                      /*零线电流异常电流触发下限*/
#define CNeutralUnbalanceRate                   0x30400602                      /*零线电流异常不平衡率限值*/
#define CNeutralAbnormal_Delay_T                0x30400603                      /*零线电流异常判定延迟时间*/
#define CNeutralCurrentAbnormal_Current         0x30400700                      /*零线电流异常事件记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CNeutralCurrentAbnormal                 0x30400702                      /*零线电流异常事件记录总次数，总累计时间*/
#define CABnor_ZeroCurrent_Report_Mode          0x30400800                      /*零线电流异常上报模式字*/
#define CABnor_ZeroCurrent_Report_Type          0x30400B00                      /*零线电流异常上报类型*/
/*零线电流异常记录-645*/
#define CNeutralCurrentAbnormal_Degree_645      0x03FD0000                      /*零线电流异常事件记录总次数*/

#define CNeutralCurrentAbnormal_HpData_1        0x3040FC01                      /*上1次零线电流异常事件记录*/
#define CNeutralCurrentAbnormal_EndData_1       0x3040FD01                      /*上1次零线电流异常事件记录*/
#if 0
/******************************************************************************/
/*广播校时异常事件*/
#define CBroadTimeAbnormal_Note_1               0x30510201                      /*上1次广播校时异常记录*/
#define CBroadTimeAbnormal_OADTab               0x30510300                      /*广播校时异常记录可变OAD关联列表*/
#define CBroadTimeAbnormal_DegreeCurr           0x30510400                      /*广播校时异常记录总次数,当前值*/
#define CBroadTimeAbnormal_Current              0x30510700                      /*广播校时异常记录当前值记录表∷=array 当前值,总次数，总累计时间，包括发生源*/
#define CBroadTimeAbnormal                      0x30510702                      /*广播校时异常记录总次数，总累计时间*/
#define CBroadTimeAbnormal_Report_Mode          0x30510800                      /*广播校时异常上报模式字*/
#define CBroadTimeAbnormal_Report_Type          0x30510B00                      /*广播校时上报类型*/

/*广播校时异常事件-645*/
#define CBroadTimeAbnormal_Degree_645           0x03FF0000                      /*广播校时异常记录总次数*/
#endif
/******************************************************************************/
/*软IJ有效时间编程记录-645-自扩*/
#define CSoft_I_J_Prog_Degree                   0x03FE0000                      /*软IJ有效时间编程总次数*/
/******************************************************************************/
/*校表记录-645-自扩*/
#define CRec_Meter_Bef1_Data_1                  0x03FB0101                      /*上1次1号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_2                  0x03FB0201                      /*上1次2号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_3                  0x03FB0301                      /*上1次3号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_4                  0x03FB0401                      /*上1次4号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_5                  0x03FB0501                      /*上1次5号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_6                  0x03FB0601                      /*上1次6号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_7                  0x03FB0701                      /*上1次7号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_8                  0x03FB0801                      /*上1次8号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_9                  0x03FB0901                      /*上1次9号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_10                 0x03FB0A01                      /*上1次10号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_11                 0x03FB0B01                      /*上1次11号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_12                 0x03FB0C01                      /*上1次12号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_13                 0x03FB0D01                      /*上1次13号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_14                 0x03FB0E01                      /*上1次14号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_15                 0x03FB0F01                      /*上1次15号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_16                 0x03FB1001                      /*上1次16号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_17                 0x03FB1101                      /*上1次17号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_18                 0x03FB1201                      /*上1次18号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_19                 0x03FB1301                      /*上1次19号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_20                 0x03FB1401                      /*上1次20号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_21                 0x03FB1501                      /*上1次21号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_22                 0x03FB1601                      /*上1次22号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_23                 0x03FB1701                      /*上1次23号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_24                 0x03FB1801                      /*上1次24号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_25                 0x03FB1901                      /*上1次25号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_26                 0x03FB1A01                      /*上1次26号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_27                 0x03FB1B01                      /*上1次27号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_28                 0x03FB1C01                      /*上1次28号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_29                 0x03FB1D01                      /*上1次29号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_30                 0x03FB1E01                      /*上1次30号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_31                 0x03FB1F01                      /*上1次31号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_32                 0x03FB2001                      /*上1次32号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_33                 0x03FB2101                      /*上1次33号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_34                 0x03FB2201                      /*上1次34号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_35                 0x03FB2301                      /*上1次35号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_36                 0x03FB2401                      /*上1次36号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_37                 0x03FB2501                      /*上1次37号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_38                 0x03FB2601                      /*上1次38号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_39                 0x03FB2701                      /*上1次39号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_40                 0x03FB2801                      /*上1次40号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_41                 0x03FB2901                      /*上1次41号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_42                 0x03FB2A01                      /*上1次42号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_43                 0x03FB2B01                      /*上1次43号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_44                 0x03FB2C01                      /*上1次44号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_45                 0x03FB2D01                      /*上1次45号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_46                 0x03FB2E01                      /*上1次46号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_47                 0x03FB2F01                      /*上1次47号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_48                 0x03FB3001                      /*上1次48号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_49                 0x03FB3101                      /*上1次49号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_50                 0x03FB3201                      /*上1次50号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_51                 0x03FB3301                      /*上1次51号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_52                 0x03FB3401                      /*上1次52号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_53                 0x03FB3501                      /*上1次53号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_54                 0x03FB3601                      /*上1次54号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_55                 0x03FB3701                      /*上1次55号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_56                 0x03FB3801                      /*上1次56号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_57                 0x03FB3901                      /*上1次57号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_58                 0x03FB3A01                      /*上1次58号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_59                 0x03FB3B01                      /*上1次59号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_60                 0x03FB3C01                      /*上1次60号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_61                 0x03FB3D01                      /*上1次61号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_62                 0x03FB3E01                      /*上1次62号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_63                 0x03FB3F01                      /*上1次63号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_64                 0x03FB4001                      /*上1次64号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_65                 0x03FB4101                      /*上1次65号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_66                 0x03FB4201                      /*上1次66号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_67                 0x03FB4301                      /*上1次67号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_68                 0x03FB4401                      /*上1次68号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_69                 0x03FB4501                      /*上1次69号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_70                 0x03FB4601                      /*上1次70号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_71                 0x03FB4701                      /*上1次71号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_72                 0x03FB4801                      /*上1次72号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_73                 0x03FB4901                      /*上1次73号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_74                 0x03FB4A01                      /*上1次74号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_75                 0x03FB4B01                      /*上1次75号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_76                 0x03FB4C01                      /*上1次76号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_77                 0x03FB4D01                      /*上1次77号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_78                 0x03FB4E01                      /*上1次78号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_79                 0x03FB4F01                      /*上1次79号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_80                 0x03FB5001                      /*上1次80号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_81                 0x03FB5101                      /*上1次81号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_82                 0x03FB5201                      /*上1次82号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_83                 0x03FB5301                      /*上1次83号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_84                 0x03FB5401                      /*上1次84号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_85                 0x03FB5501                      /*上1次85号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_86                 0x03FB5601                      /*上1次86号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_87                 0x03FB5701                      /*上1次87号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_88                 0x03FB5801                      /*上1次88号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_89                 0x03FB5901                      /*上1次89号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_90                 0x03FB5A01                      /*上1次90号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_91                 0x03FB5B01                      /*上1次91号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_92                 0x03FB5C01                      /*上1次92号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_93                 0x03FB5D01                      /*上1次93号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_94                 0x03FB5E01                      /*上1次94号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_95                 0x03FB5F01                      /*上1次95号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_96                 0x03FB6001                      /*上1次96号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_97                 0x03FB6101                      /*上1次97号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_98                 0x03FB6201                      /*上1次98号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_99                 0x03FB6301                      /*上1次99号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_100                0x03FB6401                      /*上1次100号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_101                0x03FB6501                      /*上1次101号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_102                0x03FB6601                      /*上1次102号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_103                0x03FB6701                      /*上1次103号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_104                0x03FB6801                      /*上1次104号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_105                0x03FB6901                      /*上1次105号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_106                0x03FB6A01                      /*上1次106号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_107                0x03FB6B01                      /*上1次107号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_108                0x03FB6C01                      /*上1次108号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_109                0x03FB6D01                      /*上1次109号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_110                0x03FB6E01                      /*上1次110号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_111                0x03FB6F01                      /*上1次111号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_112                0x03FB7001                      /*上1次112号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_113                0x03FB7101                      /*上1次113号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_114                0x03FB7201                      /*上1次114号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_115                0x03FB7301                      /*上1次115号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_116                0x03FB7401                      /*上1次116号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_117                0x03FB7501                      /*上1次117号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_118                0x03FB7601                      /*上1次118号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_119                0x03FB7701                      /*上1次119号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_120                0x03FB7801                      /*上1次120号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_121                0x03FB7901                      /*上1次121号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_122                0x03FB7A01                      /*上1次122号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_123                0x03FB7B01                      /*上1次123号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_124                0x03FB7C01                      /*上1次124号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_125                0x03FB7D01                      /*上1次125号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_126                0x03FB7E01                      /*上1次126号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_127                0x03FB7F01                      /*上1次127号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_128                0x03FB8001                      /*上1次128号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_129                0x03FB8101                      /*上1次129号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_130                0x03FB8201                      /*上1次130号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_131                0x03FB8301                      /*上1次131号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_132                0x03FB8401                      /*上1次132号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_133                0x03FB8501                      /*上1次133号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_134                0x03FB8601                      /*上1次134号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_135                0x03FB8701                      /*上1次135号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_136                0x03FB8801                      /*上1次136号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_137                0x03FB8901                      /*上1次137号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_138                0x03FB8A01                      /*上1次138号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_139                0x03FB8B01                      /*上1次139号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_140                0x03FB8C01                      /*上1次140号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_141                0x03FB8D01                      /*上1次141号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_142                0x03FB8E01                      /*上1次142号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_143                0x03FB8F01                      /*上1次143号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_144                0x03FB9001                      /*上1次144号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_145                0x03FB9101                      /*上1次145号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_146                0x03FB9201                      /*上1次146号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_147                0x03FB9301                      /*上1次147号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_148                0x03FB9401                      /*上1次148号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_149                0x03FB9501                      /*上1次149号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_150                0x03FB9601                      /*上1次150号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_151                0x03FB9701                      /*上1次151号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_152                0x03FB9801                      /*上1次152号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_153                0x03FB9901                      /*上1次153号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_154                0x03FB9A01                      /*上1次154号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_155                0x03FB9B01                      /*上1次155号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_156                0x03FB9C01                      /*上1次156号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_157                0x03FB9D01                      /*上1次157号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_158                0x03FB9E01                      /*上1次158号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_159                0x03FB9F01                      /*上1次159号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_160                0x03FBA001                      /*上1次160号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_161                0x03FBA101                      /*上1次161号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_162                0x03FBA201                      /*上1次162号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_163                0x03FBA301                      /*上1次163号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_164                0x03FBA401                      /*上1次164号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_165                0x03FBA501                      /*上1次165号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_166                0x03FBA601                      /*上1次166号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_167                0x03FBA701                      /*上1次167号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_168                0x03FBA801                      /*上1次168号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_169                0x03FBA901                      /*上1次169号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_170                0x03FBAA01                      /*上1次170号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_171                0x03FBAB01                      /*上1次171号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_172                0x03FBAC01                      /*上1次172号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_173                0x03FBAD01                      /*上1次173号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_174                0x03FBAE01                      /*上1次174号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_175                0x03FBAF01                      /*上1次175号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_176                0x03FBB001                      /*上1次176号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_177                0x03FBB101                      /*上1次177号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_178                0x03FBB201                      /*上1次178号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_179                0x03FBB301                      /*上1次179号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_180                0x03FBB401                      /*上1次180号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_181                0x03FBB501                      /*上1次181号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_182                0x03FBB601                      /*上1次182号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_183                0x03FBB701                      /*上1次183号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_184                0x03FBB801                      /*上1次184号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_185                0x03FBB901                      /*上1次185号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_186                0x03FBBA01                      /*上1次186号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_187                0x03FBBB01                      /*上1次187号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_188                0x03FBBC01                      /*上1次188号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_189                0x03FBBD01                      /*上1次189号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_190                0x03FBBE01                      /*上1次190号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_191                0x03FBBF01                      /*上1次191号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_192                0x03FBC001                      /*上1次192号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_193                0x03FBC101                      /*上1次193号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_194                0x03FBC201                      /*上1次194号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_195                0x03FBC301                      /*上1次195号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_196                0x03FBC401                      /*上1次196号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_197                0x03FBC501                      /*上1次197号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_198                0x03FBC601                      /*上1次198号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_199                0x03FBC701                      /*上1次199号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_200                0x03FBC801                      /*上1次200号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_201                0x03FBC901                      /*上1次201号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_202                0x03FBCA01                      /*上1次202号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_203                0x03FBCB01                      /*上1次203号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_204                0x03FBCC01                      /*上1次204号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_205                0x03FBCD01                      /*上1次205号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_206                0x03FBCE01                      /*上1次206号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_207                0x03FBCF01                      /*上1次207号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_208                0x03FBD001                      /*上1次208号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_209                0x03FBD101                      /*上1次209号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_210                0x03FBD201                      /*上1次210号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_211                0x03FBD301                      /*上1次211号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_212                0x03FBD401                      /*上1次212号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_213                0x03FBD501                      /*上1次213号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_214                0x03FBD601                      /*上1次214号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_215                0x03FBD701                      /*上1次215号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_216                0x03FBD801                      /*上1次216号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_217                0x03FBD901                      /*上1次217号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_218                0x03FBDA01                      /*上1次218号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_219                0x03FBDB01                      /*上1次219号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_220                0x03FBDC01                      /*上1次220号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_221                0x03FBDD01                      /*上1次221号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_222                0x03FBDE01                      /*上1次222号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_223                0x03FBDF01                      /*上1次223号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_224                0x03FBE001                      /*上1次224号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_225                0x03FBE101                      /*上1次225号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_226                0x03FBE201                      /*上1次226号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_227                0x03FBE301                      /*上1次227号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_228                0x03FBE401                      /*上1次228号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_229                0x03FBE501                      /*上1次229号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_230                0x03FBE601                      /*上1次230号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_231                0x03FBE701                      /*上1次231号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_232                0x03FBE801                      /*上1次232号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_233                0x03FBE901                      /*上1次233号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_234                0x03FBEA01                      /*上1次234号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_235                0x03FBEB01                      /*上1次235号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_236                0x03FBEC01                      /*上1次236号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_237                0x03FBED01                      /*上1次237号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_238                0x03FBEE01                      /*上1次238号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_239                0x03FBEF01                      /*上1次239号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_240                0x03FBF001                      /*上1次240号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_241                0x03FBF101                      /*上1次241号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_242                0x03FBF201                      /*上1次242号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_243                0x03FBF301                      /*上1次243号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_244                0x03FBF401                      /*上1次244号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_245                0x03FBF501                      /*上1次245号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_246                0x03FBF601                      /*上1次246号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_247                0x03FBF701                      /*上1次247号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_248                0x03FBF801                      /*上1次248号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_249                0x03FBF901                      /*上1次249号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_250                0x03FBFA01                      /*上1次250号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_251                0x03FBFB01                      /*上1次251号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_252                0x03FBFC01                      /*上1次252号校表参数校表前数据*/
#define CRec_Meter_Bef1_Data_253                0x03FBFD01                      /*上1次253号校表参数校表前数据*/
#define CRec_Meter_FF_Data_1                    0x03FBFF01                      /*上1次校表记录数据集合*/

/******************************参变量类对象******************************/
#define CDate_Time                         		0x40000200                      /*采用原645  0x0400010C日期、星期（0表示星期天）及时间修改为698 date_time_s格式*/
#define C_TimeBeforeCalib                       0x40002200                      /*校时前时间*/
#define C_TimeAfterCalib                        0x40008200                      /*校时后时间*/
#define CBroadcastTimeOffset_Min                0x40000501                      /*广播校时偏差最小值*/
#define CBroadcastTimeOffset_Max                0x40000502                      /*广播校时偏差最大值*/
#define CBroadcastTimeM                         0x40007F00                      /*广播校时*/
#define CComm_Address                           0x40010200                      /*通讯地址*/
#define CMeter_Num                              0x40020200                      /*表号*/
#define CCustomer_Num                           0x40030200                      /*客户编号*/
#define CMeter_Position                         0x40040200                      /*电能表位置信息:经度、纬度、高度*/
#define CMeter_Position_Longitude               0x40040201                      /*电能表位置信息:经度*/
#define CMeter_Position_Latitude                0x40040202                      /*电能表位置信息:纬度*/
#define CMeter_Position_High                    0x40040203                      /*电能表位置信息:高度*/
#define CMulticastAddr                          0x40050200                      /*组播通讯地址*/
#define C_LCDPara                               0x40070200                      /*LCD参数集合*/
#define CPowerOn_Dis_All_Time                   0x40070201                      /*上电全显时间*/
#define CBacklightTime                          0x40070202                      /*背光点亮时间*/
#define CSViewBacklightTime                     0x40070203                      /*显示查看背光点亮时间*/
#define CNEScreenDisplay                        0x40070204                      /*无电按键屏幕驻留最大时间*/
#define CEnergy_Decimal_Num                     0x40070205                      /*电能小数位数*/
#define CPower_Decimal_Num                      0x40070206                      /*显示功率（最大需量）小数位数*/
#define C1And2Display                           0x40070207                      /*液晶①②字样意义*/
#define CChange_TZ_Time                         0x40080200                      /*两套时区表切换时间*/
#define CChange_PT_Time                         0x40090200                      /*两套日时段表切换时间*/
#define CChange_Rate                            0x400A0200                      /*两套费率电价切换时间*/
#define CChange_Ladder                          0x400B0200                      /*两套阶梯电价切换时间*/
#define CZone__Table_Num                        0x400C0200                      /*时区时段数*/
#define CYear_Zone_Num                          0x400C0201                      /*年时区数*/
#define CDay_Table_Num                          0x400C0202                      /*日时段表数*/
#define CDay_Time_Num                           0x400C0203                      /*日时段数*/
#define CRate_Num                               0x400C0204                      /*费率数*/
#define CHoliday_Num                            0x400C0205                      /*公共假日数*/
#define CStep_Num                               0x400D0200                      /*阶梯数*/
#define CKey_Tol_Num                            0x400F0200                      /*密钥总条数*/
#define CLine_Num                               0x40100200                      /*计量单元数*/
#define CHolidy_PT_TableFF                      0x40110200                      /*第1-20公共假日日期及日时段表号数据块*/
#define CHolidy_PT_Table20                      0x40110214                      /*第20公共假日日期及日时段表号数据块*/
#define CHolidy_PT_Table1                       0x40110201                      /*第1公共假日日期及日时段表号*/
#define CWeek_RestDay                           0x40120200                      /*周休日特征字*/
#define CWeek_RestDay_DTable                    0x40130200                      /*周休日采取的日时段表号*/
#define CFirst_TZone_Data                       0x40140200                      /*第一套时区表数据*/
#define CSec_TZone_Data                         0x40150200                      /*第二套时区表数据*/
#define CFirst_TZone_1PT_Data                   0x40160201                      /*第一套第1日时段表数据*/
#define CFirst_TZone_2PT_Data                   0x40160202                      /*第一套第2日时段表数据*/
#define CFirst_TZone_3PT_Data                   0x40160203                      /*第一套第3日时段表数据*/
#define CFirst_TZone_4PT_Data                   0x40160204                      /*第一套第4日时段表数据*/
#define CFirst_TZone_5PT_Data                   0x40160205                      /*第一套第5日时段表数据*/
#define CFirst_TZone_6PT_Data                   0x40160206                      /*第一套第6日时段表数据*/
#define CFirst_TZone_7PT_Data                   0x40160207                      /*第一套第7日时段表数据*/
#define CFirst_TZone_8PT_Data                   0x40160208                      /*第一套第8日时段表数据*/
#define CSec_TZone_1PT_Data                     0x40170201                      /*第二套第1日时段表数据*/
#define CSec_TZone_2PT_Data                     0x40170202                      /*第二套第2日时段表数据*/
#define CSec_TZone_3PT_Data                     0x40170203                      /*第二套第3日时段表数据*/
#define CSec_TZone_4PT_Data                     0x40170204                      /*第二套第4日时段表数据*/
#define CSec_TZone_5PT_Data                     0x40170205                      /*第二套第5日时段表数据*/
#define CSec_TZone_6PT_Data                     0x40170206                      /*第二套第6日时段表数据*/
#define CSec_TZone_7PT_Data                     0x40170207                      /*第二套第7日时段表数据*/
#define CSec_TZone_8PT_Data                     0x40170208                      /*第二套第8日时段表数据*/
#define CCurrent_RateFF_Price                   0x40180200                      /*当前套费率电价数据块*/
#define CCurrent_Rate1_Price                    0x40180201                      /*当前费率1电价*/
#define CCurrent_Rate2_Price                    0x40180202                      /*当前费率2电价*/
#define CCurrent_Rate3_Price                    0x40180203                      /*当前费率3电价*/
#define CCurrent_Rate4_Price                    0x40180204                      /*当前费率4电价*/
#define CCurrent_Rate5_Price                    0x40180205                      /*当前费率5电价*/
#define CCurrent_Rate6_Price                    0x40180206                      /*当前费率6电价*/
#define CCurrent_Rate7_Price                    0x40180207                      /*当前费率7电价*/
#define CCurrent_Rate8_Price                    0x40180208                      /*当前费率8电价*/
#define CCurrent_Rate9_Price                    0x40180209                      /*当前费率9电价*/
#define CCurrent_Rate10_Price                   0x4018020A                      /*当前费率10电价*/
#define CCurrent_Rate11_Price                   0x4018020B                      /*当前费率11电价*/
#define CCurrent_Rate12_Price                   0x4018020C                      /*当前费率12电价*/
#define CBackUp_RateFF_Price                    0x40190200                      /*备用套费率电价数据块*/
#define CBackUp_Rate1_Price                     0x40190201                      /*备用套费率1电价*/
#define CBackUp_Rate2_Price                     0x40190202                      /*备用套费率2电价*/
#define CBackUp_Rate3_Price                     0x40190203                      /*备用套费率3电价*/
#define CBackUp_Rate4_Price                     0x40190204                      /*备用套费率4电价*/
#define CBackUp_Rate5_Price                     0x40190205                      /*备用套费率5电价*/
#define CBackUp_Rate6_Price                     0x40190206                      /*备用套费率6电价*/
#define CBackUp_Rate7_Price                     0x40190207                      /*备用套费率7电价*/
#define CBackUp_Rate8_Price                     0x40190208                      /*备用套费率8电价*/
#define CBackUp_Rate9_Price                     0x40190209                      /*备用套费率9电价*/
#define CBackUp_Rate10_Price                    0x4019020A                      /*备用套费率10电价*/
#define CBackUp_Rate11_Price                    0x4019020B                      /*备用套费率11电价*/
#define CBackUp_Rate12_Price                    0x4019020C                      /*备用套费率12电价*/
#define CCurrent_Ladder_Table                   0x401A0200                      /*当前套阶梯表*/
#define CCurrent_Ladder_Table_LadNum            0x401A0201                      /*当前套阶梯表,阶梯值*/
#define CCurrent_Ladder_Table_LadPri            0x401A0202                      /*当前套阶梯表,阶梯电价*/
#define CCurrent_Ladder_Table_LadSett           0x401A0203                      /*当前套阶梯表,阶梯结算日*/
#define CBackUp_Ladder_Table                    0x401B0200                      /*备用套阶梯表*/
#define CBackUp_Ladder_Table_LadNum             0x401B0201                      /*备用套阶梯表,阶梯值*/
#define CBackUp_Ladder_Table_LadPri             0x401B0202                      /*备用套阶梯表,阶梯电价*/
#define CBackUp_Ladder_Table_LadSett            0x401B0203                      /*备用套阶梯表,阶梯结算日*/
#define CRatio_Curr_Tran                        0x401C0200                      /*电流互感器变比*/
#define CRatio_Vol_Tran                         0x401D0200                      /*电压互感器变比*/
#define CAlam_Money                             0x401E0200                      /*报警金额限值*/
#define CAlam1_Money                            0x401E0201                      /*报警金额1限值*/
#define CAlam2_Money                            0x401E0202                      /*报警金额2限值*/
#define COther_Money                            0x401F0200                      /*其他金额限值*/
#define COverDraft_Money                        0x401F0201                      /*透支金额限值*/
#define CHoarding_Money                         0x401F0202                      /*囤积金额限值*/
#define CClose_Relay_Money                      0x401F0203                      /*合闸允许金额限值*/
#define CInset_Card_State                       0x40220200                      /*插卡状态字*/
#define CVolage_Check_UpLim                     0x40300201                      /*电压考核上限*/
#define CVolage_Check_LowLim                    0x40300202                      /*电压考核下限*/
#define CVoltage_UpLim                          0x40300203                      /*电压上限值*/
#define CVoltage_LowLim                         0x40300204                      /*电压下限值*/
#define CFactoryInf_4031                        0x40310300                      /*模组版本信息*/
#define CFactory_Address_4031                   0x40310301                      /*模组逻辑地址*/
#define CFactory_Number_4031                    0x40310302                      /*厂商代码*/
#define CFactory_Softw_Version_4031             0x40310303                      /*软件版本号*/
#define CFactory_Hardw_Version_4031             0x40310304                      /*软件版本日期*/
#define CFactory_Softw_VersionDate_4031         0x40310305                      /*硬件版本号*/
#define CFactory_Hardw_VersionDate_4031         0x40310306                      /*硬件版本日期*/
#define CFactory_ExternSign_4031                0x40310307                      /*厂商扩展信息*/

#define CDemand_Cycle                           0x41000200                      /*最大需量周期*/
#define CSliding_Time                           0x41010200                      /*滑差时间*/
#define CPluse_Wide                             0x41020200                      /*脉冲宽度*/
#define CManage_Code                            0x41030200                      /*资产管理编码*/
#define CRated_Vol                              0x41040200                      /*额定电压*/
#define CRated_Curr                             0x41050200                      /*额定电流/基本电流*/
#define CMax_Curr                               0x41060200                      /*最大电流*/
#define CMin_Curr                               0x41060300                      /*最小电流*/
#define CTurn_Curr                              0x41060400                      /*转折电流*/
#define CActive_Accur_Deg                       0x41070200                      /*有功准确度等级*/
#define CReactive_Accur_Deg                     0x41080200                      /*无功准确度等级*/
#define CMeter_Ac_Const                         0x41090200                      /*电表有功常数*/
#define CMeter_Re_Const                         0x410A0200                      /*电表有无功常数*/
#define CMeter_Model                            0x410B0200                      /*电表型号*/
#define CMeter_Work_Char1                       0x41100200                      /*电表运行特征字1*/
#define CSoftw_Record_Number                    0x41110200                      /*软件备案号*/
#define CActive_Com_State                       0x41120200                      /*有功组合状态字*/
#define CReactive_Com_State1                    0x41130200                      /*无功组合状态字1*/
#define CReactive_Com_State2                    0x41140200                      /*无功组合状态字2*/
#define CSettle_Day1                            0x41160201                      /*每月第1结算日*/
#define CSettle_Day2                            0x41160202                      /*每月第2结算日*/
#define CSettle_Day3                            0x41160203                      /*每月第3结算日*/

#define CEquipmentDis                           0x43000200                      /*设备描述符*/
#define CFactory_Number                         0x43000301                      /*厂家编号*/
#define CFactory_Softw_Version                  0x43000302                      /*厂家软件版本号*/
#define CFactory_Softw_VersionDate              0x43000303                      /*厂家软件版本日期*/
#define CFactory_Hardw_Version                  0x43000304                      /*硬件版本*/
#define CFactory_Hardw_VersionDate              0x43000305                      /*厂家硬件版本日期*/
#define CFactory_ExternSign                     0x43000306                      /*厂家扩展信息*/
#define CProd_Date                              0x43000400                      /*生产日期*/
#define CMeter_CommPro                          0x43000600                      /*电表支持通信协议*/
#define CMeter_CommPro1                         0x43000601                      /*电表支持通信协议1*/
#define CMeter_CommPro2                         0x43000602                      /*电表支持通信协议2*/
#define CAllowFollowUpTell                      0x43000700                      /*是否允许跟随上报*/
#define CAllowAccordUpTell                      0x43000800                      /*是否允许主动上报*/
#define CAllowMasterCall                        0x43000900                      /*允许与主站通话*/
#define CUpTellChannel                          0x43000A00                      /*上报通道*/

#define CAppProInformation                      0x44000301                      /*协议版本信息*/
#define CAppMaxReAPDU                           0x44000302                      /*最大接收APDU尺寸*/
#define CAppMaxSeAPDU                           0x44000303                      /*最大发送APDU尺寸*/
#define CAppMaxHandleAPDU                       0x44000304                      /*最大可处理APDU尺寸*/
#define CAppProConsistency                      0x44000305                      /*协议一致性块*/
#define CAppFunConsistency                      0x44000306                      /*功能一致性块*/
#define CAppStaticTimeout                       0x44000307                      /*静态超时时间*/
#define CAppStaticTimeout_termal                0x440003A7                      /*终端静态超时时间*/
#define CClientAddr                             0x44000400                      /*当前连接的客户机地址*/
#define CConAutheMechanism                      0x44000500                      /*连接认证机制*/
#define C698Key                                 0x44010200                      /*698,认证密码*/

#define CGPS_Signal                             0x45000900                      /*无线通讯在线及信号强弱指示*/
/*校表参数-645*/
#define CAlarm_Status_645                       0x04900001                      /*报警模式字*/

#define CRTC_Inital                             0x04CC0304                      /*RTC初始化命令，矩泉*/
#define CRTC_Adjust                             0x04CC0300                      /*RTC校准命令，矩泉*/
#define CRTC_AdjustTemp                         0x04CC0301                      /*RTC校准温度值，矩泉*/

#define CVolage_Type_645                        0x04FE0001                      /*电压类型*/
#define CCurrent_Type_645                       0x04FE0002                      /*电流类型*/
#define CLine_Type_645                          0x04FE0003                      /*相线类型*/
#define CAuxi_Power_Sign_645                    0x04FE0004                      /*辅助电源标志*/
#define CRelay_Type_645                         0x04FE0005                      /*负荷开关类型*/
#define CComm_Way_645                           0x04FE0006                      /*通信方式*/
#define CProgram_Valid_645                      0x04FE0007                      /*编程有效标志*/
#define CZero_Current_Sign_645                  0x04FE0008                      /*零线电流标志*/

#define CStart_Up_Current_645                   0x04FE0101                      /*电流瞬时量阀值*/
#define CStart_Up_Power_645                     0x04FE0102                      /*功率瞬时量阀值*/

#define CVolage_Abnor_Vol_645                   0x04FE0201                      /*电压异常判断电压*/
#define CLoss_Volage_Curr_645                   0x04FE0202                      /*全失压电流*/
#define CLoss_Volage_Vol_645                    0x04FE0203                      /*全失压电压*/
#define CRev_Phase_Vol_645                      0x04FE0204                      /*逆相序判断电压*/
#define CRelayOpen_Vol__LowLim_645              0x04FE0205                      /*跳闸下门限*/
#define CRelayOpen_Vol__UpLim_645               0x04FE0206                      /*跳闸上门限*/

#define CPluse_Most__Lim_645                    0x04FE0301                      /*从计量芯片读出的脉冲最大阀值*/
#define CCurr_Ratio_30A_645                     0x04FE0302                      /*校表30A对应的相应电流规格系数*/
#define CPulse_Constant_645                     0x04FE0303                      /*脉冲常数*/
#define CSoftIJ_Valid_Time_645                  0x04FE0304                      /*软IJ有效时间*/
#define CExtern_Relay_PulW_645                  0x04FE0305                      /*外置继电器脉冲宽度*/

#define CMeterRunStatic_645                     0x04FE0700                      /*当前运行在第几套时区表、时段表。时区表在前（低地址）*/

#define CHardError_State_645                    0x04FE0900                      /*硬件故障运行状态字*/

#define CF1_TerUpCommParam_645                  0x04FE0A01                      /*F1终端上行通信参数*/
#define CF3_MainStaCommParam_645                0x04FE0A02                      /*F3主站通信参数*/
#define CF4_SMSCommParam_645                    0x04FE0A03                      /*F4短信通信参数*/
#define CF7_TerminalIPAddr_645                  0x04FE0A04                      /*F7终端IP地址*/
#define CF8_ConnectParam_645                    0x04FE0A05                      /*F8连接参数*/
#define CF16_MoveAPNPassWord_645                0x04FE0A06                      /*F16移动APN密码*/
#define CF89_TerminalAddr_645                   0x04FE0A07                      /*F89终端地址*/

#define CRec_MeterSequence_645                  0x04FE0D01                      /*校表序列号*/
#define CRec_MeterPassWord_645                  0x04FE0D02                      /*校表密码*/
#define C_UserCardNo_645                        0x04FE0D03                      /*用户卡卡片序列号*///
#define C_OddHar_AddData1_645                   0x04FE0D04                      /*奇次谐波补偿值1，（电流：2.8A~4A 条件）*/
#define C_OddHar_AddData2_645                   0x04FE0D05                      /*奇次谐波补偿值2，（电流：1.4A~2A 条件）*/
#define C_EvenHar_AddData_A0_645                0x04FE0D06                      /*偶次谐波补偿值A0，（0.5L条件，A相补偿值）*/
#define C_EvenHar_AddData_A1_645                0x04FE0D07                      /*偶次谐波补偿值A1，（0.5L条件，A相补偿值）*/
#define C_EvenHar_AddData_B0_645                0x04FE0D08                      /*偶次谐波补偿值B0，（0.5L条件，B相补偿值）*/
#define C_EvenHar_AddData_B1_645                0x04FE0D09                      /*偶次谐波补偿值B1，（0.5L条件，B相补偿值）*/
#define C_EvenHar_AddData_C0_645                0x04FE0D0A                      /*偶次谐波补偿值C0，（0.5L条件，C相补偿值）*/
#define C_EvenHar_AddData_C1_645                0x04FE0D0B                      /*偶次谐波补偿值C1，（0.5L条件，C相补偿值）*/
#define C_EvenHar_Time_645                      0x04FE0D10                      /*偶次谐波补偿计时器，默认24h*/

#define CFactoryInMeterNum_645                  0x04FE0E01                      /*电表内部序号*/
/*参变量-645*/
#define CDate_Week                              0x04000101                      /*日期及星期（0表示星期天）*/
#define CTime                                   0x04000102                      /*时间*/
#define CDemand_Cycle645                        0x04000103                      /*最大需量周期*/
#define CSliding_Time645                        0x04000104                      /*滑差时间*/
#define CChange_TZ_Time_645                     0x04000106                      /*两套时区表切换时间*/
#define CChange_PT_Time_645                     0x04000107                      /*两套日时段表切换时间*/
#define CDate_Week_Time_645                     0x0400010C                      /*采用原645  0x0400010C日期、星期（0表示星期天）及时间修改为698 date_time_s格式*/
#define CYear_Zone_Num_645                      0x04000201                      /*年时区数*/
#define CDay_Table_Num_645                      0x04000202                      /*日时段表数*/
#define CDay_Time_Num_645                       0x04000203                      /*日时段数*/
#define CRate_Num_645                           0x04000204                      /*费率数*/
#define CHoliday_Num_645                        0x04000205                      /*公共假日数*/
#define CAuto_Dis_Screen_Num_645                0x04000301                      /*自动循显屏数*/
#define CPer_Dis_Screen_Time_645                0x04000302                      /*每屏显示时间*/
#define CEnergy_Decimal_Num_645                 0x04000303                      /*电能小数位数*/
#define CPower_Decimal_Num_645                  0x04000304                      /*显示功率（最大需量）小数位数*/
#define CKey_CycDis_Screen_Num_645              0x04000305                      /*按键循环显示屏数*/
#define CRatio_Curr_Tran_645                    0x04000306                      /*电流互感器变比*/
#define CRatio_Vol_Tran_645                     0x04000307                      /*电压互感器变比*/
#define CPowerOn_Dis_All_Time_645               0x04000308                      /*上电全显时间*/
#define CComm_Address_645                       0x04000401                      /*通讯地址*/
#define CMeter_Num_645                          0x04000402                      /*表号*/
#define CManage_Code_645                        0x04000403                      /*资产管理编码*/
#define CRated_Vol645                           0x04000404                      /*额定电压*/
#define CRated_Curr645                          0x04000405                      /*额定电流/基本电流*/
#define CMax_Curr645                            0x04000406                      /*最大电流*/
#define CActive_Accur_Deg645                    0x04000407                      /*有功准确度等级*/
#define CReactive_Accur_Deg645                  0x04000408                      /*无功准确度等级*/
#define CMeter_Ac_Const645                      0x04000409                      /*电表有功常数*/
#define CMeter_Re_Const645                      0x0400040A                      /*电表无功常数*/
#define CMeter_Model645                         0x0400040B                      /*电表型号*/
#define CProd_Date645                           0x0400040C                      /*生产日期*/
#define CProd_Date_645                          0x0400040C                      /*生产日期-重复*/
#define CProt_Version_Num                       0x0400040D                      /*协议版本号*/
#define CActive_Com_State_645                   0x04000601                      /*有功组合状态字*/
#define CReactive_Com_State1_645                0x04000602                      /*无功组合状态字1*/
#define CReactive_Com_State2_645                0x04000603                      /*无功组合状态字2*/
#define CMod_InFr_Baud_645                      0x04000701                      /*通信速率特征字调制红外*/
#define COne485_Baud_645                        0x04000703                      /*1路485波特率特征字*/
#define CTwo485_Baud_645                        0x04000704                      /*2路485波特率特征字*/
#define CModular_Baud_645                       0x04000705                      /*模块通道波特率特征字*/
#define CWeek_RestDay_645                       0x04000801                      /*周休日特征字*/
#define CWeek_RestDay_DTable_645                0x04000802                      /*周休日采取的日时段表号*/
#define CLoad_Rec_Time_Year                     0x04000A0F                      /*负荷记录起始时间,YYMMDDhhmm*/
#define CSettle_Day1_645                        0x04000B01                      /*每月第1结算日*/
#define CSettle_Day2_645                        0x04000B02                      /*每月第2结算日*/
#define CSettle_Day3_645                        0x04000B03                      /*每月第3结算日*/
#define CKey_0_Class                            0x04000C01                      /*0级密码*/
#define CKey_1_Class                            0x04000C02                      /*1级密码*/
#define CKey_2_Class                            0x04000C03                      /*2级密码*/
#define CKey_3_Class                            0x04000C04                      /*3级密码*/
#define CKey_4_Class                            0x04000C05                      /*4级密码*/
#define CKey_5_Class                            0x04000C06                      /*5级密码*/
#define CKey_6_Class                            0x04000C07                      /*6级密码*/
#define CKey_7_Class                            0x04000C08                      /*7级密码*/
#define CKey_8_Class                            0x04000C09                      /*8级密码*/
#define CKey_9_Class                            0x04000C0A                      /*9级密码*/
#define CReturn_Money                           0x04001006                      /*退费金额*/
#define CMeter_Work_Char1_645                   0x04001101                      /*电表运行特征字1*/
#define CDrive_Report_Mode_645                  0x04001104                      /*645主动上报模式字*/
#define CTiming_Freeze_Time                     0x04001204                      /*定时冻结时间*/
#define CRelay_Delay_Time_645                   0x04001401                      /*698兼容645时增加，645跳闸延时时间，由于698此参数由方法下发*/
#define C_IRAuth_Timer645                       0x04001404                      /*红外认证时效645*/
#define CRst_ReportState_Timer                  0x04001405                      /*主动上报自动复位时间*/
#define CDrive_Report_State_645                 0x04001501                      /*645主动上报状态字*/
#define CRst_Report_State_645                   0x04001503                      /*复位主动上报状态字*/
#define CFirst_TZone_Data_645                   0x04010000                      /*第一套时区表数据*/
#define CFirst_TZone_1PT_Data_645               0x04010001                      /*第一套第1日时段表数据*/
#define CFirst_TZone_2PT_Data_645               0x04010002                      /*第一套第2日时段表数据*/
#define CFirst_TZone_3PT_Data_645               0x04010003                      /*第一套第3日时段表数据*/
#define CFirst_TZone_4PT_Data_645               0x04010004                      /*第一套第4日时段表数据*/
#define CFirst_TZone_5PT_Data_645               0x04010005                      /*第一套第5日时段表数据*/
#define CFirst_TZone_6PT_Data_645               0x04010006                      /*第一套第6日时段表数据*/
#define CFirst_TZone_7PT_Data_645               0x04010007                      /*第一套第7日时段表数据*/
#define CFirst_TZone_8PT_Data_645               0x04010008                      /*第一套第8日时段表数据*/
#define CSec_TZone_Data_645                     0x04020000                      /*第二套时区表数据*/
#define CSec_TZone_1PT_Data_645                 0x04020001                      /*第二套第1日时段表数据*/
#define CSec_TZone_2PT_Data_645                 0x04020002                      /*第二套第2日时段表数据*/
#define CSec_TZone_3PT_Data_645                 0x04020003                      /*第二套第3日时段表数据*/
#define CSec_TZone_4PT_Data_645                 0x04020004                      /*第二套第4日时段表数据*/
#define CSec_TZone_5PT_Data_645                 0x04020005                      /*第二套第5日时段表数据*/
#define CSec_TZone_6PT_Data_645                 0x04020006                      /*第二套第6日时段表数据*/
#define CSec_TZone_7PT_Data_645                 0x04020007                      /*第二套第7日时段表数据*/
#define CSec_TZone_8PT_Data_645                 0x04020008                      /*第二套第8日时段表数据*/
#define CLCD_View                               0x04040300                      /*液晶查看*/
#define CLossVolage_Vol_UpLim_645               0x04090101                      /*失压事件电压触发上限*/
#define CLossVolage_Vol_LowLim_645              0x04090102                      /*失压事件电压恢复下限*/
#define CLossVolage_Curr_LowLim_645             0x04090103                      /*失压事件电流触发下限*/
#define CLossVolage_Delay_T_645                 0x04090104                      /*失压事件判断延时时间*/
#define CLowVolage_Vol_UpLim_645                0x04090201                      /*欠压事件电压触发上限*/
#define CLowVolage_Delay_T_645                  0x04090202                      /*欠压事件判断延时时间*/
#define COverVolage_Vol_LowLim_645              0x04090301                      /*过压事件电压触发下限*/
#define COverVolage_Delay_T_645                 0x04090302                      /*过压事件判断延时时间*/
#define CBreakVol_Vol_UpLim_645                 0x04090401                      /*断相事件电压触发上限*/
#define CBreakVol_Curr_UpLim_645                0x04090402                      /*断相事件电流触发上限*/
#define CBreakVol_Delay_T_645                   0x04090403                      /*断相事件判定延时时间*/
#define CNoBal_Vol_Lim_645                      0x04090501                      /*电压不平衡率限值*/
#define CNoBal_Vol_Delay_T_645                  0x04090502                      /*电压不平衡率判定延时时间*/
#define CNoBal_Curr_Lim_645                     0x04090601                      /*电流不平衡率限值*/
#define CNoBal_Curr_Delay_T_645                 0x04090602                      /*电流不平衡率判定延时时间*/
#define CLossCurr_Vol_LowLim_645                0x04090701                      /*失流事件电压触发下限*/
#define CLossCurr_Curr_UpLim_645                0x04090702                      /*失流事件电流触发上限*/
#define CLossCurr_Curr_LowLim_645               0x04090703                      /*失流事件电流触发下限*/
#define CLossCurr_Delay_T_645                   0x04090704                      /*失流事件判断延时时间*/
#define COverCurr_Curr_LowLim_645               0x04090801                      /*过流事件电流触发下限*/
#define COverCurr_Delay_T_645                   0x04090802                      /*过流事件判断延时时间*/
#define CBreakCurr_Vol_LowLim_645               0x04090901                      /*断流事件电压触发下限*/
#define CBreakCurr_Curr_UpLim_645               0x04090902                      /*断流事件电流触发上限*/
#define CBreakCurr_Delay_T_645                  0x04090903                      /*断流事件判定延时时间*/
#define CTrendRev_AcPower_LowLim_645            0x04090A01                      /*潮流反向事件有功功率触发下限*/
#define CTrendRev_Delay_T_645                   0x04090A02                      /*潮流反向事件判定延时时间*/
#define COverLoad_AcPower_LowLim_645            0x04090B01                      /*过载事件有功功率触发下限*/
#define COverLoad_Delay_T_645                   0x04090B02                      /*过载事件判定延时时间*/
#define CVolage_Check_UpLim_645                 0x04090C01                      /*电压考核上限*/
#define CVolage_Check_LowLim_645                0x04090C02                      /*电压考核下限*/
#define CAcDemandOv_De_LowLim_645               0x04090D01                      /*有功需量超限事件需量触发下限*/
#define CReDemandOv_De_LowLim_645               0x04090D02                      /*无功需量超限事件需量触发下限*/
#define CDemandOv_Delay_T_645                   0x04090D03                      /*需量超限事件判定延时时间*/
#define CPowerFactor_LowLim_645                 0x04090E01                      /*功率因数超下限阀值*/
#define CPowerFactor_Delay_T_645                0x04090E02                      /*功率因素超下限判定延时时间*/
#define CSeriNoBal_Curr_Lim_645                 0x04090F01                      /*电流严重不平衡率限值*/
#define CSeriNoBal_Curr_Delay_T_645             0x04090F02                      /*电流严重不平衡率判定延时时间*/
#define CPowerRev_AcPower_LowLim_645            0x04091001                      /*功率反向事件有功功率触发下限*/
#define CPowerRev_Delay_T_645                   0x04091002                      /*功率反向事件判定延时时间*/
#define CSoftw_Record_Number_645                0x04800004                      /*645软件备案号*/

/******************************冻结类对象******************************/
/*顺序与数据层关联*/
#define C_RelatedOAD_Immid                      0x50000200                      /*698瞬时冻结*/
#define C_RelatedOAD_Sec                        0x50010200                      /*698秒冻结*/
#define C_RelatedOAD_Min                        0x50020200                      /*698分钟冻结*/
#define C_RelatedOAD_Hour                       0x50030200                      /*698小时冻结*/
#define C_RelatedOAD_Day                        0x50040200                      /*698日冻结*/
#define C_RelatedOAD_Day_1                      0x50040201                      /*698日冻结，上1日*/
#define C_RelatedOAD_Settle                     0x50050200                      /*698结算日冻结*/
#define C_RelatedOAD_Month                      0x50060200                      /*698月冻结*/
#define C_RelatedOAD_Year                       0x50070200                      /*698年冻结*/
#define C_RelatedOAD_TimeZone                   0x50080200                      /*698时区表切换冻结*/
#define C_RelatedOAD_TimeRegion                 0x50090200                      /*698日时段表切换冻结*/
#define C_RelatedOAD_RateTalbe                  0x500A0200                      /*698费率电价切换冻结*/
#define C_RelatedOAD_StepTable                  0x500B0200                      /*698阶梯切换冻结*/
#define C_RelatedOAD_YSettle                    0x50110200                      /*698阶梯结算冻结*/
/*瞬时冻结方法*/
#define C_ImmidMethod_TriggerOnce               0x50000300                      /*698瞬时冻结,方法3，触发一次冻结*/
#define C_ImmidMethod_AddOneRelatedOAD          0x50000400                      /*698瞬时冻结,方法4，添加一个冻结对象属性*/
#define C_ImmidMethod_DelOneRelatedOAD          0x50000500                      /*698瞬时冻结,方法4，删除一个冻结对象属性*/
#define C_ImmidMethod_AddManyRelatedOAD         0x50000700                      /*698瞬时冻结,方法4，批量添加冻结对象属性*/
#define C_ImmidMethod_DelAllRelatedOAD          0x50000800                      /*698瞬时冻结,方法4，清空冻结对象属性*/
/*定时冻结-645*/
#define CT_Free_Time_1                          0x05000001                      /*上1次定时冻结时间*/
#define CT_Free_Pos_Ac_En_1                     0x05000101                      /*上1次定时冻结正向有功电能数据*/
#define CT_Free_Rev_Ac_En_1                     0x05000201                      /*上1次定时冻结反向有功电能数据*/
#define CT_Free_Com_Re1_En_1                    0x05000301                      /*上1次定时冻结组合无功1电能数据*/
#define CT_Free_Com_Re2_En_1                    0x05000401                      /*上1次定时冻结组合无功2电能数据*/
#define CT_Free_Qua1_Re_En_1                    0x05000501                      /*上1次定时冻结1象限无功电能数据*/
#define CT_Free_Qua2_Re_En_1                    0x05000601                      /*上1次定时冻结2象限无功电能数据*/
#define CT_Free_Qua3_Re_En_1                    0x05000701                      /*上1次定时冻结3象限无功电能数据*/
#define CT_Free_Qua4_Re_En_1                    0x05000801                      /*上1次定时冻结4象限无功电能数据*/
#define CT_Free_Pos_Ac_De_1                     0x05000901                      /*上1次定时冻结正向有功最大需量及发生时刻数据*/
#define CT_Free_Rev_Ac_De_1                     0x05000A01                      /*上1次定时冻结反向有功最大需量及发生时刻数据*/
#define CT_Free_Variable_1                      0x05001001                      /*上1次定时冻结变量数据*/
#define CT_Free_FF_1                            0x0500FF01                      /*上1次定时冻结数据块*/
/*瞬时冻结-645*/
#define CI_Free_Time_1                          0x05010001                      /*上1次瞬时冻结时间*/
#define CI_Free_Pos_Ac_En_1                     0x05010101                      /*上1次瞬时冻结正向有功电能数据*/
#define CI_Free_Rev_Ac_En_1                     0x05010201                      /*上1次瞬时冻结反向有功电能数据*/
#define CI_Free_Com_Re1_En_1                    0x05010301                      /*上1次瞬时冻结组合无功1电能数据*/
#define CI_Free_Com_Re2_En_1                    0x05010401                      /*上1次瞬时冻结组合无功2电能数据*/
#define CI_Free_Qua1_Re_En_1                    0x05010501                      /*上1次瞬时冻结1象限无功电能数据*/
#define CI_Free_Qua2_Re_En_1                    0x05010601                      /*上1次瞬时冻结2象限无功电能数据*/
#define CI_Free_Qua3_Re_En_1                    0x05010701                      /*上1次瞬时冻结3象限无功电能数据*/
#define CI_Free_Qua4_Re_En_1                    0x05010801                      /*上1次瞬时冻结4象限无功电能数据*/
#define CI_Free_Pos_Ac_De_1                     0x05010901                      /*上1次瞬时冻结正向有功最大需量及发生时刻数据*/
#define CI_Free_Rev_Ac_De_1                     0x05010A01                      /*上1次瞬时冻结反向有功最大需量及发生时刻数据*/
#define CI_Free_Variable_1                      0x05011001                      /*上1次瞬时冻结变量数据*/
#define CI_Free_FF_1                            0x0501FF01                      /*上1次瞬时冻结数据块*/
/*整点冻结-645*/
#define CH_Free_Degree                          0x05040000                      /*整点冻结总次数*/
#define CH_Free_Time_1                          0x05040001                      /*上1次整点冻结时间*/
#define CH_Free_Pos_Ac_TolEn_1                  0x05040101                      /*上1次整点冻结正向有功总电能数据*/
#define CH_Free_Rev_Ac_En_1                     0x05040201                      /*上1次整点冻结反向有功总电能数据*/
#define CH_Free_FF_1                            0x0504FF01                      /*上1次整点冻结数据块*/
/*日冻结-645*/
#define CD_Free_Degree                          0x05060000                      /*日冻结总次数*/
#define CD_Free_Time_1                          0x05060001                      /*上1次日冻结时间*/
#define CD_Free_Pos_Ac_En_1                     0x05060101                      /*上1次日冻结正向有功电能数据*/
#define CD_Free_Rev_Ac_En_1                     0x05060201                      /*上1次日冻结反向有功电能数据*/
#define CD_Free_Com_Re1_En_1                    0x05060301                      /*上1次日冻结组合无功1电能数据*/
#define CD_Free_Com_Re2_En_1                    0x05060401                      /*上1次日冻结组合无功2电能数据*/
#define CD_Free_Qua1_Re_En_1                    0x05060501                      /*上1次日冻结1象限无功电能数据*/
#define CD_Free_Qua2_Re_En_1                    0x05060601                      /*上1次日冻结2象限无功电能数据*/
#define CD_Free_Qua3_Re_En_1                    0x05060701                      /*上1次日冻结3象限无功电能数据*/
#define CD_Free_Qua4_Re_En_1                    0x05060801                      /*上1次日冻结4象限无功电能数据*/
#define CD_Free_Pos_Ac_De_1                     0x05060901                      /*上1次日冻结正向有功最大需量及发生时刻数据*/
#define CD_Free_Rev_Ac_De_1                     0x05060A01                      /*上1次日冻结反向有功最大需量及发生时刻数据*/
#define CD_Free_Variable_1                      0x05061001                      /*上1次日冻结变量数据*/
#define CD_Free_FF_1                            0x0506FF01                      /*上1次日冻结数据块*/
/*负荷记录-645*/
#define CVoltageA_Load                          0x06100101                      /*负荷中A相电压*/
#define CVoltageB_Load                          0x06100102                      /*负荷中B相电压*/
#define CVoltageC_Load                          0x06100103                      /*负荷中C相电压*/
#define CVoltageBlock_Load                      0x061001FF                      /*电压曲线数据块*/

#define CCurrentA_Load                          0x06100201                      /*负荷中A相电流*/
#define CCurrentB_Load                          0x06100202                      /*负荷中B相电流*/
#define CCurrentC_Load                          0x06100203                      /*负荷中C相电流*/
#define CCurrentBlock_Load                      0x061002FF                      /*电流曲线数据块*/

#define CActPowerT_Load                         0x06100300                      /*负荷中总有功功率*/
#define CActPowerA_Load                         0x06100301                      /*负荷中A相有功功率*/
#define CActPowerB_Load                         0x06100302                      /*负荷中B相有功功率*/
#define CActPowerC_Load                         0x06100303                      /*负荷中C相有功功率*/
#define CActPowerBlock_Load                     0x061003FF                      /*有功功率曲线数据块*/

#define CReActPowerT_Load                       0x06100400                      /*负荷中总无功功率*/
#define CReActPowerA_Load                       0x06100401                      /*负荷中A相无功功率*/
#define CReActPowerB_Load                       0x06100402                      /*负荷中B相无功功率*/
#define CReActPowerC_Load                       0x06100403                      /*负荷中C相无功功率*/
#define CReActPowerBlock_Load                   0x061004FF                      /*无功功率曲线数据块*/

#define CPowFactorT_Load                        0x06100500                      /*负荷中总功率因素*/
#define CPowFactorA_Load                        0x06100501                      /*负荷中A相功率因素*/
#define CPowFactorB_Load                        0x06100502                      /*负荷中B相功率因素*/
#define CPowFactorC_Load                        0x06100503                      /*负荷中C相功率因素*/
#define CPowFactorBlock_Load                    0x061005FF                      /*功率因素曲线数据块*/

#define CPosActEnergyT_Load                     0x06100601                      /*负荷中正向有功总电能*/
#define CRevActEnergyT_Load                     0x06100602                      /*负荷中反向有功总电能*/
#define CComReAct1T_Load                        0x06100603                      /*负荷中组合无功1总电能*/
#define CComReAct2T_Load                        0x06100604                      /*负荷中组合无功2总电能*/
#define CTotEnergyBlock_Load                    0x061006FF                      /*有无功总电能曲线数据块*/

#define CReActQuad1_Load                        0x06100701                      /*负荷中1象限无功电能*/
#define CReActQuad2_Load                        0x06100702                      /*负荷中2象限无功电能*/
#define CReActQuad3_Load                        0x06100703                      /*负荷中3象限无功电能*/
#define CReActQuad4_Load                        0x06100704                      /*负荷中4象限无功电能*/
#define CReActQuadTBlock_Load                   0x061007FF                      /*4象限无功电能曲线数据块*/

#define CActDemand_Load                         0x06100801                      /*负荷中当前有功需量*/
#define CReActDemand_Load                       0x06100802                      /*负荷中当前无功需量*/
#define CDemandBlock_Load                       0x061008FF                      /*当前需量曲线数据块*/

#define CEarlietRec1_Load                       0x06010000                      /*第1类最早记录块*/
#define CEarlietRec2_Load                       0x06020000                      /*第2类最早记录块*/
#define CEarlietRec3_Load                       0x06030000                      /*第3类最早记录块*/
#define CEarlietRec4_Load                       0x06040000                      /*第4类最早记录块*/
#define CEarlietRec5_Load                       0x06050000                      /*第5类最早记录块*/
#define CEarlietRec6_Load                       0x06060000                      /*第6类最早记录块*/

/******************************控制类对象******************************/
#define CRelay_Delay_Time                       0x80008102                      /*跳闸延时时间*/
#define CRelay_Open_CurrTreshold                0x80000201                      /*继电器拉闸控制电流门限值*/
#define CRelay_Open_CurrTimer                   0x80000202                      /*拉闸控制电流门限保护延时时间*/

/******************************ESAM接口类对象******************************/
#define CKey_State                              0xF1000400                      /*密钥状态字*/
#define CBeforeUpDateKeyState                   0xF1002400                      /*密钥更新前密钥状态*/
#define CID_Auth_Remain_Time                    0xF1000600                      /*身份认证时效剩余时间*/
#define C_IRAuth_Timer                          0xF1000E00                      /*红外认证时效*/
#define CInfra_Auth_Remain_Time                 0xF1000F00                      /*红外认证时效剩余时间*/
#define CAuthenticationEnabled                  0xF1001100                      /*身份认证启用*/
#define CID_Auth_T_Remain_Time                  0xF1008F00                      /*终端身份认证时效剩余时间*/
#define CSafeModePara                           0xF1010200                      /*安全模式参数*/
#define CSafeModeParaNat3                       0xF1010300                      /*安全模式参数,属性3*/

/******************************输入输出设备类对象******************************/
#define CMod_InFr_Baud                          0xF2020201                      /*调制型红外光口波特率特征字*/
#define CTouch_InFr_Baud                        0xF2020202                      /*接触式红外光口波特率特征字*/
#define COne485_Baud                            0xF2010201                      /*1路485波特率特征字*/
#define CTwo485_Baud                            0xF2010202                      /*2路485波特率特征字*/
#define C485_Baud_Gather                        0xF2010200                      /*485集合*/
#define C_RelayFa_State                         0xF2050201                      /*负荷开关误动作时状态*/
#define CModular_Baud                           0xF2090201                      /*模块通道波特率特征字*/
#define CModular_Baud_Gather                    0xF2090200                      /*模块通道集合*/
#define CModular_BaudConsult                    0xF20902FD                      /*模块通道协商波特率特征字*/

/******************************显示类对象******************************/
#define CAuto_Dis_1ScreenCode                   0xF3000201                      /*自动循显显示第1屏显示代码*/
#define CAuto_Dis_99ScreenCode                  0xF3000263                      /*自动循显显示第99屏显示代码*/
#define CPer_Dis_Screen_Time                    0xF3000300                      /*每屏显示时间*/
#define CAuto_Dis_Screen_Num                    0xF3000401                      /*自动循显屏数*/
#define CAuto_Dis_Screen_MaxNum                 0xF3000402                      /*自动循显最大屏数*/
#define CKey_Dis_1ScreenCode                    0xF3010201                      /*按键显示第1屏显示代码*/
#define CKey_Dis_99ScreenCode                   0xF3010263                      /*按键显示第99屏显示代码*/
#define CPerkey_Dis_Screen_Time                 0xF3010300                      /*按键每屏显示时间*/
#define CKey_CycDis_Screen_Num                  0xF3010401                      /*按键循环显示屏数*/
#define CKey_CycDis_Screen_MaxNum               0xF3010402                      /*按键循环最大显示屏数*/

/******************************自扩类对象******************************/
/*电能模块*/
#define CChargeBal_Hex_Full                     0xFF000200                      /*当前剩余金额,电能模块充值时*/
#define COverDraft_Hex_Full                     0xFF000300                      /*当前透支金额,电能模块充值时*/
#define CM_Pos_Ac_Tol_En_Pul_1                  0xFF000400                      /*上1月度正向有功累计电量-脉冲数格式*/
#define CM_Rev_Ac_Tol_En_Pul_1                  0xFF000500                      /*上1月度反向有功累计电量-脉冲数格式*/
/*瞬时量模块*/
#define CVolage_Type                            0xFF200201                      /*电压类型*/
#define CCurrent_Type                           0xFF200202                      /*电流类型*/
#define CLine_Type                              0xFF200203                      /*相线类型*/
#define CAuxi_Power_Sign                        0xFF200204                      /*辅助电源标志*/
#define CRelay_Type                             0xFF200205                      /*负荷开关类型*/
#define CComm_Way                               0xFF200206                      /*通信方式*/
#define CProgram_Valid                          0xFF200207                      /*编程有效标志*/
#define CZero_Current_Sign                      0xFF200208                      /*零线电流标志*/
#define CStart_Up_Current                       0xFF200301                      /*电流瞬时量阀值*/
#define CStart_Up_Power                         0xFF200302                      /*功率瞬时量阀值*/
#define CPluse_Most__Lim                        0xFF200401                      /*从计量芯片读出的脉冲最大阀值*/
#define CCurr_Ratio_30A                         0xFF200402                      /*校表30A对应的相应电流规格系数*/
#define CPulse_Constant                         0xFF200403                      /*脉冲常数*/
#define CSoftIJ_Valid_Time                      0xFF200404                      /*软IJ有效时间*/
#define CExtern_Relay_PulW                      0xFF200405                      /*外置继电器脉冲宽度*/
#define CHardError_State                        0xFF200501                      /*硬件故障运行状态字*/
#define CRec_MeterSequence                      0xFF200601                      /*校表序列号*/
#define CRec_MeterPassWord                      0xFF200602                      /*校表密码*/
#define C_UserCardNo                            0xFF200603                      /*用户卡卡片序列号*/
#define C_OddHar_AddData1                       0xFF200604                      /*奇次谐波补偿值1，（电流：2.8A~4A 条件）*/
#define C_OddHar_AddData2                       0xFF200605                      /*奇次谐波补偿值2，（电流：1.4A~2A 条件）*/
#define C_EvenHar_AddData_A0                    0xFF200606                      /*偶次谐波补偿值A0，（0.5L条件，A相补偿值）*/
#define C_EvenHar_AddData_A1                    0xFF200607                      /*偶次谐波补偿值A1，（0.5L条件，A相补偿值）*/
#define C_EvenHar_AddData_B0                    0xFF200608                      /*偶次谐波补偿值B0，（0.5L条件，B相补偿值）*/
#define C_EvenHar_AddData_B1                    0xFF200609                      /*偶次谐波补偿值B1，（0.5L条件，B相补偿值）*/
#define C_EvenHar_AddData_C0                    0xFF20060A                      /*偶次谐波补偿值C0，（0.5L条件，C相补偿值）*/
#define C_EvenHar_AddData_C1                    0xFF20060B                      /*偶次谐波补偿值C1，（0.5L条件，C相补偿值）*/
#define C_EvenHar_Time                          0xFF200610                      /*偶次谐波补偿计时器，默认24h*/
#define CBackTime_OneSec                        0xFF200701                      /*备份时间，每s写铁电*/
#define CAlarm_Status                           0xFF200801                      /*报警模式字*/

#define CSoftI_J_RemainTime                     0xFF200901                      /*软IJ有效剩余时间*/
#define CCurrMon_Vol_Pass_Time                  0xFF200A01                      /*本月总电压合格时间*/
#define CEnter_LowPower_Time                    0xFF200B01                      /*进入低功耗时间*/
#define CExit_LowPower_Time                     0xFF200B02                      /*退出低功耗时间*/
#define CCurrFF_Phase                           0xFF200C00                      /*电流相角数据块*/
#define CCurrA_Phase                            0xFF200C01                      /*A相电流相角*/
#define CCurrB_Phase                            0xFF200C02                      /*B相电流相角*/
#define CCurrC_Phase                            0xFF200C03                      /*C相电流相角*/
#define CPhaseFF_Curr_4Dig                      0xFF200D00                      /*电流数据块,4位小数*/
#define CPhaseA_Curr_4Dig                       0xFF200D01                      /*A相电流,4位小数*/
#define CPhaseB_Curr_4Dig                       0xFF200D02                      /*B相电流,4位小数*/
#define CPhaseC_Curr_4Dig                       0xFF200D03                      /*C相电流,4位小数*/
#define CRemote_Local_State                     0xFF200E01                      /*远程、本地开户状态*/
#define CCloc_Batt_LowState                     0xFF200F01                      /*时钟电池欠压状态*/
#define CReadMeter_Batt_LowState                0xFF200F02                      /*唤醒电池欠压状态*/
#define CESAM_FaultState                        0xFF200F03                      /*ESAM故障状态*/
#define CClock_FaultState                       0xFF200F04                      /*时钟故障状态*/
#define CClock_FaultTime                        0xFF200F05                      /*上1次广播校时异常时钟故障记录时间*/
#define CDoubleAgreementFlag                    0xFF200F06                      /*是否双协议的标志，主要是用于协议版本号一个还是两个*/
#define CCap_Vol                                0xFF201001                      /*超级电容电压*/
#define COneMin_AcPower_Pre_FF                  0xFF201100                      /*1分钟有功总平均功率数据块(6位小数)*/
#define COneMin_AcPower_Pre                     0xFF201101                      /*1分钟有功总平均功率*/
#define COneMin_AcPower_A_Pre                   0xFF201102                      /*1分钟有功总平均功率A*/
#define COneMin_AcPower_B_Pre                   0xFF201103                      /*1分钟有功总平均功率B*/
#define COneMin_AcPower_C_Pre                   0xFF201104                      /*1分钟有功总平均功率c*/
#define COneMin_RePower_Pre_FF                  0xFF201200                      /*1分钟无功总平均功率数据块(6位小数)*/
#define COneMin_RePower_Pre                     0xFF201201                      /*1分钟无功总平均功率*/
#define COneMin_RePower_A_Pre                   0xFF201202                      /*1分钟无功总平均功率A*/
#define COneMin_RePower_B_Pre                   0xFF201203                      /*1分钟无功总平均功率B*/
#define COneMin_RePower_C_Pre                   0xFF201204                      /*1分钟无功总平均功率C*/
/*事件模块*/
/*顺序与数据层关联*/
#define CAll_Loss_Vol_OADTabLen                 0xFF308201                      /*全失压可变关联列表OAD个数*/
#define CAux_Pow_Down_OADTabLen                 0xFF308202                      /*辅助电源掉电可变关联列表OAD个数*/
#define CPow_Down_OADTabLen                     0xFF308203                      /*电源掉电可变关联列表OAD个数*/
#define CPos_Ac_De_Over_OADTabLen               0xFF308204                      /*正向有功需量可变关联列表OAD个数*/
#define CRev_Ac_De_Over_OADTabLen               0xFF308205                      /*反向有功需量超限事件可变关联列表OAD个数*/
#define CQua_Re_De_Over_OADTabLen               0xFF308206                      /*无功需量超限可变关联列表OAD个数*/
#define CLoss_Vol_OADTabLen                     0xFF308207                      /*失压可变关联列表OAD个数*/
#define CLow_Vol_OADTabLen                      0xFF308208                      /*欠压可变关联列表OAD个数*/
#define COver_Vol_OADTabLen                     0xFF308209                      /*过压可变关联列表OAD个数*/
#define CBreak_Vol_OADTabLen                    0xFF30820A                      /*断相可变关联列表OAD个数*/
#define CRevPS_Vol_OADTabLen                    0xFF30820B                      /*电压逆相序可变关联列表OAD个数*/
#define CRevPS_Curr_OADTabLen                   0xFF30820C                      /*电流逆相序可变关联列表OAD个数*/
#define CNoBal_Vol_OADTabLen                    0xFF30820D                      /*电压不平衡可变关联列表OAD个数*/
#define CNoBal_Curr_OADTabLen                   0xFF30820E                      /*电流不平衡可变关联列表OAD个数*/
#define CSevNoBal_Curr_OADTabLen                0xFF30820F                      /*电流严重不平衡可变关联列表OAD个数*/
#define CLoss_Curr_OADTabLen                    0xFF308210                      /*失流可变关联列表OAD个数*/
#define COver_Curr_OADTabLen                    0xFF308211                      /*过流可变关联列表OAD个数*/
#define CBreak_Curr_OADTabLen                   0xFF308212                      /*断流可变关联列表OAD个数*/
#define CPower_Rev_OADTabLen                    0xFF308213                      /*功率反向可变关联列表OAD个数*/
#define COver_Lo_OADTabLen                      0xFF308214                      /*过载可变关联列表OAD个数*/
#define CTol_Clear_OADTabLen                    0xFF308215                      /*总清可变关联列表OAD个数*/
#define CDe_Clear_OADTabLen                     0xFF308216                      /*需清可变关联列表OAD个数*/
#define CEven_Clear_OADTabLen                   0xFF308217                      /*编程记录可变关联列表OAD个数*/
#define CProgram_OADTabLen                      0xFF308218                      /*异常插卡记录可变关联列表OAD个数*/
#define CAbnorC_OADTabLen                       0xFF308219                      /*异常插卡记录可变关联列表OAD个数*/
#define COpenW_OADTabLen                        0xFF30821A                      /*开盖记录可变关联列表OAD个数*/
#define COpenCW_OADTabLen                       0xFF30821B                      /*购电记录可变关联列表OAD个数*/
#define CBuyCurr_OADTabLen                      0xFF30821C                      /*购电记录可变关联列表OAD个数*/
#define CReturn_M_OADTabLen                     0xFF30821D                      /*退费记录可变关联列表OAD个数*/
#define CConM_OADTabLen                         0xFF30821E                      /*恒定磁场可变关联列表OAD个数*/
#define CRelayFa_OADTabLen                      0xFF30821F                      /*继电器异常可变关联列表OAD个数*/
#define CPowerFa_OADTabLen                      0xFF308220                      /*电源异常可变关联列表OAD个数*/
#define CRelayOpen_OADTabLen                    0xFF308221                      /*跳闸记录可变关联列表OAD个数*/
#define CRelayClose_OADTabLen                   0xFF308222                      /*合闸记录可变关联列表OAD个数*/
#define CPFactorT_Over_OADTabLen                0xFF308223                      /*总功率因数超限可变关联列表OAD个数*/
#define CAdjTime_OADTabLen                      0xFF308224                      /*时钟调整，1*/
#define CProgPT_OADTabLen                       0xFF308225                      /*时段表，1*/
#define CProgTZ_OADTabLen                       0xFF308226                      /*时区表，1*/
#define CProgWRe_OADTabLen                      0xFF308227                      /*周休日，1*/
#define CProgHol_OADTabLen                      0xFF308228                      /*节假日，1*/
#define CProgAcC_OADTabLen                      0xFF308229                      /*有功组合方式，1*/
#define CProgReC_OADTabLen                      0xFF30822A                      /*无功组合方式，1*/
#define CProgSettD_OADTabLen                    0xFF30822B                      /*结算日编程记录，1*/
#define CProgTPara_OADTabLen                    0xFF30822C                      /*费率表编程记录，1*/
#define CProgLad_OADTabLen                      0xFF30822D                      /*阶梯表编程记录，1*/
#define CProgKD_OADTabLen                       0xFF30822E                      /*密钥更新编程记录，1*/
#define CMeterFa_OADTabLen                      0xFF30822F                      /*计量芯片记录，1*/
#define CClockFa_OADTabLen                      0xFF308230                      /*时钟故障记录，1*/
#define CBroadcastTime_OADTabLen                0xFF308231                      /*广播校时记录，1*/
#define CNeutralCurrentAbnormal_OADTabLen       0xFF308232                      /*零线电流异常记录，1*/
#define CBroadTimeAbnormal_OADTabLen            0xFF308233                      /*广播校时异常记录，1*/

#define CVolage_Abnor_Vol                       0xFF308301                      /*电压异常判断电压*/
#define CLoss_Volage_Curr                       0xFF308302                      /*全失压电流*/
#define CLoss_Volage_Vol                        0xFF308303                      /*全失压电压*/
#define CRev_Phase_Vol                          0xFF308304                      /*逆相序判断电压*/
#define CRelayOpen_Vol__LowLim                  0xFF308305                      /*跳闸下门限*/
#define CRelayOpen_Vol__UpLim                   0xFF308306                      /*跳闸上门限*/
#define CProgReC1_Degree                        0xFF308401                      /*无功组合方式1编程记录总次数*/
#define CProgReC2_Degree                        0xFF308402                      /*无功组合方式2编程记录总次数*/

#define CLossA_Vol_Degree                       0xFF300002                      /*A相失压总次数*/
#define CLossB_Vol_Degree                       0xFF300003                      /*B相失压总次数*/
#define CLossC_Vol_Degree                       0xFF300004                      /*C相失压总次数*/
#define CLossA_Vol_Time                         0xFF30A002                      /*A相失压总累计时间*/
#define CLossB_Vol_Time                         0xFF30A003                      /*B相失压总累计时间*/
#define CLossC_Vol_Time                         0xFF30A004                      /*C相失压总累计时间*/
#define CLowA_Vol_Degree                        0xFF300102
#define CLowB_Vol_Degree                        0xFF300103
#define CLowC_Vol_Degree                        0xFF300104
#define CLowA_Vol_Time                          0xFF30A102                      /*A相欠压总累计时间*/
#define CLowB_Vol_Time                          0xFF30A103                      /*B相欠压总累计时间*/
#define CLowC_Vol_Time                          0xFF30A104                      /*C相欠压总累计时间*/
#define COverA_Vol_Degree                       0xFF300202                      /*A相过压总次数*/
#define COverB_Vol_Degree                       0xFF300203                      /*B相过压总次数*/
#define COverC_Vol_Degree                       0xFF300204                      /*C相过压总次数*/
#define COverA_Vol_Time                         0xFF30A202                      /*A相过压总累计时间*/
#define COverB_Vol_Time                         0xFF30A203                      /*B相过压总累计时间*/
#define COverC_Vol_Time                         0xFF30A204                      /*C相过压总累计时间*/
#define CBreakA_Vol_Degree                      0xFF300302                      /*A相断相总次数*/
#define CBreakB_Vol_Degree                      0xFF300303                      /*B相断相总次数*/
#define CBreakC_Vol_Degree                      0xFF300304                      /*C相断相总次数*/
#define CBreakA_Vol_Time                        0xFF30A302                      /*A相断相总累计时间*/
#define CBreakB_Vol_Time                        0xFF30A303                      /*B相断相总累计时间*/
#define CBreakC_Vol_Time                        0xFF30A304                      /*C相断相总累计时间*/
#define CLossA_Curr_Degree                      0xFF300402                      /*A相失流总次数*/
#define CLossB_Curr_Degree                      0xFF300403                      /*B相失流总次数*/
#define CLossC_Curr_Degree                      0xFF300404                      /*C相失流总次数*/
#define CLossA_Curr_Time                        0xFF30A402                      /*A相失流总累计时间*/
#define CLossB_Curr_Time                        0xFF30A403                      /*B相失流总累计时间*/
#define CLossC_Curr_Time                        0xFF30A404                      /*C相失流总累计时间*/
#define COverA_Curr_Degree                      0xFF300502                      /*A相过流总次数*/
#define COverB_Curr_Degree                      0xFF300503                      /*B相过流总次数*/
#define COverC_Curr_Degree                      0xFF300504                      /*C相过流总次数*/
#define COverA_Curr_Time                        0xFF30A502                      /*A相过流总累计时间*/
#define COverB_Curr_Time                        0xFF30A503                      /*B相过流总累计时间*/
#define COverC_Curr_Time                        0xFF30A504                      /*C相过流总累计时间*/
#define CBreakA_Curr_Degree                     0xFF300602                      /*A相断流总次数*/
#define CBreakB_Curr_Degree                     0xFF300603                      /*B相断流总次数*/
#define CBreakC_Curr_Degree                     0xFF300604                      /*C相断流总次数*/
#define CBreakA_Curr_Time                       0xFF30A602                      /*A相断流总累计时间*/
#define CBreakB_Curr_Time                       0xFF30A603                      /*B相断流总累计时间*/
#define CBreakC_Curr_Time                       0xFF30A604                      /*C相断流总累计时间*/
#define CPowerT_Rev_Degree                      0xFF300701                      /*总相功率反向总次数*/
#define CPowerA_Rev_Degree                      0xFF300702                      /*A相功率反向总次数*/
#define CPowerB_Rev_Degree                      0xFF300703                      /*B相功率反向总次数*/
#define CPowerC_Rev_Degree                      0xFF300704                      /*C相功率反向总次数*/
#define CPowerT_Rev_Time                        0xFF30A701                      /*总相功率反向总累计时间*/
#define CPowerA_Rev_Time                        0xFF30A702                      /*A相功率反向总累计时间*/
#define CPowerB_Rev_Time                        0xFF30A703                      /*B相功率反向总累计时间*/
#define CPowerC_Rev_Time                        0xFF30A704                      /*C相功率反向总累计时间*/
#define COverA_Lo_Degree                        0xFF300802                      /*A相过载总次数*/
#define COverB_Lo_Degree                        0xFF300803                      /*B相过载总次数*/
#define COverC_Lo_Degree                        0xFF300804                      /*C相过载总次数*/
#define COverA_Lo_Time                          0xFF30A802                      /*A相过载总累计时间*/
#define COverB_Lo_Time                          0xFF30A803                      /*B相过载总累计时间*/
#define COverC_Lo_Time                          0xFF30A804                      /*C相过载总累计时间*/
#define CPos_Ac_De_Over_Degree                  0xFF300900                      /*正向有功需量超限总次数*/
#define CPos_Ac_De_Over_Time                    0xFF30A900                      /*正向有功需量超限累计时间*/
#define CRev_Ac_De_Over_Degree                  0xFF300A00                      /*反向有功需量超限总次数*/
#define CRev_Ac_De_Over_Time                    0xFF30AA00                      /*反向有功需量超限累计时间*/
#define CQua1_Re_De_Over_Degree                 0xFF300B01                      /*1象限无功需量超限总次数*/
#define CQua2_Re_De_Over_Degree                 0xFF300B02                      /*2象限无功需量超限总次数*/
#define CQua3_Re_De_Over_Degree                 0xFF300B03                      /*3象限无功需量超限总次数*/
#define CQua4_Re_De_Over_Degree                 0xFF300B04                      /*4象限无功需量超限总次数*/
#define CQua1_Re_De_Over_Time                   0xFF30AB01                      /*1象限无功需量超限累计时间*/
#define CQua2_Re_De_Over_Time                   0xFF30AB02                      /*2象限无功需量超限累计时间*/
#define CQua3_Re_De_Over_Time                   0xFF30AB03                      /*3象限无功需量超限累计时间*/
#define CQua4_Re_De_Over_Time                   0xFF30AB04                      /*4象限无功需量超限累计时间*/
/*0xFF300C00*/
#define CAll_Loss_Vol_Degree                    0xFF300D00                      /*全失压总次数*/
#define CAll_Loss_Vol_Time                      0xFF30AD00                      /*全失压累计时间*/
#define CAux_Pow_Down_Degree                    0xFF300E00                      /*总次数*/
#define CAux_Pow_Down_Time                      0xFF30AE00                      /*总累计时间*/
#define CRevPS_Vol_Degree						0xFF300F00                      /*电压逆相序总次数*/
#define CRevPS_Vol_Time                         0xFF30AF00                      /*电压逆相序总累计时间*/
#define CRevPS_Curr_Degree                      0xFF301000                      /*电流逆相序总次数*/
#define CRevPS_Curr_Time                        0xFF30B000                      /*电流逆相序总累计时间*/
#define CPow_Down_Degree                        0xFF301100                      /*掉电总次数*/
#define CPow_Down_Time                          0xFF30B100                      /*掉电累计时间*/

#define CProgram_Degree                         0xFF301200                      /*编程记录总次数*/
#define CTol_Clear_Degree                       0xFF301300                      /*电表清零总次数*/
#define CDe_Clear_Degree                        0xFF301400                      /*需量清零总次数*/
#define CEven_Clear_Degree                      0xFF301500                      /*事件清零总次数*/
#define CAdjTime_Degree                         0xFF301600                      /*校时记录总次数*/
#define CProgPT_Degree                          0xFF301700                      /*时段表编程记录总次数*/
#define CProgTZ_Degree							0xFF301800						/*时区表编程记录总次数*/
#define CProgWRe_Degree                         0xFF301900                      /*周休日编程记录总次数*/
#define CProgSettD_Degree                       0xFF301A00                      /*结算日编程记录总次数*/

#define COpenW_Degree                           0xFF301B00                      /*开表盖记录总次数*/
#define COpenW_Time                             0xFF30BB00                      /*开表盖记录累计时间*/
#define COpenCW_Degree                          0xFF301C00                      /*开端钮盖记录总次数*/
#define COpenCW_Time                            0xFF30BC00                      /*开端钮盖累计时间*/
#define CNoBal_Vol_Degree						0xFF301D00                      /*电压不平衡总次数*/
#define CNoBal_Vol_Time							0xFF30BD00						/*电压不平衡总累计时间*/
#define CNoBal_Curr_Degree                      0xFF301E00                      /*电流不平衡总次数*/
#define CNoBal_Curr_Time                        0xFF30BE00                      /*电流不平衡总累计时间*/

#define CRelayOpen_Degree                       0xFF301F00                      /*跳闸记录总次数*/
#define CRelayClose_Degree                      0xFF302000                      /*合闸记录总次数*/
#define CProgHol_Degree                         0xFF302100                      /*节假日编程记录总次数*/
#define CProgAcC_Degree                         0xFF302200                      /*有功组合方式编程记录总次数*/
#define CProgReC_Degree                         0xFF302300                      /*无功组合方式编程记录总次数,包括无功1、无功2*/
#define CProgTPara_Degree                       0xFF302400                      /*费率参数表编程记录总次数*/
#define CProgLad_Degree                         0xFF302500                      /*阶梯表编程记录总次数*/
#define CProgKD_Degree                          0xFF302600                      /*密钥编程记录总次数*/
#define CAbnorC_Degree                          0xFF302700                      /*异常插卡记录总次数*/
#define CBuyCurr_Degree                         0xFF302800                      /*购电记录总次数*/
#define CReturn_M_Degree                        0xFF302900                      /*退费记录总次数*/

#define CConM_Degree                            0xFF302A00                      /*恒定磁场干扰记录总次数*/
#define CConM_Time                              0xFF30CA00                      /*恒定磁场干扰记录累计时间*/
#define CRelayFa_Degree                         0xFF302B00                      /*负荷开关误动作记录总次数*/
#define CRelayFa_Time                           0xFF30CB00                      /*负荷开关误动作记录累计时间*/
#define CPowerFa_Degree                         0xFF302C00                      /*电源异常记录总次数*/
#define CPowerFa_Time                           0xFF30CC00                      /*电源异常记录总累计时间*/
#define CSevNoBal_Curr_Degree                   0xFF302D00                      /*电流严重不平衡总次数*/
#define CSevNoBal_Curr_Time                     0xFF30CD00                      /*电流严重不平衡总累计时间*/
#define CClockFa_Degree                         0xFF302E00                      /*时钟故障记录总次数*/
#define CClockFa_Time                           0xFF30CE00                      /*时钟故障记录累计时间*/
#define CMeterFa_Degree                         0xFF302F00                      /*计量芯片故障记录总次数*/
#define CMeterFa_Time                           0xFF30CF00                      /*计量芯片故障记录累计时间*/

#define CPFactorT_Over_Degree                   0xFF303B01                      /*总功率因数超下限总次数*/
#define CPFactorA_Over_Degree                   0xFF303B02                      /*A相总功率因数超下限总次数*/
#define CPFactorB_Over_Degree                   0xFF303B03                      /*B相总功率因数超下限总次数*/
#define CPFactorC_Over_Degree                   0xFF303B04                      /*C相总功率因数超下限总次数*/
#define CPFactorT_Over_Time                     0xFF30DB01                      /*总功率因数超下限总累计时间*/
#define CPFactorA_Over_Time                     0xFF30DB02                      /*A相总功率因数超下限总累计时间*/
#define CPFactorB_Over_Time                     0xFF30DB03                      /*B相总功率因数超下限总累计时间*/
#define CPFactorC_Over_Time                     0xFF30DB04                      /*C相总功率因数超下限总累计时间*/
#define CBroadcastTime_Degree                   0xFF303C00                      /*广播校时记录总次数*/

#define CNeutralCurrentAbnormal_Degree          0xFF304000                      /*零线电流异常事件记录总次数*/
#define CNeutralCurrentAbnormal_Time            0xFF30E000                      /*零线电流异常事件记录累计时间*/

//
#define CSoft_I_J_Prog_1                        0xFF306001                      /*上1次软IJ编程记录*/
#define CSoft_I_J_Prog_2                        0xFF306002                      /*上2次软IJ编程记录*/

#define CRec_Meter_Degree                       0xFF306100                      /*校表总次数*/
#define CRec_Meter_Hp_T_1                       0xFF306101                      /*上1次校表发生时刻*/
#define CRec_Meter_Bef1_Data_254                0xFF3062FE                      /*上1次254号校表参数校表前数据*/

#define CProgPT_CurrentPart_Degree              0xFF306300                      /*时段表编程记录总次数*/
#define CProgPT_NoteC_1                         0xFF3064C1                      /*上1次时段表编程记录自扩C*/
#define CProgPT_NoteD_1                         0xFF3064D1                      /*上1次时段表编程记录自扩D*/
#define CProgPT_NoteE_1                         0xFF3064E1                      /*上1次时段表编程记录自扩E*/
#define CProgPT_NoteF_1                         0xFF3064F1                      /*上1次时段表编程记录自扩F*/

#define CProgTZ_CurrentPart_Degree              0xFF306500                      /*时区表编程记录总次数*/
#define CProgTZ_CurrentPart_Note_1              0xFF306501                      /*上1次时区表编程记录*/

#define CProgram_Degree_645_2                   0xFF306600                      /*编程记录总次数*/
#define CProgram_Note_1_645                     0xFF306701                      /*上1次编程记录*/

/*费率模块*/
#define CMeterRunStatic                         0xFF400200                      /*当前运行在第几套时区表、时段表。时区表在前（低地址）*/
#define CCurr_Rate_No                           0xFF400301                      /*当前费率号*/
#define CCurr_Step_No                           0xFF400302                      /*当前阶梯号*/
/*通信模块*/
#define CF1_TerUpCommParam                      0xFF440201                      /*F1终端上行通信参数*/
#define CF3_MainStaCommParam                    0xFF440202                      /*F3主站通信参数*/
#define CF4_SMSCommParam                        0xFF440203                      /*F4短信通信参数*/
#define CF7_TerminalIPAddr                      0xFF440204                      /*F7终端IP地址*/
#define CF8_ConnectParam                        0xFF440205                      /*F8连接参数*/
#define CF16_MoveAPNPassWord                    0xFF440206                      /*F16移动APN密码*/
#define CF89_TerminalAddr                       0xFF440207                      /*F89终端地址*/
#define CFactoryInMeterNum                      0xFF440301                      /*电表内部序号*/

#define CReportNewAddNum                        0xFF440401                      /*上报次数*/
#define CHaveReportState                        0xFF440402                      /*已上报标志*/
/*冻结模块*/
#define CI_Free_OADTabLen_T                     0xFF500201                      /*瞬时冻结OAD序号表实际长度及周期*/
#define CMin_Free_OADTabLen_T                   0xFF500202                      /*分钟冻结OAD序号表实际长度及周期*/
#define CH_Free_OADTabLen_T                     0xFF500203                      /*小时冻结OAD序号表实际长度及周期*/
#define CD_Free_OADTabLen_T                     0xFF500204                      /*日冻结OAD序号表实际长度及周期*/
#define CSett_Free_OADTabLen_T                  0xFF500205                      /*结算日冻结OAD序号表实际长度及周期*/
#define CM_Free_OADTabLen_T                     0xFF500206                      /*月冻结OAD序号表实际长度及周期*/
#define CYSettle_Free_OADTabLen_T               0xFF500207                      /*年冻结OAD序号表实际长度及周期，后改为阶梯结算*/
#define CTZ_Free_OADTabLen_T                    0xFF500208                      /*时区表切换冻结OAD序号表实际长度及周期*/
#define CPT_Free_OADTabLen_T                    0xFF500209                      /*日时段表切换冻结OAD序号表实际长度及周期*/
#define CR_Free_OADTabLen_T                     0xFF50020A                      /*费率电价切换冻结OAD序号表实际长度及周期*/
#define CL_Free_OADTabLen_T                     0xFF50020B                      /*阶梯电价切换冻结OAD序号表实际长度及周期*/
#if 0
#define CY_Free_OADTabLen_T                     0xFF50020C                      /*年冻结OAD序号表实际长度及周期*/
#endif

#define CI_Free_OADTab                          0xFF500301                      /*瞬时冻结OAD序号表*/
#define CMin_Free_OADTab                        0xFF500302                      /*分钟冻结OAD序号表*/
#define CH_Free_OADTab                          0xFF500303                      /*小时冻结OAD序号表*/
#define CD_Free_OADTab                          0xFF500304                      /*日冻结OAD序号表*/
#define CSett_Free_OADTab                       0xFF500305                      /*结算日冻结OAD序号表*/
#define CM_Free_OADTab                          0xFF500306                      /*月冻结OAD序号表*/
#define CYSettle_Free_OADTab                    0xFF500307                      /*年冻结OAD序号表，后改为阶梯结算*/
#define CTZ_Free_OADTab                         0xFF500308                      /*时区表切换冻结OAD序号表*/
#define CPT_Free_OADTab                         0xFF500309                      /*日时段表切换冻结OAD序号表*/
#define CR_Free_OADTab                          0xFF50030A                      /*费率电价切换冻结OAD序号表*/
#define CL_Free_OADTab                          0xFF50030B                      /*阶梯电价切换冻结OAD序号表*/
#if 0
#define CY_Free_OADTab                          0xFF50030C                      /*年冻结OAD序号表*/
#endif

#define CTotEnergyBlock_698                     0xFF500401                      /*用于645电能负荷抄读*/
#define CTotQua_Re_Block_698                    0xFF500402                      /*用于645四象限无功负荷抄读*/
#define CCurr_Demand_Block                      0xFF500500                      /*用于当前有功需量645*/
/*费控模块*/
#define CRelay_RemoteOrder                      0xFF800201                      /*远程控制命令*/
#define CRelay_State                            0xFF800202                      /*继电器状态*/
#define CRelay_LocalOrder                       0xFF800203                      /*本地控制命令*/
/*安全模块*/
#define CKey_Update_ID                          0xFFF10200                      /*密钥更新第1个标识码是操作者代码*/
#if 0
#define CTemp_Key_State0                        0xFFF10300                      /*临时密钥状态0*/
#define CTemp_Key_State31                       0xFFF1031F                      /*临时密钥状态31*/
#define CTemp_Key_StateFF                       0xFFF103FF                      /*临时密钥状态数据块*/
#define CTemp_Key_Save0                         0xFFF10400                      /*临时密钥存储0*/
#define CTemp_Key_Save31                        0xFFF1041F                      /*临时密钥存储31*/
#endif
#define CSafeModeParaNat3_Num                   0xFFF10501                      /*安全模式参数,属性3,元素个数*/

#define CID_Auth_Remain_Time_645                0xFFF10601                      /*645身份认证时效剩余时间*/
#define CInfra_Auth_Remain_Time_645             0xFFF10602                      /*645红外认证时效剩余时间*/
/*显示模块*/
#define CDisplayBorrowPoint                     0xFFF30201                      /*显示借位位数*/
#define CDisplayBorrowPoint_RecFlag             0xFFF30202                      /*显示借位位数矫正标志*/



#define C_EventDI 0x000000FF

#endif
