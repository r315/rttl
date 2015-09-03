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



//const char song []= "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
const char itchy [] = {
//c,8,a5,8,p,4,c,8,a,8,p,4,c,8,a5,8,c,8,a5,8,c,8,a,8,p,4,p,8,c,8,d,8,e,8,p,8,e,8,f,8,g,8,p,4,d,8,c,8,d,4,f,8,Bb,4,a,4,c7,2
"Itchy:d=8,o=6,b=160:c,a5,4p,c,a,4p,c,a5,c,a5,c,a,4p,p,c,d,e,p,e,f,g,4p,d,c,4d,f,4a#,4a,2c7"
};

const char test [] = {
a,8,h,2,c,4,d,8,p,8 
};
//---------------------------------------------------
//
//---------------------------------------------------
void main(void)
{

	ADCON0 = 6;
	TRISC = 0b11111100;
	
	soundinit();
	setTimer0();
	TMR0IE = 0; // stop timer for now

while(1){	
	//play(welcome, sizeof(welcome));
	//play(furelise,sizeof(furelise));
	//play(starwars,sizeof(starwars));
	play(itchy,sizeof(itchy));
	//play(test,sizeof(test));
	while(sound.play);
	DelayMs(250);
	DelayMs(250);
	//DelayMs(250);

}
}

