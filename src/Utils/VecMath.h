//////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////
///< Standard Libraries
#include <math.h>
///< Raylib Library
#include "raylib.h"
//////////////////////////////////////////////////////////
/// Swap two variables of the same type
#define SWAP(a, b) do { \
    __typeof__(a) temp = (a); \
    (a) = (b); \
    (b) = temp; \
} while(0)


//////////////////////////////////////////////////////////
static inline Vector2 vec2_new(float x, float y) {return (Vector2){x, y};}                          /// Create a new Vector2
static inline Vector2 vec2_add(Vector2 a, Vector2 b) {return (Vector2){a.x + b.x, a.y + b.y};}      /// Add two vectors
static inline Vector2 vec2_sub(Vector2 a, Vector2 b) {return (Vector2){a.x - b.x, a.y - b.y};}      /// Subtract two vectors
static inline Vector2 vec2_mul(Vector2 a, float s) {return (Vector2){a.x * s, a.y * s};}            /// Multiply vector by scalar
static inline Vector2 vec2_div(Vector2 a, float s) {return (Vector2){a.x / s, a.y / s};}            /// Divide vector by scalar
static inline Vector2 vec2_mulv(Vector2 a, Vector2 b) {return (Vector2){ a.x * b.x, a.y * b.y };}   /// Multiply vector by vector
static inline float vec2_dot(Vector2 a, Vector2 b) {return a.x * b.x + a.y * b.y;}                  /// Dot product (returns a scalar)
static inline float vec2_len(Vector2 a) {return sqrtf(a.x * a.x + a.y * a.y);}                      /// Vector length (magnitude)
static inline Vector2 vec2_inv(Vector2 v) {return (Vector2){ 1.0f / v.x, 1.0f / v.y };}             /// Invert vector components
static inline Vector2 vec2_norm(Vector2 a)                                                          /// Normalize vector (returns unit vector, or zero vector if length = 0)
{
    float l = vec2_len(a);
    return (l > 0.0f) ? vec2_div(a, l) : (Vector2){0.0f, 0.0f};
}
///////////////////////////////////////////////////////////
static inline void swap_Float(float *a, float *b)                                                         /// Swap two floats
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

