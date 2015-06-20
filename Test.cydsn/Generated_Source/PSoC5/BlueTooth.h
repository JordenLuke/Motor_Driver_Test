/*******************************************************************************
* File Name: BlueTooth.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_BlueTooth_H)
#define CY_UART_BlueTooth_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define BlueTooth_RX_ENABLED                     (1u)
#define BlueTooth_TX_ENABLED                     (1u)
#define BlueTooth_HD_ENABLED                     (0u)
#define BlueTooth_RX_INTERRUPT_ENABLED           (0u)
#define BlueTooth_TX_INTERRUPT_ENABLED           (0u)
#define BlueTooth_INTERNAL_CLOCK_USED            (1u)
#define BlueTooth_RXHW_ADDRESS_ENABLED           (0u)
#define BlueTooth_OVER_SAMPLE_COUNT              (8u)
#define BlueTooth_PARITY_TYPE                    (0u)
#define BlueTooth_PARITY_TYPE_SW                 (0u)
#define BlueTooth_BREAK_DETECT                   (0u)
#define BlueTooth_BREAK_BITS_TX                  (13u)
#define BlueTooth_BREAK_BITS_RX                  (13u)
#define BlueTooth_TXCLKGEN_DP                    (1u)
#define BlueTooth_USE23POLLING                   (1u)
#define BlueTooth_FLOW_CONTROL                   (0u)
#define BlueTooth_CLK_FREQ                       (0u)
#define BlueTooth_TX_BUFFER_SIZE                 (4u)
#define BlueTooth_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define BlueTooth_CONTROL_REG_REMOVED            (0u)
#else
    #define BlueTooth_CONTROL_REG_REMOVED            (1u)
#endif /* End BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct BlueTooth_backupStruct_
{
    uint8 enableState;

    #if(BlueTooth_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End BlueTooth_CONTROL_REG_REMOVED */

} BlueTooth_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void BlueTooth_Start(void) ;
void BlueTooth_Stop(void) ;
uint8 BlueTooth_ReadControlRegister(void) ;
void BlueTooth_WriteControlRegister(uint8 control) ;

void BlueTooth_Init(void) ;
void BlueTooth_Enable(void) ;
void BlueTooth_SaveConfig(void) ;
void BlueTooth_RestoreConfig(void) ;
void BlueTooth_Sleep(void) ;
void BlueTooth_Wakeup(void) ;

/* Only if RX is enabled */
#if( (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) )

    #if (BlueTooth_RX_INTERRUPT_ENABLED)
        #define BlueTooth_EnableRxInt()  CyIntEnable (BlueTooth_RX_VECT_NUM)
        #define BlueTooth_DisableRxInt() CyIntDisable(BlueTooth_RX_VECT_NUM)
        CY_ISR_PROTO(BlueTooth_RXISR);
    #endif /* BlueTooth_RX_INTERRUPT_ENABLED */

    void BlueTooth_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void BlueTooth_SetRxAddress1(uint8 address) ;
    void BlueTooth_SetRxAddress2(uint8 address) ;

    void  BlueTooth_SetRxInterruptMode(uint8 intSrc) ;
    uint8 BlueTooth_ReadRxData(void) ;
    uint8 BlueTooth_ReadRxStatus(void) ;
    uint8 BlueTooth_GetChar(void) ;
    uint16 BlueTooth_GetByte(void) ;
    uint8 BlueTooth_GetRxBufferSize(void)
                                                            ;
    void BlueTooth_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define BlueTooth_GetRxInterruptSource   BlueTooth_ReadRxStatus

#endif /* End (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) */

