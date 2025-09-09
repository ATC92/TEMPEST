#pragma once
///< C/C++ Libraries
#include <math.h>
///< Extern Libraries
#include "raylib.h"
<<<<<<< HEAD
#include "raymath.h"
///< CGame Lib
#include "../Components/Entity.h"
#include "../Components/Collision.h"
#include "../Engine/Engine.h"
// #include "Game.h"
=======
///< CGame Lib
#include "../Entity/Entity.h"
#include "Game.h"
>>>>>>> origin/main
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
<<<<<<< HEAD
 * @param float             ///< Delta Time for frame-independent movement
 * 
 * @return @n `Void`
 */
void UpdateMovement(Entity*,float);
=======
 * 
 * @return @n `Void`
 */
void updateMovement(Entity*);
>>>>>>> origin/main
/**
 * @brief Update Collision between two entities
 * 
 * @param Entity* eplayer   ///< The Entity Player
 * @param Entity* eEnemy    ///< The Entity Enemy
<<<<<<< HEAD
 * @param float dt        ///< Delta Time for frame-independent movement
 * 
 * @return @n `Bool`
 */
bool IsColliding(Entity*,Entity*,float);
=======
 * 
 * @return @n `Void`
 */
void UpdateCollision(Entity*,Entity*);
>>>>>>> origin/main
/**
 * @brief Update the collision movement of the entity
 * 
 * @param Entity* entiy     ///< The Entity to update the collision movement
 * 
 * @return @n `Void`
 */
<<<<<<< HEAD
void SyncCollisionBox(Entity*);
/**
 * @brief Resolve the collision of the entity with a rectangle
 * 
 * @param Entity* entiy     ///< The Entity to resolve the collision
 * @param Rectangle size    ///< The Rectangle to resolve the collision with
 * 
 * @return @n `Void`
 * 
 * @note This function checks if the entity's position is within the bounds of the rectangle and adjusts its position accordingly.
 * If the entity's position is outside the rectangle, it will be moved back to the nearest edge of the rectangle.
 * 
 */
void ClampPlayerToMap(Entity*,Rectangle);
/**
 * @brief Lock the camera to a specific zone
 * 
 * @param camera       Pointer to the Camera2D structure
 * @param zoneSize     Size of the zone to lock the camera to
 * 
 * @return @n `Void`
 * 
 * This function ensures that the camera's target position does not exceed the boundaries of the specified zone size.
 * It adjusts the camera's target position to keep it within the defined zone, preventing it from
 * going out of bounds based on the screen dimensions and camera zoom level.
 * 
 */
void LockCameraToZone(Camera2D*,Rectangle);
=======
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
>>>>>>> origin/main


