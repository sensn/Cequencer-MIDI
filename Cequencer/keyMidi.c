//
// Programmer:    Craig Stuart Sapp <craig@ccrma.stanford.edu>
// Creation Date: Sat Jan  1 20:29:45 PST 2005
// Last Modified: Sat Jan  1 20:37:28 PST 2005
// Filename:      ...midiio/doc/windowsmidi/keymidi/keymidi.c
// URL:           http://midiio.sapp.org/doc/windowsmidi/keymidi/keymidi.c
// Syntax:        C; Visual C/C++ 5/6
//
// Description:   The example program shows how to open MIDI output,
//                send a MIDI message, and close MIDI output.
//                When you press a key on the computer keyboard, a MIDI
//                note will be either turned on or off.
//

#include <conio.h>     /* include for kbhit() and getch() functions */
#include <stdio.h>     /* for printf() function */

#include <windows.h>   /* required before including mmsystem.h */
#include <mmsystem.h>  /* multimedia functions (such as MIDI) for Windows */

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

void midi1_noteout(int chan, int noten, int velo);

int ckey;           // storage for the current keyboard key being pressed
int notestate = 0;  // keeping track of when the note is on or off
int velocity = 100; // MIDI note velocity parameter value
int midiport;       // select which MIDI output port to open
int flag;           // monitor the status of returning functions
HMIDIOUT device;

union { unsigned long word; unsigned char data[4]; } message;
union { unsigned long word; unsigned char data[8]; } message1;

int midi_main(int argc, char** argv) {

	
	// variable which is both an integer and an array of characters:

	// message.data[0] = command byte of the MIDI message, for example: 0x90
	// message.data[1] = first data byte of the MIDI message, for example: 60
	// message.data[2] = second data byte of the MIDI message, for example 100
	// message.data[3] = not used for any MIDI messages, so set to 0
	message.data[0] = 153;  // MIDI note-on message (requires to data bytes)
	message.data[1] = 60;    // MIDI note-on message: Key number (60 = middle C)
	message.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
	message.data[3] = 0;     // Unused parameter

	// Assign the MIDI output port number (from input or default to 0)
	if (argc < 2) {
		midiport = 0;   //0 = Virtual Midi Synth - 1 = Microsoft GW Synth...
	}
	else {
		midiport = atoi(argv[1]);
	}
	printf("MIDI output port set to %d.\n", midiport);

	// Open the MIDI output port
	flag = midiOutOpen(&device, midiport, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("Error opening MIDI Output.\n");
		return 1;
	}

	//// Main event loop
	//printf("Press \"q\" to quit.\n");
	////while (1) {         // event loop
	//	if (kbhit()) {   // If a key on the computer keyboard has been pressed 
	//		ckey = getch();
	//		if (notestate == 0) {
	//			// Note is currently off, turn on note.
	//			message.data[2] = velocity;
	//			notestate = 1;
	//			printf("Note turned ON.\n");
	//			//midi1_noteout();
	//		}
	//		else {
	//			// Note is currently on, turn off note.
	//			message.data[2] = 0;  // 0 velocity = note off
	//			notestate = 0;
	//			printf("Note turned OFF.\n");
	//		}
	//	//	flag = midiOutShortMsg(device, message.word);
	//		if (flag != MMSYSERR_NOERROR) {
	//			printf("Warning: MIDI Output is not open.\n");
	//		}
	//		//if (ckey == 'q') break;
	//	}
	////}

	// turn any MIDI notes currently playing:
	//midiOutReset(device);

	// Remove any data in MIDI device and close the MIDI Output port
	//midiOutClose(device);

	return 0;
}
void midi1_reset() {
	midiOutReset(device);
	midiOutClose(device);
}

void midi1_noteout(int chan,int noten,int velo) {
	//message.data[0] = 144;  // MIDI note-on message (requires to data bytes)
	

	message.data[0] = 144;  // MIDI note-on message (requires to data bytes)
	message.data[1] = noten;    // MIDI note-on message: Key number (60 = middle C)
	message.data[2] = 100;   // MIDI note-on message: Key velocity (100 = loud)
	message.data[3] = 0;
	flag = midiOutShortMsg(device, message.word);
}
void midi1_all_notesoff() {
	for (int j = 0; j < 15; j++) {
		message.data[0] = 176 + j;
		message.data[1] = 123;  //ALL notes off
		message.data[2] = 0;  //ALL notes off
		//message.data[3] = 0;
		flag = midiOutShortMsg(device, message.word);
	}

}

void midi1_sendPrgChange(int thechannel, int prgnumber) {
	message.data[0] = 192 + thechannel;
	message.data[1] = prgnumber;
	flag = midiOutShortMsg(device, message.word);
}


void midi1_close() {
	// turn any MIDI notes currently playing:
	midiOutReset(device);

	// Remove any data in MIDI device and close the MIDI Output port
	midiOutClose(device);
}

void sendMidiBank(int thechannel, int thebank) {
	 
	message1.data[0] = 176 + thechannel; //0-15;
	message1.data[1] = 0;  //ALL notes off
	message1.data[2] = thebank;  //ALL notes off
		   
	//message1.data[3] = 32;
	//message1.data[4] = 0;  //ALL notes off
	//message1.data[5] = 192 + thechannel;
	//message1.data[6] = theprg;

	flag = midiOutShortMsg(device, message1.word);
	//printf("OOO");
	//flag = midiOutShortMsg();
	//flag = midiOutMessage(device,message1.word,8,8);
   //ALL notes off
}
/* Windows I/O functions used in this program:
 *
 * Keyboard Console Functions:
 * int kbhit(void) -- Returns true if a key on the computer keyboard has
 *                    been pressed, or false if no key has been pressed.
 * int getch(void) -- Returns the key which has been pressed on the computer
 *                    keyboard.  Returns -1 if there was not key press.
 *
 * MIDI Output Functions:
 * midiOutOpen     -- http://msdn.microsoft.com/library/en-us/multimed/htm/_win32_midioutopen.asp
 * midiOutShortMsg -- http://msdn.microsoft.com/library/en-us/multimed/htm/_win32_midioutshortmsg.asp
 * midiOutClose    -- http://msdn.microsoft.com/library/en-us/multimed/htm/_win32_midioutclose.asp
 * midiOutReset    -- http://msdn.microsoft.com/library/en-us/multimed/htm/_win32_midioutclose.asp
 */

