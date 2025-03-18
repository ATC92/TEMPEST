#include "EngineUpdates.h"
/**
 * @brief Mouse Wheel Update
 * 
 * @param Camera2D*           ///< Camera 2D reference
 * 
 * @return @n `Void`  
 */
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
/**
 * @brief Movement update and Looking of the player
 * 
 * @param Entity*           ///< Player Entity reference
 * 
 * @return @n `Void`
 */
void updateMovement(Entity* eplayer)
{
    if(IsKeyDown(KEY_A))
    {
        eplayer->_player.position.x -= eplayer->_player.speed;
        if(eplayer->_eLook != LEFT)
            eplayer->_eLook = LEFT;
    }
    else if (IsKeyDown(KEY_D))
    {
        eplayer->_player.position.x += eplayer->_player.speed;
        if(eplayer->_eLook != RIGHT)
            eplayer->_eLook = RIGHT;    
    }
    else if(IsKeyDown(KEY_W))
    {
        eplayer->_player.position.y -= eplayer->_player.speed;
        if(eplayer->_eLook != UP)
            eplayer->_eLook = UP;
    }
    else if(IsKeyDown(KEY_S))
    {
        eplayer->_player.position.y += eplayer->_player.speed;
        if(eplayer->_eLook != DOWN)
            eplayer->_eLook = DOWN;
    }

    if(IsKeyDown(KEY_LEFT_SHIFT))
        eplayer->_player.speed = 2.f;
    else if(IsKeyReleased(KEY_LEFT_SHIFT))
        eplayer->_player.speed = 1.5f;

}


