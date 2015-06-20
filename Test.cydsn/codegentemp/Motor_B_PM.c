/*******************************************************************************
* File Name: Motor_B_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Motor_B.h"

/* Check for removal by optimization */
#if !defined(Motor_B_Sync_ctrl_reg__REMOVED)

static Motor_B_BACKUP_STRUCT  Motor_B_backup = {0u};

    
/*******************************************************************************
* Function Name: Motor_B_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Motor_B_SaveConfig(void) 
{
    Motor_B_backup.controlState = Motor_B_Control;
}


/*******************************************************************************
* Function Name: Motor_B_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void Motor_B_RestoreConfig(void) 
{
     Motor_B_Control = Motor_B_backup.controlState;
}


/*******************************************************************************
* Function Name: Motor_B_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Motor_B_Sleep(void) 
{
    Motor_B_SaveConfig();
}


/*******************************************************************************
* Function Name: Motor_B_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Motor_B_Wakeup(void)  
{
    Motor_B_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
