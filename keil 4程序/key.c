sbit k0=P2^0;
bit mode=0;
void key()
{
	 if(k0==0)
	 {
	  delayus(300);
	  if(k0==0)
	  {
	   mode =! mode;
	  }
	  while(k0==0);	 
	 }
}