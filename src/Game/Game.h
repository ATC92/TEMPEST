#pragma once
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "OnUpdate.h"

#include "../Components/Map.h"
#include "../Components/Sound.h"
#include "../Components/Camera.h"
#include "../Components/Entity.h"
#include "../Components/Inventory.h"
#include "../Components/Animation.h"
#include "../Components/Collision.h"
#include "../Components/LoadTextures.h"

#include "../Utils/Vector.h"
#include "../Utils/Information.h"

#include "../Scenes/ScenesManager.h"
#include "../Scenes/MenuScene.h"

// #include "../Scenes/FightScene.h"
/////////////////////////////////////////////////////
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
void InitGameScene(void);
/**
 * @brief Game Update Render Function
 * This function handles the rendering of the game, including the map and entities.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void UpdateGameRender(void);
/**
 * @brief Game Update Logic Function
 * This function updates the game logic, including player movement and collision detection.
 * 
 * @param `float` Delta time for frame-independent movement
 * 
 * @return `void`
 * 
 */
void UpdateGameLogic(float dt);
/**
 * @brief Game Update Scene Function
 * This function updates the game scene based on user input.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void UpdateGameScene(void);
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
 * @brief Deinitialize Game Function
 * This function deinitializes the game, freeing resources and textures.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 */
void DestroyGameScene(void);




/////////////////////////////////////////////////////