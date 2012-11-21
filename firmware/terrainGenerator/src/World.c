#include <stdio.h>
#include <../inc/Chunk.h>
#include <../inc/World.h>
#include <Drawing.h>
#include <game/Font.h>
#include <game/Game.h>
#include <game/Debug.h>

struct world
{
	int seed;
	struct chunk chunks[10];
};

#define sizeX 3
#define sizeY 2

#define size sizeX*sizeY

int genNewSeed(void)
{
	int i = 0;
	int ret = 0;

	int counter = 0;
	while(i < 80 && counter < 10)
	{
		i = GetRandomInteger() % 100;

		ret += GetRandomInteger() % 50;

		counter++;
	}

	return ret;
}

struct world *genNewWorld(void)
{
	struct world *theWorld;

	theWorld = malloc(sizeof(struct world));
	if(theWorld == NULL)return NULL;

	int seed = genNewSeed();
	srand(seed);

	theWorld->seed = seed;

	int i3 = 0;
	for(int i = 0; i < sizeY; i++)
	{
		for(int i2 = 0; i2 < sizeX; i2++)
		{
			theWorld->chunks[i3] = genNewChunk(i2*chunkSizeSide, i*chunkSizeSide, seed);
			//free(theWorld->chunks[i3]);
			i3++;
		}
	}

	SetLEDs(1 << 3);

	//theWorld->chunks = genNewChunk(0, 0);

	//free(theWorld);

	return theWorld;
}

void drawWorld(Bitmap *b, struct world *w)
{
	if(w == NULL)
	{
		//DrawText(b, "blub", 100, 100);
		return;
	}

	for(int i = 0; i < size; i++)
	{
		drawChunk(b, w->chunks[i]);
	}

	//drawChunk(b, w->chunks);
}
