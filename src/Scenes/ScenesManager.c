#include "ScenesManager.h"
//////////////////////////////////////////////////////////
Scene* scenes;
//////////////////////////////////////////////////////////
void InitScenesManager(void)
{
    ///< Create Scenes Manager Memory
    scenes = CreateScene(MainMenu);
}
//////////////////////////////////////////////////////////
Scene* CreateScene(ManagerScenes type)
{
    Scene* sc = (Scene*)calloc(1,sizeof(Scene));
    sc->infScene.type = type;
    sc->ActivedScenes = (bool*)calloc(5, sizeof(bool)); // Initialize all scenes as inactive
    return sc;
}
//////////////////////////////////////////////////////////
void ChangeScene(ManagerScenes next)
{
    scenes->infScene.type = next;
}
//////////////////////////////////////////////////////////
InformationScene GetCurrentScene(Scene current)
{
    return current.infScene;
}
//////////////////////////////////////////////////////////


