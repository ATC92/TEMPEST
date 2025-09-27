//////////////////////////////////////////////////////////////////////////////
#include "OptionMenuScene.h"
//////////////////////////////////////////////////////////////////////////////
///< Private declarations
static Button* btt_Return;
static Button* btt_dot;
static Button* btt_MainMenu;
static Vector2 foo, bar,fooMM;
static Texture2D bg;
static double startTime;
static bool waitingCooldown;
//////////////////////////////////////////////////////////////////////////////
void InitOptionMenuScene(void)
{
    ///!<------ Loading Textures ------>
    ///<    BackGround
    bg = LoadTexture("assets/BackGrounds/Vorealis.png");
    ///<    Information for the Buttons (Path)
    char* pathT1 = "assets/UI/check_round_grey.png";
    char* pathT2 = "assets/UI/check_round_round_circle.png";
    char* pathT3 = "assets/UI/button_rectangle_depth_line.png";
    char* pathT4 = "assets/UI/button_rectangle_line.png";
    ///<    Texture Temp for buttons position
    Texture2D temp = LoadTexture("assets/UI/button_rectangle_depth_line.png");
    Texture2D tempDot = LoadTexture("assets/UI/check_round_grey.png");
    ///!<------- Creation of Buttons -------->
    ///<    Button creation (DOT)
    float midScreenButton = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    float midScreenDot = {(float)GetScreenWidth() / 2 - (float)tempDot.width / 2.0f};
    btt_dot = CreateButton(pathT1,pathT2,(Vector2){midScreenDot - 300,350.f});
    btt_dot->action = gameConfig.fullscreen ? true : false;
    ///< Button for Return to MainMenuScene
    btt_MainMenu = CreateButton(pathT3,pathT4,(Vector2){midScreenButton,600.f});
    ///< Button creation Return
    btt_Return = CreateButton(pathT3,pathT4,(Vector2){midScreenButton,800.f});
    ///!<------- Position of the text for the buttons ------->
    ///<    Font for buttons
    bar = MeasureTextEx(*fontType, "Menu Principal", 40, 0);
    fooMM = (Vector2)
    {
        .x = (btt_MainMenu->position.x + btt_MainMenu->sourceButton.width / 2) - bar.x / 2,
        .y = (btt_MainMenu->position.y + btt_MainMenu->sourceButton.height / 2) - bar.y / 2
    };  
    ///<    Font for Return button
    bar = MeasureTextEx(*fontType, "Regresar", 40, 0);
    foo = (Vector2)
    {
        .x = (btt_Return->position.x + btt_Return->sourceButton.width / 2) - bar.x / 2,
        .y = (btt_Return->position.y + btt_Return->sourceButton.height / 2) - bar.y / 2
    };
    ///!<------- Unload Textures ------>
    UnloadTexture(temp);
    UnloadTexture(tempDot);
}

void UpdateOptionMenuScene(void)
{
    ///<    Mouse Position
    mouse = GetMousePosition();
    ///<    Position for Text Dot
    Vector2 pos = (Vector2){(float)GetScreenWidth() / 2 - 250.f , btt_dot->position.y + 15};
    ///<    BackGround draw
    DrawTexturePro
    (
        bg,
        (Rectangle){.x=0,.y=0,.height=(float)bg.height,.width=(float)bg.width},
        (Rectangle){.x=0,.y=0,.height = (float)GetScreenHeight(),.width= (float)GetScreenWidth()},
        (Vector2){0,0},
        0,
        WHITE
    );
    ////////////////////////////////////////////////////

    Rectangle bar = { (float)GetScreenWidth() / 2 - 200 / 2, 500, 200, 20 };
    float knobX = bar.x + masterVolume * bar.width;
    DrawRectangleRec(bar, GRAY);
    DrawRectangle(bar.x, bar.y, masterVolume * bar.width, bar.height, DARKGREEN);
    DrawCircle(knobX, bar.y + bar.height/2, 10, RAYWHITE);

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, bar)) {
            // Calcular porcentaje
            masterVolume = (mouse.x - bar.x) / bar.width;

            // Clamp para que no se salga
            if (masterVolume < 0.0f) masterVolume = 0.0f;
            if (masterVolume > 1.0f) masterVolume = 1.0f;
            if (currentMusic != MS_NONE)
                SetMusicVolume(music[currentMusic], masterVolume);
        }   
    }

    ///<    DrawButtons
    ///<    <IF>[Prev Scene == MainMenu] Draw return mainmenu button.
    DrawButton(btt_Return,"Regresar",foo,*fontType,BLACK);
    DrawButton(btt_dot,"Activar/Desactivar pantalla completa",pos,*fontType,WHITE);
    if(scenes->previousScene == sGAMESTATE)
        DrawButton(btt_MainMenu,"Menu Principal",fooMM,*fontType,BLACK);
    DrawTexturePro(btt_dot->Texture[btt_dot->action ? true : false], btt_dot->sourceButton,btt_dot->destinationButton, (Vector2){0,0}, 0, WHITE);
    ///<    Collision Logic
    if (CheckCollisionPointRec(mouse,btt_Return->boundingBox))
        if(scenes->previousScene == sGAMESTATE)
            AccionButton(btt_Return,*fontType,"Regresar",S_INVERT,foo,sGAMESTATE,MS_NONE,MS_NONE,0.1f,true,WHITE);
        else
            AccionButton(btt_Return,*fontType,"Regresar",S_INVERT,foo,sMAINMENU,MS_NONE,MS_NONE,0.1f,true,WHITE);
    else if (CheckCollisionPointRec(mouse,btt_MainMenu->boundingBox) && scenes->previousScene == sGAMESTATE)
        AccionButton(btt_MainMenu,*fontType,"Menu Principal",S_INVERT,fooMM,sMAINMENU,MS_GAMESTATE,MS_MAINMENU,0.1f,true,WHITE);
    else if(CheckCollisionPointRec(mouse,btt_dot->boundingBox))
    {
        AccionButton(btt_dot,*fontType,"Activar/Desactivar pantalla completa",S_INVERT,pos,sOPTIONMENU,MS_NONE,MS_NONE,0.1f,false, WHITE);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            startTime = GetTime();
            waitingCooldown = true;
        }
        if(waitingCooldown && (GetTime() - startTime) >= 0.1)
        {
            PlaySound(sounds[0]);
            ToggleFullscreen();
            btt_dot->action = IsWindowState(FLAG_FULLSCREEN_MODE) ? true : false;
            gameConfig.fullscreen = (int)btt_dot->action;
            // SaveConfig(gameConfig, CONFIG_FILE);
            waitingCooldown = false;
        }
    }
}

void DestroyOptionMenuScene(void)
{
    for(size_t i = 0; i < 2; i++)
    {
        UnloadTexture(btt_Return->Texture[i]);
        UnloadTexture(btt_dot->Texture[i]);
    }
    free(btt_Return);
    free(btt_dot);
    UnloadTexture(bg);
}