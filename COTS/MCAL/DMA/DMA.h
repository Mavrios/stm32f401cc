/*
 * DMA.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Kishk
 */

#ifndef MCAL_DMA_DMA_H_
#define MCAL_DMA_DMA_H_

typedef void * DmaChannel_t;

typedef void (* DmaCbf_t) (void);
typedef enum{
	DMA_enuOk,
	DMA_enuErrorNullPointer,
	DMA_enuErrorChannel,
	DMA_enuErrorDataNumber,
}DMA_tenuErrorStatus;

typedef struct{
	DmaChannel_t DMA_pvNumber;
	u8  DMA_u8StreamSelect;
	u32  DMA_u32ChannelSelect;
	u32  DMA_u32MemoryDataSize;
	u32  DMA_u32PeripheralDataSize;
	u32  DMA_u32MemoryIncrementMode;
	u32  DMA_u32PeripheralIncrementMode;
	u32  DMA_u32CircularMode;
	u32  DMA_u32Periority;
	u32  DMA_u32Direction;
	u32  DMA_u32InterruptCtrl;
	u16	 DMA_u16NumberOfData;
	void * DMA_pvPeripheralAddress;
	void * DMA_pvMemoryAddress;
	DmaCbf_t DMA_Callback;
}DMA_tstrInitConfig;





#define DMA_u64INTERRUPT_CH0_TRANS_COMPLETE			((u64) 0x00000020)
#define DMA_u64INTERRUPT_CH1_TRANS_COMPLETE			((u64) 0x00000800)
#define DMA_u64INTERRUPT_CH2_TRANS_COMPLETE			((u64) 0x00200000)
#define DMA_u64INTERRUPT_CH3_TRANS_COMPLETE			((u64) 0x08000000)
#define DMA_u64INTERRUPT_CH4_TRANS_COMPLETE			((u64) 0x0000002000000000)
#define DMA_u64INTERRUPT_CH5_TRANS_COMPLETE			((u64) 0x0000080000000000)
#define DMA_u64INTERRUPT_CH6_TRANS_COMPLETE			((u64) 0x0020000000000000)
#define DMA_u64INTERRUPT_CH7_TRANS_COMPLETE			((u64) 0x0800000000000000)

#define DMA_u64INTERRUPT_CH0_HALF_TRANS_COMPLETE	((u64) 0x00000010)
#define DMA_u64INTERRUPT_CH1_HALF_TRANS_COMPLETE	((u64) 0x00000400)
#define DMA_u64INTERRUPT_CH2_HALF_TRANS_COMPLETE	((u64) 0x00100000)
#define DMA_u64INTERRUPT_CH3_HALF_TRANS_COMPLETE	((u64) 0x04000000)
#define DMA_u64INTERRUPT_CH4_HALF_TRANS_COMPLETE	((u64) 0x0000001000000000)
#define DMA_u64INTERRUPT_CH5_HALF_TRANS_COMPLETE	((u64) 0x0000040000000000)
#define DMA_u64INTERRUPT_CH6_HALF_TRANS_COMPLETE	((u64) 0x0010000000000000)
#define DMA_u64INTERRUPT_CH7_HALF_TRANS_COMPLETE	((u64) 0x0400000000000000)


#define DMA_u32CHANNEL_SELECT_CH0					((u32) 0x00000000)
#define DMA_u32CHANNEL_SELECT_CH1					((u32) 0x02000000)
#define DMA_u32CHANNEL_SELECT_CH2					((u32) 0x04000000)
#define DMA_u32CHANNEL_SELECT_CH3					((u32) 0x06000000)
#define DMA_u32CHANNEL_SELECT_CH4					((u32) 0x08000000)
#define DMA_u32CHANNEL_SELECT_CH5					((u32) 0x0A000000)
#define DMA_u32CHANNEL_SELECT_CH6					((u32) 0x0C000000)
#define DMA_u32CHANNEL_SELECT_CH7					((u32) 0x0E000000)

