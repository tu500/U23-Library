
#ifndef PLAYER_H
#define PLAYER_H

#define MAXINVENTORYSIZE 100




typedef enum Items{

	STARTSHOES,
	SLOWSHOES,
	FASTSHOES,
	TURBOSHOES,

	STARTPICKAXE,
	SLOWPICKAXE,
	FASTPICKAXE,
	TURBOPICKAXE,

	STARTBACKPACK,
	SMALLBACKPACK,
	MEDIUMBACKPACK,
	BIGBACKPACK,
	HUGEBACKPACK
} Items;


typedef enum MineralTypes{

	MIN_COAL,
	MIN_IRON,
	MIN_GOLD,
	MIN_DIAMOND,
	MINERALCOUNT

}MineralTypes;

typedef struct Item{

	int inventorySizeTaken;
	int speedDigMod;
	int speedWalkMod;
	int maxDepthMod;
	int inventorySizeMod;
	int prize;
} Item;

typedef struct Player{

	int speedDig;
	int speedWalk;
	int maxDepth;
	int inventorySize;
	int money;

	Item* inventory[MAXINVENTORYSIZE];
	int minerals[MINERALCOUNT];

} Player;



void initPlayer(Player *p);

#endif


