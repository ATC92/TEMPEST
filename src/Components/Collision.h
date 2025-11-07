//////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////
/// TEMPEST Lib
#include "../Engine/Flags.h"

#include "Entity.h"
#include "../Utils/VecMath.h"
//////////////////////////////////////////////////////////////
typedef enum _typeCollision
{
    _COLLISION_BOX,
    _TRIGGER_BOX
}TypeCollision;
//////////////////////////////////////////////////////////////
/**
 * @brief 
 * 
 */
bool SystemAABBMid(Entity* Source, Entity* Target, bool r, TypeCollision tc);
/**
 * @brief Update the collision movement of the entity
 * 
 * @param Entity* entiy     ///< The Entity to update the collision movement
 * 
 * @return @n `Void`
 */
void SyncCollisionBox(Entity*);
//////////////////////////////////////////////////////////////