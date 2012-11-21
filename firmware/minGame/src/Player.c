#include "Player.h"

#include <string.h>
#include <stdbool.h>

////////////////////////////////////
////// ITEM DEFINITIONS ////////////


//                       INVTA, SPD, SPW, MDM,   INV,    PRZ,   NAME,               DESC
Item shoesStart =       {  100,   0,   0,   0,     0,      0,   "Start Shoes",      "The Shoes you start with."};
Item pickaxeStart =     {  100,   2,  -1,   0,     0,      0,   "Start Pickaxe",    "The Pickace you start with."};
Item backpackStart =    {    0,  -1,  -1,   0,   300,      0,   "Start Backpack",   "The Backpack you start with."};

Item shoesSlow =        {  200,   1,   3,   1,     0,    300,   "Slow Shoes",       "Fairly slow shoes. They speed you up somewhat."};
Item shoesFast =        {  400,   2,   5,   2,     0,    700,   "Fast Shoes",       "Quite good shoes you might want to take for a walk."};
Item shoesTurbo =       {  700,   3,   9,   3,     0,   1100,   "Turbo Shoes",      "Very good shoes that make you feel incredibly fast."};

Item pickaxeSlow =      {  300,   4,  -2,   2,     0,    400,   "Slow Pickaxe",     "A weak Pickaxe. There are better ones."};
Item pickaxeFast =      {  500,   7,  -3,   4,     0,    700,   "Fast Pickaxe",     "Quite good pickaxe. It gets the job done well."};
Item pickaxeTurbo =     {  900,  11,  -4,   7,     0,   1300,   "Turbo Pickaxe",    "Awesomely fast pickaxe. You're blazing through rock."};

Item backpackSmall =    {    0,  -2,  -2,   1,   800,    500,   "Small Backpack",   "It can barely hold more than your equiptment."};
Item backpackMedium =   {    0,  -3,  -3,   3,  1600,    900,   "Medium Backpack",  "It should get you through a few minutes of mining."};
Item backpackBig =      {    0,  -4,  -4,   6,  2600,   1200,   "Big Backpack",     "This backpack should hold all you'd ever want to carry."};
Item backpackHuge =     {    0,  -5,  -5,  10,  3300,   1900,   "Huge Backpack",    "This backpack can probably hold more minerals than our world has."};


////////////////////////////////////


//////////////////////////////
/// MINERALS

Mineral mineralInfo[MINERALCOUNT] = {
    //VAL ,WGHT, HP ,PROB,UPPR,LOWR,NAME, DESC 
    {    5,   3,   6, 100,   0,  12,"Coal", "Nice coal."},
    {   35,   7,   9,  70,   5,  18,"Iron", "Some iron. Sells good."},
    {   60,  11,  20,  40,   9,  24,"Gold", "Shiny gold. Worth quite a lot."},
    {  300, 400,  50,  10,  22,  30,"Diamond", "Precious diamons. Arent they beautiful?"}
};





////////////

///////////////////////////
/////   Starting Values ///

static const int startSpeedDig = 3;
static const int startSpeedWalk = 10;
static const int startMaxDepth = 10;
static const int startInventorySize = 100;
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


// float getSpeedWalk(Player *p){
//     float speed = p->speedWalk;
//     return 0;
// }

bool itemBuy(Player *p, Item *i){
    //Check if Item is already owned
    if(listSearch(&p->inventory, i)) return false;
    int newmoney = p->money -= i->prize;
    int newspace = getFreeInvSpace(p) - i->inventorySizeTaken;
    if( newmoney >= 0 && newspace >= 0){
        p->money = newmoney;
        listInsert(&p->inventory, i);
        updateItems(p);
        return true;
    }
    return false;
}

bool itemSell(Player *p, Item *i){
    if(listSearch(&p->inventory, i)){
        listRemoveByValue(p->inventory, i);
        p->money += i->prize*(2/3);
        updateItems(p);
        return true;
    }
    return false;
}


bool mineralPickup(Player *p, Mineral *m){
    int newspace = getFreeInvSpace(p) - mineralInfo[m].weight;
    if(newspace >= 0){
        p->minerals[m]++;
        return true;
    }
    return false;
    
}

bool mineralSell(Player *p, MineralType m, int amount){
    if(p->minerals[m] >= amount){
        p->minerals[m] -= amount;
        p->money += amount * mineralInfo[m].value;
        updateItems(p);
        return true;
    }
    return false;
}

int getMineralAmount(Player *p, MineralType m){
    return p->minerals[m];
}

void validatePlayerValues(Player *p){
    if(p->speedDig <= 0) p->speedDig = 1;
    if(p->speedWalk <= 0) p->speedWalk = 1;
    if(p->maxDepth <= 0) p->maxDepth = 1;
    if(p->inventorySize <= 0) p->inventorySize = 1;    
}

void updateItems(Player *p){
    p->speedDig = startSpeedDig;
    p->speedWalk = startSpeedWalk;
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
    for(int i = 0; i < MINERALCOUNT ; i++){
        space -= p->minerals[i] * mineralInfo[i].weight;
    }
    return space;
}
