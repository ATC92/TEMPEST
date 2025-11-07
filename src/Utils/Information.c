#include "Information.h"
//////////////////////////////////////////////////////////////////
void DrawInformationCamera(Camera2D camera, Entity* eplayer)
{
    DrawRectangle(5,5,330,120,Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(5,5,330,120,BLUE);

    DrawText(TextFormat("Camera Target: (%06.2f, %06.2f)",camera.target.x, camera.target.y),15,10,14,YELLOW);
    DrawText(TextFormat("Camera Zoom: %06.2f ", camera.zoom),15,30,14,YELLOW);
    
    DrawText(TextFormat("FPS: [%d FPS]", GetFPS()), 15, 50, 15, MAGENTA);

    DrawText(TextFormat("Mouse Position: [x: %.2f Y: %.2f]",mouse.x,mouse.y), 15, 70,14, YELLOW);

    if(IsGameInit)
    {
        DrawText(TextFormat("Player Position: %2.f %2.f ", eplayer->position.x, eplayer->position.y),15,85,14,WHITE);
    }
}
//////////////////////////////////////////////////////////////////
void DrawLinesMidScreen()
{
    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;
    DrawLine(centerX, 0, centerX, GetScreenHeight() , RED);
    DrawLine(0, centerY, GetScreenWidth(), centerY, RED);
}

