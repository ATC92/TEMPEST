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
    case OptionMenu:
        //OptiomMenuRender();
        break;
    case ConfigurationMenu:
        break;
    default:
        perror("Error with Render Current Scene.");
        break;
    }
}
//////////////////////////////////////////////////////////


