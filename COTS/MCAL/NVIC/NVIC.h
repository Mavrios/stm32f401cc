/*
 * NVIC.h
 *
 *  Created on: Mar 28, 2022
 *      Author: Kishk
 */

#ifndef MCAL_NVIC_H_
#define MCAL_NVIC_H_

/******************************************** TYPEDEF ********************************************/
typedef enum{
	NVIC_enuOk,
	NVIC_enuErrorIRQNumber,
	NVIC_enuErrorNumberOfGrouping,
	NVIC_enuErrorSubGroup,
	NVIC_enuErrorNullPointer,
}NVIC_ErrorStatus_t;

typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  FPU_IRQn                    = 81,      /*!< FPU global interrupt                                             */
  SPI4_IRQn                   = 84       /*!< SPI4 global Interrupt                                            */
} Nvic_tenuIRQn;

/********************************************* MACROS *********************************************/
#define NVIC_u8PENDING_ON			((u8) 0x01)
#define NVIC_u8PENDING_OFF			((u8) 0x00)

#define NVIC_u32SUB_GROUP_NONE		((u32) 0x00000000)
#define NVIC_u32SUB_GROUP_ONE		((u32) 0x00000400)
#define NVIC_u32SUB_GROUP_TWO		((u32) 0x00000500)
#define NVIC_u32SUB_GROUP_THREE		((u32) 0x00000600)
#define NVIC_u32SUB_GROUP_FOUR		((u32) 0x00000700)

/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  NVIC_EnableIRQ
 * --------------------
 * ENABLE IRQ FOR SPECIFIC PERIPHERAL
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_EnableIRQ(Nvic_tenuIRQn Copy_enuIRQn);
/*
 * Function:  NVIC_DisableIRQ
 * --------------------
 * DISABLE IRQ FOR SPECIFIC PERIPHERAL
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_DisableIRQ(Nvic_tenuIRQn Copy_enuIRQn);
/*
 * Function:  NVIC_GetPendingIRQ
 * --------------------
 * READ PENDING FOR SPECIFIC IRQ
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 * Add_pu8Pending: ADDRESS OF VARIABLE TO STORE RESULT INSIDE IT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_GetPendingIRQ (Nvic_tenuIRQn Copy_enuIRQn , pu8 Add_pu8Pending);
/*
 * Function:  NVIC_SetPendingIRQ
 * --------------------
 * SET PENDING FOR SPECIFIC IRQ
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_SetPendingIRQ (Nvic_tenuIRQn Copy_enuIRQn);
/*
 * Function:  NVIC_ClearPendingIRQ
 * --------------------
 * CLEAR PENDING FOR SPECIFIC IRQ
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_ClearPendingIRQ (Nvic_tenuIRQn Copy_enuIRQn);
/*
 * Function:  NVIC_GetActive
 * --------------------
 * GET PENDING FOR SPECIFIC IRQ
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 * Add_pu8Active: ADDRESS OF VARIABLE TO STORE THE RESULT INSIDE IT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_GetActive (Nvic_tenuIRQn Copy_enuIRQn , pu8 Add_pu8Active);
/*
 * Function:  NVIC_SetPriority
 * --------------------
 * SET PERIORITY FOR SPECIFIC IRQ
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 * Copy_u8Priority: DESIRED PERIORITY WITH SUBGROUP PERIORITY
 *
 * NOTE: YOU CAN USE "getEncodingPriority" TO CALCULATE THE PERIORITY.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_SetPriority (Nvic_tenuIRQn Copy_enuIRQn, u8 Copy_u8Priority);
/*
 * Function:  NVIC_setSubGroup
 * --------------------
 * CONFIGURE NUMBER OF BITS TO USE IN PERIORITY
 *
 * Copy_u32SubGroup: OPTIONS --> NVIC_u32SUB_GROUP_xxx
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_setSubGroup (u32 Copy_u32SubGroup);
/*
 * Function:  NVIC_GetPriority
 * --------------------
 * READ CURRENT PERIORITY FOR SPECIFIC IRQ
 *
 * Copy_enuIRQn: NUMBER OF DESIRED IRQ
 * Add_pu8Priority: ADDRESS OF VARIABLE TO STORE THE RESULT INSIDE IT.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_GetPriority (Nvic_tenuIRQn Copy_enuIRQn, pu8 Add_pu8Priority);
/*
 * Function:  getEncodingPriority
 * --------------------
 * FUNCTION TO ENCODE PERIORITY TO BE USED IN "NVIC_SetPriority" FUNCTION.
 *
 * Number_of_Sub_Group: NUMBER OF SUB GROUP BITS.
 * Sub_Group_Priority: SUB-GROUP PERIORITY
 * PreemptionPeriority: PREEMPTION PERIORITY.
 *
 *  returns: THE ENCODED VALUE TO BE USED INSIDE "NVIC_SetPriority" FUNCTION.
 */
u32 getEncodingPriority(u8 Number_of_Sub_Group, u8 Sub_Group_Priority,u8 PreemptionPeriority);


#endif /* MCAL_NVIC_H_ */
