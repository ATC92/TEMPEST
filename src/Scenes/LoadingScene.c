#include "LoadingScene.h"
//////////////////////////////////////////////////////////
void SimulateLoading(float seconds)
{
    double startTime = GetTime();
    float midX = GetScreenWidth() / 2;
    float midY = GetScreenHeight() / 2;

    /// Mid oh Text
    Vector2 bar = MeasureTextEx(*fontType,"Cargando....",20,0);
    Vector2 posText = 
    {
        .x = midX - bar.x / 2,
        .y = midY - bar.y - 5
    };
    while ((GetTime() - startTime) < seconds)
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(*fontType,"Cargando....", posText, 20,0, WHITE);
            #if DEBUG
            DrawLinesMidScreen();
            #endif
            DrawRectangleLines(midX - 100,midY,200,20,WHITE);
            DrawRectangle(midX - 100, midY, (int)(((GetTime() - startTime) / seconds) * 200), 20, GREEN);
        EndDrawing();
    }
}
//////////////////////////////////////////////////////////
