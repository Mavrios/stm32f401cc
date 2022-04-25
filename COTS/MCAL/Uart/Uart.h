/*
 * Uart.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Kishk
 */

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

/******************************************** TYPEDEF ********************************************/
typedef void (* Uart_Cbf) (void);

typedef struct{
	void * Uart_pvChannel;
	u16    Uart_u16DataLength;
	u16	   Uart_u16BaudRate;
	u16    Uart_u16OverSamplingMode;
	u16    Uart_u16InterruptsCtrl;
	u16	   Uart_u16TransmittingCtrl;
	u16	   Uart_u16ReceivingCtrl;
	u16	   Uart_u16StopBits;
	Uart_Cbf Uart_pfCallbackFnc;
}Uart_Cfg_t;

typedef enum{
	Uart_enuOk,
	Uart_enuErrorNullPointer,
	Uart_enuErrorOverSampling,
	Uart_enuErrorInterruptStatus,
	Uart_enuErrorDmaState

}Uart_tenuErrorStatus;

/********************************************* MACROS *********************************************/
#define UART_pvUART1				((void *) 0x40011000)
#define UART_pvUART2				((void *) 0x40004400)
#define UART_pvUART6				((void *) 0x40011400)

#define UART_u16OVERSAMPLING_BY_16		((u16) 0x0000)
#define UART_u16OVERSAMPLING_BY_8		((u16) 0x8000)

#define UART_u16DATA_LENGTH_8BIT		((u16) 0x0)
#define UART_u16DATA_LENGTH_9BIT		((u16) 0x1000)

#define UART_u16INTERRUPT_TXE			((u16) 0x0080)
#define UART_u16INTERRUPT_TC			((u16) 0x0040)
#define UART_u16INTERRUPT_RXNE			((u16) 0x0020)



#define UART_u16TRANSMITTER_ENABLE		((u16) 0x0008)
#define UART_u16TRANSMITTER_DISABLE		((u16) 0x0000)

#define UART_u16RECIEVER_ENABLE			((u16) 0x0004)
#define UART_u16RECIEVER_DISABLE		((u16) 0x0000)


#define UART_u16STOPBIT_1BIT			((u16)	0x0000)
#define UART_u16STOPBIT_HALFBIT			((u16)  0x1000)
#define UART_u16STOPBIT_2BIT			((u16)  0x2000)
#define UART_u16STOPBIT_ONE_HALF_BIT	((u16)  0x3000)


#define UART_u8TXE_EMPTY					((u8) 0x01)
#define UART_u8TXE_NOT_EMPTY				((u8) 0x00)


#define UART_u8TX_COMPLETE					((u8) 0x01)
#define UART_u8TX_NOT_COMPLETE				((u8) 0x00)

#define UART_u8RX_NOTEMPTY					((u8) 0x01)
#define UART_u8RX_EMPTY						((u8) 0x00)

#define UART_u8INTERRUPT_ENABLE				((u8) 0x01)
#define UART_u8INTERRUPT_DISABLE			((u8) 0x00)

#define UART_u32DMA_TRANS_ENABLE			((u32) 0x00000080)
#define UART_u32DMA_TRANS_DISABLE			((u32) 0xFFFFFF7F)
#define UART_u32DMA_RECIEVE_ENABLE			((u32) 0x00000040)
#define UART_u32DMA_RECIEVE_DISABLE			((u32) 0xFFFFFFBF)
/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  Uart_vidInit
 * --------------------
 * INITIALIZE THE UART BASED ON POST PASSED CONFIGURATIONS.
 *
 *	Add_pstrCfg: CONFIGURATIONS CHECK STRUCT FOR MORE INFO
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */

extern Uart_tenuErrorStatus Uart_vidInit(Uart_Cfg_t * Add_pstrCfg);
/*
 * Function:  Uart_vidDMACtrl
 * --------------------
 * CONTROL UART DMA FEATURE.
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Copy_u32DmaState : DESIRED STATE OPTIONS--> (UART_u32DMA_xxxx)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */

extern Uart_tenuErrorStatus Uart_vidDMACtrl(void * Add_pvChannel ,u32 Copy_u32DmaState);
/*
 * Function:  Uart_enuTransmiteData
 * --------------------
 * TRANSMIT BYTE THROUGH UART.
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Copy_u16Data : DESIRED DATA TO BE TRAMSMITTED
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */

extern Uart_tenuErrorStatus Uart_enuTransmiteData(void * Add_pvChannel , u16 Copy_u16Data);
/*
 * Function:  Uart_enuRecieveData
 * --------------------
 * RECIEVE BYTE FROM UART.
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Add_pu16Data : DESIRED DATA TO BE TRAMSMITTED
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */

extern Uart_tenuErrorStatus Uart_enuRecieveData(void * Add_pvChannel , pu16 Add_pu16Data);
/*
 * Function:  Uart_ReadTXEFlag
 * --------------------
 * READ TXE FLAG
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Add_pu8FlagStatus : ADDRESSED TO RETURN THE FLAG RESULT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */
extern Uart_tenuErrorStatus Uart_ReadTXEFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus);
/*
 * Function:  Uart_ReadRXNEFlag
 * --------------------
 * READ TXNE FLAG
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Add_pu8FlagStatus : ADDRESSED TO RETURN THE FLAG RESULT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */
extern Uart_tenuErrorStatus Uart_ReadRXNEFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus);
/*
 * Function:  Uart_ReadTCFlag
 * --------------------
 * READ TCF FLAG
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Add_pu8FlagStatus : ADDRESSED TO RETURN THE FLAG RESULT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */
extern Uart_tenuErrorStatus Uart_ReadTCFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus);
/*
 * Function:  Uart_ReadTCFlag
 * --------------------
 * CLEAR TCF FLAG
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */
extern Uart_tenuErrorStatus Uart_ClearTCFlag	  (void * Add_pvChannel);
/*
 * Function:  Uart_enuControlRXNEInterrupt
 * --------------------
 * CONTROL INTERRUPT FOR RXNE FLAG
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Copy_u8InterruptStatus: INTERRUPT STATUS OPTIONS (UART_u8INTERRUPT_x)
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */
extern Uart_tenuErrorStatus Uart_enuControlRXNEInterrupt(void * Add_pvChannel,u8 Copy_u8InterruptStatus);

#endif /* MCAL_UART_UART_H_ */
