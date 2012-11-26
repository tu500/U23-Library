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

  	struct chunk c = genNewChunk(1, 1, 666);
  	struct chunk *ptr = &c;
  	ptr->tiles[5].iD = 0;

  	saveChunk(ptr);

  	struct chunk *c2 = loadChunk(0, 0, 10);
  	if(c2->x == 1)
  	{
  		SetLEDs(1 << 3);
  		Delay(200);
  	}else if(c2->x == 0)
  	{
  		SetLEDs(1 << 2);
  		Delay(200);
  	}else 
  	{
  		SetLEDs(1 << 1);
  		Delay(200);
  	}
}

struct chunk *loadChunk(int x, int y, int height)
{
	char name[7];
	name[0] = '0'; name[1] = ':'; name[2] = 'c'; name[3] = 'k'; name[4] = '_'; name[5] = x; name[6] = y;

	FILE* file = fopen(name, "r+");
	if(!file) 
	{
		fclose(file);
		return NULL;
	}

	struct chunk *c;
	int res = fread(c, 1, sizeof(struct chunk), file);

	if(!res) 
	{
		if(ferror(file))
			printf("Error occured\r\n");
		if(feof(file))
			printf("EOF occured\r\n");
		perror("fread()");

		return NULL;
	}

	while(res < sizeof(struct chunk))
	{
		res+=fread(c, 1, sizeof(struct chunk)-res, file);
	}

	return c;
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
		//exit(0);
	}
	readcontent[res] = '\0';

	printf("Read raw: %s\n", readcontent);

	bool b = false;

	for(int i = 0; i < 1024; i++)
	{
		if(readcontent[i] == 's')
		{
			b = true;
			break;
		}
	}

	if(b)
	{
		SetLEDs(1 << 2);
		
	} else
	{
		SetLEDs(1 << 3);
	}

	Delay(100);
}

void saveChunk(struct chunk *c)
{	
	InitializeFilesystem();

	char name[9];
	name[0] = '0'; name[1] = ':'; name[2] = 'c'; name[3] = 'k'; name[4] = '_'; name[5] = '1'; name[6] = '.'; name[7] = '1'; name[8] = '\0';

	FILE* file = fopen("0:ck_1_1", "r+");
	if(!file) 
	{
		fclose(file);
		file = fopen("0:ck_1_1", "w+");
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

	res = fwrite(c, 1, sizeof(struct chunk), file);
	if(!res) {
		perror("fwrite()");
		exit(0);
		//ErrorHandler(file);
		return;
	}

	//free(highscoreBuf);

	//readFromSD(file);

	//readFromSD(file);

	//SetLEDs(1 << 2);
	//Delay(100);

	// //Close file
	 res = fclose(file);
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
