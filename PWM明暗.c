#include <REG51.h> 

#define DY_PORT		P1 
#define DY_PWM		350 


void delay (unsigned int a)
{ 
    unsigned int i;
	while( --a != 0)
	{
		for(i = 0; i < 12; i++); 
	}   				   		 
}

void display (unsigned int a)
{ 
	DY_PORT = 0x00; 
	delay (a); 		
	DY_PORT = 0xff; 
	delay (DY_PWM-a);
}

void main (void)
{ 
  unsigned int t;
  int i;
    while(1)
    {

	i=1;
      while(i<100)
	  {
        for(t=0;t<1;t++)
        {
          display(i);

         
        }
       i++;
       }

	    while(i>2)
		{
        for(t=0;t<1;t++)
		{
           display(i);
		}
		i--;
      }

	 }
}
