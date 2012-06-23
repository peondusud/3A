#ifndef __TIMERS_H
#define __TIMERS_H

#include <pconfig.h>
/* PIC18 timers peripheral library. */

/* used to hold 16-bit timer value */
union Timers
{
  unsigned int lt;
  char bt[2];
};


/* storage class of library routine parameters; pre-built with auto;
 * do not change unless you rebuild the libraries with the new storage class */ 
#define PARAM_SCLASS auto


/* Interrupt bit mask to be 'anded' with the other configuration masks and
 * passed as the 'config' parameter to the 'open' routines. */

#ifdef USE_OR_MASKS
#define TIMER_INT_OFF  		0b00000000  // Interrupts disabled
#define TIMER_INT_ON   		0b10000000  // Interrupts enabled
#define TIMER_INT_MASK		(~TIMER_INT_ON)

/* ***** TIMER0 ***** */

/* TIMER0 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
#define T0_16BIT       		0b00000000  // Timer 0 is in 16 Bit mode
#define T0_8BIT       		0b01000000  // Timer 0 is in 8 bit mode
#define T0_BIT_MASK			(~T0_8BIT)

#define T0_SOURCE_INT  		0b00000000  // Internal clock source
#define T0_SOURCE_EXT  		0b00100000  // External clock source
#define T0_SOURCE_MASK		(~T0_SOURCE_EXT)

#define T0_EDGE_RISE   		0b00000000  // External rising edge clocs timer
#define T0_EDGE_FALL   		0b00010000  // External falling edge clocks timer
#define T0_EDGE_MASK		(~T0_EDGE_FALL)

#define T0_PS_1_1      		0b00001000  // Prescaler 1:1 (NO Prescaler)
#define	NO_T0_PS_MASK		(~T0_PS_1_1)
		
#define T0_PS_1_2      		0b00000000  //           1:2
#define T0_PS_1_4      		0b00000001  //           1:4
#define T0_PS_1_8      		0b00000010  //           1:8
#define T0_PS_1_16     		0b00000011  //           1:16
#define T0_PS_1_32     		0b00000100  //           1:32
#define T0_PS_1_64     		0b00000101  //           1:64
#define T0_PS_1_128    		0b00000110  //           1:128
#define T0_PS_1_256    		0b00000111  //           1:256
#define T0_PS_MASK			(~T0_PS_1_256)
//---------------AND MASK--------------------------------
#else //!USE_OR_MASKS
#define TIMER_INT_OFF  0b01111111  // Interrupts disabled
#define TIMER_INT_ON   0b11111111  // Interrupts enabled

/* ***** TIMER0 ***** */

/* TIMER0 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
#define T0_16BIT       0b10111111  // Timer 0 is in 16 Bit mode
#define T0_8BIT        0b11111111  // Timer 0 is in 8 bit mode
#define T0_SOURCE_INT  0b11011111  // Internal clock source
#define T0_SOURCE_EXT  0b11111111  // External clock source
#define T0_EDGE_RISE   0b11101111  // External rising edge clocs timer
#define T0_EDGE_FALL   0b11111111  // External falling edge clocks timer
#define T0_PS_1_1      0b11111111  // Prescaler 1:1 (NO Prescaler)
#define T0_PS_1_2      0b11110000  //           1:2
#define T0_PS_1_4      0b11110001  //           1:4
#define T0_PS_1_8      0b11110010  //           1:8
#define T0_PS_1_16     0b11110011  //           1:16
#define T0_PS_1_32     0b11110100  //           1:32
#define T0_PS_1_64     0b11110101  //           1:64
#define T0_PS_1_128    0b11110110  //           1:128
#define T0_PS_1_256    0b11110111  //           1:256

#endif//USE_OR_MASKS



void OpenTimer0 (PARAM_SCLASS unsigned char config);
void CloseTimer0 (void);
unsigned int ReadTimer0 (void);
void WriteTimer0 (PARAM_SCLASS unsigned int timer0);


/* ***** TIMER1 ***** */

