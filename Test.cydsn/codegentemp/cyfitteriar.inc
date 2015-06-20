#ifndef INCLUDED_CYFITTERIAR_INC
#define INCLUDED_CYFITTERIAR_INC
    INCLUDE cydeviceiar.inc
    INCLUDE cydeviceiar_trm.inc

/* EN_A */
EN_A__0__MASK EQU 0x20
EN_A__0__PC EQU CYREG_PRT12_PC5
EN_A__0__PORT EQU 12
EN_A__0__SHIFT EQU 5
EN_A__AG EQU CYREG_PRT12_AG
EN_A__BIE EQU CYREG_PRT12_BIE
EN_A__BIT_MASK EQU CYREG_PRT12_BIT_MASK
EN_A__BYP EQU CYREG_PRT12_BYP
EN_A__DM0 EQU CYREG_PRT12_DM0
EN_A__DM1 EQU CYREG_PRT12_DM1
EN_A__DM2 EQU CYREG_PRT12_DM2
EN_A__DR EQU CYREG_PRT12_DR
EN_A__INP_DIS EQU CYREG_PRT12_INP_DIS
EN_A__MASK EQU 0x20
EN_A__PORT EQU 12
EN_A__PRT EQU CYREG_PRT12_PRT
EN_A__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
EN_A__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
EN_A__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
EN_A__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
EN_A__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
EN_A__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
EN_A__PS EQU CYREG_PRT12_PS
EN_A__SHIFT EQU 5
EN_A__SIO_CFG EQU CYREG_PRT12_SIO_CFG
EN_A__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
EN_A__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
EN_A__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
EN_A__SLW EQU CYREG_PRT12_SLW

/* EN_A_PWM_PWMUDB */
EN_A_PWM_PWMUDB_genblk8_stsreg__0__MASK EQU 0x01
EN_A_PWM_PWMUDB_genblk8_stsreg__0__POS EQU 0
EN_A_PWM_PWMUDB_genblk8_stsreg__2__MASK EQU 0x04
EN_A_PWM_PWMUDB_genblk8_stsreg__2__POS EQU 2
EN_A_PWM_PWMUDB_genblk8_stsreg__3__MASK EQU 0x08
EN_A_PWM_PWMUDB_genblk8_stsreg__3__POS EQU 3
EN_A_PWM_PWMUDB_genblk8_stsreg__MASK EQU 0x0D
EN_A_PWM_PWMUDB_genblk8_stsreg__MASK_REG EQU CYREG_B0_UDB15_MSK
EN_A_PWM_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB15_MSK_ACTL
EN_A_PWM_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB15_MSK_ACTL
EN_A_PWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB15_ACTL
EN_A_PWM_PWMUDB_genblk8_stsreg__STATUS_CNT_REG EQU CYREG_B0_UDB15_ST_CTL
EN_A_PWM_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG EQU CYREG_B0_UDB15_ST_CTL
EN_A_PWM_PWMUDB_genblk8_stsreg__STATUS_REG EQU CYREG_B0_UDB15_ST
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB14_15_A0
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB14_15_A1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB14_15_D0
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB14_15_D1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB14_15_ACTL
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB14_15_F0
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB14_15_F1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__A0_A1_REG EQU CYREG_B0_UDB14_A0_A1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__A0_REG EQU CYREG_B0_UDB14_A0
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG EQU CYREG_B0_UDB14_A1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__D0_D1_REG EQU CYREG_B0_UDB14_D0_D1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__D0_REG EQU CYREG_B0_UDB14_D0
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG EQU CYREG_B0_UDB14_D1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB14_ACTL
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__F0_F1_REG EQU CYREG_B0_UDB14_F0_F1
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__F0_REG EQU CYREG_B0_UDB14_F0
EN_A_PWM_PWMUDB_sP16_pwmdp_u0__F1_REG EQU CYREG_B0_UDB14_F1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__A0_A1_REG EQU CYREG_B0_UDB15_A0_A1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__A0_REG EQU CYREG_B0_UDB15_A0
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__A1_REG EQU CYREG_B0_UDB15_A1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__D0_D1_REG EQU CYREG_B0_UDB15_D0_D1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__D0_REG EQU CYREG_B0_UDB15_D0
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__D1_REG EQU CYREG_B0_UDB15_D1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG EQU CYREG_B0_UDB15_ACTL
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__F0_F1_REG EQU CYREG_B0_UDB15_F0_F1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__F0_REG EQU CYREG_B0_UDB15_F0
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__F1_REG EQU CYREG_B0_UDB15_F1
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB15_MSK_ACTL
EN_A_PWM_PWMUDB_sP16_pwmdp_u1__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB15_MSK_ACTL

