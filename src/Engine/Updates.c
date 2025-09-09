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
    case LoadingScreen:
        SimulateLoading(3);
        scenes->infScene.type = GameState;
        break;
    case OptionMenu:
        break;
    default:
        perror("Error with Render Current Scene.");
        break;
    }
}
//////////////////////////////////////////////////////////