/* Only if TX is enabled */
#if(BlueTooth_TX_ENABLED || BlueTooth_HD_ENABLED)

    #if(BlueTooth_TX_INTERRUPT_ENABLED)
        #define BlueTooth_EnableTxInt()  CyIntEnable (BlueTooth_TX_VECT_NUM)
        #define BlueTooth_DisableTxInt() CyIntDisable(BlueTooth_TX_VECT_NUM)
        #define BlueTooth_SetPendingTxInt() CyIntSetPending(BlueTooth_TX_VECT_NUM)
        #define BlueTooth_ClearPendingTxInt() CyIntClearPending(BlueTooth_TX_VECT_NUM)
        CY_ISR_PROTO(BlueTooth_TXISR);
    #endif /* BlueTooth_TX_INTERRUPT_ENABLED */

    void BlueTooth_SetTxInterruptMode(uint8 intSrc) ;
    void BlueTooth_WriteTxData(uint8 txDataByte) ;
    uint8 BlueTooth_ReadTxStatus(void) ;
    void BlueTooth_PutChar(uint8 txDataByte) ;
    void BlueTooth_PutString(const char8 string[]) ;
    void BlueTooth_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void BlueTooth_PutCRLF(uint8 txDataByte) ;
    void BlueTooth_ClearTxBuffer(void) ;
    void BlueTooth_SetTxAddressMode(uint8 addressMode) ;
    void BlueTooth_SendBreak(uint8 retMode) ;
    uint8 BlueTooth_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define BlueTooth_PutStringConst         BlueTooth_PutString
    #define BlueTooth_PutArrayConst          BlueTooth_PutArray
    #define BlueTooth_GetTxInterruptSource   BlueTooth_ReadTxStatus

#endif /* End BlueTooth_TX_ENABLED || BlueTooth_HD_ENABLED */

#if(BlueTooth_HD_ENABLED)
    void BlueTooth_LoadRxConfig(void) ;
    void BlueTooth_LoadTxConfig(void) ;
#endif /* End BlueTooth_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BlueTooth) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    BlueTooth_CyBtldrCommStart(void) CYSMALL ;
    void    BlueTooth_CyBtldrCommStop(void) CYSMALL ;
    void    BlueTooth_CyBtldrCommReset(void) CYSMALL ;
    cystatus BlueTooth_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus BlueTooth_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BlueTooth)
        #define CyBtldrCommStart    BlueTooth_CyBtldrCommStart
        #define CyBtldrCommStop     BlueTooth_CyBtldrCommStop
        #define CyBtldrCommReset    BlueTooth_CyBtldrCommReset
        #define CyBtldrCommWrite    BlueTooth_CyBtldrCommWrite
        #define CyBtldrCommRead     BlueTooth_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BlueTooth) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define BlueTooth_BYTE2BYTE_TIME_OUT (25u)
    #define BlueTooth_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define BlueTooth_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define BlueTooth_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define BlueTooth_SET_SPACE      (0x00u)
#define BlueTooth_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (BlueTooth_TX_ENABLED) || (BlueTooth_HD_ENABLED) )
    #if(BlueTooth_TX_INTERRUPT_ENABLED)
        #define BlueTooth_TX_VECT_NUM            (uint8)BlueTooth_TXInternalInterrupt__INTC_NUMBER
        #define BlueTooth_TX_PRIOR_NUM           (uint8)BlueTooth_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BlueTooth_TX_INTERRUPT_ENABLED */

    #define BlueTooth_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define BlueTooth_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define BlueTooth_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(BlueTooth_TX_ENABLED)
        #define BlueTooth_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (BlueTooth_HD_ENABLED) */
        #define BlueTooth_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (BlueTooth_TX_ENABLED) */

    #define BlueTooth_TX_STS_COMPLETE            (uint8)(0x01u << BlueTooth_TX_STS_COMPLETE_SHIFT)
    #define BlueTooth_TX_STS_FIFO_EMPTY          (uint8)(0x01u << BlueTooth_TX_STS_FIFO_EMPTY_SHIFT)
    #define BlueTooth_TX_STS_FIFO_FULL           (uint8)(0x01u << BlueTooth_TX_STS_FIFO_FULL_SHIFT)
    #define BlueTooth_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << BlueTooth_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (BlueTooth_TX_ENABLED) || (BlueTooth_HD_ENABLED)*/

