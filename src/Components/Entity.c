#include "Entity.h"
//////////////////////////////////////////////////////////
Entity* GenEntity(TypeEntity _t, char* _n, uint8_t _s)
{
    Entity* _e = (Entity*)calloc(1,sizeof(Entity));                         ///< Generation Entity
    switch (_t)                                                             ///< Selection of the Type to gen.
    {
        case _PLAYER:
            _e->name = strdup(_n);                                          ///< Name of the Entity        
            _e->position = (Vector2){210,160};                              ///< Position of the Entity
            _e->speed = _s;                                              ///< Speed of the Entity
            _e->prev_position = (Vector2){0,0};                             ///< Previous Position of the Entity
            _e->velocity = (Vector2){0,0};                                  ///< Velocity of the Entity
            _e->typeEntity = _PLAYER;                                       ///< Type of Entity             
            _e->sizeRect = (Rectangle){0,0,.width=16,.height=16};           ///< CollisionBox RECT of the Entity
            _e->eLook = DOWN;                                               ///< Where the entity is looking (Default: DOWN)
            break;
        case _ENEMY:
            _e->name = strdup(_n);                                          ///< Name of the Entity
            _e->position = (Vector2){150,150};                              ///< Position of the Entity
            _e->prev_position = (Vector2){0,0};                             ///< Previous Position of the Entity
            _e->typeEntity = _ENEMY;                                        ///< Type of Entity 
            _e->sizeRect = (Rectangle){0,0,.width = 16,.height=16};         ///< CollisionBox RECT of the Entity
            break;
        default:
        break;
    }
    return _e;
}
//////////////////////////////////////////////////////////



