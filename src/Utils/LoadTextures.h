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
#include "../MapGen/Map.h"
#include "../Entity/Entity.h"
///< Forward Declaration of sTile
struct _sTile;
typedef struct _sTile sTile;
///< Forward Declaration of MapEnum
enum _mapEnum;
typedef enum _mapEnum MapEnum;
///< Forward Declaration of RenderData
struct _renderData;
typedef struct _renderData RenderData;




///< TILE TEXTURE SIZE
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
//
typedef void (*ProcessItemFunc)(void*, const cJSON*);
////////////////////////////////////////////////////////////////
//
cJSON* Load_cJSON(const char*);
//
sTile* LoadMapTextures(const cJSON*);
//
tEntity* GenTextureEntity(const char*,const char*);
//
void* LoadTexturesFromJSON(const cJSON*, const char*, size_t, int, ProcessItemFunc);
//
void ProcessEntity(void*, const cJSON*);
//
void ProcessTile(void*, const cJSON*);
//
void RenderTileMap(RenderData*,MapEnum);
//
void RenderPlayer(const Entity,const Camera2D);
////////////////////////////////////////////////////////////////




