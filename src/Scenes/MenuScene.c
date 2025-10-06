///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MenuScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Public declarations
///< Private declarations
static Button* btt_StartGame;
static Button* btt_Option;
static Button* btt_Exit;
static Button* btt_Bestiary;
static float sfBG,smBG,scBG,sbBG;
static Vector2* bar;
static Vector2* foo;
static Texture2D frontBG, midBG, cloudBG,backBG;
static Texture2D Logo;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitMenuScene(void)
{
    ///!<------ Loading Textures ------>
    ///<    Load Logo for the game && Validate if the file exists
    if(IsPathFile("assets/Icons/VeyxTempest.png")) 
        Logo = LoadTexture("assets/Icons/VeyxTempest.png");
    else 
        TraceLog(LOG_ERROR, "Texture couldnt load: assets/Icons/VeyxTempest.png");
    ///<    Information for the Buttons (Path)
    char* pathT1 = "assets/UI/Buttons/button_rectangle_depth_line.png";
    char* pathT2 = "assets/UI/Buttons/button_rectangle_line.png";
    ///<    BackGround for the parallax
    frontBG = LoadTexture("assets/BackGrounds/PlainsForest/4.png");
    midBG = LoadTexture("assets/BackGrounds/PlainsForest/3.png");
    backBG = LoadTexture("assets/BackGrounds/PlainsForest/1.png");
    cloudBG = LoadTexture("assets/BackGrounds/PlainsForest/2.png");

    ///<    Texture Temp
    Texture2D temp = LoadTexture("assets/UI/Buttons/button_rectangle_depth_line.png");
    ///!<------- Creation of Buttons -------->
    ///<    Creation of 3 buttons
    CustomScale(1.f);
        float midScrenTexture = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
        btt_StartGame = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 540.f});
        btt_Option = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 700.f});
        btt_Exit =  CreateButton(pathT1,pathT2,(Vector2){midScrenTexture, 860.f});
        Vector2 posBes = {.x =1700, .y = 90};
    CustomScale(.6f);
        btt_Bestiary = CreateButton("assets/UI/BookInformation.png","assets/UI/BookInformation.png",posBes);
    CustomScale(1.f);
    ///!<------- Position of the text for the buttons ------->
    ///<    Memory allocation for the positions of the text
    bar = (Vector2*)calloc(3,sizeof(Vector2));
    foo = (Vector2*)calloc(3,sizeof(Vector2));
    ///<    Font for buttons
    bar[0] = MeasureTextEx(fontType, "Iniciar Juego", 40, 0);
    bar[1] = MeasureTextEx(fontType, "Opciones",40,0);
    bar[2] = MeasureTextEx(fontType, "Salir",40,0);
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
    ///!<------------- Init stuff for MainMenuScene ------------->]
    ///< Shader configuration
    ///< Value's for Outline Shader
    SetShaderValue(shaders[S_OUTLINE], GetShaderLocation(shaders[S_OUTLINE], "resolution"), (float[2]){ (float)btt_Bestiary->Texture[1].width, (float)btt_Bestiary->Texture[1].height }, SHADER_UNIFORM_VEC2);
    SetShaderValue(shaders[S_OUTLINE], GetShaderLocation(shaders[S_OUTLINE], "outlineThickness"), (float[1]){ 5.f }, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders[S_OUTLINE], GetShaderLocation(shaders[S_OUTLINE], "outlineColor"), (float[3]){ 1.0f, 1.0f, 1.0f }, SHADER_UNIFORM_VEC3);
    ///<    Play Music for the MainMenuScene
    PlayMusicStream(music[MS_MAINMENU]);
    ///<    Scroll init for the background
    sfBG = 0.f;
    smBG = 0.f;
    scBG = 0.f;
    sbBG = 0.f;
    ///!<------------- UnLoad Textures ----------->
    UnloadTexture(temp);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateMenuScene(void)
{
    ///!<---- Background Draw -->
    ///< Background Layer
    DrawParallax(backBG,    &sbBG, 0.f, 3.5f, 0.f);
    DrawParallax(cloudBG,   &scBG, 0.1f, 3.5f, 0.f);
    DrawParallax(midBG,     &smBG, 0.5f, 3.5f, 0.f);
    DrawParallax(frontBG,   &sfBG, 1.f, 3.5f, 0.f);
    ///!<---- Logo Draw -->
    ///<    Centered at the top of the screen, with a custom scale applied.
    float posLogo = (float)GetScreenWidth() / 2.f - (float)Logo.width / 2.f * scale.ScaleUniform;
    DrawTexturePro(
        Logo,
        (Rectangle){.x=0,.y=0,.width=(float)Logo.width,.height=(float)Logo.height},
        (Rectangle){.x =posLogo, .y=10.f, .width = (float)Logo.width * scale.ScaleUniform,.height=(float)Logo.height * scale.ScaleUniform},
        (Vector2){0,0},
        0,
        WHITE);
    ///!<---- Buttons Draw -->
    DrawButton(btt_StartGame,"Iniciar Juego",foo[0],fontType,40, BLACK);      ///< Start Game Button
    DrawButton(btt_Option,"Opciones",foo[1],fontType,40, BLACK);              ///< Options Button
    DrawButton(btt_Exit,"Salir",foo[2],fontType,40, BLACK);                   ///< Exit Game Button
    DrawButton(btt_Bestiary,"",foo[3],fontType,40,BLACK);

#if DEBUG
    DrawRectangleLinesEx(btt_Bestiary->destinationButton,3.f,RED);
#endif

    ///!<---- Collision logic -->
    if (CheckCollisionPointRec(mouse,btt_StartGame->destinationButton))
    {
        AccionButton(btt_StartGame,fontType,"Iniciar Juego",S_INVERT,foo[0],sLOADSCREEN,MS_MAINMENU,MS_GAMESTATE,0.f,40,true, WHITE,BLACK);
    }
    else if(CheckCollisionPointRec(mouse, btt_Option->destinationButton))
    {
        AccionButton(btt_Option,fontType,"Opciones",S_INVERT,foo[1],sOPTIONMENU,MS_NONE,MS_NONE,0.f,40,true,WHITE,BLACK);
        scenes->previousScene = sMAINMENU;
    }
    else if(CheckCollisionPointRec(mouse, btt_Exit->destinationButton))
        AccionButton(btt_Exit,fontType,"Salir",S_INVERT,foo[2],sEXIT_GAME,MS_NONE,MS_NONE,0.1f,40,true,WHITE,BLACK);
    else if(CheckCollisionPointRec(mouse,btt_Bestiary->destinationButton))
    {
        scrollVeyx.cur = scrollVeyx.first;
        AccionButton(btt_Bestiary,fontType,"",S_OUTLINE,foo[3],sBESTIARY,MS_NONE,MS_NONE,0.f,40,true,WHITE,BLACK);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyMenuScene(void)
{
    for (size_t i = 0; i < 2; i++)
    {
        UnloadTexture(btt_StartGame->Texture[i]);
        UnloadTexture(btt_Option->Texture[i]);
        UnloadTexture(btt_Exit->Texture[i]);
        UnloadTexture(btt_Bestiary->Texture[i]);
    }
    
    free(btt_StartGame->Texture);
    free(btt_Option->Texture);
    free(btt_Exit->Texture);
    free(btt_Bestiary->Texture);
    
    UnloadTexture(frontBG);
    UnloadTexture(midBG);
    UnloadTexture(cloudBG);
    UnloadTexture(backBG);
    UnloadTexture(Logo);

    free(foo);
    free(bar);
    
    free(btt_StartGame);
    free(btt_Option);
    free(btt_Exit);
    free(btt_Bestiary);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


