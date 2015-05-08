/**********************************************************************************/
/*
/* File name : cs_master.h
/* CPU 		 : R8C/2D Group
/* Function  : Clock Synchronous Serial I/O with Chip Select (SSU)
/* Version   : 1.00 (2008-04-28) Initial
/*
/* Copyright(C)2008, Renesas Electronics Corporation. All rights reserved.
/*
/**********************************************************************************/
/* Refer to the corresponding application notes for program specifications. */

/**********************************************************************************/
/* RAM
/**********************************************************************************/
/* Definition of RAM area */

unsigned char data[3] = {0x66, 0x33, 0x55};			/* transmit data */
unsigned char data_store[3];						/* receive data */

/* Declaration of function prototype */

extern void sfr_init(void);							/* Initial setting of SFR registers */
extern unsigned char cs_communication(void);		/* communication main routine */

/**********************************************************************************/
/* define
/**********************************************************************************/
#define TRANS_COUNT	3								/* transfer counter value */

#define PASS	0									/* No overrun errors generated */
#define OVERRUN_ERR	1								/* Overrun errors generated */

#define SSU_MODE 0									/* ssu communication mode */
													/* "0" 4-wire bus communication mode */
													/* "1" 4-wire bus(bidirectional)communication mode */
													/* "2" Clock synchronous communication mode */

#if SSU_MODE == 0									/* 4-wire bus communication mode */
#define SSUMS_INIT	1								/* 4-wire bus communication mode */
#define SSMR2_INIT	0x71							/* bidirectional mode disable,ssck is serial clock pin,scs output */
													/* 4-wire bus communication mode */

#elif SSU_MODE == 1									/* 4-wire bus(bidirectional)communication mode */
#define SSUMS_INIT	1								/* 4-wire bus communication mode */
#define SSMR2_INIT	0xf1							/* bidirectional mode enable,ssck is serial clock pin */
													/* scs output,4-wire bus communication mode */

#else
#define SSUMS_INIT	0								/* clock synchronous communication mode */
#define SSMR2_INIT	0x40							/* bidirectional mode disable,ssck is serial clock pin */
													/* scs port,clock synchronous communication mode */

#endif
