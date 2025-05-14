#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///< CGame Lib
#include "../Textures/Textures.h"
#include "../Utils/Information.h"
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
    char* name;
    bool action;
    ButtonState state;
    ///< Textures
    Sound sound;
    Texture2D Texture;
    float frameHeight;
    Vector2 position;
    Rectangle sourcRec;
    Rectangle Bounds;
}Button;
///////////////////////////////////////////////////////////////
///< Init GUI
void InitGUI(void);
///< MainMenuGUI
void MainMenuGUI(void);
///< CreateButton 
Button* CreateButton(const char*,const char*);
///////////////////////////////////////////////////////////////
///< Variable Globales
extern Button* button;