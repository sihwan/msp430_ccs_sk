// Sihwan Kim
// Jan. 19, 2020
// P1.2 doesn't work as GPIO.

#include <msp430.h>
#include <stdio.h>

int main(void)
{
    WDTCTL = WDTPW+WDTHOLD;                     // Stop WDT

    ADC12CTL0 = ADC12SHT02 + ADC12ON;           // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP;                       // Use sampling timer
    ADC12IE = 0x01;                             // Enable interrupt
    ADC12CTL0 |= ADC12ENC;
    P6SEL |= BIT0;                              // P6.0 ADC option select

    P1DIR |= BIT0;                              // P1.0 set as output

    P1SEL &= (~BIT4);                           // Set P1.4 SEL for GPIO
    P1DIR |= BIT4;                              // Set P1.4 as Output
    P2SEL &= (~BIT0);                           // Set P2.0 SEL for GPIO
    P2DIR |= BIT0;                              // Set P2.0 as Output
    P2SEL &= (~BIT2);                           // Set P2.2 SEL for GPIO
    P2DIR |= BIT2;                              // Set P2.2 as Output
    P2SEL &= (~BIT4);                           // Set P2.4 SEL for GPIO
    P2DIR |= BIT4;                              // Set P2.4 as Output
    P2SEL &= (~BIT5);                           // Set P2.5 SEL for GPIO
    P2DIR |= BIT5;                              // Set P2.5 as Output

    P1SEL &= (~BIT3);                           // Set P1.3 SEL as GPIO
    P1DIR &= (~BIT3);                           // Set P1.3 set SEL as Input
    P1IES |= (BIT3);                            // Falling Edge 1 -> 0
    P1IFG &= (~BIT3);                           // Clear interrupt flag for P1.3

    while(1)
    {
        if(P1IFG & BIT3){
            P1OUT ^= BIT0;                          // XOR P1.0
            P1OUT ^= BIT4;                          // XOR P1.4
            P2OUT ^= BIT0;                          // XOR P2.0
            P2OUT ^= BIT2;                          // XOR P2.2
            P2OUT ^= BIT4;                          // XOR P2.4
            P2OUT ^= BIT5;                          // XOR P2.5
            ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
            printf("Hello world! %d \n",ADC12MEM0);
            P1IFG &= (~BIT3);                           // Clear interrupt flag for P1.3
        }
    }
}
