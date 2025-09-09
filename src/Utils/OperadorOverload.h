#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///< RayLib 
#include "raylib.h"
//////////////////////////////////////////////////////////////////
/**
 * @brief Overloaded operator for Vector2
 * 
 * This function performs an operation on two Vector2 objects based on the specified operator.
 * It currently supports addition ('+') and returns a new Vector2.
 * 
 * @param init    The initial Vector2 object.
 * @param final   The final Vector2 object.
 * @param operator The operator to apply ('+').
 * 
 * @return Vector2  The resulting Vector2 after applying the operator.
 */
Vector2 OperadorOverload(Vector2,Vector2,char);
/**
 * @brief Overloaded boolean operator for Vector2
 * 
 * This function compares two Vector2 objects based on the specified operator.
 * It currently supports less than ('<'), greater than ('>'), and equality ('=').
 * 
 * @param init    The initial Vector2 object.
 * @param final   The final Vector2 object.
 * @param operator The operator to apply ('<', '>', '=').
 * 
 * @return bool  The result of the comparison.
 */
bool OperadorOverloadBool(Vector2,Vector2,char);


//////////////////////////////////////////////////////////////////