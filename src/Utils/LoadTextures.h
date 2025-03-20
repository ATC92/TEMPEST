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
////////////////////////////////////////////////////////////////
///< Forward Declaration of sTile
struct _sTile;
typedef struct _sTile sTile;
///< Forward Declaration of MapEnum
enum _mapEnum;
typedef enum _mapEnum MapEnum;
///< Forward Declaration of RenderData
struct _renderData;
typedef struct _renderData RenderData;
///< Forward Declaration of ListTileSize
struct _szListTile;
typedef struct _szListTile ListTileSize;
///< Forward Declaration of _Entity
struct _Entity;
typedef struct _Entity Entity;
///< Forward Declaration of _tEntity
struct _tEntity;
typedef struct _tEntity tEntity;
////////////////////////////////////////////////////////////////
///< TILE TEXTURE SIZE
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
//
typedef void (*ProcessItemFunc)(void*, const cJSON*);
////////////////////////////////////////////////////////////////

//
cJSON* Load_cJSON(const char*, ListTileSize*);
//
sTile* LoadMapTextures(cJSON*,int);
//
tEntity* GenTextureEntity(const char*,const char*,ListTileSize**);
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
//
void GetArraySizeJSON(const cJSON*,ListTileSize*);
////////////////////////////////////////////////////////////////




