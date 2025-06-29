#pragma once
///< C/C++ Libraries
#include <math.h>
///< Extern Libraries
#include "raylib.h"
///< CGame Lib
#include "../Entity/Entity.h"
#include "Game.h"
/**
 * @brief Mouse Wheel Update
 * 
 * @param Camera2D*           ///< Camera 2D reference
 * 
 * @return @n `Void`  
 */
void UpdateCameraWheel(Camera2D*);
/**
 * @brief Movement update and Looking of the player
 * 
 * @param Entity*           ///< Player Entity reference
 * 
 * @return @n `Void`
 */
void updateMovement(Entity*);
/**
 * @brief Update Collision between two entities
 * 
 * @param Entity* eplayer   ///< The Entity Player
 * @param Entity* eEnemy    ///< The Entity Enemy
 * 
 * @return @n `Void`
 */
void UpdateCollision(Entity*,Entity*);
/**
 * @brief Update the collision movement of the entity
 * 
 * @param Entity* entiy     ///< The Entity to update the collision movement
 * 
 * @return @n `Void`
 */
void UpdateCollisionMovement(Entity*);
/**
 * @brief Resolve the collision between two entities
 * 
 * @param Entity* eplayer   ///< The Entity Player
 * @param Entity* eEnemy    ///< The Entity Enemy
 * 
 * @return @n `Void`
 */
void ResolveCollision(Entity*,Entity*);


