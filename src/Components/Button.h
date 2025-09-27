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
 * @brief AccionButton
 * This function handles the action of a button when it is pressed.
 * 
 * @param `button` A pointer to the Button structure representing the button.
 * @param `font` The font used for rendering the button text.
 * @param `text` The text displayed on the button.
 * @param `type` The type of shader effect to apply when the button is pressed.
 * @param `posFoo` The position where the button text is drawn.
 * @param `nextScene` The scene to switch to when the button is pressed.
 * @param `prev` The previous music type before the button action.
 * @param `next` The next music type after the button action.
 * @param `s` A float value that may represent a scaling factor or duration.
 * @param `action` A boolean indicating whether the button action should be executed.
 * @param `c` The color used for rendering the button text.
 * 
 * @return `void`
 * 
 * @note This function checks if the button is pressed, plays the associated sound, applies a shader effect,
 * 
 */
void AccionButton(Button* button, Font font, const char* text,TypeShader type,Vector2 posFoo, ManagerScenes nextScene,MusicType prev,MusicType next,float s, bool action, Color c);
/**
 * @brief DrawButton
 * This function draws a button on the screen with the specified text and style.
 * 
 * @param `button` A pointer to the Button structure representing the button to be drawn.
 * @param `text` The text to be displayed on the button.
 * @param `posFoo` The position where the button text is drawn.
 * @param `font` The font used for rendering the button text.
 * @param `c` The color used for rendering the button text.
 * 
 * @return `void`
 * 
 * @note This function draws the button's texture and text on the screen, applying the specified font and color.
 */
void DrawButton(Button* button, const char* text, Vector2 posFoo, Font font, Color c);

////////////////////////////////////////////////////////////////////////////////////////////