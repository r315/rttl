/**************************************************************************
RTTL player
http://midi.mathewvp.com/rttl2Midi.php
RTTL Spec
http://www.mobilefish.com/tutorials/rtttl/rtttl_quickguide_specification.html
RTTL project
http://www.instructables.com/id/Aruino-Tone-RTTL-Player/?ALLSTEPS
**************************************************************************/

#ifndef _rttl_h_
#define _rttl_h_


typedef struct{
const char *notes;				//notes pointer
	char play;					//play flag
	char default_duration;		//
	char default_octave;		//
    unsigned int size;			//number of notes on sound
	unsigned int noteduration;	//duration of note in ms
	unsigned int wholenote;		//duration of whole note in ms
}RTTL;


#ifndef sound_out_port
    #error "define sound_out_port"
#endif
#ifndef sound_out_pin
    #error "define sound_out_pin"
#endif

#define FULL_NOTE_DURATION 240000UL  //wholenote duration = (60 seconds * 1000ms * 4 beats full note) / (bpm of song)

void stop(void);
void play(const char *tone, int size);

#define PAUSE_VALUE -1
const int cmp_values[]={PAUSE_VALUE,
852,804,759,717,676,638,602,569,537,506,478,451,
426,402,379,358,338,319,301,284,268,253,239,225,
213,201,189,179,169,159,150,142,134,126,119,112,
106,100, 94, 89, 84, 79, 75, 71, 67, 63, 59, 56
};

// values for 12Mhz 
#define a	1	/* note freq: 440.0Hz */
#define Bb	2	/* note freq: 466.0Hz */
#define h	3	/* note freq: 494.0Hz */
#define c	4	/* note freq: 523.0Hz */
#define Db	5	/* note freq: 554.0Hz */
#define d	6	/* note freq: 587.0Hz */
#define Eb	7	/* note freq: 622.0Hz */
#define e	8	/* note freq: 659.0Hz */
#define f	9	/* note freq: 698.0Hz */
#define Gb	10	/* note freq: 740.0Hz */
#define g	11	/* note freq: 784.0Hz */
#define Ab	12	/* note freq: 830.0Hz */
#define a5	13	/* note freq: 880.0Hz */
#define Bb5	14	/* note freq: 932.0Hz */
#define b5	15	/* note freq: 988.0Hz */
#define c5	16	/* note freq: 1046.0Hz */
#define Db5	17	/* note freq: 1108.0Hz */
#define d5	18	/* note freq: 1174.0Hz */
#define Eb5	19	/* note freq: 1244.0Hz */
#define e5	20	/* note freq: 1318.0Hz */
#define f5	21	/* note freq: 1396.0Hz */
#define Gb5	22	/* note freq: 1480.0Hz */
#define g5	23	/* note freq: 1568.0Hz */
#define Ab5	24	/* note freq: 1660.0Hz */
#define a6	25	/* note freq: 1760.0Hz */
#define Bb6	26	/* note freq: 1864.0Hz */
#define b6	27	/* note freq: 1976.0Hz */
#define c6	28	/* note freq: 2092.0Hz */
#define Db6	29	/* note freq: 2216.0Hz */
#define d6	30	/* note freq: 2348.0Hz */
#define Eb6	31	/* note freq: 2488.0Hz */
#define e6	32	/* note freq: 2636.0Hz */
#define f6	33	/* note freq: 2792.0Hz */
#define Gb6	34	/* note freq: 2960.0Hz */
#define g6	35	/* note freq: 3136.0Hz */
#define Ab6	36	/* note freq: 3320.0Hz */
#define a7	37	/* note freq: 3520.0Hz */
#define Bb7	38	/* note freq: 3728.0Hz */
#define b7	39	/* note freq: 3952.0Hz */
#define c7	40	/* note freq: 4184.0Hz */
#define Db7	41	/* note freq: 4432.0Hz */
#define d7	42	/* note freq: 4696.0Hz */
#define Eb7	43	/* note freq: 4976.0Hz */
#define e7	44	/* note freq: 5272.0Hz */
#define f7	45	/* note freq: 5584.0Hz */
#define Gb7	46	/* note freq: 5920.0Hz */
#define g7	47	/* note freq: 6272.0Hz */
#define Ab7	48	/* note freq: 6640.0Hz */
#define p	0	/* pause */
#endif
