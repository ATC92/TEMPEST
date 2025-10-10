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
    vT_FIRE,
    vT_AQUA,
    vT_ELECTRIC,
    vT_GRASS,
    vT_ROCK,
    vT_FLY,
    vT_STEEL,
    vT_POISON,
    vT_DARK,
    vT_LIGHT,
    vT_DRAGON,
    vT_ECHO
}VeyxType;

typedef struct _veyx
{
    char* name;
    char* origin;
    char* description;
    uint8_t life;
    uint8_t mana;
    uint8_t speed;
    uint8_t defense;
    uint8_t physical_attack;
    uint8_t magic_attack;
    VeyxType type[2];

    SpriteAnimation animation;
    
}Veyx;
///////////////////////////////////////////////////////////
///< Public declarations
extern Veyx* VeyxRegistry;
///////////////////////////////////////////////////////////
/**
 * 
 */
Veyx GetVeyx(VeyxList list);
/**
 * 
 */
void LoadVeyxData(char* path);
/**
 * 
 */

///////////////////////////////////////////////////////////
