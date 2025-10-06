///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AuxScenes.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float minX;
float maxX;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundBarFollowPoint(Button* vN,Rectangle* dot)
{
    // Posición inicial del dot (mitad de la barra)
    // float dotX = bar.x + bar.width/2.0f - dot->width/2.0f;
    // float dotY = bar.y + (bar.height/2.0f - dot->height/2.0f);

    if(CheckCollisionPointRec(mouse,*dot))
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DotPressed = true;
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        DotPressed = false;
    if(DotPressed)
    {
        if((masterVolume)*100 > 9)
            DrawButton(vN,TO_STRING(masterVolume),(Vector2){vN->destinationButton.x + vN->destinationButton.width / 4 - 1,vN->destinationButton.y + vN->destinationButton.height / 4 - 2},fontType,20,BLACK);
        else
            DrawButton(vN,TO_STRING(masterVolume),(Vector2){vN->destinationButton.x + vN->destinationButton.width / 3 + 1,vN->destinationButton.y + vN->destinationButton.height / 4},fontType,20,BLACK);

        float newX = mouse.x - dot->width/2.0f;
        if (newX < minX) newX = minX;
        if (newX > maxX - dot->width) newX = maxX - dot->width;

        masterVolume = (newX - minX) / (maxX - minX);

        // if (masterVolume < 0.0f) masterVolume = 0.0f;
        // if (masterVolume > 1.0f) masterVolume = 1.0f;
        if (currentMusic != -1)
            SetMusicVolume(music[currentMusic], masterVolume);

    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////