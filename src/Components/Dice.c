///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Dice.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SpriteAnimation* diceAnimations;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitSpriteAnimationDice()
{
    diceAnimations = (SpriteAnimation*)calloc(6,sizeof(SpriteAnimation));
    diceAnimations[0] = LoadAnimationDice("D4");
    diceAnimations[1] = LoadAnimationDice("D6");
    diceAnimations[2] = LoadAnimationDice("D8");
    diceAnimations[3] = LoadAnimationDice("D10");
    diceAnimations[4] = LoadAnimationDice("D12");
    diceAnimations[5] = LoadAnimationDice("D20");
}

void DestroySpriteAnimationDice()
{
    DestroyAnimation(&diceAnimations[0],_OBJECT_DICE);
    DestroyAnimation(&diceAnimations[1],_OBJECT_DICE);
    DestroyAnimation(&diceAnimations[2],_OBJECT_DICE);
    DestroyAnimation(&diceAnimations[3],_OBJECT_DICE);
    DestroyAnimation(&diceAnimations[4],_OBJECT_DICE);
    DestroyAnimation(&diceAnimations[5],_OBJECT_DICE);
    // free(diceAnimations);
}
SpriteAnimation LoadAnimationDice(const char* name)
{
    SpriteAnimation anim = {0};

    anim.spriteSheet = LoadTexture(TextFormat(ASSETS"/Dice/%s-Roll.png",name));
    if(!IsTextureValid(anim.spriteSheet))
        AssertNotNull(&anim.spriteSheet,TextFormat("Erro in load Dice %s",name),"anim.spriteSheet");
    anim.cur = 0;
    anim.first = 0;
    anim.last = 18;
    anim.speed = 0.08f;
    anim.step = 1;
    anim.type = A_ONESHOT;
    anim.durationLeft = .5f;

    return anim;
}
Texture2D LoadIconDice(const char* name)
{
    Texture2D tex;
    tex = LoadTexture(TextFormat(ASSETS"/Dice/%s-Icon.png",name));
    if(!IsTextureValid(tex))
        AssertNotNull(&tex,TextFormat("Erro in load Dice icon %s",name),"tex");
    return tex;
}

void DrawDiceIcons(Dice* self, Vector2* pos)
{
    Rectangle origin = (Rectangle){.x=0,.y=0,.width=self->icon.width,.height=self->icon.height};  
    Rectangle dest = (Rectangle){.x = pos->x,.y=pos->y,.width = origin.width, .height = origin.height};
    DrawTexturePro(self->icon,origin,dest,(Vector2){0,0},0.f,WHITE);
    self->boundingBox = dest;
#if DEBUG
    DrawRectangleLinesEx(dest,1.f,RED);
#endif  
}

size_t RollDice(DiceType type)
{
    int roll = (rand() % type);
    TraceLog(LOG_INFO,"Roll result :%d",roll);
    if(roll <= 0 )
        roll++;
    return (size_t)roll;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
