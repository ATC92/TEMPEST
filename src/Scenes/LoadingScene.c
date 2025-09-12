#include "LoadingScene.h"
//////////////////////////////////////////////////////////
///< Private declaratios
static double startTime;
static float midX, midY, seconds;
static Vector2 bar, posText;
//////////////////////////////////////////////////////////
void InitLoadingScene(float sec)
{
    startTime = GetTime();
    midX = (float)GetScreenWidth() / 2;
    midY = (float)GetScreenHeight() / 2;
    bar = MeasureTextEx(*fontType,"Cargando....",20,0);
    posText = (Vector2)
    {
        .x = midX - bar.x / 2,
        .y = midY - bar.y - 5
    };
    seconds = sec;
}

void UpdateLoadingScene(void)
{
    while ((GetTime() - startTime) < seconds)
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(*fontType,"Cargando....", posText, 20,0, WHITE);
            #if DEBUG
            DrawLinesMidScreen();
            #endif
            DrawRectangleLines((int)midX - 100,(int)midY,200,20,WHITE);
            DrawRectangle((int)midX - 100, (int)midY, (int)(((GetTime() - startTime) / seconds) * 200), 20, GREEN);
        EndDrawing();
    }
}

void DestroyLoadingScene(void)
{
    startTime = 0;
    midX = 0;
    midY = 0;
    bar = (Vector2){0};
    posText = (Vector2){0};
}
//////////////////////////////////////////////////////////
