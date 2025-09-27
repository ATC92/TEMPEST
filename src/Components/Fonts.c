//////////////////////////////////////////////////////////
#include "Fonts.h"
//////////////////////////////////////////////////////////
///< Public Declarations
Font* fontType = NULL;
//////////////////////////////////////////////////////////
void InitFont(void)
{
    fontType = (Font*)calloc(1,sizeof(Font));
    *fontType = LoadFontEx("assets/Font/04B.ttf",20,NULL,0);
    if(!IsFontValid(*fontType))
        TraceLog(LOG_ERROR, "Font not valid %s", "assets/Font/04B.ttf");
}
void DestroyFont(void)
{
    UnloadFont(*fontType);
    free(fontType);
}
//////////////////////////////////////////////////////////