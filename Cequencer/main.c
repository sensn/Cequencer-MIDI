//#include "Header.h"
//#include <cstddef>
#include <stdlib.h>
#include "rlutil.h"
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)



#define MAX 35
#define X_COUNT 8
#define Y_COUNT 16



struct dat
{
	int posX;
	int posY;
	int triggerX;
	int notenumber;
	char playerChr;

	char name[MAX];

	struct date {
		int day;
		int month;
		int year;
	}date;
};

typedef struct {
	int trigger[16];
	int notenumber;
	int vel;
	int channel;
}Room;


typedef struct {
	int screenX;
	int screenY;
	Room room[3];

}House;

//***
typedef struct IDirectSound* LPDIRECTSOUND;

//***


int playSequence(struct dat lib[17][9]);

//int input_Buffer_Events_main();
int call_raster_main();
void draw_buttons(int xb, int yb, int yoffset1);

extern int posX;
extern int posY;
extern int myMouseB;
extern int thebpm;
int thebpm = 150;

double ms;
double dur;
double swing = 0;
double theswing = 0.33;




//asd
int xs = X_COUNT + 1;
int ys = Y_COUNT + 1;

int yoffset = 1;
int s_main(char** fpath, int nr);
char* fpath[] = { "C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\snare.wav", "C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\kick.wav" };

struct dat lib[X_COUNT + 1][Y_COUNT + 1] = { '\0' };

DWORD WINAPI ThreadFunc(void* data) {
	playSequence(lib);
	// Do stuff.  This will be the first function called on the new thread.
	// When this function returns, the thread goes away.  See MSDN for more details.
	return 0;
}
DWORD WINAPI ThreadFunc1(void* data) {
	s_main(fpath, 0);
	
	// Do stuff.  This will be the first function called on the new thread.
	// When this function returns, the thread goes away.  See MSDN for more details.
	return 0;
}

int main(int argc, char argv[]) {
	
	//HRESULT WINAPI DirectSoundCreate(LPGUID lpGuid, LPDIRECTSOUND * ppDS, LPUNKNOWN  pUnkOuter);

	HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);   //Playsequence in own Thread
	midi_main(0, 0);													//open Midi Port, set up Midi
	//getch();
	call_raster_main();													// Print Raster etc..								
	

	
	
	//s_main(fpath, 0);
	//s_main(fpath, 1);
	//printf("this is the end");
	//input_Buffer_Events_main();
//	setColor(10);  //				reset to white;

}

int call_raster_main() {

	int tx = 0;  //tmp for trigger print

	char player[2] = { 'X','O' };
	int p = 2;
	int eingabe = 1;
	int yoffset = 1;
	//lib[1][1].posY = 1;
	//lib[1][1].posX =1;
	//lib[1][1].playerChr ='x';
	//playSequence(lib);
	HANDLE    hIOMutex = CreateMutex(NULL, TRUE, NULL);

	
	do
	{
		WaitForSingleObject(hIOMutex, INFINITE);
		system("cls");  // Clean the screen!
						//Print the Rastaman!
		setColor(7);
		for (int i = 0; i < yoffset; i++) {
			puts("");

		}
		for (size_t x = 0; x < ys*2-2; x +=2) {
			SetPosition(x, yoffset);
			printf(" %c", '_');
			//printf(" ");
			/*SetPosition(x+1, yoffset);
			printf("%c ",'_');*/
		}
		puts("");
		for (size_t x = 1; x < xs; x++) {
			for (size_t y = 1; y < ys; y++) {
				//(y>1)? SetPosition(y+y, x + yoffset): 
					SetPosition(y + y-2, x + yoffset);
			
				printf("|");
				
				//printf("%c", ((lib[x][y].posX > 0 && lib[x][y].posY > 0) && (x == lib[x][y].posX && y == lib[x][y].posY)) ? lib[x][y].playerChr : '_');
				if ((lib[x][y].posX > 0 && lib[x][y].posY > 0) && (x == lib[x][y].posX && y == lib[x][y].posY)) {
					setColor(10);
					printf("%c", lib[x][y].playerChr);
					setColor(7);
				}
				else {
					printf("%c", '_');
				}

				//printf("%s", ((lib[x][y].posX >0 && lib[x][y].posY >0) && (x == lib[x][y].posX && y == lib[x][y].posY)) ? "T" :"_" );
				if (y == ys - 1) {
					printf("|");
				}
				
			}
		puts("");
		}

		draw_buttons(1, 3, 4);
		draw_buttons(1, 3, 6);
		/*printf("MOUSElib X: %d Y:%d\n", lib[posX][posY].posX, lib[posX][posY].posY);
		printf("MOUSEPOS X: %d Y:%d", posX, posY);*/
		do
		{
			
		} while (!input_Buffer_Events_main());
		//	setColor(10);
			//printf("MOUSE X: %d Y:%d",posX,posY);
		//if (input_Buffer_Events_main()) {
		//	if (posX < xs && posY < ys) {
		if (myMouseB != 0) {
			tx = posX;
			
				if (posX == 1) {

				}
				else if (posX > 1) {
					posX = posX - (posX / 2);                                // Cast Mousecklick to cells
				}
				posY = posY - yoffset;
				if (posX < Y_COUNT + 1 && posY < X_COUNT + 1 + yoffset && posY> yoffset-1) {          //Click inside Rectangle?
				lib[posY][posX].posY = posX;
				lib[posY][posX].posX = posY;
				if (myMouseB == 1) {
					lib[posY][posX].playerChr = '*';
				}
				else if (myMouseB == 2) {
					lib[posY][posX].playerChr = ' ';
					//	midi1_close();
				}

				lib[posY][posX].triggerX = tx;
			}
			//}
		//	ReleaseMutex(hIOMutex);
		
	/*	else {                           //Mouseclick outside struct
			printf("outyout");
		}*/

		}
		//printf("MOUSE");
	} while (eingabe != 0);

	return 1;
}