#if( (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) )
    #if(BlueTooth_RX_INTERRUPT_ENABLED)
        #define BlueTooth_RX_VECT_NUM            (uint8)BlueTooth_RXInternalInterrupt__INTC_NUMBER
        #define BlueTooth_RX_PRIOR_NUM           (uint8)BlueTooth_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BlueTooth_RX_INTERRUPT_ENABLED */
    #define BlueTooth_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define BlueTooth_RX_STS_BREAK_SHIFT             (0x01u)
    #define BlueTooth_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define BlueTooth_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define BlueTooth_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define BlueTooth_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define BlueTooth_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define BlueTooth_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define BlueTooth_RX_STS_MRKSPC           (uint8)(0x01u << BlueTooth_RX_STS_MRKSPC_SHIFT)
    #define BlueTooth_RX_STS_BREAK            (uint8)(0x01u << BlueTooth_RX_STS_BREAK_SHIFT)
    #define BlueTooth_RX_STS_PAR_ERROR        (uint8)(0x01u << BlueTooth_RX_STS_PAR_ERROR_SHIFT)
    #define BlueTooth_RX_STS_STOP_ERROR       (uint8)(0x01u << BlueTooth_RX_STS_STOP_ERROR_SHIFT)
    #define BlueTooth_RX_STS_OVERRUN          (uint8)(0x01u << BlueTooth_RX_STS_OVERRUN_SHIFT)
    #define BlueTooth_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << BlueTooth_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define BlueTooth_RX_STS_ADDR_MATCH       (uint8)(0x01u << BlueTooth_RX_STS_ADDR_MATCH_SHIFT)
    #define BlueTooth_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << BlueTooth_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define BlueTooth_RX_HW_MASK                     (0x7Fu)
#endif /* End (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) */

/* Control Register definitions */
#define BlueTooth_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define BlueTooth_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define BlueTooth_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define BlueTooth_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define BlueTooth_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define BlueTooth_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define BlueTooth_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define BlueTooth_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define BlueTooth_CTRL_HD_SEND               (uint8)(0x01u << BlueTooth_CTRL_HD_SEND_SHIFT)
#define BlueTooth_CTRL_HD_SEND_BREAK         (uint8)(0x01u << BlueTooth_CTRL_HD_SEND_BREAK_SHIFT)
#define BlueTooth_CTRL_MARK                  (uint8)(0x01u << BlueTooth_CTRL_MARK_SHIFT)
#define BlueTooth_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << BlueTooth_CTRL_PARITY_TYPE0_SHIFT)
#define BlueTooth_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << BlueTooth_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define BlueTooth_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define BlueTooth_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define BlueTooth_SEND_BREAK                         (0x00u)
#define BlueTooth_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define BlueTooth_REINIT                             (0x02u)
#define BlueTooth_SEND_WAIT_REINIT                   (0x03u)

#define BlueTooth_OVER_SAMPLE_8                      (8u)
#define BlueTooth_OVER_SAMPLE_16                     (16u)

#define BlueTooth_BIT_CENTER                         (BlueTooth_OVER_SAMPLE_COUNT - 2u)

#define BlueTooth_FIFO_LENGTH                        (4u)
#define BlueTooth_NUMBER_OF_START_BIT                (1u)
#define BlueTooth_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define BlueTooth_TXBITCTR_BREAKBITS8X   ((BlueTooth_BREAK_BITS_TX * BlueTooth_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define BlueTooth_TXBITCTR_BREAKBITS ((BlueTooth_BREAK_BITS_TX * BlueTooth_OVER_SAMPLE_COUNT) - 1u)

#define BlueTooth_HALF_BIT_COUNT   \
                            (((BlueTooth_OVER_SAMPLE_COUNT / 2u) + (BlueTooth_USE23POLLING * 1u)) - 2u)
