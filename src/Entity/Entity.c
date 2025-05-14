#include "Entity.h"
Entity* GenEntity(int _t, char* _n, float _h, float _ar, float _sp, float _crt)
{
    Entity* _e = (Entity*)calloc(1,sizeof(Entity));             ///< Generation Entity
    switch (_t)                                                 ///< Selection of the Type to gen.
    {
        case _PLAYER:
            _e->name = strdup(_n);
            _e->health = _h;
            _e->armor = _ar;
            _e->speed = _sp;
            _e->position = (Vector2){85,120};
            _e->_typeEntity = _PLAYER;
            _e->_eLook = 2;
            _e->_textureArray = (Texture2D*)calloc(5,sizeof(Texture2D));
            break;
        case _NPC:
            _e->name = strdup(_n);
            _e->health = _h;
            _e->armor = _ar;
            _e->crit = _crt;
            _e->speed = _sp;
            _e->position = (Vector2){0,0};
            _e->_typeEntity = _NPC;
            _e->_textureArray = (Texture2D*)calloc(5,sizeof(Texture2D));
        break;
        default:
        break;
    }
    return _e;              ///< Return entity
}

