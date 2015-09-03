/*******************************************************************
http://aquaticus.info/pwm-music
https://github.com/4a4ik/AVR/tree/master/music

	tone output
06-08-2012 funcional
********************************************************************/
#include <htc.h>
__CONFIG(0x3F1A);
#define PIC_CLK 12000000
#include <timers.c>
#include <delay.c>

#define tone_out_port PORTC
#define TONE_OUT_PIN (1<<1)
#include "tones.h"

// Star Wars
const int starwars[] = 
{
	Ais2,8, Ais2,8, P,16, F3,8, F3,8, P,16, Dis3,16, P,16, D3,16, P,16, C3,16, P,16, Ais3,8,
	Ais3,8, P,16, F3,8, P,16, Dis3,16, P,16, D3,16, P,16, C3,16, P,16, Ais3,8, Ais3,8, P,16,
	F3,8, P,16, Dis3,16, P,16, D3,16, P,16, Dis3,16, P,16, C3,8, C3,8, 
	MUSIC_END
};
// Fur Elise
const int furelise[] = 
{
    e4, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3,8, p, 8,
    c3, 8, e3, 8, a3, 8,  b3, 4, p, 8, e3, 8, g3x, 8, b3, 8, c4, 4, p, 8, e3, 8,
    e3, 8, d4x, 8, e4, 8, d4x, 8, e4, 8, b3, 8, d4, 8, c4, 8, a3, 8, p, 8, c3, 8,
    e3, 8, a3, 8, b3, 4, p, 8, e3, 8, c4, 8, b3, 8, a3, 4,
    MUSIC_END
};



void interrupt snd_irq(void){
	tone_out_port ^= TONE_OUT_PIN;
	Timer1Irqclr;  
}
//---------------------------------------------------
//tone(frequencia,duracao);
//Fmax 20.000hz, 500us
//Fmin 16Hz, 62.500us
//---------------------------------------------------
void tone(int f, char d, int t){
int periodo;
char i;
	if(f != 1){
		if(f > 20000) f = 20000;
		if(f < 16) f = 16;	
		// a testar p = -(1000000UL/f)	
		if(f <= 1000){
			periodo = 1000/f;	
			periodo *= 1000;
		}else{
			f /= 1000;
			periodo = 1000/f;
		}
		setTimer1(periodo/2);
		startTimer1;
	}
	
	for(i = 0; i < d; i++)
		DelayMs(t);
	
	tone_out_port &= ~TONE_OUT_PIN;	
	stopTimer1;	
}

void play(const int *m,char tempo){
int note;
int duration;
	while(*m){
		note = *m++;
		duration = (32 - (*m++));
		tone(note, duration, tempo * 1000 );	
	}
}
//---------------------------------------------------
//
//---------------------------------------------------
void main(void)
{
char i;

int freqbase=480;

ADCON0 = 6;
TRISC &= ~TONE_OUT_PIN;


while(1)
{
	
//play(furelise,10);
play(starwars,9);
  
RC4 = 1;
for(i = 0;i<8;i++)
	DelayMs(250);
RC4 = 0;



}
}

