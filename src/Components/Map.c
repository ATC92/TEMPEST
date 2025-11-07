#include "Map.h"
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
RenderData* LoadInformationMap(char* pathTileMap, ...)
{
    va_list args;
    va_start(args,pathTileMap);

    const char* layerPath = NULL;
    size_t index = 0;
    
    ///< Allocate Memory to RenderData.
    RenderData* tempData = (RenderData*)calloc(1,sizeof(RenderData));
    tempData->mapsData = (MapData*)calloc(5,sizeof(MapData));
    ///< Load Layers
    while ((layerPath = va_arg(args, const char*)) != NULL)
    {
        tempData->mapsData[index].data =LoadMapTiles(layerPath,&tempData->mapsData[index].width,&tempData->mapsData[index].height);
        tempData->mapsData[index].size = (Rectangle){0,0,(float)tempData->mapsData[index].width * 16, (float)tempData->mapsData[index].height * 16};
        index ++;
    }
    ///< Load Textures
    ///<    TileMap && EmptyTexture
    va_end(args);
    tempData->tileMapTex = LoadTexture(pathTileMap);
    if(!IsTextureValid(tempData->tileMapTex))
        TraceLog(LOG_ERROR,"TilMap not valid");
    int sizeArray = (tempData->tileMapTex.width / TILE_SIZE) * (tempData->tileMapTex.height / TILE_SIZE);
    tempData->texturesArray = (Texture2D*)calloc(sizeArray,sizeof(Texture2D));
    tempData->emptyTexture = LoadTexture(ASSETS"/Tilemap/EmptyTexture.png");
    tempData->sizeArrayTextures = FillTextures(tempData);
    return tempData;
}
//////////////////////////////////////////////////////////////////
int** LoadMapTiles(const char* path, int* c, int* r)
{
    ///< Load file CSV[MAP]
    FILE* archivo = fopen(path,"r");
    if (!archivo)
    {
        TraceLog(LOG_ERROR,"File error not loaded");
        return NULL;
    }
    ///< Read R*C.
    char b[8192];
    int filas=0, columnas=0;
    while (fgets(b,sizeof(b),archivo))
    {
        if (filas == 0)
        {
            char* copia = strdup(b);
            char* token = strtok(copia,",");
            while (token)
            {
                columnas++;
                token = strtok(NULL,",");
            }
            free(copia);
        }
        filas++;
    }
    rewind(archivo);

    //< Matrix creation **.
    int** mapa = calloc((size_t)filas, sizeof(int*));
    for (int i = 0; i < filas; i++)
        mapa[i] = calloc((size_t)columnas, sizeof(int));
    // Fill Matrix
    int f = 0;
    while (fgets(b, sizeof(b), archivo) && f < filas)
    {
        int c = 0;
        char* token = strtok(b, ",");
        while (token && c < columnas)
        {
            mapa[f][c] = atoi(token);
            token = strtok(NULL, ",");
            c++;
        }
        f++;
    }
    fclose(archivo);

    if(columnas)*c = columnas;
    if(filas)*r = filas;

    return mapa;
}

void DestroyRenderMap(RenderData** self, TypeMap tMap)
{
    for (int i=0; i < self[tMap]->sizeArrayTextures; i++)
    {
        if(IsTextureValid(self[tMap]->texturesArray[i]))
        {
            UnloadTexture(self[tMap]->texturesArray[i]);
            self[tMap]->texturesArray[i] = (Texture2D){0};
        }
    }
    free(self[tMap]->texturesArray);
    UnloadTexture(self[tMap]->emptyTexture);

    for(int i=0; i < self[tMap]->mapsData[0].height;i++)
        free(self[tMap]->mapsData[0].data[i]);
    for(int i=0; i < self[tMap]->mapsData[1].height;i++)
        free(self[tMap]->mapsData[1].data[i]);
    free(self[tMap]->mapsData[0].data);
    free(self[tMap]->mapsData[1].data);
}
//////////////////////////////////////////////////////////////////


