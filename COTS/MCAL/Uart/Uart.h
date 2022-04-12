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


#define UART_u8TXE_EMPTY					1
#define UART_u8TXE_NOT_EMPTY				0


#define UART_u8TX_COMPLETE					1
#define UART_u8TX_NOT_COMPLETE				0
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

Uart_tenuErrorStatus Uart_vidInit(Uart_Cfg_t * Add_pstrCfg);
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

Uart_tenuErrorStatus Uart_enuTransmiteData(void * Add_pvChannel , u16 Copy_u16Data);
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
Uart_tenuErrorStatus Uart_ReadTXEFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus);
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
Uart_tenuErrorStatus Uart_ReadTCFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus);
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
Uart_tenuErrorStatus Uart_ClearTCFlag	  (void * Add_pvChannel);



#endif /* MCAL_UART_UART_H_ */
