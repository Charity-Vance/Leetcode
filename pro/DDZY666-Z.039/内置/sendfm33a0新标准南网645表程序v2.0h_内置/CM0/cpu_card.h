/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*
// <h> USART0
*/
// <h> 7816ͨ�����ƼĴ���

/*
//    <o.0> ͨ��������ʹ�ܿ���λ

//       <0=> ��������Ч
//       <1=> ��������Ч
//    <o.1> ͨ��ǿ����ʹ�ܿ���λ

//       <0=> ǿ������Ч
//       <1=> ǿ������Ч
//    <o.2> ͨ�����ݷ���ǿ���������Զ���Ч����λ

//       <0=> ���ݷ���ʱ���������Զ���Ч���ܽ�ֹ������������HPUEN��LPUEN����
//       <1=> ���ݷ���ʱ���������Զ���Ч������̬����������Ч
//    <o.3> ʱ��CLK���ʹ�ܿ���λ

//       <0=> ʱ�������ֹ
//       <1=> ʱ�����ʹ��
//    <o.4> ͨ������ʹ�ܿ���λ

//       <0=> ͨ�����ս�ֹ�����ɽ������ݣ����ض�����˿�
//       <1=> ͨ������ʹ�ܣ��ɽ�������
//    <o.5> ͨ������ʹ�ܿ���λ

//       <0=> ͨ�����ͽ�ֹ�����ɷ������ݣ����ض�����˿�
//       <1=> ͨ������ʹ�ܣ��ɷ�������
// </h>
*/

#define DEF_USART0CTRL   ((uint32_t)0x00000006U) /*!< */
// <h> 7816֡��ʽ���ƼĴ���

/*
//    <o.0> ������򣬱��뷽ʽѡ��

//       <0=> ������룬���շ�LSB
//       <1=> ������룬���շ�MSB
//    <o.1> ����������żУ���Ĵ���ʽѡ��

//       <0=> ��żУ������Զ�����ERROR SIGNAL
//       <1=> ��żУ�������T=0Э���Զ��ط�ERROR SIGNAL��
//    <o.2> ������������żУ���Ĵ���ʽѡ��

//       <0=> �յ�Error signalʱ�������Զ��ط�
//       <1=> �յ���żУ������־��error signal��������T��0Э���Զ����лط���
//    <o.3> Guard Time���ȿ���λ������ʱ�ϸ���Э��2etu��
//       <0=> Guard timeΪ2 etu
//       <1=> Guard timeΪ1 etu

//    <o.4..5> ��żУ������ѡ��
//       <0=> Even
//       <1=> Odd
//       <2=> Always 1
//       <3=> ��У�鴦��
//    <o.6> ���ƽ���������żУ�����ʱ�Զ��ط�����

//       <0=> 1��
//       <1=> 3��
//    <o.7> BGT��block guard time������λ��

//       <0=> BGT��ֹ��������Block guard time(22 etu);
//       <1=> BGTʹ�ܣ�����Block guard time(22 etu);

//    <o.8> ERROR SIGNAL��GUARDTIME���ѡ�񣨽��ڷ���ʱ��Ч��

//       <0=> ERROR SIGNAL��GUARDTIMEΪ2~2.5ETU��
//       <1=> ERROR SIGNAL��GUARDTIMEΪ1~1.5ETU��
//    <o.9..10> ERROR SIGNAL���ѡ��

//       <0=> ERROR SIGNAL���Ϊ2ETU;
//       <1=> ERROR SIGNAL���Ϊ2ETU;
//       <2=> ERROR SIGNAL���Ϊ1.5ETU;
//       <3=> ERROR SIGNAL���Ϊ1ETU;
// </h>
*/

#define DEF_USART0FRC   ((uint32_t)0x00000286U) /*!< */

// <h> 7816 EGT���üĴ���

/*
//    <o.0..7> EGT����<0-255>
//  <i> ����ʱ�����EGTʱ�䣨��ETUΪ��λ��
// </h>
*/

#define DEF_USART0EGT   ((uint32_t)0x00000000U) /*!< */
// <h> 7816 ����ʱ�ӷ�Ƶ�Ĵ���

/*
//    <o.0..4> ��Ƶ����<0-31>
//  <i> U7816ʱ�������Ƶ���ƼĴ���������7816����ʱ�ӷ�Ƶ����
//  <i> U7816����ʱ����APBCLK�ķ�Ƶ��ϵ��
//  <i> F7816=FAPBCLK/(CLKDIV+1)
//  <i> ���������CLK_DIV���ó�0��1ʱ��F7816=FAPBCLK/2
//  <i> ע��7816Э��涨�Ĺ���ʱ�ӷ�Χ��1~5MHZ��

// </h>
*/

#define DEF_USART0CLKDIV   ((uint32_t)0x00000001U) /*!< */
// <h> 7816 Ԥ��Ƶ���ƼĴ���

/*
//    <o.0..11> Ԥ��Ƶ����<0-4095>
//  <i> U7816Ԥ��Ƶ���ƼĴ���������7816ͨ�ŷ�Ƶ�ȣ������ʣ�
//  <i> Baud �� F7816/(PDIV �� 1)


// </h>
*/

#define DEF_USART0CLKPDIV   ((uint32_t)0x00000173U) /*!< */
// <h> 7816 �ж�ʹ�ܼĴ���

