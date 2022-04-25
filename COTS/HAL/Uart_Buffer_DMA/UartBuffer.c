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
#include <MCAL/DMA/DMA.h>

static void UartBuffer_vidHandler1(void);
static void UartBuffer_vidHandler2(void);
static void UartBuffer_vidHandler6(void);
static void UartBuffer1_vidRecieveDone(void);
static void UartBuffer2_vidRecieveDone(void);
static void UartBuffer6_vidRecieveDone(void);

static UartBuffer_Cbf UartBuffer_Notification[UARTBUFFER_MAX_NOTIFICATION];
static Buffer_t * UartBuffer_TxSave[UARTBUFFER_NUMBER_MAX];
static Buffer_t * UartBuffer_RxSave[UARTBUFFER_NUMBER_MAX];
static u8 TxBusyFlag[UARTBUFFER_NUMBER_MAX];
static u8 RxBusyFlag[UARTBUFFER_NUMBER_MAX];

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
			Uart_ClearTCFlag(UartBuffer_Configurations[0].Uart_pvChannel);
			NVIC_EnableIRQ(USART1_IRQn);
			NVIC_EnableIRQ(DMA2_Stream2_IRQn);
			break;
		case (u32) UART_pvUART2:
			RCC_enuEnablePeripheralClk(RCC_u8APB1_BUS,RCC_u32APB1_USART2);
			Loc_Uart_Config.Uart_pvChannel = UART_pvUART2;
			Loc_Uart_Config.Uart_pfCallbackFnc = UartBuffer_vidHandler2;
			Uart_ClearTCFlag(UartBuffer_Configurations[1].Uart_pvChannel);
			NVIC_EnableIRQ(USART2_IRQn);
			NVIC_EnableIRQ(DMA1_Stream5_IRQn);

			break;
		case (u32) UART_pvUART6:
			RCC_enuEnablePeripheralClk(RCC_u8APB2_BUS,RCC_u32APB2_USART6);
			Loc_Uart_Config.Uart_pvChannel = UART_pvUART6;
			Loc_Uart_Config.Uart_pfCallbackFnc = UartBuffer_vidHandler6;
			Uart_ClearTCFlag(UartBuffer_Configurations[2].Uart_pvChannel);
			NVIC_EnableIRQ(USART6_IRQn);
			NVIC_EnableIRQ(DMA2_Stream1_IRQn);
			break;
		}
		/*INIT THE UART*/
		Loc_Uart_Config.Uart_u16BaudRate = UartBuffer_Configurations[Loc_u8Iter].Uart_u16BaudRate;
		Loc_Uart_Config.Uart_u16OverSamplingMode = UartBuffer_Configurations[Loc_u8Iter].Uart_u16OverSamplingMode;
		Uart_vidInit(&Loc_Uart_Config);
		Uart_ClearTCFlag(UartBuffer_Configurations[Loc_u8Iter].Uart_pvChannel);

	}
	RCC_enuEnablePeripheralClk(RCC_u8AHB1_BUS , RCC_u32AHB1_DMA1);
	RCC_enuEnablePeripheralClk(RCC_u8AHB1_BUS , RCC_u32AHB1_DMA2);



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
UartBuffer_tenuErrorStatus UsartBuffer_enuRegisterCbf(u8 Copy_u8Channel,u8 Copy_u8Mode ,UartBuffer_Cbf Add_pfCbf)
{
	UartBuffer_tenuErrorStatus Loc_enuReturnStatus = UartBuffer_enuOk;
	/*VALIDATE THE ARGS*/
	if(Copy_u8Channel > UARTBUFFER_NUMBER_MAX || Copy_u8Mode > UARTBUFFER_u8MODE_RX)
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
		UartBuffer_Notification[Copy_u8Channel + Copy_u8Mode] = Add_pfCbf;
	}

	return Loc_enuReturnStatus;
}
/*
 * Function:  UsartBuffer_enuSendBufferDMAZCopy
 * --------------------
 * SEND BUFFER OF DATA USING DMA
 *
 *  Copy_u8Channel: DESIRED CHANNEL
 *	Add_pstrBuffer: ADDRESS OF THE BUFFER.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK UartBuffer_tenuErrorStatus ERROR ABOVE.
 */
