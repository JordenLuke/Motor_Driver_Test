/*******************************************************************************
* File Name: BlueTooth.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
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
#if (BlueTooth_INTERNAL_CLOCK_USED)
    #include "BlueTooth_IntClock.h"
#endif /* End BlueTooth_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 BlueTooth_initVar = 0u;

#if (BlueTooth_TX_INTERRUPT_ENABLED && BlueTooth_TX_ENABLED)
    volatile uint8 BlueTooth_txBuffer[BlueTooth_TX_BUFFER_SIZE];
    volatile uint8 BlueTooth_txBufferRead = 0u;
    uint8 BlueTooth_txBufferWrite = 0u;
#endif /* (BlueTooth_TX_INTERRUPT_ENABLED && BlueTooth_TX_ENABLED) */

#if (BlueTooth_RX_INTERRUPT_ENABLED && (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED))
    uint8 BlueTooth_errorStatus = 0u;
    volatile uint8 BlueTooth_rxBuffer[BlueTooth_RX_BUFFER_SIZE];
    volatile uint8 BlueTooth_rxBufferRead  = 0u;
    volatile uint8 BlueTooth_rxBufferWrite = 0u;
    volatile uint8 BlueTooth_rxBufferLoopDetect = 0u;
    volatile uint8 BlueTooth_rxBufferOverflow   = 0u;
    #if (BlueTooth_RXHW_ADDRESS_ENABLED)
        volatile uint8 BlueTooth_rxAddressMode = BlueTooth_RX_ADDRESS_MODE;
        volatile uint8 BlueTooth_rxAddressDetected = 0u;
    #endif /* (BlueTooth_RXHW_ADDRESS_ENABLED) */
#endif /* (BlueTooth_RX_INTERRUPT_ENABLED && (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)) */


