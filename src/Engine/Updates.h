#pragma once
///< TEMPEST Lib
#include "../Scenes/ScenesManager.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/LoadingScene.h"
#include "../Scenes/BestiaryScene.h"
#include "../Scenes/OptionMenuScene.h"
#include "../Scenes/FightScene.h"
#include "../Game/Game.h"
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
/**
 * @brief Render Current Scene Function
 * This function renders the current scene based on the provided scene type.
 * 
 * @param `type` The type of scene to render, defined in ManagerScenes.
 * 
 * @return `void`
 * @note This function handles the rendering of different scenes such as MainMenu, GameState, OptionMenu, and ConfigurationMenu.
 * If an unsupported scene type is provided, it will print an error message.
 */
void RenderCurrentScene(ManagerScenes);
//////////////////////////////////////////////////////////