/*
 * RCC.c
 *
 *  Created on: Mar 7, 20221
 *      Author: Kishk
 */
#include <SERVICES/Std_types.h>
#include <SERVICES/Bit_utils.h>
#include <SERVICES/stm32f401cc.h>
#include <MCAL/RCC/RCC.h>
#include <MCAL/RCC/RCC_prv.h>


/*******************************************************************************************************
 * Function:  RCC_enuControlSysClock																   *
 * --------------------------------------------------------------------------------------------------- *
 * SELECT THE SYSTEM CLK																   			   *
 *																									   *
 *  Copy_u8Clock: DESIRED CLK --> OPTIONS -->(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)	   *
 *																									   *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED											   *
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.															   *
 *******************************************************************************************************/
RCC_tenuErrorStatus RCC_enuControlSysClock(u8 Copy_u8Clock) {
	/*DIFINE RETURN ERROR VARIABLE*/
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*DEFINE ITERATOR FOR ITERATION USING*/
	u16 LOC_u16TimeOut = RCC_u16TIME_OUT;
	/*DEFINE TEMP VARIABLE TO TEMPERORY STORE CFGR REGISTER*/
	u32 LOC_u32TempCFGR;
	/*CHECK IF THE CLOCK OUT OF THE RANGE*/
	if (Copy_u8Clock > RCC_u8PLL_CLOCK) {
		/*WRITE AN ERROR IN RETURN ERROR VARIABLE*/
		LOC_enuReturnError = RCC_enuErrorClock;
	} else {
		/*SWITCH IN IN THE CLOCK TO MAKE SURE CLK IS READY*/
		switch (Copy_u8Clock) {
		case RCC_u8HSI_CLOCK:
			/*CHECK IF THE HSI READY*/
			if (RCC->RCC_CR & HSIRDY_MSK) {
				/*STORE CFGR REGISTER IN TEMP VARIABLE TO CLR DESIRED BITS AND ASSIGN IT */
				LOC_u32TempCFGR = RCC->RCC_CFGR;
				LOC_u32TempCFGR &= RSTSW_MSK;
				LOC_u32TempCFGR |= Copy_u8Clock;
				RCC->RCC_CFGR = LOC_u32TempCFGR;
			} else {
				LOC_enuReturnError = RCC_enuErrorClkNotRdy;
			}
			break;
		case RCC_u8HSE_CLOCK:
			/*CHECK IF THE HSE READY*/
			if (RCC->RCC_CR & HSERDY_MSK) {
				/*STORE CFGR REGISTER IN TEMP VARIABLE TO CLR DESIRED BITS AND ASSIGN IT */
				LOC_u32TempCFGR = RCC->RCC_CFGR;
				LOC_u32TempCFGR &= RSTSW_MSK;
				LOC_u32TempCFGR |= Copy_u8Clock;
				RCC->RCC_CFGR = LOC_u32TempCFGR;
				/*DUMMY LOOP TO CALCULATE TIME OUT IF CLK NOT SWITCHED IN DESIRED TIME*/
				LOC_enuReturnError = RCC_enuErrorTimedOut;
			} else {
				LOC_enuReturnError = RCC_enuErrorClkNotRdy;
			}
			break;
		case RCC_u8PLL_CLOCK:
			/*CHECK IF THE PLL READY*/
			if (RCC->RCC_CR & PLLRDY_MSK) {
				/*STORE CFGR REGISTER IN TEMP VARIABLE TO CLR DESIRED BITS AND ASSIGN IT */
				LOC_u32TempCFGR = RCC->RCC_CFGR;
				LOC_u32TempCFGR &= RSTSW_MSK;
				LOC_u32TempCFGR |= Copy_u8Clock;
				RCC->RCC_CFGR = LOC_u32TempCFGR;
				/*DUMMY LOOP TO CALCULATE TIME OUT IF CLK NOT SWITCHED IN DESIRED TIME*/
				LOC_enuReturnError = RCC_enuErrorTimedOut;
			} else {
				LOC_enuReturnError = RCC_enuErrorClkNotRdy;
			}
			break;
		}
		/*DUMMY LOOP TO CALCULATE TIME OUT IF CLK NOT SWITCHED IN DESIRED TIME*/
		LOC_enuReturnError = RCC_enuErrorTimedOut;
		while (LOC_u16TimeOut-- && (RCC->RCC_CFGR & SWS_MSK >> SWS0) != Copy_u8Clock);
		/*CHECK IF THE SYS CLK ALRDY SWITCHED*/
		if ((RCC->RCC_CFGR & SWS_MSK >> SWS0) == Copy_u8Clock) {
			/*MAKE RETURN ERROR WITH OK AND BREAK THE LOOP*/
			LOC_enuReturnError = RCC_enuOk;
		}
	}
	/*RETURN POINT OF FUNCTION TO RETURN ERROR STATUS*/
	return LOC_enuReturnError;
}

