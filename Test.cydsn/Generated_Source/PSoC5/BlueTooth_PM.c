/*******************************************************************************
* File Name: BlueTooth_PM.c
* Version 2.50
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BlueTooth.h"


/***************************************
* Local data allocation
***************************************/

static BlueTooth_BACKUP_STRUCT  BlueTooth_backup =
{
    /* enableState - disabled */
    0u,
};



/*******************************************************************************
* Function Name: BlueTooth_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component nonretention control register.
*  Does not save the FIFO which is a set of nonretention registers.
*  This function is called by the BlueTooth_Sleep() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BlueTooth_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BlueTooth_SaveConfig(void)
{
    #if(BlueTooth_CONTROL_REG_REMOVED == 0u)
        BlueTooth_backup.cr = BlueTooth_CONTROL_REG;
    #endif /* End BlueTooth_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BlueTooth_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the nonretention control register except FIFO.
*  Does not restore the FIFO which is a set of nonretention registers.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BlueTooth_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
* Notes:
*  If this function is called without calling BlueTooth_SaveConfig() 
*  first, the data loaded may be incorrect.
*
*******************************************************************************/
void BlueTooth_RestoreConfig(void)
{
    #if(BlueTooth_CONTROL_REG_REMOVED == 0u)
        BlueTooth_CONTROL_REG = BlueTooth_backup.cr;
    #endif /* End BlueTooth_CONTROL_REG_REMOVED */
}


/*******************************************************************************
* Function Name: BlueTooth_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. 
*  The BlueTooth_Sleep() API saves the current component state. Then it
*  calls the BlueTooth_Stop() function and calls 
*  BlueTooth_SaveConfig() to save the hardware configuration.
*  Call the BlueTooth_Sleep() function before calling the CyPmSleep() 
*  or the CyPmHibernate() function. 
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BlueTooth_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BlueTooth_Sleep(void)
{
    #if(BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)
        if((BlueTooth_RXSTATUS_ACTL_REG  & BlueTooth_INT_ENABLE) != 0u)
        {
            BlueTooth_backup.enableState = 1u;
        }
        else
        {
            BlueTooth_backup.enableState = 0u;
        }
    #else
        if((BlueTooth_TXSTATUS_ACTL_REG  & BlueTooth_INT_ENABLE) !=0u)
        {
            BlueTooth_backup.enableState = 1u;
        }
        else
        {
            BlueTooth_backup.enableState = 0u;
        }
    #endif /* End BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED*/

    BlueTooth_Stop();
    BlueTooth_SaveConfig();
}


/*******************************************************************************
* Function Name: BlueTooth_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when 
*  BlueTooth_Sleep() was called. The BlueTooth_Wakeup() function
*  calls the BlueTooth_RestoreConfig() function to restore the 
*  configuration. If the component was enabled before the 
*  BlueTooth_Sleep() function was called, the BlueTooth_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BlueTooth_backup - used when non-retention registers are restored.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BlueTooth_Wakeup(void)
{
    BlueTooth_RestoreConfig();
    #if( (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) )
        BlueTooth_ClearRxBuffer();
    #endif /* End (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) */
    #if(BlueTooth_TX_ENABLED || BlueTooth_HD_ENABLED)
        BlueTooth_ClearTxBuffer();
    #endif /* End BlueTooth_TX_ENABLED || BlueTooth_HD_ENABLED */

    if(BlueTooth_backup.enableState != 0u)
    {
        BlueTooth_Enable();
    }
}


/* [] END OF FILE */
