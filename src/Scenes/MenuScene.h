#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
///< CGame Lib
#include "../Components/Mouse.h"
#include "../Components/Button.h"
#include "../Components/animation.h"
#include "../Components/Sound.h"
#include "../Components/Fonts.h"
#include "../Utils/Scale.h"
#include "BestiaryScene.h"
#include "ScenesManager.h"
///////////////////////////////////////////////////////////////
/**
 * @brief InitMenuScene
 * This function initializes the GUI by loading shaders, fonts, and creating buttons.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function is called at the start of the game to prepare the GUI components.
 * It loads the invert shader, creates a font from a TTF file, and initializes a button with specified textures and sound.
 */
void InitMenuScene(void);
/**
 * @brief UpdateMenuScene
 * This function renders the main menu GUI, including the button for starting the game.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function handles the rendering of the main menu button, including mouse interactions and sound effects.
 * It checks for mouse collisions with the button, changes its state based on user interaction, and plays a sound when the button is pressed.
 * The button's text is centered within its bounding box, and the button's appearance changes when hovered or pressed.
 */
void UpdateMenuScene(void);
/**
 * 
 */
void DestroyMenuScene(void);
///////////////////////////////////////////////////////////////


