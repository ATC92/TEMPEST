#pragma once
///< Extern Libraries
#include "raylib.h"
#include "cJSON.h"
///< C Libraries
#include <string.h>
///< CGame Libraries
#include "../Textures/Textures.h"
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/**
 * @brief struct with the enumeration of where is looking the @n `Entity`
 * 
 * ---
 * 
 * Contains:
 * 
 * @param UP        ///< 0
 * @param RIGHT     ///< 1
 * @param DOWN      ///< 3
 * @param LEFT      ///< 4
*/
typedef enum _eLooking
{
    UP,
    RIGHT,
    DOWN,
    LEFT
}eLooking;
/////////////////////////////////////////////////////////////////////////
/**
 * 
 */
typedef enum _typeEntity
{
    _PLAYER,
    _NPC
}TypeEntity;
/**
 * @brief Main Entity

 * ---

 *  Contain:
 * @param Player            ///< Player struct
 * @param NPC               ///< NPC struct
 * @param eLooking          ///< Where is the Entity looking
 * @param tEntity           ///< List of textures of the entity
*/
typedef struct _Entity
{
    char* name;                     ///< Name of the entity Enemy
    float health;                   ///< Health of the entity Enemy
    float armor;                    ///< Armor of the entity Enemy
    float speed;                    ///< Speed of the entity Enemy
    float crit;                     ///< Critical of the entity Enemy
    float exp;                      ///< Experience of the entity Enemy
    Vector2 position;               ///< Position {X,Y}
    TileMap* _tileMap;              ///< TileMap of the Entities
    int _eLook;                     ///< Where the entity is looking
    HashTable* _HT;                 ///< HashTable to save all Textures.
    TypeEntity  _typeEntity;        ///< Type of entity in the ENUM.
}Entity;
/////////////////////////////////////////////////////////////////////////
/**
 * @brief Generation of entity atributes
 * 
 * ---
 * 
 * @param char*     _n      ///< Name of the Entity
 * @param float     _h      ///< Health of the Entity
 * @param float     _ar     ///< Armor of the Entity
 * @param float     _sp     ///< Speed of the Entity
 * @param float     _crt    ///< Critical of the Entity
 * 
 * @return @n `Entity`      ///< Struct main with all parameters    
 */
Entity* GenEntity(int,char*,float,float,float,float);

