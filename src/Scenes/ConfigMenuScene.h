//////////////////////////////////////////////////////////
///< C/C++ Lib
///< TEMPEST Lib
#include "../Components/Mouse.h"
#include "../Components/Sound.h"
#include "../Components/Fonts.h"
#include "../Components/Button.h"
#include "ScenesManager.h"
///< RayLib
#include "raylib.h"
//////////////////////////////////////////////////////////
/**
 * @brief Initialize the Config Menu scene
 * This function sets up all resources, variables, and settings required for the Config Menu.
 * 
 * @param `void
 * 
 * @return `void`
 * 
 * @note This function should be called once before the Config Menu scene starts.
 * 
 */
void InitConfigMenuScene(void);
/**
 * @brief Update the Config Menu scene
 * This function handles input, animations, and dynamic behavior for the Config Menu every frame.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function should be called every frame while the Config Menu is active.
 */
void UpdateConfigMenuScene(void);
/**
 * @brief Destroy the Config Menu scene
 * This function frees all resources and cleans up memory used by the Config Menu.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function should be called when the Config Menu scene is no longer needed.
 */
void DestroyConfigMenuScene(void);
//////////////////////////////////////////////////////////