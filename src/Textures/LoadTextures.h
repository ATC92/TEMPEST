#pragma once
///< Extern Libraries.
#include "cJSON.h"
#include "raylib.h"
///< Libraries C.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
///< Libraries CGame
#include "../Entity/Entity.h"
#include "Textures.h"
////////////////////////////////////////////////////////////////
///<
typedef void (*ProcessItemFunc)(void*, const cJSON*);
////////////////////////////////////////////////////////////////
//
cJSON* Load_cJSON(const char*);
//
TileMap* LoadMapTextures(char*, const int, const int);
//
void RenderTileMap(RenderData*,MapEnum);
//
void RenderPlayer(const Entity*,const Camera2D);
////////////////////////////////////////////////////////////////




