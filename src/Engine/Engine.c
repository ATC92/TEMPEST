///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Engine.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    ///< Dice Animations && carts
    InitSpriteAnimationDice();
    ///< Init Veyx Array Registry
    InitVeyxRegistry();
    LoadVeyxData("assets/VeyxData/Veyx.data");
    //////////////////////////////////////////////////////////
    ///!<---------- Init Scenes ---------->
    ///< Init Scenes Manager
    InitScenesManager();
    ///< Init MenuGUI
    InitMenuScene();
    ///< Init Loading Scene
    InitLoadingScene(2);
    ///< Init OptionMenuScene
    InitOptionMenuScene();
    ///< Init BestiaryScene
    InitBestiaryScene();
    ///< Init FightScene
    InitFightScene();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EngineRender()
{
    if(scenes->typeScene == sGAMESTATE)
    {
        ///< Frame to Animation
        UpdateAnimation(&eplayer->spriteAnimation[eplayer->eLook],eplayer->isMooving);
    }
    else if(scenes->typeScene == sBESTIARY)
    {
        UpdateAnimation(&scrollVeyx,true);
    }
    ///< Render current Scene/
    RenderCurrentScene(scenes->typeScene);
    ///< 
    UpdateMousePosition();
    ///< Show information of the game < FPS, Position of the player, etc >
    GameInformation();
#if DEBUG
    DrawRectangleLines((int)mouse.x,(int)mouse.y,(int)(cursor.width * 3),(int)(cursor.height * 3),RED);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EngineUpdate(float dt)
{   
    ///< GameUpdateLogic | Movement of Player and MouseWheel
    UpdateGameLogic(dt);
    ///< UpduateGameScene
    UpdateGameScene();
    ///< 
    UpdateMusicScene(scenes->typeScene);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DestroyEngine()
{
    ///!<---------- Free Memory and Close Scenes ---------->
    ///< Game Scene Close
    if(IsGameInit)
        DestroyGameScene();
    ///< Menu Scene Close
    DestroyMenuScene();
    ///< Loading Scene Close
    DestroyLoadingScene();
    ///< OptionMenuScene Close
    DestroyOptionMenuScene();
    ///< BestiaryScene Close
    DestroyBestiaryScene();
    ///< Destroy ScenesManager
    DestroyScenes();
    ///!<---------- Free Memory and Close Components ---------->    
    ///< Free Fonts
    DestroyFont();
    ///< Free Shaders
    DestroyShaders();
    //< Destroy Mouse
    DestroyMouse();
    ///< Destroy Audio && Music
    DestroySounds();
    DestroyMusic();
    ///<    Audio Close <RayLib Context>
    CloseAudioDevice();

    ///< Save Comfiguration
    SaveConfig(gameConfig,"assets/config.txt");

    ///< TraceLog Game Exit Success
    TraceLog(LOG_INFO,"Game Done, All destroy and All save");

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

