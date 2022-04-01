/*
 * NVIC_prv.h
 *
 *  Created on: Mar 28, 2022
 *      Author: Kishk
 */

#ifndef MCAL_NVIC_PRV_H_
#define MCAL_NVIC_PRV_H_

#define NVIC_u8REGISTER_SIZE		((u8) 32)

#define NVIC_u8NUMBER_OF_IRQ		((u8) 240)


#define NVIC_u32SET_MSK				((u32) 0x01)
#define NVIC_u8PRIORITY_START_BIT	((u8) 0x04)
#define NVIC_u8PRIORITY_MSK			((u8) 0xF0)
#define NVIC_u32PRIORITY_CLR_MSK	((u32) 0xFFFFFFFF)
#define NVIC_u32PRIORITY_ERROR_MSK	((u32) 0xFFFFFFFF)

#define AIRCR_SUBGROUP_CLR_MSK		((u32) 0xFFFFF8FF)
#define AIRCR_SUBGROUP_VLDATE_MSK	((u32) 0xFFFFF8FF)
#endif /* MCAL_NVIC_PRV_H_ */
