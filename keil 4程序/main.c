#include <REGX51.H>
#define uchar unsigned char
#define uint unsigned int
uint cp1,cp2,cp3,cp4,cp5,sec=0,hour=0,min=0,a,b=16,pwm,sec1=0;
uint  intensity,infrard,AD1,AD2;
#include <AD.c>
#include <1602.c>
#include <key.c>  
sbit LED=P2^1;
#include <display.c> 
void timer_isr()interrupt 1
{
	TL0 = (65535-1000)%256;                     
    TH0 = (65535-1000)/256;
	cp1++; 
	cp3++;
    if(cp3 > AD2)  pwm =1;
	if(cp3 <= AD2)  pwm =0;
   	if(cp3 >= 25) cp3=0;
		 
	if(cp1>=200)
	{
		cp1=0;
		cp2++;
		if(cp2 == 1)
		{
			infrard =  read_pcf8591(0x40);
		} 
		if(cp2 == 4)
		{
			cp2=0;
	  		sec++;
			intensity = read_pcf8591(0x42);//¹âÇ¿
			AD1= intensity*0.39;   
	     	AD2= intensity/10;

		}
	}	  
	if(sec>=60)
	{
	 	min++;
	 	sec=0;
	}
	if(min>=60)
	{
	 	min=0;
	 	hour++;
	}
	if(hour>=24) hour=0; 
	 if(mode == 0)
	{		  		
	if(infrard  >= 150)LED = pwm;	
	else LED = 1;
	}
	if(mode == 1)
	{
		LED = 1;	
	}
}


void timer_init()
{
    TMOD |= 0x01;                  
	TL0 = (65535-1000)%256;                     
    TH0 = (65535-1000)/256;
    TR0 = 1;                        
    ET0 = 1;                      
    EA = 1; 
}
void main()
{

//    uchar i;
    timer_init();
    init_24c04();
	init_1602();
	sec=0;
	hour=0;			
	min=0;

	while(1)
	{
		 key();
	 	display();
	}
}