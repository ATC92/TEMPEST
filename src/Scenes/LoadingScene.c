#include "LoadingScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Private declaratios
static double startTime;
static float midX, midY, seconds;
static Vector2 bar, posText;
static bool loadingDone = false;
static Texture2D Logo;
///< Shaders
static int locDirection;
static int locTime;
static int locSpeed; 
static int locWidth;
static int locIntensity; 
static int locColor;
static int locOffset; 
static float timeShader;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitLoadingScene(float sec)
{
    midX = (float)GetScreenWidth() / 2;
    midY = (float)GetScreenHeight() / 2;
    bar = MeasureTextEx(fontType,"Cargando....",20,0);
    posText = (Vector2)
    {
        .x = midX - bar.x / 2,
        .y = midY - bar.y - 5
    };
    seconds = sec;
    timeShader = 0;

    if(IsPathFile("assets/Icons/VeyxTempest.png"))
        Logo = LoadTexture("assets/Icons/VeyxTempest.png");
    else 
        TraceLog(LOG_ERROR, "Texture couldnt load: assets/Icons/VeyxTempest.png");
    
    ///< SHADER Configuration
   locDirection  = GetShaderLocation(shaders[S_SHIELDGLOW], "uDirection");
   locTime  = GetShaderLocation(shaders[S_SHIELDGLOW], "uTime");
   locSpeed  = GetShaderLocation(shaders[S_SHIELDGLOW], "uSpeed");
   locWidth  = GetShaderLocation(shaders[S_SHIELDGLOW], "uWidth");
   locIntensity  = GetShaderLocation(shaders[S_SHIELDGLOW], "uIntensity");
   locColor  = GetShaderLocation(shaders[S_SHIELDGLOW], "uColor");
   locOffset  = GetShaderLocation(shaders[S_SHIELDGLOW], "uOffset");


   IsGameInit = false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateLoadingScene(void)
{
        
    if(!loadingDone)
    {
        startTime = GetTime();
        loadingDone = true;
    }
    if ((GetTime() - startTime) < seconds)
    {
        ClearBackground(BLACK);


        timeShader += GetFrameTime();

        float speed = 0.50f;
        float width = 0.12f;
        float intensity = 0.8f;
        Vector3 color = {1.0f, 1.0f, 1.0f};
        float offset = 0.0f;

        // Actualizar uniforms
        SetShaderValue(shaders[S_SHIELDGLOW], locDirection, &(Vector2){ 1.0f, 0.0f }, SHADER_UNIFORM_VEC2);
        SetShaderValue(shaders[S_SHIELDGLOW], locTime, &timeShader, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locSpeed, &speed, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locWidth, &width, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locIntensity, &intensity, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locColor, &color, SHADER_UNIFORM_VEC3);
        SetShaderValue(shaders[S_SHIELDGLOW], locOffset, &offset, SHADER_UNIFORM_FLOAT);

        BeginShaderMode(shaders[S_SHIELDGLOW]);
            CustomScale(0.5f);
                DrawTexturePro(
                    Logo,
                    (Rectangle){.x=0,.y=0,.width=(float)Logo.width,.height=(float)Logo.height},
                    (Rectangle){.x =(float)GetScreenWidth() - (float)Logo.width / 2 , .y=(float)GetScreenHeight() - (float)Logo.height / 2  , .width = (float)Logo.width * scale.ScaleUniform,.height=(float)Logo.height * scale.ScaleUniform},
                    (Vector2){0,0},
                    0,
                    WHITE);
            CustomScale(1.f);
        EndShaderMode();
        DrawTextEx(fontType,"Cargando....", posText, 20,0, WHITE);
        #if DEBUG
        DrawLinesMidScreen();
        #endif
        DrawRectangleLines((int)midX - 100,(int)midY,200,20,WHITE);
        DrawRectangle((int)midX - 100, (int)midY, (int)(((GetTime() - startTime) / seconds) * 200), 20, GREEN);

        if(IsGameInit == false)
        {
            ///< Init Game
            InitGameScene();
            IsGameInit = true;
        }
        
    }
    if((GetTime() - startTime) >= seconds)
    {
        ChangeScene(sGAMESTATE);
        loadingDone = false;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyLoadingScene(void)
{
    startTime = 0;
    midX = 0;
    midY = 0;
    bar = (Vector2){0};
    posText = (Vector2){0};

    UnloadTexture(Logo);
}
//////////////////////////////////////////////////////////
