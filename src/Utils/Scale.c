////////////////////////////////////////////////////////////////////////////////////////////
#include "Scale.h"
////////////////////////////////////////////////////////////////////////////////////////////
Scale scale;
////////////////////////////////////////////////////////////////////////////////////////////
void InitScale()
{
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();
    scale.ScaleX = (float)screenWidth  / 1920.0f;
    scale.ScaleY = (float)screenHeight / 1080.0f;    
    scale.ScaleScreen = (scale.ScaleX < scale.ScaleY) ? scale.ScaleX : scale.ScaleY;
    scale.ScaleUniform = 1.f;
}
void CustomScale(float custom)
{
    scale.ScaleUniform = custom;
}