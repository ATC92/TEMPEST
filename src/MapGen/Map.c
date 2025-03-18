#include "Map.h"
RenderData* GenTileMap(void)
{
    // Var Temp Return
    RenderData* tempData = (RenderData*)calloc(1,sizeof(RenderData));
    ///< Load cJSON
    tempData->mapRoot = Load_cJSON("src/MapGen/map.json");
    tempData->sTilesData = LoadMapTextures(tempData->mapRoot);
    return tempData;
}
void CreateMap_sTile(RenderData* _mD, MapEnum _s)
{
    ///< Validate tileMap before use
    if (!_mD->sTilesData) {
        printf("Error: tileMap es NULL.\n");
        return;
    }
    ///< Allocate memory to _mD->mapsData
    _mD->mapsData = (MapData*)calloc(2,sizeof(MapData));
    ///< Allocate memory to _mD->mapsData->Data
    
    cJSON* jMaps = cJSON_GetObjectItemCaseSensitive(_mD->mapRoot,"maps");
    ///< Validate jMaps before use
    if (!jMaps)
    {
        printf("Error: 'maps' key not found in JSON.\n");
        return;
    }
    if (jMaps)
    {
        cJSON* map;
        int i = 0;
        cJSON_ArrayForEach(map, jMaps)
        {
            cJSON* Name = cJSON_GetObjectItemCaseSensitive(map,"Name");
            cJSON* ID = cJSON_GetObjectItemCaseSensitive(map, "ID");
            cJSON *width = cJSON_GetObjectItemCaseSensitive(map, "Width");
            cJSON *height = cJSON_GetObjectItemCaseSensitive(map, "Height");
            cJSON *data = cJSON_GetObjectItemCaseSensitive(map, "Data");
            
            if(Name && cJSON_IsString(Name)         &&
                ID && cJSON_IsNumber(ID)            &&
                width && cJSON_IsNumber(width)      &&
                height && cJSON_IsNumber(height)    && 
                data)
            {
                _mD->mapsData[i].name = strdup(Name->valuestring);              ///< Duplicate Name from the Name cJSON
                _mD->mapsData[i].width = width->valueint;                       ///< Duplicate Width from the width JSON
                _mD->mapsData[i].height = height->valueint;                     ///< Duplicate heigth from the heigth JSON

                ///< Allocate Memory to int** data.
                _mD->mapsData[i].data = (int**)calloc(_mD->mapsData[i].height, sizeof(int*));
                for (int k = 0; k < _mD->mapsData[i].width; k++)
                {
                    _mD->mapsData[i].data[k] = (int*)calloc(_mD->mapsData[i].width, sizeof(int));
                }
                ///< Fill the int** Data with values.
                for (int y = 0; y < _mD->mapsData[i].height; y++)
                {
                    cJSON* row = cJSON_GetArrayItem(data,y);
                    for (int x = 0; x < _mD->mapsData[i].width; x++)
                    {
                        cJSON* cell = cJSON_GetArrayItem(row,x);
                        _mD->mapsData[i].data[y][x] = cell->valueint;
                    }
                }
                i++;
            }
        }
    }
}