/********************************************************************************************************
 * Function:  RCC_enuControlClock																		*
 * ----------------------------------------------------------------------------------------------------	*
 * CONTROL THE CLK (ON - OFF)																			*
 *																										*
 *  Copy_u8Clock: DESIRED CLK --> OPTIONS -->(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)		*
 *	Copy_u8Status: DESIRED STATE --> OPTIONS --> (RCC_u8CLK_OFF - RCC_u8CLK_ON)							*
 *																										*
 *																										*
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED												*
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.																*
 ********************************************************************************************************/
RCC_tenuErrorStatus RCC_enuControlClock(u8 Copy_u8Clock, u8 Copy_u8Status) {
	/*DECLARE ITERATOR AND RETURN ERROR STATUS VARIABLES*/
	u16 LOC_u16TimeOut = RCC_u16TIME_OUT;;
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*CHECK IF THE ENTERED CLK OUT OF THE RANGE (INVALID)*/
	if (Copy_u8Clock > RCC_u8PLL_CLOCK) {
		LOC_enuReturnError = RCC_enuErrorClock;
		/*CHECK IF STATUS IS INVALID*/
	} else if (Copy_u8Status > RCC_u8CLK_ON) {
		LOC_enuReturnError = RCC_enuErrorContrlStatus;
		/*CHECK IF THE DESIRED CLK IS ALRDY THE SYS CLK*/
	} else if (((RCC->RCC_CFGR & SWS_MSK) >> SWS0) == Copy_u8Clock) {
		LOC_enuReturnError = RCC_enuErrorSelectedSysClk;
	} else if((RCC->RCC_PLLCFGR & PLLSRC_MSK) == Copy_u8Clock){
		LOC_enuReturnError = RCC_enuErrorSelectedPllClk;
	}
	else {
		/*SWITCH TO SWITCH ON CLK TO MAKE SURE THE DISERED CLK IS RDY*/
		switch (Copy_u8Clock) {
		case RCC_u8HSI_CLOCK:
			/*NESTED SWITCH ON STATUS*/
			switch (Copy_u8Status) {
			case RCC_u8CLK_ON:
				/*TURN ON HSI*/
				RCC->RCC_CR |= HSION_MSK;
				/*WAIT UNTIL HSI GET READY AND CHECK IF IT'S TIMED OUT*/
				LOC_enuReturnError = RCC_enuErrorTimedOut;
				while (LOC_u16TimeOut-- && !(RCC->RCC_CR & HSIRDY_MSK));
					/*IF THE CLK RDY BREAK THE LOOP AND ASSIGN RETURN ERROR WITH "OK"*/
					if ((RCC->RCC_CR & HSIRDY_MSK)) {
						LOC_enuReturnError = RCC_enuOk;
					}
				break;
			case RCC_u8CLK_OFF:
				/*TURN OFF THE CLK*/
				RCC->RCC_CR &= ~(HSION_MSK);
				break;
			}
			break;

		case RCC_u8HSE_CLOCK:
			switch (Copy_u8Status) {
			case RCC_u8CLK_ON:
				/*TURN ON HSE*/
				RCC->RCC_CR |= HSEON_MSK;
				/*WAIT UNTIL HSE GET READY AND CHECK IF IT'S TIMED OUT*/
				LOC_enuReturnError = RCC_enuErrorTimedOut;
				while (LOC_u16TimeOut-- && !(RCC->RCC_CR & HSERDY_MSK));
					/*IF THE CLK RDY BREAK THE LOOP AND ASSIGN RETURN ERROR WITH "OK"*/
					if ((RCC->RCC_CR & HSERDY_MSK)) {
						LOC_enuReturnError = RCC_enuOk;
						break;
					}

				break;
			case RCC_u8CLK_OFF:
				/*TURN OFF THE CLK*/
				RCC->RCC_CR &= ~(HSEON_MSK);
				break;
			}
			break;
		case RCC_u8PLL_CLOCK:
			switch (Copy_u8Status) {
			case RCC_u8CLK_ON:
				/*TURN ON PLL*/
				RCC->RCC_CR |= PLLON_MSK;
				/*WAIT UNTIL PLL GET READY AND CHECK IF IT'S TIMED OUT*/
				LOC_enuReturnError = RCC_enuErrorTimedOut;
				while (LOC_u16TimeOut-- && !(RCC->RCC_CR & PLLRDY_MSK));
					/*IF THE CLK RDY BREAK THE LOOP AND ASSIGN RETURN ERROR WITH "OK"*/
					if ((RCC->RCC_CR & PLLRDY_MSK)) {
						LOC_enuReturnError = RCC_enuOk;
						break;
					}

				break;
			case RCC_u8CLK_OFF:
				/*TURN OFF THE CLK*/
				RCC->RCC_CR &= ~(PLLON_MSK);
				break;
			}
			break;
		}
	}
	return LOC_enuReturnError;
}

