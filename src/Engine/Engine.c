#include "Engine.h"

void InitEngine()
{
    ///< Init audio device
    InitAudioDevice();
    ///< Set exit key
    SetExitKey(0);
    ///< Init Scenes Manager
    InitScenes();
    ///< Init GUI
    InitGUI();
    ///< Init Game
    InitGame();
    ///< Init Scenes
}

void GameRender()
{
///////////////////////////////////////////////////////////////
    ///< Show information of the game 
    ///< FPS, Position of the player, etc.
    GameInformation();
///////////////////////////////////////////////////////////////
    ///< Render current Scene/
    RenderCurrentScene(scenes->infScene.type);
///////////////////////////////////////////////////////////////
}

void EngineUpdate()
{
///////////////////////////////////////////////////////////////
    ///< GameUpdateLogic | Movement of Player and MouseWheel
    GameUpdateLogic();
///////////////////////////////////////////////////////////////
    ///< UpdateGameScene
    GameUpdateScene();
}

void DeInitEngine()
{
    ///< Audio Close
    CloseAudioDevice();
    ///< Game Close
    DeInitGame();
}
