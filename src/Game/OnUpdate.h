#pragma once
///< C/C++ Libraries
#include <math.h>
///< Extern Libraries
#include "raylib.h"
///< CGame Lib
#include "../Entity/Entity.h"
#include "Game.h"
///< Updates the wheel camera [Camera 2D*]
void UpdateCameraWheel(Camera2D*);
/**
 * @brief Update Movement of the Entity Player
        @note This will update the position in the game 2D.
    @param Entity*          ///< The Entity
*/
void updateMovement(Entity*);