/* TIMER1 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
//--------------AND OR MASK------------------------------
#ifdef	USE_OR_MASKS
#define T1_8BIT_RW       0b00000000  // 8-bit mode
#define T1_16BIT_RW      0b01000000  // 16-bit mode
#define T1_BIT_RW_MASK	 (~T1_16BIT_RW)

#define T1_PS_1_1        0b00000000  // 1:1 prescale value
#define T1_PS_1_2        0b00010000  // 1:2 prescale value
#define T1_PS_1_4        0b00100000  // 1:4 prescale value
#define T1_PS_1_8        0b00110000  // 1:8 prescale value
#define T1_PS_MASK		 (~T1_PS_1_8)	
	
#define T1_OSC1EN_OFF    0b00000000  // Timer 1 oscilator enable off
#define T1_OSC1EN_ON     0b00001000  // Timer 1 oscilator enable on
#define	T1_OSC_MASK		 (~T1_OSC1EN_ON)

#define T1_SYNC_EXT_ON   0b00000000  // Synchronize external clock input
#define T1_SYNC_EXT_OFF  0b00000100  // Do not synchronize external clock input
#define T1_SYNC_MASK	 (~T1_SYNC_EXT_OFF)

#define T1_SOURCE_INT    0b00000000  // Internal clock source
#define T1_SOURCE_EXT	 0b00000010  // External clock source
#define	T1_SOURCE_MASK	 (~T1_SOURCE_EXT)

//-----------------AND MASK-----------------------------
#else //!USE_OR_MASKS
#define T1_8BIT_RW       0b10111111  // 8-bit mode
#define T1_16BIT_RW      0b11111111  // 16-bit mode
#define T1_PS_1_1        0b11001111  // 1:1 prescale value
#define T1_PS_1_2        0b11011111  // 1:2 prescale value
#define T1_PS_1_4        0b11101111  // 1:4 prescale value
#define T1_PS_1_8        0b11111111  // 1:8 prescale value
#define T1_OSC1EN_OFF    0b11110111  // Timer 1 oscilator enable off
#define T1_OSC1EN_ON     0b11111111  // Timer 1 oscilator enable on
#define T1_SYNC_EXT_ON   0b11111011  // Synchronize external clock input
#define T1_SYNC_EXT_OFF  0b11111111  // Do not synchronize external clock input
#define T1_SOURCE_INT    0b11111101  // Internal clock source
#define T1_SOURCE_EXT    0b11111111  // External clock source

#endif //USE_OR_MASKS

void OpenTimer1 (PARAM_SCLASS unsigned char config);
void CloseTimer1 (void);
unsigned int ReadTimer1 (void);
void WriteTimer1 (PARAM_SCLASS unsigned int timer1);


/* ***** TIMER2 ***** */