extern UartBuffer_tenuErrorStatus UsartBuffer_enuSendBufferDMAZCopy(u8 Copy_u8Channel,Buffer_t * Add_pstrBuffer)
{
	UartBuffer_tenuErrorStatus Loc_enuReturnStatus = UartBuffer_enuOk;
	DMA_tstrInitConfig Loc_InitDmaCfg ={
			.DMA_Callback = NULL,
			.DMA_pvNumber = DMA_pvDMA_NUM2,
			.DMA_u16NumberOfData = (u16) Add_pstrBuffer->Size,
			.DMA_u32ChannelSelect = DMA_u32CHANNEL_SELECT_CH4,
			.DMA_u32CircularMode = DMA_u32CIRCULAR_MODE_OFF,
			.DMA_u32Direction = DMA_u32DIRECTION_MTP,
			.DMA_u32InterruptCtrl = DMA_u32INTERRUPT_OFF,
			.DMA_pvMemoryAddress = (void *) Add_pstrBuffer->Data,
			.DMA_u32MemoryDataSize = DMA_u32MEMORY_DATA_1BYTE,
			.DMA_u32MemoryIncrementMode = DMA_u32MEMORY_INC_MODE_ON,
			.DMA_u32Periority = DMA_u32PERIORITY_HIGH,
			.DMA_pvPeripheralAddress = (void *) ((u32) UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel + 0x04),
			.DMA_u32PeripheralDataSize= DMA_u32PERIPHERAL_DATA_1BYTE,
			.DMA_u32PeripheralIncrementMode = DMA_u32PERIPHERAL_INC_MODE_FIXED,
			.DMA_u8StreamSelect = DMA_u8STREAM_SELECT_ST7
	};
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
	else if(TxBusyFlag[Copy_u8Channel] == 1)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorBusy;
	}
	else
	{
		/*SAVE THE BUFFER*/
		UartBuffer_TxSave[Copy_u8Channel] = Add_pstrBuffer;
		/*INIT USED TO BE USED AS COUNTER*/
		UartBuffer_TxSave[Copy_u8Channel]->Used = 0;
		/*CHECK IF THE SIZE OF BUFFER NOT EQ Z*/


		DMA_enuInit(&Loc_InitDmaCfg);
		Uart_ClearTCFlag(UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel);
		Uart_vidDMACtrl(UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel  , UART_u32DMA_TRANS_ENABLE);
		/*ASSIGN BUSY FLAG*/
		TxBusyFlag[Copy_u8Channel] = 1;
		DMA_enuStart(&Loc_InitDmaCfg);



	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}
/*
 * Function:  UsartBuffer_enuRecieveBufferDMAZCopy
 * --------------------
 * Receive BUFFER OF DATA DMA
 *
 *  Copy_u8Channel: DESIRED CHANNEL
 *	Add_pstrBuffer: ADDRESS OF THE BUFFER.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK UartBuffer_tenuErrorStatus ERROR ABOVE.
 */
