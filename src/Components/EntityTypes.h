//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * 
 */
typedef enum _typeNPC
{
    _NPC_PLAYER = -1,
    _NPC_MIKA,
    _NPC_ARTURO
}TypeNPC;
/**
 * @brief Enumeration of the directions in which an `Entity` can look.
 * 
 * This enum defines the possible orientations for an `Entity`.
 * 
 * @note The values correspond to directional indices.
 * 
 * Contains:
 * - @c UP        = 0
 * - @c DOWN      = 1
 * - @c RIGHT     = 2
 * - @c LEFT      = 3
 */
typedef enum _eLooking
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    IDLE
}eLooking;
/**
 * 
 */
typedef enum _Accions
{
    A_NONE_ACCTION = -1,
    A_POPUP,
    A_INTERACTION
}TypeAccion;
/**
 * @brief struct with the enumeration of the type of @n `Entity`
 * 
 * ---
 * 
 * Contains:
 * 
 * @param _PLAYER   0
 * @param _ENEMY    1
 * 
 * ---
 */
typedef enum _typeEntity
{
    _TYPE_ENTITY_NONE = -1,
    _PLAYER,
    _NPC,
    _OBJECT_DICE
}TypeEntity;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////