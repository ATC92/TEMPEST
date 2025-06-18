#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///< CGame Lib
#include "../Textures/Textures.h"
#include "../Utils/Information.h"
#include "../Utils/OperadorOverload.h"
///////////////////////////////////////////////////////////////
typedef enum _state
{
    NORMAL,
    MOUSE_OVER,
    PRESSED
}ButtonState;
/**
 * @brief Struct Button
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
///////////////////////////////////////////////////////////////
///< Init GUI
void InitGUI(void);
///< MainMenuGUI
void MainMenuGUI(void);
///< CreateButton 
Button* CreateButton(const char*,const char*,const char*);
///////////////////////////////////////////////////////////////
///< Variable Globales
extern Button* button;