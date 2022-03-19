/*
 * Gpio_prv.h
 *
 *  Created on: Mar 14, 2022
 *      Author: Kishk
 */

#ifndef MCAL_GPIO_PRV_H_
#define MCAL_GPIO_PRV_H_

#define GPIO_u8_NUM_OF_PORTS		((u8) 0x06)
#define GPIO_u32MODE_CLR_MSK		((u32) 0x00000003)
#define GPIO_u8DOUBLE_BIT			((u8) 0x02)
#define GPIO_u8QUADRO_BIT			((u8) 0x04)

#define GPIO_u8PP_OD				((u8) 0x01)
#define GPIO_u8OD					((u8) 0x01)

#define GPIO_u8PULL_CLR_MSK				((u8) 0x03)
#define GPIO_u8SPEED_CLR_MSK			((u8) 0x03)

#define GPIO_u8VALUE_RST_MSK			((u8) 0x10)
#define GPIO_u8VALUE_SET_RST_MSK		((u8) 0x01)
#define GPIO_u8ALTERNATE_CLR_MSK		((u8) 0x0F)
#define GPIO_u8LPINS_MSK				((u8) 0x07)


#define GPIO_MODE_MSK				    0x03
#define GPIO_OTY_MSK					0x10
#define GPIO_PUPDR_MSK					0x300
#define GPIO_PIN_MSK					0x01
#define GPIO_OTY_SHFT					4
#define GPIO_PUPD_SHFT					8
#define GPIO_ZERO						0
#define GPIO_u8_PINS					0x0F

#endif /* MCAL_GPIO_PRV_H_ */
