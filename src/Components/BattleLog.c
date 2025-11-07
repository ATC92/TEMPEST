//////////////////////////////////////////////////////////
#include "BattleLog.h"
//////////////////////////////////////////////////////////
///< Public Declarations
BattleLog battleLog = {0};
//////////////////////////////////////////////////////////
void AddBattleLog(const char* fmt, ...)
{
    if (battleLog.count >= MAX_LOGS)
    {
        for (int i = 1; i < MAX_LOGS; i++)
        {
            strcpy(battleLog.lines[i - 1], battleLog.lines[i]);
            battleLog.displayTime[i - 1] = battleLog.displayTime[i];
        }
        battleLog.count = MAX_LOGS - 1;
    }

    va_list args;
    va_start(args, fmt);
    vsnprintf(battleLog.lines[battleLog.count], MAX_LOG_LENGTH, fmt, args);
    va_end(args);

    battleLog.displayTime[battleLog.count] = 0.0f;
    battleLog.count++;
}

void UpdateBattleLog(float delta)
{
    for (int i = 0; i < battleLog.count; i++)
        battleLog.displayTime[i] += delta;
}

void DrawBattleLog(Vector2 position)
{
    for (int i = 0; i < battleLog.count; i++) {
        float alpha = 1.0f;
        if (battleLog.displayTime[i] > 5.0f)
            alpha = 1.0f - (battleLog.displayTime[i] - 5.0f) / 1.0f;

        if (alpha <= 0.0f) continue;

        Color textColor = Fade(RAYWHITE, alpha);
        DrawText(battleLog.lines[i],
                 position.x,
                 position.y + i * 20,
                 18,
                 textColor);
    }
}
//////////////////////////////////////////////////////////