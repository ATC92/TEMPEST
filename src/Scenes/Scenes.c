#include "Scenes.h"

Button* button;

void MainMenuGUI(void)
{
    DrawTextureRec(button->Texture,
                button->sourcRec,
                button->position,
                WHITE);
}

void InitGUI(void)
{
    ///< Create Button.
    button = CreateButton("assets/Sounds/UI/click-b.wav","assets/UI/UI_TILES/Extra/Double/button_rectangle_depth_line.png");
}

Button* CreateButton(const char* soundPath,const char* texturePath)
{
    Button* bttTemp = (Button*)calloc(1,sizeof(Button));
    bttTemp->sound = LoadSound(soundPath);
    bttTemp->Texture = LoadTexture(texturePath);
    ///< FrameHeight (Height of Texute2D) / Num of frames
    bttTemp->frameHeight = (float)bttTemp->Texture.height;
    bttTemp->sourcRec = (Rectangle){0,0, (float)bttTemp->Texture.width, (float)bttTemp->Texture.height};
    bttTemp->Bounds = (Rectangle){(float)GetScreenWidth()/2.0f - bttTemp->Texture.width, 
                                (float)GetScreenHeight()/2.0f - bttTemp->Texture.height/3/2.f, 
                                (float)bttTemp->Texture.width,
                                bttTemp->frameHeight};
    bttTemp->position = (Vector2){ .x = bttTemp->Bounds.x, .y = bttTemp->Bounds.y };
    bttTemp->action = false;
    bttTemp->name = strdup("Button Init");
    bttTemp->state = NORMAL;
    return bttTemp;
}