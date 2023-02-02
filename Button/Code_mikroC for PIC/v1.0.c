// GitHub Account:     GitHub.com/AliRezaJoodi

sbit LED at RC0_bit;
bit oldstate;                       // Old state flag

void main() {
  TRISB0_bit = 1;                   // set RB0 pin as input
  TRISC0_bit = 0;                   // set RC0 pin as output
  LED=0;
  
  oldstate = 0;
  do {
    if (Button(&PORTB, 0, 1, 1)) {  // Detect logical one
      oldstate = 1;                 // Update flag
    }
    if (oldstate && Button(&PORTB, 0, 1, 0)) { // Detect one-to-zero transition
      //PORTC = ~PORTC;               // Invert PORTC
      LED=~LED;
      oldstate = 0;                 // Update flag
    }
  } while(1);                       // Endless loop
}