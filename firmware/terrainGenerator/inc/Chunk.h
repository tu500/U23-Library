#include <stdio.h>
#include <Drawing.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <game/Game.h>

static inline int genRand(int seed, int x, int y)
{
	return ((x << 16) | (y & 0xffff))^seed;
}

#define chunkSizeSide 9
#define chunkSize chunkSizeSide*chunkSizeSide

#define randCoal 10
#define randIron 30
#define randGold 70

#define mineralsCount 10

struct tile
{
	int x;
	int y;
	int iD;
};

struct chunk
{
	int seed;
	int x;
	int y;
	struct tile tiles[9*9];
};

struct chunk genNewChunk(int x, int y, int seed);
void drawChunk(Bitmap *b, struct chunk c);
Pixel getRGBFromiD(int iD);
void calculateMinerals(struct chunk *c);
void generate(int rX, int rY, int maxNum, int iD, struct chunk *c);
int GetNewRandomInt();
static inline int genRand(int seed, int x, int y);