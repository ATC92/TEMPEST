#include "../Motor/Motor.h"
#include "../Entity/Entity.h"

int main(void)
{
    // Init VAR
    // --------------------------------------------------------------------
    const int screenWidth = 1250;
    const int screenHeight = 950;
    // --------------------------------------------------------------------
    // Window Init
    InitWindow(screenWidth,screenHeight,"Project V-Beta");              // Width, Height, Name.
    SetTargetFPS(60);                                                   // Init Fps in 60.
    // --------------------------------------------------------------------
    // Init the assets and everything por the game.
    InitGame();
    // Main Loop Game
    while (!WindowShouldClose())
    {
        // --------------------------------------------------------------------
        // UPDATE
        // --------------------------------------------------------------------

        // Update Movement of Player
        updateMovement();
        // Create Entity Enemys 

        GameUpdate();
        // --------------------------------------------------------------------
        // Draw
        // --------------------------------------------------------------------

        // Init Drawing part
        BeginDrawing();
            // Clear the Canvas
            ClearBackground(RAYWHITE);
            GameRender();
        // End Drawing part
        EndDrawing();
    }
    // --------------------------------------------------------------------
    // De-Init
    // --------------------------------------------------------------------
    DeInitGame();
    CloseWindow();                                                      // OpenGL Context
    //--------------------------------------------------------------------
    // END Context Game
}