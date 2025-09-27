#include "../Engine/Engine.h"
#include "../Engine/Config.h"
#include "../Game/Game.h"
//////////////////////////////////////////////////////////////////
int main(void)
{
    gameConfig = LoadConfig(CONFIG_FILE);            ///< LoadConfiguration for the engine
    float dt = 0.0f;                                            ///< Delta Time Init
    InitWindow(gameConfig.height, gameConfig.width, "Project V-Beta");          ///< Set Name of the window
    if(gameConfig.fullscreen == 1)
    {   
        SetWindowSize(GetMonitorWidth(0),GetMonitorHeight(0));
        ToggleFullscreen();
    }
    else SetWindowSize(gameConfig.width,gameConfig.height);
    SetTargetFPS(60);                                           ///< Set FPS
    InitEngine();                                               ///< Init Engine
    while (!WindowShouldClose())                                ///< Main loop for the game
    {
        if(scenes->typeScene == sEXIT_GAME)
            break;
        dt = GetFrameTime();                                    ///< Get Delta Time
        EngineUpdate(dt);                                       ///< Game Engine Update
        BeginDrawing();                                         ///< || Start Drawing, RayLib Context
            ClearBackground(RAYWHITE);                              ///< Give a color to the Background
            EngineRender();                                         ///< Game Engine Render
        EndDrawing();                                           ///< || End Drawing, RalyLib Context
    }
    DestroyEngine();                                            ///< Destroy Game Engine
    CloseWindow();                                              ///< Close Window OpenGL Context
    return EXIT_SUCCESS;                                        ///< Close main correctly
}
//////////////////////////////////////////////////////////////////



