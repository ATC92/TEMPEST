//////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////
///< C/C++ Lib
///< CGame Lib
#include "../Components/Mouse.h"
#include "../Components/Sound.h"
#include "../Components/Button.h"
#include "../Components/Fonts.h"
#include "../Engine/Config.h"
#include "ScenesManager.h"
///< RayLib
#include "raylib.h"
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
