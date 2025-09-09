#include "Collision.h"
//////////////////////////////////////////////////////////
/**
 * @brief
 */
bool SystemAABBMid(Entity* Source, Entity* Target, bool r)
{
    auto midA = (Vector2){Source->_rect.height / 2, Source->_rect.width / 2}; 
    auto pA = Source->position;
    auto prevA = Source->prev_position;
    auto midB = (Vector2){Target->_rect.height / 2, Target->_rect.width / 2};
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