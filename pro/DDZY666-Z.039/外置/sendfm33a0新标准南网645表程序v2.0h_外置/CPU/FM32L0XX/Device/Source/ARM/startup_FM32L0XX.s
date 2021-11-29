;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp	


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
				DCD     WWDT_IRQHandler           ; 0:  WWDT   	“Ï≥£±‡∫≈16
				DCD     SVD_IRQHandler            ; 1:  SVD		“Ï≥£±‡∫≈17 	
				DCD     RTC_IRQHandler            ; 2:  RTC 	
				DCD     NVMIF_IRQHandler          ; 3:  NVMIF	
				DCD     FDET_IRQHandler           ; 4:  FDET	
				DCD     ADC_IRQHandler            ; 5:  ADC	
				DCD     HSPI_IRQHandler           ; 6:  HSPI	
				DCD     SPI1_IRQHandler           ; 7:  SPI1 	
				DCD     SPI2_IRQHandler           ; 8:  SPI2	
				DCD     UART0_IRQHandler          ; 9:  UART0	
				DCD     UART1_IRQHandler          ; 10:  UART1	
				DCD     UART2_IRQHandler          ; 11:  UART2	
				DCD     UART3_IRQHandler          ; 12:  UART3	
				DCD     UART4_IRQHandler          ; 13:  UART4	
				DCD     UART5_IRQHandler          ; 14:  UART5	
				DCD     USART0_IRQHandler         ; 15:  USART0	
				DCD     USART1_IRQHandler         ; 16:  USART1	
				DCD     I2C_IRQHandler            ; 17:  I2C	
				DCD     DISP_IRQHandler           ; 18:  DISP	
				DCD     AES_IRQHandler         	  ; 19:  AES	
				DCD     LPTIM_IRQHandler          ; 20:  LPTIM	
				DCD     DMA_IRQHandler            ; 21:  DMA	
				DCD     TRNG_IRQHandler           ; 22:  TRNG	
				DCD     COMP_IRQHandler           ; 23:  COMP	
				DCD     BT1_IRQHandler            ; 24:  BT1
				DCD     BT2_IRQHandler            ; 25:  BT2
				DCD     ETIMER1_IRQHandler        ; 26:  ETIMER1	
				DCD     ETIMER2_IRQHandler        ; 27:  ETIMER2	
				DCD     ETIMER3_IRQHandler        ; 28:  ETIMER3	
				DCD     ETIMER4_IRQHandler        ; 39:  ETIMER4	
                DCD     GPIO_IRQHandler           ; 30:  GPIO 
                DCD     0            		      ; 31: Reserved
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

															 ;0µÿ÷∑¥Ê∑≈MSP÷µ
; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]     ;“Ï≥£±‡∫≈£∫1°£1*4=4µÿ÷∑£¨∏¥ŒªœÚ¡ø
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]   	;“Ï≥£±‡∫≈£∫2°£2*4=0x8µÿ÷∑
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]   	;“Ï≥£±‡∫≈£∫3°£3*4=0xCµÿ÷∑
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]	;“Ï≥£±‡∫≈£∫4°£4*4=0x10µÿ÷∑
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]	;“Ï≥£±‡∫≈£∫11°£11*4=0x2Cµÿ÷∑
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]	;“Ï≥£±‡∫≈£∫15°£15*4=0x3Cµÿ÷∑
                B       .
                ENDP

Default_Handler PROC

                EXPORT  GPIO_IRQHandler            	[WEAK]      ;“Ï≥£±‡∫≈£∫46°£46*4=0xB8µÿ÷∑
                EXPORT  ETIMER4_IRQHandler         	[WEAK]		;“Ï≥£±‡∫≈£∫45°£45*4=0xB4µÿ÷∑
                EXPORT  ETIMER3_IRQHandler           	[WEAK]
                EXPORT  ETIMER2_IRQHandler           	[WEAK]
                EXPORT  ETIMER1_IRQHandler           [WEAK]
                EXPORT  BT2_IRQHandler           [WEAK]
                EXPORT  BT1_IRQHandler          [WEAK]
                EXPORT  COMP_IRQHandler          [WEAK]
                EXPORT  TRNG_IRQHandler          [WEAK]
                EXPORT  DMA_IRQHandler          [WEAK]
                EXPORT  LPTIM_IRQHandler          [WEAK]
                EXPORT  AES_IRQHandler           [WEAK]
                EXPORT  DISP_IRQHandler           [WEAK]
                EXPORT  I2C_IRQHandler           [WEAK]
                EXPORT  USART1_IRQHandler           [WEAK]
                EXPORT  USART0_IRQHandler           [WEAK]
                EXPORT  UART5_IRQHandler           [WEAK]	
                EXPORT  UART4_IRQHandler           [WEAK]
                EXPORT  UART3_IRQHandler           [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  SPI2_IRQHandler        [WEAK]
                EXPORT  SPI1_IRQHandler            [WEAK]
                EXPORT  HSPI_IRQHandler            [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  FDET_IRQHandler       [WEAK]
                EXPORT  NVMIF_IRQHandler            [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  SVD_IRQHandler       [WEAK]				;“Ï≥£±‡∫≈£∫17°£17*4=0x44µÿ÷∑
                EXPORT  WWDT_IRQHandler            [WEAK]		;“Ï≥£±‡∫≈£∫16°£16*4=0x40µÿ÷∑

GPIO_IRQHandler
ETIMER4_IRQHandler
ETIMER3_IRQHandler
ETIMER2_IRQHandler
ETIMER1_IRQHandler
BT2_IRQHandler
BT1_IRQHandler
COMP_IRQHandler
TRNG_IRQHandler
DMA_IRQHandler
LPTIM_IRQHandler
AES_IRQHandler
DISP_IRQHandler
I2C_IRQHandler
USART1_IRQHandler
USART0_IRQHandler
UART5_IRQHandler
UART4_IRQHandler
UART3_IRQHandler
UART2_IRQHandler
UART1_IRQHandler
UART0_IRQHandler
SPI2_IRQHandler
SPI1_IRQHandler
HSPI_IRQHandler
ADC_IRQHandler
FDET_IRQHandler
NVMIF_IRQHandler
RTC_IRQHandler
SVD_IRQHandler
WWDT_IRQHandler

                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                ALIGN

                ENDIF


                END
					
 *****END OF FILE*****