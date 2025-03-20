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
cJSON* Load_cJSON(const char* path, ListTileSize* szList)
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
    ///< Array Size for each cJSON load
    GetArraySizeJSON(json,szList);
    printf("\n\nERROR HERE");

    return json;
}
/**
 * @brief Size of the JSON File
 */
void GetArraySizeJSON(const cJSON* json,ListTileSize* szList)
{
    ///<
    cJSON* _iTiles = cJSON_GetObjectItemCaseSensitive(json, "tiles");
    cJSON* _iMaps = cJSON_GetObjectItemCaseSensitive(json, "maps");
    cJSON* _iPlayer = cJSON_GetObjectItemCaseSensitive(json, "PLAYER");
    // cJSON* _iNPC = cJSON_GetObjectItemCaseSensitive(json, "NPC");
    ///< Get the size of each cJSON List.
    if(cJSON_GetArraySize(_iTiles) > 0)
        szList->_sz1 = cJSON_GetArraySize(_iTiles);
    if(cJSON_GetArraySize(_iMaps) > 0)
        szList->_sz2 = cJSON_GetArraySize(_iMaps);
    if(cJSON_GetArraySize(_iPlayer) > 0)
        szList->_sz3 = cJSON_GetArraySize(_iPlayer);
}
/**
 * @brief Process Tile
 * 
 * This function process the entity to load the textures from the cJSON
 * 
 * @param item          Item type void*.
 * @param json          Parsed cJSON object.
 * 
 * @note The @n `void*` will be cast as a @n `sTile*`.
 * 
 * @return @n `void`
 */
void ProcessTile(void* item, const cJSON* json)
{
    ///< Init temp declaration
    sTile* tile = (sTile*)item;
    cJSON* Name = cJSON_GetObjectItemCaseSensitive(json,"Name");
    cJSON* ID = cJSON_GetObjectItemCaseSensitive(json, "ID");
    cJSON* patchTexture = cJSON_GetObjectItemCaseSensitive(json, "tPatch");
    ///< Init temp declaration
    if (Name && cJSON_IsString(Name) && ID && cJSON_IsNumber(ID) && patchTexture && cJSON_IsString(patchTexture))
    {
        tile->name = strdup(Name->valuestring);                         ///< Duplicate Name
        tile->ID = ID->valueint;                                        ///< Copy the ID of the JSON Tile
        tile->texture = LoadTexture(patchTexture->valuestring);         ///< LoadTexture Vector2D Raylib
        tile->parseTileGen = cJSON_Duplicate(json,1);                   ///< Duplicate the cJSON struct, if Free(json), the `tile->parseJson_Map` lost.
    }
}
/**
 * @brief Process Entity
 * 
 * This function process the entity to load the textures from the cJSON
 * 
 * @param item          Item type void*.
 * @param json          Parsed cJSON object.
 * 
 * @note The @n `void*` will be cast as a @n `tEntity*`.
 * 
 * @return @n `void`
 */
void ProcessEntity(void* item, const cJSON* json)
{
    ///< Init temp declaration
    tEntity* entity = (tEntity*)item;
    cJSON* Name = cJSON_GetObjectItemCaseSensitive(json,"Name");
    cJSON* ID = cJSON_GetObjectItemCaseSensitive(json, "ID");
    cJSON* patchTexture = cJSON_GetObjectItemCaseSensitive(json, "tPatch");
    ///< Validation
    if (Name && cJSON_IsString(Name) && ID && cJSON_IsNumber(ID) && patchTexture && cJSON_IsString(patchTexture))
    {
        entity->name = strdup(Name->valuestring);                       ///< Duplicate Name
        entity->ID = ID->valueint;                                      ///< Copy the ID of the JSON Tile
        entity->Texture = LoadTexture(patchTexture->valuestring);       ///< LoadTexture Vector2D Raylib
        entity->parseJson_Entity = cJSON_Duplicate(json,1);             ///< Duplicate the cJSON struct, if Free(json), the `tile->parseJson_Map` lost.
    }
}
/**
 * @brief Load all textures from cJSON.
 * 
 * This is a generic function that processes a JSON object and allocates 
 * memory for a structure.
 *
 * @param json           Parsed cJSON object.
 * @param key            Key used to extract data from cJSON.
 * @param struct_size    Size of the struct to allocate.
 * @param max_items      Maximum number of items to allocate. \n
 *                       @n `Example: StructName* ptr = malloc(max_items * struct_size);`
 * @param process_func   Function pointer to process each item. \n
 *                       @n `Signature: void* ProcessItemFunc(const cJSON*).`
 *  
 * @return @n `void*`         Pointer to the allocated structure.
 */
