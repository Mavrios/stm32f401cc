/*
 * Uart.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <SERVICES/stm32f401cc.h>
#include <MCAL/Uart/Uart.h>
#include <MCAL/Uart/Uart_cfg.h>
#include <MCAL/Uart/Uart_prv.h>

/*ISR PROTOTYPES*/
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);

/*GLOBAL VARIABLE TO STORE THE CALLBACK FUNCTIONS*/
Uart_Cbf Uart_Callback[UART_u8NUM_OF_INTERRUPTS];


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


Uart_tenuErrorStatus Uart_vidInit(Uart_Cfg_t * Add_pstrCfg) {
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	/*DECLARE POINTER FROM USART REGISTER DATA TYPE TO POINT ON THE PASSED CHABBEL*/
	Usart_Regitsers_t * Loc_pstrUartChannel;
	/*VARIABLE TO BE USED ON BAUDRATE CALCULATIONS*/
	f32 Loc_Fraction = 0;
	u32 Loc_u32BaudRate;
	/*VALIDATE THE POINTERS*/
	if (Add_pstrCfg == NULL || Add_pstrCfg->Uart_pvChannel == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else if (Add_pstrCfg->Uart_u16OverSamplingMode
			& UART_u16VALIDATE_OVERSAMPLING) {
		Loc_enuReturnStatus = Uart_enuErrorOverSampling;
	} else {
		/*CALULCATE THE BAUDRATE IF THE OVER8 -> 1 */
		if (Add_pstrCfg->Uart_u16OverSamplingMode == UART_u16OVERSAMPLING_BY_8) {
			Loc_Fraction = (f32) ((UART_SYS_CLOCK)
					/ (8 * Add_pstrCfg->Uart_u16BaudRate));
			Loc_u32BaudRate = (u32) Loc_Fraction;
			Loc_Fraction = (f32) (Loc_Fraction - (f32) Loc_u32BaudRate);
			Loc_Fraction *= 8;
			Loc_u32BaudRate <<= 4;
			Loc_u32BaudRate |= (u32) (Loc_Fraction + 0.5);
			Loc_u32BaudRate &= UART_u16BAUDRATE_VALIDATE;
		} else {
			/*CALCULATE THE BAUDRATE IF THE OVER8->0*/
			Loc_Fraction = (f32) ((UART_SYS_CLOCK)
					/ (16 * Add_pstrCfg->Uart_u16BaudRate));
			Loc_u32BaudRate = (u32) Loc_Fraction;
			Loc_Fraction = (f32) (Loc_Fraction - (f32) Loc_u32BaudRate);
			Loc_Fraction *= 16;
			Loc_u32BaudRate <<= 4;
			Loc_u32BaudRate |= (u32) (Loc_Fraction + 0.5);
		}
		/*ASSIGN PASSED UART CONFIGURATIONS*/
		Loc_pstrUartChannel = Add_pstrCfg->Uart_pvChannel;
		Loc_pstrUartChannel->USART_CR1 &= UART_u16CR1_CLRMSK;
		Loc_pstrUartChannel->USART_CR1 |= (Add_pstrCfg->Uart_u16OverSamplingMode
				| Add_pstrCfg->Uart_u16DataLength | UART_u16ENABLE
				| Add_pstrCfg->Uart_u16InterruptsCtrl
				| Add_pstrCfg->Uart_u16TransmittingCtrl
				| Add_pstrCfg->Uart_u16ReceivingCtrl);
		Loc_pstrUartChannel->USART_CR2 &= UART_u16CR2_CLRMSK;
		Loc_pstrUartChannel->USART_CR2 |= Add_pstrCfg->Uart_u16StopBits;
		Loc_pstrUartChannel->USART_BRR = Loc_u32BaudRate;
		Loc_pstrUartChannel->USART_SR &=UART_u16CLEAR_TC;
		/*SWITCH ON CHANNEL TO ASSIGN THE CALLBACK FUNCTIONS*/
		switch ((u32)Add_pstrCfg->Uart_pvChannel) {
		case (u32) UART_pvUART1:
			Uart_Callback[UART_USART1] = Add_pstrCfg->Uart_pfCallbackFnc;
			break;
		case (u32) UART_pvUART2:
			Uart_Callback[UART_USART2] = Add_pstrCfg->Uart_pfCallbackFnc;
			break;
		case (u32) UART_pvUART6:
			Uart_Callback[UART_USART6] = Add_pstrCfg->Uart_pfCallbackFnc;
			break;
		}
	}

	return Loc_enuReturnStatus;
}

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

extern Uart_tenuErrorStatus Uart_vidDMACtrl(void * Add_pvChannel ,u32 Copy_u32DmaState)
{
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	/*ASSIGN THE PASSED CHANNEL INTO POINTER WITH VALID DATATYPE*/
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE CHANNEL*/
	if (Add_pvChannel == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		switch(Copy_u32DmaState)
		{
		case UART_u32DMA_TRANS_ENABLE:
			Loc_pstrUartChannel->USART_CR3 |=Copy_u32DmaState;
			break;
		case UART_u32DMA_RECIEVE_ENABLE:
			Loc_pstrUartChannel->USART_CR3 |=Copy_u32DmaState;
			break;
		case UART_u32DMA_TRANS_DISABLE:
			Loc_pstrUartChannel->USART_CR3 &=Copy_u32DmaState;
			break;
		case UART_u32DMA_RECIEVE_DISABLE:
			Loc_pstrUartChannel->USART_CR3 &=Copy_u32DmaState;
			break;
		default:
			Loc_enuReturnStatus = Uart_enuErrorDmaState;
			break;
		}
	}
	/*RETURN THE RETURN STATUS*/
	return Loc_enuReturnStatus;
}


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

Uart_tenuErrorStatus Uart_enuTransmiteData(void * Add_pvChannel,
		u16 Copy_u16Data) {
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	/*ASSIGN THE PASSED CHANNEL INTO POINTER WITH VALID DATATYPE*/
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE CHANNEL*/
	if (Add_pvChannel == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		if((Loc_pstrUartChannel->USART_SR & UART_u16SU_TXE) && (Copy_u16Data & UART_u16DR_VALIDATE) == 0)

		/*ASSIGN THE DATA INTO DR*/
		Loc_pstrUartChannel->USART_DR = Copy_u16Data;
	}
	/*RETURN THE RETURN STATUS*/
	return Loc_enuReturnStatus;
}



/*
 * Function:  Uart_enuRecieveData
 * --------------------
 * TRANSMIT BYTE THROUGH UART.
 *
 *	Add_pvChannel: DESIRED CHANNEL OPTIONS (UART_pvUARTx)
 *	Copy_u16Data : DESIRED DATA TO BE TRAMSMITTED
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK Uart_tenuErrorStatus ERROR ENUM.
 */
Uart_tenuErrorStatus Uart_enuRecieveData(void * Add_pvChannel,
		pu16  Add_pu16Data) {
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	/*ASSIGN THE PASSED CHANNEL INTO POINTER WITH VALID DATATYPE*/
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE CHANNEL*/
	if (Add_pvChannel == NULL || Add_pu16Data == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		if((Loc_pstrUartChannel->USART_SR & UART_u16SU_RXNE))

		/*ASSIGN THE DATA INTO DR*/
			*Add_pu16Data =(u16) (Loc_pstrUartChannel->USART_DR);
	}
	/*RETURN THE RETURN STATUS*/
	return Loc_enuReturnStatus;
}

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
Uart_tenuErrorStatus Uart_ReadTXEFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus)
{
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE ARGUMENTS*/
	if (Add_pvChannel == NULL ||  Add_pu8FlagStatus == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		/*READ THE FLAG AND ASSIGN THE RESULT*/
		if(Loc_pstrUartChannel->USART_SR & UART_u16SU_TXE )
		{
			*Add_pu8FlagStatus = UART_u8TXE_EMPTY;
		}
		else
		{
			*Add_pu8FlagStatus = UART_u8TXE_NOT_EMPTY;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

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
Uart_tenuErrorStatus Uart_ReadTCFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus)
{
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE ARGUMENTS*/
	if (Add_pvChannel == NULL ||  Add_pu8FlagStatus == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		/*READ THE FLAG AND ASSIGN THE RESULT*/
		if(Loc_pstrUartChannel->USART_SR & UART_u16SU_TC )
		{
			*Add_pu8FlagStatus = UART_u8TX_COMPLETE;
		}
		else
		{
			*Add_pu8FlagStatus = UART_u8TX_NOT_COMPLETE;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}
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
Uart_tenuErrorStatus Uart_ClearTCFlag	  (void * Add_pvChannel)
{
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus;
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE ARGUMENTS*/

	if (Add_pvChannel == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		/*CLEAR TC FLAG*/
		Loc_pstrUartChannel->USART_SR &=UART_u16CLEAR_TC;

	}

	return Loc_enuReturnStatus;
}


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
extern Uart_tenuErrorStatus Uart_ReadRXNEFlag	  (void * Add_pvChannel , pu8 Add_pu8FlagStatus)
{
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE ARGUMENTS*/
	if (Add_pvChannel == NULL ||  Add_pu8FlagStatus == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	} else {
		/*READ THE FLAG AND ASSIGN THE RESULT*/
		if(Loc_pstrUartChannel->USART_SR & UART_u16SU_RXNE )
		{
			*Add_pu8FlagStatus = UART_u8RX_NOTEMPTY;
		}
		else
		{
			*Add_pu8FlagStatus = UART_u8RX_EMPTY;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;

}


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
extern Uart_tenuErrorStatus Uart_enuControlRXNEInterrupt(void * Add_pvChannel,u8 Copy_u8InterruptStatus)
{
	/*DECLARE RETURN STATUS AND INIT WITH OK*/
	Uart_tenuErrorStatus Loc_enuReturnStatus = Uart_enuOk;
	Usart_Regitsers_t * Loc_pstrUartChannel = Add_pvChannel;
	/*VALIDATE ON THE ARGUMENTS*/
	if (Add_pvChannel == NULL) {
		Loc_enuReturnStatus = Uart_enuErrorNullPointer;
	}
	else {
		switch(Copy_u8InterruptStatus)
		{
			case UART_u8INTERRUPT_ENABLE:
				Loc_pstrUartChannel->USART_CR1 |= UART_u32CR1_RXNEIE;
				break;
			case UART_u8INTERRUPT_DISABLE:
				Loc_pstrUartChannel->USART_CR1 &= ~(UART_u32CR1_RXNEIE);
				break;
			default:
				Loc_enuReturnStatus = Uart_enuErrorInterruptStatus;
				break;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;

}
/*******************************************ISR****************************************************/
void USART1_IRQHandler(void) {
	if(Uart_Callback[UART_USART1])
	{
		Uart_Callback[UART_USART1]();
	}
}

void USART2_IRQHandler(void) {
	if(Uart_Callback[UART_USART2])
	{
		Uart_Callback[UART_USART2]();
	}
}
void USART6_IRQHandler(void) {
	if(Uart_Callback[UART_USART6])
	{
		Uart_Callback[UART_USART6]();
	}
}