#if (BlueTooth_OVER_SAMPLE_COUNT == BlueTooth_OVER_SAMPLE_8)
    #define BlueTooth_HD_TXBITCTR_INIT   (((BlueTooth_BREAK_BITS_TX + \
                            BlueTooth_NUMBER_OF_START_BIT) * BlueTooth_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define BlueTooth_RXBITCTR_INIT  ((((BlueTooth_BREAK_BITS_RX + BlueTooth_NUMBER_OF_START_BIT) \
                            * BlueTooth_OVER_SAMPLE_COUNT) + BlueTooth_HALF_BIT_COUNT) - 1u)

#else /* BlueTooth_OVER_SAMPLE_COUNT == BlueTooth_OVER_SAMPLE_16 */
    #define BlueTooth_HD_TXBITCTR_INIT   ((8u * BlueTooth_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define BlueTooth_RXBITCTR_INIT      (((7u * BlueTooth_OVER_SAMPLE_COUNT) - 1u) + \
                                                      BlueTooth_HALF_BIT_COUNT)
#endif /* End BlueTooth_OVER_SAMPLE_COUNT */

#define BlueTooth_HD_RXBITCTR_INIT                   BlueTooth_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 BlueTooth_initVar;
#if (BlueTooth_TX_INTERRUPT_ENABLED && BlueTooth_TX_ENABLED)
    extern volatile uint8 BlueTooth_txBuffer[BlueTooth_TX_BUFFER_SIZE];
    extern volatile uint8 BlueTooth_txBufferRead;
    extern uint8 BlueTooth_txBufferWrite;
#endif /* (BlueTooth_TX_INTERRUPT_ENABLED && BlueTooth_TX_ENABLED) */
#if (BlueTooth_RX_INTERRUPT_ENABLED && (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED))
    extern uint8 BlueTooth_errorStatus;
    extern volatile uint8 BlueTooth_rxBuffer[BlueTooth_RX_BUFFER_SIZE];
    extern volatile uint8 BlueTooth_rxBufferRead;
    extern volatile uint8 BlueTooth_rxBufferWrite;
    extern volatile uint8 BlueTooth_rxBufferLoopDetect;
    extern volatile uint8 BlueTooth_rxBufferOverflow;
    #if (BlueTooth_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 BlueTooth_rxAddressMode;
        extern volatile uint8 BlueTooth_rxAddressDetected;
    #endif /* (BlueTooth_RXHW_ADDRESS_ENABLED) */
#endif /* (BlueTooth_RX_INTERRUPT_ENABLED && (BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define BlueTooth__B_UART__AM_SW_BYTE_BYTE 1
#define BlueTooth__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define BlueTooth__B_UART__AM_HW_BYTE_BY_BYTE 3
#define BlueTooth__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define BlueTooth__B_UART__AM_NONE 0

#define BlueTooth__B_UART__NONE_REVB 0
#define BlueTooth__B_UART__EVEN_REVB 1
#define BlueTooth__B_UART__ODD_REVB 2
#define BlueTooth__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define BlueTooth_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define BlueTooth_NUMBER_OF_STOP_BITS    (1u)

#if (BlueTooth_RXHW_ADDRESS_ENABLED)
    #define BlueTooth_RX_ADDRESS_MODE    (0u)
    #define BlueTooth_RX_HW_ADDRESS1     (0u)
    #define BlueTooth_RX_HW_ADDRESS2     (0u)
#endif /* (BlueTooth_RXHW_ADDRESS_ENABLED) */

#define BlueTooth_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << BlueTooth_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << BlueTooth_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << BlueTooth_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << BlueTooth_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << BlueTooth_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << BlueTooth_RX_STS_BREAK_SHIFT) \
                                        | (0 << BlueTooth_RX_STS_OVERRUN_SHIFT))

