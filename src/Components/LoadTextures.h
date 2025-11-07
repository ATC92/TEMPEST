#pragma once
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "Entity.h"
#include "Textures.h"
////////////////////////////////////////////////////////////////
///<
////////////////////////////////////////////////////////////////
/**
 * @brief Fill textures array for the Map.
 * 
 * This function fills the textures array in the RenderData structure with textures extracted from the tile map image.
 * 
 * @param renderData Pointer to the RenderData structure containing the tile map image and textures array.
 * 
 * @return 'int'.
 * 
 * This function iterates through the tile map image, extracts non-empty tiles as subimages, and loads them into the textures array.
 * It also unloads the original tile map image after processing.
 */
int FillTextures(RenderData*);
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
void RenderTileMap(RenderData* _mD,LayerEnum _slct);
/**
 * @brief Render entity on the screen.
 * 
 * This function renders the entity by drawing its collision box and texture based on its current direction.
 * 
 * @param eplayer Pointer to the Entity.
 * 
 * @return 'Void'.
 * 
 * This function draws a rectangle around the Entity collision box for debugging purposes and then draws the entity texture
 * based on the direction the entity is looking. The texture is drawn at the entity current position,
 * adjusted for velocity and frame rate.
 */
void RenderEntity(const Entity*);
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




