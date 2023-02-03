// GitHub Account:     GitHub.com/AliRezaJoodi

// LCD module connections
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB2_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB2_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
// End LCD module connections

char uart_rd;
unsigned char z1;

void main(){
     TRISD = 0b00001111;
     TRISB = 0b11010111;
     TRISA = 0b11101111;  PORTA = 0b11101111;
     Lcd_Init();
     Lcd_Cmd(_LCD_CLEAR);
     UART1_Init(9600);
     UART1_Write_Text("UART Test"); UART1_Write(13);
     while (1) {                     // Endless loop
           if (UART1_Data_Ready()) {      // If data is received,
              uart_rd = UART1_Read();      //   read the received data,
              UART1_Write(uart_rd);        //   and send data via UART
              //UART1_Read_Text(output, "OK", 13); // reads text until 'OK' is found
              //UART1_Write_Text(output);
              Lcd_Chr_CP((uart_rd));
           }
     }

}