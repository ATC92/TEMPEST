#include "Map.h"
RenderData* LoadInformationMap(void)
{
    // Var Temp Return
    RenderData* tempData = (RenderData*)calloc(1,sizeof(RenderData));
    ///< Load Maps
    tempData->mapsData = (MapData*)calloc(2,sizeof(MapData));
    tempData->mapsData[0].data = LoadMapTiles("assets/Maps/CGame_L1_BG_Layer.csv",&tempData->mapsData[0].width,&tempData->mapsData[0].height);
    tempData->mapsData[1].data = LoadMapTiles("assets/Maps/CGame_L1_UP_Layer.csv",&tempData->mapsData[1].width,&tempData->mapsData[1].height);
    tempData->tileMap = LoadMapTextures("assets/Tilemap/TiledMapWorld.png",96,48);
    tempData->emptyTexture = LoadTexture("assets/Tilemap/EmptyTexture.png");
    return tempData;
}

int** LoadMapTiles(char* path, int* c, int* r)
{
    ///< Load file CSV[MAP]
    FILE* archivo = fopen(path,"r");
    if (!archivo)
    {
        perror("File error.");
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
    int** mapa = calloc(filas, sizeof(int*));
    for (int i = 0; i < filas; i++) {
        mapa[i] = calloc(columnas, sizeof(int));
    }

    // Fill Matrix
    int f = 0;
    while (fgets(b, sizeof(b), archivo) && f < filas) {
        int c = 0;
        char* token = strtok(b, ",");
        while (token && c < columnas) {
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

void FillTextures(RenderData* renderData)
{
    ///< 
    int countTiles = 0;
    int tilesX = renderData->tileMap->tmImage.width / TILE_SIZE;
    int tilesY = renderData->tileMap->tmImage.height / TILE_SIZE;
    ///< 
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int tileX = x * TILE_SIZE;
            int tileY = y * TILE_SIZE;
            if (!IsTileEmpty(renderData->tileMap->tmImage, tileX, tileY))
            {
                // Extraer tile como subimagen
                Image tile = ImageFromImage(renderData->tileMap->tmImage, (Rectangle){ tileX, tileY, TILE_SIZE, TILE_SIZE });
                renderData->texturesArray[countTiles] = LoadTextureFromImage(tile);
                UnloadImage(tile);
                countTiles++;
            }
        }
    }
    UnloadImage(renderData->tileMap->tmImage);
}
