#include "LoadTextures.h"
//////////////////////////////////////////////////////////////////////////////////////
TileMap* LoadMapTextures(char* _path,const int w, const int h)
{
    TileMap* tempMapData = (TileMap*)calloc(1,sizeof(TileMap));
    tempMapData->tmImage = LoadImage(_path);
    tempMapData->texture = LoadTextureFromImage(tempMapData->tmImage);
    tempMapData->tmSize = (Rectangle){0.f,0.f,(float)w,(float)h};
    return tempMapData;
}
//////////////////////////////////////////////////////////////////
int FillTexturesEntity(Texture2D* _TextureList,TileMap* _TileMapPlayer)
{
    ///< 
    int countTiles = 0;
    int tilesX = _TileMapPlayer->tmImage.width / TILE_SIZE;
    int tilesY = _TileMapPlayer->tmImage.height / TILE_SIZE;
    ///< 
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int tileX = x * TILE_SIZE;
            int tileY = y * TILE_SIZE;
            if (!IsTileEmpty(_TileMapPlayer->tmImage, tileX, tileY))
            {
                /// Take the tile as a subimage.
                Image tile = ImageFromImage(_TileMapPlayer->tmImage, (Rectangle){ (float)tileX, (float)tileY, TILE_SIZE, TILE_SIZE });
                _TextureList[countTiles] = LoadTextureFromImage(tile);
                UnloadImage(tile);
                countTiles++;
            }
        }
    }
    UnloadImage(_TileMapPlayer->tmImage);
    return countTiles;
}
//////////////////////////////////////////////////////////////////
int FillTextures(RenderData* renderData)
{
    int countTiles = 0;
    int tilesX = renderData->tileMap->tmImage.width / TILE_SIZE;
    int tilesY = renderData->tileMap->tmImage.height / TILE_SIZE; 
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int tileX = x * TILE_SIZE;
            int tileY = y * TILE_SIZE;
            if (!IsTileEmpty(renderData->tileMap->tmImage, tileX, tileY))
            {
                // Extract tile as a subimage.
                Image tile = ImageFromImage(renderData->tileMap->tmImage, (Rectangle){ (float)tileX, (float)tileY, TILE_SIZE, TILE_SIZE });
                renderData->texturesArray[countTiles] = LoadTextureFromImage(tile);
                UnloadImage(tile);
                countTiles++;
            }
        }
    }
    return countTiles;
    UnloadImage(renderData->tileMap->tmImage);
}
//////////////////////////////////////////////////////////////////
bool IsTileEmpty(Image image, int x, int y)
{
    for (int i = 0; i < TILE_SIZE; i++)
    {
        for (int j = 0; j < TILE_SIZE; j++)
        {
            Color pixel = GetImageColor(image, x + i, y + j);
            if (pixel.a > 0) return false;                          ///< If Something is there, is not empty.
        }
    }
    return true;
}
//////////////////////////////////////////////////////////////////
void RenderTileMap(RenderData* _mD, int _slct)
{
    int tileset_columns = 5;
    for (int y = 0; y < _mD->mapsData[_slct].height; y++)
    {
        for (int x = 0; x < _mD->mapsData[_slct].width; x++)
        {
            int tile_id = _mD->mapsData[_slct].data[y][x];
            Rectangle source = {
                .x = (float)(tile_id % tileset_columns) * TILE_SIZE,
                .y = (float)(tile_id / tileset_columns) * TILE_SIZE,
                .width = TILE_SIZE,
                .height = TILE_SIZE
            };
            Rectangle dest = {
                .x = (float)(x * TILE_SIZE),
                .y = (float)(y * TILE_SIZE),
                .width = TILE_SIZE,
                .height = TILE_SIZE
            };
            Vector2 origin = {0 , 0};
            if (tile_id >= 0)
            {
                DrawTexturePro(_mD->texturesArray[tile_id], source, dest, origin, 0.0f, WHITE);
            }
            else
            {
                DrawTexturePro(_mD->emptyTexture, source, dest, origin, 0.0f, WHITE);
            }
        }
    }
}
//////////////////////////////////////////////////////////////////
void RenderPlayer(const Entity* eplayer)
{
#if DEBUG
    ///< Draw collision box for debugging
    DrawRectangleLines(
    (int)eplayer->_rect.x,
    (int)eplayer->_rect.y,
    (int)eplayer->_rect.width,
    (int)eplayer->_rect.height,
    RED);
#endif

    int look = eplayer->_eLook;
    CustomScale(0.5f);
        DrawSpriteAnimationPro(&eplayer->spriteAnimation[look],eplayer->position,0.f,(Vector2){0,0},WHITE,4);
    CustomScale(1.0f);
}
/////////////////////////////////////////////////////////////////////////


