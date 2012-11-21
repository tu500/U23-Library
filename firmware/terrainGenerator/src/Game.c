#include <game/Game.h>
#include <game/Debug.h>
#include <game/Accelerometer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <game/Font.h>
#include "../inc/Chunk.h"
#include "../inc/World.h"

void Init(struct Gamestate*);
void OnEnter(struct Gamestate* state);
void OnLeave(struct Gamestate* state);
void Update(uint32_t);
void Draw(Bitmap *);
void SetLED(uint32_t u);

Gamestate InitState = { Init, OnEnter, OnLeave, Update, Draw };
Game* TheGame = &(Game) {&InitState};

struct world *myWorld; 
//struct chunk *c;

void Init(struct Gamestate* state)
{
	myWorld = genNewWorld();

	//int in = genRand(666, 10, 10);

	//c = genNewChunk(0, 0);
}

void OnEnter(struct Gamestate* state)
{
	
}

void OnLeave(struct Gamestate* state)
{

}

int LEDB = 0;

void Update(uint32_t a)
{
 	if (LEDB == 0)
 	{
 		SetLEDs(1 << 0);
 		LEDB = 1;
 	}else
 	{
 		SetLEDs(1 << 1);
 		LEDB = 0;
 	}

 	Delay(50);
}

void Draw(Bitmap *b)
{
	ClearBitmap(b);

	drawWorld(b, myWorld);
	//drawChunk(b, c);

	setFont(fontwhite8);
	//DrawText(b, "blah", 100, 180);

	//drawChunk(b, myChunk);
}
