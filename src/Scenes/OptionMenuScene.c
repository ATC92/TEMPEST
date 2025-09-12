//////////////////////////////////////////////////////////////////////////////
#include "OptionMenuScene.h"
//////////////////////////////////////////////////////////////////////////////
///< Private 
static Button* btt_Return;
static Button* btt_dot;
static Shader invert;
static Vector2 foo, bar;
static Texture2D bg;
static double startTime;
static bool waitingCooldown;
//////////////////////////////////////////////////////////////////////////////
void InitOptionMenuScene(void)
{
    ///< Load Shaders
    invert = LoadShader(NULL, "src/Shaders/invert.fs");
    if (!IsShaderValid(invert)) TraceLog(LOG_ERROR, "Shader Invalid");
    ///< Create and load Font texture
    fontType = (Font*)calloc(1,sizeof(Font));
    *fontType = LoadFontEx("assets/Font/04B.ttf",20,NULL,0);
    if(!IsFontValid(*fontType))
        return;
    ///< BackGround
    bg = LoadTexture("assets/BackGrounds/OptionMenu.png");
    // Information for the Buttons (Path)
    char* pathT1 = "assets/UI/check_round_grey.png";
    char* pathT2 = "assets/UI/check_round_round_circle.png";
    char* pathT3 = "assets/UI/button_rectangle_depth_line.png";
    char* pathT4 = "assets/UI/button_rectangle_line.png";
    ///< Texture Temp
    Texture2D temp = LoadTexture("assets/UI/button_rectangle_depth_line.png");
    Texture2D tempDot = LoadTexture("assets/UI/check_round_grey.png");
    ///< Button creation (DOT)
    float midScreenButton = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    float midScreenDot = {(float)GetScreenWidth() / 2 - (float)tempDot.width / 2.0f};
    btt_dot = CreateButton(pathT1,pathT2,(Vector2){midScreenDot - 200,350.f});
    btt_dot->action = false;
    ///< Button creation Return
    btt_Return = CreateButton(pathT3,pathT4,(Vector2){midScreenButton,800.f});
    bar = MeasureTextEx(*fontType, "Regresar", 40, 0);
    foo = (Vector2)
    {
        .x = (btt_Return->position.x + btt_Return->sourceButton.width / 2) - bar.x / 2,
        .y = (btt_Return->position.y + btt_Return->sourceButton.height / 2) - bar.y / 2
    };
}

void UpdateOptionMenuScene(void)
{
    DrawTexturePro
    (
        bg,
        (Rectangle){.x=0,.y=0,.height=(float)bg.height,.width=(float)bg.width},
        (Rectangle){.x=0,.y=0,.height = (float)GetScreenHeight(),.width= (float)GetScreenWidth()},
        (Vector2){0,0},
        0,
        WHITE
    );
    mouse = GetMousePosition();
    DrawTextureRec(btt_Return->Texture[0],btt_Return->sourceButton,btt_Return->position,WHITE);
    if(btt_dot->action == true)
        DrawTextureRec(btt_dot->Texture[1],btt_dot->sourceButton,btt_dot->position,WHITE);
    else
        DrawTextureRec(btt_dot->Texture[0],btt_dot->sourceButton,btt_dot->position,WHITE);
    if (CheckCollisionPointRec(mouse,btt_Return->boundingBox))
    {
        BeginShaderMode(invert);
            btt_Return->state = MOUSE_OVER;
            DrawTextureRec(btt_Return->Texture[1], btt_Return->sourceButton, btt_Return->position, WHITE );
            DrawTextEx(*fontType,"Regresar",foo,40,0,BLACK);
        EndShaderMode();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // ClearBackground(WHITE);
            PlaySound(sounds[0]);
            scenes->typeScene = MainMenu; ///< Change Scene to MainMenu Scene
            WaitTime(.1);
        }
    }
    else if(CheckCollisionPointRec(mouse,btt_dot->boundingBox))
    {
        BeginShaderMode(invert);
            btt_dot->state = MOUSE_OVER;
        EndShaderMode();
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            startTime = GetTime();
            waitingCooldown = true;
        }
        if(waitingCooldown && (GetTime() - startTime) >= 0.1)
        {
            PlaySound(sounds[0]);
            DrawTextureRec(btt_dot->Texture[1],btt_dot->sourceButton,btt_dot->position,WHITE);
            ToggleFullscreen();
            btt_dot->action = !btt_dot->action;

            waitingCooldown = false;
        }
    }
    else
    {
        btt_Return->state = NORMAL;
        DrawTextEx(*fontType,"Regresar",foo,40,0,BLACK);
    }

}
void DestroyOptionMenuScene(void)
{

}