/* TIMER2 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
//-----------------AND OR MASK----------------------
#ifdef USE_OR_MASKS
#define T2_POST_1_1    0b00000000  // Postscaler 1:1
#define T2_POST_1_2    0b00001000  // Postscaler 1:2
#define T2_POST_1_3    0b00010000  // Postscaler 1:3
#define T2_POST_1_4    0b00011000  // Postscaler 1:4
#define T2_POST_1_5    0b00100000  // Postscaler 1:5
#define T2_POST_1_6    0b00101000  // Postscaler 1:6
#define T2_POST_1_7    0b00110000  // Postscaler 1:7
#define T2_POST_1_8    0b00111000  // Postscaler 1:8
#define T2_POST_1_9    0b01000000  // Postscaler 1:9
#define T2_POST_1_10   0b01001000  // Postscaler 1:10
#define T2_POST_1_11   0b01010000  // Postscaler 1:11
#define T2_POST_1_12   0b01011000  // Postscaler 1:12
#define T2_POST_1_13   0b01100000  // Postscaler 1:13
#define T2_POST_1_14   0b01101000  // Postscaler 1:14
#define T2_POST_1_15   0b01110000  // Postscaler 1:15
#define T2_POST_1_16   0b01111000  // Postscaler 1:16
#define	T2_POST_MASK	(~T2_POST_1_16)

#define T2_PS_1_1      0b00000000  // Prescale 1:1
#define T2_PS_1_4      0b00000001  // Prescale 1:4
#define T2_PS_1_16     0b00000011  // Prescale 1:16
#define T2_PS_MASK 		(~T2_PS_1_16)	

//------------------AND MASK------------------------
#else //!USE_OR_MASKS
#define T2_POST_1_1    0b10000111  // Postscaler 1:1
#define T2_POST_1_2    0b10001111  // Postscaler 1:2
#define T2_POST_1_3    0b10010111  // Postscaler 1:3
#define T2_POST_1_4    0b10011111  // Postscaler 1:4
#define T2_POST_1_5    0b10100111  // Postscaler 1:5
#define T2_POST_1_6    0b10101111  // Postscaler 1:6
#define T2_POST_1_7    0b10110111  // Postscaler 1:7
#define T2_POST_1_8    0b10111111  // Postscaler 1:8
#define T2_POST_1_9    0b11000111  // Postscaler 1:9
#define T2_POST_1_10   0b11001111  // Postscaler 1:10
#define T2_POST_1_11   0b11010111  // Postscaler 1:11
#define T2_POST_1_12   0b11011111  // Postscaler 1:12
#define T2_POST_1_13   0b11100111  // Postscaler 1:13
#define T2_POST_1_14   0b11101111  // Postscaler 1:14
#define T2_POST_1_15   0b11110111  // Postscaler 1:15
#define T2_POST_1_16   0b11111111  // Postscaler 1:16
#define T2_PS_1_1      0b11111100  // Prescale 1:1
#define T2_PS_1_4      0b11111101  // Prescale 1:4
#define T2_PS_1_16     0b11111110  // Prescale 1:16

#endif //!USE_OR_MASKS

void OpenTimer2 (PARAM_SCLASS unsigned char config);
void CloseTimer2 (void);
unsigned char ReadTimer2 (void);
#define WriteTimer2(timer2) TMR2 = (timer2)
#define ReadTimer2()	TMR2

/* ***** TIMER3 ***** */

#if defined(TMR_V1)  || defined(TMR_V2)  || defined(TMR_V4)