extern UartBuffer_tenuErrorStatus UsartBuffer_enuRecieveBufferDMAZCopy(u8 Copy_u8Channel,Buffer_t * Add_pstrBuffer)
{
	UartBuffer_tenuErrorStatus Loc_enuReturnStatus = UartBuffer_enuOk;
	DMA_tstrInitConfig Loc_InitDmaCfg ={
			.DMA_u16NumberOfData = (u16) Add_pstrBuffer->Size,
			.DMA_u32CircularMode = DMA_u32CIRCULAR_MODE_OFF,
			.DMA_u32Direction = DMA_u32DIRECTION_PTM,
			.DMA_u32InterruptCtrl = DMA_u32INTERRUPT_TRANS_COMPLETE,
			.DMA_pvMemoryAddress = (void *) Add_pstrBuffer->Data,
			.DMA_u32MemoryDataSize = DMA_u32MEMORY_DATA_1BYTE,
			.DMA_u32MemoryIncrementMode = DMA_u32MEMORY_INC_MODE_ON,
			.DMA_u32Periority = DMA_u32PERIORITY_HIGH,
			.DMA_pvPeripheralAddress = (void *) ((u32) UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel + 0x04),
			.DMA_u32PeripheralDataSize= DMA_u32PERIPHERAL_DATA_1BYTE,
			.DMA_u32PeripheralIncrementMode = DMA_u32PERIPHERAL_INC_MODE_FIXED,
	};

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
	else if(RxBusyFlag[Copy_u8Channel] == 1)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorBusy;
	}
	else
	{
		switch((u32) UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel )
		{
			case (u32) UART_pvUART1:
					Loc_InitDmaCfg.DMA_pvNumber = DMA_pvDMA_NUM2;
					Loc_InitDmaCfg.DMA_u32ChannelSelect = DMA_u32CHANNEL_SELECT_CH4;
					Loc_InitDmaCfg.DMA_u8StreamSelect = DMA_u8STREAM_SELECT_ST2;
					Loc_InitDmaCfg.DMA_Callback= UartBuffer1_vidRecieveDone;
				break;

			case (u32) UART_pvUART2:
					Loc_InitDmaCfg.DMA_pvNumber = DMA_pvDMA_NUM1;
					Loc_InitDmaCfg.DMA_u32ChannelSelect = DMA_u32CHANNEL_SELECT_CH4;
					Loc_InitDmaCfg.DMA_u8StreamSelect = DMA_u8STREAM_SELECT_ST5;
					Loc_InitDmaCfg.DMA_Callback= UartBuffer2_vidRecieveDone;
				break;
			case (u32) UART_pvUART6:
					Loc_InitDmaCfg.DMA_pvNumber = DMA_pvDMA_NUM2;
					Loc_InitDmaCfg.DMA_u32ChannelSelect = DMA_u32CHANNEL_SELECT_CH5;
					Loc_InitDmaCfg.DMA_u8StreamSelect = DMA_u8STREAM_SELECT_ST1;
					Loc_InitDmaCfg.DMA_Callback= UartBuffer6_vidRecieveDone;
				break;
		}
		/*CHECK IF THE SIZE OF BUFFER NOT EQ Z*/
		DMA_enuInit(&Loc_InitDmaCfg);
		Uart_vidDMACtrl(UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel  , UART_u32DMA_RECIEVE_ENABLE);
		/*ASSIGN BUSY FLAG*/
		RxBusyFlag[Copy_u8Channel] = 1;
		DMA_enuStart(&Loc_InitDmaCfg);



	}
	/*RETURN AN ERROR STATUS*/
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
	else if(TxBusyFlag[Copy_u8Channel] == 1)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorBusy;
	}
	else
	{
		/*ASSIGN BUSY FLAG*/
		TxBusyFlag[Copy_u8Channel] = 1;
		/*SAVE THE BUFFER*/
		UartBuffer_TxSave[Copy_u8Channel] = Add_pstrBuffer;
		/*INIT USED TO BE USED AS COUNTER*/
		UartBuffer_TxSave[Copy_u8Channel]->Used = 1;
		/*CHECK IF THE SIZE OF BUFFER NOT EQ Z*/
		if(UartBuffer_TxSave[Copy_u8Channel]->Size != 0 )
		{
			/*SEND THE DATA*/
			Uart_enuTransmiteData(UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel , Add_pstrBuffer->Data[0] );
		}
		else{
			/*SAVE AN RETURN STATUS ERROR*/
			Loc_enuReturnStatus = UartBuffer_enuErrorBufferSize;
			/*RESET THE BUSY FLAG*/
			TxBusyFlag[Copy_u8Channel] = 0;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}

/*
 * Function:  UsartBuffer_enuReadBufferZCopy
 * --------------------
 * READ BUFFER OF DATA
 *
 *  Copy_u8Channel: DESIRED CHANNEL
 *	Add_pstrBuffer: ADDRESS OF THE BUFFER.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK UartBuffer_tenuErrorStatus ERROR ABOVE.
 */
UartBuffer_tenuErrorStatus UsartBuffer_enuRecieveBufferZCopy(u8 Copy_u8Channel,Buffer_t * Add_pstrBuffer)
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
	else if(RxBusyFlag[Copy_u8Channel] == 1)
	{
		Loc_enuReturnStatus = UartBuffer_enuErrorBusy;
	}
	else
	{
		/*ASSIGN BUSY FLAG*/
		RxBusyFlag[Copy_u8Channel] = 1;
		/*SAVE THE BUFFER*/
		UartBuffer_RxSave[Copy_u8Channel] = Add_pstrBuffer;
		/*INIT USED TO BE USED AS COUNTER*/
		UartBuffer_RxSave[Copy_u8Channel]->Used = 0;
		/*CHECK IF THE SIZE OF BUFFER NOT EQ Z*/
		if(UartBuffer_RxSave[Copy_u8Channel]->Size != 0 )
		{
			Uart_enuControlRXNEInterrupt(UartBuffer_Configurations[Copy_u8Channel].Uart_pvChannel , UART_u8INTERRUPT_ENABLE);
		}
		else{
			/*SAVE AN RETURN STATUS ERROR*/
			Loc_enuReturnStatus = UartBuffer_enuErrorBufferSize;
			/*RESET THE BUSY FLAG*/
			RxBusyFlag[Copy_u8Channel] = 0;
		}
	}
	/*RETURN AN ERROR STATUS*/
	return Loc_enuReturnStatus;
}


