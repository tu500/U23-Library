#include <Player.h>

#include <string.h>

////////////////////////////////////
////// ITEM DEFINITIONS ////////////


//                      INVTA,SPD,SPW,MDM,INV,  PRZ
Item shoesStart =       {   1,  0,  0,  0,  0,      0, "Start Shoes", "The Shoes you start with."};
Item pickaxeStart =     {   1,  2, -1,  0,  0,      0, "Start Pickaxe", "The Pickace you start with."};
Item backpackStart =    {   0, -1, -1,  0,  2,      0, "Start Backpack", "The Backpack you start with."};

Item shoesSlow =        {   2,  1,  3,  1,  0,    300, "Slow Shoes", "Fairly slow shoes. They speed you up somewhat."};
Item shoesFast =        {   4,  2,  5,  2,  0,    700, "Fast Shoes", "Quite good shoes you might want to take for a walk."};
Item shoesTurbo =       {   7,  3,  9,  3,  0,   1100, "Turbo Shoes", "Very good shoes that make you feel incredibly fast."};

Item pickaxeSlow =      {   3,  4, -2,  2,  0,    400, "Slow Pickaxe", "A weak Pickaxe. There are better ones."};
Item pickaxeFast =      {   5,  7, -3,  4,  0,    700, "Fast Pickaxe", "Quite good pickaxe. It gets the job done well."};
Item pickaxeTurbo =     {   9, 11, -4,  7,  0,   1300, "Turbo Pickaxe", "Awesomely fast pickaxe. You're blazing through rock."};

Item backpackSmall =    {   0, -2, -2,  1,  8,    500, "Small Backpack", "It can barely hold more than your equiptment."};
Item backpackMedium =   {   0, -3, -3,  3, 16,    900, "Medium Backpack", "It should get you through a few minutes of mining."};
Item backpackBig =      {   0, -4, -4,  6, 26,   1200, "Big Backpack", "This backpack should hold all you'd ever want to carry."};
Item backpackHuge =     {   0, -5, -5, 10, 33,   1900, "Huge Backpack", "This backpack can probably hold more minerals than our world has."}:


////////////////////////////////////

///////////////////////////
/////   Starting Values ///

static const int startSpeedDig = 3;
static const int startSpeedWalk = 10;
static const int startMaxDepth = 25;
static const int startInventorySize = 1;
static const int startMoney = 0;


///////////////////////////

void initPlayer(Player *p){
    *p=(Player){
        startSpeedDig,
        startSpeedWalk,
        startMaxDepth,
        startInventorySize,
        startMoney
    };
    listInsert(&p->inventory, &shoesStart);
    listInsert(&p->inventory, &pickaxeStart);
    listInsert(&p->inventory, &backpackStart);
}


float getSpeedWalk(Player *p){
    float speed = p->speedWalk;
}

void itemBuy(Player *p, Item *i){
    int newmoney = p->money -= i->prize;
    int invspace = 
    if( newmoney >= 0){

        updateItems(p);
    }
}

void validatePlayerValues(Player *p){
    if(p->speedDig <= 0) p->speedDig = 1;
    if(p->speedWalk <= 0) p->speedWalk = 1;
    if(p->maxDepth <= 0) p->maxDepth = 1;
    if(p->inventorySize <= 0) p->inventorySize = 1;    
}

void updateItems(Player *p){
    p->speedDig = startSpeedDig;
    p->speedWalk = startspeedWalk;
    p->maxDepth = startMaxDepth;
    p->inventorySize = startInventorySize;

    for(list_el *i = p->inventory.head; i != NULL; i = i->next){
        p->speedDig += ((Item*)i->val)->speedDigMod;
        p->speedWalk += ((Item*)i->val)->speedWalkMod;
        p->maxDepth += ((Item*)i->val)->maxDepthMod;
        p->inventorySize += ((Item*)i->val)->inventorySizeMod;
    }
    validatePlayerValues(p);
}

int getFreeInvSpace(Player *p){
    int space = p->inventorySize;
    for(list_el *i = p->inventory.head; i != NULL; i = i->next){
        space -= ((Item*)i->val)->inventorySizeTaken;
    }

}