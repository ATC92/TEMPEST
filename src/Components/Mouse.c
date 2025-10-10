///////////////////////////////////////////////////////////////
#include "Mouse.h"
///////////////////////////////////////////////////////////////
///< Public Declarations
Vector2 mouse;
Texture2D cursor;
///////////////////////////////////////////////////////////////
void InitMouse(void)
{
    mouse = (Vector2){0.f,0.f};
    HideCursor();
    cursor = LoadTexture("assets/UI/Cursor/Pointer_2.png");
}
void UpdateMousePosition(void)
{
    switch (scenes->typeScene)
    {
    case sGAMESTATE:
        mouse = (Vector2){-cursor.width * 2,-cursor.height * 2};
        break;
    default:
        mouse = GetMousePosition();
        DrawTextureEx(cursor,mouse,0.f,3.f,WHITE);
        break;
    }
}
void DestroyMouse(void)
{
    UnloadTexture(cursor);
}

///////////////////////////////////////////////////////////////