#pragma once

#include <stdlib.h>

#include "raylib.h"


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
// extern Button* btt_StartGame;
///////////////////////////////////////////////////////////////
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
static inline Button* CreateButton(const char* texturePath, const char* texturePath2, Vector2 pos)
{
    Button* bttTemp = (Button*)calloc(1,sizeof(Button));
    // bttTemp->sound = LoadSound(soundPath);
    bttTemp->Texture = (Texture2D*)calloc(2,sizeof(Texture2D));
    bttTemp->Texture[0] = LoadTexture(texturePath);
    bttTemp->Texture[1] = LoadTexture(texturePath2);
    
    /// Bounds
    bttTemp->position = pos;


    /// Source rectangle
    bttTemp->sourceButton = (Rectangle){0,0, (float)bttTemp->Texture[0].width, (float)bttTemp->Texture[0].height};

    ///
    bttTemp->boundingBox = (Rectangle)
    {
        .x = bttTemp->position.x,
        .y = bttTemp->position.y,
        .width = bttTemp->sourceButton.width,
        .height = bttTemp->sourceButton.height
    };

    bttTemp->action = false;
    bttTemp->state = NORMAL;
    return bttTemp;
}