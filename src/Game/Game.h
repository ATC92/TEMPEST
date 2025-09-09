#pragma once
///< C/C++Lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///< Extern Lib
#include "raylib.h"
#include "raymath.h"
///< CGame Lib
#include "OnUpdate.h"
#include "../Utils/Vector.h"
#include "../Components/Entity.h"
#include "../Components/Map.h"
#include "../Components/Collision.h"
#include "../Utils/Algorithms.h"
#include "../Components/LoadTextures.h"
#include "../Utils/Information.h"
#include "../Scenes/ScenesManager.h"
#include "../Scenes/MenuScene.h"
/////////////////////////////////////////////////////
/**
 * @brief Init Game Function
 * This function initializes the game, setting up the player, enemy, map, and camera.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void InitGame(void);
/**
 * @brief Game Update Render Function
 * This function handles the rendering of the game, including the map and entities.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void GameUpdateRender(void);
/**
 * @brief Game Update Logic Function
 * This function updates the game logic, including player movement and collision detection.
 * 
 * @param `float` Delta time for frame-independent movement
 * 
 * @return `void`
 * 
 */
void GameUpdateLogic(float dt);
/**
 * @brief Game Information Function
 * This function displays game information, such as camera details.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void GameInformation(void);
/**
 * @brief Game Update Scene Function
 * This function updates the game scene based on user input.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void GameUpdateScene(void);
/**
 * @brief Deinitialize Game Function
 * This function deinitializes the game, freeing resources and textures.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void DeInitGame(void);




/////////////////////////////////////////////////////