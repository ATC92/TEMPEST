#pragma once
///< Extern Libraries.
#include "cJSON.h"
#include "raylib.h"
///< Libraries C.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
///< Libraries CGame
#include "../Utils/LoadTextures.h"
///< TILE TEXTURE SIZE
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define WORLD_TILE_WIDTH 10         // 10 * TILE_WIDTH
#define WORLD_TILE_HEIGHT 10        // 10 * TILE_HEIGHT
///< MapData
///< Save information of the map
typedef struct _MapData
{
    char* name;
    int width;
    int height;
    int** data;
    cJSON* parseMapGen;
}MapData;
/**
 * @brief sTILE, The space of the world in Tiles
 */
typedef struct _sTile
{
    char* name;             ///< Name of the texture.
    int ID;                 ///< ID of the Texture in the JSON.
    Texture2D texture;      ///< Texture 2D.
    cJSON* parseTileGen;    ///< cJSON Map.
}sTile;
/**
 * @brief Enumerate Map, State Machine for the map selector
 */
typedef enum _mapEnum
{
    level_1,                ///< Level_1.
    level_2                 ///< Level_2.
}MapEnum;
/**
 * @brief Structure that stores rendering-related data.
 */
typedef struct _renderData
{
    MapData* mapsData;      ///< Pointer to the map data.
    sTile* sTilesData;      ///< Pointer to the tile data.
    MapEnum mapSlctr;       ///< Enum that selects the current map.
    cJSON* mapRoot;         ///< Root node of the cJSON map.
}RenderData;

/**
 * @brief Generate Tiles for the Map, Using cJSON.
 * 
 * @param void
 * 
 * @return @n `RenderData*` ///< Returns all Textures and MapData loaded.
 */
RenderData* GenTileMap(void);
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
void CreateMap_sTile(RenderData*,MapEnum);


