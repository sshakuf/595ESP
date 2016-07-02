

#include "common.h" 
#include "74hc595.h"


#include "espmissingincludes.h"
#include "c_types.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "osapi.h"
#include <gpio.h>

#include "time_utils.h"

#include <string.h>

#define BITDATA BIT12
#define BITCLK BIT13
#define BITLATCH BIT14

int count;

void ICACHE_FLASH_ATTR Init595()
{
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
	count =0;
	SetPin(BITLATCH);
	ClearPin(BITCLK);


}
// GND (pin 8) to ground,
// Vcc (pin 16) to 5V
// OE (pin 13) to ground
// MR (pin 10) to 5V
// GPI12 to Pin 14 Data
// GPI13 to Pin 11 Shift (careful, some ESP07 and ESP12 have the wrong silkscreen)
// GPI14 to Pin 12 Latch
// Pin 13 /OE, Pin 10 /MR to GND of course

#define SDATA 12
#define SCLK 13
#define SLAT 14



void ICACHE_FLASH_ATTR doClk(int data)
{
	   	OutputPin(BITDATA, data);
	   	SetPin(BITCLK);
	   	   		//os_delay_us(1000);
	   	ClearPin(BITCLK);
}

void ICACHE_FLASH_ATTR loop595()
{

	int n;
	//out595();
	
	// if (count == 0)
	// {
	// 	os_printf("\nloop595 = 0\n");
	//    	ClearPin(BITLATCH);
	//    	doClk(0);
	//    	doClk(0);
	//    	doClk(1);
	//    	doClk(1);
	//    	doClk(0);
	//    	doClk(0);
	//    	doClk(1);
	//    	doClk(1);
	//    	SetPin(BITLATCH);

	//     count =1;
	// }
	// else{

	// 	os_printf("\nloop595 = 1\n");
	//    	ClearPin(BITLATCH);
	//    	doClk(1);
	//    	doClk(1);
	//    	doClk(0);
	//    	doClk(0);
	//    	doClk(1);
	//    	doClk(1);
	//    	doClk(0);
	//    	doClk(0);
	//    	SetPin(BITLATCH);
	//     count =0;
	// }
	// int x = count;

	// for(n=0; n<8; n++)
 //   	{
 //      if((x & 0x80) !=0)
 //      {
 //         doClk(1);
	// 	 os_printf("1");
 //      }
 //      else
 //      {
 //         doClk(0);
	// 	 os_printf("0");
 //      }
 //      x = x<<1;
 //      if (n==3)
 //      {
	// 	 os_printf("-");
 //      }
 //   	}
	// ClearPin(BITLATCH);
	// SetPin(BITLATCH);

	// count++;


}

void ICACHE_FLASH_ATTR out595()
{

	int n;
	int x= flashData->ePort;

	os_printf("\nloop595 = ");

	SetPin(BITLATCH);
	for(n=0; n<8; n++)
   	{
      if((x & 0x80) !=0)
      {
         doClk(1);
		 os_printf("1");
      }
      else
      {
         doClk(0);
		 os_printf("0");
      }
      x = x<<1;
   	}
	ClearPin(BITLATCH);
	SetPin(BITLATCH);

	os_printf(" ******\n\n");


}








