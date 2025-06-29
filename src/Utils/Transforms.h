#pragma once
///< C/C++ Libs
#include <math.h>
//////////////////////////////////////////////////////////////////
/**
 * @brief Structure representing a 4x4 matrix.
 * 
 * This structure contains a 4x4 matrix represented as a 2D array of floats.
 * It is typically used for transformations in 3D graphics, such as translation, rotation,
 * and scaling.
 * 
 * @c matrix[4][4] A 2D array representing the matrix elements.
 */
typedef struct _m4
{
    float matrix[4][4];
}Mat4;
/**
 * @brief Creates an identity matrix.
 * 
 * This function initializes a 4x4 identity matrix, which is a special type of matrix
 * that does not change the vector it is multiplied with. The identity matrix has 1s on the
 * diagonal and 0s elsewhere.
 * 
 * @param `void`
 * 
 * @return Mat4 A 4x4 identity matrix.
 */
Mat4 matrixIdentity(void)
{
    Mat4 m = {0};
    for (int i = 0; i < 4; i++) m.matrix[i][i] = 1.0f;
    return m;
}