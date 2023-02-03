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

void Display_Start_Text(){
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Out(1, 1, "Loading ...");
     Lcd_Out(2, 1, "Test LCD");
}

void Test_1(){
     Lcd_Cmd(_LCD_FIRST_ROW); Lcd_Out_Cp("Line 1");
     Lcd_Cmd(_LCD_SECOND_ROW); Lcd_Out_Cp("Line 2");
}

void Test_2(){
     Lcd_Chr(2, 1, 'E');
     Lcd_Chr_Cp('N');
     Lcd_Chr_Cp('D');
}

void main(){
     Lcd_Init();
     
     Display_Start_Text();
     Delay_ms(2000); Lcd_Cmd(_LCD_CLEAR);
     
     Test_1();
     Delay_ms(2000); Lcd_Cmd(_LCD_CLEAR);
     
     Test_2();
     
     while(1){

     }
}