#define DMA_u8STREAM_SELECT_ST0					((u8) 0x00)
#define DMA_u8STREAM_SELECT_ST1					((u8) 0x01)
#define DMA_u8STREAM_SELECT_ST2					((u8) 0x02)
#define DMA_u8STREAM_SELECT_ST3					((u8) 0x03)
#define DMA_u8STREAM_SELECT_ST4					((u8) 0x04)
#define DMA_u8STREAM_SELECT_ST5					((u8) 0x05)
#define DMA_u8STREAM_SELECT_ST6					((u8) 0x06)
#define DMA_u8STREAM_SELECT_ST7					((u8) 0x07)

#define DMA_u32MEMORY_DATA_1BYTE					((u32) 0x00000000)
#define DMA_u32MEMORY_DATA_2BYTE					((u32) 0x00002000)
#define DMA_u32MEMORY_DATA_4BYTE					((u32) 0x00004000)

#define DMA_u32PERIPHERAL_DATA_1BYTE				((u32) 0x00000000)
#define DMA_u32PERIPHERAL_DATA_2BYTE				((u32) 0x00000800)
#define DMA_u32PERIPHERAL_DATA_4BYTE				((u32) 0x00001000)

#define DMA_u32MEMORY_INC_MODE_FIXED				((u32) 0x00000000)
#define DMA_u32MEMORY_INC_MODE_ON					((u32) 0x00000400)

#define DMA_u32PERIPHERAL_INC_MODE_FIXED			((u32) 0x00000000)
#define DMA_u32PERIPHERAL_INC_MODE_ON				((u32) 0x00000200)

#define DMA_u32CIRCULAR_MODE_OFF					((u32) 0x00000000)
#define DMA_u32CIRCULAR_MODE_ON						((u32) 0x00000100)

#define DMA_u32INTERRUPT_OFF						((u32) 0x00000000)
#define DMA_u32INTERRUPT_TRANS_COMPLETE				((u32) 0x00000010)
#define DMA_u32INTERRUPT_HALF_TRANS_COMPLETE		((u32) 0x00000020)

#define DMA_u32PERIORITY_LOW						((u32) 0x00000000)
#define DMA_u32PERIORITY_MEDIUM						((u32) 0x00010000)
#define DMA_u32PERIORITY_HIGH						((u32) 0x00020000)
#define DMA_u32PERIORITY_VHIGH						((u32) 0x00030000)

#define DMA_u32DIRECTION_PTM						((u32) 0x00000000)
#define DMA_u32DIRECTION_MTP						((u32) 0x00000040)
#define DMA_u32DIRECTION_MTM						((u32) 0x00000080)

#define DMA_pvDMA_NUM1								((DmaChannel_t) 0x40026000)
#define DMA_pvDMA_NUM2								((DmaChannel_t) 0x40026400)

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
extern DMA_tenuErrorStatus DMA_enuInit(DMA_tstrInitConfig * Add_pstrConfigurations);
/*
 * Function:  DMA_vidClearFlag
 * --------------------
 * CLEAR SPECIFIC FLAG FOR DMA CHANNEL
 *
 *  Add_pvNumber: DMA NUMBER OPTIONS --> DMA_pvDMA_NUM1 - DMA_pvDMA_NUM2
 *	Copy_u64Flag: DESIRED FLAG TO BE CLEARED
 */
extern void 			   DMA_vidClearFlag(DmaChannel_t Add_pvNumber,u64 Copy_u64Flag);
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
extern DMA_tenuErrorStatus DMA_enuStart(DMA_tstrInitConfig * Add_pstrConfigurations);
/*
 * Function:  DMA_enuStop
 * --------------------
 * STOP DMA
 *
 *  Add_pstrConfigurations: DESIRED CONFIGURATIONS
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK DMA_tenuErrorStatus ERROR ABOVE.
 */
extern DMA_tenuErrorStatus DMA_enuStop(DMA_tstrInitConfig * Add_pstrConfigurations);


#endif /* MCAL_DMA_DMA_H_ */
