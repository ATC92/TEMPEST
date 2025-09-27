#include "Updates.h"
//////////////////////////////////////////////////////////
void RenderCurrentScene(ManagerScenes type)
{
    switch (type)
    {
    case sMAINMENU:
        UpdateMenuScene();
        break;
    case sGAMESTATE:
        UpdateGameRender();
        break;
    case sLOADSCREEN:
        UpdateLoadingScene();
        break;
    case sCONFIGURATIONMENU:
        break;
    case sOPTIONMENU:
        UpdateOptionMenuScene();
        break;
    case sBESTIARY:
        UpdateBestiaryScene();
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

