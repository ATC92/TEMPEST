#include "Entity.h"
//////////////////////////////////////////////////////////
Entity* GenEntity(int _t, char* _n, float _h, float _ar, float _sp, float _crt)
{
    Entity* _e = (Entity*)calloc(1,sizeof(Entity));                         ///< Generation Entity
    switch (_t)                                                             ///< Selection of the Type to gen.
    {
        case _PLAYER:
            _e->name = strdup(_n);                                          ///< Name of the Entity 
            _e->health = _h;                                                ///< Health of the Entity
            _e->armor = _ar;                                                ///< Health of the Entity
            _e->speed = _sp;                                                ///< Speed of the Entity 
            _e->crit = 0;                                                   ///< Critcal of the entity       
            _e->position = (Vector2){210,160};                              ///< Position of the Entity
            _e->prev_position = (Vector2){0,0};                             ///< Previous Position of the Entity
            _e->velocity = (Vector2){0,0};                                  ///< Velocity of the Entity
            _e->_typeEntity = _PLAYER;                                      ///< Type of Entity             
            _e->_rect = (Rectangle){0,0,16,16};                             ///< CollisionBox RECT of the Entity
            _e->_eLook = 2;                                                 ///< Where the entity is looking (Default: DOWN)
            _e->_textureArray = (Texture2D*)calloc(5,sizeof(Texture2D));    ///< Array of Textures of the Entity
            _e->_vectorColision = (Rectangle*)calloc(4,sizeof(Rectangle));  ///< Vector of Collision Rectangles
            break;
        case _ENEMY:
            _e->name = strdup(_n);                                          ///< Name of the Entity
            _e->health = _h;                                                ///< Health of the Entity
            _e->armor = _ar;                                                ///< Armor of the Entity
            _e->crit = _crt;                                                ///< Critical of the Entity
            _e->speed = _sp;                                                ///< Speed of the Entity
            _e->position = (Vector2){150,150};                              ///< Position of the Entity
            _e->prev_position = (Vector2){0,0};                             ///< Previous Position of the Entity
            _e->_typeEntity = _ENEMY;                                       ///< Type of Entity 
            _e->_rect = (Rectangle){0,0,16,16};                             ///< CollisionBox RECT of the Entity
            _e->_textureArray = (Texture2D*)calloc(5,sizeof(Texture2D));    ///< Array of Textures of the Entity
            break;
        default:
        break;
    }
    return _e;                                                              ///< Return entity
}
//////////////////////////////////////////////////////////



