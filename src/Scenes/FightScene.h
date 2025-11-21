//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

// #include "../Components/Card.h"
#include "../Components/Card.h"
#include "../Components/Mouse.h"
#include "../Components/Sound.h"
#include "../Components/Fonts.h"
#include "../Components/Fight.h"
#include "../Components/Entity.h"
#include "../Components/Button.h"
#include "../Components/Camera.h"
#include "../Components/CardSelector.h"
#include "../Components/LoadTextures.h"

#include "../Utils/Queues.h"

#include "ScenesManager.h"

#include "../Game/Game.h"
//////////////////////////////////////////////////////////
typedef enum _fightType
{
    _MP_MIKA
}FightType;
typedef enum _bttsType
{
    _BTT_ATTACK,
    _BTT_INVENTORY,
    _BTT_EXIT
}ButtonType;
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
 * 
 */
void UpdateRenderFight(void);
/**
 * @brief Update the logic Fight Scene
 * This function handles input, animations, and dynamic behavior for the Fight Scene every frame.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function should be called every frame while the Fight Scene is active.
 */
void UpdateLogicFight(void);
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
