///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "../Engine/Flags.h"

#include "Animation.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////< Function Pointer
typedef void (*UseFn)(void *self);

////////////////////////< DICE
typedef enum _rarity
{
    NORMAL,
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
    // SpriteAnimation animation;
    Texture2D icon;
    Rectangle sizeDice;
    Rectangle boundingBox;
}Dice;
////////////////////////< CART 
typedef enum _typeCart
{
    CART_DEBUFF,
    CART_BUFFER,
    CART_ATTACK,
    CART_DEFENSE,
    CART_HEAL,
    CART_SPECIAL
}CartType;

typedef struct _cart
{
    char name[50];
    char descEffect[255];
    CartType Type;
    size_t amount;
    Rarity rarity;
    Texture2D cartTexture;
    Rectangle sizeCart;
}Cart;
////////////////////////< OBJECT
typedef enum _objectType {
    OBJ_NONE = -1,
    OBJ_DICE,
    OBJ_CART
} ObjectType;

typedef struct _obj
{
    ObjectType type;
    union {
        Dice dice;
        Cart cart;
    };
    UseFn accion;
}Object;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////