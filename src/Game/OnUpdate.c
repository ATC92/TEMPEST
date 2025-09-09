#include "OnUpdate.h"
//////////////////////////////////////////////////////////
void UpdateCameraWheel(Camera2D* camera)
{
    float wheel = GetMouseWheelMove();
    if(wheel != 0)
    {
        const float zoomIncrement = 0.125f;
        (*camera).zoom += (wheel + zoomIncrement);
<<<<<<< HEAD
        if((*camera).zoom < 4.0f) (*camera).zoom = 4.0f;
=======
        if((*camera).zoom < 3.0f) (*camera).zoom = 3.0f;
>>>>>>> origin/main
        if((*camera).zoom > 8.0f) (*camera).zoom = 8.0f;
    }
}
//////////////////////////////////////////////////////////
<<<<<<< HEAD
void UpdateMovement(Entity* eplayer, float dt)
{
    if(IsKeyDown(KEY_A))
    {
        eplayer->position.x -= eplayer->speed * dt;
        // eplayer->velocity.x = -eplayer->speed;
=======
void updateMovement(Entity* eplayer)
{
    if(IsKeyDown(KEY_A))
    {
        eplayer->position.x -= eplayer->velocity.x;
>>>>>>> origin/main
        if(eplayer->_eLook != LEFT)
            eplayer->_eLook = LEFT;
    }
    else if (IsKeyDown(KEY_D))
    {
<<<<<<< HEAD
        eplayer->position.x += eplayer->speed * dt;
        // eplayer->velocity.x = eplayer->speed;
        if(eplayer->_eLook != RIGHT)
            eplayer->_eLook = RIGHT;
    }
    else if(IsKeyDown(KEY_W))
    {
        eplayer->position.y -= eplayer->speed * dt;
        // eplayer->velocity.y = -eplayer->speed;
=======
        eplayer->position.x += eplayer->velocity.x;
        if(eplayer->_eLook != RIGHT)
            eplayer->_eLook = RIGHT;    
    }
    else if(IsKeyDown(KEY_W))
    {
        eplayer->position.y -= eplayer->velocity.y;
>>>>>>> origin/main
        if(eplayer->_eLook != UP)
            eplayer->_eLook = UP;
    }
    else if(IsKeyDown(KEY_S))
<<<<<<< HEAD
    {   
        eplayer->position.y += eplayer->speed * dt;
        // eplayer->velocity.y = eplayer->speed;
=======
    {
        eplayer->position.y += eplayer->velocity.y;
>>>>>>> origin/main
        if(eplayer->_eLook != DOWN)
            eplayer->_eLook = DOWN;
    }

    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
<<<<<<< HEAD
        eplayer->speed = 130.f; // Increase speed when shift is held
    }
    else if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        eplayer->speed = 120.f; // Reset speed when shift is released
    }
}
//////////////////////////////////////////////////////////
void SyncCollisionBox(Entity* entiy)
=======
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
>>>>>>> origin/main
{
    entiy->_rect.x = entiy->position.x;
    entiy->_rect.y = entiy->position.y;
    entiy->_rect.width = 16;
    entiy->_rect.height = 16;
}
//////////////////////////////////////////////////////////
<<<<<<< HEAD
void ClampPlayerToMap(Entity* eplayer, Rectangle size)
{
    if(eplayer->position.x < size.x) eplayer->position.x = size.x;
    if(eplayer->position.y < size.y) eplayer->position.y = size.y;
    if(eplayer->position.x + eplayer->_rect.width > size.x + size.width)
        eplayer->position.x = size.x + size.width - eplayer->_rect.width;
    if(eplayer->position.y + eplayer->_rect.height > size.y + size.height)
        eplayer->position.y = size.y + size.height - eplayer->_rect.height;
}
//////////////////////////////////////////////////////////
void LockCameraToZone(Camera2D* cam, Rectangle zone)
{
    float half_w = GetScreenWidth() * 0.5f / cam->zoom;
    float half_h = GetScreenHeight() * 0.5f / cam->zoom;

    float min_x = zone.x + half_w;
    float min_y = zone.y + half_h;
    float max_x = zone.x + zone.width - half_w;
    float max_y = zone.y + zone.height - half_h;

    cam->target.x = Clamp(cam->target.x, min_x, max_x);
    cam->target.y = Clamp(cam->target.y, min_y, max_y);
}
//////////////////////////////////////////////////////////

=======
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





>>>>>>> origin/main
