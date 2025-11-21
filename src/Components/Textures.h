#pragma once
///< TEMPEST Lib
#include "../Engine/Flags.h"

////////////////////////////////////////////////////
#define TILE_SIZE 16
////////////////////////////////////////////////////
/**
 * @brief MapEnum, Enum that selects the current map.
 * 
 * This enum defines the different levels in the game.
 * Each level corresponds to a specific map that can be rendered.
 * 
 * @c level_1   Represents Level 1 \\
 * @c level_2   Represents Level 2
 */
typedef enum _layerEnum
{
    LAYER_1,
    LAYER_2,
    LAYER_3,
    LAYER_4,
    LAYER_5
}LayerEnum;
////////////////////////////////////////////////////
/**
 * @brief MapData, Save information of the Map
 * 
 * This struct represents the data of a map in the game.
 * It contains the name of the level, its dimensions (width and height),
 * and a 2D array of integers representing the map data.
 * 
 * @c name      Name of the Level \\
 * @c width     Width of the Map (int) \\
 * @c height    Height of the map (int) \\
 * @c data      Information of the map [(int) x][(int) y], but ptr**.
 * 
 * This struct is used to store the map's metadata, including its name and dimensions,
 * as well as the actual map data represented as a 2D array of integers.
 * The `data` field is a pointer to a dynamically allocated 2D array, allowing
 * for flexible map sizes and easy access to individual tiles.
 */
typedef struct _MapData
{
    Rectangle size;         ///< Map size
    int width;              ///< Width of the Map (int).
    int height;             ///< Heigth of the map (int).
    int** data;             ///< Information of the map [(int) x][(int) y], but ptr**.
}MapData;
/**
 * @brief RenderData, Struct that holds all the data for rendering the map.
 * 
 * This struct contains all the necessary data for rendering the map in the game.
 * It includes a pointer to the map data, a pointer to the tile map,
 * an enum to select the current map, and an array of textures used for rendering.
 * 
 * @c mapsData         Pointer to the map data \\
 * @c tileMap          Pointer to the tile data \\
 * @c mapSlctr         Enum that selects the current map \\
 * @c texturesArray    Array of textures used for rendering the map \\
 * @c emptyTexture     Empty texture used for rendering empty tiles
 */
typedef struct _renderData
{
    int sizeArrayTextures;      ///< Size of the textures array.
    size_t numMaps;             ///< Size of the mapsData
    LayerEnum mapSlctr;         ///< Enum that selects the current map.
    MapData* mapsData;          ///< Pointer to the map data.
    Texture2D tileMapTex;       ///< Pointer to the Texture2D.
    Texture2D* texturesArray;   ///< Textures array used for rendering the map.
    Texture2D emptyTexture;     ///< Empty texture.
}RenderData;
/////////////////////////////////////////////////////////////////////////////////////