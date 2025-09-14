///////////////////////////////////////////////////////////
#include "BestiaryScene.h"
///////////////////////////////////////////////////////////
///< Public declarations
///< Private declarations
static Button* btt_Return;
static Vector2 bar, foo;
///////////////////////////////////////////////////////////
void InitBestiaryScene(void)
{
    ///< Background
    // char* pathBG = "";
    // if(IsPathFile(pathBG))
    //     bg = LoadTexture();
    // else 
    //     perror("ERROR: LoadBackGround Texture";)

    /* !<--- Bestiary Menu|GUI ---> */
    ///< Textures path for the Buttons (Path)
    char* pathT1 = "assets/UI/button_rectangle_depth_line.png";
    char* pathT2 = "assets/UI/button_rectangle_line.png";
    ///< Texture temp for bttreturn;
    Texture2D temp = LoadTexture(pathT1);
    ///< Position btt_Return
    float midScrenTexture = {(float)GetScreenWidth() / 2 - (float)temp.width / 2.0f};
    ///< Button Return
    btt_Return = CreateButton(pathT1,pathT2,(Vector2){midScrenTexture,850.f});
    bar = MeasureTextEx(*fontType,"Regresar",40,0);
    foo = (Vector2){
        .x = (btt_Return->destinationButton.x + btt_Return->destinationButton.width / 2) - bar.x / 2,
        .y = (btt_Return->destinationButton.y + btt_Return->destinationButton.height / 2) - bar.y / 2
    };


    ///< Enemies to Load (IMG DEMO)
    ///< Positions
    ///< Text's
    ///< Scale (Posibility)
}
void UpdateBestiaryScene(void)
{
    ClearBackground(GRAY);
    btt_Return->state = NORMAL;
    DrawButton(btt_Return,"Regresar",foo,*fontType);
    /*!<--- CollisionBox Logic */
    if(CheckCollisionPointRec(mouse,btt_Return->destinationButton))
        AccionButton(btt_Return,*fontType,"Regresar",Invert,foo,MainMenu,0.1f,true);
}
void DestroyBestiaryScene(void)
{

}
///////////////////////////////////////////////////////////