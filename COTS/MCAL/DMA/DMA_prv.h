/*
 * DMA_prv.h
 *
 *  Created on: Apr 22, 2022
 *      Author: Kishk
 */

#ifndef MCAL_DMA_DMA_PRV_H_
#define MCAL_DMA_DMA_PRV_H_


typedef enum
{
	DMA1_enuStream0,
	DMA1_enuStream1,
	DMA1_enuStream2,
	DMA1_enuStream3,
	DMA1_enuStream4,
	DMA1_enuStream5,
	DMA1_enuStream6,
	DMA1_enuStream7,
	DMA2_enuStream0,
	DMA2_enuStream1,
	DMA2_enuStream2,
	DMA2_enuStream3,
	DMA2_enuStream4,
	DMA2_enuStream5,
	DMA2_enuStream6,
	DMA2_enuStream7,
}DMAx_tenuStream;

#define DMA_u32VALIDATE_DATA_NUMBER			0xFFFF0000
#define DMA_u32NUMBER_OF_CHANNELS			0x00000007
#define DMA_u32CLR_MSK						0x00000000

#define DMA_u32DMA1							0x00000000
#define DMA_u32DMA2							0x00000001

#define DMA_u32DMA_NUMBER_MAX				0x00000010

#define DMA_u32DMA_ENABLE					0x00000001
#define DMA_u32DMA_DISABLE					0xFFFFFFFE

#endif /* MCAL_DMA_DMA_PRV_H_ */
