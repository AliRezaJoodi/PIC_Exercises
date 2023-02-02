// GitHub Account:     GitHub.com/AliRezaJoodi

// Lcd pinout settings
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB2_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

// Pin direction
sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB2_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;

void Configuration_LCD(void);
void Configuration_ADC(void);
void Display_LCD_Start(void);
unsigned int Read_the_adc(unsigned char);
void Display_LCD_1(unsigned int);
void Display_LCD_2(unsigned int);
void Display_Float(float);

unsigned int Input_mV=0;

void main(){
    Configuration_LCD();
    Configuration_ADC();
    Display_LCD_Start();
    
     while(1){
              Input_mV=Read_the_adc(1);
              Display_LCD_1(Input_mV);
              Display_LCD_2(Input_mV);
              Delay_ms(300);
     }
}

//********************************************************
void Configuration_LCD(void){
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
}

//********************************************************
void Configuration_ADC(void){
     ADCON1=0x80;
     TRISA  = 0xFF;          // PORTA is input
}

//********************************************************
void Display_LCD_Start (void) {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_FIRST_ROW); Lcd_Out_Cp("Loading ...");
     //Lcd_Cmd(_LCD_SECOND_ROW); Lcd_Out_Cp("Test LCD");
     Delay_ms(1000); Lcd_Cmd(_LCD_CLEAR);
}

//********************************************************
unsigned int Read_the_adc(unsigned char ch){
     unsigned int x=0;
     x = ADC_Read(ch);
     x= x*4.8828125;
     return x;
}

//********************************************************
void Display_LCD_1(unsigned int x){
     Lcd_Cmd(_LCD_FIRST_ROW); Lcd_Out_Cp("In:");
     x=x/100;
     Lcd_Chr_Cp(((x /10)%10)+48);
     Lcd_Chr_Cp('.');
     Lcd_Chr_Cp(((x /1)%10)+48);
     Lcd_Out_Cp("v ");
}

//********************************************************
void Display_LCD_2(unsigned int x){
     Lcd_Cmd(_LCD_SECOND_ROW); Lcd_Out_Cp("In:");
     Lcd_Chr_Cp(((x /1000)%10)+48);
     Lcd_Chr_Cp(((x /100)%10)+48);
     Lcd_Chr_Cp(((x /10)%10)+48);
     Lcd_Chr_Cp(((x /1)%10)+48);
     Lcd_Out_Cp("mV ");
}