#include "MenuScene.h"
//////////////////////////////////////////////////////////
///< Public declarations
///< Private declarations
static Button* btt_StartGame;
static Button* btt_Option;
static Button* btt_Exit;
static Button* btt_Bestiary;
static float scrollBackGround;
static Vector2* bar;
static Vector2* foo;
static Texture2D bg;
static Texture2D Logo;
//////////////////////////////////////////////////////////
void InitMenuScene(void)
{
    ///< Load Logo
    if(IsPathFile("assets/Icons/Tempest_LOGO_Letras.png"))
        Logo = LoadTexture("assets/Icons/Tempest_LOGO_Letras.png");
    else
        perror("\nERROR NOT LOAD LOGO FILE");

    ///< Scroll BG 
    scrollBackGround = 0.f;
    // Information for the Buttons (Path)
    char* pathT1 = "assets/UI/button_rectangle_depth_line.png";
    char* pathT2 = "assets/UI/button_rectangle_line.png";
    ///< BackGround
    bg = LoadTexture("assets/BackGrounds/Plains.png");
    ///< Texture Temp
    Texture2D temp = LoadTexture("assets/UI/button_rectangle_depth_line.png");
    ///< Creation of 3 buttons
    CustomScale(1.f);
    float midScrenTexture = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    btt_StartGame = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 480.f});
    btt_Option = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 650.f});
    btt_Exit =  CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 830.f});
    ///< BestiaryButton
    Vector2 posBes = {.x =1700, .y = 90};
    CustomScale(.5f);
    btt_Bestiary = CreateButton("assets/UI/BookInformation.png","assets/UI/BookInformation.png",posBes);
    CustomScale(1.f);
    ///< Text for btt_StartGame
    bar = (Vector2*)calloc(3,sizeof(Vector2));
    foo = (Vector2*)calloc(3,sizeof(Vector2));
    
    ///< Kill Texture Temp
    UnloadTexture(temp);


    ///< Font for buttons
    bar[0] = MeasureTextEx(*fontType, "Iniciar Juego", 40, 0);
    bar[1] = MeasureTextEx(*fontType, "Opciones",40,0);
    bar[2] = MeasureTextEx(*fontType, "Salir",40,0);
    foo[0] = (Vector2)
    {
        .x = (btt_StartGame->destinationButton.x + btt_StartGame->destinationButton.width / 2) - bar[0].x / 2,
        .y = (btt_StartGame->destinationButton.y + btt_StartGame->sourceButton.height / 2) - bar[0].y / 2
    };
    foo[1] = (Vector2)
    {
        .x = (btt_Option->destinationButton.x + btt_Option->destinationButton.width / 2) - bar[1].x / 2,
        .y = (btt_Option->destinationButton.y + btt_Option->destinationButton.height / 2) - bar[1].y / 2
    };
    foo[2] = (Vector2)
    {
        .x = (btt_Exit->destinationButton.x + btt_Exit->destinationButton.width / 2) - bar[2].x / 2,
        .y = (btt_Exit->destinationButton.y + btt_Exit->destinationButton.height / 2) - bar[2].y / 2
    };
    ///< Init Sounds
    InitSoundGame();
}
//////////////////////////////////////////////////////////
void UpdateMenuScene(void)
{
    ///< Scroll Backbround
    scrollBackGround -= 1.f;
    if(scrollBackGround <= -bg.width + 229.5)
        scrollBackGround = 0;
    ///< BackGround
    DrawTextureEx(bg,(Vector2){scrollBackGround, 0}, 0.f, 0.9f,WHITE);
    DrawTextureEx(bg,(Vector2){scrollBackGround + bg.width - 229.5, 0}, 0.f, 0.9f,WHITE);
    /// Button Bestiary
    BeginShaderMode(shaders[Outline]);
        DrawTexturePro(btt_Bestiary->Texture[0], btt_Bestiary->sourceButton, btt_Bestiary->destinationButton, (Vector2){0,0}, 0.0f, WHITE);
    EndShaderMode();
    ///< Logo Creation
    CustomScale(0.5f);
    DrawTexturePro(
        Logo,
        (Rectangle){.x=0,.y=0,.width=(float)Logo.width,.height=(float)Logo.height},
        (Rectangle){.x = ((float)GetScreenWidth() / 2) - ((float)Logo.width), .y=100.f, .width = (float)Logo.width * scale.ScaleUniform,.height=(float)Logo.height * scale.ScaleUniform},
        (Vector2){0,0},
        0,
        WHITE);
    CustomScale(1.f);
    ///< Reset all states
    btt_StartGame->state = NORMAL;
    btt_Option->state = NORMAL;
    btt_Exit->state = NORMAL;
    btt_Bestiary->state = NORMAL;
    ///!<---- Buttons Draw -->
    DrawButton(btt_StartGame,"Iniciar Juego",foo[0],*fontType, BLACK);
    DrawButton(btt_Option,"Opciones",foo[1],*fontType, BLACK);
    DrawButton(btt_Exit,"Salir",foo[2],*fontType, BLACK);
    ///!<---- Collision logic -->
    if (CheckCollisionPointRec(mouse,btt_StartGame->destinationButton))
    {
        AccionButton(btt_StartGame,*fontType,"Iniciar Juego",Invert,foo[0],GameState,0.1f,true, WHITE);
    }
    else if(CheckCollisionPointRec(mouse, btt_Option->destinationButton))
    {
        AccionButton(btt_Option,*fontType,"Opciones",Invert,foo[1],OptionMenu,0.1f,true,WHITE);
    }
    else if(CheckCollisionPointRec(mouse, btt_Exit->destinationButton))
    {
        AccionButton(btt_Exit,*fontType,"Salir",Invert,foo[2],EXIT_GAME,0.1f,true,WHITE);
    }
    else if(CheckCollisionPointRec(mouse,btt_Bestiary->destinationButton))
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(sounds[0]);
            scenes->typeScene = BestiaryScene;
            WaitTime(0.1);
        }
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


