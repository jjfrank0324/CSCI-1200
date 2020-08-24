#include <c8051_SDCC.h>
#include <stdlib.h>
#include <stdio.h>
#include <i2c.h>


void Port_Init(void);
void PCA_Init (void);
void SMB_Init (void);
void ADC_Init(void);
void Interrupt_Init(void);
void PCA_ISR ( void ) __interrupt 9;
void read_accel (void);  //Sets global variables gx & gy
void set_servo_PWM (void);
void set_drive_PWM(void);
void updateLCD(void);
void set_gains(void);
void pause(void); // function which allow operator to set feedback gains
//define global variables
unsigned int PW_CENTER = 2768;
unsigned int PW_RIGHT = 3318;
unsigned int PW_LEFT = 2118;
unsigned int SERVO_PW = 2768;
unsigned int SERVO_MAX= 3502;
unsigned int SERVO_MIN= 2027;
unsigned char new_accel = 0; // flag for count of accel timing
unsigned char new_lcd = 0;  // flag for count of LCD timing
unsigned int  range; unsigned char a_count;   // overflow count for acceleration
unsigned char lcd_count;  // overflow count for LCD updates

unsigned char key0;
unsigned char key1;
float avg_gx = 0;
float avg_gy = 0;
float gx;
float gy;
int kdx;
int kdy;
int ks;
 void main(void)
 {
   unsigned char run_stop;  // define local variables
   Sys_Init();     // initialize board  putchar(' ');
   Port_Init();
   PCA_Init();
   SMB_Init();
   Interrupt_Init();
   Accel_Init_C();
   a_count = 0;  lcd_count = 0;

   while(1)
   {
     run_stop = 0;
     while (!run)
     {
        if (run_stop == 0)
        {
              set_gains();  // function adjusting feedback gains
              run_stop = 1:
        }
     }
     if (new_accels)
     {
          read_accels();
          set_servo_PWM();  // set the servo PWM
          set_drive_PWM();  // set drive PWM
           new_accels = 0;
           a_count = 0;
     }
     if (new_lcd)
     {
          updateLCD(); // display values
          new_lcd = 0;
          lcd_count = 0;
     }

   }
}


void PCA_ISR ( void ) __interrupt 9
{
  if(CF)
  {
    CF = 0; // clear overflow indicator
    a_count++;
    if(a_count>=1)
    {
         new_accel=1;
         a_count = 0;
    }
    lcd_count++;
    if (lcd_count>=2)
    {
         new_lcd = 1;
         lcd_count = 0;
    }
    PCA0 = 28614;
  }
}


void read_accel(void)
{
  avg_gx = 0;
  avg_gy =0;



  for(unsigned int i =0; i<4; i++)
  {
    i2c_read_data(0x3A, 0x27, Dataa, 1);
    while((Dataa[0] & 0x03) != 0x03 )
    {
      i2c_read_data(0x3A, 0x27,  Dataa, 1);
    }

    i2c_read_data(0x3A, 0x28|0x80, Dataa, 4);
    avg_gx += ((Dataa[1]<<8)>>4);
    avg_gy += ((Dataa[3]<<8)>>4);
  }

  avg_gx = avg_gx/4;
  avg_gy = avg_gy/4;

  gx = avg_gx;
  gy = avg_gy;

}

void set_servo_PWM(void)
{
  PCA0CP0 = 0xFFFF - 2768 + ks * gx;
}

void set_drive_PWM(void)
{
  PCA0CP2 = 0xFFFF - 2768 - kdy * gy - kdx*abs(gx);
}


void set_gains(void)
{
  lcd_clear();


  //the variable that store the data
  key0 = 0;
  key1 = 0;

  //enter the first bit, caculate it, and store it into the (Keypad)
  printf ("Enter a number \r\n");
  while(read_keypad() == 0xFF)		pause();  //wait until we enter something
  key0 = read_keypad() - 48;
  pause();
  lcd_print("Your first enter is: %u", key0);
  ks += 10*(key0);
  pause();
  while(read_keypad() != 0xFF) 		pause();//wait until the PB is released


  //enter the second bits
  printf ("Enter a number \r\n");
  while(read_keypad() == 0xFF)		pause();//wait until we enter something
  key1 = read_keypad() - 48;
  pause();
  lcd_print("Your second enter is: %u", key1);
  ks += key1;
  pause();
  while(read_keypad() != 0xFF) 		pause();//wait until the PB is released




  lcd_clear();




  //enter the first bit, caculate it, and store it into the (Keypad)
  printf ("Enter a number \r\n");
  while(read_keypad() == 0xFF)		pause();  //wait until we enter something
  key0 = read_keypad() - 48;
  pause();
  lcd_print("Your first enter is: %u", key0);
  kdy += 10*(key0);
  pause();
  while(read_keypad() != 0xFF) 		pause();//wait until the PB is released


  //enter the second bits
  printf ("Enter a number \r\n");
  while(read_keypad() == 0xFF)		pause();//wait until we enter something
  key1 = read_keypad() - 48;
  pause();
  lcd_print("Your second enter is: %u", key1);
  kdy += key1;
  pause();
  while(read_keypad() != 0xFF) 		pause();//wait until the PB is released



  lcd_clear();




  //enter the first bit, caculate it, and store it into the (Keypad)
  printf ("Enter a number \r\n");
  while(read_keypad() == 0xFF)		pause();  //wait until we enter something
  key0 = read_keypad() - 48;
  pause();
  lcd_print("Your first enter is: %u", key0);
  kdx += 10*(key0);
  pause();
  while(read_keypad() != 0xFF) 		pause();//wait until the PB is released


  //enter the second bits
  printf ("Enter a number \r\n");
  while(read_keypad() == 0xFF)		pause();//wait until we enter something
  key1 = read_keypad() - 48;
  pause();
  lcd_print("Your second enter is: %u", key1);
  kdx += key1;
  pause();
  while(read_keypad() != 0xFF) 		pause();//wait until the PB is released

}

void Update_Value(unsigned char incr, int maxval, int minval)
{
  // Constant is the global int variable to be adjusted
  int deflt = 20; //Fill in desired default value
  char input;
 // 'c' - default, 'i' - increment, 'd' - decrement // This can easily be changed to use the keypad instead of the terminal
 input = getchar_nw();
 if (input == 0xFF) return;
 else if (input == 'i')
 {
   ks += incr;
   kdx += incr;
   kdy +=incr;
 }
 else if (input == 'd')
 {
   ks -= incr;
   kdx -= incr;
   kdy -= incr;
 }
}

void Port_Init(void)
{
  P0MDOUT &= ~0xC0;
  P0 |= 0xC0;
  P1MDOUT &= 0xAF;
  P1MDOUT |= 0x05;
  P1MDIN &= 0xEF;
  P1 |= ~0xAF;
  P3MDOUT |= 0x80;

}

void Interrupt_Init(void)
{
  IE |= 0x02;
  EIE1 |= 0x08;    // enable PCA interrupts
  EA = 1;          // enable all interrupts
}



void PCA_Init(void)
{
  PCA0MD = 0x81;
  PCA0CPM0 = 0xC2;

  PCA0CPM2 = 0xC2;

  PCA0CN = 0x40;
}

void SMB_Init(void)
{
  SMB0CR = 0x93;
  ENSMB = 1;
}

void XBR0_Init()
{
	XBR0 = 0x27;//configure crossbar with UART, SPI, SMBus, and CEX channels as
// in worksheet
}

void pause(void)
{
    count = 0;
    while (count  < 1);// 1 count -> (65536-PCA_START) x 12/22118400 = 20ms
}
