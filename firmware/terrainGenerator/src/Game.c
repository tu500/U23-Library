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
#include <TiledMap.h>

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

TiledMap *map;
MapObject player;

bool playerCollision(MapObject *obj, MapObject *target)
{

}

void Init(struct Gamestate* state)
{
	myWorld = genNewWorld();

	map = TiledMap_init(0, 0, 0, NULL);

	player = (MapObject) { .collision = COLLISION_SPRITE };
	player.x = 100;
	player.y = 10;

	//player->moving->onTargetReached = resetStar;
  	player.moving->onCollision = playerCollision;

  	listInsert(&map->objects, &player);
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

	TiledMap_draw(b, map, 0, 0);

	drawWorld(b, myWorld);
	//drawChunk(b, c);

	setFont(fontwhite8);
	//DrawText(b, "blah", 100, 180);

	//drawChunk(b, myChunk);
}
