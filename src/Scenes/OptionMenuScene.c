///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "OptionMenuScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Private declarations
static Button** buttons;
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
    buttons = (Button**)calloc(6,sizeof(Button*));
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------ Loading Textures ------>
    ///<    BackGround
    bg = LoadTexture(ASSETS"/BackGrounds/Vorealis.png");
    targetBlur = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    ///<    Information for the Buttons (Path)
    // char* pathT1 = "assets/UI/Buttons/check_round_grey.png";
    // char* pathT2 = "assets/UI/Buttons/check_round_round_circle.png";
    char* pathT3 = ASSETS"/UI/Buttons/button_rectangle_depth_line.png";
    char* pathT4 = ASSETS"/UI/Buttons/button_rectangle_line.png";
    ///<    Texture Temp for buttons position
    Texture2D temp = LoadTexture(pathT3);
    // Texture2D tempDot = LoadTexture("assets/UI/Buttons/check_round_grey.png");

    Line = LoadTexture(ASSETS"/UI/Buttons/slide_horizontal_grey-export.png");
    Dott = LoadTexture(ASSETS"/UI/Buttons/icon_circle.png");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------- Creation of Buttons -------->
    ///<    Button creation
    float midScreenButton = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    ///<    Button for Return to MainMenuScene
    buttons[_BTT_MAINMENU] = CreateButton(pathT3,pathT4,(Vector2){midScreenButton,800.f});
    ///<    Keys Loading
    k_ESC = LoadTexture(ASSETS"/UI/Keys/White/ESC.png");
    ///<    Button ESC
    Vector2 barESC = MeasureTextEx(fontType,"Regresar",30,0);
    CustomScale(2.f);
        buttons[_BTT_ESC] = CreateButton(ASSETS"/UI/Keys/White/ESC.png",ASSETS"/UI/Keys/White/ESC.png",(Vector2)
        {
            .x = (float)GetScreenWidth() - (float)k_ESC.width * scale.ScaleUniform - 10 - barESC.x,
            .y = (float)GetScreenHeight() - (float)k_ESC.height * scale.ScaleUniform- 10,
        });
    CustomScale(1.f);
    foo[0] = (Vector2)
    {
        .x = (buttons[_BTT_ESC]->destinationButton.x + buttons[_BTT_ESC]->destinationButton.width / 2) + barESC.x/6,
        .y = (buttons[_BTT_ESC]->destinationButton.y + buttons[_BTT_ESC]->destinationButton.height / 2) - barESC.y / 2
    };
    buttons[_BTT_ESC]->boundingBox = (Rectangle)
    {
        .x = buttons[_BTT_ESC]->destinationButton.x,
        .y = buttons[_BTT_ESC]->destinationButton.y,
        .width = buttons[_BTT_ESC]->destinationButton.width + barESC.x,
        .height = buttons[_BTT_ESC]->destinationButton.height
    };

    ///<    Button for fullScreen
    buttons[_BTT_FULLSCREEN] = CreateButton(pathT3,pathT4,(Vector2){(float)( (float)GetScreenWidth() / 2 - (float)temp.width / 2.0f *2.f), 318});
    buttons[_BTT_FULLSCREEN]->destinationButton.width *= 2;

    ///< Button for Volume
    buttons[_BTT_VOLUME] = CreateButton(pathT3,pathT4,(Vector2){ (float)((float)GetScreenWidth() / 2 - (float)temp.width / 2.0f * 0.5),530});
    ///< Position for Line && Dot Music Master Volume
    buttons[_BTT_VOLUME]->destinationButton.width *= 0.5f;
    buttons[_BTT_VOLUME]->destinationButton.height *= 0.5f;
    bar[2] = MeasureTextEx(fontType, "Volumen", 30, 0);
    foo[3] = (Vector2)
    {
        .x = (buttons[_BTT_VOLUME]->position.x + buttons[_BTT_VOLUME]->destinationButton.width / 2) - bar[2].x/2,
        .y = (buttons[_BTT_VOLUME]->position.y + buttons[_BTT_VOLUME]->destinationButton.height / 2) - bar[2].y/2
    };
    posLine = (Rectangle)
    {
        .x = ((float)GetScreenWidth()/2 - (float)Line.width / 2) - 20,
        .y = 600,
        .height = (float)Line.height,
        .width = (float)Line.width + 20
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
    buttons[_BTT_vDOT] = CreateButton(ASSETS"/UI/Buttons/slide_hangle.png",ASSETS"/UI/Buttons/slide_hangle.png",(Vector2){posDot.x + 20, posDot.y - 48});
    CustomScale(1.f);
    ///< States FullScreen button
    buttons[_BTT_STATES] = CreateButton(ASSETS"/UI/Buttons/icon_checkmark.png",ASSETS"/UI/Buttons/icon_cross.png",(Vector2){
        .x = buttons[_BTT_FULLSCREEN]->position.x + 55,
        .y = buttons[_BTT_FULLSCREEN]->position.y + 43,
    });

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------- Position of the text for the buttons ------->
    ///<    Font for buttons
    bar[0] = MeasureTextEx(fontType, "Menu Principal", 40, 0);
    foo[1] = (Vector2)
    {
        .x = (buttons[_BTT_MAINMENU]->position.x + buttons[_BTT_MAINMENU]->sourceButton.width / 2) - bar[0].x / 2,
        .y = (buttons[_BTT_MAINMENU]->position.y + buttons[_BTT_MAINMENU]->sourceButton.height / 2) - bar[0].y / 2
    };  
    ///<    Font for FullScreen
    bar[1] = MeasureTextEx(fontType,"Activar/Desactivar pantalla completa",30,0);
    foo[2] = (Vector2)
    {
        .x = (buttons[_BTT_FULLSCREEN]->position.x + buttons[_BTT_FULLSCREEN]->destinationButton.width / 2) - bar[1].x/2 + 20,
        .y = (buttons[_BTT_FULLSCREEN]->position.y + buttons[_BTT_FULLSCREEN]->sourceButton.height / 2) - bar[1].y/2
    };
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///!<------- Unload Textures ------>
    UnloadTexture(temp);
    UnloadTexture(k_ESC);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateOptionMenuScene(void)
{
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
    {
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
    }
    ////////////////////////////////////////////////////
    ///<    DrawButtons
    ///<    <IF>[Prev Scene == MainMenu] Draw return mainmenu button.
    DrawButton(buttons[_BTT_VOLUME],"Volumen",foo[3],fontType,30.f,BLACK);
    DrawButton(buttons[_BTT_FULLSCREEN],"Activar/Desactivar pantalla completa",foo[2],fontType,30,BLACK);
    DrawButton(buttons[_BTT_ESC],"Regresar",foo[0],fontType,30, WHITE);
    DrawTexturePro(buttons[_BTT_STATES]->Texture[IsWindowState(FLAG_FULLSCREEN_MODE) ? 0 : 1],buttons[_BTT_STATES]->sourceButton,buttons[_BTT_STATES]->destinationButton,(Vector2){0,0},0,WHITE);

    if(CheckCollisionPointRec(mouse,posLine))
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            posDot.x = mouse.x;
    SoundBarFollowPoint(buttons[_BTT_vDOT],&posDot);
    posDot.x = minX + masterVolume * (maxX - minX);
    buttons[_BTT_vDOT]->destinationButton.x = posDot.x;
    DrawTexturePro(Line,(Rectangle){.x=0,.y=0,.width=(float)Line.width,.height=(float)Line.height},(Rectangle){.x =posLine.x, .y = posLine.y, .width = posLine.width + 30, .height = posLine.height},(Vector2){0,0},0,WHITE);
    DrawTexturePro(Dott,(Rectangle){.x=0,.y=0,.width=(float)Dott.width,.height=(float)Dott.height},posDot,(Vector2){0,0},0,WHITE);
    
    if(scenes->previousScene == sGAMESTATE)
        DrawButton(buttons[_BTT_MAINMENU],"Menu Principal",foo[1],fontType,40,BLACK);
    ///<    Collision Logic
#if DEBUG
    DrawRectangleLinesEx(buttons[_BTT_ESC]->boundingBox,2.f,RED);
    DrawRectangleLinesEx(posDot,2.f,BLUE);
    DrawRectangleLinesEx(posLine,2.f,RED);
#endif

    if (CheckCollisionPointRec(mouse,buttons[_BTT_ESC]->boundingBox))
        if(scenes->previousScene == sGAMESTATE)
            AccionButton(buttons[_BTT_ESC],fontType,"Regresar",S_INVERT,foo[0],sGAMESTATE,MS_NONE,MS_NONE,0.1f,30,true,WHITE,WHITE);
        else
            AccionButton(buttons[_BTT_ESC],fontType,"Regresar",S_INVERT,foo[0],sMAINMENU,MS_NONE,MS_NONE,0.1f,30,true,WHITE,GRAY);
    else if (CheckCollisionPointRec(mouse,buttons[_BTT_MAINMENU]->boundingBox) && scenes->previousScene == sGAMESTATE)
        AccionButton(buttons[_BTT_MAINMENU],fontType,"Menu Principal",S_INVERT,foo[1],sLOADSCREEN,MS_GAMESTATE,MS_MAINMENU,0.1f,40,true,WHITE,BLACK);
    else if(CheckCollisionPointRec(mouse,buttons[_BTT_FULLSCREEN]->destinationButton))
    {
        AccionButton(buttons[_BTT_FULLSCREEN],fontType,"Activar/Desactivar pantalla completa",S_INVERT,foo[2],sOPTIONMENU,MS_NONE,MS_NONE,0.1f,30,false, WHITE,BLACK);
        BeginShaderMode(shaders[S_INVERT]);
            DrawTexturePro(buttons[_BTT_STATES]->Texture[IsWindowState(FLAG_FULLSCREEN_MODE) ? 0 : 1],buttons[_BTT_STATES]->sourceButton,buttons[_BTT_STATES]->destinationButton,(Vector2){0,0},0,WHITE);
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
            buttons[_BTT_FULLSCREEN]->action = IsWindowState(FLAG_FULLSCREEN_MODE) ? true : false;
            gameConfig.fullscreen = (int)buttons[_BTT_FULLSCREEN]->action;
            waitingCooldown = false;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyOptionMenuScene(void)
{
    for(size_t i = 0; i < 2; i++)
    {
        UnloadTexture(buttons[_BTT_ESC]->Texture[i]);
        UnloadTexture(buttons[_BTT_VOLUME]->Texture[i]);
        UnloadTexture(buttons[_BTT_MAINMENU]->Texture[i]);
        UnloadTexture(buttons[_BTT_FULLSCREEN]->Texture[i]);
        UnloadTexture(buttons[_BTT_vDOT]->Texture[i]);
        UnloadTexture(buttons[_BTT_STATES]->Texture[i]);
    }

    for(size_t i=0; i <= _BTT_vDOT;i++)
    {
        free(buttons[i]->Texture);
        free(buttons[i]);
    }

    free(buttons);

    free(bar);
    free(foo);

    UnloadTexture(bg);
    UnloadRenderTexture(targetBlur);
    UnloadTexture(Line);
    UnloadTexture(Dott);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////