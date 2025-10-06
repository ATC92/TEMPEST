//////////////////////////////////////////////////////////
#pragma once 
//////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "../Utils/Scale.h"
//////////////////////////////////////////////////////////
///< Public definitions
extern size_t frameSpeed;
extern size_t framecurrent;
extern size_t framesCounter;
//////////////////////////////////////////////////////////
///< Struct for AnimationType
typedef enum _animationType
{
    A_LOOP,
    A_ONESHOT
}AnimationType;
///< Struct for SpriteAnimation
typedef struct _spriteAnimation
{
    Texture2D spriteSheet;

    int first;
    int last;
    int cur;

    float speed;
    float durationLeft;

    AnimationType type;
}SpriteAnimation;
//////////////////////////////////////////////////////////
/**
 * 
 */
SpriteAnimation CreateSpriteAnimation(char* path, int first, int last,float speed, float duration, AnimationType type);
/**
 * 
 */
void DestroySpriteAnimation(SpriteAnimation animation);
/**
 * 
 */
void DrawSpriteAnimationPro(SpriteAnimation* anim, Vector2 position, float rotation, Vector2 origin, Color tint, int numFramesPerRow, float tileWidth, float tileHeight);
/**
 * 
 */
void UpdateAnimation(SpriteAnimation* self, bool isMooving);
/**
 * 
 */
Rectangle AnimationFrame(SpriteAnimation* self, int numFramesPerRow, float tileWidth, float tileHeight);
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/**
 * 
 */
void DrawParallax(Texture2D tex, float* offset, float speed, float scale, float y);
//////////////////////////////////////////////////////////