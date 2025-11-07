#pragma once
///<
#include "../Engine/Flags.h"
///< CGame Lib
#include "../Components/Entity.h"
// #include "../Components/Collision.h"
// #include "../Engine/Engine.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
 * 
 */
void UpdatePrevPosition(Entity* player, Entity** pool, size_t sizePool);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

