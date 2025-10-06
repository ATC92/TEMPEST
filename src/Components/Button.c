/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include"Button.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Button* CreateButton(const char* texturePath, const char* texturePath2, Vector2 pos)
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

    bttTemp->destinationButton = (Rectangle)
    {
        .x = bttTemp->position.x,
        .y =bttTemp->position.y,
        .width = (float)bttTemp->Texture[0].width * scale.ScaleUniform,
        .height = (float)bttTemp->Texture[0].height * scale.ScaleUniform
    };
    ///
    bttTemp->boundingBox = (Rectangle)
    {
        .x = bttTemp->position.x,
        .y = bttTemp->position.y,
        .width = bttTemp->sourceButton.width,
        .height = bttTemp->sourceButton.height
    };

    bttTemp->action = false;
    return bttTemp;
}
void AccionButton(Button* button, Font font, const char* text,TypeShader type,Vector2 posFoo, ManagerScenes nextScene,MusicType prev,MusicType next,float s, float fontSize, bool action, Color c, Color fontColor)
{
    BeginShaderMode(shaders[type]);
        DrawTexturePro(button->Texture[1],button->sourceButton,button->destinationButton,(Vector2){0,0},0,c);
        DrawTextEx(font,text,posFoo,fontSize,0,fontColor);
    EndShaderMode();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && action)
    {
        PlaySound(sounds[0]);
        ChangeScene(nextScene);
        if(prev != MS_NONE && next != MS_NONE)
            ChangeMusic();
        WaitTime(s);
    }
}
void DrawButton(Button* button, const char* text, Vector2 posFoo, Font font,float fontSize, Color c)
{
    DrawTexturePro(button->Texture[0],button->sourceButton, button->destinationButton,(Vector2){0,0},0,WHITE);
    DrawTextEx(font, text, posFoo, fontSize, 0, c);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
