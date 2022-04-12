/*
 * Uart_buffer.h
 *
 *  Created on: Apr 10, 2022
 *      Author: Kishk
 */

#ifndef HAL_UART_BUFFER_UARTBUFFER_H_
#define HAL_UART_BUFFER_UARTBUFFER_H_
#include "UartBuffer_cfg.h"
/*******************************************  TYPEDEF  ****************************************************/
typedef struct{
	void * Uart_pvChannel;
	u16	   Uart_u16BaudRate;
	u16    Uart_u16OverSamplingMode;
}UartBuffer_Cfg_t;


typedef enum{
	UartBuffer_enuOk,
	UartBuffer_enuErrorChannel,
	UartBuffer_enuErrorNullPointer,
	UartBuffer_enuErrorBufferSize,
	UartBuffer_enuErrorBusy,

}UartBuffer_tenuErrorStatus;
typedef void (*UartBuffer_Cbf) (void);

/********************************************** PROTOTYPES ***************************************************/
/*
 * Function:  UsartBuffer_enuInit
 * --------------------
 * INITIALIZE UART TO BE USED TO SEND BUFFER OF DATA
 *
 */
extern void UsartBuffer_enuInit(void);
/*
 * Function:  UsartBuffer_enuRegisterCbf
 * --------------------
 * REGISTER AN CBF TO BE CALLED AFTER FINISHING SENDING BUFFER
 *
 *  Copy_u8Channel: DESIRED CHANNEL
 *	Add_pfCbf: ADDRESS OF THE CALLBACK FUNCTION.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK UartBuffer_tenuErrorStatus ERROR ABOVE.
 */
UartBuffer_tenuErrorStatus UsartBuffer_enuRegisterCbf(u8 Copy_u8Channel,UartBuffer_Cbf Add_pfCbf);
/*
 * Function:  UsartBuffer_enuSendBufferZCopy
 * --------------------
 * SEND BUFFER OF DATA
 *
 *  Copy_u8Channel: DESIRED CHANNEL
 *	Add_pstrBuffer: ADDRESS OF THE BUFFER.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK UartBuffer_tenuErrorStatus ERROR ABOVE.
 */
extern UartBuffer_tenuErrorStatus UsartBuffer_enuSendBufferZCopy(u8 Copy_u8Channel,Buffer_t * Add_pstrBuffer);
/********************************************** EXTERN ***************************************************/
extern const UartBuffer_Cfg_t UartBuffer_Configurations[];

#endif /* HAL_UART_BUFFER_UARTBUFFER_H_ */
