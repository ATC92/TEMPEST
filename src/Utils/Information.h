#pragma once
////////////////////////////////////////////////////////////////////////////////////////////
///< C/C++ Lib
///< CGame Lib
#include "../Components/Mouse.h"
#include "../Components/Entity.h"
///< RayLib
#include "raylib.h"
////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Draws information about the camera.
 * 
 * This function draws a rectangle with camera information such as target position and zoom level.
 * It also displays the current frames per second (FPS).
 * 
 * @param camera The Camera2D object containing the camera information to be displayed.
 * 
 * @return 'Void'.
 */
void DrawInformationCamera(Camera2D camera, Entity* eplayer);
/**
 * @brief 
 */
void DrawLinesMidScreen();
////////////////////////////////////////////////////////////////////////////////////////////
