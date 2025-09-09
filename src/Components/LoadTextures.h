#pragma once
///< Extern Libraries.
#include "raylib.h"
///< Libraries C.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
///< Libraries CGame
#include "Entity.h"
#include "Textures.h"
////////////////////////////////////////////////////////////////
///<
////////////////////////////////////////////////////////////////
/**
 * @brief Load map textures from the file.
 * 
 * This function loads a tile map from a specified file path and initializes its texture and size.
 * 
 * @param _path Path to the tile map image file.
 * @param w Width of the tile map.
 * @param h Height of the tile map.
 * 
 * @return TileMap* Pointer to the loaded TileMap structure.
 * 
 * This function allocates memory for a TileMap structure, loads the image from the specified path,
 * creates a texture from the image, and sets the size of the tile map. It returns a pointer to the TileMap structure.
 */
TileMap* LoadMapTextures(char*, const int, const int);
/**
 * @brief Fill textures array for the Map.
 * 
 * This function fills the textures array in the RenderData structure with textures extracted from the tile map image.
 * 
 * @param renderData Pointer to the RenderData structure containing the tile map image and textures array.
 * 
 * @return 'Void'.
 * 
 * This function iterates through the tile map image, extracts non-empty tiles as subimages, and loads them into the textures array.
 * It also unloads the original tile map image after processing.
 */
void FillTextures(RenderData*);
/**
 * @brief Fill Texture2D* array for load all textures for Entity struct.
 * 
 * This function fills the Texture2D array with textures extracted from the player's tile map.
 * 
 * @param _TextureList Pointer to the Texture2D array where textures will be stored.
 * @param _TileMapPlayer Pointer to the TileMap structure containing the player's tile map image
 * 
 * @return 'void'.
 * 
 * This function iterates through the tile map image, extracts non-empty tiles as subimages, and loads them into the Texture2D array.
 * It also unloads the original tile map image after processing.
 */
void FillTexturesEntity(Texture2D*,TileMap*);
/**
 * @brief Render map from the data information.
 * 
 * This function renders the tile map based on the data provided in the RenderData structure.
 * It draws each tile according to its ID, using the textures stored in the textures array.
 * 
 * @param _mD Pointer to the RenderData structure containing the tile map data and textures.
 * @param _slct Index of the selected map to render.
 * 
 * @return 'Void'.
 * 
 * This function iterates through the map data, calculates the source and destination rectangles for each tile,
 * and draws the corresponding texture. If a tile ID is negative, it draws an empty texture instead.
 */
void RenderTileMap(RenderData*,int);
/**
 * @brief Render player entity on the screen.
 * 
 * This function renders the player entity by drawing its collision box and texture based on its current direction.
 * 
 * @param eplayer Pointer to the Entity structure representing the player.
 * 
 * @return 'Void'.
 * 
 * This function draws a rectangle around the player's collision box for debugging purposes and then draws the player's texture
 * based on the direction the player is looking. The texture is drawn at the player's current position,
 * adjusted for velocity and frame rate.
 */
void RenderPlayer(const Entity*);
/**
 * @brief Validate if the tile is empty.
 * 
 * Checks whether the tile in the given image (TileAtlas) at position `(x, y)` is empty.
 * This function checks each pixel in a square of size TILE_SIZE x TILE_SIZE
 * starting from the specified `(x, y)` position. If any pixel has an alpha value
 * greater than 0, it returns false, indicating that the tile is not empty.
 * 
 * @param image Image to validate from the TileAtlas.
 * @param x     Initial position on the X axis.
 * @param y     Initial position on the Y axis.
 * 
 * @return true if the tile is empty, false if there is something.
 * 
 * This function iterates through the pixels in the specified area of the image,
 * checking their alpha values. If it finds any pixel with an alpha value greater than 0
 * (indicating that it is not transparent), it returns false. If all pixels are transparent
 * (alpha value of 0), it returns true, indicating that the tile is empty.
 */
bool IsTileEmpty(Image,int,int);
////////////////////////////////////////////////////////////////




