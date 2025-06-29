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
/// @brief Enemy Entity
Entity* eEnemy;
//////////////////////////////////////////////////////////
void InitGame(void)
{
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Gen player.
    eplayer = GenEntity(_PLAYER, "Hero", 100.f,20.f,1.5f,20.f);
    ///< Player Gen Textures
    eplayer->_tileMap = LoadMapTextures("assets/Tilemap/Tilemap_Entity.png",64,16);
    ///< Fill arrayTextures of the Entity Player.
    FillTexturesEntity(eplayer->_textureArray,eplayer->_tileMap);

    ///< Enemy
    eEnemy = GenEntity(_ENEMY, "Enemy", 100.f,20.f,1.5f,20.f);
    ///< Enemy Gen Textures
    eEnemy->_tileMap = LoadMapTextures("assets/Tilemap/Tilemap_Entity.png",64,16);
    ///< Fill arrayTextures of the Entity Enemy.
    FillTexturesEntity(eEnemy->_textureArray,eEnemy->_tileMap);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Generate the tilemap (16x16 tiles)
    mapWorld = LoadInformationMap();
    ///< Fill arrayTexture.
    mapWorld->texturesArray = (Texture2D*)calloc(20,sizeof(Texture2D));
    mapWorld->emptyTexture = LoadTexture("assets/Tilemap/EmptyTexture.png");
    FillTextures(mapWorld);
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
void GameUpdateRender(void)
{
    BeginMode2D(camera);                    ///< Enter 2D Mode
    {
        ///< Selection of the map to Render
        _slct = level_1;
        ///< Map Render
        RenderTileMap(mapWorld,_slct);
        ///< Player Render
        RenderPlayer(eplayer);
        RenderPlayer(eEnemy);
        ///< Selection of the map to Render
        _slct = level_2;
        ///< Map Render
        RenderTileMap(mapWorld,_slct);
    }
    EndMode2D();                            ///< Close 2D Mode
}
//////////////////////////////////////////////////////////
void GameUpdateLogic(void)
{
    switch (scenes->infScene.type)
    {
        case GameState:
                ///< Preview Position
            eplayer->prev_position = eplayer->position;
            
            /// Collision Detection
            UpdateCollision(eplayer, eEnemy);
            
            // Update Movement of Player
            updateMovement(eplayer);

            /// Update CollisionBox Movement
            UpdateCollisionMovement(eplayer);
            UpdateCollisionMovement(eEnemy);

            ///< WheelUpdates
            float smoothFactor = 0.1f;                      ///< Smooth Camera follow (Default: 0.1f, Options: 0.05f o 0.2f)
            UpdateCameraWheel(&camera);
            camera.target.x += (eplayer->position.x - camera.target.x) * smoothFactor;
            camera.target.y += (eplayer->position.y - camera.target.y) * smoothFactor;
            break;            
        default:
            break;
    }
}
//////////////////////////////////////////////////////////
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
    else if(IsKeyDown(KEY_ESCAPE))
    {
        scenes->infScene.type = OptionMenu;
    }
    else if(IsKeyDown(KEY_O))
    {
        scenes->infScene.type = ConfigurationMenu;
    }
}
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void GameInformation(void)
{
    ///< Rectangle for the information of the camera
    DrawInformationCamera(camera);
}
//////////////////////////////////////////////////////////
void DeInitGame(void)
{
    for (int i=0; i < 20; i++)
        UnloadTexture(mapWorld->texturesArray[i]);
        
    free(mapWorld->mapsData);
    free(mapWorld->tileMap);
    free(mapWorld);

    ///< Delete Player Data
    free(eplayer->_tileMap);
}
//////////////////////////////////////////////////////////



