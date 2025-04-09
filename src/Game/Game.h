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
#include "../Entity/Entity.h"
#include "../Textures/Map.h"
#include "../Textures/LoadTextures.h"
#include "../Utils/Information.h"
#include "../Scenes/ScenesManager.h"
#include "../Scenes/Scenes.h"
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
void InitGame(void);
void GameUpdateRender(void);
void GameUpdateLogic(void);
void GameInformation(void);
void GameUpdateScene(void);
void DeInitGame(void);