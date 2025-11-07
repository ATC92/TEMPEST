#include "Collision.h"
//////////////////////////////////////////////////////////
bool SystemAABBMid(Entity* Source, Entity* Target, bool r, TypeCollision tc)
{
    Vector2 MidA = {0,0};
    Vector2 MidB = {0,0};
    switch (tc)
    {
    case _COLLISION_BOX:
        MidA = (Vector2){Source->boundingBox.width/2, Source->boundingBox.height/2};
        MidB = (Vector2){Target->boundingBox.width/2, Target->boundingBox.height/2};
        break;
    case _TRIGGER_BOX:
        MidA = (Vector2){Source->triggerBox.width/2, Source->triggerBox.height/2};
        MidB = (Vector2){Target->triggerBox.width/2, Target->triggerBox.height/2};
        break;
    }
    // auto midA = (Vector2){Source->boundingBox.width / 2,Source->boundingBox.height / 2}; 
    auto pA = Source->position;
    auto prevA = Source->prev_position;
    // auto midB = (Vector2){Target->boundingBox.width / 2,Target->boundingBox.height / 2};
    auto pB = Target->position;

    float dx = fabsf(pB.x - pA.x);
    float dy = fabsf(pB.y - pA.y);

    float SumMidX = MidA.x + MidB.x;
    float SumMidY = MidA.y + MidB.y;

    bool v = SumMidX - dx > 0;
    bool h = SumMidY - dy > 0;
    bool Collision = v && h;
    
    if(Collision && r)
        Source->position = prevA;
    return Collision;
}

void SyncCollisionBox(Entity* entiy)
{
    entiy->boundingBox.x = entiy->position.x;
    entiy->boundingBox.y = entiy->position.y;

    entiy->triggerBox.x = entiy->position.x - 2;
    entiy->triggerBox.y = entiy->position.y - 2;
}
//////////////////////////////////////////////////////////