#include "Engine.h"
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void InitEngine()
{
    //////////////////////////////////////////////////////////
    ///< FLAGS FOR THE ENGINE
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    
    
    //////////////////////////////////////////////////////////
    ///< Init audio device
    InitAudioDevice();
    ///< Set exit key
    SetExitKey(0);
    ///< Init Scenes Manager
    InitScenesManager();
    ///< Init MenuGUI
    InitMenuScene();
    ///< Init Loading Scene
    InitLoadingScene(4);
    ///< OptionMenuScene
    InitOptionMenuScene();
    ///< Init Game
    InitGameScene();
}
//////////////////////////////////////////////////////////
void EngineRender()
{
    ///< Render current Scene/
    RenderCurrentScene(scenes->typeScene);
    ///< Show information of the game 
    ///< FPS, Position of the player, etc.
    GameInformation();
}
//////////////////////////////////////////////////////////
void EngineUpdate(float dt)
{
    ///< Update EngineFlags
    UpdateEngineFlags();
    ///< GameUpdateLogic | Movement of Player and MouseWheel
    UpdateGameLogic(dt);
    ///< UpdateGameScene
    UpdateGameScene();
}
//////////////////////////////////////////////////////////
void DeInitEngine()
{
    ///< Audio Close
    CloseAudioDevice();
    ///< Game Scene Close
    DestroyGameScene();
    ///< Menu Scene Close
    DestroyMenuScene();
    ///< Loading Scene Close
    DestroyLoadingScene();
}
//////////////////////////////////////////////////////////

