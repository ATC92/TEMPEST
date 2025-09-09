#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///< CGame Lib
<<<<<<< HEAD
#include "../Components/Textures.h"
#include "../Utils/Information.h"
#include "../Engine/Updates.h"
#include "../Utils/Fonts.h"
=======
#include "../Textures/Textures.h"
#include "../Utils/Information.h"
#include "../Utils/OperadorOverload.h"
>>>>>>> origin/main
///////////////////////////////////////////////////////////////
/**
 * @brief ButtonState
 * 
 * This enum defines the possible states of a button in the GUI.
 * 
 * The states are:
 * - @c NORMAL: The button is in its default state. \\
 * - @c MOUSE_OVER: The button is hovered by the mouse. \\
 * - @c PRESSED: The button is currently pressed.
 */
typedef enum _state
{
    NORMAL,
    MOUSE_OVER,
    PRESSED
}ButtonState;
/**
 * @brief Button
 * This struct represents a button in the GUI.
 * 
 * It contains the following fields:
 * - @c name: The name of the button. \\
 * - @c action: A boolean indicating if the button is pressed. \\
 * - @c frameHeight: The height of the button frame. \\
 * - @c state: The current state of the button (NORMAL, MOUSE_OVER,PRESSED). \\
 * - @c Texture: An array of textures for the button. \\
 * - @c sound: The sound played when the button is pressed. \\
 * - @c position: The position of the button in the GUI. \\
 * - @c boundingBox: The collision box for the button. \\
 * - @c sourceButton: The size of the button in a rectangle.
 * 
 */
typedef struct _btt
{
    char* name;                 ///< Name of the button
    bool action;                ///< Pressed
    float frameHeight;          ///< FrameHight
    ButtonState state;          ///< Estate of the button
    Texture2D* Texture;          ///< Textures
    Sound sound;                ///< Spound when is pressed
    Vector2 position;           ///< Position
    Rectangle boundingBox;      ///< CollisiomBox position.
    Rectangle sourceButton;     ///< Size of the button in Rectangle
}Button;
///////////////////////////////////////////////////////////////
#define NUM_FRAMES 3
/**
 * @brief button
 * This is a global pointer to a Button structure that represents the main menu button.
 * It is used to handle the button's state, textures, sound, and interactions in the main menu GUI.
 * It is initialized in the `InitGUI` function and used in the `MainMenuGUI` function to render the button and handle user interactions.
 */
extern Button* button;
///////////////////////////////////////////////////////////////
/**
 * @brief InitGUI
 * This function initializes the GUI by loading shaders, fonts, and creating buttons.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note This function is called at the start of the game to prepare the GUI components.
 * It loads the invert shader, creates a font from a TTF file, and initializes a button with specified textures and sound.
 */
void InitGUI(void);
/**
 * @brief MainMenuGUI
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
void MainMenuGUI(void);
/**
 * @brief CreateButton
 * This function creates a button with specified textures and sound.
 * 
 * @param `soundPath` The path to the sound file played when the button is pressed.
 * @param `texturePath` The path to the texture file for the button in its normal state.
 * @param `texturePath2` The path to the texture file for the button in its pressed state.
 * 
 * @return `Button*` A pointer to the created Button structure.
 * 
 * @note This function allocates memory for a Button structure, loads the specified textures and sound, 
 * and initializes the button's properties such as position, bounding box, and source rectangle.
 * 
 */
Button* CreateButton(const char*,const char*,const char*);
///////////////////////////////////////////////////////////////


