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
    ///!<------ Loading Textures ------>
    ///<    Load Logo for the game && Validate if the file exists
    if(IsPathFile("assets/Icons/Tempest.png")) Logo = LoadTexture("assets/Icons/Tempest.png");
    else perror("\nERROR NOT LOAD LOGO FILE");
    ///<    Information for the Buttons (Path)
    char* pathT1 = "assets/UI/button_rectangle_depth_line.png";
    char* pathT2 = "assets/UI/button_rectangle_line.png";
    ///<    BackGround for the parallax
    bg = LoadTexture("assets/BackGrounds/Plains.png");
    ///<    Texture Temp
    Texture2D temp = LoadTexture("assets/UI/button_rectangle_depth_line.png");
    ///!<------- Creation of Buttons -------->
    ///<    Creation of 3 buttons
    CustomScale(1.f);
        float midScrenTexture = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
        btt_StartGame = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 540.f});
        btt_Option = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 700.f});
        btt_Exit =  CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 860.f});
        Vector2 posBes = {.x =1700, .y = 90};
    CustomScale(.5f);
        btt_Bestiary = CreateButton("assets/UI/BookInformation.png","assets/UI/BookInformation.png",posBes);
    CustomScale(1.f);
    ///!<------- Position of the text for the buttons ------->
    ///<    Memory allocation for the positions of the text
    bar = (Vector2*)calloc(3,sizeof(Vector2));
    foo = (Vector2*)calloc(3,sizeof(Vector2));
    ///<    Font for buttons
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
    ///!<------------- Init stuff for MainMenuScene ------------->
    ///<    Play Music for the MainMenuScene
    PlayMusicStream(music[MS_MAINMENU]);
    ///<    Scroll init for the background
    scrollBackGround = 0.f;
    ///!<------------- UnLoad Textures ----------->
    UnloadTexture(temp);

}
//////////////////////////////////////////////////////////
void UpdateMenuScene(void)
{
    ///!<---- Background Draw -->
    ///<    Background moves slower than the foreground to create an illusion of depth
    ///<    `` scrollBackGround -= 1.f ``, is the speed of the background movement. So the higher the value, the faster the background moves.   
    scrollBackGround -= 1.f;
    if(scrollBackGround <= -bg.width + 229.5)
        scrollBackGround = 0;
    DrawTextureEx(bg,(Vector2){scrollBackGround, 0}, 0.f, 0.9f,WHITE);
    DrawTextureEx(bg,(Vector2){(float)(scrollBackGround + (float)bg.width - 229.5), 0}, 0.f, 0.9f,WHITE);
    ///!<---- Bestiary Button Draw -->
    ///<    Outline Shader for the Bestiary Button. Is the book icon on the top right corner
    BeginShaderMode(shaders[S_OUTLINE]);
        DrawTexturePro(btt_Bestiary->Texture[0], btt_Bestiary->sourceButton, btt_Bestiary->destinationButton, (Vector2){0,0}, 0.0f, WHITE);
    EndShaderMode();
    ///!<---- Logo Draw -->
    ///<    Centered at the top of the screen, with a custom scale applied.
    CustomScale(0.5f);
        float posLogo = (float)GetScreenWidth() / 2.f - (float)Logo.width / 2.f * scale.ScaleUniform;
        DrawTexturePro(
            Logo,
            (Rectangle){.x=0,.y=0,.width=(float)Logo.width,.height=(float)Logo.height},
            (Rectangle){.x =posLogo, .y=10.f, .width = (float)Logo.width * scale.ScaleUniform,.height=(float)Logo.height * scale.ScaleUniform},
            (Vector2){0,0},
            0,
            WHITE);
    CustomScale(1.f);
    ///!<---- Buttons Draw -->
    DrawButton(btt_StartGame,"Iniciar Juego",foo[0],*fontType, BLACK);      ///< Start Game Button
    DrawButton(btt_Option,"Opciones",foo[1],*fontType, BLACK);              ///< Options Button
    DrawButton(btt_Exit,"Salir",foo[2],*fontType, BLACK);                   ///< Exit Game Button
    ///!<---- Collision logic -->
    if (CheckCollisionPointRec(mouse,btt_StartGame->destinationButton))
    {
        AccionButton(btt_StartGame,*fontType,"Iniciar Juego",S_INVERT,foo[0],sLOADSCREEN,MS_MAINMENU,MS_GAMESTATE,0.f,true, WHITE);
    }
    else if(CheckCollisionPointRec(mouse, btt_Option->destinationButton))
    {
        AccionButton(btt_Option,*fontType,"Opciones",S_INVERT,foo[1],sOPTIONMENU,MS_NONE,MS_NONE,0.f,true,WHITE);
        scenes->previousScene = sMAINMENU;
    }
    else if(CheckCollisionPointRec(mouse, btt_Exit->destinationButton))
        AccionButton(btt_Exit,*fontType,"Salir",S_INVERT,foo[2],sEXIT_GAME,MS_NONE,MS_NONE,0.1f,true,WHITE);
    else if(CheckCollisionPointRec(mouse,btt_Bestiary->destinationButton))
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(sounds[0]);
            scenes->typeScene = sBESTIARY;
            WaitTime(0.1);
        }
}
void DestroyMenuScene(void)
{
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


