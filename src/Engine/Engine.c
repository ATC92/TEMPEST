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
    ///< Render current Scene/
    RenderCurrentScene(scenes->infScene.type);
    ///////////////////////////////////////////////////////////////
    ///< Show information of the game 
    ///< FPS, Position of the player, etc.
    GameInformation();
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
