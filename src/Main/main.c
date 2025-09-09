#include "../Engine/Engine.h"
#include "../Game/Game.h"
//////////////////////////////////////////////////////////////////
int main(void)
{
    int MonitorWidth = GetMonitorWidth(0);
    int MonitorHeight = GetMonitorHeight(0);
    float dt = 0.0f;   ///< Delta Time
    InitWindow(MonitorWidth, MonitorHeight, "Project V-Beta");        ///< Set Name of the window
    ToggleFullscreen();
    SetTargetFPS(60);                               ///< Set FPS
    InitEngine();                                   ///< Init Engine
    while (!WindowShouldClose())                    ///< Main loop for the game
    {
        dt = GetFrameTime();                  ///< Get Delta Time
        EngineUpdate(dt);                             ///< Game Engine Update
        BeginDrawing();                             ///< || Start Drawing, RayLib Context
            ClearBackground(RAYWHITE);              ///< Give a color to the Background
            EngineRender();                           ///< Game Engine Render
        EndDrawing();                               ///< || End Drawing, RalyLib Context
    }
    DeInitEngine();                                 ///< De-Init Game Engine
    CloseWindow();                                  ///< Close Window OpenGL Context
    return EXIT_SUCCESS;                            ///< Close main correctly
}
//////////////////////////////////////////////////////////////////



