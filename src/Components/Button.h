////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////////////////
///< C/C++ Lib
#include <stdlib.h>
///< CGame Lib
#include "../Scenes/ScenesManager.h"
#include "../Components/Shaders.h"
#include "../Utils/Scale.h"
#include "Sound.h"
///< RayLib
#include "raylib.h"
////////////////////////////////////////////////////////////////////////////////////////////
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
    bool action;                    ///< Pressed
    float frameHeight;              ///< FrameHight
    ButtonState state;              ///< Estate of the button
    Texture2D* Texture;             ///< Textures
    Sound sound;                    ///< Spound when is pressed
    Vector2 position;               ///< Position
    Rectangle boundingBox;          ///< CollisiomBox position.
    Rectangle sourceButton;         ///< Size of the button in Rectangle
    Rectangle destinationButton;    ///< Helps for scalin.
}Button;
////////////////////////////////////////////////////////////////////////////////////////////
#define NUM_FRAMES 3
////////////////////////////////////////////////////////////////////////////////////////////
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
 */
Button* CreateButton(const char* texturePath, const char* texturePath2, Vector2 pos);
/**
 * 
 */
void AccionButton(Button* button, Font font, const char* text,TypeShader type,Vector2 posFoo, ManagerScenes nextScene, float s, bool action, Color c);
/**
 * 
 */
void DrawButton(Button* button, const char* text, Vector2 posFoo, Font font, Color c);

////////////////////////////////////////////////////////////////////////////////////////////