///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Game.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///!<------- Private declarations
/// @brief Main Camera for the game.
static Camera2D camera = {0};
/// @brief Main map world generator.
static RenderData* mapWorld;
/// @brief Map enumerator
static MapEnum _slct;
//--------------------------------------------------------
///!<------- Public declarations
/// Main Entity for the player.
Entity* eplayer;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitGameScene(void)
{
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Gen player.
    eplayer = GenEntity(_PLAYER, "Hero",90);
    ///< Create SpriteAnimation for PlayerEntity.
    eplayer->spriteAnimation = (SpriteAnimation*)calloc(4,sizeof(SpriteAnimation));
    eplayer->spriteAnimation[UP]    = CreateSpriteAnimation("assets/Entities/_aSimon/BackWalk/SimonUp.png",      0,4,0.1f,0.1f,A_LOOP);
    eplayer->spriteAnimation[DOWN]  = CreateSpriteAnimation("assets/Entities/_aSimon/FrontWalk/SimonDown.png",   0,4,0.1f,0.1f,A_LOOP);
    eplayer->spriteAnimation[RIGHT] = CreateSpriteAnimation("assets/Entities/_aSimon/SideWalk/SimonSideR.png",   0,3,0.1f,0.1f,A_LOOP);
    eplayer->spriteAnimation[LEFT]  = CreateSpriteAnimation("assets/Entities/_aSimon/SideWalk/SimonSideL.png",   0,3,0.1f,0.1f,A_LOOP);
    /////////////////////////////////////////////////////////////////////////////////////////
    // Generate the tilemap (16x16 tiles)
    mapWorld = LoadInformationMap();
    ///< Fill arrayTexture.
    mapWorld->texturesArray = (Texture2D*)calloc(20,sizeof(Texture2D));
    // mapWorld->emptyTexture = LoadTexture("assets/Tilemap/EmptyTexture.png");
    mapWorld->sizeArrayTextures = FillTextures(mapWorld);
    ///< Selection of the map to load First
    _slct = level_1;
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Camera Init 
    camera.target = (Vector2){ eplayer->sizeRect.x + eplayer->sizeRect.width/2, eplayer->sizeRect.y + eplayer->sizeRect.height/2 };
    camera.zoom = 4.0f;
    camera.rotation = 0.0f;
    camera.offset = (Vector2){ (float)GetScreenWidth()/2.0f, (float)GetScreenHeight()/2.0f };
    /////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void UpdateGameRender(void)
{
    BeginMode2D(camera);                    ///< Enter 2D Mode
    {
        ///< Selection of the map to Render
        _slct = level_1;
        ///< Map Render
        RenderTileMap(mapWorld,_slct);
        
        ///< Player Render
        RenderPlayer(eplayer);
        // RenderPlayer(eEnemy);
        ///< Selection of the map to Render
        _slct = level_2;
        ///< Map Render
        RenderTileMap(mapWorld,_slct);

#if DEBUG
    DrawRectangleLinesEx(mapWorld->mapsData[0].size, 2.0f, RED);
#endif

    }
    EndMode2D();                            ///< Close 2D Mode
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateGameLogic(float dt)
{
    if(scenes->typeScene == sGAMESTATE)
    {
        /// Movement and Collision
        UpdateMovement(eplayer,dt);
        /// Collision System
        // SystemAABBMid(eplayer,eEnemy,true);
        /// Collision with Rectangle
        ClampPlayerToMap(eplayer,mapWorld->mapsData[0].size);
        /// Update CollisionBox Movement
        // SyncCollisionBox(eEnemy);
        SyncCollisionBox(eplayer);
        ///< WheelUpdates
        UpdateCameraWheel(&camera);

        ///!<--------- Smooth Camera follow
        ///< If you want a more rigid camera, increase the < smoothFactor > value.
        ///< If you want a more fluid camera, decrease the < smoothFactor > value.
        float smoothFactor = 0.15f;                      ///< Smooth Camera follow (Default: 0.1f, Options: 0.05f o 0.2f)
        camera.target.x += (eplayer->sizeRect.x + eplayer->sizeRect.width/2 - camera.target.x) * smoothFactor;
        camera.target.y += (eplayer->sizeRect.y + eplayer->sizeRect.height/2 - camera.target.y) * smoothFactor;
        ///< Lock camera to a zone
        LockCameraToZone(&camera, mapWorld->mapsData[0].size);
        ///< Save Prev Position of the player
        eplayer->prev_position = eplayer->position;
    }   
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateGameScene(void)
{
    ///< Check if the player pressed the Escape key
    if(IsKeyPressed(KEY_ESCAPE) && scenes->typeScene != sMAINMENU && scenes->typeScene != sLOADSCREEN)
    {
        if(scenes->typeScene == sGAMESTATE)
        {
            PlaySound(sounds[0]);                                       ///< Play Sound when is pressed
            scenes->typeScene = sOPTIONMENU;                            ///< Change Scene to Option Menu
            scenes->previousScene = sGAMESTATE;                         ///< Save Previous Scene
        }
        else if(scenes->typeScene == sOPTIONMENU && scenes->previousScene != sMAINMENU)
        {
            PlaySound(sounds[0]);
            scenes->typeScene = sGAMESTATE;
            scenes->previousScene = sOPTIONMENU;
        }
        else if(scenes->typeScene == sOPTIONMENU && scenes->previousScene == sMAINMENU)
        {
            PlaySound(sounds[0]);
            scenes->typeScene = sMAINMENU;
            scenes->previousScene = sOPTIONMENU;
        }
        else if(scenes->typeScene == sBESTIARY && scenes->previousScene == sMAINMENU)
        {
            PlaySound(sounds[0]);
            scenes->typeScene = sMAINMENU;
            scenes->previousScene = sBESTIARY;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInformation(void)
{
    ///< Rectangle for the information of the camera
    #if DEBUG
    DrawInformationCamera(camera);
    DrawLinesMidScreen();
    #endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyGameScene(void)
{
    for (int i=0; i < 20; i++)
    {
        if(IsTextureValid(mapWorld->texturesArray[i]))
        {
            UnloadTexture(mapWorld->texturesArray[i]);
            mapWorld->texturesArray[i] = (Texture2D){0};
        }
    }
    free(mapWorld->texturesArray);
    UnloadTexture(mapWorld->emptyTexture);
    free(mapWorld->mapsData);
    free(mapWorld);

    ///< Delete Player Data
    for (size_t i = 0; i < 4; i++)
    {
        UnloadTexture(eplayer->spriteAnimation[i].spriteSheet);
    }
    free(eplayer->spriteAnimation);
    free(eplayer);
    // free(eplayer->name);
}   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



