//////////////////////////////////////////////////////////
#include "Shaders.h"
//////////////////////////////////////////////////////////
///< Public declaration
Shader* shaders;
static size_t totalShaders;


///< Shield Shader 
///< Shaders
int locDirection;
int locTime;
int locSpeed; 
int locWidth;
int locIntensity; 
int locColor;
int locOffset; 
float timeShader;
//////////////////////////////////////////////////////////
void InitShaders(void)
{
    totalShaders = 5;
    shaders = (Shader*)calloc(totalShaders,sizeof(Shader));
    ///< Load Shaders
    Shader invert = LoadShader(NULL, "src/Shaders/invert.fs");
    Shader outline = LoadShader(NULL,"src/Shaders/outline.fs");
    Shader blur = LoadShader("src/Shaders/blur.vs","src/Shaders/glassblur.fs");
    Shader shieldGlow = LoadShader("src/Shaders/shieldGLow.vs","src/Shaders/shield_glow.fs");
    Shader grayScale = LoadShader("src/Shaders/grayscale.vs","src/Shaders/grayscale.fs");
    
    if (!IsShaderValid(invert)) 
        AssertNotNull(&invert,"Shader error in load.","invert");
    else
        shaders[S_INVERT] = invert;
    if(!IsShaderValid(outline))
        AssertNotNull(&outline,"Shader error in load.","outline");
    else
        shaders[S_OUTLINE] = outline;
    if(!IsShaderValid(blur))
        AssertNotNull(&blur,"Shader error in load.","blur");
    else
        shaders[S_BLUR] = blur;
    if(!IsShaderValid(shieldGlow))
        AssertNotNull(&shieldGlow,"Shader error in load.","shieldGlow");
    else
        shaders[S_SHIELDGLOW] = shieldGlow;
    if(!IsShaderValid(grayScale))
        AssertNotNull(&grayScale,"Shader error in load.","grayScale");
    else
        shaders[S_GRAYSCALE] = grayScale;
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

void DrawShader(Texture2D self, TypeShader s, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color color)
{
    BeginShaderMode(shaders[s]);
    {
        DrawTexturePro(self,source,dest,origin,rotation,color);
    }
    EndShaderMode();
}
//////////////////////////////////////////////////////////