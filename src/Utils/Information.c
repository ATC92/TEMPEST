#include "Information.h"
//////////////////////////////////////////////////////////////////
void DrawInformationCamera(Camera2D camera)
{
    DrawRectangle(5,5,330,120,Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(5,5,330,120,BLUE);

    DrawText(TextFormat("Camera Target: (%06.2f, %06.2f)",camera.target.x, camera.target.y),15,10,14,YELLOW);
    DrawText(TextFormat("Camera Zoom: %06.2f ", camera.zoom),15,30,14,YELLOW);

    DrawText(TextFormat("FPS: [%d FPS]", GetFPS()), 15, 50, 15, GRAY);
}
//////////////////////////////////////////////////////////////////
void DrawLinesMidScreen()
{
    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;
    DrawLine(centerX, 0, centerX, GetScreenHeight() , RED);
    DrawLine(0, centerY, GetScreenWidth(), centerY, RED);
}

