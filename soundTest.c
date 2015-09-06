/*******************************************************************
	pwm sound demo
	frequency modulation based
	
29-07-2011:
********************************************************************/

#include <htc.h>
__CONFIG(0x3f1A);
#define PIC_CLK 12000000
#include <timers.c>
#include <delay.c>

#define sound_out_port PORTC
#define sound_out_pin (1<<1) 

#include "rttl.c"



const char simpsons []= "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
const char itchy [] = {
//"teste1:d=4,o=4,b=160:a,p,b"
"Itchy:d=8,o=6,b=160:c,a5,4p,c,a,4p,c,a5,c,a5,c,a,4p,p,c,d,e,p,e,f,g,4p,d,c,4d,f,4a#,4a,2c7"
};

const char starwars [] = {
//"teste2:d=4,o=4,b=160:c,p,d"
"StarWars:d=4,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6"
};

const char smb [] = {
"smb:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6"
};

const char smoothcr [] = {
"SmoothCr:d=4,o=5,b=125:8a,16a,16a,16g,16a,8b,8b,8#,16a,16b,8c6,8c6,8#6,16b,16c6,8b,4g,8a,8#,8a,16a,16a,16g,16a,8b,8b,8#,16a,16b,8c6,8c6,8#6,16b,16c6,8b,4g"
};

const char demo[] = {
"Axel-F:d=4,o=5,b=125:g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g,p,16f6,8d6,8c6,8a#,g,8a#.,16g,16p,16g,8c6,8g,8f,g,8d.6,16g,16p,16g,8d#6,8d6,8a#,8g,8d6,8g6,16g,16f,16p,16f,8d,8a#,2g"
};
//---------------------------------------------------
//
//---------------------------------------------------
void main(void)
{	
	ADCON0 = 6;
	TRISC = 0b11111100;	
	soundinit();	
	
	sound_out_port &= ~1;
	DelayMs(250);
	DelayMs(250);
	DelayMs(250);
	DelayMs(250);
	sound_out_port |= 1;
	
while(1){	

	play(demo);	
	while(rttl.play);
	DelayMs(250);
	DelayMs(250);
	
	play(smoothcr);	
	while(rttl.play);
	DelayMs(250);
	DelayMs(250);
	
	play(starwars);	
	while(rttl.play);
	DelayMs(250);
	DelayMs(250);
	
	play(itchy);	
	while(rttl.play);
	DelayMs(250);
	DelayMs(250);
	
	play(simpsons);	
	while(rttl.play);
	DelayMs(250);
	DelayMs(250);
	
	play(smb);	
	while(rttl.play);
	DelayMs(250);
	DelayMs(250);
	
	
}
}

