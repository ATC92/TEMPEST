///////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "animation.h"
///////////////////////////////////////////////////////////
typedef enum _veyxList
{
    vL_DRALIK = 1,
}VeyxList;

typedef enum _veyxType
{
    vT_NONE_TYPE = -1,
    vT_FIRE,                // 0
    vT_AQUA,                // 1
    vT_ELECTRIC,            // 2
    vT_GRASS,               // 3
    vT_ROCK,                // 4
    vT_FLY,                 // 5
    vT_STEEL,               // 6
    vT_POISON,              // 7
    vT_DARK,                // 8
    vT_LIGHT,               // 9
    vT_DRAGON,              // 10
    vT_ECHO                 // 11
}VeyxType;

typedef struct _veyx
{
    char name[20];
    char origin[100];
    char description[255];
    uint8_t life;
    uint8_t mana;
    uint8_t speed;
    uint8_t defense;
    uint8_t physical_attack;
    uint8_t magic_attack;
    VeyxType type[2];

    Texture2D iconText;
    SpriteAnimation* animation;
    
}Veyx;
////////////////////////////////////////////////////////////
///< Public declaration
extern Veyx* VeyxRegistry;
extern size_t countVeyx;
////////////////////////////////////////////////////////////
/**
 * 
 */
void InitVeyxRegistry(void);
/**
 * 
 */
void LoadVeyxData(char* path);
/**
 * 
 */
void DestroyVeyxRegistry(void);
///////////////////////////////////////////////////////////
