/*******************************************************************************
* File Name: BlueToothINT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service functionality of the UART component
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BlueTooth.h"


/***************************************
* Custom Declarations
***************************************/
/* `#START CUSTOM_DECLARATIONS` Place your declaration here */

/* `#END` */

#if (BlueTooth_RX_INTERRUPT_ENABLED && (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED))
    /*******************************************************************************
    * Function Name: BlueTooth_RXISR
    ********************************************************************************
    *
    * Summary:
    *  Interrupt Service Routine for RX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_rxBuffer - RAM buffer pointer for save received data.
    *  BlueTooth_rxBufferWrite - cyclic index for write to rxBuffer,
    *     increments after each byte saved to buffer.
    *  BlueTooth_rxBufferRead - cyclic index for read from rxBuffer,
    *     checked to detect overflow condition.
    *  BlueTooth_rxBufferOverflow - software overflow flag. Set to one
    *     when BlueTooth_rxBufferWrite index overtakes
    *     BlueTooth_rxBufferRead index.
    *  BlueTooth_rxBufferLoopDetect - additional variable to detect overflow.
    *     Set to one when BlueTooth_rxBufferWrite is equal to
    *    BlueTooth_rxBufferRead
    *  BlueTooth_rxAddressMode - this variable contains the Address mode,
    *     selected in customizer or set by UART_SetRxAddressMode() API.
    *  BlueTooth_rxAddressDetected - set to 1 when correct address received,
    *     and analysed to store following addressed data bytes to the buffer.
    *     When not correct address received, set to 0 to skip following data bytes.
    *
    *******************************************************************************/
    CY_ISR(BlueTooth_RXISR)
    {
        uint8 readData;
        uint8 readStatus;
        uint8 increment_pointer = 0u;

    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START BlueTooth_RXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        do
        {
            /* Read receiver status register */
            readStatus = BlueTooth_RXSTATUS_REG;
            /* Copy the same status to readData variable for backward compatibility support 
            *  of the user code in BlueTooth_RXISR_ERROR` section. 
            */
            readData = readStatus;

            if((readStatus & (BlueTooth_RX_STS_BREAK | 
                            BlueTooth_RX_STS_PAR_ERROR |
                            BlueTooth_RX_STS_STOP_ERROR | 
                            BlueTooth_RX_STS_OVERRUN)) != 0u)
            {
                /* ERROR handling. */
                BlueTooth_errorStatus |= readStatus & ( BlueTooth_RX_STS_BREAK | 
                                                            BlueTooth_RX_STS_PAR_ERROR | 
                                                            BlueTooth_RX_STS_STOP_ERROR | 
                                                            BlueTooth_RX_STS_OVERRUN);
                /* `#START BlueTooth_RXISR_ERROR` */

                /* `#END` */
            }
            
            if((readStatus & BlueTooth_RX_STS_FIFO_NOTEMPTY) != 0u)
            {
                /* Read data from the RX data register */
                readData = BlueTooth_RXDATA_REG;
            #if (BlueTooth_RXHW_ADDRESS_ENABLED)
                if(BlueTooth_rxAddressMode == (uint8)BlueTooth__B_UART__AM_SW_DETECT_TO_BUFFER)
                {
                    if((readStatus & BlueTooth_RX_STS_MRKSPC) != 0u)
                    {
                        if ((readStatus & BlueTooth_RX_STS_ADDR_MATCH) != 0u)
                        {
                            BlueTooth_rxAddressDetected = 1u;
                        }
                        else
                        {
                            BlueTooth_rxAddressDetected = 0u;
                        }
                    }
                    if(BlueTooth_rxAddressDetected != 0u)
                    {   /* Store only addressed data */
                        BlueTooth_rxBuffer[BlueTooth_rxBufferWrite] = readData;
                        increment_pointer = 1u;
                    }
                }
                else /* Without software addressing */
                {
                    BlueTooth_rxBuffer[BlueTooth_rxBufferWrite] = readData;
                    increment_pointer = 1u;
                }
            #else  /* Without addressing */
                BlueTooth_rxBuffer[BlueTooth_rxBufferWrite] = readData;
                increment_pointer = 1u;
            #endif /* (BlueTooth_RXHW_ADDRESS_ENABLED) */

                /* Do not increment buffer pointer when skip not addressed data */
                if(increment_pointer != 0u)
                {
                    if(BlueTooth_rxBufferLoopDetect != 0u)
                    {   /* Set Software Buffer status Overflow */
                        BlueTooth_rxBufferOverflow = 1u;
                    }
                    /* Set next pointer. */
                    BlueTooth_rxBufferWrite++;

                    /* Check pointer for a loop condition */
                    if(BlueTooth_rxBufferWrite >= BlueTooth_RX_BUFFER_SIZE)
                    {
                        BlueTooth_rxBufferWrite = 0u;
                    }

                    /* Detect pre-overload condition and set flag */
                    if(BlueTooth_rxBufferWrite == BlueTooth_rxBufferRead)
                    {
                        BlueTooth_rxBufferLoopDetect = 1u;
                        /* When Hardware Flow Control selected */
                        #if (BlueTooth_FLOW_CONTROL != 0u)
                            /* Disable RX interrupt mask, it is enabled when user read data from the buffer using APIs */
                            BlueTooth_RXSTATUS_MASK_REG  &= (uint8)~BlueTooth_RX_STS_FIFO_NOTEMPTY;
                            CyIntClearPending(BlueTooth_RX_VECT_NUM);
                            break; /* Break the reading of the FIFO loop, leave the data there for generating RTS signal */
                        #endif /* (BlueTooth_FLOW_CONTROL != 0u) */
                    }
                }
            }
        }while((readStatus & BlueTooth_RX_STS_FIFO_NOTEMPTY) != 0u);

        /* User code required at end of ISR (Optional) */
        /* `#START BlueTooth_RXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (BlueTooth_RX_INTERRUPT_ENABLED && (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)) */


#if (BlueTooth_TX_INTERRUPT_ENABLED && BlueTooth_TX_ENABLED)
    /*******************************************************************************
    * Function Name: BlueTooth_TXISR
    ********************************************************************************
    *
    * Summary:
    * Interrupt Service Routine for the TX portion of the UART
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BlueTooth_txBuffer - RAM buffer pointer for transmit data from.
    *  BlueTooth_txBufferRead - cyclic index for read and transmit data
    *     from txBuffer, increments after each transmitted byte.
    *  BlueTooth_rxBufferWrite - cyclic index for write to txBuffer,
    *     checked to detect available for transmission bytes.
    *
    *******************************************************************************/
    CY_ISR(BlueTooth_TXISR)
    {
    #if(CY_PSOC3)
        uint8 int_en;
    #endif /* (CY_PSOC3) */

        /* User code required at start of ISR */
        /* `#START BlueTooth_TXISR_START` */

        /* `#END` */

    #if(CY_PSOC3)   /* Make sure nested interrupt is enabled */
        int_en = EA;
        CyGlobalIntEnable;
    #endif /* (CY_PSOC3) */

        while((BlueTooth_txBufferRead != BlueTooth_txBufferWrite) &&
             ((BlueTooth_TXSTATUS_REG & BlueTooth_TX_STS_FIFO_FULL) == 0u))
        {
            /* Check pointer wrap around */
            if(BlueTooth_txBufferRead >= BlueTooth_TX_BUFFER_SIZE)
            {
                BlueTooth_txBufferRead = 0u;
            }

            BlueTooth_TXDATA_REG = BlueTooth_txBuffer[BlueTooth_txBufferRead];

            /* Set next pointer */
            BlueTooth_txBufferRead++;
        }

        /* User code required at end of ISR (Optional) */
        /* `#START BlueTooth_TXISR_END` */

        /* `#END` */

    #if(CY_PSOC3)
        EA = int_en;
    #endif /* (CY_PSOC3) */
    }

#endif /* (BlueTooth_TX_INTERRUPT_ENABLED && BlueTooth_TX_ENABLED) */


/* [] END OF FILE */