/********************************************************************************************************
 * Function:  RCC_enuGetClockRdyStatus																	*
 * ----------------------------------------------------------------------------------------------------	*
 * CHECK THE CLK STATUS IF IT'S RDY OR NOT!																*
 *																										*
 *  Copy_u8Clock: DESIRED CLK --> OPTIONS -->(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)		*
 *	Add_pu8RtrnRdyStatus: ADDRESS OF VARIABLE WITH TYPE (u8) TO STORE THE RESULT IN THIS ADDRESS		*
 *																										*
 *																										*
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED												*
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.																*
 ********************************************************************************************************/
RCC_tenuErrorStatus RCC_enuGetClockRdyStatus(u8 Copy_u8Clock,
		pu8 Add_pu8RtrnRdyStatus) {
	/*DEFINE RETURN ERROR VARIABLE*/
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*CHECK IF THE CLK IS OUT OF THE RANGE (INVALID)*/
	if (Copy_u8Clock > RCC_u8PLL_CLOCK) {
		LOC_enuReturnError = RCC_enuErrorClock;
		/*CHECK IF THE POINTER IS NULL !!*/
	} else if (Add_pu8RtrnRdyStatus == NULL) {
		LOC_enuReturnError = RCC_enuErrorNullPointer;
	} else {
		/*SWITCH IN THE CLK*/
		switch (Copy_u8Clock) {
		case RCC_u8HSI_CLOCK:
			/*CHECK IF CLK IS RDY AND STORE IT TO THE PASSED ADDRESS*/
			if (RCC->RCC_CR & HSIRDY_MSK) {
				*Add_pu8RtrnRdyStatus = RCC_u8CLK_RDY;
			} else {
				*Add_pu8RtrnRdyStatus = RCC_u8CLK_NOTRDY;
			}
			break;
		case RCC_u8HSE_CLOCK:
			/*CHECK IF CLK IS RDY AND STORE IT TO THE PASSED ADDRESS*/
			if (RCC->RCC_CR & HSERDY_MSK) {
				*Add_pu8RtrnRdyStatus = RCC_u8CLK_RDY;
			} else {
				*Add_pu8RtrnRdyStatus = RCC_u8CLK_NOTRDY;
			}
			break;
		case RCC_u8PLL_CLOCK:
			/*CHECK IF CLK IS RDY AND STORE IT TO THE PASSED ADDRESS*/
			if (RCC->RCC_CR & PLLRDY_MSK) {
				*Add_pu8RtrnRdyStatus = RCC_u8CLK_RDY;
			} else {
				*Add_pu8RtrnRdyStatus = RCC_u8CLK_NOTRDY;
			}
			break;
		}
	}
	/*RETURN THE ERROR STATUS*/
	return LOC_enuReturnError;
}

