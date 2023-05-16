#include <REGX51.H>
#define uchar unsigned char
#define uint unsigned int
uchar cp1,cp2,cp3,cp4,sec=0,hour=0,min=0,a,b,pwm;

uint  intensity,infrard,AD1;

#include <AD.c>
#include <1602.c>
#include <display.c> 


#include <key.c>
sbit LED=P2^1;
void timer_isr()interrupt 1
{
	TL0 = (65535-1000)%256;                     
    TH0 = (65535-1000)/256;
	cp1++; cp3++;key();
	if(cp1>=250)
	{
		cp1=0;
		cp2++;
//		LCD_clr1602();
		intensity=read_pcf8591(0x40);//¹âÇ¿
		AD1= intensity/10;
		infrard=read_pcf8591(0x42);//ºìÍâ
	}
	
	if(cp2>=4)
	{
		cp2=0;
      a++;
		sec++;
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
	if(mode==0)
	{		
	if(cp3>=20) cp3=0;  
	if(cp3>=AD1)  pwm =1;
	if(cp3<=AD1)  pwm =0;
    if(infrard>=60)
			{
				b=a;
				if(b >= a+10) LED=1;
				
			 }
   	else
		LED=pwm;
    }
   if(mode==1)
    LED=1;	   
			
}
void timer_init()
{
    TMOD = 0x01;                  
	TL0 = (65535-1000)%256;                     
    TH0 = (65535-1000)/256;
    TR0 = 1;                        
    ET0 = 1;                      
    EA = 1; 
}
void main()
{
     timer_init();
     init_24c04();
	init_1602();
	while(1)
	{
	 display();
		
		key();
	}
}