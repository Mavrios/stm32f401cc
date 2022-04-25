/*
 * DMA.c
 *
 *  Created on: Apr 22, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <SERVICES/stm32f401cc.h>

#include <MCAL/DMA/DMA.h>
#include <MCAL/DMA/DMA_cfg.h>
#include <MCAL/DMA/DMA_prv.h>


void DMA1_Stream0_IRQHandler (void);
void DMA1_Stream1_IRQHandler (void);
void DMA1_Stream2_IRQHandler (void);
void DMA1_Stream3_IRQHandler (void);
void DMA1_Stream4_IRQHandler (void);
void DMA1_Stream5_IRQHandler (void);
void DMA1_Stream6_IRQHandler (void);
void DMA1_Stream7_IRQHandler (void);

void DMA2_Stream0_IRQHandler (void);
void DMA2_Stream1_IRQHandler (void);
void DMA2_Stream2_IRQHandler (void);
void DMA2_Stream3_IRQHandler (void);
void DMA2_Stream4_IRQHandler (void);
void DMA2_Stream5_IRQHandler (void);
void DMA2_Stream6_IRQHandler (void);
void DMA2_Stream7_IRQHandler (void);



static DmaCbf_t DMA_Cbf[DMA_u32DMA_NUMBER_MAX];


/*
 * Function:  DMA_enuInit
 * --------------------
 * INITIALIZE DMA WITH DESIRED CONFIGURATION CHECK DMA_tstrInitConfig
 *
 *  Add_pstrConfigurations: DESIRED CONFIGURATIONS
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK DMA_tenuErrorStatus ERROR ABOVE.
 */
DMA_tenuErrorStatus DMA_enuInit(DMA_tstrInitConfig * Add_pstrConfigurations) {
	/*DECLARE ERROR STATUS AND INIT WITH OK*/
	DMA_tenuErrorStatus Loc_enuReturnStatus = DMA_enuOk;
	/*ASSIGN BASE ADDRESS FOR POINTER TO CONTROL REGISTERS*/
	DMA_Register_t * Loc_pstrDMAChannel = Add_pstrConfigurations->DMA_pvNumber;
	/*VALIDATE NULL POINTERS*/
	if (Add_pstrConfigurations == NULL
			|| Add_pstrConfigurations->DMA_pvPeripheralAddress == NULL
			|| Add_pstrConfigurations->DMA_pvMemoryAddress == NULL
			|| Loc_pstrDMAChannel == NULL) {
		Loc_enuReturnStatus = DMA_enuErrorNullPointer;
		/*VALIDATE STREAM SELECTION*/
	} else if (Add_pstrConfigurations->DMA_u8StreamSelect
			> DMA_u32NUMBER_OF_CHANNELS) {
		Loc_enuReturnStatus = DMA_enuErrorChannel;
		/*VALIDATE NUMBER OF DATA TO BE TRANSFERED*/
	} else if (Add_pstrConfigurations->DMA_u16NumberOfData
			& DMA_u32VALIDATE_DATA_NUMBER) {
		Loc_enuReturnStatus = DMA_enuErrorDataNumber;
	} else {
		/*CLR CR REGITSER TO RECONFIGURE IT*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxCR =
		DMA_u32CLR_MSK;
		/*CONFIGURE THE CR REGISTER WITH DESIRED CONFIGURATIONS*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxCR =
				Add_pstrConfigurations->DMA_u32CircularMode
						| Add_pstrConfigurations->DMA_u32ChannelSelect
						| Add_pstrConfigurations->DMA_u32InterruptCtrl
						| Add_pstrConfigurations->DMA_u32MemoryDataSize
						| Add_pstrConfigurations->DMA_u32MemoryIncrementMode
						| Add_pstrConfigurations->DMA_u32PeripheralDataSize
						| Add_pstrConfigurations->DMA_u32PeripheralIncrementMode
						| Add_pstrConfigurations->DMA_u32Periority
						| Add_pstrConfigurations->DMA_u32Direction;
		/*ASSIGN NUMBER OF DATA TO BE TRANSFERRED*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxNDTR =
				Add_pstrConfigurations->DMA_u16NumberOfData;
		/*ASSIGN MEMORY ADDRESS*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxM0AR =
				(u32) Add_pstrConfigurations->DMA_pvMemoryAddress;
		/*ASSIGN PERIPHERAL ADDRESS*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxPAR =
				(u32) Add_pstrConfigurations->DMA_pvPeripheralAddress;
			/**/
			switch ((u32) Loc_pstrDMAChannel) {
			case (u32) DMA_pvDMA_NUM1:
				DMA_Cbf[Add_pstrConfigurations->DMA_u8StreamSelect] = Add_pstrConfigurations->DMA_Callback;
				break;
			case (u32) DMA_pvDMA_NUM2:
				DMA_Cbf[Add_pstrConfigurations->DMA_u8StreamSelect + 8] = Add_pstrConfigurations->DMA_Callback;
				break;
			}
	}

	return Loc_enuReturnStatus;
}

/*
 * Function:  DMA_vidClearFlag
 * --------------------
 * CLEAR SPECIFIC FLAG FOR DMA CHANNEL
 *
 *  Add_pvNumber: DMA NUMBER OPTIONS --> DMA_pvDMA_NUM1 - DMA_pvDMA_NUM2
 *	Copy_u64Flag: DESIRED FLAG TO BE CLEARED
 */
