#include "Engine.h"

///< Global Variables
Camera2D camera = {0};
RenderData* mapWorld;
MapEnum _slct;
Entity eplayer;

void InitGame()
{
    ///< Init audio device
    InitAudioDevice();
    // Generate the tilemap (16x16 tiles)
    mapWorld = GenTileMap();
    if (mapWorld == NULL) {
        printf("\n\nError: Could not generate the map.\n\n");
        return;
    }
    

    ///< Map create with Tiles and Selection of map
    CreateMap_sTile(mapWorld,_slct);
    ///< Selection of the map to load
    _slct = level_1;
    ///< Player
    eplayer = GenEntity(_PLAYER, "Hero", 100.f,20.f,1.5f,20.f);
    eplayer._player.position = (Vector2){0,0};
    ///< Player Gen Textures
    eplayer._tEntity = GenTextureEntity("assets/JSON/Entity.json","PLAYER");
    ///< Camera Init
    camera.target = eplayer._player.position;
    camera.zoom = 3.0f;
    camera.rotation = 0.0f;
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
}

void GameRender()
{
    //////////////////////////////////////////////////////////
    BeginMode2D(camera);                    ///< Enter 2D Mode
        ///< Map Render with RayLib Render
        RenderTileMap(mapWorld,_slct);
        ///< Player Render
        RenderPlayer(eplayer,camera);
    EndMode2D();                            ///< Close 2D Mode
    ///< Rectangle for the information of the camera
    DrawInformationCamera(camera);
}

void GameUpdate()
{
    ///< WheelUpdates
    UpdateCameraWheel(&camera);
    ///< Update Target
    float smoothFactor = 0.1f;                      ///< Smooth Camera follow (Default: 0.1f, Options: 0.05f o 0.2f)
    camera.target.x += (eplayer._player.position.x - camera.target.x) * smoothFactor;
    camera.target.y += (eplayer._player.position.y - camera.target.y) * smoothFactor;
    // Update Movement of Player
    updateMovement(&eplayer);
}

void DeInitGame()
{
    ///< Audio Close
    CloseAudioDevice();
    ///< Delete Map data
    cJSON_Delete(mapWorld->sTilesData->parseTileGen);
    cJSON_Delete(mapWorld->mapRoot);
    free(mapWorld->sTilesData);
    free(mapWorld->mapsData);
    free(mapWorld);
    ///< Delete Player Data

}