/********************************************************************************************************
 * Function:  RCC_enuConfigurePLL																		*
 * ----------------------------------------------------------------------------------------------------	*
 * CONFIGURE PLL CLOCK																					*
 * RESTRICTIONS : (THE PLL SHOULD BE OFF).																*
 *																										*
 *  Copy_strCfg(STRUCT): STRUCT CONTAIN ALL DESIRED OPTIONS:-											*
 *																										*
 *  --> Copy_strCfg.RCC_u32DivisionFactor_M: (SHOULD NOT EXCEED "63 DECIMAL")							*
 *  Caution: The software has to set these bits correctly to ensure that the VCO input frequency        *
 *	ranges from 1 to 2 MHz. It is recommended to select a frequency of 2 MHz to limit PLL jitter        *
 *                                                                                                      *
 *	--> Copy_strCfg.RCC_u16MultiplyFactor_N: (SHOULD NOT EXCEED "432 DECIMAL")                          *
 *	The software has to set these bits correctly to ensure that the VCO output                          *
 * 	frequency is between 192 and 432 MHz.                                                               *
 *                                                                                                      *
 * 	-->Copy_strCfg.RCC_enuPLL_P:	ENUM OF TYPE (RCC_tenuPLL_P) MUST CHOOSE ONE OF ENUM OPTIONS.       *
 *                                                                                                      *
 * 	-->Copy_strCfg.RCC_u8SourceClock: DESIRED CLK --> OPTIONS -->                                       *
 * 	(RCC_u8HSI_CLOCK - RCC_u8HSE_CLOCK - RCC_u8PLL_CLOCK)                                               *
 *                                                                                                      *
 * 	-->Copy_strCfg.RCC_enuPLL_Q:	ENUM OF TYPE (RCC_tenuPLL_Q) MUST CHOOSE ONE OF ENUM OPTIONS.       *
 *                                                                                                      *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                                *
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.                                                              *
 ********************************************************************************************************/
