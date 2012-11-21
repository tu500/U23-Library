#include <stdio.h>
#include <../inc/Chunk.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <Drawing.h>
#include <game/Font.h>
#include <platform/Random.h>

int GetNewRandomInt()
{
	//srand(666);
	return rand();
}

int getRandomPosition(int seed, int x, int y)
{
	int r = genRand(seed, x, y) % chunkSizeSide;
	return r;
}

static int countII = 0; 

void generate(int rX, int rY, int maxNum, int iD, struct chunk *c)
{
	int index = (rY*chunkSizeSide)+rX;

	if(index > chunkSize || iD == 0 || iD > 3) return;

	c->tiles[index].iD = iD;
	countII++;

}

void generateStructure(int maxNum, int iD, struct chunk *c, int random)
{
	int rM = 0;
	int xToAdd = 0;
	int yToAdd = 0;
	int count = 0;

	/*int rX = getRandomPosition(c->seed, c->x, c->y);
	int rY = getRandomPosition(c->seed, c->x, c->y);
	generate((rX+xToAdd), (rY+yToAdd), maxNum, iD, c);
	*/
	int rX = 0, rY = 0;

	//rX = genRand(c->seed, ) & chunkSizeSide;

	while(rM < 90 && count <= maxNum) 
	{
		generate((rX+xToAdd), (rY+yToAdd), maxNum, iD, c);

		rM = genRand(c->seed, rX, rY) % 100;
		xToAdd = (genRand(c->seed, rX, rY) % 3) - 1;
		yToAdd = (genRand(c->seed, rX, rY) % 3) - 1;

		count++;
	}
}

void calculateMinerals(struct chunk *c)
{
	int size = 3;

	int randArray[size]; 	randArray[0] = randCoal; randArray[1] = randIron; randArray[2] = randGold;
	int iDArray[size];	  	iDArray[0] = 1; iDArray[1] = 2;  iDArray[2] = 3;
	int manyArray[size];	manyArray[0] = 15; manyArray[1] = 6; manyArray[2] = 3;

	for(int i = 0; i < mineralsCount; i++)
	{
		for(int j = 0; j < size; j++)
		{
			int rM = genRand(c->seed, c->x, c->y) % 100;

			if(rM % randArray[j] == 0)
			{
				//c.tiles[0].iD = 1;
				generateStructure(manyArray[j], iDArray[j], c, randArray[j]);
			}
		}
	}

	//for(int i = 0; i < 10; i++) c.tiles[i].iD = 1;

	//c.tiles[0].iD = 1;
}

void calcMineral(struct tile *t, int seed)
{
	int r = genRand(seed, t->x, t->y) % 3;
	t->iD = r;
}

void calcAdditional(struct tile *t, struct chunk *c, int *rands, int iD)
{
	int count = 0;

	do
	{
		int rX = (genRand(c->seed+count, t->x, t->y) % 3) - 1;
		int rY = (genRand(c->seed-count, t->x, t->y) % 3) - 1;

		int index = ((t->y)*chunkSizeSide)+t->x;
		index += rY*chunkSizeSide;
		index += rX;

		if(index >= chunkSize)
		{
			count++;
			continue;
		}

		struct tile *t2 = &c->tiles[index];
		t2->iD = iD;
		
		count++;
	}while((genRand(c->seed, t->x, t->y) % 1000) < (rands[iD]/2) && count < mineralsCount);
}

void calcMin(struct chunk *c)
{
	int size = 3;
	int randArray[size]; 	randArray[0] = randCoal; randArray[1] = randIron; randArray[2] = randGold;

	for(int i = 0; i < 9*9; i++)
	{
		struct tile *t = &c->tiles[i];
		if(t == NULL) continue;

		int type = genRand(c->seed, t->x, t->y) % size;
		
		if(type < size && (genRand(c->seed, t->x, t->y) % 1000) < randArray[type])
		{
			t->iD = type + 1;
			calcAdditional(t, c, randArray, type+1);
		}
	}
}

struct chunk genNewChunk(int x, int y, int seed)
{
	struct chunk c;

	/*c = malloc(sizeof(struct chunk)*256*sizeof(struct tile));
	if(c == NULL)return NULL;*/

	c.seed = seed;
	c.x = x;
	c.y = y;

	int index = 0;
	for(int i = 0; i < chunkSizeSide; i++)
	{
		for(int j = 0; j < chunkSizeSide; j++)
		{
			struct tile t;

			t.x = (int)(i+x);
			t.y = (int)(j+y);

			//t.iD = genRand(seed, t.x+c.x, t.y+c.y) % 3;
			t.iD = 0;

			//calcMineral(&t, c.seed);

			c.tiles[index] = (struct tile)t;

			index++;
		}
	}

	calcMin(&c);

	//calculateMinerals(&c);

	//free(c);

	return c;
}

Pixel getRGBFromiD(int iD)
{
	switch(iD)
	{
		case 0: return RGB(100, 100, 100);
		case 1: return RGB(40, 40, 40);
		case 2: return RGB(150, 150, 150);
		case 3: return RGB(50, 230, 255);
		default: return RGB(0, 0, 0);
	}
}

void drawChunk(Bitmap *b, struct chunk c)
{
	/*if(c == NULL)
	{
		setFont(fontwhite8);
		DrawText(b, "blub", 10, 180);
		//return;
	}*/

		setFont(fontwhite8);
		char *highscoreString;
		asprintf(&highscoreString, "%d", genRand(c.seed, 1, 5) % 3);

		//DrawText(b, highscoreString, 10, 180);

		free(highscoreString);

	for(int i = 0; i < 9*9; i++)
	{
	    struct tile t = (struct tile)c.tiles[i];
		DrawFilledRectangle(b, t.x*16, t.y*16, 16, 16, getRGBFromiD(t.iD));
	}
}
