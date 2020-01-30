// Sihwan Kim
// Jan. 19, 2020
// P1.2 doesn't work as GPIO.

#include <msp430.h>
#include <stdio.h>

int main(void)
{
    int i, out00, out01, out10, out11;

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

    P1OUT |= BIT4;                          // XOR P1.4 - Reset "On"
    P2OUT &= (~BIT4);                          // XOR P2.4 - nFet Row0 "Off"
    P2OUT &= (~BIT5);                          // XOR P2.5 - nFet Row1 "Off"
    P2OUT &= (~BIT0);                          // XOR P2.0 - nFet Col0 "Off"
    P2OUT &= (~BIT2);                          // XOR P2.2 - nFet Col1 "Off"

    while(1)
    {
        P1OUT ^= BIT0;                          // XOR P1.0 (LED)

        P2OUT |= BIT4;                          // P2.4 - nFet Row0 "On"
        P2OUT |= BIT0;                          // P2.0 - nFet Col0 "On"
        P1OUT &= (~BIT4);                       // P1.4 - Reset "Off"
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        out00=ADC12MEM0;
        P2OUT &= (~BIT0);                       // P2.0 - nFet Col0 "Off"
        P2OUT &= (~BIT4);                       // P2.4 - nFet Row0 "Off"
        P1OUT |= BIT4;                          // P1.4 - Reset "On"

        for(i=0;i<0x00FF;i++);                  // Delay for reset

        P2OUT |= BIT4;                          // P2.4 - nFet Row0 "On"
        P2OUT |= BIT2;                          // P2.2 - nFet Col1 "On"
        P1OUT &= (~BIT4);                       // P1.4 - Reset "Off"
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        out01=ADC12MEM0;
        P2OUT &= (~BIT2);                       // P2.2 - nFet Col1 "Off"
        P2OUT &= (~BIT4);                       // P2.4 - nFet Row0 "Off"
        P1OUT |= BIT4;                          // P1.4 - Reset "On"

        for(i=0;i<0x00FF;i++);                  // Delay for reset

        P2OUT |= BIT5;                          // P2.5 - nFet Row1 "On"
        P2OUT |= BIT0;                          // P2.0 - nFet Col0 "On"
        P1OUT &= (~BIT4);                       // P1.4 - Reset "Off"
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        out10=ADC12MEM0;
        P2OUT &= (~BIT0);                       // P2.0 - nFet Col0 "Off"
        P2OUT &= (~BIT5);                       // P2.5 - nFet Row1 "Off"
        P1OUT |= BIT4;                          // P1.4 - Reset "On"

        for(i=0;i<0x00FF;i++);                  // Delay for reset

        P2OUT |= BIT5;                          // P2.5 - nFet Row1 "On"
        P2OUT |= BIT2;                          // P2.2 - nFet Col1 "On"
        P1OUT &= (~BIT4);                       // P1.4 - Reset "Off"
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
        for(i=0;i<0xFFFF;i++);                  // Delay for current to settle down
        out11=ADC12MEM0;
        P2OUT &= (~BIT2);                       // P2.2 - nFet Col1 "Off"
        P2OUT &= (~BIT5);                       // P2.5 - nFet Row1 "Off"
        P1OUT |= BIT4;                          // P1.4 - Reset "On"

        for(i=0;i<0x00FF;i++);                   // Delay for reset

        printf("00= %d, 01= %d, 10= %d, 11= %d \n",out00,out01,out10,out11);
    }
}
