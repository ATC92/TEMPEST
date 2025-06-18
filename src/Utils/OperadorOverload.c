#include "OperadorOverload.h"

Vector2 OperadorOverload(Vector2 init, Vector2 final, char operator)
{
    Vector2 pos = {0};
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
    }
}