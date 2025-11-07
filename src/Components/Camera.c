//////////////////////////////////////////////////////////////////
#include "Camera.h"
//////////////////////////////////////////////////////////////////
Camera2D camera = {0};
//////////////////////////////////////////////////////////////////
Camera2D InitCamera(void)
{
    Camera2D camera;
    // camera.target = (Vector2){ eplayer->boundingBox.x + eplayer->boundingBox.width/2, eplayer->boundingBox.y + eplayer->boundingBox.height/2 };
    camera.zoom = 4.0f;
    camera.rotation = 0.0f;
    camera.offset = (Vector2){ (float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f };
    return camera;
}

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

void LockCameraToZone(Camera2D* cam, Rectangle zone)
{
    float half_w = (float)GetScreenWidth() * 0.5f / cam->zoom;
    float half_h = (float)GetScreenHeight() * 0.5f / cam->zoom;

    float min_x = zone.x + half_w;
    float min_y = zone.y + half_h;
    float max_x = zone.x + zone.width - half_w;
    float max_y = zone.y + zone.height - half_h;

    cam->target.x = Clamp(cam->target.x, min_x, max_x);
    cam->target.y = Clamp(cam->target.y, min_y, max_y);
}

void SmoothCameraMovement(Camera2D* camera, float smoothFactor, Rectangle target)
{
        ///!<--------- Smooth Camera follow
        ///< If you want a more rigid camera, increase the < smoothFactor > value.
        ///< If you want a more fluid camera, decrease the < smoothFactor > value.
        ///< Smooth Camera follow (Default: 0.1f, Options: 0.05f o 0.2f)
        camera->target.x += (target.x + target.width/2 - camera->target.x) * smoothFactor;
        camera->target.y += (target.y + target.height/2 - camera->target.y) * smoothFactor;
}
//////////////////////////////////////////////////////////////////