//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>
#include <inttypes.h>

#include <math.h>
#include <float.h>
#include <time.h>
#include <string.h>
///< RayLig
#include "raylib.h"
#include "raymath.h"
//////////////////////////////////////////////////////////
///< COLORS by TEMPEST
// Color fullyTransparent = { 0, 0, 0, 0 }
#define TRANSPARENT      CLITERAL(Color){ 0, 0, 0, 0 }    /// Transparent

//////////////////////////////////////////////////////////
///< Game Flags State
extern bool IsGameInit;
extern int tNPCSCoop;
///< Fight Flag State
extern bool IsFightRuning;
extern bool IsVeyxPriorityInit;
extern bool FightBattleEnds;
extern bool UseDice;
extern bool sortActive;
extern bool startAnimationDice;
extern bool doneAnimationDice;
//////////////////////////////////////////////////////////
///< OptionMenu Flags State
extern bool DotPressed;
//////////////////////////////////////////////////////////
