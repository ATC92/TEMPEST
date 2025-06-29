#include "OperadorOverload.h"
//////////////////////////////////////////////////////////////////
Vector2 OperadorOverload(Vector2 init, Vector2 final, char operator)
{
    switch (operator)
    {
        case '+':
            Vector2 pos = {
                .x = (init.x + final.x),
                .y = (init.y +final.y)
            };
            return pos;
            break;
        
        default:
            break;
    };
    return (Vector2){0,0};  ///< Return zero vector if operator is not recognized
}
//////////////////////////////////////////////////////////////////
bool OperadorOverloadBool(Vector2 init, Vector2 final, char operator)
{
    switch (operator)
    {
        case '<':
            return (init.x < final.x) && (init.y < final.y);
        case '>':
            return (init.x > final.x) && (init.y > final.y);
        case '=':
            return (init.x == final.x) && (init.y == final.y);
        default:
            return false;
    }
}
//////////////////////////////////////////////////////////////////