/* EN_B */
EN_B__0__MASK EQU 0x10
EN_B__0__PC EQU CYREG_PRT6_PC4
EN_B__0__PORT EQU 6
EN_B__0__SHIFT EQU 4
EN_B__AG EQU CYREG_PRT6_AG
EN_B__AMUX EQU CYREG_PRT6_AMUX
EN_B__BIE EQU CYREG_PRT6_BIE
EN_B__BIT_MASK EQU CYREG_PRT6_BIT_MASK
EN_B__BYP EQU CYREG_PRT6_BYP
EN_B__CTL EQU CYREG_PRT6_CTL
EN_B__DM0 EQU CYREG_PRT6_DM0
EN_B__DM1 EQU CYREG_PRT6_DM1
EN_B__DM2 EQU CYREG_PRT6_DM2
EN_B__DR EQU CYREG_PRT6_DR
EN_B__INP_DIS EQU CYREG_PRT6_INP_DIS
EN_B__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
EN_B__LCD_EN EQU CYREG_PRT6_LCD_EN
EN_B__MASK EQU 0x10
EN_B__PORT EQU 6
EN_B__PRT EQU CYREG_PRT6_PRT
EN_B__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
EN_B__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
EN_B__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
EN_B__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
EN_B__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
EN_B__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
EN_B__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
EN_B__PS EQU CYREG_PRT6_PS
EN_B__SHIFT EQU 4
EN_B__SLW EQU CYREG_PRT6_SLW

