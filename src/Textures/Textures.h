#pragma once
///< Externs Lib.
#include "raylib.h"
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
///< CGame Lib
////////////////////////////////////////////////////
#define TILE_SIZE 16
////////////////////////////////////////////////////
/**
 * @brief sTILE, The space of the world in Tiles
 */
typedef struct _tileMap
{
    Image tmImage;          ///< Image of the TileMap.
    Texture2D texture;      ///< Texture 2D.
    Rectangle tmSize;       ///< Size of the TileMap.
}TileMap;
/**
 * @brief MapData, Save information of the map
 */
typedef struct _MapData
{
    char* name;             ///< Name of the Level.
    int width;              ///< Width of the Map (int).
    int height;             ///< Heigth of the map (int).
    int** data;             ///< Information of the map [(int) x][(int) y], but ptr**.
    // cJSON* parseMapGen;     ///< Struct cJSON with the raw map in JSON format. 
}MapData;
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
    MapData* mapsData;          ///< Pointer to the map data.
    TileMap* tileMap;           ///< Pointer to the tile data.
    MapEnum mapSlctr;           ///< Enum that selects the current map.
    Texture2D* texturesArray;   ///< 
    Texture2D emptyTexture;     ///< Empty texture.
}RenderData;
/////////////////////////////////////////////////////////////////////////////////////