#include <htc.h>
#include <timers.h>
#include "rttl.h"
volatile RTTL rttl;
volatile char aux;
//---------------------------------------------------
//timer1 tick period = 1.333333us @ 12Mhz
//---------------------------------------------------
void soundinit(void){
	setTimer1(0);
	setTimer0();
	TMR0IE = 0; 						// stop timer for now	
	sound_out_port &= ~sound_out_pin;
	rttl.play = 0;	
}
//---------------------------------------------------
//
//---------------------------------------------------
int atoi(const char *str){
int num = 0;
	while((*str>0x2f) && (*str<0x3a)){
		num = (num * 10) + (*str++ - '0');
	}
	return num;
}
//---------------------------------------------------
//
//---------------------------------------------------
void play(const char *music){
	do{
		if(!(*music))
			return;             //not rttl header		
	}while( (*music++) != ':'); //skip name

	do{
		if(!(*music))
			return;   
		if( *music == 'd'){
			music += 2; // skip "d="
			aux = (char) atoi(music);
			if(aux > 0)
				rttl.default_duration = aux;
			else
				rttl.default_duration = DEFAULT_DURATION;
		}
		if(*music == 'o'){
			music += 2; // skip "o="
			rttl.default_octave = *music - '0';
		}

		if(*music == 'b'){
			music += 2; // skip "d="
			rttl.bpm = atoi(music);
		}			
	}while( (*music++) != ':');
	
	rttl.notes = music;
	rttl.fullnoteduration = FULL_NOTE_DURATION / rttl.bpm;	
	rttl.play = 1;           // enable play
	rttl.noteduration = 0;   // force note load	
	T1Ticks = PAUSE_VALUE;   // load first note to force interrupt
	startTimer1;             // start play		
}
//---------------------------------------------------
//TODO: 
//     
//---------------------------------------------------
void interrupt system(void){
	// variable interval, depends of tone
	if(Timer1Irq){
		if(rttl.play){
			if(!rttl.noteduration){
				sound_out_port &= ~sound_out_pin;	// disable output
				stopTimer1;
				
				if(!(*rttl.notes)){ // Stop music  									
					rttl.play = 0;	
					TMR0IE = 0;	
					Timer1Irqclr;										
					return;
				}
				
				//get duration				
				aux = 0;
				while((*rttl.notes>0x2f) && (*rttl.notes<0x3a))
					aux = (aux * 10) + (*rttl.notes++ - '0');
				if(!aux) aux = rttl.default_duration;  
				rttl.noteduration = rttl.fullnoteduration/aux;
				
				//check sharp note
				aux = note_map[*rttl.notes - 'a'];
				*rttl.notes++;
				if( (*rttl.notes) == '#'){	
					aux++; 
					*rttl.notes++;
				}
				
				T1Ticks = ccp_values[aux]; 	   // load value into compare module
				
				//dotted note?
				if( (*rttl.notes) == '.'){ 
					rttl.noteduration += (rttl.noteduration >> 1);
					*rttl.notes++;
				}
				
				//get octave
				aux = 0;
				if((*rttl.notes>0x2f) && (*rttl.notes<0x3a))
					aux = *rttl.notes++ - '0';
				if(!aux) aux = rttl.default_octave;  
				while(aux > BASE_OCTAVE){					
					T1Ticks >>= 1;
					aux--;
				}
				
				//skip ','
				if(*rttl.notes == ',')
					*rttl.notes++; 				
				TIMER1 = 0;    	// must reset, avoid deadtime								
				startTimer1;
				TMR0 = TIMER0_1MS_RELOAD;
				TMR0IE = 1;     // enable timer 0 intr
				
			}else{
				if(T1Ticks < MAX_CCP_VALUE)
					sound_out_port ^= sound_out_pin;  // toggle output			
			}
		}		
		Timer1Irqclr;  //clear timer interrupt flag
	}
	// ~1ms interval
	if(Timer0Irq){
		//sound_out_port ^= 1;		
		TMR0 = TIMER0_1MS_RELOAD;
		rttl.noteduration--;
		if(!rttl.noteduration)
			TMR0IE = 0;
		Timer0Irqclr;		
	}
}