RCC_tenuErrorStatus RCC_enuConfigurePLL(RCC_tstrPllCfg Copy_strCfg) {
	/*DEFINE ERROR STATUS VARIABLE*/
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*CHECK IF THE PLL IS ON*/
	if (RCC->RCC_CR & PLLON_MSK) {
		LOC_enuReturnError = RCC_enuErrorPLLOn;
	}
	/*CHECK IF THE INSERTED PLL M  OUT OF THE RANGE*/
	else if (Copy_strCfg.RCC_u32DivisionFactor_M > PLLM_MAX) {
		LOC_enuReturnError = RCC_enuErrorMFactor;
	} /*CHECK IF THE PLL N OUT OF THE RANGE*/
	else if (Copy_strCfg.RCC_u16MultiplyFactor_N > PLLN_MAX) {
		LOC_enuReturnError = RCC_enuErrorNFactor;
	} /*CHECK IF THE CLK SOURCE OF THE THE RANGE (INVALID CLK)*/
	else if (Copy_strCfg.RCC_u8SourceClock > RCC_u8HSE_CLOCK) {
		LOC_enuReturnError = RCC_enuErrorClock;
	} /*FCHECK IF P OUT OF THE RANGE*/
	else if (Copy_strCfg.RCC_enuPLL_P > RCC_enuPDivBy8) {
		LOC_enuReturnError = RCC_enuErrorPLLP;
	} /*CHECK IF THE Q OUT OF THE RANGE*/
	else if (Copy_strCfg.RCC_enuPLL_Q > RCC_enuQDivBy15
			|| Copy_strCfg.RCC_enuPLL_Q < RCC_enuQDivBy2) {
		LOC_enuReturnError = RCC_enuErrorPLLQ;
	} else {
		/*ASSIGN THE DESIRED CONFIGURATION INTO PLLCFGR REGISTER*/
		RCC->RCC_PLLCFGR = (Copy_strCfg.RCC_u32DivisionFactor_M)
				| (u16) (Copy_strCfg.RCC_u16MultiplyFactor_N << PLLN)
				| (RCC_tenuPLL_P) (Copy_strCfg.RCC_enuPLL_P << PLLP)
				| (u8)(Copy_strCfg.RCC_u8SourceClock << PLLSRC)
				| (u16)(Copy_strCfg.RCC_enuPLL_Q << PLLQ);

	}
	/*RETURN ERROR STATUS*/
	return LOC_enuReturnError;

}
/************************************************************************************************************
 * Function:  RCC_enuControlBusPrescaler																	*
 * --------------------                                                                                     *
 * CONFIGURE BUS PRESCALER                                                                                  *
 *                                                                                                          *
 *  Copy_u32Prescaler: DESIRED CLK --> OPTIONS -->                                                          *
 *  (RCC_u32APB1_DIV_BY_x - RCC_u32APB2_DIV_BY_x - RCC_u32AHB_DIV_BY_x) "REPLACE X WITH DESIERED OPTION     *
 *	(RCC_u32APB1_NOT_DIVIDED  - RCC_u32APB2_NOT_DIVIDED - RCC_u32AHB_NOT_DIVIDED)                           *
 *                                                                                                          *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                                    *
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.                                                                  *
 ************************************************************************************************************/
RCC_tenuErrorStatus RCC_enuControlBusPrescaler(u32 Copy_u8Prescaler) {
	/*DEFINE RETURN ERROR STATUS VARIABLE*/
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*SWITCH TO CHECK IF THE PASSED PRESCALLER IS VALID OR NOT AND APPLY IT IF IT'S VALID*/
	switch (Copy_u8Prescaler) {
	case RCC_u32APB1_NOT_DIVIDED:
		RCC->RCC_CFGR &= Copy_u8Prescaler;
		break;
	case RCC_u32APB1_DIV_BY_2:
		RCC->RCC_CFGR &= RCC_u32APB1_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB1_DIV_BY_4:
		RCC->RCC_CFGR &= RCC_u32APB1_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB1_DIV_BY_8:
		RCC->RCC_CFGR &= RCC_u32APB1_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB1_DIV_BY_16:
		RCC->RCC_CFGR &= RCC_u32APB1_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB2_NOT_DIVIDED:
		RCC->RCC_CFGR &= Copy_u8Prescaler;
		break;
	case RCC_u32APB2_DIV_BY_2:
		RCC->RCC_CFGR &= RCC_u32APB2_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB2_DIV_BY_4:
		RCC->RCC_CFGR &= RCC_u32APB2_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB2_DIV_BY_8:
		RCC->RCC_CFGR &= RCC_u32APB2_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32APB2_DIV_BY_16:
		RCC->RCC_CFGR &= RCC_u32APB2_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_NOT_DIVIDED:
		RCC->RCC_CFGR &= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_2:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_4:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_8:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_16:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_64:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_128:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_256:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	case RCC_u32AHB_DIV_BY_512:
		RCC->RCC_CFGR &= RCC_u32AHB_NOT_DIVIDED;
		RCC->RCC_CFGR |= Copy_u8Prescaler;
		break;
	default:
		LOC_enuReturnError = RCC_enuErrorBusPrescaler;
		break;
	}
	/*RETURN ERROR STATUS*/
	return LOC_enuReturnError;
}