/* EN_B_PWM_PWMUDB */
EN_B_PWM_PWMUDB_genblk8_stsreg__0__MASK EQU 0x01
EN_B_PWM_PWMUDB_genblk8_stsreg__0__POS EQU 0
EN_B_PWM_PWMUDB_genblk8_stsreg__16BIT_STATUS_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
EN_B_PWM_PWMUDB_genblk8_stsreg__16BIT_STATUS_REG EQU CYREG_B0_UDB13_14_ST
EN_B_PWM_PWMUDB_genblk8_stsreg__2__MASK EQU 0x04
EN_B_PWM_PWMUDB_genblk8_stsreg__2__POS EQU 2
EN_B_PWM_PWMUDB_genblk8_stsreg__3__MASK EQU 0x08
EN_B_PWM_PWMUDB_genblk8_stsreg__3__POS EQU 3
EN_B_PWM_PWMUDB_genblk8_stsreg__MASK EQU 0x0D
EN_B_PWM_PWMUDB_genblk8_stsreg__MASK_REG EQU CYREG_B0_UDB13_MSK
EN_B_PWM_PWMUDB_genblk8_stsreg__MASK_ST_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
EN_B_PWM_PWMUDB_genblk8_stsreg__PER_ST_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
EN_B_PWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
EN_B_PWM_PWMUDB_genblk8_stsreg__STATUS_CNT_REG EQU CYREG_B0_UDB13_ST_CTL
EN_B_PWM_PWMUDB_genblk8_stsreg__STATUS_CONTROL_REG EQU CYREG_B0_UDB13_ST_CTL
EN_B_PWM_PWMUDB_genblk8_stsreg__STATUS_REG EQU CYREG_B0_UDB13_ST
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG EQU CYREG_B0_UDB12_13_A0
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG EQU CYREG_B0_UDB12_13_A1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG EQU CYREG_B0_UDB12_13_D0
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG EQU CYREG_B0_UDB12_13_D1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB12_13_ACTL
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG EQU CYREG_B0_UDB12_13_F0
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG EQU CYREG_B0_UDB12_13_F1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__A0_A1_REG EQU CYREG_B0_UDB12_A0_A1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__A0_REG EQU CYREG_B0_UDB12_A0
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__A1_REG EQU CYREG_B0_UDB12_A1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__D0_D1_REG EQU CYREG_B0_UDB12_D0_D1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__D0_REG EQU CYREG_B0_UDB12_D0
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__D1_REG EQU CYREG_B0_UDB12_D1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG EQU CYREG_B0_UDB12_ACTL
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__F0_F1_REG EQU CYREG_B0_UDB12_F0_F1
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__F0_REG EQU CYREG_B0_UDB12_F0
EN_B_PWM_PWMUDB_sP16_pwmdp_u0__F1_REG EQU CYREG_B0_UDB12_F1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_A0_REG EQU CYREG_B0_UDB13_14_A0
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_A1_REG EQU CYREG_B0_UDB13_14_A1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_D0_REG EQU CYREG_B0_UDB13_14_D0
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_D1_REG EQU CYREG_B0_UDB13_14_D1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_F0_REG EQU CYREG_B0_UDB13_14_F0
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__16BIT_F1_REG EQU CYREG_B0_UDB13_14_F1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__A0_A1_REG EQU CYREG_B0_UDB13_A0_A1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__A0_REG EQU CYREG_B0_UDB13_A0
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__A1_REG EQU CYREG_B0_UDB13_A1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__D0_D1_REG EQU CYREG_B0_UDB13_D0_D1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__D0_REG EQU CYREG_B0_UDB13_D0
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__D1_REG EQU CYREG_B0_UDB13_D1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__F0_F1_REG EQU CYREG_B0_UDB13_F0_F1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__F0_REG EQU CYREG_B0_UDB13_F0
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__F1_REG EQU CYREG_B0_UDB13_F1
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__MSK_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
EN_B_PWM_PWMUDB_sP16_pwmdp_u1__PER_DP_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL

/* IN_1 */
IN_1__0__MASK EQU 0x10
IN_1__0__PC EQU CYREG_PRT12_PC4
IN_1__0__PORT EQU 12
IN_1__0__SHIFT EQU 4
IN_1__AG EQU CYREG_PRT12_AG
IN_1__BIE EQU CYREG_PRT12_BIE
IN_1__BIT_MASK EQU CYREG_PRT12_BIT_MASK
IN_1__BYP EQU CYREG_PRT12_BYP
IN_1__DM0 EQU CYREG_PRT12_DM0
IN_1__DM1 EQU CYREG_PRT12_DM1
IN_1__DM2 EQU CYREG_PRT12_DM2
IN_1__DR EQU CYREG_PRT12_DR
IN_1__INP_DIS EQU CYREG_PRT12_INP_DIS
IN_1__MASK EQU 0x10
IN_1__PORT EQU 12
IN_1__PRT EQU CYREG_PRT12_PRT
IN_1__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT12_DBL_SYNC_IN
IN_1__PRTDSI__OE_SEL0 EQU CYREG_PRT12_OE_SEL0
IN_1__PRTDSI__OE_SEL1 EQU CYREG_PRT12_OE_SEL1
IN_1__PRTDSI__OUT_SEL0 EQU CYREG_PRT12_OUT_SEL0
IN_1__PRTDSI__OUT_SEL1 EQU CYREG_PRT12_OUT_SEL1
IN_1__PRTDSI__SYNC_OUT EQU CYREG_PRT12_SYNC_OUT
IN_1__PS EQU CYREG_PRT12_PS
IN_1__SHIFT EQU 4
IN_1__SIO_CFG EQU CYREG_PRT12_SIO_CFG
IN_1__SIO_DIFF EQU CYREG_PRT12_SIO_DIFF
IN_1__SIO_HYST_EN EQU CYREG_PRT12_SIO_HYST_EN
IN_1__SIO_REG_HIFREQ EQU CYREG_PRT12_SIO_REG_HIFREQ
IN_1__SLW EQU CYREG_PRT12_SLW

