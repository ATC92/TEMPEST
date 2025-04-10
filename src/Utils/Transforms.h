#pragma once
///< C/C++ Libs
#include <math.h>


///< Structs
typedef struct _m4
{
    float matrix[4][4];
}Mat4;

Mat4 matrixIdentity()
{
    Mat4 m = {0};
    for (int i = 0; i < 4; i++) m.matrix[i][i] = 1.0f;
    return m;
}