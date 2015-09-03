//https://www.youtube.com/watch?v=4byHVqXD-UI

#include <htc.h>
__CONFIG(0x3F1A);

#define PIC_CLK 12000000
#include <timers.c>
#include <pwm.c>
#include <delay.c>

#define SAMPLE_RATE 8000
#define SAMPLE_RATE_PERIOD (SAMPLE_RATE / 32)
#define PWM_FREQUENCY 8000 //SAMPLE_RATE * 2 //nyquist theorem?
#define OUTPUT 0

#define CCP1_PIN (1<<2)
#define CCP2_PIN (1<<1)


char sine[]={0,1,2,4,8,16,32,64,128,255,128,64,32,16,8,4,2,1,0};

struct Sound{	
	char *sample;
	unsigned int play;	
};

static struct Sound sys_sound;

void play(char *snd, unsigned int size){
	sys_sound.sample = snd;	
	sys_sound.play = size;
	startTimer1;
} 
//---------------------------------------------------
//
//---------------------------------------------------
void main(void)
{
	ADCON0 = 6;
	TRISC = 0b111111001;
	
	CCP2CON = CCP_PWM;
	T2CON = 0;			//Prescaler 1:1			
	PR2 = 255; 			//11,7khz 10 bit resolutin
	CCPR2L = 0;			
	TMR2ON = 1;

	setTimer1(SAMPLE_RATE_PERIOD);	
	
	while(1){		
		play(sine,sizeof(sine));
		while(sys_sound.play);
		/*while(sys_sound.play){
			CCPR2L = *sys_sound.sample++;		
			sys_sound.play--;
			DelayMs(10);
		}*/		
	}
}

void interrupt snsIrq(void){
	if(sys_sound.play){		
		CCPR2L = *sys_sound.sample++;
		sys_sound.play--;
		PORTC ^= CCP1_PIN;		
	}
	else{
		CCPR2L = 0;
		stopTimer1;
	}	
	Timer1Irqclr;
}



