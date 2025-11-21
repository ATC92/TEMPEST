///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Game.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///!<------- Private declarations
/// @brief Main Camera for the game.
// Camera2D camera = {0};
/// @brief Main map world generator.
static RenderData** mapWorld;
static size_t nEntitys = 2;
/// @brief Textures
static Texture2D Button_E;
//--------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitGameScene(void)
{
    /////////////////////////////////////////////////////////////////////////////////////////
    entityPool = (Entity**)calloc(nEntitys,sizeof(Entity*));
    /////////////////////////////////////////////////////////////////////////////////////////
    Button_E = LoadTexture(ASSETS"/UI/Keys/White/E.png");
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< Gen player.
    eplayer = GenEntity(_PLAYER, "Simon",120);
    ///< Create SpriteAnimation for PlayerEntity.
    eplayer->spriteAnimation = (SpriteAnimation*)calloc(4,sizeof(SpriteAnimation));
    eplayer->spriteAnimation[UP]    = CreateSpriteAnimation(ASSETS "/Entities/_aSimon/BackWalk/SimonUp.png",      0,3,1,0.1f,0.5f,A_LOOP);
    eplayer->spriteAnimation[DOWN]  = CreateSpriteAnimation(ASSETS "/Entities/_aSimon/FrontWalk/SimonDown.png",   0,3,1,0.1f,0.5f,A_LOOP);
    eplayer->spriteAnimation[RIGHT] = CreateSpriteAnimation(ASSETS "/Entities/_aSimon/SideWalk/SimonSideR.png",   0,3,1,0.1f,0.5f,A_LOOP);
    eplayer->spriteAnimation[LEFT]  = CreateSpriteAnimation(ASSETS "/Entities/_aSimon/SideWalk/SimonSideL.png",   0,3,1,0.1f,0.5f,A_LOOP);
    eplayer->isInteraction = false;
    ///< Create NPC for the game.
    LoadNPCtoMemory(entityPool);
    ///< LoadVeyxData for Player
    LoadVeyxList(eplayer);
    /////////////////////////////////////////////////////////////////////////////////////////
    mapWorld = (RenderData**)calloc(1,sizeof(RenderData*));
    // Generate the tilemap (16x16 tiles)
    mapWorld[MP_MINI_TOWN] = LoadInformationMap(ASSETS"/Tilemap//MiniTownTileMap/TileMap.png",
        ASSETS"/Maps/MiniTownMap/MiniTownTiled_Ground.csv",
        ASSETS"/Maps/MiniTownMap/MiniTownTiled_Mid.csv",
        ASSETS"/Maps/MiniTownMap/MiniTownTiled_Top.csv",
        ASSETS"/Maps/MiniTownMap/MiniTownTiled_Deco.csv"
                            ,NULL);
    /////////////////////////////////////////////////////////////////////////////////////////
    camera = InitCamera();
    camera.zoom = 3.f;
    /////////////////////////////////////////////////////////////////////////////////////////
    ///< InitInventary
    eplayer->inventory = InitInventory();
    /////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void UpdateGameRender(void)
{
    BeginMode2D(camera);                    ///< Enter 2D Mode
    {
        ///< Map Render
        // int y = 0;
        // int x = 0;
        // for(size_t i=0;i < 400; i++,x+=16)
        // {
        //     if(i % 28 == 0)
        //     {
        //         x = 0;
        //         y += 16;
        //     }
        //     DrawTexture(mapWorld[MP_MINI_TOWN]->texturesArray[i],x,y,WHITE);
        // }
        RenderTileMap(mapWorld[MP_MINI_TOWN],LAYER_1);
        RenderEntity(entityPool[_NPC_MIKA]);
        RenderEntity(eplayer);
        RenderTileMap(mapWorld[MP_MINI_TOWN],LAYER_2);
        ///< Player Render
        RenderEntity(entityPool[_NPC_ARTURO]);

        RenderTileMap(mapWorld[MP_MINI_TOWN],LAYER_3);
        RenderTileMap(mapWorld[MP_MINI_TOWN],LAYER_4);
        ///< Draw Box PopUp
        if(eplayer->accions[A_POPUP])
        {
            timeShader += GetFrameTime();
            float speed = 0.80f;
            float width = 0.8f;
            float intensity = 0.5f;
            Vector3 color = {1.0f, 1.0f, 1.0f};
            float offset = 0.0f;

            SetShaderValue(shaders[S_SHIELDGLOW], locDirection, &(Vector2){ 1.0f, 0.0f }, SHADER_UNIFORM_VEC2);
            SetShaderValue(shaders[S_SHIELDGLOW], locTime, &timeShader, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaders[S_SHIELDGLOW], locSpeed, &speed, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaders[S_SHIELDGLOW], locWidth, &width, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaders[S_SHIELDGLOW], locIntensity, &intensity, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaders[S_SHIELDGLOW], locColor, &color, SHADER_UNIFORM_VEC3);
            SetShaderValue(shaders[S_SHIELDGLOW], locOffset, &offset, SHADER_UNIFORM_FLOAT);

            CustomScale(0.5f);
            Rectangle target = (Rectangle){.x = entityPool[tNPCSCoop]->triggerBox.x + ((Button_E.width*scale.ScaleUniform)/2), .y = entityPool[tNPCSCoop]->triggerBox.y - Button_E.height * scale.ScaleUniform, .width = Button_E.width * scale.ScaleUniform, .height = Button_E.height * scale.ScaleUniform};
            BeginShaderMode(shaders[S_SHIELDGLOW]);
            DrawTexturePro(Button_E,
                        (Rectangle){.x = 0,.y = 0, .height = Button_E.height, .width = Button_E.width},
                        target,
                        (Vector2){0,0},
                        0, WHITE);
            EndShaderMode();
            CustomScale(1.f);              
        }
        ///< Map Render
        // RenderTileMap(mapWorld[MP_MINI_TOWN],LAYER_2);
        
    #if DEBUG
        DrawRectangleLinesEx(mapWorld[MP_MINI_TOWN]->mapsData[0].size, 1.0f, RED);
    #endif
    }
    EndMode2D();                            ///< Close 2D Mode
    ///< Interacction for scenes
    if(eplayer->accions[A_INTERACTION])
    {
        DrawRectangleRec((Rectangle){.x=(GetScreenWidth() / 2) - 600,.y=GetScreenHeight() - 350,.height=300,.width=1200},RED);
        entityPool[_NPC_MIKA]->prev_position = entityPool[_NPC_MIKA]->position;
        eplayer->position = eplayer->prev_position;
        eplayer->accions[A_INTERACTION] = false;
        IsFightRuning = true;
        IsVeyxPriorityInit = true;
        ChangeMusic();
        ChangeScene(sFIGHTSTATE);
    } 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateGameLogic(float dt)
{
    if(scenes->typeScene == sGAMESTATE)
    {
        /// Movement and Collision
        UpdateMovement(eplayer,dt);
        /// Collision System
        for(size_t i=0; i<nEntitys; i++)
        {
            SystemAABBMid(eplayer,entityPool[i],true,_COLLISION_BOX);
            if(SystemAABBMid(eplayer,entityPool[i],false,_TRIGGER_BOX))
            {
                eplayer->accions[A_POPUP] = true;
                if(IsKeyPressed(KEY_E))
                {
                    eplayer->accions[A_INTERACTION] = true;
                }
                tNPCSCoop = i;
                break;
            }
            else
            {
                eplayer->accions[A_INTERACTION] = false;
                eplayer->isInteraction = false;
                eplayer->accions[A_POPUP] = false;
            }
        }
        /// Collision with Rectangle
        ClampPlayerToMap(eplayer,mapWorld[MP_MINI_TOWN]->mapsData[LAYER_1].size);
        /// Update CollisionBox Movement
        SyncCollisionBox(eplayer);
        SyncCollisionBox(entityPool[_NPC_MIKA]);
        SyncCollisionBox(entityPool[_NPC_ARTURO]);
        ///< WheelUpdates
        UpdateCameraWheel(&camera);
        ///< Smooth factor for camera movement.
        SmoothCameraMovement(&camera,0.25,eplayer->boundingBox);
        ///< Lock camera to a zone
        LockCameraToZone(&camera, mapWorld[MP_MINI_TOWN]->mapsData[LAYER_1].size);
        ///< Save Prev Position of all entites 
        UpdatePrevPosition(eplayer,entityPool,nEntitys);
        ///< Update Animation _NPC
        UpdateAnimation(&eplayer->spriteAnimation[eplayer->eLook],eplayer->isMooving);
        UpdateAnimation(&entityPool[_NPC_MIKA]->spriteAnimation[0],true);
        UpdateAnimation(&entityPool[_NPC_ARTURO]->spriteAnimation[0],true);

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
            ChangeScene(sOPTIONMENU);
            // scenes->typeScene = sOPTIONMENU;                            ///< Change Scene to Option Menu
            // scenes->previousScene = sGAMESTATE;                         ///< Save Previous Scene
        }
        else if(scenes->typeScene == sOPTIONMENU && scenes->previousScene == sGAMESTATE)
        {
            PlaySound(sounds[0]);
            ChangeScene(sGAMESTATE);
            // scenes->typeScene = sGAMESTATE;
            // scenes->previousScene = sOPTIONMENU;
        }
        else if(scenes->typeScene == sOPTIONMENU && scenes->previousScene == sMAINMENU)
        {
            PlaySound(sounds[0]);
            ChangeScene(sMAINMENU);
            // scenes->typeScene = sMAINMENU;
            // scenes->previousScene = sO   PTIONMENU;
        }
        else if(scenes->typeScene == sFIGHTSTATE)
        {
            PlaySound(sounds[0]);
            ChangeScene(sOPTIONMENU);
        }
        else if(scenes->typeScene == sOPTIONMENU && scenes->previousScene == sFIGHTSTATE)
        {
            PlaySound(sounds[0]);
            ChangeScene(sFIGHTSTATE);
            // scenes->typeScene = sFIGHTSTATE;
            // scenes->previousScene = sOPTIONMENU;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameInformation(void)
{
    ///< Rectangle for the information of the camera
#if DEBUG
    DrawInformationCamera(camera, eplayer);
    DrawLinesMidScreen();
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyGameScene(void)
{
    ///< Render Map
    DestroyRenderMap(mapWorld,MP_MINI_TOWN);

    

    ///< Animation Data
    ///< Delete Player Data
    DestroyAnimation(eplayer->spriteAnimation,_PLAYER);
    free(eplayer);
    ///< Pool entities
    DestroyAnimation(entityPool[_NPC_MIKA]->spriteAnimation,_NPC);
    DestroyAnimation(entityPool[_NPC_ARTURO]->spriteAnimation,_NPC);
    free(entityPool[_NPC_MIKA]);
    free(entityPool[_NPC_ARTURO]);
    free(entityPool);

    ///< Textures
    UnloadTexture(Button_E);
}   
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



