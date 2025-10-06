#include "Collision.h"
//////////////////////////////////////////////////////////
/**
 * @brief
 */
bool SystemAABBMid(Entity* Source, Entity* Target, bool r)
{
    auto midA = (Vector2){Source->sizeRect.height / 2, Source->sizeRect.width / 2}; 
    auto pA = Source->position;
    auto prevA = Source->prev_position;
    auto midB = (Vector2){Target->sizeRect.height / 2, Target->sizeRect.width / 2};
    auto pB = Target->position;

    float dx = fabsf(pB.x - pA.x);
    float dy = fabsf(pB.y - pA.y);

    float SumMidX = midA.x + midB.x;
    float SumMidY = midA.y + midB.y;

    bool v = SumMidX - dx > 0;
    bool h = SumMidY - dy > 0;
    bool Collision = v && h;
    
    if(Collision && r)
        Source->position = prevA;
    return Collision;
}

//////////////////////////////////////////////////////////