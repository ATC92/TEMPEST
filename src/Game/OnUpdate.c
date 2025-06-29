#include "OnUpdate.h"
//////////////////////////////////////////////////////////
void UpdateCameraWheel(Camera2D* camera)
{
    float wheel = GetMouseWheelMove();
    if(wheel != 0)
    {
        const float zoomIncrement = 0.125f;
        (*camera).zoom += (wheel + zoomIncrement);
        if((*camera).zoom < 3.0f) (*camera).zoom = 3.0f;
        if((*camera).zoom > 8.0f) (*camera).zoom = 8.0f;
    }
}
//////////////////////////////////////////////////////////
void updateMovement(Entity* eplayer)
{
    if(IsKeyDown(KEY_A))
    {
        eplayer->position.x -= eplayer->velocity.x;
        if(eplayer->_eLook != LEFT)
            eplayer->_eLook = LEFT;
    }
    else if (IsKeyDown(KEY_D))
    {
        eplayer->position.x += eplayer->velocity.x;
        if(eplayer->_eLook != RIGHT)
            eplayer->_eLook = RIGHT;    
    }
    else if(IsKeyDown(KEY_W))
    {
        eplayer->position.y -= eplayer->velocity.y;
        if(eplayer->_eLook != UP)
            eplayer->_eLook = UP;
    }
    else if(IsKeyDown(KEY_S))
    {
        eplayer->position.y += eplayer->velocity.y;
        if(eplayer->_eLook != DOWN)
            eplayer->_eLook = DOWN;
    }

    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        eplayer->velocity.x = 2.f;
        eplayer->velocity.y = 2.f;
    }
    else if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        eplayer->velocity.x = eplayer->speed;
        eplayer->velocity.y = eplayer->speed;
    }
}
//////////////////////////////////////////////////////////
void UpdateCollision(Entity* eplayer, Entity* eEnemy)
{
    if(CheckCollisionRecs(eplayer->_rect, eEnemy->_rect))
    {
        ResolveCollision(eplayer,eEnemy);
    }
    
}
//////////////////////////////////////////////////////////
void UpdateCollisionMovement(Entity* entiy)
{
    entiy->_rect.x = entiy->position.x;
    entiy->_rect.y = entiy->position.y;
    entiy->_rect.width = 16;
    entiy->_rect.height = 16;
}
//////////////////////////////////////////////////////////
void ResolveCollision(Entity* eplayer, Entity* eEnemy)
{    
    Rectangle a = eplayer->_rect;
    Rectangle b = eEnemy->_rect;

    float dx = (a.x + a.width / 2.0f) - (b.x + b.width / 2.0f);
    float dy = (a.y + a.height / 2.0f) - (b.y + b.height / 2.0f);

    float overlapX = (a.width + b.width) / 2.0f - fabsf(dx);
    float overlapY = (a.height + b.height) / 2.0f - fabsf(dy);

    if (overlapX > 0 && overlapY > 0)
    {
        if (overlapX < overlapY)
        {
            if (dx > 0)
                eplayer->position.x += overlapX;
            else
                eplayer->position.x -= overlapX;
        }
        else
        {
            if (dy > 0)
                eplayer->position.y += overlapY;
            else
                eplayer->position.y -= overlapY;
        }

        eplayer->_rect.x = eplayer->position.x;
        eplayer->_rect.y = eplayer->position.y;
    }
}
//////////////////////////////////////////////////////////