void setBpm(int updown) {
	(updown > 0) ? thebpm++ : thebpm--;

	ms = ((60000.0 / (double)thebpm) / (double)4);  //Milliseconds per quarternote
	//ms = 125;  //Millisecond per quarternote
	dur = (ms / 1000) * CLOCKS_PER_SEC;
	//printf("MILLIS PER QUATER:%f\n", ms);
	//printf("ms/Clocks :%f\n", dur);
	SetPosition(0, 0);
	printf("%d BPM", thebpm);
}

int playSequence(struct dat lib[X_COUNT + 1][Y_COUNT + 1]) {
	HANDLE    hIOMutex = CreateMutex(NULL, TRUE, NULL);

	WaitForSingleObject(hIOMutex, INFINITE);
	
	setBpm(1);
	
	
	
	_Bool isplaying = 1;

	//double time_spent = 0.0;
	
	long begin = clock();
	// do some stuff here
	//Sleep(3);
	//long end = clock();
	double theend = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	//time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
	//	printf("Time elpased is %f seconds", time_spent);

		//
	int index = 1;

//******MS

	//
	for (size_t x = 1; x < xs; x++) {
		for (size_t y = 1; y < ys; y++) {
			lib[x][y].notenumber = 35 + x;    //assign Notenumbers
		}
	}
		//if (myHouse.room[i].trigger[index]) {
		
	House myHouse = { 640,400,.room[0] = {{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},64,127,1},
							   .room[1] = {{1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},64,127,1},
							   .room[2] = {{1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},64,127,1} };
	//printf("THE ROOM: %d\n", myHouse.room[1].notenumber);

	while (isplaying) {
		begin = clock();
		if ((double)begin > theend) {

			theend = (double)clock() + dur + (dur * (swing));
			swing = (index % 2) ? 0 : theswing;
			//printf("%f", swing);
			//printf("*");									 //Do things...
			SetPosition(index * 2 - 1, 1);		//cursorPosition as Step Indicator   Curser
			midi1_all_notesoff();
			//midi1_reset();
			for (int i = 1; i < xs; i++) {
				
				//if (myHouse.room[i].trigger[index]) {
				if (lib[i][index].playerChr == '*') {
					
				// SetPosition(lib[i][index].triggerX, X_COUNT+1+ yoffset + i);
				// SetPosition(lib[i][index].triggerX, 1);
				// printf("T");

				// printf("X: %d Y: %d",i, index);
				// s_main(fpath, 0);
				 midi1_noteout(1, lib[i][index].notenumber,100);

				// HANDLE thread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);

					//PlaySound("C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\snare.wav", NULL, SND_ASYNC);  //   PLAY THE SOUND using win api
					//PlaySound("C:\\Users\\ATN_70\\Desktop\\C2_Ausbildung-master\\C2_Ausbildung\\kick.wav", NULL, SND_ASYNC);
				
				}
				else {
					//	printf("-");
				}
				
			}//for

			

			index++;
		} //if beginn > end


		if (index == 17) { //reset things
			//tickindex = 0;
			index = 1;
			//system("cls");
			//puts("");
			ReleaseMutex(hIOMutex);
		}

	}

}

void draw_buttons(int xb, int yb,int yoffset1) {
	/*for (int i = 0; i < yoffset; i++) {
		puts("");

	}*/
	for (size_t x = 0; x < (yb +1) * 2 - 2; x += 2) {
		SetPosition(x, yoffset+X_COUNT+1+yoffset1);
		printf(" %c", '_');
		//printf(" ");
		/*SetPosition(x+1, yoffset);
		printf("%c ",'_');*/
	}
	puts("");
	for (size_t x = 1; x < xb+1; x++) {
		for (size_t y = 1; y < yb+1; y++) {
			//(y>1)? SetPosition(y+y, x + yoffset): 
			SetPosition(y + y - 2, x + yoffset + X_COUNT + 1 + yoffset1);

			printf("|");

			//if
			//else
			printf("%c", '_');


			if (y == yb +1 - 1) {
				printf("|");
			}
			//printf("%c", ((lib[x][y].posX > 0 && lib[x][y].posY > 0) && (x == lib[x][y].posX && y == lib[x][y].posY)) ? lib[x][y].playerChr : '_');
			
			/*if ((lib[x][y].posX > 0 && lib[x][y].posY > 0) && (x == lib[x][y].posX && y == lib[x][y].posY)) {
				setColor(10);
				printf("%c", lib[x][y].playerChr);
				setColor(7);
			}
			else {
				printf("%c", '_');
			}*/

			//printf("%s", ((lib[x][y].posX >0 && lib[x][y].posY >0) && (x == lib[x][y].posX && y == lib[x][y].posY)) ? "T" :"_" );
			
		}
		puts("");

	}


}