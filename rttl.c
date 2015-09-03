#include <htc.h>
#include <timers.h>
#include "rttl.h"
SOUND sound;
char aux;
//---------------------------------------------------
//timer1 tick period = 1.333333us @ 12Mhz
//---------------------------------------------------
void soundinit(void)
{
	stop();
    setTimer1(0);
	TRISC &= ~sound_out_pin;
	//sound_out_port|0x80 &= ~sound_out_pin;
    GIE = 1;	    
}
//---------------------------------------------------
//
//---------------------------------------------------
void stop(void)
{
	stopTimer1;
	sound_out_port &= ~sound_out_pin;
	sound.play = 0;	
}

char isDigit(char c){
	if( c > '/' && c < ':')
		return 1;
	return 0;
}
//---------------------------------------------------
//
//---------------------------------------------------

void play(const char *music, int size){
	do{
		if(!(*music))
			return;             //not rttl header		
	}while( (*music++) != ':'); //skip name

	do{
		if(!(*music))
			return;   
		if( *music == 'd'){
			*music++;
			
			
		return;
	*music++;




	sound.notes = music;      // music notes
	sound.size = size/2;	  	  //
	sound.wholenote = FULL_NOTE_DURATION/160;
	sound.play = 1;           // enable play
	sound.noteduration = 0;   // force note load
	T1Ticks = cmp_values[*sound.notes];   // load first note
	startTimer1;              // start play	
}
//---------------------------------------------------
//TODO: 
//     
//---------------------------------------------------
void interrupt system(void){
	// variable interval, depends of tone
	if(Timer1Irq){
		if(sound.play){
			if(!sound.noteduration){
				if(!sound.size){     //end of music
					stopTimer1;		 // stop timer
					sound_out_port &= ~sound_out_pin;	// clr out avoid current consume
					sound.play = 0;	 // music not playing	
					Timer1Irqclr;					
					return;
				}
				T1Ticks = cmp_values[*sound.notes++]; 	         // load note
				aux = 0;
				while( !((*sound.notes) & (1<<aux))) aux++;		//log2(x)=aux
				sound.noteduration = sound.wholenote >> aux; // load note duration in ms				
				sound.size --;                       // decrement note counter		
				*sound.notes++;                      // next note
				TIMER1 = 0;    	// must reset, becouse if next note < prev note 
								// it creates dead time
				TMR0IE = 1;               // enable timer 0 intr
			}else{
				if(T1Ticks < PAUSE_VALUE)
					sound_out_port ^= sound_out_pin;  // toggle output			
			}
		}		
		Timer1Irqclr;  //clear timer interrupt flag
	}
	// ~1ms interval
	if(Timer0Irq){
		//sound_out_port ^= 1;		
		TMR0 = TIMER0_1MS_RELOAD;
		sound.noteduration--;
		if(!sound.noteduration)
			TMR0IE = 0;
		Timer0Irqclr;		
	}
}
