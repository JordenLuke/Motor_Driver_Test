/*******************************************************************************
* File Name: Motor_B.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_Motor_B_H) /* CY_CONTROL_REG_Motor_B_H */
#define CY_CONTROL_REG_Motor_B_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} Motor_B_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    Motor_B_Write(uint8 control) ;
uint8   Motor_B_Read(void) ;

void Motor_B_SaveConfig(void) ;
void Motor_B_RestoreConfig(void) ;
void Motor_B_Sleep(void) ; 
void Motor_B_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define Motor_B_Control        (* (reg8 *) Motor_B_Sync_ctrl_reg__CONTROL_REG )
#define Motor_B_Control_PTR    (  (reg8 *) Motor_B_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_Motor_B_H */


/* [] END OF FILE */