/* TIMER3 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
#ifdef USE_OR_MASKS
#define T3_8BIT_RW      0b00000000 // 8-bit mode
#define T3_16BIT_RW     0b00000001 // 16-bit mode
#define T3_BIT_MASK		(~T3_16BIT_RW)

#define T3_PS_1_1       0b00000000 // 1:1 prescale value
#define T3_PS_1_2       0b00010000 // 1:2 prescale value
#define T3_PS_1_4       0b00100000 // 1:4 prescale value
#define T3_PS_1_8       0b00110000 // 1:8 prescale value
#define T3_PS_MASK		(~T3_PS_1_8)

#define T3_OSC1EN_OFF   0b00000000 // Timer 3 oscillator enable off
#define T3_OSC1EN_ON    0b00000010 // Timer 3 oscillator enable on
#define T3_OSC1_MASK	(~T3_OSC1EN_ON)

#define T3_SYNC_EXT_ON  0b00000000 // Synchronize external clock input
#define T3_SYNC_EXT_OFF 0b00000100 // Do not synchronize external clock input
#define T3_SYNC_MASK	(~T3_SYNC_EXT_OFF)

#define T3_SOURCE_INT   0b00000000 // Internal clock source
#define T3_SOURCE_EXT   0b00000010 // External clock source
#define T3_SOURCE_MASK	(~T3_SOURCE_EXT)

#else //!USE_OR_MASKS
#define T3_8BIT_RW      0b11111110 // 8-bit mode
#define T3_16BIT_RW     0b11111111 // 16-bit mode
#define T3_PS_1_1       0b11001111 // 1:1 prescale value
#define T3_PS_1_2       0b11011111 // 1:2 prescale value
#define T3_PS_1_4       0b11101111 // 1:4 prescale value
#define T3_PS_1_8       0b11111111 // 1:8 prescale value
#define T3_OSC1EN_OFF   0b11111101 // Timer 3 oscillator enable off
#define T3_OSC1EN_ON    0b11111111 // Timer 3 oscillator enable on
#define T3_SYNC_EXT_ON  0b11111011 // Synchronize external clock input
#define T3_SYNC_EXT_OFF 0b11111111 // Do not synchronize external clock input
#define T3_SOURCE_INT   0b11111101 // Internal clock source
#define T3_SOURCE_EXT   0b11111111 // External clock source


#endif //USE_OR_MASKS

#if defined(__18F6520)  || defined(__18F6620)  || defined(__18F6720) || \
    defined(__18F8520)  || defined(__18F8620)  || defined(__18F8720) || \
    defined(__18F6620)  || defined(__18F6621)  || \
    defined(__18F8620)  || defined(__18F8621)  || \
    defined(__18F64J15) || defined(__18F65J10) || defined(__18F65J15) || \
    defined(__18F66J10) || defined(__18F66J15) || defined(__18F67J10) || \
    defined(__18F84J15) || defined(__18F85J10) || defined(__18F85J15) || \
    defined(__18F86J10) || defined(__18F86J15) || defined(__18F87J10) || \
    defined(__18F6527)  || defined(__18F6622)  || \
    defined(__18F6627)  || defined(__18F6722)  || \
    defined(__18F8527)  || defined(__18F8622)  || \
    defined(__18F8627)  || defined(__18F8722)

//---------------AND OR MASK-----------------------------------------------------
#ifdef USE_OR_MASKS
#define T34_SOURCE_CCP   		  	0b01001000		// T3 and T4 are sources for CCP1 thru CCP5
#define T12_CCP12_T34_CCP345		0b01000000			// T1 and T2 are sources for CCP1 and CCP2 and T3 and T4 are sources for CCP3 thru CCP5
#define T12_CCP1_T34_CCP2345		0b00001000			// T1 and T2 are sources for CCP1 and T3 and T4 are sources for CCP2 thru CCP5
#define T12_SOURCE_CCP   		  	0b00000000		// T1 and T2 are sources for CCP1 thru CCP5
#define TMR_SOURCE_CCP_MASK			(~T34_SOURCE_CCP)

//-------------AND MASK---------------------------------------
#else  //!USE_OR_MASKS
#define T34_SOURCE_CCP   		  	0b11111111		// T3 and T4 are sources for CCP1 thru CCP5
#define T12_CCP12_T34_CCP345		0b11110111			// T1 and T2 are sources for CCP1 and CCP2 and T3 and T4 are sources for CCP3 thru CCP5
#define T12_CCP1_T34_CCP2345		0b10111111			// T1 and T2 are sources for CCP1 and T3 and T4 are sources for CCP2 thru CCP5
#define T12_SOURCE_CCP   		  	0b10110111		// T1 and T2 are sources for CCP1 thru CCP5
#endif //USE_OR_MASKS
//-------------------------------------------------------------------------------

#else //USE_OR_MASKS

//---------------AND OR MASK-----------------------------------------------------
#ifdef USE_OR_MASKS
#define T3_SOURCE_CCP        	0b01001000			// T3 is source for CCP
#define T1_CCP1_T3_CCP2       	0b00001000			// T1 is source for CCP1 and T3 is source for CCP2
#define T1_SOURCE_CCP        	0b00000000			// T1 is source for CCP
#define TMR_SOURCE_CCP_MASK		(~T3_SOURCE_CCP)
//----------------AND MASK-------------------------------------------------------
#else //!USE_OR_MASKS
#define T3_SOURCE_CCP         0b11111111			// T3 is source for CCP
#define T1_CCP1_T3_CCP2       0b10111111			// T1 is source for CCP1 and T3 is source for CCP2
#define T1_SOURCE_CCP         0b10110111			// T1 is source for CCP
#endif //USE_OR_MASKS

#endif

void OpenTimer3 (PARAM_SCLASS unsigned char config);
void CloseTimer3 (void);
unsigned int ReadTimer3 (void);
void WriteTimer3 (PARAM_SCLASS unsigned int timer3);

#endif


/* ***** TIMER4 ***** */