/* IN_2 */
IN_2__0__MASK EQU 0x20
IN_2__0__PC EQU CYREG_PRT6_PC5
IN_2__0__PORT EQU 6
IN_2__0__SHIFT EQU 5
IN_2__AG EQU CYREG_PRT6_AG
IN_2__AMUX EQU CYREG_PRT6_AMUX
IN_2__BIE EQU CYREG_PRT6_BIE
IN_2__BIT_MASK EQU CYREG_PRT6_BIT_MASK
IN_2__BYP EQU CYREG_PRT6_BYP
IN_2__CTL EQU CYREG_PRT6_CTL
IN_2__DM0 EQU CYREG_PRT6_DM0
IN_2__DM1 EQU CYREG_PRT6_DM1
IN_2__DM2 EQU CYREG_PRT6_DM2
IN_2__DR EQU CYREG_PRT6_DR
IN_2__INP_DIS EQU CYREG_PRT6_INP_DIS
IN_2__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
IN_2__LCD_EN EQU CYREG_PRT6_LCD_EN
IN_2__MASK EQU 0x20
IN_2__PORT EQU 6
IN_2__PRT EQU CYREG_PRT6_PRT
IN_2__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
IN_2__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
IN_2__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
IN_2__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
IN_2__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
IN_2__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
IN_2__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
IN_2__PS EQU CYREG_PRT6_PS
IN_2__SHIFT EQU 5
IN_2__SLW EQU CYREG_PRT6_SLW

/* IN_3 */
IN_3__0__MASK EQU 0x40
IN_3__0__PC EQU CYREG_PRT6_PC6
IN_3__0__PORT EQU 6
IN_3__0__SHIFT EQU 6
IN_3__AG EQU CYREG_PRT6_AG
IN_3__AMUX EQU CYREG_PRT6_AMUX
IN_3__BIE EQU CYREG_PRT6_BIE
IN_3__BIT_MASK EQU CYREG_PRT6_BIT_MASK
IN_3__BYP EQU CYREG_PRT6_BYP
IN_3__CTL EQU CYREG_PRT6_CTL
IN_3__DM0 EQU CYREG_PRT6_DM0
IN_3__DM1 EQU CYREG_PRT6_DM1
IN_3__DM2 EQU CYREG_PRT6_DM2
IN_3__DR EQU CYREG_PRT6_DR
IN_3__INP_DIS EQU CYREG_PRT6_INP_DIS
IN_3__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
IN_3__LCD_EN EQU CYREG_PRT6_LCD_EN
IN_3__MASK EQU 0x40
IN_3__PORT EQU 6
IN_3__PRT EQU CYREG_PRT6_PRT
IN_3__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
IN_3__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
IN_3__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
IN_3__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
IN_3__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
IN_3__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
IN_3__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
IN_3__PS EQU CYREG_PRT6_PS
IN_3__SHIFT EQU 6
IN_3__SLW EQU CYREG_PRT6_SLW

