#include "animation.h"
#include <stdio.h>
//////////////////////////////////////////////////////////
SpriteAnimation CreateSpriteAnimation(char* path, int first, int last,float speed, float duration)
{
    Texture2D atlas = LoadTexture(path);
    if(!IsTextureValid(atlas))
        TraceLog(LOG_FATAL,"Error with the Texture2D loaded in CreateSpriteAnimation");
    SpriteAnimation spriteAnimation = 
    {
        .spriteSheet = atlas,
        .first = first,
        .last = last,
        .cur = 0,
        .speed = speed,
        .durationLeft = duration,
        .type = LOOP
    };
    return spriteAnimation;
}
void DestroySpriteAnimation(SpriteAnimation animation)
{
    UnloadTexture(animation.spriteSheet);
}
void DrawSpriteAnimationPro(SpriteAnimation* anim, Vector2 position, float rotation, Vector2 origin, Color tint, int numFramesPerRow)
{
    ///< Rectangle for the destination (where to draw the texture)
    Rectangle destRec = {
        position.x,
        position.y,
        (float)32 * scale.ScaleUniform,
        (float)32 * scale.ScaleUniform
    };
    ///< Rectangle for the source (part of the texture to draw)
    DrawTexturePro(anim->spriteSheet, AnimationFrame(anim,numFramesPerRow), destRec, origin, rotation, tint);
}
//////////////////////////////////////////////////////////
void UpdateAnimation(SpriteAnimation* self, bool isMooving)
{
    float dt = GetFrameTime();

    self->durationLeft -= dt;

    if(self->durationLeft <= 0)
    {
        self->durationLeft = self->speed;
        self->cur ++;
        if(self->cur > self->last)
            switch (self->type)
            {
            case LOOP:
                if(!isMooving)
                    self->cur = self->last;                    
                else
                    self->cur = self->first;
                break;
            case ONESHOT:
                self->cur = self->last;
                break;
            default:
                break;
            }
    }
}

Rectangle AnimationFrame(SpriteAnimation* self, int numFramesPerRow)
{
    float x = (float)(self->cur % numFramesPerRow) * 32;
    float y = (float)(self->cur / numFramesPerRow) * 32;

    return (Rectangle){ .x= (float)x, .y = (float)y, 32, 32 };
}
//////////////////////////////////////////////////////////