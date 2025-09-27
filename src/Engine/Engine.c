//////////////////////////////////////////////////////////
#include "Engine.h"
//////////////////////////////////////////////////////////
void InitEngine()
{
    //////////////////////////////////////////////////////////
    ///< FLAGS FOR THE ENGINE
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);        
    ///< Set exit key
    SetExitKey(0);
    ///<    Init audio device <RayLib Context>
    InitAudioDevice();
    //////////////////////////////////////////////////////////
    ///!<---------- Init Components ---------->
    ///< Init Scale
    InitScale();
    ///< Mouse Init
    InitMouse();
    ///< Init Fonts
    InitFont();
    ///< Init Shaders
    InitShaders();
    ///< Init Sounds && Music
    InitSounds();
    InitMusic();
    //////////////////////////////////////////////////////////
    ///!<---------- Init Scenes ---------->
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
    ///< Frame to Animation
    UpdateAnimation(&eplayer->spriteAnimation[eplayer->_eLook],eplayer->isMooving);
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
    ///< 
    UpdateMusicScene(scenes->typeScene);
}
//////////////////////////////////////////////////////////
void DestroyEngine()
{
    ///!<---------- Free Memory and Close Scenes ---------->
    ///< Game Scene Close
    DestroyGameScene();
    ///< Menu Scene Close
    DestroyMenuScene();
    ///< Loading Scene Close
    DestroyLoadingScene();
    ///< OptionMenuScene Close
    DestroyOptionMenuScene();
    ///< BestiaryScene Close
    DestroyBestiaryScene();
    ///!<---------- Free Memory and Close Components ---------->    
    ///< Free Fonts
    DestroyFont();
    ///< Free Shaders
    DestroyShaders();
    ///< Destroy Audio && Music
    DestroySounds();
    DestroyMusic();
    ///<    Audio Close <RayLib Context>
    CloseAudioDevice();

    ///< Save Comfiguration
    SaveConfig(gameConfig,"assets/config.txt");
}
//////////////////////////////////////////////////////////