/* IN_4 */
IN_4__0__MASK EQU 0x80
IN_4__0__PC EQU CYREG_PRT6_PC7
IN_4__0__PORT EQU 6
IN_4__0__SHIFT EQU 7
IN_4__AG EQU CYREG_PRT6_AG
IN_4__AMUX EQU CYREG_PRT6_AMUX
IN_4__BIE EQU CYREG_PRT6_BIE
IN_4__BIT_MASK EQU CYREG_PRT6_BIT_MASK
IN_4__BYP EQU CYREG_PRT6_BYP
IN_4__CTL EQU CYREG_PRT6_CTL
IN_4__DM0 EQU CYREG_PRT6_DM0
IN_4__DM1 EQU CYREG_PRT6_DM1
IN_4__DM2 EQU CYREG_PRT6_DM2
IN_4__DR EQU CYREG_PRT6_DR
IN_4__INP_DIS EQU CYREG_PRT6_INP_DIS
IN_4__LCD_COM_SEG EQU CYREG_PRT6_LCD_COM_SEG
IN_4__LCD_EN EQU CYREG_PRT6_LCD_EN
IN_4__MASK EQU 0x80
IN_4__PORT EQU 6
IN_4__PRT EQU CYREG_PRT6_PRT
IN_4__PRTDSI__CAPS_SEL EQU CYREG_PRT6_CAPS_SEL
IN_4__PRTDSI__DBL_SYNC_IN EQU CYREG_PRT6_DBL_SYNC_IN
IN_4__PRTDSI__OE_SEL0 EQU CYREG_PRT6_OE_SEL0
IN_4__PRTDSI__OE_SEL1 EQU CYREG_PRT6_OE_SEL1
IN_4__PRTDSI__OUT_SEL0 EQU CYREG_PRT6_OUT_SEL0
IN_4__PRTDSI__OUT_SEL1 EQU CYREG_PRT6_OUT_SEL1
IN_4__PRTDSI__SYNC_OUT EQU CYREG_PRT6_SYNC_OUT
IN_4__PS EQU CYREG_PRT6_PS
IN_4__SHIFT EQU 7
IN_4__SLW EQU CYREG_PRT6_SLW

/* Clock_2 */
Clock_2__CFG0 EQU CYREG_CLKDIST_DCFG0_CFG0
Clock_2__CFG1 EQU CYREG_CLKDIST_DCFG0_CFG1
Clock_2__CFG2 EQU CYREG_CLKDIST_DCFG0_CFG2
Clock_2__CFG2_SRC_SEL_MASK EQU 0x07
Clock_2__INDEX EQU 0x00
Clock_2__PM_ACT_CFG EQU CYREG_PM_ACT_CFG2
Clock_2__PM_ACT_MSK EQU 0x01
Clock_2__PM_STBY_CFG EQU CYREG_PM_STBY_CFG2
Clock_2__PM_STBY_MSK EQU 0x01

/* Motor_A */
Motor_A_Sync_ctrl_reg__0__MASK EQU 0x01
Motor_A_Sync_ctrl_reg__0__POS EQU 0
Motor_A_Sync_ctrl_reg__1__MASK EQU 0x02
Motor_A_Sync_ctrl_reg__1__POS EQU 1
Motor_A_Sync_ctrl_reg__2__MASK EQU 0x04
Motor_A_Sync_ctrl_reg__2__POS EQU 2
Motor_A_Sync_ctrl_reg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB15_ACTL
Motor_A_Sync_ctrl_reg__CONTROL_REG EQU CYREG_B0_UDB15_CTL
Motor_A_Sync_ctrl_reg__CONTROL_ST_REG EQU CYREG_B0_UDB15_ST_CTL
Motor_A_Sync_ctrl_reg__COUNT_REG EQU CYREG_B0_UDB15_CTL
Motor_A_Sync_ctrl_reg__COUNT_ST_REG EQU CYREG_B0_UDB15_ST_CTL
Motor_A_Sync_ctrl_reg__MASK EQU 0x07
Motor_A_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB15_MSK_ACTL
Motor_A_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB15_MSK_ACTL
Motor_A_Sync_ctrl_reg__PERIOD_REG EQU CYREG_B0_UDB15_MSK

