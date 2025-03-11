#pragma once

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include Lib of Entity
#include "../Entity/Entity.h"
// TILE TEXTURE SIZE
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
// WORLD MAP SIZE
#define WORLD_TILE_WIDTH 20         // 20 * TILE_WIDTH
#define WORLD_TILE_HEIGHT 20        // 20 * TILE_HEIGHT
// TEXTURES ASSETS 
#define MAX_TEXTURES 1
typedef enum
{
    TEXTURE_TILEMAP = 0
}Texture_Assets;

// sTILE
typedef struct
{
    float x;
    float y;
} sTile;

/*


*/
void InitGame();
/*


*/
void GameRender();
/*

*/
void DeInitGame();
/*

*/
void GameUpdate();
/*
    Update Movement of the Entity Player
        This will update the position in the game 2D.
    
    In:         
        - Entity*

    Return:
        - Void

    ----------------------------------------------------
    Last Modification 07/03/2025
*/
void updateMovement();




