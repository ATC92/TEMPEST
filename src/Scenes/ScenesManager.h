#pragma once
///< C/C++ Lib
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
///< CGame Lib
#include "../Textures/Textures.h"
#include "../Utils/Information.h"
#include "Scenes.h"
//////////////////////////////////////////////////////////////////
/**
 * 
 */
typedef enum _scn
{
    MainMenu,
    GameState,
    OptionMenu,
    ConfigurationMenu,
    LoadScreen
}ManagerScenes;
typedef struct _inf
{
    char* Name;
    char* information;
    char* LOG;
    ManagerScenes type;
}InformationScene;
/**
 * 
 */
typedef struct _scene
{
    InformationScene infScene;
    ///< Texturas o GUI
    ///< Size of the Scene
}Scene;
//////////////////////////////////////////////////////////////////
/// @brief Global Scenes Manager
extern Scene* scenes;

//////////////////////////////////////////////////////////////////
void InitScenes(void);
Scene* CreateScene(char*,char*,char*,ManagerScenes);
void ChangeScene();
InformationScene GetCurrentScene(Scene);





