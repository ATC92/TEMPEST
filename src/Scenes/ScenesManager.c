#include "ScenesManager.h"
<<<<<<< HEAD
//////////////////////////////////////////////////////////
Scene* scenes;
//////////////////////////////////////////////////////////
void InitScenesManager(void)
{
    ///< Create Scenes Manager Memory
    scenes = CreateScene("Scenes Manager",MainMenu);
}
//////////////////////////////////////////////////////////
Scene* CreateScene(char* name, ManagerScenes type)
{
    Scene* sc = (Scene*)calloc(1,sizeof(Scene));
    sc->infScene.type = type;
    sc->ActivedScenes = (bool*)calloc(5, sizeof(bool)); // Initialize all scenes as inactive
    return sc;
}
//////////////////////////////////////////////////////////
=======

Scene* scenes;

void InitScenes(void)
{
    ///< Create Scenes Manager Memory
    scenes = CreateScene("MainMenu",
                        "Menu GUI of the game",
                        "Only 1 button (Texture2D)",
                        MainMenu);
}

Scene* CreateScene(char* name, char* inf, char* LOG, ManagerScenes type)
{
    Scene* sc = (Scene*)calloc(1,sizeof(Scene));
    sc->infScene.Name = strdup(name);
    sc->infScene.information = strdup(inf);
    sc->infScene.LOG = strdup(LOG);
    sc->infScene.type = type;
    return sc;
}

>>>>>>> origin/main
void ChangeScene(ManagerScenes next)
{
    scenes->infScene.type = next;
}
<<<<<<< HEAD
//////////////////////////////////////////////////////////
=======

>>>>>>> origin/main
InformationScene GetCurrentScene(Scene _ms)
{
    return _ms.infScene;
}
<<<<<<< HEAD
//////////////////////////////////////////////////////////


=======
>>>>>>> origin/main
