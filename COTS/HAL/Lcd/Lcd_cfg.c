/*
 * Lcd_cfg.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Kishk
 */

#include <SERVICES/Bit_utils.h>
#include <SERVICES/Std_types.h>
#include <MCAL/GPIO/Gpio.h>
#include <HAL/Lcd/Lcd.h>

const Lcd_tstrCfg LcdPinCfg[] = {
		[LCD_u8RS] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_00,
		},
		[LCD_u8RW] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_01,
		},
		[LCD_u8EN] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_02,
		},
		[LCD_u8D0] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_03,
		},
		[LCD_u8D1] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_04,
		},
		[LCD_u8D2] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_05,
		},
		[LCD_u8D3] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_06,
		},
		[LCD_u8D4] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_07,
		},
		[LCD_u8D5] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_08,
		},
		[LCD_u8D6] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_09,
		},
		[LCD_u8D7] = {
				.Lcd_pvPort = GPIO_pvPORTA,
				.Lcd_u16Pin = GPIO_u16PIN_10,
		},


};


