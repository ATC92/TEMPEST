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
 * @brief Structure for Player entity.
 * 
 * ---
 * 
 * @param char*     <NAME>          ///< Name of the entity Enemy
 * @param float     <HEALTH>        ///< Health of the entity Enemy
 * @param float     <ARMOR>         ///< Armor of the entity Enemy
 * @param float     <SPEED>         ///< Speed of the entity Enemy
 * @param float     <EXPERIENCE>    ///< Experience of the entity Enemy
 * @param Vector2   <POSITION>      ///< Position { X , Y }
 */
typedef struct _Player
{
    char* name;         ///< Name of the entity Player
    float health;       ///< Health of the entity Player
    float armor;        ///< Armor of the entity Player
    float speed;        ///< Speed of the entity Player
    float exp;          ///< Experience of the entity Player
    Vector2 position;   ///< Vector2D position {X,Y}
}Player;
/**
 * @brief Structure for Enemy entity.
 * 
 * ---
 * 
 * @param char*     <NAME>          ///< Name of the entity Enemy
 * @param float     <HEALTH>        ///< Health of the entity Enemy
 * @param float     <ARMOR>         ///< Armor of the entity Enemy
 * @param float     <SPEED>         ///< Speed of the entity Enemy
 * @param float     <CRITICAL>      ///< Critical of the entity Enemy
 * @param float     <EXPERIENCE>    ///< Experience of the entity Enemy
 * @param Vector2   <POSITION>      ///< Position { X , Y }
 */
typedef struct _npc
{
    char* name;         ///< Name of the entity Enemy
    float health;       ///< Health of the entity Enemy
    float armor;        ///< Armor of the entity Enemy
    float speed;        ///< Speed of the entity Enemy
    float crit;         ///< Critical of the entity Enemy
    float exp;          ///< Experience of the entity Enemy
    Vector2 position;   ///< Position {X,Y}
}NPC;
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
    Player _player;                 ///< Player struct
    NPC _npc;                       ///< NPC struct
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

