///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "OnUpdate.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClampPlayerToMap(Entity* eplayer, Rectangle size)
{
    if(eplayer->position.x < size.x) eplayer->position.x = size.x;
    if(eplayer->position.y < size.y) eplayer->position.y = size.y;
    if(eplayer->position.x + eplayer->boundingBox.width > size.x + size.width)
        eplayer->position.x = size.x + size.width - eplayer->boundingBox.width;
    if(eplayer->position.y + eplayer->boundingBox.height > size.y + size.height)
        eplayer->position.y = size.y + size.height - eplayer->boundingBox.height;
}
void UpdatePrevPosition(Entity* player, Entity** pool, size_t sizePool)
{
    player->prev_position = player->position;  
    for (size_t i = 0; i < sizePool; i++)
        pool[i]->prev_position = pool[i]->position;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

