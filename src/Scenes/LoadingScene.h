#pragma once
///< C/C++ Lib
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <stdbool.h>
///< CGame Lib
#include "../Game/Game.h"
#include "../Utils/Fonts.h"
#include "../Utils/Information.h"
/////////////////////////////////////s/////////////////////
/**
 * 
 */
void InitLoadingScene(float sec);
/**
 * 
 */
void UpdateLoadingScene(void);
/**
 * 
 */
void DestroyLoadingScene(void);
//////////////////////////////////////////////////////////