/* Motor_B */
Motor_B_Sync_ctrl_reg__0__MASK EQU 0x01
Motor_B_Sync_ctrl_reg__0__POS EQU 0
Motor_B_Sync_ctrl_reg__1__MASK EQU 0x02
Motor_B_Sync_ctrl_reg__1__POS EQU 1
Motor_B_Sync_ctrl_reg__16BIT_CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB13_14_ACTL
Motor_B_Sync_ctrl_reg__16BIT_CONTROL_CONTROL_REG EQU CYREG_B0_UDB13_14_CTL
Motor_B_Sync_ctrl_reg__16BIT_CONTROL_COUNT_REG EQU CYREG_B0_UDB13_14_CTL
Motor_B_Sync_ctrl_reg__16BIT_COUNT_CONTROL_REG EQU CYREG_B0_UDB13_14_CTL
Motor_B_Sync_ctrl_reg__16BIT_COUNT_COUNT_REG EQU CYREG_B0_UDB13_14_CTL
Motor_B_Sync_ctrl_reg__16BIT_MASK_MASK_REG EQU CYREG_B0_UDB13_14_MSK
Motor_B_Sync_ctrl_reg__16BIT_MASK_PERIOD_REG EQU CYREG_B0_UDB13_14_MSK
Motor_B_Sync_ctrl_reg__16BIT_PERIOD_MASK_REG EQU CYREG_B0_UDB13_14_MSK
Motor_B_Sync_ctrl_reg__16BIT_PERIOD_PERIOD_REG EQU CYREG_B0_UDB13_14_MSK
Motor_B_Sync_ctrl_reg__2__MASK EQU 0x04
Motor_B_Sync_ctrl_reg__2__POS EQU 2
Motor_B_Sync_ctrl_reg__CONTROL_AUX_CTL_REG EQU CYREG_B0_UDB13_ACTL
Motor_B_Sync_ctrl_reg__CONTROL_REG EQU CYREG_B0_UDB13_CTL
Motor_B_Sync_ctrl_reg__CONTROL_ST_REG EQU CYREG_B0_UDB13_ST_CTL
Motor_B_Sync_ctrl_reg__COUNT_REG EQU CYREG_B0_UDB13_CTL
Motor_B_Sync_ctrl_reg__COUNT_ST_REG EQU CYREG_B0_UDB13_ST_CTL
Motor_B_Sync_ctrl_reg__MASK EQU 0x07
Motor_B_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
Motor_B_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG EQU CYREG_B0_UDB13_MSK_ACTL
Motor_B_Sync_ctrl_reg__PERIOD_REG EQU CYREG_B0_UDB13_MSK

