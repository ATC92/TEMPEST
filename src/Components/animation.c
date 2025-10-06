#include "animation.h"
#include <stdio.h>
//////////////////////////////////////////////////////////
SpriteAnimation CreateSpriteAnimation(char* path, int first, int last,float speed, float duration, AnimationType type)
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
        self->cur ++;
        if(self->cur > self->last)
            switch (self->type)
            {
            case A_LOOP:
                if(!isMooving)
                    self->cur = self->last;                    
                else
                    self->cur = self->first;
                break;
            case A_ONESHOT:
                self->cur = self->last;
                break;
            default:
                break;
            }
    }
}

Rectangle AnimationFrame(SpriteAnimation* self, int numFramesPerRow,float tileWidth, float tileHeight)
{
    int x = (self->cur % numFramesPerRow) * tileWidth;
    int y = (self->cur / numFramesPerRow) * tileHeight;

    return (Rectangle){ .x= (float)x, .y = (float)y, .height = tileHeight, .width = tileWidth };
}
//////////////////////////////////////////////////////////
///< Parallax Effect
void DrawParallax(Texture2D tex, float* offset, float speed, float scale, float y)
{
    *offset -= speed;
    float w = tex.width * scale;

    if(*offset <= -w) 
        *offset = 0;
        
    DrawTextureEx(tex, (Vector2){*offset, y}, 0.f, scale, WHITE);
    DrawTextureEx(tex, (Vector2){*offset + w, y}, 0.f, scale, WHITE);
}


//////////////////////////////////////////////////////////