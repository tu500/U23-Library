
#include <Player.h>
#include <string.h>

////////////////////////////////////
////// ITEM DEFINITIONS ////////////


//						INVTA,SPD,SPW, MD,INV,	PRZ
Item shoesStart = 		{	1,	0,	0,	0,	0,		0};
Item pickaxeStart = 	{	1,	2, -1,	0,	0,		0};
Item backpackStart = 	{	0, -1, -1,	0,	2,		0};

Item shoesSlow = 		{	2,	1,	3,	1,	0,	  300};
Item shoesFast = 		{	4,	2,	5,	2,	0,	  700};
Item shoesTurbo = 		{	7,	3,	9,	3,	0,	 1100};

Item pickaxeSlow = 		{	3,	4, -2,	2,	0,	  400};
Item pickaxeFast = 		{	5,	7, -3,	4,	0,	  700};
Item pickaxeTurbo = 	{	9, 11, -4,	7,	0,	 1300};

Item backpackSmall = 	{	0, -2, -2,	1,	4,	  500};
Item backpackMedium = 	{	0, -3, -3,	3,	8,	  900};
Item backpackBig = 		{	0, -4, -4,	6, 13,	 1200};
Item backpackHuge = 	{	0, -5, -5, 10, 18,	 1900};


////////////////////////////////////

///////////////////////////
/////   Starting Values ///

static const int startSpeedDig = 3;
static const int startSpeedWalk = 10;
static const int startMaxDepth = 25;
static const int startInventorySize = 1;
static const int startMoney = 0;
static const Item* startInventory[3]={&startShoes, &startPickAxe, &startBackpack};


///////////////////////////

void initPlayer(Player *p){
	*p=(Player){
		startSpeedDig,
		startSpeedWalk,
		startMaxDepth,
		startInventorySize,
		startMoney
	};
	memcpy(&(p->inventory), startInventory, sizeof(startInventory));

}