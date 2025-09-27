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
void InitGameScene(void)
{
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Gen player.
    eplayer = GenEntity(_PLAYER, "Hero", 100.f,20.f,90.f,0.f);
    ///< Player Gen Textures
    // eplayer->_tileMap = LoadMapTextures("assets/Tilemap/Tilemap_Entity.png",64,16);
    ///< Fill arrayTextures of the Entity Player.
    // eplayer->sizeArrayTextures = FillTexturesEntity(eplayer->_textureArray,eplayer->_tileMap);
    eplayer->spriteAnimation = (SpriteAnimation*)calloc(4,sizeof(SpriteAnimation));
    eplayer->spriteAnimation[0] = CreateSpriteAnimation("assets/Entities/_aSimon/BackWalk/SimonUp.png",      0,4,0.1f,0.1f);
    eplayer->spriteAnimation[1] = CreateSpriteAnimation("assets/Entities/_aSimon/FrontWalk/SimonDown.png",   0,4,0.1f,0.1f);
    eplayer->spriteAnimation[2] = CreateSpriteAnimation("assets/Entities/_aSimon/SideWalk/SimonSideR.png",   0,3,0.1f,0.1f);
    eplayer->spriteAnimation[3] = CreateSpriteAnimation("assets/Entities/_aSimon/SideWalk/SimonSideL.png",   0,3,0.1f,0.1f);

    ///< Set initial position of the player
    ///< Enemy
    eEnemy = GenEntity(_ENEMY, "Enemy", 100.f,20.f,1.5f,20.f);
    ///< Enemy Gen Textures
    eEnemy->_tileMap = LoadMapTextures("assets/Tilemap/Tilemap_Entity.png",64,16);
    ///< Fill arrayTextures of the Entity Enemy.
    eEnemy->sizeArrayTextures = FillTexturesEntity(eEnemy->_textureArray,eEnemy->_tileMap);

    /////////////////////////////////////////////////////////////////////////////////////////
    // Generate the tilemap (16x16 tiles)
    mapWorld = LoadInformationMap();
    ///< Fill arrayTexture.
    mapWorld->texturesArray = (Texture2D*)calloc(20,sizeof(Texture2D));
    mapWorld->emptyTexture = LoadTexture("assets/Tilemap/EmptyTexture.png");
    mapWorld->sizeArrayTextures = FillTextures(mapWorld);
    ///< Selection of the map to load First
    _slct = level_1;
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Camera Init 
    camera.target = eplayer->position;
    camera.zoom = 4.0f;
    camera.rotation = 0.0f;
    camera.offset = (Vector2){ (float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f };
    /////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////// 
void UpdateGameRender(void)
{
    BeginMode2D(camera);                    ///< Enter 2D Mode
    {
        ///< Selection of the map to Render
        _slct = level_1;
        ///< Map Render
        RenderTileMap(mapWorld,_slct);
        DrawRectangleLinesEx(mapWorld->mapsData[0].size, 2.0f, RED);
        ///< Player Render
        RenderPlayer(eplayer);
        // RenderPlayer(eEnemy);
        ///< Selection of the map to Render
        _slct = level_2;
        ///< Map Render
        RenderTileMap(mapWorld,_slct);
    }
    EndMode2D();                            ///< Close 2D Mode
}
//////////////////////////////////////////////////////////
void UpdateGameLogic(float dt)
{
    switch (scenes->typeScene)
    {
        ///< Game State
        case sGAMESTATE:
            
            /// Movement and Collision
            UpdateMovement(eplayer,dt);
            

            /// Collision System
            SystemAABBMid(eplayer,eEnemy,true);

            /// Collision with Rectangle
            ClampPlayerToMap(eplayer,mapWorld->mapsData[0].size);
            
            /// Update CollisionBox Movement
            SyncCollisionBox(eEnemy);
            SyncCollisionBox(eplayer);

            ///< WheelUpdates
            float smoothFactor = 0.1f;                      ///< Smooth Camera follow (Default: 0.1f, Options: 0.05f o 0.2f)
            UpdateCameraWheel(&camera);
            camera.target.x += (eplayer->position.x - camera.target.x) * smoothFactor;
            camera.target.y += (eplayer->position.y - camera.target.y) * smoothFactor;

            ///< Lock camera to a zone
            LockCameraToZone(&camera, mapWorld->mapsData[0].size);

            ///< Save Prev Position of the player
            eplayer->prev_position = eplayer->position;
            break;  
        default:
            break;
    }
}
//////////////////////////////////////////////////////////
void UpdateGameScene(void)
{
    ///< Check if the player pressed the Escape key
    ///< To open or close the Option Menu
    if(IsKeyPressed(KEY_ESCAPE) && scenes->typeScene != sMAINMENU)
    {
        if(scenes->previousScene != sOPTIONMENU)
        {
            PlaySound(sounds[0]);                                   ///< Play Sound when is pressed
            scenes->typeScene = sOPTIONMENU;                  ///< Change Scene to Option Menu
            scenes->previousScene = sGAMESTATE;                      ///< Save Previous Scene
            // WaitTime(0.1);
        }
        else
        {
            PlaySound(sounds[0]);                                   ///< Play Sound when is pressed
            scenes->typeScene = sGAMESTATE;                          ///< Change Scene to Game State
            scenes->previousScene = sOPTIONMENU;              ///< Save Previous Scene
        }
    }
}
//////////////////////////////////////////////////////////
void GameInformation(void)
{
    ///< Rectangle for the information of the camera
    #if DEBUG
    DrawInformationCamera(camera);
    DrawLinesMidScreen();
    #endif
}
//////////////////////////////////////////////////////////
void DestroyGameScene(void)
{
    for (int i=0; i < 20; i++)
        UnloadTexture(mapWorld->texturesArray[i]);
        
    UnloadTexture(mapWorld->emptyTexture);
    free(mapWorld->mapsData);
    free(mapWorld->tileMap);
    free(mapWorld);

    ///< Delete Player Data
    free(eplayer->_tileMap);
    for(int i=0; i<eplayer->sizeArrayTextures; i++)
        UnloadTexture(eplayer->_textureArray[i]);
    free(eplayer->_textureArray);
    free(eplayer);
    ///< Delete Enemy None Data
    free(eEnemy->_tileMap);
    for(int i=0; i<eEnemy->sizeArrayTextures; i++)
        UnloadTexture(eEnemy->_textureArray[i]);
    free(eEnemy->_textureArray);
    free(eEnemy);


}   
//////////////////////////////////////////////////////////



