//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "../Components/Veyx.h"
#include "../Components/Animation.h"
#include "../Components/Inventory.h"
#include "Textures.h"
#include "EntityTypes.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    eLooking eLook;                         ///< Where the entity is looking
    Vector2 position;                       ///< Position {X,Y}
    Vector2 prev_position;                  ///< Previous Position {X,Y}
    Vector2 velocity;                       ///< Velocity of the Entity
    SpriteAnimation* spriteAnimation;       ///< Sprite Animation of Entities
    Inventory inventory;                    ///< Inventory for entity.
    TypeEntity  typeEntity;                 ///< Type of entity in the ENUM.
    Rectangle boundingBox;                  ///< Rectangle of the Entity
    Rectangle triggerBox;                   ///< Trigger Box
    Veyx veyxInventory[4];                  ///< VeyxInventory
    size_t veyxAlive;                       ///< Size of the array veyxInventory
    size_t cooldownSpecialCard;                       ///< Cooldown for use special card
    bool isMooving;                         ///< Is the entity moving?
    bool isInteraction;
    bool accions[2];                        ///< Interaction type.
    bool hasSpecialCard;                    ///< Has Special Card (Bosses).

    size_t AP;                              ///< Acction Points
}Entity;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern bool PlayerCanMove;

extern Entity* eplayer;
extern Entity** entityPool;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
/**
 * @brief Movement update and Looking of the player
 * 
 * @param Entity*           ///< Player Entity reference
 * @param float             ///< Delta Time for frame-independent movement
 * 
 * @return @n `Void`
 */
void UpdateMovement(Entity*,float);
/**
 * 
 */
void LoadNPCtoMemory(Entity** pool);
/**
 * 
 */
void LoadVeyxList(Entity* entity);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////