#pragma once
///< Extern Libraries.
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
////////////////////////////////////////////////////////////////
//
TileMap* LoadMapTextures(char*, const int, const int);
//
void FillTexturesEntity(Texture2D*,TileMap*);
//
void RenderTileMap(RenderData*,int);
//
void RenderPlayer(const Entity*);
//
bool IsTileEmpty(Image,int,int);
////////////////////////////////////////////////////////////////




