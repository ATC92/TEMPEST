#include "Engine.h"
//////////////////////////////////////////////////////////
const float FIXED_DT = 1 / 60.0f; ///< Fixed Delta Time for consistent updates
//////////////////////////////////////////////////////////
void InitEngine()
{
    ///< Init audio device
    InitAudioDevice();
    ///< Set exit key
    SetExitKey(0);
    ///< Init Scenes Manager
    InitScenesManager();
    ///< Init GUI
    InitGUI();
    ///< Init Game
    InitGame();
}
//////////////////////////////////////////////////////////
void EngineRender()
{
    ///< Render current Scene/
    RenderCurrentScene(scenes->infScene.type);
    ///< Show information of the game 
    ///< FPS, Position of the player, etc.
    GameInformation();
}
//////////////////////////////////////////////////////////
void EngineUpdate(float dt)
{
    ///< GameUpdateLogic | Movement of Player and MouseWheel
    GameUpdateLogic(dt);
    ///< UpdateGameScene
    GameUpdateScene();
}
//////////////////////////////////////////////////////////
void DeInitEngine()
{
    ///< Audio Close
    CloseAudioDevice();
    ///< Game Close
    DeInitGame();
}
//////////////////////////////////////////////////////////

