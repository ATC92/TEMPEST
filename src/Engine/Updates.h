#pragma once
///< C/C++ Lib
///< CGame Lib
#include "../Scenes/ScenesManager.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/LoadingScene.h"
#include "../Game/Game.h"
///< Extern Lib
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