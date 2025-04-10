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
 * @brief Render all the map from the Parse cJSON
 * 
 * @param RenderData*           ///< 
 */
void RenderTileMap(RenderData* _mD, MapEnum _slct)
{
    int tileset_columns = 10;
    for (int y = 0; y < _mD->mapsData[_slct].height; y++)
    {
        for (int x = 0; x < _mD->mapsData[_slct].width; x++)
        {
            int tile_id = _mD->mapsData[_slct].data[y][x];
            Rectangle source = {
                (float)(tile_id % tileset_columns) * TILE_SIZE,
                (float)(tile_id / tileset_columns) * TILE_SIZE,
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };
            Rectangle dest = {
                (float)(x * TILE_SIZE),
                (float)(y * TILE_SIZE),
                (float)TILE_SIZE,
                (float)TILE_SIZE
            };
            Vector2 origin = {0 , 0};
            if (tile_id >= 0)
            {
                // DrawTexturePro(_mD->sTilesData[tile_id].texture, source, dest, origin, 0.0f, WHITE);
                ItemHT* item= SearchItem(_mD->hashTable,tile_id);
                DrawTexturePro(item->tile, source, dest, origin, 0.0f, WHITE);
            }
            else
            {
                DrawTexturePro(_mD->emptyTexture, source, dest, origin, 0.0f, WHITE);
            }
        }
    }
}
/**
 * 
 */
void RenderPlayer(const Entity* eplayer, const Camera2D _cam)
{
    Rectangle source = 
    { 
        (float)1 * TILE_SIZE,
        (float)1 * TILE_SIZE, 
        (float)TILE_SIZE, (float)TILE_SIZE 
    };
    Rectangle dest =
    {
        eplayer->position.x + ((1.f/GetFPS()) * eplayer->speed), 
        eplayer->position.y + ((1.f/GetFPS()) * eplayer->speed), 
        (float)TILE_SIZE, (float)TILE_SIZE 
    };
    Vector2 origin = { 0, 0 };
    ItemHT* item= SearchItem(eplayer->_HT,eplayer->_eLook);
    DrawTexturePro(item->tile, source, dest, origin, 0.0f, WHITE);
}