#if defined(__18F6520) || defined(__18F6620) || defined(__18F6720) || \
    defined(__18F8520) || defined(__18F8620) || defined(__18F8720) || \
    defined(__18F6620) || defined(__18F6621) || \
    defined(__18F8620) || defined(__18F8621) || \
    defined(__18F6527) || defined(__18F6622) || \
    defined(__18F6627) || defined(__18F6722) || \
    defined(__18F8527) || defined(__18F8622) || \
    defined(__18F8627) || defined(__18F8722)

/* TIMER4 configuration masks -- to be 'anded' together and passed to the
 * 'open' routine. */
//-----------------AND OR MASK
#ifdef USE_OR_MASKS
#define T4_POST_1_1    0b00000000  // Postscaler 1:1
#define T4_POST_1_2    0b00001000  // Postscaler 1:2
#define T4_POST_1_3    0b00010000  // Postscaler 1:3
#define T4_POST_1_4    0b00011000  // Postscaler 1:4
#define T4_POST_1_5    0b00100000  // Postscaler 1:5
#define T4_POST_1_6    0b00101000  // Postscaler 1:6
#define T4_POST_1_7    0b00110000  // Postscaler 1:7
#define T4_POST_1_8    0b00111000  // Postscaler 1:8
#define T4_POST_1_9    0b01000000  // Postscaler 1:9
#define T4_POST_1_10   0b01001000  // Postscaler 1:10
#define T4_POST_1_11   0b01010000  // Postscaler 1:11
#define T4_POST_1_12   0b01011000  // Postscaler 1:12
#define T4_POST_1_13   0b01100000  // Postscaler 1:13
#define T4_POST_1_14   0b01101000  // Postscaler 1:14
#define T4_POST_1_15   0b01110000  // Postscaler 1:15
#define T4_POST_1_16   0b01111000  // Postscaler 1:16
#define T4_POST_MASK	(~T4_POST_1_16)

#define T4_PS_1_1      0b00000000  // Prescale 1:1
#define T4_PS_1_4      0b00000001  // Prescale 1:4
#define T4_PS_1_16     0b00000011  // Prescale 1:16
#define T4_PS_MASK		(~T4_PS_1_16)
//----------------AND MASK--------------------------
#else //!USE_OR_MASKS
#define T4_POST_1_1    0b10000111  // Postscaler 1:1
#define T4_POST_1_2    0b10001111  // Postscaler 1:2
#define T4_POST_1_3    0b10010111  // Postscaler 1:3
#define T4_POST_1_4    0b10011111  // Postscaler 1:4
#define T4_POST_1_5    0b10100111  // Postscaler 1:5
#define T4_POST_1_6    0b10101111  // Postscaler 1:6
#define T4_POST_1_7    0b10110111  // Postscaler 1:7
#define T4_POST_1_8    0b10111111  // Postscaler 1:8
#define T4_POST_1_9    0b11000111  // Postscaler 1:9
#define T4_POST_1_10   0b11001111  // Postscaler 1:10
#define T4_POST_1_11   0b11010111  // Postscaler 1:11
#define T4_POST_1_12   0b11011111  // Postscaler 1:12
#define T4_POST_1_13   0b11100111  // Postscaler 1:13
#define T4_POST_1_14   0b11101111  // Postscaler 1:14
#define T4_POST_1_15   0b11110111  // Postscaler 1:15
#define T4_POST_1_16   0b11111111  // Postscaler 1:16
#define T4_PS_1_1      0b11111100  // Prescale 1:1
#define T4_PS_1_4      0b11111101  // Prescale 1:4
#define T4_PS_1_16     0b11111111  // Prescale 1:16

