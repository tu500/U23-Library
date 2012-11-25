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
#include <game/Filesystem.h>

void Init(struct Gamestate*);
void OnEnter(struct Gamestate* state);
void OnLeave(struct Gamestate* state);
void Update(uint32_t);
void Draw(Bitmap *);
void SetLED(uint32_t u);
void readFromSD(FILE *file);
void saveChunk(struct chunk *c);

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

	player = (MapObject){ .collision = COLLISION_SPRITE };
	player.x = 100;
	player.y = 10;

	//player->moving->onTargetReached = resetStar;
  	player.moving->onCollision = playerCollision;

  	listInsert(&map->objects, &player);

  	struct chunk c = genNewChunk(0, 0, 666);
  	struct chunk *ptr = &c;
  	ptr->tiles[5].iD = 0;

  	saveChunk(ptr);
}

void readFromSD(FILE *file)
{
	char readcontent[1024];
	int res = fread(readcontent, 1, 1023, file);
	if(!res) {
		if(ferror(file))
			printf("Error occured\r\n");
		if(feof(file))
			printf("EOF occured\r\n");
		perror("fread()");
		exit(0);
	}
	readcontent[res] = '\0';

	printf("Read raw: %s\n", readcontent);
}

void saveChunk(struct chunk *c)
{	
	InitializeFilesystem();

	//Open a file
	FILE* file = fopen("0:data", "r+");
	if(!file) {
		fclose(file);
		file = fopen("0:data", "w+");
		if (!file)
		{
			perror("fopen()");
			//ErrorHandler(file);
			exit(0);
			return;
		}
	}

	//ReadHighscore(file);

	// if (newScore > score[0])
	// {
	// 	score[9] = newScore;
	// 	// quick_sort(score, 10);
	// 	// reverse(score, 10);
	// } else {
	// 	ErrorHandler(file);
	// 	return;
	// }

	//Seek to start
	int res = fseek(file, 0, SEEK_SET);
	if(res == -1) {
		perror("fseek()");
		exit(0);
		//ErrorHandler(file);
		return;
	}

	char *highscoreBuf;

	/*for(int i = 0; i < chunkSize; i++)
	{
		if(c->tiles[i].iD == 0)
		{
			asprintf(&highscoreBuf, "%d:%d", c->tiles[i].x, c->tiles[i].y);
		}
	}*/

	asprintf(&highscoreBuf, "%c", 'a');

	printf("WRITE: %s\n", highscoreBuf);

	res = fwrite(highscoreBuf, 1, strlen(highscoreBuf), file);
	if(!res) {
		perror("fwrite()");
		exit(0);
		//ErrorHandler(file);
		return;
	}

	free(highscoreBuf);

	//readFromSD(file);

	//SetLEDs(1 << 2);
	//Delay(100);

	// //Close file
	// res = fclose(file);
	// if(res != 0) {
	// 	perror("fclose()");
	// 	ErrorHandler(file);
	// 	return;
	// }
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
