#include "LoadTextures.h"
/**
 * @brief Loads and parses a JSON file into a cJSON object.
 * 
 * This function reads a JSON file from the given path, allocates memory for its content, 
 * and parses it into a `cJSON` object.
 * 
 * @param patch Path to the JSON file.
 * 
 * @return cJSON* Pointer to the parsed JSON object, or `NULL` if an error occurs.
 * 
 * @note The caller is responsible for freeing the returned `cJSON*` using `cJSON_Delete()`.
 * 
 * @warning If the file cannot be opened, memory allocation fails, or parsing fails, 
 *          the function returns `NULL`.
 * 
 * Example usage:
 * @code{.c}
 * cJSON* json = Load_cJSON("config.json");
 * @endcode
 */
cJSON* Load_cJSON(const char* path)
{
    FILE *file = fopen(path, "r");                                  ///< Creating the FILE
    if(!file) 
    { 
        perror("Error, json can't open"); 
        return NULL; 
    } 
    ///< Looking for the size of the json. 
    fseek(file,0,SEEK_END); 
    long fSize = ftell(file); 
    rewind(file);
    char* entityData = (char*)calloc(fSize + 1, sizeof(char));          ///< Create space for the data.
    ///< Validate if the malloc take the memory to allo cate
    if (!entityData) 
    { 
        perror("Error allocating memory"); 
        fclose(file); 
        return NULL; 
    } 
    fread(entityData,1,fSize,file);                                 ///< Read .JSON
    fclose(file);                                                   ///< Close the FILE
    ///< Parse the JSON file
    cJSON *json = cJSON_Parse(entityData);                          ///< Create cJSON Parse
    free(entityData);                                               ///< Char* mapData
    if (!json)
    {
        printf("Error, the JSON can't parse: %s\n",cJSON_GetErrorPtr());
        cJSON_Delete(json); 
        return NULL;
    }
    ///< Return Raw cJSON
    return json;
}
/**
 * @brief Generate an array of tiles (sTile*).
 * 
 * Parses a cJSON object to create an array of tiles.
 *
 * @param json Parsed cJSON object.
 * @return @n `sTile*` Pointer to the generated array of tiles.
 */
TileMap* LoadMapTextures(char* _path,const int w, const int h)
{
    TileMap* tempMapData = (TileMap*)calloc(1,sizeof(TileMap));
    tempMapData->tmImage = LoadImage(_path);
    tempMapData->texture = LoadTextureFromImage(tempMapData->tmImage);
    tempMapData->tmSize = (Rectangle){0,0,w,h};
    return tempMapData;
}
/**
 * 
 */
void FillTexturesEntity(Texture2D* _TextureList,TileMap* _TileMapPlayer)
{
    ///< 
    int countTiles = 0;
    int tilesX = _TileMapPlayer->tmImage.width / TILE_SIZE;
    int tilesY = _TileMapPlayer->tmImage.width / TILE_SIZE;
    ///< 
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int tileX = x * TILE_SIZE;
            int tileY = y * TILE_SIZE;
            if (!IsTileEmpty(_TileMapPlayer->tmImage, tileX, tileY))
            {
                // Extraer tile como subimagen
                Image tile = ImageFromImage(_TileMapPlayer->tmImage, (Rectangle){ tileX, tileY, TILE_SIZE, TILE_SIZE });
                _TextureList[countTiles] = LoadTextureFromImage(tile);
                UnloadImage(tile);
                countTiles++;
            }
        }
    }
    UnloadImage(_TileMapPlayer->tmImage);
}
/**
 * 
 */
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
/**
 * @brief Render all the map from the Parse cJSON
 * 
 * @param RenderData*           ///< 
 */
void RenderTileMap(RenderData* _mD, MapEnum _slct)
{
    int tileset_columns = 6;
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
            if (tile_id > 0)
            {
                DrawTexturePro(_mD->texturesArray[tile_id], source, dest, origin, 0.0f, WHITE);
            }
            // else
            // {
            //     DrawTexturePro(_mD->emptyTexture, source, dest, origin, 0.0f, WHITE);
            // }
        }
    }
}
/**
 * 
 */
void RenderPlayer(const Entity* eplayer)
{
    int tileset_columns = 4;
    Rectangle source = 
    { 
        .x = (float)(eplayer->_eLook % tileset_columns) * TILE_SIZE,
        .y = (float)(eplayer->_eLook / tileset_columns) * TILE_SIZE,
        .width = TILE_SIZE,
        .height = TILE_SIZE
    };
    Rectangle dest =
    {
        eplayer->position.x + ((1.f/GetFPS()) * eplayer->speed), 
        eplayer->position.y + ((1.f/GetFPS()) * eplayer->speed), 
        (float)TILE_SIZE, 
        (float)TILE_SIZE 
    };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(eplayer->_textureArray[eplayer->_eLook], source, dest, origin, 0.0f, WHITE);
}

