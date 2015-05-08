/******************************************************************************
* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/* Copyright (C) 2008(2010) Renesas Electronics Corporation. All rights reserved.  */
/******************************************************************************
* File Name    : rjj05b0944_src_slave.c
* Abstract     : Clock Synchronous Serial I/O with Chip Select (SSU)
* Version      : Ver 1.01
* Device       : R5F212D7SNFP(R8C/2D Group)
* Tool-Chain   : High-performance Embedded Workshop (Version 4.07.01.004)
*              : C Compiler Package for M16C Series and R8C Family M3T-NC30WA(V.5.45 Release 01)
*              : 
/******************************************************************************
* History      : Apr.28.2008 Ver. 1.00 First Release
*              : Dec.28.2010 Ver. 1.01 Modification for Technical Update
******************************************************************************/

#include "sfr_r82d.h"							/* Definition of the R8C/2D SFR */
#include "cs_slave.h"							/* Definition of processing for CS mode */
/**********************************************************************************/
/* Program
/**********************************************************************************/

/******************************************************************************
* Outline           : Main processing
* Declaration       : void main(void)
* Description       : The slave sends and receives it by synchronous serial
*                   : communications. 
* Argument          : void
* Return Value      : void
******************************************************************************/
main(){
	char dummy_read;							/* dummy data read RAM */

	unsigned int i = 0;

	asm("FCLR I");								/* Interrupt disabled */

	/*-----------------------------------------------------------
	-	Set High-speed on-chip oscillator clock to System clock	-
	-----------------------------------------------------------*/
	prc0 = 1;									/* Protect off */
	cm14 = 0;									/* Low-speed on-chip oscillator on */
	fra2 = 0x00;								/* Selects Divide-by-2 mode */
	fra00 = 1;									/* High-speed on-chip oscillator on */
	while( i <= 30 ) i++;						/* This setting is an example of waiting time for the */
												/* oscillation stabilization. Please evaluate the time */
												/* for oscillation stabilization by a user. */
	fra01 = 1;									/* Selects High-speed on-chip oscillator */
	cm16 = 0;									/* Main clock = No division mode */
	cm17 = 0;
	cm06 = 0;									/* CM16 and CM17 enable */
	prc0 = 0;									/* Protect on */
    
	sfr_init();									/* Initial setting of SFR registers */
	asm("FSET I");								/* Interrupt enable */

	while(1){									/* main processing */
		if(cs_communication() != PASS){
			sser &= 0xe7;						/* receive disable,transmit disable */
			orer_sssr = 0;						/* overrun error flag clear */
			re_sser = 1;						/* receive enable */
			dummy_read = ssrdr;					/* dummy read */
		}
	}
}

/******************************************************************************
* Outline                  : SFR initial setting
* Declaration              : void sfr_init(void)
* Description              : Initial setting of SFR registers
* Argument                 : none
* Return Value             : none
******************************************************************************/
void sfr_init(void){
	char dummy_read;							/* dummy data read RAM */
    /* Setting CS mode (slave transfer mode) */
	pd3 &= 0x47;								/* p3_7(SSO),p3_5(SCCK),p3_4(SCS),p3_3(SSI) input mode */
	mstiic = 1;									/* SSU enable */
	iicsel = 0;									/* selects SSU function */
	sser = 0x00;								/* RE bit and TE bit clear */
	ssums_ssmr2 = SSUMS_INIT;					/* communication mode set */
	ssmr = 0x08;								/* MSB first */
	mss_sscrh = 0;								/* slave device set */
	ssmr2 = SSMR2_INIT;							/* bidirectional mode select,ssck pin select,scs pin select */
												/* communication mode select */
	sscrh &= 0x60;								/* communication clock rate = f1/256 */
	orer_sssr = 0;								/* overrun error flag clear */
	sser = 0x08;								/* transmit disables,receive enable,interruput disable */
	dummy_read = ssrdr; 						/* dummy read */
}

/******************************************************************************
* Outline                  : Communication process
* Declaration              : unsigned char cs_communication(void)
* Description              : Communication main routine
* Argument                 : none
* Return Value             : OVERRUN_ERR : Overrun Errors Generated
*                          : PASS        : Process Succeed
******************************************************************************/
unsigned char cs_communication(void){
	char receive_cnt;							/* receive counter */
	char trans_cnt;								/* transfer counter */
	char dummy_read;							/* dummy data read RAM */
    
	/* 3 byte receive  */
	for(receive_cnt = 0; receive_cnt < 3; receive_cnt ++){
		/* wait data receive and overrun error check */
		do{
			if(orer_sssr == 1) return OVERRUN_ERR;
		}while(rdrf_sssr != 1);
		data_store[receive_cnt] = ssrdr;		/* reveive data store */
	}
	re_sser = 0;								/* receive disnable  */
	te_sser = 1;								/* transmit enable */

	/* 3 bytes transmit */
	for(trans_cnt = 0; trans_cnt < TRANS_COUNT; trans_cnt ++){
		sstdr = data_set[trans_cnt];			/* write transmit data */
		asm("nop");                             /* Refer to TN-R8C-A016A/E or TN-R8C-A016A/J. */
		asm("nop");
		asm("nop");
		while(tdre_sssr != 1);					/* wait transmit data empty */
	}
	while(tend_sssr != 1);	 					/* wait transmit end */
	tend_sssr = 0;								/* tend bit set to "0" */
	te_sser = 0;								/* transmit disable */
	re_sser = 1;								/* receive enable */
	dummy_read = ssrdr;							/* ssrdr dummy read */
	return PASS;
}


