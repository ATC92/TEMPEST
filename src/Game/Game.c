#include "Game.h"

///< Definition of Global Variables
///< Global Variables
/// @brief Main Camera for the game.
Camera2D camera = {0};
/// @brief Main map world generator.
RenderData* mapWorld;
/// @brief Map enumerator
MapEnum _slct;
/// @brief Main Entity for the player.
Entity* eplayer;

//////////////////////////////////////////////////////////
/**
 * 
 */
void InitGame(void)
{
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Gen player.
    eplayer = GenEntity(_PLAYER, "Hero", 100.f,20.f,1.5f,20.f);
    ///< Player Gen Textures
    eplayer->_tileMap = LoadMapTextures("assets/Tilemap/Tilemap_Entity.png",64,16);
    ///< Fill the HashTable to the Entity Player.
    FillTexturesEntity(eplayer->_textureArray,eplayer->_tileMap);
    /////////////////////////////////////////////////////////////////////////////////////////
    // Generate the tilemap (16x16 tiles)
    mapWorld = LoadInformationMap();
    ///< Fill arrayTexture.
    mapWorld->texturesArray = (Texture2D*)calloc(20,sizeof(Texture2D));
    mapWorld->emptyTexture = LoadTexture("assets/Tilemap/EmptyTexture.png");
    FillTextures(mapWorld);
    ///< Map create with Tiles and Selection of map
    // CreateMapTiles(mapWorld);
    ///< Selection of the map to load First
    _slct = level_1;
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Camera Init 
    camera.target = eplayer->position;
    camera.zoom = 3.0f;
    camera.rotation = 0.0f;
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    /////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////// 
/*
 * 
 */
void GameUpdateRender(void)
{
    BeginMode2D(camera);                    ///< Enter 2D Mode
    {
        ///< Selection of the map to Render
        _slct = level_1;
        ///< Map Render with RayLib Render
        RenderTileMap(mapWorld,_slct);
        ///< Player Render
        RenderPlayer(eplayer);
        ///< Selection of the map to Render
        _slct = level_2;
        ///< Map Render with RayLib Render
        RenderTileMap(mapWorld,_slct);
    }
    EndMode2D();                            ///< Close 2D Mode
}
/**
 * 
 *
 * 
 */
void GameUpdateLogic(void)
{
    if(scenes->infScene.type == GameState)
    {
        ///< WheelUpdates
        UpdateCameraWheel(&camera);
        ///< Update Target
        float smoothFactor = 0.1f;                      ///< Smooth Camera follow (Default: 0.1f, Options: 0.05f o 0.2f)
        camera.target.x += (eplayer->position.x - camera.target.x) * smoothFactor;
        camera.target.y += (eplayer->position.y - camera.target.y) * smoothFactor;
        // Update Movement of Player
        updateMovement(eplayer);
    }
}
/**
 * 
 */
void GameUpdateScene(void)
{
    if(IsKeyDown(KEY_Y))
    {
        PlaySound(button->sound);
        scenes->infScene.type = MainMenu;
    }
    else if (IsKeyDown(KEY_U))
    {
        scenes->infScene.type = GameState;
    }
    else if(IsKeyDown(KEY_I))
    {
        scenes->infScene.type = OptionMenu;
    }
    else if(IsKeyDown(KEY_O))
    {
        scenes->infScene.type = ConfigurationMenu;
    }
}
//////////////////////////////////////////////////////////
/**
 * 
 */
void GameInformation(void)
{
    ///< Rectangle for the information of the camera
    DrawInformationCamera(camera);
}
//////////////////////////////////////////////////////////
/**
 * 
 */
void DeInitGame(void)
{
    free(mapWorld->mapsData);
    free(mapWorld->tileMap);
    free(mapWorld);
    // FreeHashTable(mapWorld->hashTable);
    ///< Delete Player Data
    free(eplayer->_tileMap);
    // FreeHashTable(eplayer->_HT);
}