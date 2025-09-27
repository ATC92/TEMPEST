//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
///< RayLib Lib
#include "raylib.h"
//< C/C++ Lib
#include <stdlib.h>
//////////////////////////////////////////////////////////
/**
 * 
 */
typedef enum _fontType
{
    f04B
}FontStyle;
//////////////////////////////////////////////////////////
///< Public Definition
extern Font* fontType;
//////////////////////////////////////////////////////////
/**
 * @brief Initialize the font to be used in the game.
 * 
 * This function loads a specific font from the assets directory
 * and assigns it to the global fontType variable. It is essential
 * 
 * @param `void`
 * 
 * @returns `void`
 * 
 * @note Make sure to call this function before using the font in any rendering operations.
 */
void InitFont(void);
/**
 * @brief Unload and free the font resources.
 * 
 * This function unloads the font stored in the global fontType variable
 * and frees the allocated memory. It should be called when the font is
 * no longer needed to prevent memory leaks.
 * 
 * @param `void`
 * 
 * @returns `void`
 * 
 * @note Ensure that this function is called during the cleanup phase of the application.
 */
void DestroyFont(void);
//////////////////////////////////////////////////////////