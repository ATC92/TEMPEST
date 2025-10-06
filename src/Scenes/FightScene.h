//////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "../Components/Mouse.h"
#include "../Components/Sound.h"
#include "../Components/Fonts.h"
#include "../Components/Button.h"
#include "ScenesManager.h"
//////////////////////////////////////////////////////////
/**
 * @brief Initialize the Fight scene
 * This function sets up all resources, variables, and settings required for the Fight Scene.
 * 
 * @param `void
 * 
 * @return `void`
 * 
 * @note This function should be called once before the Fight Scene scene starts.
 * 
 */
void InitFightScene(void);
/**
 * @brief Update the Fight Scene
 * This function handles input, animations, and dynamic behavior for the Fight Scene every frame.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function should be called every frame while the Fight Scene is active.
 */
void UpdateFightScene(void);
/**
 * @brief Destroy the Fight Scene scene
 * This function frees all resources and cleans up memory used by the Fight Scene.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function should be called when the Fight Scene scene is no longer needed.
 */
void DestroyFightScene(void);
//////////////////////////////////////////////////////////