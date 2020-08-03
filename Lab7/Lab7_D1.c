/*------------------------------------------------------------------------------
 * File:        Lab7_D1.c (CPE 325 Lab7 Demo code)
 * Function:    Toggling LED1 using WDT ISR (MPS430F5529)
 *
 * Description: This C program configures the WDT in interval timer mode and
 *              it is clocked with ACLK. The WDT is configured to give an
 *              interrupt for every 1s. LED1 is toggled in the WDT ISR
 *              by xoring P1.0. The blinking frequency of LED1 is 0.5Hz.
 *
 * Clocks:      ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = DCO = default (~1MHz)
 *              An external watch crystal between XIN & XOUT is required for ACLK
 *
 *                          MSP430xG461x
 *                       -----------------
 *                   /|\|              XIN|-
 *                    | |                 | 32kHz
 *                    --|RST          XOUT|-
 *                      |                 |
 *                      |             P1.0|-->LED1(RED)
 *                      |                 |
 * Input:       None
 * Output:      LED1 blinks at 0.5Hz frequency
 * Author:      Aleksandar Milenkovic, milenkovic@computer.org
 *              Prawar Poudel
 * Date:        December 2008
 *------------------------------------------------------------------------------*/
#include <msp430.h>

void main(void) {
    WDTCTL = WDT_ADLY_1000;           // 1 s interval timer
    P1DIR |= BIT0;                    // Set P1.0 to output direction
    SFRIE1 |= WDTIE;                  // Enable WDT interrupt
    _BIS_SR(LPM0_bits + GIE);         // Enter LPM0 w/ interrupt
}

// Watchdog Timer Interrupt Service Routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void) {
    P1OUT ^= BIT0;                    // Toggle P2.2 using exclusive-OR
}
