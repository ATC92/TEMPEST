///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Inventory.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Inventory InitInventory()
{
    Inventory temp = {0};

    temp.object[0].type = OBJ_DICE;
    strcpy(temp.object[0].dice.name,"D4");
    temp.object[0].dice.type = D4;
    temp.object[0].dice.amount = 5;
    temp.object[0].dice.rarity = NORMAL; 
    // temp.object[0].dice.animation = 
    temp.object[0].dice.icon = LoadIconDice("D4");
    temp.object[0].dice.sizeDice = (Rectangle){.x=0,.y=0,.width = temp.object[0].dice.icon.width, .height = temp.object[0].dice.icon.height};

    temp.object[1].type = OBJ_DICE;
    strcpy(temp.object[1].dice.name,"D6");
    temp.object[1].dice.type = D6;
    temp.object[1].dice.amount = 5;
    temp.object[1].dice.rarity = NORMAL; 
    // temp.object[1].dice.animation = LoadAnimationDice("D6");
    temp.object[1].dice.icon = LoadIconDice("D6");
    temp.object[1].dice.sizeDice = (Rectangle){.x=0,.y=0,.width = temp.object[1].dice.icon.width, .height = temp.object[1].dice.icon.height};

    temp.object[2].type = OBJ_DICE;
    strcpy(temp.object[2].dice.name,"D8");
    temp.object[2].dice.type = D8;
    temp.object[2].dice.amount = 3;
    temp.object[2].dice.rarity = RARE; 
    // temp.object[2].dice.animation = LoadAnimationDice("D8");
    temp.object[2].dice.icon = LoadIconDice("D8");
    temp.object[2].dice.sizeDice = (Rectangle){.x=0,.y=0,.width = temp.object[2].dice.icon.width, .height = temp.object[2].dice.icon.height};

    temp.object[3].type = OBJ_DICE;
    strcpy(temp.object[3].dice.name,"D10");
    temp.object[3].dice.type = D10;
    temp.object[3].dice.amount = 2;
    temp.object[3].dice.rarity = SUPER_RARE;
    // temp.object[3].dice.animation = LoadAnimationDice("D10"); 
    temp.object[3].dice.icon = LoadIconDice("D10");
    temp.object[3].dice.sizeDice = (Rectangle){.x=0,.y=0,.width = temp.object[3].dice.icon.width, .height = temp.object[3].dice.icon.height};

    temp.object[4].type = OBJ_DICE;
    strcpy(temp.object[4].dice.name,"D12");
    temp.object[4].dice.type = D12;
    temp.object[4].dice.amount = 2;
    temp.object[4].dice.rarity = SUPER_RARE; 
    // temp.object[4].dice.animation = LoadAnimationDice("D12");
    temp.object[4].dice.icon = LoadIconDice("D12");
    temp.object[4].dice.sizeDice = (Rectangle){.x=0,.y=0,.width = temp.object[4].dice.icon.width, .height = temp.object[4].dice.icon.height};

    temp.object[5].type = OBJ_DICE;
    strcpy(temp.object[5].dice.name,"D20");
    temp.object[5].dice.type = D20;
    temp.object[5].dice.amount = 1;
    temp.object[5].dice.rarity = SUPER_EXTRA_RARE; 
    // temp.object[5].dice.animation = LoadAnimationDice("D20");
    temp.object[5].dice.icon = LoadIconDice("D20");
    temp.object[5].dice.sizeDice = (Rectangle){.x=0,.y=0,.width = temp.object[5].dice.icon.width, .height = temp.object[5].dice.icon.height};

    return temp;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////