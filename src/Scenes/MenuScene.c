#include "MenuScene.h"
#include "ScenesManager.h"
//////////////////////////////////////////////////////////
Button* button;
Vector2 mousePoint = { 0.0f, 0.0f };
Shader invert;
//////////////////////////////////////////////////////////
void MainMenuGUI(void)
{
    mousePoint = GetMousePosition();
    button->sourceButton.y = (float)button->state * button->frameHeight;
    DrawTextureRec
    (
        button->Texture[0],
        button->sourceButton,
        button->position,
        WHITE
    );
    ///< Text
    Vector2 bar = MeasureTextEx(*fontType, "Iniciar Juego", 40, 0);
    Vector2 foo =
    {
        .x = (button->position.x + button->sourceButton.width / 2) - bar.x / 2,
        .y = (button->position.y + button->sourceButton.height / 2) - bar.y / 2
    };
    if (CheckCollisionPointRec(mousePoint,button->boundingBox))
    {
        BeginShaderMode(invert);
            button->state = MOUSE_OVER;
            DrawTextureRec
            (
                button->Texture[0],
                button->sourceButton,
                button->position,
                WHITE
            );
            DrawTextEx(*fontType,"Iniciar Juego",foo,40,0,BLACK);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                ClearBackground(WHITE);
                PlaySound(button->sound);
                scenes->infScene.type = LoadingScreen; ///< Change Scene to Loading Screen
                WaitTime(1);
            }
        EndShaderMode();
    }
    else
    {
        button->state = NORMAL;
        DrawTextEx(*fontType,"Iniciar Juego",foo,40,0,BLACK);
    }
}
//////////////////////////////////////////////////////////
void InitGUI(void)
{
    ///< Load Shaders
    invert = LoadShader(NULL, "src/Shaders/invert.fs");
    if (!IsShaderValid(invert)) TraceLog(LOG_ERROR, "Shader Invalid");
    ///< Create and load Font texture
    fontType = (Font*)calloc(1,sizeof(Font));
    *fontType = LoadFontEx("assets/Font/04B.ttf",20,NULL,0);
    if(!IsFontValid(*fontType))
        return;
    // button
    button = CreateButton("assets/Sounds/UI/click-b.wav","assets/UI/UI_TILES/Extra/Double/button_rectangle_depth_line.png","assets/UI/UI_TILES/Extra/Double/button_rectangle_line.png");
}
//////////////////////////////////////////////////////////
Button* CreateButton(const char* soundPath,const char* texturePath, const char* texturePath2)
{
    Button* bttTemp = (Button*)calloc(1,sizeof(Button));
    bttTemp->sound = LoadSound(soundPath);
    bttTemp->Texture = (Texture2D*)calloc(2,sizeof(Texture2D));
    bttTemp->Texture[0] = LoadTexture(texturePath);
    bttTemp->Texture[1] = LoadTexture(texturePath2);
    
    /// Bounds
    bttTemp->position = (Vector2)
    {
        (float)GetScreenWidth()/2.0f - (float)bttTemp->Texture[0].width/2.0f, 
        (float)GetScreenHeight()/2.0f - (float)bttTemp->Texture[0].height/NUM_FRAMES/2.0f,
    };


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
    bttTemp->name = strdup("Button Init");
    bttTemp->state = NORMAL;
    return bttTemp;
}
//////////////////////////////////////////////////////////