#endif //USE_OR_MASKS


void OpenTimer4 (PARAM_SCLASS unsigned char config);
void CloseTimer4 (void);
unsigned char ReadTimer4 (void);
#define WriteTimer4(timer4) TMR4 = (timer4)
#define ReadTimer4()	TMR4
#endif



//-------- TIMER 5 DECLARATION ---------------------
#if defined TMR_V5
//--------------AND OR MASK-----------------------------------
#ifdef USE_OR_MASKS
#define T5_SLP_EN       	0b10000000   // Enable during sleep
#define T5_SLP_DIS      	0b00000000   // Disable during sleep
#define T5_SLP_MASK			(~T5_SLP_EN)

#define T5_SP_EVNT_REN  	0b00000000   // special event reset enable
#define T5_SP_EVNT_RDIS 	0b01000000   // special event reset disable
#define T5_SP_ENNT_MASK		(~T5_SP_EVNT_RDIS)

#define T5_MD_SNGL_SHOT  	0b00100000   // SINGLE SHOT MODE
#define T5_MD_CONT_COUNT 	0b00000000   // CONTINOUS COUNT MODE
#define T5_MD_MASK			(~T5_MD_SNGL_SHOT)

#define T5_PS_1_1      		0b00000000   // Prescale 1:1
#define T5_PS_1_2      		0b00001000   // Prescale 1:2
#define T5_PS_1_4      		0b00010000   // Prescale 1:4
#define T5_PS_1_8      		0b00011000   // Prescale 1:8
#define T5_PS_MASK			(~T5_PS_1_8)

#define T5_EX_CLK_SYNC   	0b00000000   // EXT. CLOCK SYNCHRONIZATION
#define T5_EX_CLK_NOSYNC 	0b00000100   // DO NOT synchronize
#define T5_EX_CLK_SYNC_MASK	(~T5_EX_CLK_NOSYNC)	

#define T5_CLK_EXTRN  		0b00000010   // Clock source external
#define T5_CLK_INT	  		0b00000000   // Clock source internal
#define T5_CLK_SOURCE_MASK	(~T5_CLK_EXTRN)

//----------------AND MASK--------------------------------------
#else //!USE_OR_MASKS
#define T5_SLP_EN       	0b11111111   // Enable during sleep
#define T5_SLP_DIS      	0b01111111   // Disable during sleep 
#define T5_SP_EVNT_REN  	0b10111111   // special event reset enable
#define T5_SP_EVNT_RDIS 	0b11111111   // special event reset disable
#define T5_MD_SNGL_SHOT  	0b11111111   // SINGLE SHOT MODE
#define T5_MD_CONT_COUNT 	0b11011111   // CONTINOUS COUNT MODE
#define T5_PS_1_1      		0b11100111   // Prescale 1:1
#define T5_PS_1_2      		0b11101111   // Prescale 1:2
#define T5_PS_1_4      		0b11110111   // Prescale 1:4
#define T5_PS_1_8      		0b11111111   // Prescale 1:8
#define T5_EX_CLK_SYNC   	0b11111011   // EXT. CLOCK SYNCHRONIZATION
#define T5_EX_CLK_NOSYNC 	0b11111111   // DO NOT synchronize
#define T5_CLK_EXTRN  		0b11111111   // Clock source external
#define T5_CLK_INT	  		0b11111101   // Clock source internal

#endif	//USE_OR_MASKS

void CloseTimer5(void);
void OpenTimer5(PARAM_SCLASS unsigned char, PARAM_SCLASS unsigned int);
unsigned int ReadTimer5(void);
void WriteTimer5(PARAM_SCLASS unsigned int);
#endif

#endif//__TIMERS_H

