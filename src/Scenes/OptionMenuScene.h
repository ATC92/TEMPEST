//////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "../Components/Mouse.h"
#include "../Components/Sound.h"
#include "../Components/Fonts.h"
#include "../Components/Button.h"
#include "../Engine/Config.h"

#include "../Game/Game.h"
#include "FightScene.h"

#include "ScenesManager.h"
#include "AuxScenes.h"
//////////////////////////////////////////////////////////////////////////////
typedef enum _btts
{
    _BTT_ESC,
    _BTT_MAINMENU,
    _BTT_FULLSCREEN,
    _BTT_STATES,
    _BTT_VOLUME,
    _BTT_vDOT
}TypeButton;
//////////////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize the Options Menu scene
 * This function sets up all resources, variables, and settings required for the Options Menu.
 * 
 * @param void
 * 
 * @return void
 * 
 * @note This function should be called once before the Options Menu scene starts.
 */
void InitOptionMenuScene(void);
/**
 * @brief Update the Options Menu scene
 * This function handles input, animations, and dynamic behavior for the Options Menu every frame.
 * 
 * @param void
 * 
 * @return void
 * 
 * @note This function should be called every frame while the Options Menu is active.
 */
void UpdateOptionMenuScene(void);
/**
 * @brief Destroy the Options Menu scene
 * This function frees all resources and cleans up memory used by the Options Menu.
 * 
 * @param void
 * 
 * @return void
 * 
 * @note This function should be called when the Options Menu scene is no longer needed.
 */
void DestroyOptionMenuScene(void);

//////////////////////////////////////////////////////////////////////////////
