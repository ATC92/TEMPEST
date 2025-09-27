//////////////////////////////////////////////////////////
#pragma once 
//////////////////////////////////////////////////////////
///< C/C++ Lib
#include <stdlib.h>
///< TEMPEST Lib
#include "../Utils/Scale.h"
///< RayLib
#include "raylib.h"
//////////////////////////////////////////////////////////
///< FRAME SPEED
#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
///< Public definitions
extern size_t frameSpeed;
extern size_t framecurrent;
extern size_t framesCounter;
//////////////////////////////////////////////////////////
///< Struct for AnimationType
typedef enum _animationType
{
    LOOP,
    ONESHOT
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
SpriteAnimation CreateSpriteAnimation(char* path, int first, int last,float speed, float duration);
/**
 * 
 */
void DestroySpriteAnimation(SpriteAnimation animation);
/**
 * 
 */
void DrawSpriteAnimationPro(SpriteAnimation* anim, Vector2 position, float rotation, Vector2 origin, Color tint, int numFramesPerRow);
/**
 * 
 */
void UpdateAnimation(SpriteAnimation* self, bool isMooving);
/**
 * 
 */
Rectangle AnimationFrame(SpriteAnimation* self, int numFramesPerRow);
//////////////////////////////////////////////////////////