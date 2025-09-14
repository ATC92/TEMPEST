///////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////
///< C/C++ Lib
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>
#include <stdbool.h>
///< CGame Lib
#include "../Utils/Information.h"
#include "../Components/Fonts.h"
#include "../Game/Game.h"
///////////////////////////////////////////////////////////
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


