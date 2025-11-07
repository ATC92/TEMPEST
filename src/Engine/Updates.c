#include "Updates.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    case sFIGHTSTATE:
        UpdateLogicFight();
        UpdateRenderFight();
        break;
    default:
        TraceLog(LOG_ERROR, "Error, Scene not in Range [%d]",type);
        break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

