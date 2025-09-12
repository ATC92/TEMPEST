#include "Updates.h"
//////////////////////////////////////////////////////////
void RenderCurrentScene(ManagerScenes type)
{
    switch (type)
    {
    case MainMenu:
        UpdateMenuScene();
        break;
    case GameState:
        UpdateGameRender();
        break;
    case LoadingScreen:
        UpdateLoadingScene();
        scenes->typeScene = GameState;
        break;
    case ConfigurationMenu:
        break;
    case OptionMenu:
        UpdateOptionMenuScene();
        break;
    default:
        perror("Error with Render Current Scene.");
        break;
    }
}
void UpdateEngineFlags(void)
{
}
//////////////////////////////////////////////////////////

