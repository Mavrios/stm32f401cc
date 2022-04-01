/*
 * NVIC.h
 *
 *  Created on: Mar 28, 2022
 *      Author: Kishk
 */

#ifndef MCAL_NVIC_H_
#define MCAL_NVIC_H_

/******************************************** TYPEDEF ********************************************/
typedef enum{
	NVIC_enuOk,
	NVIC_enuErrorIRQNumber,
	NVIC_enuErrorNumberOfGrouping,
	NVIC_enuErrorSubGroup,
	NVIC_enuErrorNullPointer,
}NVIC_ErrorStatus_t;

/********************************************* MACROS *********************************************/
#define NVIC_u8PENDING_ON			((u8) 0x01)
#define NVIC_u8PENDING_OFF			((u8) 0x00)

#define NVIC_u32SUB_GROUP_NONE		((u32) 0x00000000)
#define NVIC_u32SUB_GROUP_ONE		((u32) 0x00000400)
#define NVIC_u32SUB_GROUP_TWO		((u32) 0x00000500)
#define NVIC_u32SUB_GROUP_THREE		((u32) 0x00000600)
#define NVIC_u32SUB_GROUP_FOUR		((u32) 0x00000700)

/******************************************* PROTOTYPES *******************************************/
/*
 * Function:  NVIC_EnableIRQ
 * --------------------
 * ENABLE IRQ FOR SPECIFIC PERIPHERAL
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_EnableIRQ(u8 Copy_u8IRQn);
/*
 * Function:  NVIC_DisableIRQ
 * --------------------
 * DISABLE IRQ FOR SPECIFIC PERIPHERAL
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_DisableIRQ(u8 Copy_u8IRQn);
/*
 * Function:  NVIC_GetPendingIRQ
 * --------------------
 * READ PENDING FOR SPECIFIC IRQ
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 * Add_pu8Pending: ADDRESS OF VARIABLE TO STORE RESULT INSIDE IT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_GetPendingIRQ (u8 Copy_u8IRQn , pu8 Add_pu8Pending);
/*
 * Function:  NVIC_SetPendingIRQ
 * --------------------
 * SET PENDING FOR SPECIFIC IRQ
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_SetPendingIRQ (u8 Copy_u8IRQn);
/*
 * Function:  NVIC_ClearPendingIRQ
 * --------------------
 * CLEAR PENDING FOR SPECIFIC IRQ
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_ClearPendingIRQ (u8 Copy_u8IRQn);
/*
 * Function:  NVIC_GetActive
 * --------------------
 * GET PENDING FOR SPECIFIC IRQ
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 * Add_pu8Active: ADDRESS OF VARIABLE TO STORE THE RESULT INSIDE IT
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_GetActive (u8 Copy_u8IRQn , pu8 Add_pu8Active);
/*
 * Function:  NVIC_SetPriority
 * --------------------
 * SET PERIORITY FOR SPECIFIC IRQ
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 * Copy_u8Priority: DESIRED PERIORITY WITH SUBGROUP PERIORITY
 *
 * NOTE: YOU CAN USE "getEncodingPriority" TO CALCULATE THE PERIORITY.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_SetPriority (u8 Copy_u8IRQn, u8 Copy_u8Priority);
/*
 * Function:  NVIC_setSubGroup
 * --------------------
 * CONFIGURE NUMBER OF BITS TO USE IN PERIORITY
 *
 * Copy_u32SubGroup: OPTIONS --> NVIC_u32SUB_GROUP_xxx
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_setSubGroup (u32 Copy_u32SubGroup);
/*
 * Function:  NVIC_GetPriority
 * --------------------
 * READ CURRENT PERIORITY FOR SPECIFIC IRQ
 *
 * Copy_u8IRQn: NUMBER OF DESIRED IRQ
 * Add_pu8Priority: ADDRESS OF VARIABLE TO STORE THE RESULT INSIDE IT.
 *
 *  returns: AN ERROR STATUS IF SOMETHING WRONG HAPPENED
 *  CHECK NVIC_ErrorStatus_t ERROR ENUM.
 */
NVIC_ErrorStatus_t NVIC_GetPriority (u8 Copy_u8IRQn, pu8 Add_pu8Priority);
/*
 * Function:  getEncodingPriority
 * --------------------
 * FUNCTION TO ENCODE PERIORITY TO BE USED IN "NVIC_SetPriority" FUNCTION.
 *
 * Number_of_Sub_Group: NUMBER OF SUB GROUP BITS.
 * Sub_Group_Priority: SUB-GROUP PERIORITY
 * PreemptionPeriority: PREEMPTION PERIORITY.
 *
 *  returns: THE ENCODED VALUE TO BE USED INSIDE "NVIC_SetPriority" FUNCTION.
 */
u32 getEncodingPriority(u8 Number_of_Sub_Group, u8 Sub_Group_Priority,u8 PreemptionPeriority);


#endif /* MCAL_NVIC_H_ */
