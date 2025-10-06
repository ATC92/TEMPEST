///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "BestiaryScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Public declarations
SpriteAnimation scrollVeyx;
///< Private declarations
static bool scrollAnimation;
///< KeysDraw
static Button* btt_ESC;
static Texture2D k_ESC;
static Vector2 foo;
static Vector2 barESC;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitBestiaryScene(void)
{
    /* !<--- Bestiary LoadingTextures ---> */
    k_ESC = LoadTexture("assets/UI/Keys/White/ESC.png");
    /* !<--- Button Creation ---> */
    barESC = MeasureTextEx(fontType,"Regresar",30,0);
    CustomScale(2.f);
    btt_ESC = CreateButton("assets/UI/Keys/White/ESC.png","assets/UI/Keys/White/ESC.png",(Vector2){
        .x = (float)GetScreenWidth() - (float)k_ESC.width * scale.ScaleUniform - 10 - barESC.x,
        .y = (float)GetScreenHeight() - (float)k_ESC.height * scale.ScaleUniform- 10,});
    CustomScale(1.f);
    foo = (Vector2)
    {
        .x = (btt_ESC->destinationButton.x + btt_ESC->destinationButton.width / 2) + barESC.x/6,
        .y = (btt_ESC->destinationButton.y + btt_ESC->destinationButton.height / 2) - barESC.y / 2
    };
    btt_ESC->boundingBox = (Rectangle)
    {
        .x = btt_ESC->destinationButton.x,
        .y = btt_ESC->destinationButton.y,
        .width = btt_ESC->destinationButton.width + barESC.x,
        .height = btt_ESC->destinationButton.height
    };
    ///!<--- Scroll Bestiary ---->
    scrollVeyx = CreateSpriteAnimation("assets/UI/Scroll/OpenScroll/Scroll_SpriteSheet.png",0,10,0.01f,0.1f,A_ONESHOT);
    /* !<--- Bestiary Menu|GUI ---> */    
    /* !<--- Bestiary Components ---> */    
    scrollAnimation = false;
    UnloadTexture(k_ESC);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateBestiaryScene(void)
{
    ClearBackground(GRAY);
#if DEBUG
    DrawRectangleLinesEx(btt_ESC->boundingBox,2.f,RED);
#endif
    ///< Animation Scroll
    CustomScale(3.1f);
        DrawSpriteAnimationPro(&scrollVeyx,(Vector2){(float)GetScreenWidth() / 2 - (494/2)*3.1f , -45},0,(Vector2){0,0},WHITE,11,494.f,377.f);
    CustomScale(1.f);
    ///< If animation still working
    if(scrollVeyx.cur == scrollVeyx.last)
        scrollAnimation = true;
    if(scrollAnimation)
    {
        DrawButton(btt_ESC,"Regresar",foo,fontType,30, BLACK);
        DrawTextEx(fontType,"Bestiary", (Vector2){800, 90}, 80,0,BLACK);
        scrollAnimation = false;
    }
    /*!<--- CollisionBox Logic */
    if(CheckCollisionPointRec(mouse,btt_ESC->boundingBox))
        AccionButton(btt_ESC,fontType,"Regresar",S_INVERT,foo,sMAINMENU,MS_NONE,MS_NONE,0.1f,30.f,true,WHITE,BLACK);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyBestiaryScene(void)
{
    for(size_t i=0; i<2; i++)
        UnloadTexture(btt_ESC->Texture[i]);
    
    free(btt_ESC->Texture);

    free(btt_ESC);
}
///////////////////////////////////////////////////////////