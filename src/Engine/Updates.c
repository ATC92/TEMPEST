#include "Updates.h"
//////////////////////////////////////////////////////////
void RenderCurrentScene(ManagerScenes type)
{
    switch (type)
    {
    case MainMenu:
        MainMenuGUI();
        break;
    case GameState:
        GameUpdateRender();
        break;
<<<<<<< HEAD
    case LoadingScreen:
        SimulateLoading(3);
        scenes->infScene.type = GameState;
        break;
    case OptionMenu:
=======
    case OptionMenu:
        //OptiomMenuRender();
        break;
    case ConfigurationMenu:
>>>>>>> origin/main
        break;
    default:
        perror("Error with Render Current Scene.");
        break;
    }
}
//////////////////////////////////////////////////////////

<<<<<<< HEAD
=======

>>>>>>> origin/main
