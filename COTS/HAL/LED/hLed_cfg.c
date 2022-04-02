/*
 * Led_cfg.c
 *
 *  Created on: Mar 24, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <HAL/LED/hLed.h>
#include <HAL/LED/hLed_cfg.h>
#include <MCAL/GPIO/Gpio.h>

const Led_Cnfg_t Leds[NUM_OF_LEDS] = {
		[LED_TEST] = {
				.Port = GPIO_pvPORTA,
				.Pin = GPIO_u16PIN_00,
				.Active_State = LED_u8ACTIVE_STATE_HIGH,
		}
};
