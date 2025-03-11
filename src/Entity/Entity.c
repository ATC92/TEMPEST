#include "Entity.h"

Entity GenEntity(int _t, char* _n, float _h, float _ar, float _sp, float _crt)
{
    // Generation Entity Player
    Entity _e;
    _e.EntityType = _t;

    switch (_t)
    {
        case PLAYER:
            _e.EntityData.Player.name = _n;
            _e.EntityData.Player.health = _h;
            _e.EntityData.Player.armor = _ar;
            _e.EntityData.Player.armor = _ar;
            _e.EntityData.Player.speed = _sp;
            _e.EntityData.Player.position = (Vector2){0,0};
            break;
        case ENEMY:
            _e.EntityData.Enemy.name = _n;
            _e.EntityData.Enemy.health = _h;
            _e.EntityData.Enemy.armor = _ar;
            _e.EntityData.Enemy.armor = _ar;
            _e.EntityData.Enemy.crit = _crt;
            _e.EntityData.Enemy.speed = _sp;
            _e.EntityData.Enemy.position = (Vector2){20.f,20.f};
            break;
        default:
            break;
    }
    
    return _e;
}

// Enf Entity.c
