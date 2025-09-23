///////////////////////////////////////////////////////////
#include "BestiaryScene.h"
///////////////////////////////////////////////////////////
///< Public declarations
///< Private declarations
static Button* btt_Return;
static Vector2 bar, foo;
static Texture2D bg, Enemy;
static Rectangle source, dest;
static Rectangle sourceE, destE;
///////////////////////////////////////////////////////////
void InitBestiaryScene(void)
{
    ///< Background
    char* pathBG = "assets/UI/Pergamino.png";
    char* pathEnemy = "assets/Enemies/Golem.png";
    if(IsPathFile(pathBG) || IsPathFile(pathEnemy))
    {
        bg = LoadTexture(pathBG);
        Enemy = LoadTexture(pathEnemy);
    }
    else 
        perror("ERROR: LoadBackGround Texture");

    source = (Rectangle)
    {
        .x = 0,
        .y = 0,
        .width = (float)bg.width,
        .height = (float)bg.height
    };
    // CustomScale(1f);
    dest = (Rectangle)
    {
        .x = ((float)GetScreenWidth() / 2) - ((float)bg.width / 2),
        .y = 0,
        .width = (float)bg.width * scale.ScaleUniform,
        .height = (float)bg.height * scale.ScaleScreen
    };
    ////< enemies
    sourceE = (Rectangle)
    {
        .x = 0,
        .y = 0,
        .width = (float)Enemy.width,
        .height = (float)Enemy.height
    };
    CustomScale(3.5f);
    // CustomScale(1f);
    destE = (Rectangle)
    {
        .x = 550,
        .y =  200,
        .width = (float)Enemy.width * scale.ScaleUniform,
        .height = (float)Enemy.height * scale.ScaleUniform
    };
    CustomScale(1.f);
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
    foo = (Vector2)
    {
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
    DrawTexturePro(bg,source,dest,(Vector2){0,0},0.f,WHITE);
    DrawTexturePro(Enemy,sourceE,destE,(Vector2){0,0},0.f,WHITE);
    DrawTextEx(*fontType,"Bestiary", (Vector2){800, 90}, 80,0,BLACK);
    btt_Return->state = NORMAL;
    DrawButton(btt_Return,"Regresar",foo,*fontType, BLACK);
    /*!<--- CollisionBox Logic */
    if(CheckCollisionPointRec(mouse,btt_Return->destinationButton))
        AccionButton(btt_Return,*fontType,"Regresar",Invert,foo,MainMenu,0.1f,true,WHITE);
}
void DestroyBestiaryScene(void)
{
    UnloadTexture(btt_Return->Texture[0]);
    UnloadTexture(btt_Return->Texture[1]);

    free(btt_Return);
}
///////////////////////////////////////////////////////////