//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "../Utils/ErrorManager.h"

//////////////////////////////////////////////////////////
///< Public definition
extern Shader* shaders;

///< Shield shader
extern int locDirection;
extern int locTime;
extern int locSpeed; 
extern int locWidth;
extern int locIntensity; 
extern int locColor;
extern int locOffset; 
extern float timeShader;
//////////////////////////////////////////////////////////
typedef enum _typeShader
{
    S_INVERT,
    S_OUTLINE,
    S_BLUR,
    S_SHIELDGLOW,
    S_GRAYSCALE
}TypeShader;
//////////////////////////////////////////////////////////
/**
 * @brief Load and initialize all shaders used in the game.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note Call this function at the start of the game.
 */
void InitShaders(void);
/**
 * @brief Free all shaders loaded.
 * 
 * @param `void`
 * 
 * @return `void`
 * 
 * @note Call this function before closing the game.
 */
void DestroyShaders(void);
/**
 * 
 */
void DrawShader(Texture2D self, TypeShader s, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color color);
//////////////////////////////////////////////////////////