static void UartBuffer1_vidRecieveDone(void)
{
	DMA_vidClearFlag(DMA_pvDMA_NUM2 , DMA_u64INTERRUPT_CH2_TRANS_COMPLETE|DMA_u64INTERRUPT_CH2_HALF_TRANS_COMPLETE);
	RxBusyFlag[0] = 0;
	if(UartBuffer_Notification[1])
	{
		UartBuffer_Notification[1]();
	}
}
static void UartBuffer2_vidRecieveDone(void)
{
	DMA_vidClearFlag(DMA_pvDMA_NUM1 , DMA_u64INTERRUPT_CH5_TRANS_COMPLETE|DMA_u64INTERRUPT_CH5_HALF_TRANS_COMPLETE);
	RxBusyFlag[1] = 0;
	if(UartBuffer_Notification[3])
	{
		UartBuffer_Notification[3]();
	}
}
static void UartBuffer6_vidRecieveDone(void)
{
	DMA_vidClearFlag(DMA_pvDMA_NUM2 , DMA_u64INTERRUPT_CH1_TRANS_COMPLETE|DMA_u64INTERRUPT_CH1_HALF_TRANS_COMPLETE);
	RxBusyFlag[2] = 0;
	if(UartBuffer_Notification[5])
	{
		UartBuffer_Notification[5]();
	}
}

static void UartBuffer_vidHandler1(void)
{
	u8 TC_Flag;
	Uart_ReadTCFlag(UART_pvUART1 , &TC_Flag);
	if(TC_Flag && TxBusyFlag[0])
	{
		TxBusyFlag[0] = 0;
		Uart_ClearTCFlag(UartBuffer_Configurations[0].Uart_pvChannel);
		DMA_vidClearFlag(DMA_pvDMA_NUM2 , DMA_u64INTERRUPT_CH7_TRANS_COMPLETE|DMA_u64INTERRUPT_CH7_HALF_TRANS_COMPLETE);
		if(UartBuffer_Notification[0])
		{
			UartBuffer_Notification[0]();
		}
	}
	else{
		Uart_ClearTCFlag(UartBuffer_Configurations[0].Uart_pvChannel);

	}

}
static void UartBuffer_vidHandler2(void)
{
	u8 TC_Flag;
	Uart_ReadTCFlag(UART_pvUART2 , &TC_Flag);
	if(TC_Flag && TxBusyFlag[1])
	{
		TxBusyFlag[1] = 0;
		Uart_ClearTCFlag(UartBuffer_Configurations[1].Uart_pvChannel);
		DMA_vidClearFlag(DMA_pvDMA_NUM1 , DMA_u64INTERRUPT_CH6_TRANS_COMPLETE|DMA_u64INTERRUPT_CH6_HALF_TRANS_COMPLETE);
		if(UartBuffer_Notification[2])
		{
			UartBuffer_Notification[2]();
		}
	}
	else{
		Uart_ClearTCFlag(UartBuffer_Configurations[1].Uart_pvChannel);

	}
}
static void UartBuffer_vidHandler6(void)
{
	u8 TC_Flag;
	Uart_ReadTCFlag(UART_pvUART6 , &TC_Flag);
	if(TC_Flag && TxBusyFlag[2])
	{
		TxBusyFlag[1] = 0;
		Uart_ClearTCFlag(UartBuffer_Configurations[2].Uart_pvChannel);
		DMA_vidClearFlag(DMA_pvDMA_NUM2 , DMA_u64INTERRUPT_CH6_TRANS_COMPLETE|DMA_u64INTERRUPT_CH6_HALF_TRANS_COMPLETE);
		if(UartBuffer_Notification[4])
		{
			UartBuffer_Notification[4]();
		}
	}
	else{
		Uart_ClearTCFlag(UartBuffer_Configurations[2].Uart_pvChannel);

	}
}
