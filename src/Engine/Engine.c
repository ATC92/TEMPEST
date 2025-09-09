#include "Engine.h"
//////////////////////////////////////////////////////////
<<<<<<< HEAD
const float FIXED_DT = 1 / 60.0f; ///< Fixed Delta Time for consistent updates
//////////////////////////////////////////////////////////
=======
>>>>>>> origin/main
void InitEngine()
{
    ///< Init audio device
    InitAudioDevice();
    ///< Set exit key
    SetExitKey(0);
    ///< Init Scenes Manager
<<<<<<< HEAD
    InitScenesManager();
=======
    InitScenes();
>>>>>>> origin/main
    ///< Init GUI
    InitGUI();
    ///< Init Game
    InitGame();
<<<<<<< HEAD
}
//////////////////////////////////////////////////////////
void EngineRender()
=======
    ///< Init Scenes
}
//////////////////////////////////////////////////////////
void GameRender()
>>>>>>> origin/main
{
    ///< Render current Scene/
    RenderCurrentScene(scenes->infScene.type);
    ///< Show information of the game 
    ///< FPS, Position of the player, etc.
    GameInformation();
}
//////////////////////////////////////////////////////////
<<<<<<< HEAD
void EngineUpdate(float dt)
{
    ///< GameUpdateLogic | Movement of Player and MouseWheel
    GameUpdateLogic(dt);
=======
void EngineUpdate()
{
    ///< GameUpdateLogic | Movement of Player and MouseWheel
    GameUpdateLogic();
>>>>>>> origin/main
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