extern void 			   DMA_vidClearFlag(DmaChannel_t Add_pvNumber,u64 Copy_u64Flag)
{
	/*ASSIGN THE DMA CHANNEL POINTER TO CONTROL THE REGISTERS*/
	DMA_Register_t * Loc_pstrDMAChannel = Add_pvNumber;
	/*CLEAR DESIRED FLAGS*/
	Loc_pstrDMAChannel->DMA_HIFCR |=(u32) (Copy_u64Flag>>32);
	Loc_pstrDMAChannel->DMA_LIFCR |= (u32) Copy_u64Flag;
}

/*
 * Function:  DMA_enuStart
 * --------------------
 * ENABLE DMA
 *
 *  Add_pstrConfigurations: DESIRED CONFIGURATIONS
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK DMA_tenuErrorStatus ERROR ABOVE.
 */
DMA_tenuErrorStatus DMA_enuStart(DMA_tstrInitConfig * Add_pstrConfigurations) {
	/*ASSIGN ERROR STATUS WITH OK */
	DMA_tenuErrorStatus Loc_enuReturnStatus = DMA_enuOk;
	/*ASSIGN THE DMA CHANNEL POINTER TO CONTROL THE REGISTERS*/
	DMA_Register_t * Loc_pstrDMAChannel = Add_pstrConfigurations->DMA_pvNumber;
	/*VALIDATE ON NULL POINTER*/
	if (Add_pstrConfigurations == NULL || Loc_pstrDMAChannel == NULL) {
		Loc_enuReturnStatus = DMA_enuErrorNullPointer;
		/*VALIDATE ON STREAM SELECT*/
	} else if (Add_pstrConfigurations->DMA_u8StreamSelect
			> DMA_u32NUMBER_OF_CHANNELS) {
		Loc_enuReturnStatus = DMA_enuErrorChannel;
	} else {
		/*ENABLE DMA*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxCR |=
		DMA_u32DMA_ENABLE;
	}
	return Loc_enuReturnStatus;
}
DMA_tenuErrorStatus DMA_enuStop(DMA_tstrInitConfig * Add_pstrConfigurations) {
	/*ASSIGN ERROR STATUS WITH OK */
	DMA_tenuErrorStatus Loc_enuReturnStatus = DMA_enuOk;
	/*ASSIGN THE DMA CHANNEL POINTER TO CONTROL THE REGISTERS*/
	DMA_Register_t * Loc_pstrDMAChannel = Add_pstrConfigurations->DMA_pvNumber;
	/*VALIDATE ON NULL POINTER*/
	if (Add_pstrConfigurations == NULL || Loc_pstrDMAChannel == NULL) {
		Loc_enuReturnStatus = DMA_enuErrorNullPointer;
		/*VALIDATE ON STREAM SELECT*/
	} else if (Add_pstrConfigurations->DMA_u8StreamSelect
			> DMA_u32NUMBER_OF_CHANNELS) {
		Loc_enuReturnStatus = DMA_enuErrorChannel;
	} else {
		/*ENABLE DMA*/
		Loc_pstrDMAChannel->DMA_x[Add_pstrConfigurations->DMA_u8StreamSelect].DMA_SxCR &=
		DMA_u32DMA_DISABLE;
	}
	return Loc_enuReturnStatus;
}


void DMA1_Stream0_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream0])
	{
		(DMA_Cbf[DMA1_enuStream0])();
	}
}
void DMA1_Stream1_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream1])
	{
		(DMA_Cbf[DMA1_enuStream1])();
	}
}
void DMA1_Stream2_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream2])
	{
		(DMA_Cbf[DMA1_enuStream2])();
	}
}
void DMA1_Stream3_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream3])
	{
		(DMA_Cbf[DMA1_enuStream3])();
	}
}
void DMA1_Stream4_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream4])
	{
		(DMA_Cbf[DMA1_enuStream4])();
	}
}
void DMA1_Stream5_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream5])
	{
		(DMA_Cbf[DMA1_enuStream5])();
	}
}
void DMA1_Stream6_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream6])
	{
		(DMA_Cbf[DMA1_enuStream6])();
	}
}
void DMA1_Stream7_IRQHandler (void)
{
	if(DMA_Cbf[DMA1_enuStream7])
	{
		(DMA_Cbf[DMA1_enuStream7])();
	}
}


void DMA2_Stream0_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream0])
	{
		(DMA_Cbf[DMA2_enuStream0])();
	}
}
void DMA2_Stream1_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream1])
	{
		(DMA_Cbf[DMA2_enuStream1])();
	}
}
void DMA2_Stream2_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream2])
	{
		(DMA_Cbf[DMA2_enuStream2])();
	}
}
void DMA2_Stream3_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream3])
	{
		(DMA_Cbf[DMA2_enuStream3])();
	}
}
void DMA2_Stream4_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream4])
	{
		(DMA_Cbf[DMA2_enuStream4])();
	}
}
void DMA2_Stream5_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream5])
	{
		(DMA_Cbf[DMA2_enuStream5])();
	}
}
void DMA2_Stream6_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream6])
	{
		(DMA_Cbf[DMA2_enuStream6])();
	}
}
void DMA2_Stream7_IRQHandler (void)
{
	if(DMA_Cbf[DMA2_enuStream7])
	{
		(DMA_Cbf[DMA2_enuStream7])();
	}
}

