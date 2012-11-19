#include <game/Game.h>
#include <game/Debug.h>
#include <game/Font.h>

#include <stdio.h>
#include <string.h>

#include "Player.h"

#define MAXINVENTORYSIZE 100

void Init(struct Gamestate*);
void OnEnter(struct Gamestate* state);
void OnLeave(struct Gamestate* state);
void Update(uint32_t);
void Draw(Bitmap *);
void isAlive(Bitmap *);



Gamestate InitState = { Init, OnEnter, OnLeave, Update, Draw };
Game* TheGame = &(Game) {&InitState};


static int ticks = 0;

static int tempr = 0;
static int tempb = 0;
static int tempg = 0;



Player p1;


void Init(struct Gamestate* state)
{

}

void OnEnter(struct Gamestate* state)
{
}

void OnLeave(struct Gamestate* state)
{
}

void Update(uint32_t a)
{
	ticks += a;
	ticks %= 255;

	if (GetControllerState1().buttons.Up){
		tempb += 20;
	}
	if (GetControllerState1().buttons.Down){
		tempb -= 20;
	}
	if (GetControllerState1().buttons.Right){
		tempg += 20;
	}
	if (GetControllerState1().buttons.Left){	
		tempg -= 20;
	}
	if (GetControllerState1().buttons.L)	tempr -= 20;
	if (GetControllerState1().buttons.R)	tempr += 20;
}

void Draw(Bitmap *b)
{

	ClearBitmap(b);

	isAlive(b);
}

void isAlive(Bitmap *b){
	DrawFilledRectangle(b, 310,0, 10, 10,RGB(tempr,tempg,tempb));
	DrawFilledRectangle(b, 313,2, 4, 4,RGB(ticks, ticks, ticks));
	if(tempr > 255) tempr = 255;
	if(tempg > 255) tempg = 255;
	if(tempb > 255) tempb = 255;

	if(tempr < 0) tempr = 0;
	if(tempg < 0) tempg = 0;
	if(tempb < 0) tempb = 0;
}



