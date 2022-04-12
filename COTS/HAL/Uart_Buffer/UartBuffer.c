/*
 * Uart_buffer.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Kishk
 */



#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <MCAL/Uart/Uart.h>
#include <HAL/Uart_Buffer/UartBuffer.h>
#include <HAL/Uart_Buffer/UartBuffer_cfg.h>
#include <HAL/Uart_Buffer/UartBuffer_prv.h>
#include <MCAL/RCC/RCC.h>
#include <MCAL/NVIC/NVIC.h>

static void UartBuffer_vidHandler1(void);
static void UartBuffer_vidHandler2(void);
static void UartBuffer_vidHandler6(void);

static UartBuffer_Cbf UartBuffer_Notification[UARTBUFFER_NUMBER_MAX];
static Buffer_t * UartBuffer_Save[UARTBUFFER_NUMBER_MAX];
static u8 Loc_BusyFlag[UARTBUFFER_NUMBER_MAX];

/*
 * Function:  UsartBuffer_enuInit
 * --------------------
 * INITIALIZE UART TO BE USED TO SEND BUFFER OF DATA
 *
 */
void UsartBuffer_enuInit(void)
{
	/*DECLARE VARIABLES*/
	u8 Loc_u8Iter;
	Uart_Cfg_t Loc_Uart_Config;
	/*INITIALIZE UART CONFIGURATIONS*/
	Loc_Uart_Config.Uart_u16DataLength = UART_u16DATA_LENGTH_8BIT;
	Loc_Uart_Config.Uart_u16InterruptsCtrl = UART_u16INTERRUPT_TC;
	Loc_Uart_Config.Uart_u16ReceivingCtrl = UART_u16RECIEVER_ENABLE;
	Loc_Uart_Config.Uart_u16TransmittingCtrl= UART_u16TRANSMITTER_ENABLE;
	Loc_Uart_Config.Uart_u16StopBits= UART_u16STOPBIT_1BIT;
	/*LOOP IN THE CONFIG CHANNEL*/
	for(Loc_u8Iter = 0 ; Loc_u8Iter < NUM_OF_UART ; Loc_u8Iter++)
	{
		/*SWITCH FOR EVERY CHANNEL*/
		switch((u32) (UartBuffer_Configurations[Loc_u8Iter].Uart_pvChannel))
		{
		/*
		 * ENABLE THE PERIPHERAL CLK
		 * SET CONFIGURATIONS FOR UART CONFIG
		 * ENABLE IRQ FOR CHANNEL
		 * */
		case (u32) UART_pvUART1:
			RCC_enuEnablePeripheralClk(RCC_u8APB2_BUS,RCC_u32APB2_USART1);
			Loc_Uart_Config.Uart_pvChannel = UART_pvUART1;
			Loc_Uart_Config.Uart_pfCallbackFnc = UartBuffer_vidHandler1;
			NVIC_EnableIRQ(USART1_IRQn);
			break;
		case (u32) UART_pvUART2:
			RCC_enuEnablePeripheralClk(RCC_u8APB1_BUS,RCC_u32APB1_USART2);
			Loc_Uart_Config.Uart_pvChannel = UART_pvUART2;
			Loc_Uart_Config.Uart_pfCallbackFnc = UartBuffer_vidHandler2;
			NVIC_EnableIRQ(USART2_IRQn);
			break;
		case (u32) UART_pvUART6:
			RCC_enuEnablePeripheralClk(RCC_u8APB2_BUS,RCC_u32APB2_USART6);
			Loc_Uart_Config.Uart_pvChannel = UART_pvUART6;
			Loc_Uart_Config.Uart_pfCallbackFnc = UartBuffer_vidHandler6;
			NVIC_EnableIRQ(USART6_IRQn);
			break;
		}
		/*INIT THE UART*/
		Loc_Uart_Config.Uart_u16BaudRate = UartBuffer_Configurations[Loc_u8Iter].Uart_u16BaudRate;
		Loc_Uart_Config.Uart_u16OverSamplingMode = UartBuffer_Configurations[Loc_u8Iter].Uart_u16OverSamplingMode;
		Uart_vidInit(&Loc_Uart_Config);
	}


}

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
UartBuffer_tenuErrorStatus UsartBuffer_enuRegisterCbf(u8 Copy_u8Channel,UartBuffer_Cbf Add_pfCbf)
{
	UartBuffer_tenuErrorStatus Loc_enuReturnStatus = UartBuffer_enuOk;
	/*VALIDATE THE ARGS*/
	if(Copy_u8Channel > UARTBUFFER_NUMBER_MAX)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorChannel;
	}
	else if(Add_pfCbf == NULL)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorNullPointer;
	}
	else
	{
		/*SAVE THE CBF*/
		UartBuffer_Notification[Copy_u8Channel] = Add_pfCbf;
	}

	return Loc_enuReturnStatus;
}

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
UartBuffer_tenuErrorStatus UsartBuffer_enuSendBufferZCopy(u8 Copy_u8Channel,Buffer_t * Add_pstrBuffer)
{
	UartBuffer_tenuErrorStatus Loc_enuReturnStatus = UartBuffer_enuOk;
	/*VALIDATE THE ARGUMMENTS*/
	if(Copy_u8Channel > UARTBUFFER_NUMBER_MAX)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorChannel;
	}
	else if(Add_pstrBuffer == NULL)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorNullPointer;
	}
	/*CHECK IF THE CHANNEL IS BUSY*/
	else if(Loc_BusyFlag[Copy_u8Channel] == 1)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorBusy;
	}
	else
	{
		/*ASSIGN BUSY FLAG*/
		Loc_BusyFlag[Copy_u8Channel] = 1;
		/*SAVE THE BUFFER*/
		UartBuffer_Save[Copy_u8Channel] = Add_pstrBuffer;
		/*INIT USED TO BE USED AS COUNTER*/
		UartBuffer_Save[Copy_u8Channel]->Used = 1;
		/*CHECK IF THE SIZE OF BUFFER NOT EQ Z*/
		if(UartBuffer_Save[Copy_u8Channel]->Size != 0 )
		{
			/*SEND THE DATA*/
			Uart_enuTransmiteData(UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel , Add_pstrBuffer->Data[0] );
		}
		else{
			/*SAVE AN RETURN STATUS ERROR*/
			Loc_enuReturnStatus = UartBuffer_enuErrorBufferSize;
			/*RESET THE BUSY FLAG*/
			Loc_BusyFlag[Copy_u8Channel] = 0;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

static void UartBuffer_vidHandler1(void)
{
	u8 TC_Flag;
	Uart_ReadTCFlag(UART_pvUART1 , &TC_Flag);
	if(TC_Flag)
	{
		if(UartBuffer_Save[0]->Used == UartBuffer_Save[0]->Size)
		{
			Loc_BusyFlag[0] = 0;
			Uart_ClearTCFlag(UartBuffer_Configurations[0].Uart_pvChannel);
			UartBuffer_Notification[0]();
		}
		else
		{
			Uart_enuTransmiteData(UartBuffer_Configurations[0].Uart_pvChannel , UartBuffer_Save[0]->Data[UartBuffer_Save[0]->Used] );
			(UartBuffer_Save[0]->Used)++;
		}
	}
}
static void UartBuffer_vidHandler2(void)
{
	u8 TC_Flag;
	Uart_ReadTCFlag(UART_pvUART1 , &TC_Flag);
	if(TC_Flag)
	{
		if(UartBuffer_Save[1]->Used == UartBuffer_Save[1]->Size)
		{
			Loc_BusyFlag[1] = 0;
			UartBuffer_Notification[1]();
		}
		else
		{
			Uart_enuTransmiteData(UartBuffer_Configurations[1].Uart_pvChannel , UartBuffer_Save[1]->Data[UartBuffer_Save[1]->Used] );
			UartBuffer_Save[1]->Used++;
		}
	}
}
static void UartBuffer_vidHandler6(void)
{
	u8 TC_Flag;
	Uart_ReadTCFlag(UART_pvUART1 , &TC_Flag);
	if(TC_Flag)
	{
		if(UartBuffer_Save[2]->Used == UartBuffer_Save[2]->Size)
		{
			Loc_BusyFlag[2] = 0;
			UartBuffer_Notification[2]();
		}
		else
		{
			Uart_enuTransmiteData(UartBuffer_Configurations[2].Uart_pvChannel , UartBuffer_Save[2]->Data[UartBuffer_Save[2]->Used] );
			UartBuffer_Save[2]->Used++;
		}
	}
}
