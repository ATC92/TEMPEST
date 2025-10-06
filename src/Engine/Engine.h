//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
//< TEMPEST Libraries
#include "../Components/Shaders.h"
#include "../Components/animation.h"
#include "../Utils/Scale.h"
#include "../Game/Game.h"

#include "Flags.h"
#include "Config.h"
#include "Updates.h"
//////////////////////////////////////////////////////////
///
///
/**
 * @brief Initialize the game engine
 * This function sets up the audio device, initializes scenes, GUI, and the game.
 * 
 * @param `None`
 * 
 * @return `void`
 * 
 * * @note This function is called at the start of the game to prepare all necessary components.
 * It initializes the audio device, sets the exit key, initializes the scenes manager, GUI,
 */
void InitEngine();
/**
 * @brief Updates the game engine
 * This function updates the game logic and scene.
 * 
 * @param `None`
 * 
 * @return `void`
 * 
 * @note It handles the game update logic, including player movement and mouse wheel interactions, and updates the game scene.
 */
void EngineUpdate(float dt);
/**
 * @brief Renders the game scene
 * This function is responsible for rendering the current game scene.
 * 
 * @param `None`
 * 
 * @return `void`
 * 
 * @note It calls the function to render the current scene and displays game information such as FPS and player position.
 */
void EngineRender();
/**
 * @brief De-initializes the game engine
 * This function cleans up resources used by the game engine.
 * 
 * @param `None`
 * 
 * @return `void`
 * 
 * @note It closes the audio device and de-initializes the game.
 */
void DestroyEngine();




