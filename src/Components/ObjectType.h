///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Engine/Flags.h"
#include "Animation.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////< Function Pointer
typedef void (*UseFn)(void *self, void* dest);

////////////////////////< DICE
typedef enum _rarity
{
    NORMAL = 1,
    RARE,
    SUPER_RARE,
    SUPER_EXTRA_RARE
}Rarity;

typedef enum _typDice
{
    D4 = 4,
    D6 = 6,
    D8 = 8,
    D10 = 10,
    D12 = 12,
    D20 = 20
}DiceType;

typedef struct _dice
{
    char name[5];
    DiceType type;
    size_t amount;
    Rarity rarity;
    Texture2D icon;
    Rectangle sizeDice;
    Rectangle boundingBox;
}Dice;
////////////////////////< CART 
typedef enum _typeCard
{
    CARD_HEAL,
    CARD_DEBUFF_DEFESE,
    CARD_BUFF_DEFENSE,
    CARD_DEBUFF_SPEED,
    CARD_BUFF_SPEED,
    CARD_DEBUFF_ATTACK,
    CARD_BUFF_ATTACK,
    CARD_CLEANSE,
    CARD_SPECIAL_POLINIZAR,
    CARD_MAX_TYPES
}CardType;

typedef enum _typeActionCard
{
    ACTION_CARD_TEAM,
    ACTION_CARD_ENEMY,
    ACTION_CARD_ALL
}ActionCard;

typedef struct _cart
{
    char name[50];
    char descEffect[255];
    CardType type;
    ActionCard actionCard;
    size_t amount;
    size_t cooldown;
    Rarity rarity;
    Texture2D* cardTexture;
    Rectangle sizeCard;
    Rectangle boundingBox;
}Card;
////////////////////////< OBJECT
typedef enum _objectType {
    OBJ_NONE = -1,
    OBJ_DICE,
    OBJ_CARD
}ObjectType;

typedef struct _obj
{
    ObjectType type;
    union {
        Dice dice;
        Card card;
    };
    UseFn accion;
}Object;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////