#include "Map.h"
//////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////
int** LoadMapTiles(char* path, int* c, int* r)
{
    ///< Load file CSV[MAP]
    FILE* archivo = fopen(path,"r");
    if (!archivo)
    {
        printf("%s | ",path);
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
//////////////////////////////////////////////////////////////////


