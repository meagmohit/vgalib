
/*
 *  Written By:-
 *  Mohit Agarwal 
 *  Electronics Club, IIT Kanpur
 *  Contact: me.agmohit@gmail.com
 *  See Project Documentation for more details
*/


#include <avr/io.h>
#include <avr/signal.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "sram.h"
#include "symbol_tbl.h"
#include "avrlibdefs.h"
#include "vgalib.c"
#include "sram.c"

#define NOP asm("nop")

//Global definitions for VGA render
#define vga_field_line_count 525 //standart VGA quantity lines

#define buffer_on  cbi(PORTD,1)
#define buffer_off sbi(PORTD,1)
//HSYNC
#define hsync_off  sbi(PORTD,3)
#define hsync_on  cbi(PORTD,3)
//VSYNC
#define vsync_on  PORTD= PORTD&(0b11110011)// AFFECTS ONLY HSYNC AND VSYNC PINS
#define vsync_off sbi(PORTD,2)// so after evry vsync_off.. h_sync on is necessary

//Global variables
volatile unsigned int urgent; // frame skipping flag
volatile unsigned int video_enable_flg;//flag for enable render
volatile unsigned int linecount;// current line for render
volatile unsigned int framecount;
static void avr_init(void); // defined that a such function exists

//All VGA sincronize made here..
SIGNAL(SIG_OVERFLOW0)
{
 TCNT0 = 0xC3; //reload counter value
		//******Syncronization Handler********

            if (++linecount == vga_field_line_count)
			{
			linecount = 0;
			framecount++;
			
			if(((framecount%2)==0))
			{
                     urgent=2;      //denotes blank
            }
            else
            {
                urgent=1;
            }
			}
	
			

			//Make Vsync length 2 VGA lines 
			if ((linecount == 10 )||(linecount == 11 ))
			{
				//Make here vertical syncronization & HSYNC syncro level on
				vsync_on;
			}
			else
			{
				//.. & HSYNC syncro level on
				vsync_off;
				hsync_on;
			}
		
		
			
	
			if (linecount < 45)
			{
				video_enable_flg = 3;
					//Add to avoid flickering at top display
					NOP;
					NOP;
					NOP;
					NOP;
					NOP;
					NOP;
					NOP;
     				NOP;
					NOP;
					NOP;
					NOP;
					NOP;
					NOP;
					NOP;
					NOP;//15 times
					
			}
			else
			{
		    if(urgent==1)
            {
                 video_enable_flg = 2;
            }
            if(urgent==2)
            {
                 video_enable_flg = 4;
            }
		
			}
		
		
			hsync_off; //HSYNC syncro level off
		
		//******Syncronization Handler********

}


int main(void)
{
     framecount=1;
	 urgent=1;
	 
 SRAM_Init();
{
/************************************
 * Define your Global variables Here*
*************************************
*/
}

     avr_init();
 	for(;;)
    {

		//Wait compare interrupt signal from Timer1
		sleep_mode();
		
		
		//Check visible field
		if(video_enable_flg==2)
		{
		//OK, visible
		
              
	SRAM_DATA_DDR = 0x00;
	SRAM_ADDRL_PORT=(linecount>>1)-22;
	SRAM_ADDRH_PORT=0;
	sbi(PORTD,4);
	sbi(PORTD,5);
	cbi(PORTD,7);
	buffer_on;
	cbi(PORTD,5);
	NOP;
	sbi(PORTD,5);
	SRAM_ADDRH_PORT=1;
	                           
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=2;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=3;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=4;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=5;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=6;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=7;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=8;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=9;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=10;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=11;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=12;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=13;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=14;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=15;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=16;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=17;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=18;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=19;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=20;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=21;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=22;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=23;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=24;
        		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=25;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=26;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=27;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=28;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=29;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=30;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=31;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=32;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=33;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=34;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=35;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=36;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=37;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=38;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=39;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=40;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=41;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=42;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=43;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=44;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=45;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=46;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=47;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=48;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=49;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
    	SRAM_ADDRH_PORT=50;
		cbi(PORTD,5);
		NOP;
		sbi(PORTD,5);
		SRAM_ADDRH_PORT=51;
	cbi(PORTD,5);
	NOP;
    sbi(PORTD,5);
	sbi(PORTD,7);
				buffer_off;

		}
		else if(video_enable_flg==4)
		{
{
/**********************************
 *Define your Local variables here*
 *and write your code here*********
***********************************
*/
}
  
{
      asm("pqrs:");
      if(linecount!=524)
      {
        asm("RJMP pqrs");
      }

    

}




        

		}
		else
		{
		}
		
    }//for(;;)
    return(0);
}



static void avr_init(void)
{
 
  // Initialize Sync for VGA
  TCCR0 = 0x00; //stop
  TCNT0 = 0xC3; //set count, One VGA line 31.77us
  TCCR0 = 1<<CS01; //start timer with prescaler select 1/8    CS01 bit is set to one it means timer freq=prescalar/8
  TIMSK = 1<<TOV0; //enable interrupt from Timer0 overflow
  // When the TOIE0 bit is written to one, and the I-bit in the Status Register is set (one), the
//Timer/Counter0 Overflow interrupt is enabled. The corresponding interrupt is executed if an
//overflow in Timer/Counter0 occurs, that is, when the TOV0 bit is set in the Timer/Counter Interrupt
//Flag Register – TIFR.
  

  //init ports
  //HSYNC
  sbi(PORTD,3);
  sbi(DDRD,3);
  //VSYNC
  sbi(PORTD,2);
  sbi(DDRD,2);
  sbi(DDRD,1);
  //DDRC=0xFF;

  //Set power mode
  set_sleep_mode(SLEEP_MODE_IDLE); 	

  //Enable global interrupt
  asm ("sei");

  return;
}
    
	
    