/****************************************************************************************************
 * Function:  RCC_enuEnablePeripheralClk															*
 * ------------------------------------------------------------------------------------------------ *
 * ENABLE PERIPHERAL SPECIFIC PERIPHERAL CLK                                                        *
 *                                                                                                  *
 *  Copy_u8Bus: DESIRED CLK --> OPTIONS --> (RCC_u8APB1_BUS - RCC_u8APB2_BUS - RCC_u8AHB_BUS)       *
 *	Copy_u32Peripheral: DESIRED PERIPHERAL OPTIONS -->  											*
 *	(RCC_u32AHB1_xxxx - RCC_u32AHB2_xxxx - RCC_u32APB1_xxxx - RCC_u32APB2_xxxx)						*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
RCC_tenuErrorStatus RCC_enuEnablePeripheralClk(u8 Copy_u8Bus,
		u32 Copy_u32Peripheral) {
	/*DEFINE RETURN ERROR STATUS VARIABLE*/
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*SWITCH CASE TO CHECK DESIRED BUS*/
	switch (Copy_u8Bus) {
	case RCC_u8APB1_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_APB1ENR |= Copy_u32Peripheral;
		break;
	case RCC_u8APB2_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_APB2ENR |= Copy_u32Peripheral;
		break;
	case RCC_u8AHB1_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_AHB1ENR |= Copy_u32Peripheral;
		break;
	case RCC_u8AHB2_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_AHB2ENR |= Copy_u32Peripheral;
		break;
	default:
		/*ASSIGN ERROR BUS IF THE BUS IS INVALID*/
		LOC_enuReturnError = RCC_enuErrorBus;
	}
	/*RETURN ERROR STATUS*/
	return LOC_enuReturnError;
}

/****************************************************************************************************
 * Function:  RCC_enuDisablePeripheralClk															*
 * ------------------------------------------------------------------------------------------------ *
 * DISABLE PERIPHERAL SPECIFIC PERIPHERAL CLK                                                       *
 *                                                                                                  *
 *  Copy_u8Bus: DESIRED CLK --> OPTIONS --> (RCC_u8APB1_BUS - RCC_u8APB2_BUS - RCC_u8AHB_BUS)       *
 *	Copy_u32Peripheral: DESIRED PERIPHERAL OPTIONS -->  											*
 *	(RCC_u32AHB1_xxxx - RCC_u32AHB2_xxxx - RCC_u32APB1_xxxx - RCC_u32APB2_xxxx)						*
 *																									*
 *                                                                                                  *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED                                            *
 *  CHECK RCC_tenuErrorStatus ERROR ABOVE.                                                          *
 ****************************************************************************************************/
RCC_tenuErrorStatus RCC_enuDisablePeripheralClk(u8 Copy_u8Bus,
		u32 Copy_u32Peripheral) {
	/*DEFINE RETURN ERROR STATUS VARIABLE*/
	RCC_tenuErrorStatus LOC_enuReturnError = RCC_enuOk;
	/*SWITCH CASE TO CHECK DESIRED BUS*/
	switch (Copy_u8Bus) {
	case RCC_u8APB1_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_APB1ENR &= ~(Copy_u32Peripheral);
		break;
	case RCC_u8APB2_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_APB2ENR &= ~(Copy_u32Peripheral);
		break;
	case RCC_u8AHB1_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_AHB1ENR &= ~(Copy_u32Peripheral);
		break;
	case RCC_u8AHB2_BUS:
		/*ASSIGN THE PERIPHERAL MASK INTO THE REGISTER*/
		RCC->RCC_AHB2ENR &= ~(Copy_u32Peripheral);
		break;
	default:
		/*ASSIGN ERROR BUS IF THE BUS IS INVALID*/
		LOC_enuReturnError = RCC_enuErrorBus;
	}
	/*RETURN ERROR STATUS*/
	return LOC_enuReturnError;
}