/*
//    <q.0> ���ݽ����ж�ʹ��λ
//    <q.1> ���ݷ����ж�ʹ��λ
//    <q.2> ��·״̬�ж�ʹ��
// </h>
*/

#define DEF_USART0IE   ((uint32_t)0x00000000U) /*!< */

/*
// </h>
*/

//*** <<< end of configuration section >>>    ***

//USART_Type *USART0;

#define DEF_USART0RX_EN       B0001_0000
#define DEF_USART0TX_EN       B0010_0000
#define DEF_USART0CLK_EN      B0000_1000

#define	U7816CTRL0				USART0->U7816CTRL	//7816ͨ��0�˿ڿ��ƼĴ���
#define	U7816FRMCTRL0			    	USART0->U7816FRC	//7816֡��ʽ���ƼĴ���0
#define	U7816EGTCTRL0			    	USART0->U7816EGT	//7816 EGT���üĴ���
#define	U7816CLKDIV0				USART0->U7816CLKDIV	//7816����ʱ�ӷ�Ƶ���ƼĴ���
#define	U7816PREDIV0				USART0->U7816PDIV	//7816Ԥ��Ƶ���ƼĴ���
#define	U7816RXBUF0				USART0->U7816RXBUF	//7816���ݽ��ջ���Ĵ���
#define	U7816TXBUF0				USART0->U7816TXBUF	//7816���ݷ��ͻ���Ĵ���
#define	U7816INTEN0				USART0->U7816IE		//7816�ж�ʹ�ܼĴ���
#define	U7816PRIMARYSTATUS0			USART0->U7816IF		//7816��״̬�Ĵ���
#define	U7816ERRSTATUS0			  	USART0->U7816ERR	//7816������Ϣ�Ĵ���
#define	U7816SECONDSTATUS0		  	USART0->U7816STA	//7816��״̬�Ĵ���

#define	U7816CTRL1				USART1->U7816CTRL	//7816ͨ��0�˿ڿ��ƼĴ���
#define	U7816FRMCTRL1			    	USART1->U7816FRC	//7816֡��ʽ���ƼĴ���0
#define	U7816EGTCTRL1			    	USART1->U7816EGT	//7816 EGT���üĴ���
#define	U7816CLKDIV1				USART1->U7816CLKDIV	//7816����ʱ�ӷ�Ƶ���ƼĴ���
#define	U7816PREDIV1				USART1->U7816PDIV	//7816Ԥ��Ƶ���ƼĴ���
#define	U7816RXBUF1				USART1->U7816RXBUF	//7816���ݽ��ջ���Ĵ���
#define	U7816TXBUF1				USART1->U7816TXBUF	//7816���ݷ��ͻ���Ĵ���
#define	U7816INTEN1				USART1->U7816IE		//7816�ж�ʹ�ܼĴ���
#define	U7816PRIMARYSTATUS1			USART1->U7816IF		//7816��״̬�Ĵ���
#define	U7816ERRSTATUS1			  	USART1->U7816ERR	//7816������Ϣ�Ĵ���
#define	U7816SECONDSTATUS1		 	USART1->U7816STA	//7816��״̬�Ĵ���

//-------------- CPU ---------------------------
#define		OK_CARD_PROC		0	//��Ƭ�����ɹ�
#define		IC_VLOW_ERR		1	//��Ƶ�ѹ����176V(80%Un)
#define		IC_ESAM_RDWR_ERR	2	//����ESAM����
#define		IC_ESAM_RST_ERR		3	//ESAM��λ����
#define		IC_IC_RST_ERR		4	//��Ƭ��λ����:���忨�����Ƭ
#define		IC_AUTH_ERR		5	//�����֤����(ͨ�ųɹ������Ĳ�ƥ��)
#define		IC_EXAUTH_ERR		6	//�ⲿ�����֤����(ͨ�ųɹ�����֤��ͨ��)
#define		IC_NOFX_ERR		7	//δ���еĿ�Ƭ(����Ƭʱ����6B00)
#define		IC_TYPE_ERR		8	//�����ʹ���
#define		IC_KER_ERR		9	//��Ƭ����δ��Ȩ����Կ״̬��Ϊ��Կ�ǲ����Ԥ�ƿ�
#define		IC_MAC_ERR		10	//MACУ�����(6988)
#define		IC_ID_ERR		11	//��Ų�һ��
#define		IC_HUHAO_ERR		12	//�ͻ���Ų�һ��
#define		IC_SERIAL_ERR		13	//����Ų�һ��
#define		IC_FORMAT_ERR		14	//��Ƭ�ļ���ʽ���Ϸ�
#define		IC_NOOPEN_ERR		15	//���翨����δ�������
#define		IC_NOOPEN2_ERR		16	//��������δ�������
#define		IC_TIMES_ERR		17	//�����������
#define		IC_NONULL_ERR		18	//�û�����д��Ϣ�ļ���Ϊ��
#define		IC_NOIN_ERR		19	//������ƬͨѶ����(��д��Ƭʧ��)
#define		IC_PREIC_ERR		20	//��ǰ�ο�
#define		IC_OVERMAX_ERR		21	//ʣ����ڻ�
//-------------- CPU end -----------------------
