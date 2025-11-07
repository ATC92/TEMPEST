//////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "Textures.h"
#include "LoadTextures.h"
//////////////////////////////////////////////////////////////////
typedef enum _typeMap
{
    MP_MINI_TOWN,
    MP_TOWN
}TypeMap;
//////////////////////////////////////////////////////////////////
/**
 * @brief Load all information about the map.
 * 
 * This function loads the map data, tile map textures, and empty texture.
 * It returns a pointer to a RenderData structure containing all the loaded information.
 * 
 * @param `void`
 * 
 * @return RenderData* Pointer to the RenderData structure containing map data and textures.
 */
RenderData* LoadInformationMap(char* pathTileMap, ...);
/**
 * @brief Load map tiles from a CSV file.
 * 
 * This function reads a CSV file containing map tile data and returns a 2D array of integers representing the map.
 * It also sets the number of columns and rows in the map.
 * 
 * @param path Path to the CSV file containing map tile data.
 * @param c Pointer to an integer where the number of columns will be stored.
 * @param r Pointer to an integer where the number of rows will be stored.
 * 
 * @return int** Pointer to a 2D array of integers representing the map tiles.
 */
int** LoadMapTiles(const char*,int*,int*);
/**
 * 
 */
void DestroyRenderMap(RenderData** self, TypeMap tMap);

//////////////////////////////////////////////////////////////////