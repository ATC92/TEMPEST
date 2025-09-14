#include "Engine.h"
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
void InitEngine()
{
    //////////////////////////////////////////////////////////
    ///< FLAGS FOR THE ENGINE
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);    
    
    //////////////////////////////////////////////////////////
    ///< Init Scale
    InitScale();
    ///< Mouse Init
    InitMouse();
    ///< Init Fonts
    InitFont();
    ///< Init Shaders
    InitShaders();
    ///< Set exit key
    SetExitKey(0);
    ///< Init audio device
    InitAudioDevice();
    ///< Init Scenes Manager
    InitScenesManager();
    ///< Init MenuGUI
    InitMenuScene();
    ///< Init Loading Scene
    InitLoadingScene(4);
    ///< Init OptionMenuScene
    InitOptionMenuScene();
    ///< Init BestiaryScene
    InitBestiaryScene(); 
    ///< Init Game
    InitGameScene();
}
//////////////////////////////////////////////////////////
void EngineRender()
{
    ///< MousePosition
    UpdateMousePosition();
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
void DestroyEngine()
{
    ///< Audio Close
    CloseAudioDevice();
    ///< Game Scene Close
    DestroyGameScene();
    ///< Menu Scene Close
    DestroyMenuScene();
    ///< Loading Scene Close
    DestroyLoadingScene();

    ///< Save Comfiguration
    // SaveConfig(gameConfig,"assets/config.txt");
}
//////////////////////////////////////////////////////////

