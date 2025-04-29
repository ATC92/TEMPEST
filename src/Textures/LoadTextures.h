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
void FillTexturesEntity(Texture2D*,TileMap*);
//
void RenderTileMap(RenderData*,MapEnum);
//
void RenderPlayer(const Entity*);
//
bool IsTileEmpty(Image,int,int);
////////////////////////////////////////////////////////////////




