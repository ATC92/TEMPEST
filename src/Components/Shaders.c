//////////////////////////////////////////////////////////
#include "Shaders.h"
//////////////////////////////////////////////////////////
///< Public declaration
Shader* shaders;
//////////////////////////////////////////////////////////
void InitShaders(void)
{
    size_t totalShaders = 2;
    ///< Load Shaders
    Shader invert = LoadShader(NULL, "src/Shaders/invert.fs");
    Shader outline = LoadShader(NULL,"src/Shaders/outline.fs");
    if (!IsShaderValid(invert) || !IsShaderValid(outline)) 
        TraceLog(LOG_ERROR, "Shader Invalid");

    ///< Value's for Outline Shader
    Texture2D tex = LoadTexture("assets/UI/BookInformation.png"); 
    SetShaderValue(outline, GetShaderLocation(outline, "resolution"), (float[2]){ (float)tex.width, (float)tex.height }, SHADER_UNIFORM_VEC2);
    SetShaderValue(outline, GetShaderLocation(outline, "outlineThickness"), (float[1]){ 5.0f }, SHADER_UNIFORM_FLOAT);
    SetShaderValue(outline, GetShaderLocation(outline, "outlineColor"), (float[3]){ 1.0f, 1.0f, 1.0f }, SHADER_UNIFORM_VEC3);
    UnloadTexture(tex);

    ///< Create and Load Shaders
    shaders = (Shader*)calloc(totalShaders,sizeof(Shader));
    shaders[0] = invert;
    shaders[1] = outline;
}