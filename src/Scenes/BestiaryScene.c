///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "BestiaryScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Public declarations
SpriteAnimation scrollVeyx;
///< Private declarations
static bool scrollAnimationDone;
static bool scrollAnimationOut;
///< KeysDraw
static Button* btt_ESC;
static Vector2 foo;
static Vector2 barESC;

static Texture2D* buttonTexture;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitBestiaryScene(void)
{
    buttonTexture = (Texture2D*)calloc(3,sizeof(Texture2D));
    buttonTexture[0] = LoadTexture(ASSETS "/UI/Buttons/button_rectangle_depth_line.png");
    buttonTexture[1] = LoadTexture(ASSETS "/UI/Buttons/button_rectangle_line.png");
    buttonTexture[2] = LoadTexture(ASSETS "/UI/Buttons/button_square_line.png");
    /* !<--- Bestiary LoadingTextures ---> */
    Texture2D k_ESC = LoadTexture(ASSETS "/UI/Keys/White/ESC.png");
    /* !<--- Button Creation ---> */
    barESC = MeasureTextEx(fontType,"Regresar",30,0);
    CustomScale(2.f);
    btt_ESC = CreateButton(ASSETS "/UI/Keys/White/ESC.png",ASSETS "/UI/Keys/White/ESC.png",(Vector2){
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
    scrollVeyx = CreateSpriteAnimation(ASSETS "/UI/Scroll/OpenScroll/Scroll_SpriteSheet.png",0,10,1,0.01f,0.1f,A_ONESHOT);
    /* !<--- Bestiary Menu|GUI ---> */    
    /* !<--- Bestiary Components ---> */    
    scrollAnimationDone = false;
    scrollAnimationOut = false;
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
    /*<----------- Animation Section ----------->*/
    {
        ///< Update change scene, do animation backwards
        if(IsKeyPressed(KEY_ESCAPE) && !scrollAnimationDone)
        {
            PlaySound(sounds[0]);
            scrollVeyx.cur = scrollVeyx.last;
            scrollVeyx.step = -1;
            scrollAnimationOut = true;
        }
        ///< If animation done
        if(scrollVeyx.cur == scrollVeyx.last)
        {
            scrollAnimationDone = true;
        }
        if(scrollAnimationOut == false && scrollAnimationDone == true)
        {
            DrawScroll(buttonTexture);
        }
        if(scrollAnimationDone)
        {
            DrawButton(btt_ESC,"Regresar",foo,fontType,30, BLACK);
            DrawTextEx(fontType,"Bestiary", (Vector2){800, 90}, 80,0,BLACK);
            scrollAnimationDone = false;
        }
        ///< CollisionBox Logic
        if(CheckCollisionPointRec(mouse,btt_ESC->boundingBox))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !scrollAnimationDone)
            {
                scrollVeyx.cur = scrollVeyx.last;
                scrollVeyx.step = -1;
                scrollAnimationOut = true;
            }
            AccionButton(btt_ESC,fontType,"Regresar",S_INVERT,foo,sBESTIARY,MS_NONE,MS_NONE,0.1f,30.f,true,WHITE,BLACK);
        }
        ///< If animation done (Reverse version) 
        if(scrollAnimationOut && scrollVeyx.cur == scrollVeyx.first)
        {
            
            scenes->typeScene = sMAINMENU;
            scenes->previousScene = sBESTIARY;

            scrollAnimationOut = false;
            scrollVeyx.step = 1;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyBestiaryScene(void)
{
    for(size_t i=0; i<2; i++)
        UnloadTexture(btt_ESC->Texture[i]);
    
    free(btt_ESC->Texture);

    for (size_t i = 0; i < 3; i++)
        UnloadTexture(buttonTexture[i]);
    free(buttonTexture);
    
    free(btt_ESC);
}
///////////////////////////////////////////////////////////