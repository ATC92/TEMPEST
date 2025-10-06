//////////////////////////////////////////////////////////
#include "Shaders.h"
//////////////////////////////////////////////////////////
///< Public declaration
Shader* shaders;
static size_t totalShaders;
//////////////////////////////////////////////////////////
void InitShaders(void)
{
    totalShaders = 4;
    shaders = (Shader*)calloc(totalShaders,sizeof(Shader));
    ///< Load Shaders
    Shader invert = LoadShader(NULL, "src/Shaders/invert.fs");
    Shader outline = LoadShader(NULL,"src/Shaders/outline.fs");
    Shader blur = LoadShader("src/Shaders/blur.vs","src/Shaders/glassblur.fs");
    Shader shieldGLow = LoadShader("src/Shaders/shieldGLow.vs","src/Shaders/shield_glow.fs");
    
    if (!IsShaderValid(invert)) 
        TraceLog(LOG_ERROR, "Shader Invalid: [%d]",invert.id);
    else
        shaders[S_INVERT] = invert;
    if(!IsShaderValid(outline))
        TraceLog(LOG_ERROR, "Shader Invalid: [%d]",outline.id);
    else
        shaders[S_OUTLINE] = outline;
    if(!IsShaderValid(blur))
        TraceLog(LOG_ERROR,"Shader Invalid: [%d]",blur.id);
    else
        shaders[S_BLUR] = blur;
    if(!IsShaderValid(shieldGLow))
        TraceLog(LOG_ERROR,"Shader Invalid [%d]",shieldGLow.id);
    else
        shaders[S_SHIELDGLOW] = shieldGLow;  
}
void DestroyShaders(void)
{
    for(size_t i = 0; i < totalShaders; i++)
    {
        if (IsShaderValid(shaders[i]))
            UnloadShader(shaders[i]);
    }
    free(shaders);
}
//////////////////////////////////////////////////////////