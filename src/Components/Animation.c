#include "Animation.h"
#include <stdio.h>
//////////////////////////////////////////////////////////
SpriteAnimation CreateSpriteAnimation(char* path, int first, int last,int step, float speed, float duration, AnimationType type)
{
    Texture2D atlas = LoadTexture(path);
    SpriteAnimation spriteAnimation = {0};
    if(!IsTextureValid(atlas))
        TraceLog(LOG_FATAL,"Error with the Texture2D loaded in CreateSpriteAnimation");
    else 
        spriteAnimation = (SpriteAnimation)
        {
            .spriteSheet = atlas,
            .first = first,
            .last = last,
            .cur = 0,
            .step = step,
            .speed = speed,
            .durationLeft = duration,
            .type = type
        };
    return spriteAnimation;
}

void DestroySpriteAnimation(SpriteAnimation animation)
{
    UnloadTexture(animation.spriteSheet);
}
void DrawSpriteAnimationPro(SpriteAnimation* anim,Vector2 position, float rotation, Vector2 origin, Color tint, int numFramesPerRow,float tileWidth, float tileHeight)
{
    ///< Rectangle for the destination (where to draw the texture)
    Rectangle destRec = {
        position.x,
        position.y,
        (float)tileWidth * scale.ScaleUniform,
        (float)tileHeight * scale.ScaleUniform
    };
    ///< Rectangle for the source (part of the texture to draw)
    DrawTexturePro(anim->spriteSheet,AnimationFrame(anim,numFramesPerRow,tileWidth,tileHeight), destRec, origin, rotation, tint);
}
//////////////////////////////////////////////////////////
void UpdateAnimation(SpriteAnimation* self, bool isMooving)
{
    float dt = GetFrameTime();

    self->durationLeft -= dt;

    if(self->durationLeft <= 0)
    {
        self->durationLeft = self->speed;
        self->cur += self->step;
        if(!isMooving)
            self->cur = self->last;  
        if(self->cur > self->last)
        {
            switch (self->type)
            {
            case A_LOOP:
                self->cur = self->first;
                break;
            case A_ONESHOT:
                self->cur = self->last;
                break;
            }
        }
        else if (self->cur < self->first) 
        {
        // handle reaching the end (which is the beginning) of an animation going backwards
        switch (self->type)
        {
            case A_LOOP:
                self->cur = self->last;
                break;
            case A_ONESHOT:
                self->cur = self->first;
                break;
        }
        }
    }
}

Rectangle AnimationFrame(SpriteAnimation* self, int numFramesPerRow,float tileWidth, float tileHeight)
{
    int x = (self->cur % numFramesPerRow) * (int)tileWidth;
    int y = (self->cur / numFramesPerRow) * (int)tileHeight;

    return (Rectangle){ .x= (float)x, .y = (float)y, .height = tileHeight, .width = tileWidth };
}

void DestroyAnimation(SpriteAnimation* self, TypeEntity type)
{
    size_t count = 0;
    switch (type)
    {
        case _PLAYER:
            count = 4;  /// Player
            break;
        case _NPC:
            count = 2;  /// NPC
            break;
        case _OBJECT_DICE:
            count = 6;
        default:
            break;
    }

    for (size_t i = 0; i < count; i++)
    {
        UnloadTexture(self[i].spriteSheet);
    }
    free(self);
}
//////////////////////////////////////////////////////////
///< Parallax Effect
void DrawParallax(Texture2D tex, float* offset, float speed, float scale, float y)
{
    *offset -= speed;
    float w = (float)tex.width * scale;

    if(*offset <= -w) 
        *offset = 0;
        
    DrawTextureEx(tex, (Vector2){*offset, y}, 0.f, scale, WHITE);
    DrawTextureEx(tex, (Vector2){*offset + w, y}, 0.f, scale, WHITE);
}
//////////////////////////////////////////////////////////