void* LoadTexturesFromJSON(const cJSON* json, const char* key, size_t struct_size, int max_items, ProcessItemFunc processFunc)
{
    void* items = calloc(max_items, struct_size);
    if (!items) {
        perror("Error allocating memory");
        return NULL;
    }

    cJSON* jItems = cJSON_GetObjectItemCaseSensitive(json, key);
    if (!jItems || !cJSON_IsObject(jItems))
    {
        printf("\n\nError: JSON key '%s' is missing or is not an object.\n", key);
        free(items);
        return NULL;
    }
    cJSON* _item;
    int i = 0;
    cJSON_ArrayForEach(_item, jItems)
    {
        if (i >= max_items) break;                              ///< Avoid Overflows
        processFunc( (char*)items + (i * struct_size), _item);
        i++;
    }

    if (i == 0) {
        printf("\n[ERROR] No tiles were processed!\n");
        free(items);
        return NULL;
    }
    return items;
}
/**
 * @brief Generate an array of tiles (sTile*).
 * 
 * Parses a cJSON object to create an array of tiles.
 *
 * @param json Parsed cJSON object.
 * @return @n `sTile*` Pointer to the generated array of tiles.
 */
sTile* LoadMapTextures(cJSON* _data,int _sz)
{
    return (sTile*)LoadTexturesFromJSON(_data, "tiles", sizeof(sTile), _sz, ProcessTile);
}
/**
 * @brief Generate an array of textures (tEntity*).
 * 
 * Loads textures from a JSON file and creates an array of entities.
 * 
 * @param Patch Path to the JSON file containing the configuration.
 * @param key Key identifying the entity to load from the JSON.
 * @param _lsz Size List of the amount of textures in the JSON.
 * @return @n `tEntity*` Pointer to the generated array of textures.
 */
tEntity* GenTextureEntity(const char*path, const char*key,ListTileSize** _lsz)
{
    cJSON* json = Load_cJSON(path,*_lsz);
    tEntity* eTemp;
    if(strcmp(key,"PLAYER") == 0)
        eTemp = LoadTexturesFromJSON(json, key, sizeof(tEntity), (*_lsz)->_sz3, ProcessEntity);
    else if(strcmp(key,"NPC") == 0)
        eTemp = LoadTexturesFromJSON(json, key, sizeof(tEntity), (*_lsz)->_sz4, ProcessEntity);
    return eTemp;
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
                (float)(tile_id % tileset_columns) * TILE_WIDTH,
                (float)(tile_id / tileset_columns) * TILE_HEIGHT,
                (float)TILE_WIDTH,
                (float)TILE_HEIGHT
            };

            Rectangle dest = {
                (float)(x * TILE_WIDTH),
                (float)(y * TILE_HEIGHT),
                (float)TILE_WIDTH,
                (float)TILE_HEIGHT
            };

            Vector2 origin = {0 , 0};

            if (tile_id >= 0)
            {
                DrawTexturePro(_mD->sTilesData[tile_id].texture, source, dest, origin, 0.0f, WHITE);
            }
        }
    }
}
/**
 * 
 */
void RenderPlayer(const Entity eplayer, const Camera2D _cam)
{
    Rectangle source = 
    { 
        (float)1 * TILE_WIDTH,
        (float)1 * TILE_HEIGHT, 
        (float)TILE_WIDTH, (float)TILE_HEIGHT 
    };

    Rectangle dest =
    {
        eplayer._player.position.x + ((1.f/GetFPS()) * eplayer._player.speed), 
        eplayer._player.position.y + ((1.f/GetFPS()) * eplayer._player.speed), 
        (float)TILE_WIDTH, (float)TILE_HEIGHT 
    };

    Vector2 origin = { 0, 0 };

    DrawTexturePro(eplayer._tEntity[eplayer._eLook].Texture, source, dest, origin, 0.0f, WHITE);
}

