#pragma once
#include "raylib.h"
/*
    ----------------------------------------------------
    Definition of the types of entitys.
    
    - PLAYER
    - ENEMY
    ----------------------------------------------------
    - Last Modification 06/03/2025
    ----------------------------------------------------
*/
typedef enum
{
    PLAYER,
    ENEMY
}eType;

/**
 * @brief Structure for Player entity.
 * 
 * - Last Modification 06/03/2025
 */
typedef struct Player
{
    char* name;         ///< Name of the entity Player
    float health;       ///< Health of the entity Player
    float armor;        ///< Armor of the entity Player
    float speed;        ///< Speed of the entity Player
    float exp;          ///< Experience of the entity Player
    Vector2 position;   ///< Position {X,Y}
}_ply;

/**
 * @brief Structure for Enemy entity.
 * 
 * - Last Modification 06/03/2025
 */
typedef struct Enemy
{
    char* name;         ///< Name of the entity Enemy
    float health;       ///< Health of the entity Enemy
    float armor;        ///< Armor of the entity Enemy
    float speed;        ///< Speed of the entity Enemy
    float crit;         ///< Critical of the entity Enemy
    float exp;          ///< Experience of the entity Enemy
    Vector2 position;   ///< Position {X,Y}
}_eny;

/*
    ----------------------------------------------------
        Union Data Entity
            It will contain all the entities that the Union can handle.
            Adding:
                - Player
                - Enemy
    ----------------------------------------------------
    - Last Modification 06/03/2025
    ----------------------------------------------------
*/
typedef union _eData
{
    // Struct type Player
    _ply Player;
    // Struct type Enemy
    _eny Enemy;
}eData;

/*
    ----------------------------------------------------
        Main Entity
        Contain:
            * _eData, Entity Data.
            * _eType, Entity Type

    ----------------------------------------------------
    - Last Modification 06/03/2025
    ----------------------------------------------------
*/
typedef struct _entity
{
    // Union entity 
    eData EntityData;
    // Struct Entity Type
    eType EntityType;
}Entity;


// Funtions of the game

/*
    GenEntity
    - char _t       = Type of the Entity
    - char* _n      = Name of the Entity
    - float _h      = Health of the Entity
    - float _ar     = Armor of the Entity
    - float _sp     = Speed of the Entity
    - float _crt    = Critical of the Entity
    ----------------------------------------------------
    - Last Modification 06/03/2025
    ----------------------------------------------------
*/
Entity GenEntity(int,char*,float,float,float,float);