/*******************************************************************************
* Function Name: BlueTooth_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  BlueTooth_Start() sets the initVar variable, calls the
*  BlueTooth_Init() function, and then calls the
*  BlueTooth_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The BlueTooth_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time BlueTooth_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the BlueTooth_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BlueTooth_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(BlueTooth_initVar == 0u)
    {
        BlueTooth_Init();
        BlueTooth_initVar = 1u;
    }

    BlueTooth_Enable();
}


/*******************************************************************************
* Function Name: BlueTooth_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call BlueTooth_Init() because
*  the BlueTooth_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BlueTooth_Init(void) 
{
    #if(BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)

        #if (BlueTooth_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(BlueTooth_RX_VECT_NUM, &BlueTooth_RXISR);
            CyIntSetPriority(BlueTooth_RX_VECT_NUM, BlueTooth_RX_PRIOR_NUM);
            BlueTooth_errorStatus = 0u;
        #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

        #if (BlueTooth_RXHW_ADDRESS_ENABLED)
            BlueTooth_SetRxAddressMode(BlueTooth_RX_ADDRESS_MODE);
            BlueTooth_SetRxAddress1(BlueTooth_RX_HW_ADDRESS1);
            BlueTooth_SetRxAddress2(BlueTooth_RX_HW_ADDRESS2);
        #endif /* End BlueTooth_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        BlueTooth_RXBITCTR_PERIOD_REG = BlueTooth_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        BlueTooth_RXSTATUS_MASK_REG  = BlueTooth_INIT_RX_INTERRUPTS_MASK;
    #endif /* End BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED*/

    #if(BlueTooth_TX_ENABLED)
        #if (BlueTooth_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(BlueTooth_TX_VECT_NUM, &BlueTooth_TXISR);
            CyIntSetPriority(BlueTooth_TX_VECT_NUM, BlueTooth_TX_PRIOR_NUM);
        #endif /* (BlueTooth_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (BlueTooth_TXCLKGEN_DP)
            BlueTooth_TXBITCLKGEN_CTR_REG = BlueTooth_BIT_CENTER;
            BlueTooth_TXBITCLKTX_COMPLETE_REG = ((BlueTooth_NUMBER_OF_DATA_BITS +
                        BlueTooth_NUMBER_OF_START_BIT) * BlueTooth_OVER_SAMPLE_COUNT) - 1u;
        #else
            BlueTooth_TXBITCTR_PERIOD_REG = ((BlueTooth_NUMBER_OF_DATA_BITS +
                        BlueTooth_NUMBER_OF_START_BIT) * BlueTooth_OVER_SAMPLE_8) - 1u;
        #endif /* End BlueTooth_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (BlueTooth_TX_INTERRUPT_ENABLED)
            BlueTooth_TXSTATUS_MASK_REG = BlueTooth_TX_STS_FIFO_EMPTY;
        #else
            BlueTooth_TXSTATUS_MASK_REG = BlueTooth_INIT_TX_INTERRUPTS_MASK;
        #endif /*End BlueTooth_TX_INTERRUPT_ENABLED*/

    #endif /* End BlueTooth_TX_ENABLED */

    #if(BlueTooth_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        BlueTooth_WriteControlRegister( \
            (BlueTooth_ReadControlRegister() & (uint8)~BlueTooth_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(BlueTooth_PARITY_TYPE << BlueTooth_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End BlueTooth_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: BlueTooth_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call BlueTooth_Enable() because the BlueTooth_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BlueTooth_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void BlueTooth_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        BlueTooth_RXBITCTR_CONTROL_REG |= BlueTooth_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        BlueTooth_RXSTATUS_ACTL_REG  |= BlueTooth_INT_ENABLE;

        #if (BlueTooth_RX_INTERRUPT_ENABLED)
            BlueTooth_EnableRxInt();

            #if (BlueTooth_RXHW_ADDRESS_ENABLED)
                BlueTooth_rxAddressDetected = 0u;
            #endif /* (BlueTooth_RXHW_ADDRESS_ENABLED) */
        #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */
    #endif /* (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED) */

    #if(BlueTooth_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!BlueTooth_TXCLKGEN_DP)
            BlueTooth_TXBITCTR_CONTROL_REG |= BlueTooth_CNTR_ENABLE;
        #endif /* End BlueTooth_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        BlueTooth_TXSTATUS_ACTL_REG |= BlueTooth_INT_ENABLE;
        #if (BlueTooth_TX_INTERRUPT_ENABLED)
            BlueTooth_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            BlueTooth_EnableTxInt();
        #endif /* (BlueTooth_TX_INTERRUPT_ENABLED) */
     #endif /* (BlueTooth_TX_INTERRUPT_ENABLED) */

    #if (BlueTooth_INTERNAL_CLOCK_USED)
        BlueTooth_IntClock_Start();  /* Enable the clock */
    #endif /* (BlueTooth_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BlueTooth_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BlueTooth_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)
        BlueTooth_RXBITCTR_CONTROL_REG &= (uint8) ~BlueTooth_CNTR_ENABLE;
    #endif /* (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED) */

    #if (BlueTooth_TX_ENABLED)
        #if(!BlueTooth_TXCLKGEN_DP)
            BlueTooth_TXBITCTR_CONTROL_REG &= (uint8) ~BlueTooth_CNTR_ENABLE;
        #endif /* (!BlueTooth_TXCLKGEN_DP) */
    #endif /* (BlueTooth_TX_ENABLED) */

    #if (BlueTooth_INTERNAL_CLOCK_USED)
        BlueTooth_IntClock_Stop();   /* Disable the clock */
    #endif /* (BlueTooth_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)
        BlueTooth_RXSTATUS_ACTL_REG  &= (uint8) ~BlueTooth_INT_ENABLE;

        #if (BlueTooth_RX_INTERRUPT_ENABLED)
            BlueTooth_DisableRxInt();
        #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */
    #endif /* (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED) */

    #if (BlueTooth_TX_ENABLED)
        BlueTooth_TXSTATUS_ACTL_REG &= (uint8) ~BlueTooth_INT_ENABLE;

        #if (BlueTooth_TX_INTERRUPT_ENABLED)
            BlueTooth_DisableTxInt();
        #endif /* (BlueTooth_TX_INTERRUPT_ENABLED) */
    #endif /* (BlueTooth_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BlueTooth_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 BlueTooth_ReadControlRegister(void) 
{
    #if (BlueTooth_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(BlueTooth_CONTROL_REG);
    #endif /* (BlueTooth_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: BlueTooth_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  BlueTooth_WriteControlRegister(uint8 control) 
{
    #if (BlueTooth_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       BlueTooth_CONTROL_REG = control;
    #endif /* (BlueTooth_CONTROL_REG_REMOVED) */
}


#if(BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)
    /*******************************************************************************
    * Function Name: BlueTooth_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      BlueTooth_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      BlueTooth_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      BlueTooth_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      BlueTooth_RX_STS_BREAK            Interrupt on break.
    *      BlueTooth_RX_STS_OVERRUN          Interrupt on overrun error.
    *      BlueTooth_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      BlueTooth_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BlueTooth_SetRxInterruptMode(uint8 intSrc) 
    {
        BlueTooth_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: BlueTooth_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  BlueTooth_rxBuffer - RAM buffer pointer for save received data.
    *  BlueTooth_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BlueTooth_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BlueTooth_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BlueTooth_ReadRxData(void) 
    {
        uint8 rxData;

    #if (BlueTooth_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BlueTooth_DisableRxInt();

        locRxBufferRead  = BlueTooth_rxBufferRead;
        locRxBufferWrite = BlueTooth_rxBufferWrite;

        if( (BlueTooth_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BlueTooth_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= BlueTooth_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BlueTooth_rxBufferRead = locRxBufferRead;

            if(BlueTooth_rxBufferLoopDetect != 0u)
            {
                BlueTooth_rxBufferLoopDetect = 0u;
                #if ((BlueTooth_RX_INTERRUPT_ENABLED) && (BlueTooth_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BlueTooth_HD_ENABLED )
                        if((BlueTooth_CONTROL_REG & BlueTooth_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BlueTooth_RXSTATUS_MASK_REG  |= BlueTooth_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BlueTooth_RXSTATUS_MASK_REG  |= BlueTooth_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BlueTooth_HD_ENABLED */
                #endif /* ((BlueTooth_RX_INTERRUPT_ENABLED) && (BlueTooth_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = BlueTooth_RXDATA_REG;
        }

        BlueTooth_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = BlueTooth_RXDATA_REG;

    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BlueTooth_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  BlueTooth_RX_STS_FIFO_NOTEMPTY.
    *  BlueTooth_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  BlueTooth_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   BlueTooth_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   BlueTooth_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 BlueTooth_ReadRxStatus(void) 
    {
        uint8 status;

        status = BlueTooth_RXSTATUS_REG & BlueTooth_RX_HW_MASK;

    #if (BlueTooth_RX_INTERRUPT_ENABLED)
        if(BlueTooth_rxBufferOverflow != 0u)
        {
            status |= BlueTooth_RX_STS_SOFT_BUFF_OVER;
            BlueTooth_rxBufferOverflow = 0u;
        }
    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: BlueTooth_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. BlueTooth_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  BlueTooth_rxBuffer - RAM buffer pointer for save received data.
    *  BlueTooth_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BlueTooth_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BlueTooth_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BlueTooth_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (BlueTooth_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BlueTooth_DisableRxInt();

        locRxBufferRead  = BlueTooth_rxBufferRead;
        locRxBufferWrite = BlueTooth_rxBufferWrite;

        if( (BlueTooth_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BlueTooth_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= BlueTooth_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BlueTooth_rxBufferRead = locRxBufferRead;

            if(BlueTooth_rxBufferLoopDetect != 0u)
            {
                BlueTooth_rxBufferLoopDetect = 0u;
                #if( (BlueTooth_RX_INTERRUPT_ENABLED) && (BlueTooth_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BlueTooth_HD_ENABLED )
                        if((BlueTooth_CONTROL_REG & BlueTooth_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BlueTooth_RXSTATUS_MASK_REG |= BlueTooth_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BlueTooth_RXSTATUS_MASK_REG |= BlueTooth_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BlueTooth_HD_ENABLED */
                #endif /* BlueTooth_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = BlueTooth_RXSTATUS_REG;
            if((rxStatus & BlueTooth_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = BlueTooth_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (BlueTooth_RX_STS_BREAK | BlueTooth_RX_STS_PAR_ERROR |
                                BlueTooth_RX_STS_STOP_ERROR | BlueTooth_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        BlueTooth_EnableRxInt();

    #else

        rxStatus =BlueTooth_RXSTATUS_REG;
        if((rxStatus & BlueTooth_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = BlueTooth_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (BlueTooth_RX_STS_BREAK | BlueTooth_RX_STS_PAR_ERROR |
                            BlueTooth_RX_STS_STOP_ERROR | BlueTooth_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BlueTooth_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 BlueTooth_GetByte(void) 
    {
        
    #if (BlueTooth_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        BlueTooth_DisableRxInt();
        locErrorStatus = (uint16)BlueTooth_errorStatus;
        BlueTooth_errorStatus = 0u;
        BlueTooth_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | BlueTooth_ReadRxData() );
    #else
        return ( ((uint16)BlueTooth_ReadRxStatus() << 8u) | BlueTooth_ReadRxData() );
    #endif /* BlueTooth_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: BlueTooth_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  BlueTooth_rxBufferWrite - used to calculate left bytes.
    *  BlueTooth_rxBufferRead - used to calculate left bytes.
    *  BlueTooth_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 BlueTooth_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BlueTooth_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        BlueTooth_DisableRxInt();

        if(BlueTooth_rxBufferRead == BlueTooth_rxBufferWrite)
        {
            if(BlueTooth_rxBufferLoopDetect != 0u)
            {
                size = BlueTooth_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(BlueTooth_rxBufferRead < BlueTooth_rxBufferWrite)
        {
            size = (BlueTooth_rxBufferWrite - BlueTooth_rxBufferRead);
        }
        else
        {
            size = (BlueTooth_RX_BUFFER_SIZE - BlueTooth_rxBufferRead) + BlueTooth_rxBufferWrite;
        }

        BlueTooth_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((BlueTooth_RXSTATUS_REG & BlueTooth_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: BlueTooth_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_rxBufferWrite - cleared to zero.
    *  BlueTooth_rxBufferRead - cleared to zero.
    *  BlueTooth_rxBufferLoopDetect - cleared to zero.
    *  BlueTooth_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void BlueTooth_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        BlueTooth_RXDATA_AUX_CTL_REG |= (uint8)  BlueTooth_RX_FIFO_CLR;
        BlueTooth_RXDATA_AUX_CTL_REG &= (uint8) ~BlueTooth_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BlueTooth_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BlueTooth_DisableRxInt();

        BlueTooth_rxBufferRead = 0u;
        BlueTooth_rxBufferWrite = 0u;
        BlueTooth_rxBufferLoopDetect = 0u;
        BlueTooth_rxBufferOverflow = 0u;

        BlueTooth_EnableRxInt();

    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: BlueTooth_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  BlueTooth__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  BlueTooth__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  BlueTooth__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  BlueTooth__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  BlueTooth__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  BlueTooth_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void BlueTooth_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(BlueTooth_RXHW_ADDRESS_ENABLED)
            #if(BlueTooth_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* BlueTooth_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = BlueTooth_CONTROL_REG & (uint8)~BlueTooth_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << BlueTooth_CTRL_RXADDR_MODE0_SHIFT);
                BlueTooth_CONTROL_REG = tmpCtrl;

                #if(BlueTooth_RX_INTERRUPT_ENABLED && \
                   (BlueTooth_RXBUFFERSIZE > BlueTooth_FIFO_LENGTH) )
                    BlueTooth_rxAddressMode = addressMode;
                    BlueTooth_rxAddressDetected = 0u;
                #endif /* End BlueTooth_RXBUFFERSIZE > BlueTooth_FIFO_LENGTH*/
            #endif /* End BlueTooth_CONTROL_REG_REMOVED */
        #else /* BlueTooth_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End BlueTooth_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BlueTooth_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BlueTooth_SetRxAddress1(uint8 address) 
    {
        BlueTooth_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: BlueTooth_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BlueTooth_SetRxAddress2(uint8 address) 
    {
        BlueTooth_RXADDRESS2_REG = address;
    }

#endif  /* BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED*/


#if( (BlueTooth_TX_ENABLED) || (BlueTooth_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: BlueTooth_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   BlueTooth_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   BlueTooth_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   BlueTooth_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   BlueTooth_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BlueTooth_SetTxInterruptMode(uint8 intSrc) 
    {
        BlueTooth_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: BlueTooth_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  BlueTooth_txBuffer - RAM buffer pointer for save data for transmission
    *  BlueTooth_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  BlueTooth_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  BlueTooth_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BlueTooth_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(BlueTooth_initVar != 0u)
        {
        #if (BlueTooth_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            BlueTooth_DisableTxInt();

            if( (BlueTooth_txBufferRead == BlueTooth_txBufferWrite) &&
                ((BlueTooth_TXSTATUS_REG & BlueTooth_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                BlueTooth_TXDATA_REG = txDataByte;
            }
            else
            {
                if(BlueTooth_txBufferWrite >= BlueTooth_TX_BUFFER_SIZE)
                {
                    BlueTooth_txBufferWrite = 0u;
                }

                BlueTooth_txBuffer[BlueTooth_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                BlueTooth_txBufferWrite++;
            }

            BlueTooth_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            BlueTooth_TXDATA_REG = txDataByte;

        #endif /*(BlueTooth_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: BlueTooth_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 BlueTooth_ReadTxStatus(void) 
    {
        return(BlueTooth_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: BlueTooth_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_txBuffer - RAM buffer pointer for save data for transmission
    *  BlueTooth_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  BlueTooth_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  BlueTooth_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void BlueTooth_PutChar(uint8 txDataByte) 
    {
    #if (BlueTooth_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            BlueTooth_DisableTxInt();
        #endif /* (BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = BlueTooth_txBufferWrite;
            locTxBufferRead  = BlueTooth_txBufferRead;

        #if ((BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            BlueTooth_EnableTxInt();
        #endif /* (BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(BlueTooth_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((BlueTooth_TXSTATUS_REG & BlueTooth_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            BlueTooth_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= BlueTooth_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            BlueTooth_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3))
            BlueTooth_DisableTxInt();
        #endif /* (BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3) */

            BlueTooth_txBufferWrite = locTxBufferWrite;

        #if ((BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3))
            BlueTooth_EnableTxInt();
        #endif /* (BlueTooth_TX_BUFFER_SIZE > BlueTooth_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (BlueTooth_TXSTATUS_REG & BlueTooth_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                BlueTooth_SetPendingTxInt();
            }
        }

    #else

        while((BlueTooth_TXSTATUS_REG & BlueTooth_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        BlueTooth_TXDATA_REG = txDataByte;

    #endif /* BlueTooth_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BlueTooth_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void BlueTooth_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BlueTooth_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                BlueTooth_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BlueTooth_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void BlueTooth_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BlueTooth_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                BlueTooth_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BlueTooth_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BlueTooth_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(BlueTooth_initVar != 0u)
        {
            BlueTooth_PutChar(txDataByte);
            BlueTooth_PutChar(0x0Du);
            BlueTooth_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: BlueTooth_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  BlueTooth_txBufferWrite - used to calculate left space.
    *  BlueTooth_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 BlueTooth_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BlueTooth_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BlueTooth_DisableTxInt();

        if(BlueTooth_txBufferRead == BlueTooth_txBufferWrite)
        {
            size = 0u;
        }
        else if(BlueTooth_txBufferRead < BlueTooth_txBufferWrite)
        {
            size = (BlueTooth_txBufferWrite - BlueTooth_txBufferRead);
        }
        else
        {
            size = (BlueTooth_TX_BUFFER_SIZE - BlueTooth_txBufferRead) +
                    BlueTooth_txBufferWrite;
        }

        BlueTooth_EnableTxInt();

    #else

        size = BlueTooth_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & BlueTooth_TX_STS_FIFO_FULL) != 0u)
        {
            size = BlueTooth_FIFO_LENGTH;
        }
        else if((size & BlueTooth_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (BlueTooth_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: BlueTooth_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_txBufferWrite - cleared to zero.
    *  BlueTooth_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void BlueTooth_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        BlueTooth_TXDATA_AUX_CTL_REG |= (uint8)  BlueTooth_TX_FIFO_CLR;
        BlueTooth_TXDATA_AUX_CTL_REG &= (uint8) ~BlueTooth_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BlueTooth_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BlueTooth_DisableTxInt();

        BlueTooth_txBufferRead = 0u;
        BlueTooth_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        BlueTooth_EnableTxInt();

    #endif /* (BlueTooth_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BlueTooth_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   BlueTooth_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   BlueTooth_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   BlueTooth_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   BlueTooth_SEND_WAIT_REINIT - Performs both options: 
    *      BlueTooth_SEND_BREAK and BlueTooth_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with BlueTooth_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The BlueTooth_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void BlueTooth_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(BlueTooth_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(BlueTooth_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == BlueTooth_SEND_BREAK) ||
                (retMode == BlueTooth_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() |
                                                      BlueTooth_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                BlueTooth_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BlueTooth_TXSTATUS_REG;
                }
                while((tmpStat & BlueTooth_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BlueTooth_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BlueTooth_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BlueTooth_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BlueTooth_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BlueTooth_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BlueTooth_REINIT) ||
                (retMode == BlueTooth_SEND_WAIT_REINIT) )
            {
                BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() &
                                              (uint8)~BlueTooth_CTRL_HD_SEND_BREAK);
            }

        #else /* BlueTooth_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == BlueTooth_SEND_BREAK) ||
                (retMode == BlueTooth_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (BlueTooth_PARITY_TYPE != BlueTooth__B_UART__NONE_REVB) || \
                                    (BlueTooth_PARITY_TYPE_SW != 0u) )
                    BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() |
                                                          BlueTooth_CTRL_HD_SEND_BREAK);
                #endif /* End BlueTooth_PARITY_TYPE != BlueTooth__B_UART__NONE_REVB  */

                #if(BlueTooth_TXCLKGEN_DP)
                    txPeriod = BlueTooth_TXBITCLKTX_COMPLETE_REG;
                    BlueTooth_TXBITCLKTX_COMPLETE_REG = BlueTooth_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = BlueTooth_TXBITCTR_PERIOD_REG;
                    BlueTooth_TXBITCTR_PERIOD_REG = BlueTooth_TXBITCTR_BREAKBITS8X;
                #endif /* End BlueTooth_TXCLKGEN_DP */

                /* Send zeros */
                BlueTooth_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BlueTooth_TXSTATUS_REG;
                }
                while((tmpStat & BlueTooth_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BlueTooth_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BlueTooth_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BlueTooth_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BlueTooth_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BlueTooth_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BlueTooth_REINIT) ||
                (retMode == BlueTooth_SEND_WAIT_REINIT) )
            {

            #if(BlueTooth_TXCLKGEN_DP)
                BlueTooth_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                BlueTooth_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End BlueTooth_TXCLKGEN_DP */

            #if( (BlueTooth_PARITY_TYPE != BlueTooth__B_UART__NONE_REVB) || \
                 (BlueTooth_PARITY_TYPE_SW != 0u) )
                BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() &
                                                      (uint8) ~BlueTooth_CTRL_HD_SEND_BREAK);
            #endif /* End BlueTooth_PARITY_TYPE != NONE */
            }
        #endif    /* End BlueTooth_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: BlueTooth_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       BlueTooth_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       BlueTooth_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears BlueTooth_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void BlueTooth_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( BlueTooth_CONTROL_REG_REMOVED == 0u )
            BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() |
                                                  BlueTooth_CTRL_MARK);
        #endif /* End BlueTooth_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( BlueTooth_CONTROL_REG_REMOVED == 0u )
            BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() &
                                                  (uint8) ~BlueTooth_CTRL_MARK);
        #endif /* End BlueTooth_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndBlueTooth_TX_ENABLED */

#if(BlueTooth_HD_ENABLED)


    /*******************************************************************************
    * Function Name: BlueTooth_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void BlueTooth_LoadRxConfig(void) 
    {
        BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() &
                                                (uint8)~BlueTooth_CTRL_HD_SEND);
        BlueTooth_RXBITCTR_PERIOD_REG = BlueTooth_HD_RXBITCTR_INIT;

    #if (BlueTooth_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        BlueTooth_SetRxInterruptMode(BlueTooth_INIT_RX_INTERRUPTS_MASK);
    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BlueTooth_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void BlueTooth_LoadTxConfig(void) 
    {
    #if (BlueTooth_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        BlueTooth_SetRxInterruptMode(0u);
    #endif /* (BlueTooth_RX_INTERRUPT_ENABLED) */

        BlueTooth_WriteControlRegister(BlueTooth_ReadControlRegister() | BlueTooth_CTRL_HD_SEND);
        BlueTooth_RXBITCTR_PERIOD_REG = BlueTooth_HD_TXBITCTR_INIT;
    }

#endif  /* BlueTooth_HD_ENABLED */


/* [] END OF FILE */
