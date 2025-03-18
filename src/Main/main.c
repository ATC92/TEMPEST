#include "../Engine/Engine.h"
int main(void)
{
    InitWindow(1250, 950, "Project V-Beta");        ///< Set Name of the window
    SetTargetFPS(75);                               ///< Set FPS
    InitGame();                                     ///< Init Game Engine
    while (!WindowShouldClose())                    ///< Main loop for the game
    {
        GameUpdate();                               ///< Game Engine Update
        BeginDrawing();                             ///< || Start Drawing, RayLib Context
            ClearBackground(RAYWHITE);              ///< Give a color to the Background
            GameRender();                           ///< Game Engine Render
        EndDrawing();                               ///< || End Drawing, RalyLib Context
    }
    DeInitGame();                                   ///< De-Init Game Engine
    CloseWindow();                                  ///< Close Window OpenGL Context
    return EXIT_SUCCESS;                            ///< Close main correctly
}
