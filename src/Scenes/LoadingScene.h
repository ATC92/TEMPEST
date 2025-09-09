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

//////////////////////////////////////////////////////////
extern atomic_bool dataLoaded;
extern atomic_int dataProgress;
extern pthread_t loadThread;
/////////////////////////////////////s/////////////////////
/**
 * 
 */
void SimulateLoading(float seconds);
//////////////////////////////////////////////////////////


