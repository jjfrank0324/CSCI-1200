#include <c8051_SDCC.h>
#include <stdio.h>
#include <i2c.h>

#define pw_min 1000               // set limits for the pulsewidth
#define pw_max 65000


void PCA_Init(void);
void XBR0_Init(void);
void Port_Init(void);
void Interrupt_Init(void);
void PCA_ISR(void) __interrupt 9;
void SMB_Init(void);

unsigned int PW = 5000;           // pulsewidth for speed controller
unsigned int PCA_start = 28614;   // start count for PCA
int new_range = 0 ;
int r_count = 0 ;
unsigned int result  = 0;
unsigned char Dataa[3];
 unsigned char addr = 0xE0;
unsigned int HEADING = 0;
unsigned int h_count=0;
unsigned int new_heading = 0;


void main()
{

    Sys_Init();            // initial functions in c8051_SDCC.h file
    putchar(' ');
    Port_Init();
    XBR0_Init();           // initialize XBAR
    Interrupt_Init();      // initialize Interrupts
    PCA_Init ();           // initialize PCA
    SMB_Init();
    while(1)
    {
	//	printf("the new heading is %u\r\n", h_count);
      // if (new_heading)
      // {
      //   HEADING = read_compass();
      //   printf("The compass is %u \r\n" , HEADING);   // print heading
      //   new_heading = 0;
      // }



        //part one
        if(new_range)
        {
          HEADING = ReadCompass();
        result = ReadRanger();
	//	printf("The result of the ranger reading is %u\r\n",result );
        new_range =0;
        Dataa[0] = 0x51;
        i2c_write_data(addr, 0, Dataa, 1);
       	printf("The result of the ranger reading is %u\r\n",result );


      }

    }
}


void XBR0_Init()
{
    XBR0 = 0x07;     // set up URART0, SPI, SMB, and CEX 0-3
}


void Interrupt_Init()
{
    EIE1 |= 0x08;    // enable PCA interrupts
    EA = 1;          // enable all interrupts
}


void PCA_Init()
{
    PCA0MD = 0x81;   // SYSCLK/12, enable CF interrupts, suspend when idle
    PCA0CPM1 = 0xC2; // 16 bit, enable compare, enable PWM
    PCA0CN |= 0x40;  // enable PCA
}


void PCA_ISR(void) __interrupt 9
{
    if (CF)
    {
        PCA0 = PCA_start;       // start count
        CF = 0;                 // Very important - clear interrupt flag
        //
        // h_count++;
        // if(h_count>=4)
        // {
        //   new_heading=1;  // 2 overflows is about 40 ms
        //   h_count = 0;
        // }



        //part one
        r_count++;
        if(r_count>=4)
        {
          new_range=1;  // 4 overflows is about 80 ms
          r_count = 0;
        }
    }

    // else PCA0CN &= 0xC0;        // all other type 9 interrupts
}

unsigned int ReadRanger()
{
  unsigned char Data[2];
  unsigned int range =0;
  i2c_read_data(addr,2 , Data, 2);
  range = (((unsigned int)Data[0] << 8) | Data[1]);
  return range;
}


void Port_Init(void)
{
  P0MDOUT &= ~0xD0;
  P0 |= 0xD0;

}

void SMB_Init(void)
{
  SMB0CR = 0x93;
  ENSMB = 1;
}

unsigned int ReadCompass()
{
  unsigned char addr = 0xC0; // the address of the sensor, 0xC0 for the compass
  unsigned char Data[2];      // Data is an array with a length of 2
  unsigned int heading;       // the heading returned in degrees between 0 and 3599
  i2c_read_data(addr, 2, Data, 2);  // read two byte, starting at reg 2
  heading =(((unsigned int)Data[0] << 8) | Data[1]);  //combine the two values
    //heading has units of 1/10 of a degree
  return heading;             // the heading returned in degrees between 0 and 3599
}
