#pragma once

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include Lib of Entity
#include "../Entity/Entity.h"
// Include Lib of Mapa
#include "../MapGen/Map.h"
// Include Lib of Information
#include "../Utils/Information.h"
// Include Lib of LoadTextures
#include "../Utils/LoadTextures.h"
// Include Lib of EngineUpdates
#include "../Utils/EngineUpdates.h"

/**
 * @brief Initialization of the engine
 */
void InitGame();
/**
 * @brief Render of the Engine
 */
void GameRender();
/**
 * @brief De-Initialization of the engine
 */
void DeInitGame();
/**
 * 
 */
void GameUpdate();




