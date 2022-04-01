/*
 * Led_cfg.c
 *
 *  Created on: Mar 24, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <MCAL/Gpio.h>
#include <HAL/LED/hLed.h>
#include <HAL/LED/hLed_cfg.h>

const Led_Cnfg_t Leds[NUM_OF_LEDS] = {
		[LED_TEST] = {
				.Port = GPIO_pvPORTC,
				.Pin = GPIO_u16PIN_13,
				.Active_State = LED_u8ACTIVE_STATE_LOW,
		}
};
