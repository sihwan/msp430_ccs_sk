// Sihwan Kim
// Jul. 29, 2018

#include <msp430.h>

int main(void)
{
  int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT
  P1DIR |= BIT0;                            // P1.0 set as output

  while(1)                                  // continuous loop
  {
    BCSCTL1 &= ~BIT3;                 // set to DCO(7,3)
    BCSCTL1 |= BIT0 + BIT1 + BIT2;
    DCOCTL &= ~BIT7;
    DCOCTL |= BIT5 + BIT6;

    P1OUT ^= BIT0;                          // XOR P1.0
    //for(i=0;i<0xFFFF;i++);                   // Delay
    for(i=0;i<0x0FFF;i++);                   // Delay
  }
}

