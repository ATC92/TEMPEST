#pragma once
///< Extern Libraries.
#include "raylib.h"
///< Libraries C.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
///< Libraries CGame
#include "Textures.h"
#include "LoadTextures.h"
///< TILE TEXTURE SIZE
// #define WORLD_TILE_WIDTH 10         // 10 * TILE_WIDTH
// #define WORLD_TILE_HEIGHT 10        // 10 * TILE_HEIGHT
/**
 * @brief Generate Tiles for the Map, Using cJSON.
 * 
 * @param void
 * 
 * @return @n `RenderData*` ///< Returns all Textures and MapData loaded.
 */
RenderData* LoadInformationMap(void);
/**
 * @brief Creates the map after loading the texture.
 *        Uses JSON to load all necessary data.
 * 
 *        @n - cJSON `NAME`
 * 
 *        @n - cJSON `ID`
 * 
 *        @n - cJSON `WIDTH`
 * 
 *        @n - cJSON `HEIGHT`
 * 
 *        @n - cJSON `DATA`
 * 
 * @return void
 * @note @n `cJSON DATA` is an n×n matrix, defined by the `WIDTH` and `HEIGHT` 
 *           values in the JSON.
 */
// void CreateMapTiles(RenderData*);
/**
 * 
 */
int** LoadMapTiles(char*,int*,int*);
/**
 * 
 */
void FillTextures(RenderData*);

