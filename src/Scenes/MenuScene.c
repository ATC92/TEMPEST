#include "MenuScene.h"
//////////////////////////////////////////////////////////
///< Private Declaration
static Button* btt_StartGame;
static Button* btt_Option;
static Button* btt_Exit;
static Shader invert;
static Vector2* bar;
static Vector2* foo;
static Texture2D bg;
//////////////////////////////////////////////////////////
void InitMenuScene(void)
{
    ///< Load Shaders
    invert = LoadShader(NULL, "src/Shaders/invert.fs");
    if (!IsShaderValid(invert)) TraceLog(LOG_ERROR, "Shader Invalid");
    ///< Create and load Font texture
    fontType = (Font*)calloc(1,sizeof(Font));
    *fontType = LoadFontEx("assets/Font/04B.ttf",20,NULL,0);
    if(!IsFontValid(*fontType))
        return;
    // Information for the Buttons (Path)
    char* pathT1 = "assets/UI/button_rectangle_depth_line.png";
    char* pathT2 = "assets/UI/button_rectangle_line.png";
    ///< BackGround
    bg = LoadTexture("assets/BackGrounds/MainMenu.png");
    ///< Texture Temp
    Texture2D temp = LoadTexture("assets/UI/button_rectangle_depth_line.png");
    ///< Creation of 3 buttons
    float midScrenTexture = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    btt_StartGame = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 480.f});
    btt_Option = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 650.f});
    btt_Exit =  CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 830.f});
    ///< Text for btt_StartGame
    bar = (Vector2*)calloc(3,sizeof(Vector2));
    foo = (Vector2*)calloc(3,sizeof(Vector2));
    
    ///< Kill Texture Temp
    UnloadTexture(temp);

    bar[0] = MeasureTextEx(*fontType, "Iniciar Juego", 40, 0);
    bar[1] = MeasureTextEx(*fontType, "Opciones",40,0);
    bar[2] = MeasureTextEx(*fontType, "Salir",40,0);
    foo[0] = (Vector2)
    {
        .x = (btt_StartGame->position.x + btt_StartGame->sourceButton.width / 2) - bar[0].x / 2,
        .y = (btt_StartGame->position.y + btt_StartGame->sourceButton.height / 2) - bar[0].y / 2
    };
    foo[1] = (Vector2)
    {
        .x = (btt_Option->position.x + btt_Option->sourceButton.width / 2) - bar[1].x / 2,
        .y = (btt_Option->position.y + btt_Option->sourceButton.height / 2) - bar[1].y / 2
    };
    foo[2] = (Vector2)
    {
        .x = (btt_Exit->position.x + btt_Exit->sourceButton.width / 2) - bar[2].x / 2,
        .y = (btt_Exit->position.y + btt_Exit->sourceButton.height / 2) - bar[2].y / 2
    };
    /// Mouse Init
    InitMouse();
    ///< Init Sounds
    InitSoundGame();
}
//////////////////////////////////////////////////////////
void UpdateMenuScene(void)
{
    DrawTexturePro(bg,
    (Rectangle){.x=0,.y=0,.height=(float)bg.height,.width=(float)bg.width},
    (Rectangle){.x=0,.y=0,.height = (float)GetScreenHeight(),.width= (float)GetScreenWidth()},
    (Vector2){0,0},
    0,
    WHITE);
    mouse = GetMousePosition();
    btt_StartGame->sourceButton.y = (float)btt_StartGame->state * btt_StartGame->frameHeight;
    
    ///< Buttons
    ///< Butotn Start.
    DrawTextureRec(btt_StartGame->Texture[0], btt_StartGame->sourceButton, btt_StartGame->position, WHITE );
    ///< Button Options.
    DrawTextureRec(btt_Option->Texture[0], btt_Option->sourceButton, btt_Option->position, WHITE);
    ///< Button Exit
    DrawTextureRec(btt_Exit->Texture[0], btt_Exit->sourceButton, btt_Exit->position, WHITE);

    if (CheckCollisionPointRec(mouse,btt_StartGame->boundingBox))
    {
        BeginShaderMode(invert);
            btt_StartGame->state = MOUSE_OVER;
            DrawTextureRec(btt_StartGame->Texture[1], btt_StartGame->sourceButton, btt_StartGame->position, WHITE );
            DrawTextEx(*fontType,"Iniciar Juego",foo[0],40,0,BLACK);
        EndShaderMode();
        DrawTextEx(*fontType,"Opciones",foo[1],40,0,BLACK);
        DrawTextEx(*fontType,"Salir",foo[2],40,0,BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // ClearBackground(WHITE);
            PlaySound(sounds[0]);
            scenes->typeScene = LoadingScreen; ///< Change Scene to Loading Screen
            WaitTime(0.1);
        }
    }
    else if(CheckCollisionPointRec(mouse, btt_Option->boundingBox))
    {
        BeginShaderMode(invert);
            btt_Option->state = MOUSE_OVER;
            DrawTextureRec(btt_Option->Texture[1], btt_Option->sourceButton, btt_Option->position, WHITE);
            DrawTextEx(*fontType,"Opciones",foo[1],40,0,BLACK);
        EndShaderMode();
        DrawTextEx(*fontType,"Iniciar Juego",foo[0],40,0,BLACK);
        DrawTextEx(*fontType,"Salir",foo[2],40,0,BLACK);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // ClearBackground(WHITE);
            PlaySound(sounds[0]);
            scenes->typeScene = OptionMenu;
            WaitTime(0.1);
        }
    }
    else if(CheckCollisionPointRec(mouse, btt_Exit->boundingBox))
    {
        BeginShaderMode(invert);
            btt_Exit->state = MOUSE_OVER;
            DrawTextureRec(btt_Exit->Texture[1], btt_Exit->sourceButton, btt_Exit->position, WHITE);
            DrawTextEx(*fontType,"Salir",foo[2],40,0,BLACK);
        EndShaderMode();
        DrawTextEx(*fontType,"Iniciar Juego",foo[0],40,0,BLACK);
        DrawTextEx(*fontType,"Opciones",foo[1],40,0,BLACK);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // ClearBackground(WHITE);
            PlaySound(sounds[0]);
            scenes->typeScene = EXIT_GAME;
            WaitTime(0.1);
        }
    }
    else
    {
        btt_StartGame->state = NORMAL;
        DrawTextEx(*fontType,"Iniciar Juego",foo[0],40,0,BLACK);
        DrawTextEx(*fontType,"Opciones",foo[1],40,0,BLACK);
        DrawTextEx(*fontType,"Salir",foo[2],40,0,BLACK);
    }
}

void DestroyMenuScene(void)
{
    free(sounds);
    for (size_t i = 0; i < 2; i++)
    {
        UnloadTexture(btt_StartGame->Texture[i]);
        UnloadTexture(btt_Option->Texture[i]);
        UnloadTexture(btt_Exit->Texture[i]);
    }
    free(foo);
    free(bar);
    
    free(btt_StartGame);
    free(btt_Option);
    free(btt_Exit);
    
    
}
//////////////////////////////////////////////////////////


