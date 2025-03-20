#include "Entity.h"
Entity GenEntity(int _t, char* _n, float _h, float _ar, float _sp, float _crt)
{
    Entity _e = {0};            ///< Generation Entity
    switch (_t)                 ///< Selection of the Type to gen.
    {
        case _PLAYER:
            _e._player.name = strdup(_n);
            _e._player.health = _h;
            _e._player.armor = _ar;
            _e._player.speed = _sp;
            _e._player.position = (Vector2){0,0};
            _e._typeEntity = _PLAYER;
            _e._lSize = (ListTileSize*)calloc(1,sizeof(ListTileSize));
            break;
        case _NPC:
            _e._npc.name = strdup(_n);;
            _e._npc.health = _h;
            _e._npc.armor = _ar;
            _e._npc.crit = _crt;
            _e._npc.speed = _sp;
            _e._npc.position = (Vector2){0,0};
            _e._typeEntity = _NPC;
            _e._lSize = (ListTileSize*)calloc(1,sizeof(ListTileSize));
        break;
        default:
        break;
    }
    return _e;              ///< Return entity
}

