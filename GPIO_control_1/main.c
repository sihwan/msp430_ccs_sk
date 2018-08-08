// Sihwan Kim
// Aug. 7th, 2018

#include <msp430.h> 

int main(void)
{
  int i;

  WDTCTL = WDTPW+WDTHOLD;                   // Stop WDT

  P2DIR |= BIT5;                            // P2.5 set as output
//  P1DIR |= BIT0;                            // P1.0 set as output

  P2DIR |= BIT2;                            // SMCLK set out to pins
  P2SEL |= BIT2;

  P5SEL |= BIT2+BIT3;                       // Port select XT2

  UCSCTL6 &= ~XT2OFF;                       // Enable XT2
  UCSCTL3 |= SELREF_2;                      // FLLref = REFO
                                            // Since LFXT1 is not used,
                                            // sourcing FLL with LFXT1 can cause
                                            // XT1OFFG flag to set
  UCSCTL4 |= SELA_2;                        // ACLK=REFO,SMCLK=DCO,MCLK=DCO

  // Loop until XT1,XT2 & DCO stabilizes - in this case loop until XT2 settles
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL6 &= ~XT2DRIVE0;                    // Decrease XT2 Drive according to
                                            // expected frequency

  UCSCTL4 |= SELS_5 + SELM_5;               // SMCLK=MCLK=XT2
//  UCSCTL4 &= ~SELS_5 + ~SELM_5;               // SMCLK=MCLK=XT2

  while(1)                                 // Loop in place
  {
    P2OUT ^= BIT5;                          // XOR P2.5
//    P1OUT ^= BIT0;                          // XOR P1.0
//    P1OUT = ~BIT0;                          // XOR P1.0

//    for(i=0;i<0xFFFF;i++);                   // Delay
//    __delay_cycles(600000);                 // Delay
  }
//  return 0;
}