/* Miscellaneous */
BCLK__BUS_CLK__HZ EQU 24000000
BCLK__BUS_CLK__KHZ EQU 24000
BCLK__BUS_CLK__MHZ EQU 24
CYDEV_CHIP_DIE_GEN4 EQU 2
CYDEV_CHIP_DIE_LEOPARD EQU 1
CYDEV_CHIP_DIE_PANTHER EQU 12
CYDEV_CHIP_DIE_PSOC4A EQU 5
CYDEV_CHIP_DIE_PSOC5LP EQU 11
CYDEV_CHIP_DIE_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_PSOC3 EQU 1
CYDEV_CHIP_FAMILY_PSOC4 EQU 2
CYDEV_CHIP_FAMILY_PSOC5 EQU 3
CYDEV_CHIP_FAMILY_UNKNOWN EQU 0
CYDEV_CHIP_FAMILY_USED EQU CYDEV_CHIP_FAMILY_PSOC5
CYDEV_CHIP_JTAG_ID EQU 0x2E160069
CYDEV_CHIP_MEMBER_3A EQU 1
CYDEV_CHIP_MEMBER_4A EQU 5
CYDEV_CHIP_MEMBER_4C EQU 9
CYDEV_CHIP_MEMBER_4D EQU 3
CYDEV_CHIP_MEMBER_4E EQU 4
CYDEV_CHIP_MEMBER_4F EQU 6
CYDEV_CHIP_MEMBER_4G EQU 2
CYDEV_CHIP_MEMBER_4L EQU 8
CYDEV_CHIP_MEMBER_4M EQU 7
CYDEV_CHIP_MEMBER_5A EQU 11
CYDEV_CHIP_MEMBER_5B EQU 10
CYDEV_CHIP_MEMBER_UNKNOWN EQU 0
CYDEV_CHIP_MEMBER_USED EQU CYDEV_CHIP_MEMBER_5B
CYDEV_CHIP_DIE_EXPECT EQU CYDEV_CHIP_MEMBER_USED
CYDEV_CHIP_DIE_ACTUAL EQU CYDEV_CHIP_DIE_EXPECT
CYDEV_CHIP_REV_GEN4_ES EQU 17
CYDEV_CHIP_REV_GEN4_ES2 EQU 33
CYDEV_CHIP_REV_GEN4_PRODUCTION EQU 17
CYDEV_CHIP_REV_LEOPARD_ES1 EQU 0
CYDEV_CHIP_REV_LEOPARD_ES2 EQU 1
CYDEV_CHIP_REV_LEOPARD_ES3 EQU 3
CYDEV_CHIP_REV_LEOPARD_PRODUCTION EQU 3
CYDEV_CHIP_REV_PANTHER_ES0 EQU 0
CYDEV_CHIP_REV_PANTHER_ES1 EQU 1
CYDEV_CHIP_REV_PANTHER_PRODUCTION EQU 1
CYDEV_CHIP_REV_PSOC4A_ES0 EQU 17
CYDEV_CHIP_REV_PSOC4A_PRODUCTION EQU 17
CYDEV_CHIP_REV_PSOC5LP_ES0 EQU 0
CYDEV_CHIP_REV_PSOC5LP_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_3A_ES1 EQU 0
CYDEV_CHIP_REVISION_3A_ES2 EQU 1
CYDEV_CHIP_REVISION_3A_ES3 EQU 3
CYDEV_CHIP_REVISION_3A_PRODUCTION EQU 3
CYDEV_CHIP_REVISION_4A_ES0 EQU 17
CYDEV_CHIP_REVISION_4A_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4C_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4D_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4E_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4F_PRODUCTION_256K EQU 0
CYDEV_CHIP_REVISION_4G_ES EQU 17
CYDEV_CHIP_REVISION_4G_ES2 EQU 33
CYDEV_CHIP_REVISION_4G_PRODUCTION EQU 17
CYDEV_CHIP_REVISION_4L_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_4M_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_5A_ES0 EQU 0
CYDEV_CHIP_REVISION_5A_ES1 EQU 1
CYDEV_CHIP_REVISION_5A_PRODUCTION EQU 1
CYDEV_CHIP_REVISION_5B_ES0 EQU 0
CYDEV_CHIP_REVISION_5B_PRODUCTION EQU 0
CYDEV_CHIP_REVISION_USED EQU CYDEV_CHIP_REVISION_5B_PRODUCTION
CYDEV_CHIP_REV_EXPECT EQU CYDEV_CHIP_REVISION_USED
CYDEV_CONFIG_FASTBOOT_ENABLED EQU 1
CYDEV_CONFIG_UNUSED_IO_AllowButWarn EQU 0
CYDEV_CONFIG_UNUSED_IO EQU CYDEV_CONFIG_UNUSED_IO_AllowButWarn
CYDEV_CONFIG_UNUSED_IO_AllowWithInfo EQU 1
CYDEV_CONFIG_UNUSED_IO_Disallowed EQU 2
CYDEV_CONFIGURATION_COMPRESSED EQU 1
CYDEV_CONFIGURATION_DMA EQU 0
CYDEV_CONFIGURATION_ECC EQU 1
CYDEV_CONFIGURATION_IMOENABLED EQU CYDEV_CONFIG_FASTBOOT_ENABLED
CYDEV_CONFIGURATION_MODE_COMPRESSED EQU 0
CYDEV_CONFIGURATION_MODE EQU CYDEV_CONFIGURATION_MODE_COMPRESSED
CYDEV_CONFIGURATION_MODE_DMA EQU 2
CYDEV_CONFIGURATION_MODE_UNCOMPRESSED EQU 1
CYDEV_DEBUG_ENABLE_MASK EQU 0x20
CYDEV_DEBUG_ENABLE_REGISTER EQU CYREG_MLOGIC_DEBUG
CYDEV_DEBUGGING_DPS_Disable EQU 3
CYDEV_DEBUGGING_DPS_JTAG_4 EQU 1
CYDEV_DEBUGGING_DPS_JTAG_5 EQU 0
CYDEV_DEBUGGING_DPS_SWD EQU 2
CYDEV_DEBUGGING_DPS_SWD_SWV EQU 6
CYDEV_DEBUGGING_DPS EQU CYDEV_DEBUGGING_DPS_SWD_SWV
CYDEV_DEBUGGING_ENABLE EQU 1
CYDEV_DEBUGGING_XRES EQU 0
CYDEV_DMA_CHANNELS_AVAILABLE EQU 24
CYDEV_ECC_ENABLE EQU 0
CYDEV_HEAP_SIZE EQU 0x80
CYDEV_INSTRUCT_CACHE_ENABLED EQU 1
CYDEV_INTR_RISING EQU 0x00000000
CYDEV_PROJ_TYPE EQU 0
CYDEV_PROJ_TYPE_BOOTLOADER EQU 1
CYDEV_PROJ_TYPE_LAUNCHER EQU 5
CYDEV_PROJ_TYPE_LOADABLE EQU 2
CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER EQU 4
CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER EQU 3
CYDEV_PROJ_TYPE_STANDARD EQU 0
CYDEV_PROTECTION_ENABLE EQU 0
CYDEV_STACK_SIZE EQU 0x0800
CYDEV_USE_BUNDLED_CMSIS EQU 1
CYDEV_VARIABLE_VDDA EQU 0
CYDEV_VDDA_MV EQU 5000
CYDEV_VDDD_MV EQU 5000
CYDEV_VDDIO0_MV EQU 5000
CYDEV_VDDIO1_MV EQU 5000
CYDEV_VDDIO2_MV EQU 5000
CYDEV_VDDIO3_MV EQU 5000
CYDEV_VIO0_MV EQU 5000
CYDEV_VIO1_MV EQU 5000
CYDEV_VIO2_MV EQU 5000
CYDEV_VIO3_MV EQU 5000
CYIPBLOCK_ARM_CM3_VERSION EQU 0
CYIPBLOCK_P3_ANAIF_VERSION EQU 0
CYIPBLOCK_P3_CAN_VERSION EQU 0
CYIPBLOCK_P3_CAPSENSE_VERSION EQU 0
CYIPBLOCK_P3_COMP_VERSION EQU 0
CYIPBLOCK_P3_DECIMATOR_VERSION EQU 0
CYIPBLOCK_P3_DFB_VERSION EQU 0
CYIPBLOCK_P3_DMA_VERSION EQU 0
CYIPBLOCK_P3_DRQ_VERSION EQU 0
CYIPBLOCK_P3_DSM_VERSION EQU 0
CYIPBLOCK_P3_EMIF_VERSION EQU 0
CYIPBLOCK_P3_I2C_VERSION EQU 0
CYIPBLOCK_P3_LCD_VERSION EQU 0
CYIPBLOCK_P3_LPF_VERSION EQU 0
CYIPBLOCK_P3_OPAMP_VERSION EQU 0
CYIPBLOCK_P3_PM_VERSION EQU 0
CYIPBLOCK_P3_SCCT_VERSION EQU 0
CYIPBLOCK_P3_TIMER_VERSION EQU 0
CYIPBLOCK_P3_USB_VERSION EQU 0
CYIPBLOCK_P3_VIDAC_VERSION EQU 0
CYIPBLOCK_P3_VREF_VERSION EQU 0
CYIPBLOCK_S8_GPIO_VERSION EQU 0
CYIPBLOCK_S8_IRQ_VERSION EQU 0
CYIPBLOCK_S8_SAR_VERSION EQU 0
CYIPBLOCK_S8_SIO_VERSION EQU 0
CYIPBLOCK_S8_UDB_VERSION EQU 0
DMA_CHANNELS_USED__MASK0 EQU 0x00000000
CYDEV_BOOTLOADER_ENABLE EQU 0

#endif /* INCLUDED_CYFITTERIAR_INC */