/**************************************************************************
			Ring Tones Text Transfer Language
			
RTTL player
http://midi.mathewvp.com/rttl2Midi.php
RTTL Spec
http://www.mobilefish.com/tutorials/rtttl/rtttl_quickguide_specification.html
RTTL project
http://www.instructables.com/id/Aruino-Tone-RTTL-Player/?ALLSTEPS


                       ______  BUZ
                      |
          10k       |/
out ----/\/\/\--+---|  2222A
                |   |\
                |     |
		  10uF ---	  |
			   ---    |
				|     |
				|_____|
				  GND
**************************************************************************/

#ifndef _rttl_h_
#define _rttl_h_


typedef struct{
	const char *notes;			  //notes to play
	char play;					  //play flag
	char default_octave;		  //default octave
	unsigned int default_duration;//default note duration
	unsigned int bpm;             //mustic rhythym
	unsigned int noteduration;	  //duration of note in ms
	unsigned int fullnoteduration;//duration of whole note in ms
}RTTL;


#ifndef sound_out_port
    #error "define sound_out_port"
#endif
#ifndef sound_out_pin
    #error "define sound_out_pin"
#endif

#define FULL_NOTE_DURATION 240000UL  //wholenote duration = (60 seconds * 1000ms * 4 beats full note) / (bpm of song)
#define DEFAULT_DURATION 4
#define BASE_OCTAVE 4               //4th octave
#define MAX_CCP_VALUE 1024          //
#define PAUSE_VALUE -1



const int ccp_values[]={
852,804,759,717,676,638,602,569,537,506,478,451,
PAUSE_VALUE,
};
//                       a b c d e f g        ..        p
const char note_map[] = {0,2,3,5,7,8,10,0,0,0,0,0,0,0,0,12};

void soundinit(void);				//init / stop player
void play(const char *tone);		//start player
#endif
