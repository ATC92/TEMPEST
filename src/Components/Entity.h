#pragma once
///< TEMPEST Lib
#include "../Engine/Flags.h"

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
    _ENEMY,
    _NPC,
    _BOSS
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
    int sizeArrayTextures;                  ///< Size of the array of textures
    uint8_t speed;                          ///< Speed of the Entity
    bool isMooving;                         ///< Is the entity moving?
    eLooking eLook;                         ///< Where the entity is looking
    Vector2 position;                       ///< Position {X,Y}
    Vector2 prev_position;                  ///< Previous Position {X,Y}
    Vector2 velocity;                       ///< Velocity of the Entity
    SpriteAnimation* spriteAnimation;       ///< Sprite Animation of Entities
    TypeEntity  typeEntity;                 ///< Type of entity in the ENUM.
    Rectangle sizeRect;                     ///< Rectangle of the Entity
}Entity;
/**
 * @brief Generation of entity atributes
 * 
 * ---
 * 
 * @param TypeEntity       _t      ///< Type of the Entity (Player or Enemy)
 * @param char*     _n      ///< Name of the Entity
 * @param uint8_t   _sp     ///< Speed of the Entity
 * 
 * @return @n `Entity`      ///< Struct main with all parameters    
 * 
 * @note This function generates an entity with the given parameters.
 *       The type of entity is determined by the first parameter.
 *       If the type is _PLAYER, it generates a player entity.
 */
Entity* GenEntity(TypeEntity TypeEntity,char* Name, uint8_t _s);

