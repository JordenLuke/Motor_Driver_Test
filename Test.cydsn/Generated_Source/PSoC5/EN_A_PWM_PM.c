/*******************************************************************************
* File Name: EN_A_PWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "EN_A_PWM.h"

static EN_A_PWM_backupStruct EN_A_PWM_backup;


/*******************************************************************************
* Function Name: EN_A_PWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EN_A_PWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EN_A_PWM_SaveConfig(void) 
{

    #if(!EN_A_PWM_UsingFixedFunction)
        #if(!EN_A_PWM_PWMModeIsCenterAligned)
            EN_A_PWM_backup.PWMPeriod = EN_A_PWM_ReadPeriod();
        #endif /* (!EN_A_PWM_PWMModeIsCenterAligned) */
        EN_A_PWM_backup.PWMUdb = EN_A_PWM_ReadCounter();
        #if (EN_A_PWM_UseStatus)
            EN_A_PWM_backup.InterruptMaskValue = EN_A_PWM_STATUS_MASK;
        #endif /* (EN_A_PWM_UseStatus) */

        #if(EN_A_PWM_DeadBandMode == EN_A_PWM__B_PWM__DBM_256_CLOCKS || \
            EN_A_PWM_DeadBandMode == EN_A_PWM__B_PWM__DBM_2_4_CLOCKS)
            EN_A_PWM_backup.PWMdeadBandValue = EN_A_PWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EN_A_PWM_KillModeMinTime)
             EN_A_PWM_backup.PWMKillCounterPeriod = EN_A_PWM_ReadKillTime();
        #endif /* (EN_A_PWM_KillModeMinTime) */

        #if(EN_A_PWM_UseControl)
            EN_A_PWM_backup.PWMControlRegister = EN_A_PWM_ReadControlRegister();
        #endif /* (EN_A_PWM_UseControl) */
    #endif  /* (!EN_A_PWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EN_A_PWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EN_A_PWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EN_A_PWM_RestoreConfig(void) 
{
        #if(!EN_A_PWM_UsingFixedFunction)
            #if(!EN_A_PWM_PWMModeIsCenterAligned)
                EN_A_PWM_WritePeriod(EN_A_PWM_backup.PWMPeriod);
            #endif /* (!EN_A_PWM_PWMModeIsCenterAligned) */

            EN_A_PWM_WriteCounter(EN_A_PWM_backup.PWMUdb);

            #if (EN_A_PWM_UseStatus)
                EN_A_PWM_STATUS_MASK = EN_A_PWM_backup.InterruptMaskValue;
            #endif /* (EN_A_PWM_UseStatus) */

            #if(EN_A_PWM_DeadBandMode == EN_A_PWM__B_PWM__DBM_256_CLOCKS || \
                EN_A_PWM_DeadBandMode == EN_A_PWM__B_PWM__DBM_2_4_CLOCKS)
                EN_A_PWM_WriteDeadTime(EN_A_PWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EN_A_PWM_KillModeMinTime)
                EN_A_PWM_WriteKillTime(EN_A_PWM_backup.PWMKillCounterPeriod);
            #endif /* (EN_A_PWM_KillModeMinTime) */

            #if(EN_A_PWM_UseControl)
                EN_A_PWM_WriteControlRegister(EN_A_PWM_backup.PWMControlRegister);
            #endif /* (EN_A_PWM_UseControl) */
        #endif  /* (!EN_A_PWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EN_A_PWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EN_A_PWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EN_A_PWM_Sleep(void) 
{
    #if(EN_A_PWM_UseControl)
        if(EN_A_PWM_CTRL_ENABLE == (EN_A_PWM_CONTROL & EN_A_PWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            EN_A_PWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EN_A_PWM_backup.PWMEnableState = 0u;
        }
    #endif /* (EN_A_PWM_UseControl) */

    /* Stop component */
    EN_A_PWM_Stop();

    /* Save registers configuration */
    EN_A_PWM_SaveConfig();
}


/*******************************************************************************
* Function Name: EN_A_PWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EN_A_PWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EN_A_PWM_Wakeup(void) 
{
     /* Restore registers values */
    EN_A_PWM_RestoreConfig();

    if(EN_A_PWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EN_A_PWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
