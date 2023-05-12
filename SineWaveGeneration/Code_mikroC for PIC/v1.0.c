/*******************************************************************************
* Program Written by_ Engr. Mithun K. Das                                      *
* Date:18-04-2020                                                              *
*******************************************************************************/

// GitHub Account:     GitHub.com/AliRezaJoodi

unsigned char sin_table[40]=
{0,2,6,14,24,37,53,70,88,108,
128,147,167,185,202,218,231,241,249,253,
255,253,249,241,231,218,202,185,167,147,
128,108,88,70,53,37,24,14,6,2};

bit enable;
bit alt;
int duty=0;
float correction=0.8;

void Interrupt() iv 0x0004 ics ICS_AUTO{
   if (TMR2IF_bit == 1){
   
      duty++;
      if(duty>=40){
        duty=0;
        alt=~alt;
        RC0_bit=0; CCPR1L = 0; //inverter shutdown
        RC3_bit=0; CCPR2L = 0; //inverter shutdown
        asm nop; asm nop;
      }

      if(enable){
          if(alt){
               RC0_bit=1; CCPR1L = sin_table[duty]*correction;
               RC3_bit=0; CCPR2L=0; //inverter shutdown
          }
          else{
               RC0_bit=0; CCPR1L=0; //inverter shutdown
               RC3_bit=1; CCPR2L = sin_table[duty]*correction;
          }
      }
      else{
           RC0_bit=0; CCPR1L = 0; //inverter shutdown
           RC3_bit=0; CCPR2L = 0; //inverter shutdown
      }
      TMR2IF_bit = 0;
   }
}

void main(){
   TRISC = 0x00; //all output
   PORTC=0x00;

   CCP1CON = 0x4C;   //PWM mode.
   CCPR1L = 0;
   CCP2CON = 0x4C;
   CCPR2L = 0;
   TMR2IF_bit = 0;
   T2CON = 0b00011100; //Timer2 control register. Prescaler is 1. Postscale is 1:4
   PR2 = 249; //Timer2 increments from 00h until it matches PR2 and then resets to 00h
   TMR2IF_bit = 0;
   TRISC = 0;
   TMR2IE_bit = 1;
   GIE_bit = 1;
   PEIE_bit = 1;
   
   enable=1;
   while(1){
   }
}