#define BlueTooth_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << BlueTooth_TX_STS_COMPLETE_SHIFT) \
                                        | (1 << BlueTooth_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << BlueTooth_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << BlueTooth_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BlueTooth_CONTROL_REG \
                            (* (reg8 *) BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define BlueTooth_CONTROL_PTR \
                            (  (reg8 *) BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BlueTooth_TX_ENABLED)
    #define BlueTooth_TXDATA_REG          (* (reg8 *) BlueTooth_BUART_sTX_TxShifter_u0__F0_REG)
    #define BlueTooth_TXDATA_PTR          (  (reg8 *) BlueTooth_BUART_sTX_TxShifter_u0__F0_REG)
    #define BlueTooth_TXDATA_AUX_CTL_REG  (* (reg8 *) BlueTooth_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BlueTooth_TXDATA_AUX_CTL_PTR  (  (reg8 *) BlueTooth_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BlueTooth_TXSTATUS_REG        (* (reg8 *) BlueTooth_BUART_sTX_TxSts__STATUS_REG)
    #define BlueTooth_TXSTATUS_PTR        (  (reg8 *) BlueTooth_BUART_sTX_TxSts__STATUS_REG)
    #define BlueTooth_TXSTATUS_MASK_REG   (* (reg8 *) BlueTooth_BUART_sTX_TxSts__MASK_REG)
    #define BlueTooth_TXSTATUS_MASK_PTR   (  (reg8 *) BlueTooth_BUART_sTX_TxSts__MASK_REG)
    #define BlueTooth_TXSTATUS_ACTL_REG   (* (reg8 *) BlueTooth_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define BlueTooth_TXSTATUS_ACTL_PTR   (  (reg8 *) BlueTooth_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(BlueTooth_TXCLKGEN_DP)
        #define BlueTooth_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BlueTooth_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BlueTooth_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define BlueTooth_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define BlueTooth_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BlueTooth_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BlueTooth_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BlueTooth_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BlueTooth_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define BlueTooth_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) BlueTooth_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* BlueTooth_TXCLKGEN_DP */

#endif /* End BlueTooth_TX_ENABLED */

#if(BlueTooth_HD_ENABLED)

    #define BlueTooth_TXDATA_REG             (* (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__F1_REG )
    #define BlueTooth_TXDATA_PTR             (  (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__F1_REG )
    #define BlueTooth_TXDATA_AUX_CTL_REG     (* (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define BlueTooth_TXDATA_AUX_CTL_PTR     (  (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BlueTooth_TXSTATUS_REG           (* (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_REG )
    #define BlueTooth_TXSTATUS_PTR           (  (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_REG )
    #define BlueTooth_TXSTATUS_MASK_REG      (* (reg8 *) BlueTooth_BUART_sRX_RxSts__MASK_REG )
    #define BlueTooth_TXSTATUS_MASK_PTR      (  (reg8 *) BlueTooth_BUART_sRX_RxSts__MASK_REG )
    #define BlueTooth_TXSTATUS_ACTL_REG      (* (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BlueTooth_TXSTATUS_ACTL_PTR      (  (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End BlueTooth_HD_ENABLED */

#if( (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) )
    #define BlueTooth_RXDATA_REG             (* (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__F0_REG )
    #define BlueTooth_RXDATA_PTR             (  (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__F0_REG )
    #define BlueTooth_RXADDRESS1_REG         (* (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__D0_REG )
    #define BlueTooth_RXADDRESS1_PTR         (  (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__D0_REG )
    #define BlueTooth_RXADDRESS2_REG         (* (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__D1_REG )
    #define BlueTooth_RXADDRESS2_PTR         (  (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__D1_REG )
    #define BlueTooth_RXDATA_AUX_CTL_REG     (* (reg8 *) BlueTooth_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BlueTooth_RXBITCTR_PERIOD_REG    (* (reg8 *) BlueTooth_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BlueTooth_RXBITCTR_PERIOD_PTR    (  (reg8 *) BlueTooth_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BlueTooth_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BlueTooth_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BlueTooth_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BlueTooth_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BlueTooth_RXBITCTR_COUNTER_REG   (* (reg8 *) BlueTooth_BUART_sRX_RxBitCounter__COUNT_REG )
    #define BlueTooth_RXBITCTR_COUNTER_PTR   (  (reg8 *) BlueTooth_BUART_sRX_RxBitCounter__COUNT_REG )

    #define BlueTooth_RXSTATUS_REG           (* (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_REG )
    #define BlueTooth_RXSTATUS_PTR           (  (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_REG )
    #define BlueTooth_RXSTATUS_MASK_REG      (* (reg8 *) BlueTooth_BUART_sRX_RxSts__MASK_REG )
    #define BlueTooth_RXSTATUS_MASK_PTR      (  (reg8 *) BlueTooth_BUART_sRX_RxSts__MASK_REG )
    #define BlueTooth_RXSTATUS_ACTL_REG      (* (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BlueTooth_RXSTATUS_ACTL_PTR      (  (reg8 *) BlueTooth_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) */

#if(BlueTooth_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define BlueTooth_INTCLOCK_CLKEN_REG     (* (reg8 *) BlueTooth_IntClock__PM_ACT_CFG)
    #define BlueTooth_INTCLOCK_CLKEN_PTR     (  (reg8 *) BlueTooth_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define BlueTooth_INTCLOCK_CLKEN_MASK    BlueTooth_IntClock__PM_ACT_MSK
#endif /* End BlueTooth_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(BlueTooth_TX_ENABLED)
    #define BlueTooth_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End BlueTooth_TX_ENABLED */

#if(BlueTooth_HD_ENABLED)
    #define BlueTooth_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End BlueTooth_HD_ENABLED */

#if( (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) )
    #define BlueTooth_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define BlueTooth_WAIT_1_MS      BlueTooth_BL_CHK_DELAY_MS   

#define BlueTooth_TXBUFFERSIZE   BlueTooth_TX_BUFFER_SIZE
#define BlueTooth_RXBUFFERSIZE   BlueTooth_RX_BUFFER_SIZE

#if (BlueTooth_RXHW_ADDRESS_ENABLED)
    #define BlueTooth_RXADDRESSMODE  BlueTooth_RX_ADDRESS_MODE
    #define BlueTooth_RXHWADDRESS1   BlueTooth_RX_HW_ADDRESS1
    #define BlueTooth_RXHWADDRESS2   BlueTooth_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define BlueTooth_RXAddressMode  BlueTooth_RXADDRESSMODE
#endif /* (BlueTooth_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define BlueTooth_initvar                    BlueTooth_initVar

#define BlueTooth_RX_Enabled                 BlueTooth_RX_ENABLED
#define BlueTooth_TX_Enabled                 BlueTooth_TX_ENABLED
#define BlueTooth_HD_Enabled                 BlueTooth_HD_ENABLED
#define BlueTooth_RX_IntInterruptEnabled     BlueTooth_RX_INTERRUPT_ENABLED
#define BlueTooth_TX_IntInterruptEnabled     BlueTooth_TX_INTERRUPT_ENABLED
#define BlueTooth_InternalClockUsed          BlueTooth_INTERNAL_CLOCK_USED
#define BlueTooth_RXHW_Address_Enabled       BlueTooth_RXHW_ADDRESS_ENABLED
#define BlueTooth_OverSampleCount            BlueTooth_OVER_SAMPLE_COUNT
#define BlueTooth_ParityType                 BlueTooth_PARITY_TYPE

#if( BlueTooth_TX_ENABLED && (BlueTooth_TXBUFFERSIZE > BlueTooth_FIFO_LENGTH))
    #define BlueTooth_TXBUFFER               BlueTooth_txBuffer
    #define BlueTooth_TXBUFFERREAD           BlueTooth_txBufferRead
    #define BlueTooth_TXBUFFERWRITE          BlueTooth_txBufferWrite
#endif /* End BlueTooth_TX_ENABLED */
#if( ( BlueTooth_RX_ENABLED || BlueTooth_HD_ENABLED ) && \
     (BlueTooth_RXBUFFERSIZE > BlueTooth_FIFO_LENGTH) )
    #define BlueTooth_RXBUFFER               BlueTooth_rxBuffer
    #define BlueTooth_RXBUFFERREAD           BlueTooth_rxBufferRead
    #define BlueTooth_RXBUFFERWRITE          BlueTooth_rxBufferWrite
    #define BlueTooth_RXBUFFERLOOPDETECT     BlueTooth_rxBufferLoopDetect
    #define BlueTooth_RXBUFFER_OVERFLOW      BlueTooth_rxBufferOverflow
#endif /* End BlueTooth_RX_ENABLED */

#ifdef BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BlueTooth_CONTROL                BlueTooth_CONTROL_REG
#endif /* End BlueTooth_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BlueTooth_TX_ENABLED)
    #define BlueTooth_TXDATA                 BlueTooth_TXDATA_REG
    #define BlueTooth_TXSTATUS               BlueTooth_TXSTATUS_REG
    #define BlueTooth_TXSTATUS_MASK          BlueTooth_TXSTATUS_MASK_REG
    #define BlueTooth_TXSTATUS_ACTL          BlueTooth_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(BlueTooth_TXCLKGEN_DP)
        #define BlueTooth_TXBITCLKGEN_CTR        BlueTooth_TXBITCLKGEN_CTR_REG
        #define BlueTooth_TXBITCLKTX_COMPLETE    BlueTooth_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define BlueTooth_TXBITCTR_PERIOD        BlueTooth_TXBITCTR_PERIOD_REG
        #define BlueTooth_TXBITCTR_CONTROL       BlueTooth_TXBITCTR_CONTROL_REG
        #define BlueTooth_TXBITCTR_COUNTER       BlueTooth_TXBITCTR_COUNTER_REG
    #endif /* BlueTooth_TXCLKGEN_DP */
#endif /* End BlueTooth_TX_ENABLED */

#if(BlueTooth_HD_ENABLED)
    #define BlueTooth_TXDATA                 BlueTooth_TXDATA_REG
    #define BlueTooth_TXSTATUS               BlueTooth_TXSTATUS_REG
    #define BlueTooth_TXSTATUS_MASK          BlueTooth_TXSTATUS_MASK_REG
    #define BlueTooth_TXSTATUS_ACTL          BlueTooth_TXSTATUS_ACTL_REG
#endif /* End BlueTooth_HD_ENABLED */

#if( (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) )
    #define BlueTooth_RXDATA                 BlueTooth_RXDATA_REG
    #define BlueTooth_RXADDRESS1             BlueTooth_RXADDRESS1_REG
    #define BlueTooth_RXADDRESS2             BlueTooth_RXADDRESS2_REG
    #define BlueTooth_RXBITCTR_PERIOD        BlueTooth_RXBITCTR_PERIOD_REG
    #define BlueTooth_RXBITCTR_CONTROL       BlueTooth_RXBITCTR_CONTROL_REG
    #define BlueTooth_RXBITCTR_COUNTER       BlueTooth_RXBITCTR_COUNTER_REG
    #define BlueTooth_RXSTATUS               BlueTooth_RXSTATUS_REG
    #define BlueTooth_RXSTATUS_MASK          BlueTooth_RXSTATUS_MASK_REG
    #define BlueTooth_RXSTATUS_ACTL          BlueTooth_RXSTATUS_ACTL_REG
#endif /* End  (BlueTooth_RX_ENABLED) || (BlueTooth_HD_ENABLED) */

#if(BlueTooth_INTERNAL_CLOCK_USED)
    #define BlueTooth_INTCLOCK_CLKEN         BlueTooth_INTCLOCK_CLKEN_REG
#endif /* End BlueTooth_INTERNAL_CLOCK_USED */

#define BlueTooth_WAIT_FOR_COMLETE_REINIT    BlueTooth_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_BlueTooth_H */


/* [] END OF FILE */
