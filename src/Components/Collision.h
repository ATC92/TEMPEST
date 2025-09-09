#pragma once
/// C/C++ standard library
#include <math.h>
#include <float.h>
/// Raylib library
#include "raylib.h"
/// CGame library
#include "Entity.h"
#include "../Utils/VecMath.h"
//////////////////////////////////////////////////////////////
/**
 * @brief 
 * 
 */
bool SystemAABBMid(Entity* Source, Entity* Target, bool r);
//////////////////////////////////////////////////////////////