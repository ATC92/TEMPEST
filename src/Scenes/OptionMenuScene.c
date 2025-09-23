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
    bg = LoadTexture("assets/BackGrounds/Vorealis.png");
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
    btt_dot = CreateButton(pathT1,pathT2,(Vector2){midScreenDot - 300,350.f});
    btt_dot->action = gameConfig.fullscreen ? true : false;
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
    ///< Position for Text Dot
    Vector2 pos = (Vector2){(float)GetScreenWidth() / 2 - 250.f , btt_dot->position.y + 15};
    ///< BackGround
    DrawTexturePro
    (
        bg,
        (Rectangle){.x=0,.y=0,.height=(float)bg.height,.width=(float)bg.width},
        (Rectangle){.x=0,.y=0,.height = (float)GetScreenHeight(),.width= (float)GetScreenWidth()},
        (Vector2){0,0},
        0,
        WHITE
    );
    ///< Mouse Position
    mouse = GetMousePosition();
    ///< DrawButtons
    DrawButton(btt_Return,"Regresar",foo,*fontType,BLACK);
    DrawButton(btt_dot,"Activar/Desactivar pantalla completa",pos,*fontType,WHITE);
    // DrawTextEx(*fontType,"Activar/Desactivar pantalla completa",pos,40,0,WHITE);
    DrawTexturePro(btt_dot->Texture[btt_dot->action ? true : false], btt_dot->sourceButton,btt_dot->destinationButton, (Vector2){0,0}, 0, WHITE);
    ///< Reset all States
    btt_Return->state = NORMAL;
    btt_dot->state = NORMAL;
    /**
     * Button for Return to MainMenuScene
     */
    if (CheckCollisionPointRec(mouse,btt_Return->boundingBox))
    {
        AccionButton(btt_Return,*fontType,"Regresar",Invert,foo,MainMenu,0.1f,true,WHITE);
        // DrawTextEx(*fontType,"Activar/Desactivar pantalla completa",pos,40,0,WHITE);
    }
    /**
     * Button to Togle FullScreen.
     */
    else if(CheckCollisionPointRec(mouse,btt_dot->boundingBox))
    {
        AccionButton(btt_dot,*fontType,"Activar/Desactivar pantalla completa",Invert,pos,OptionMenu,0.1f,false, WHITE);
        // BeginShaderMode(invert);
        //     btt_dot->state = MOUSE_OVER;
        //     DrawTextEx(*fontType,"Activar/Desactivar pantalla completa",pos,40,0,BLACK);
        // EndShaderMode();
        // DrawTextEx(*fontType,"Regresar",foo,40,0,BLACK);
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
            SaveConfig(gameConfig, CONFIG_FILE);
            waitingCooldown = false;
        }
    }
}

void DestroyOptionMenuScene(void)
{

}