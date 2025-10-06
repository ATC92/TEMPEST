///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "OptionMenuScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Private declarations
static Button* btt_ESC;
static Button* btt_MainMenu;
static Button* btt_FullScreen;
static Button* btt_statesFS;
static Button* btt_Volume;
static Button* btt_VolumeNum;
static Vector2* bar;
static Vector2* foo;
static Texture2D bg;
static Texture2D Line;
static Texture2D Dott;
static Texture2D k_ESC;
static Rectangle posLine,posDot;
static RenderTexture2D targetBlur;
static double startTime;
static bool waitingCooldown;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitOptionMenuScene(void)
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    bar = (Vector2*)calloc(3,sizeof(Vector2));
    foo = (Vector2*)calloc(4,sizeof(Vector2));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------ Loading Textures ------>
    ///<    BackGround
    bg = LoadTexture("assets/BackGrounds/Vorealis.png");
    targetBlur = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    ///<    Information for the Buttons (Path)
    // char* pathT1 = "assets/UI/Buttons/check_round_grey.png";
    // char* pathT2 = "assets/UI/Buttons/check_round_round_circle.png";
    char* pathT3 = "assets/UI/Buttons/button_rectangle_depth_line.png";
    char* pathT4 = "assets/UI/Buttons/button_rectangle_line.png";
    ///<    Texture Temp for buttons position
    Texture2D temp = LoadTexture("assets/UI/Buttons/button_rectangle_depth_line.png");
    // Texture2D tempDot = LoadTexture("assets/UI/Buttons/check_round_grey.png");

    Line = LoadTexture("assets/UI/Buttons/slide_horizontal_grey-export.png");
    Dott = LoadTexture("assets/UI/Buttons/icon_circle.png");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------- Creation of Buttons -------->
    ///<    Button creation
    float midScreenButton = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    ///<    Button for Return to MainMenuScene
    btt_MainMenu = CreateButton(pathT3,pathT4,(Vector2){midScreenButton,800.f});
    ///<    Keys Loading
    k_ESC = LoadTexture("assets/UI/Keys/White/ESC.png");
    ///<    Button ESC
    Vector2 barESC = MeasureTextEx(fontType,"Regresar",30,0);
    CustomScale(2.f);
        btt_ESC = CreateButton("assets/UI/Keys/White/ESC.png","assets/UI/Keys/White/ESC.png",(Vector2)
        {
            .x = (float)GetScreenWidth() - (float)k_ESC.width * scale.ScaleUniform - 10 - barESC.x,
            .y = (float)GetScreenHeight() - (float)k_ESC.height * scale.ScaleUniform- 10,
        });
    CustomScale(1.f);
    foo[0] = (Vector2)
    {
        .x = (btt_ESC->destinationButton.x + btt_ESC->destinationButton.width / 2) + barESC.x/6,
        .y = (btt_ESC->destinationButton.y + btt_ESC->destinationButton.height / 2) - barESC.y / 2
    };
    btt_ESC->boundingBox = (Rectangle)
    {
        .x = btt_ESC->destinationButton.x,
        .y = btt_ESC->destinationButton.y,
        .width = btt_ESC->destinationButton.width + barESC.x,
        .height = btt_ESC->destinationButton.height
    };

    ///<    Button for fullScreen
    btt_FullScreen = CreateButton(pathT3,pathT4,(Vector2){(float)( (float)GetScreenWidth() / 2 - (float)temp.width / 2.0f *2.f), 318});
    btt_FullScreen->destinationButton.width *= 2;

    ///< Button for Volume
    btt_Volume = CreateButton(pathT3,pathT4,(Vector2){ (float)((float)GetScreenWidth() / 2 - (float)temp.width / 2.0f * 0.5),530});
    ///< Position for Line && Dot Music Master Volume
    btt_Volume->destinationButton.width *= 0.5f;
    btt_Volume->destinationButton.height *= 0.5f;
    bar[2] = MeasureTextEx(fontType, "Volumen", 30, 0);
    foo[3] = (Vector2)
    {
        .x = (btt_Volume->position.x + btt_Volume->destinationButton.width / 2) - bar[2].x/2,
        .y = (btt_Volume->position.y + btt_Volume->destinationButton.height / 2) - bar[2].y/2
    };
    posLine = (Rectangle)
    {
        .x = (float)GetScreenWidth()/2 - (float)Line.width / 2,
        .y = 600,
        .height = (float)Line.height,
        .width = (float)Line.width
    };
    posDot = (Rectangle)
    {
        .x = posLine.x,
        .y = posLine.y,
        .width = (float)Dott.width * 1.5f,
        .height = (float)Dott.height * 1.5f
    };
    
    minX = posLine.x;
    maxX = posLine.x + posLine.width;
    ///< Button VolumenNumber
    CustomScale(1.5f);
    btt_VolumeNum = CreateButton("assets/UI/Buttons/slide_hangle.png","assets/UI/Buttons/slide_hangle.png",(Vector2){posDot.x + 50, posDot.y - 35});
    CustomScale(1.f);
    ///< States FullScreen button
    btt_statesFS = CreateButton("assets/UI/Buttons/icon_checkmark.png","assets/UI/Buttons/icon_cross.png",(Vector2){
        .x = btt_FullScreen->position.x + 55,
        .y = btt_FullScreen->position.y + 43,
    });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------- Position of the text for the buttons ------->
    ///<    Font for buttons
    bar[0] = MeasureTextEx(fontType, "Menu Principal", 40, 0);
    foo[1] = (Vector2)
    {
        .x = (btt_MainMenu->position.x + btt_MainMenu->sourceButton.width / 2) - bar[0].x / 2,
        .y = (btt_MainMenu->position.y + btt_MainMenu->sourceButton.height / 2) - bar[0].y / 2
    };  
    ///<    Font for FullScreen
    bar[1] = MeasureTextEx(fontType,"Activar/Desactivar pantalla completa",30,0);
    foo[2] = (Vector2)
    {
        .x = (btt_FullScreen->position.x + btt_FullScreen->destinationButton.width / 2) - bar[1].x/2 + 20,
        .y = (btt_FullScreen->position.y + btt_FullScreen->sourceButton.height / 2) - bar[1].y/2
    };
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------- Unload Textures ------>
    UnloadTexture(temp);
    UnloadTexture(k_ESC);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateOptionMenuScene(void)
{
    ///<    Position for Text Dot
    // Vector2 pos = (Vector2){(float)GetScreenWidth() / 2 - 250.f , btt_dot->position.y + 15};
    ///!<-------------- Blur Effect ------------->
    if(scenes->previousScene == sGAMESTATE)
    {
        BeginTextureMode(targetBlur);
            UpdateGameRender();
        EndTextureMode();

        BeginShaderMode(shaders[S_BLUR]);
            float res[2] = {(float)GetScreenWidth(), (float)GetScreenHeight()};
            float r = 4.0f;
            SetShaderValue(shaders[S_BLUR], GetShaderLocation(shaders[S_BLUR], "resolution"), res, SHADER_UNIFORM_VEC2);
            SetShaderValue(shaders[S_BLUR], GetShaderLocation(shaders[S_BLUR], "radius"), &r, SHADER_UNIFORM_FLOAT);
            DrawTextureRec(targetBlur.texture,
                        (Rectangle){0,0,(float)targetBlur.texture.width, (float)-targetBlur.texture.height},
                        (Vector2){0,0}, WHITE);
        EndShaderMode();
    }
    else 
        ///<    BackGround draw
        DrawTexturePro
        (
            bg,
            (Rectangle){.x=0,.y=0,.height=(float)bg.height,.width=(float)bg.width},
            (Rectangle){.x=0,.y=0,.height = (float)GetScreenHeight(), .width= (float)GetScreenWidth()},
            (Vector2){0,0},
            0,
            WHITE
        );
    ////////////////////////////////////////////////////
    ///<    DrawButtons
    ///<    <IF>[Prev Scene == MainMenu] Draw return mainmenu button.
    DrawButton(btt_Volume,"Volumen",foo[3],fontType,30.f,BLACK);
    DrawButton(btt_FullScreen,"Activar/Desactivar pantalla completa",foo[2],fontType,30,BLACK);
    DrawButton(btt_ESC,"Regresar",foo[0],fontType,30, WHITE);
    DrawTexturePro(btt_statesFS->Texture[IsWindowState(FLAG_FULLSCREEN_MODE) ? 0 : 1],btt_statesFS->sourceButton,btt_statesFS->destinationButton,(Vector2){0,0},0,WHITE);

    // float knobX = posLine.x + masterVolume * posLine.width;
    posDot.x = minX + masterVolume * (maxX - minX);
    btt_VolumeNum->destinationButton.x = posDot.x + 11;
    DrawTexturePro(Line,(Rectangle){.x=0,.y=0,.width=(float)Line.width,.height=(float)Line.height},posLine,(Vector2){0,0},0,WHITE);
    DrawTexturePro(Dott,(Rectangle){.x=0,.y=0,.width=(float)Dott.width,.height=(float)Dott.height},posDot,(Vector2){0,0},0,WHITE);
    SoundBarFollowPoint(btt_VolumeNum,&posDot);

    if(scenes->previousScene == sGAMESTATE)
        DrawButton(btt_MainMenu,"Menu Principal",foo[1],fontType,40,BLACK);
    ///<    Collision Logic
#if DEBUG
    DrawRectangleLinesEx(btt_ESC->boundingBox,2.f,RED);
    DrawRectangleLinesEx(posDot,2.f,BLUE);
    DrawRectangleLinesEx(posLine,2.f,RED);
#endif

    if (CheckCollisionPointRec(mouse,btt_ESC->boundingBox))
        if(scenes->previousScene == sGAMESTATE)
            AccionButton(btt_ESC,fontType,"Regresar",S_INVERT,foo[0],sGAMESTATE,MS_NONE,MS_NONE,0.1f,30,true,WHITE,WHITE);
        else
            AccionButton(btt_ESC,fontType,"Regresar",S_INVERT,foo[0],sMAINMENU,MS_NONE,MS_NONE,0.1f,30,true,WHITE,GRAY);
    else if (CheckCollisionPointRec(mouse,btt_MainMenu->boundingBox) && scenes->previousScene == sGAMESTATE)
        AccionButton(btt_MainMenu,fontType,"Menu Principal",S_INVERT,foo[1],sMAINMENU,MS_GAMESTATE,MS_MAINMENU,0.1f,40,true,WHITE,BLACK);
    else if(CheckCollisionPointRec(mouse,btt_FullScreen->destinationButton))
    {
        AccionButton(btt_FullScreen,fontType,"Activar/Desactivar pantalla completa",S_INVERT,foo[2],sOPTIONMENU,MS_NONE,MS_NONE,0.1f,30,false, WHITE,BLACK);
        BeginShaderMode(shaders[S_INVERT]);
            DrawTexturePro(btt_statesFS->Texture[IsWindowState(FLAG_FULLSCREEN_MODE) ? 0 : 1],btt_statesFS->sourceButton,btt_statesFS->destinationButton,(Vector2){0,0},0,WHITE);
        EndShaderMode();
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            startTime = GetTime();
            waitingCooldown = true;
        }
        if(waitingCooldown && (GetTime() - startTime) >= 0.01)
        {
            PlaySound(sounds[0]);
            ToggleFullscreen();
            btt_FullScreen->action = IsWindowState(FLAG_FULLSCREEN_MODE) ? true : false;
            gameConfig.fullscreen = (int)btt_FullScreen->action;
            waitingCooldown = false;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyOptionMenuScene(void)
{
    for(size_t i = 0; i < 2; i++)
    {
        UnloadTexture(btt_ESC->Texture[i]);
        UnloadTexture(btt_Volume->Texture[i]);
        UnloadTexture(btt_MainMenu->Texture[i]);
        UnloadTexture(btt_FullScreen->Texture[i]);
        UnloadTexture(btt_statesFS->Texture[i]);
    }

    free(btt_ESC->Texture);
    free(btt_Volume->Texture);
    free(btt_statesFS->Texture);
    free(btt_MainMenu->Texture);
    free(btt_FullScreen->Texture);

    free(btt_ESC);
    free(btt_Volume);
    free(btt_statesFS);
    free(btt_MainMenu);
    free(btt_FullScreen);
    
    free(bar);
    free(foo);

    UnloadTexture(bg);
    UnloadRenderTexture(targetBlur);
    UnloadTexture(Line);
    UnloadTexture(Dott);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////