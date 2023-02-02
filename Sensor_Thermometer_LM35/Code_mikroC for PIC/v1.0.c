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
unsigned int Convert(unsigned int x);
void Display_LCD_1(unsigned int);
void Display_LCD_2(unsigned int);
void CustomChar(char pos_row, char pos_char);

const char character[] = {28,20,28,0,0,0,0,0};

unsigned int Input_mV=0;
unsigned int Temp=0;

void main(){
    Configuration_LCD();
    Configuration_ADC();
    Display_LCD_Start();
    
     while(1){
              Input_mV=Read_the_adc(1);
              Temp=Convert(Input_mV);
              Display_LCD_1(Temp);
              //Display_LCD_2(Input_mV);
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
     TRISA  = 0xFF;
}

//********************************************************
void Display_LCD_Start (void) {
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_FIRST_ROW); Lcd_Out_Cp("Loading ...");
     //Lcd_Cmd(_LCD_SECOND_ROW); Lcd_Out_Cp("Test LCD");
     Delay_ms(500); Lcd_Cmd(_LCD_CLEAR);
}

//********************************************************
unsigned int Read_the_adc(unsigned char ch){
     unsigned int x=0;
     x = ADC_Read(ch);
     x= x*4.8828125;
     return x;
}

//********************************************************
unsigned int Convert(unsigned int x){
     x=x/10;
     return x;
}

//********************************************************
void Display_LCD_1(unsigned int x){
     Lcd_Cmd(_LCD_FIRST_ROW); Lcd_Out_Cp("Temp: ");
     Lcd_Chr_Cp(((x /100)%10)+48);
     Lcd_Chr_Cp(((x /10)%10)+48);
     Lcd_Chr_Cp(((x /1)%10)+48);
     CustomChar(1,10);
     Lcd_Out_Cp("C");
     Lcd_Cmd(_LCD_SECOND_ROW); Lcd_Out_Cp("LM35 Sensor");
}

//********************************************************
void Display_LCD_2(unsigned int x){
     Lcd_Cmd(_LCD_SECOND_ROW); Lcd_Out_Cp("Input: ");
     Lcd_Chr_Cp(((x /1000)%10)+48);
     Lcd_Chr_Cp(((x /100)%10)+48);
     Lcd_Chr_Cp(((x /10)%10)+48);
     Lcd_Chr_Cp(((x /1)%10)+48);
     Lcd_Out_Cp("mV ");
}

//********************************************************
void CustomChar(char pos_row, char pos_char) {
  char i;
    LCD_Cmd(64);
    for (i = 0; i<=7; i++) LCD_Chr_Cp(character[i]);
    LCD_Chr(pos_row, pos_char, 0);
}