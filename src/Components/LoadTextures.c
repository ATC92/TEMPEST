#include "LoadTextures.h"
//////////////////////////////////////////////////////////////////
int FillTextures(RenderData* renderData)
{
    int countTiles = 0;
    int tilesX = renderData->tileMapTex.width / TILE_SIZE;
    int tilesY = renderData->tileMapTex.height / TILE_SIZE; 
    Image img = LoadImageFromTexture(renderData->tileMapTex);
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int tileX = x * TILE_SIZE;
            int tileY = y * TILE_SIZE;

            if (!IsTileEmpty(img, tileX, tileY))
            {
                Image tile = ImageFromImage(img, (Rectangle){ (float)tileX, (float)tileY, TILE_SIZE, TILE_SIZE });
                renderData->texturesArray[countTiles] = LoadTextureFromImage(tile);
                UnloadImage(tile);
                countTiles++;
            }
        }
    }

    UnloadImage(img);
    UnloadTexture(renderData->tileMapTex);
    return countTiles;
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
void RenderTileMap(RenderData* _mD, LayerEnum _slct)
{
    int tileset_columns = _mD->mapsData->size.width;
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
void RenderEntity(const Entity* eplayer)
{
#if DEBUG
    DrawRectangleLines(
    (int)eplayer->boundingBox.x,
    (int)eplayer->boundingBox.y,
    (int)eplayer->boundingBox.width,
    (int)eplayer->boundingBox.height,
    RED);
    DrawRectangleLines(
    (int)eplayer->triggerBox.x,
    (int)eplayer->triggerBox.y,
    (int)eplayer->triggerBox.width,
    (int)eplayer->triggerBox.height,
    YELLOW);
#endif

    int look = eplayer->eLook;
    DrawSpriteAnimationPro(&eplayer->spriteAnimation[look],eplayer->position,0.f,(Vector2){0,0},WHITE,4,eplayer->boundingBox.width,eplayer->boundingBox.height);
}

/////////////////////////////////////////////////////////////////////////


