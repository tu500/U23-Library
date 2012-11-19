
#include <Player.h>
#include <string.h>

////////////////////////////////////
////// ITEM DEFINITIONS ////////////


Item startShoes = {1,0,0,0,0};
Item startPickAxe = {1,5,-3,0,0};
Item startBackpack = {0,-1,-1,0,5};

////////////////////////////////////

///////////////////////////
/////   Starting Values ///

static const int startSpeedDig = 3;
static const int startSpeedWalk = 10;
static const int startMaxDepth = 25;
static const int startInventorySize = 5;
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

