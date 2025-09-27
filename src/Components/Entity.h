#pragma once
///< Extern Libraries
#include "raylib.h"
///< C Libraries
#include <string.h>
///< CGame Libraries
#include "../Components/animation.h"
#include "Textures.h"
/////////////////////////////////////////////////////////////////////////
/**
 * @brief Enumeration of the directions in which an `Entity` can look.
 * 
 * This enum defines the possible orientations for an `Entity`.
 * 
 * @note The values correspond to directional indices.
 * 
 * Contains:
 * - @c UP        = 0
 * - @c DOWN      = 1
 * - @c RIGHT     = 2
 * - @c LEFT      = 3
 */
typedef enum _eLooking
{
    UP,
    DOWN,
    RIGHT,
    LEFT
}eLooking;
/**
 * @brief struct with the enumeration of the type of @n `Entity`
 * 
 * ---
 * 
 * Contains:
 * 
 * @param _PLAYER   0
 * @param _ENEMY    1
 * 
 * ---
 */
typedef enum _typeEntity
{
    _PLAYER,
    _ENEMY
}TypeEntity;
/**
 * @brief Main Entity

 * ---

 *  Contain:
 * @param Player            Player struct
 * @param NPC               NPC struct
 * @param eLooking          Where is the Entity looking
 * @param tEntity           List of textures of the entity
*/
typedef struct _Entity
{
    char* name;                             ///< Name of the entity
    float health;                           ///< Health of the entity
    float armor;                            ///< Armor of the entity
    float speed;                            ///< Speed of the entity
    float crit;                             ///< Critical of the entity
    float exp;                              ///< Experience of the entity
    int _eLook;                             ///< Where the entity is looking
    int sizeArrayTextures;                  ///< Size of the array of textures
    bool isMooving;                         ///< Is the entity moving?
    Vector2 position;                       ///< Position {X,Y}
    Vector2 prev_position;                  ///< Previous Position {X,Y}
    Vector2 velocity;                       ///< Velocity of the Entity
    TileMap* _tileMap;                      ///< TileMap of the Entities
    SpriteAnimation* spriteAnimation;       ///< Sprite Animation of Entities
    Texture2D* _textureArray;               ///< Array of Textures of the Entity 
    TypeEntity  _typeEntity;                ///< Type of entity in the ENUM.
    Rectangle _rect;                        ///< Rectangle of the Entity
}Entity;
/**
 * @brief Generation of entity atributes
 * 
 * ---
 * 
 * @param int       _t      ///< Type of the Entity (Player or Enemy)
 * @param char*     _n      ///< Name of the Entity
 * @param float     _h      ///< Health of the Entity
 * @param float     _ar     ///< Armor of the Entity
 * @param float     _sp     ///< Speed of the Entity
 * @param float     _crt    ///< Critical of the Entity
 * 
 * @return @n `Entity`      ///< Struct main with all parameters    
 * 
 * @note This function generates an entity with the given parameters.
 *       The type of entity is determined by the first parameter.
 *       If the type is _PLAYER, it generates a player entity.
 */
Entity* GenEntity(int TypeEntity,char* Name,float Health,float Armor,float Speed,float Critical);

