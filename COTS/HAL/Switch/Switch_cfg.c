/*
 * Switch_cfg.c
 *
 *  Created on: Mar 25, 2022
 *      Author: Kishk
 */

#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <HAL/Switch/Switch.h>
#include <MCAL/Gpio.h>


const Switch_Cnfg_t Switchs [NUM_OF_SWITCH] = {
		[SWITCH_u16TEST] = {
				.Port = GPIO_pvPORTA,
				.Pin  = GPIO_u16PIN_03,
				.Pull_State = GPIO_u32MODE_INPUT_PD,
		}
};



