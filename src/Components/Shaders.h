//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
///< C/C++ Lib
#include <stdlib.h>
///< CGame Lib
///< Raylib
#include "raylib.h"
//////////////////////////////////////////////////////////
///< Public definition
extern Shader* shaders;
//////////////////////////////////////////////////////////
typedef enum _typeShader
{
    S_INVERT,
    S_OUTLINE
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
//////////////////////////////////////////////////////////