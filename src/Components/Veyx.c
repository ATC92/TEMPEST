///////////////////////////////////////////////////////////
#include "Veyx.h"
#include<string.h>
///////////////////////////////////////////////////////////
///< Public declarations
Veyx VeyxRegistry[10];
size_t countVeyx;
static AttackMove VeyxMoves[vT_TYPE_MAX][2] = {
    // FIRE
    {
        {"Flame Burst", CATEGORY_MAGICAL, 20, vT_FIRE, 95, 6, STATUS_NONE, 20, false},
        {"Fire Punch",  CATEGORY_PHYSICAL, 30, vT_FIRE, 90, 10, STATUS_BURN, 15, false}
    },
    // AQUA
    {
        {"Water Jet",    CATEGORY_MAGICAL, 35, vT_AQUA, 95, 5, STATUS_NONE, 0, false},
        {"Bubble Crush", CATEGORY_PHYSICAL, 20, vT_AQUA, 100, 0, STATUS_NONE, 0, false}
    },
    // ELECTRIC
    {
        {"Thunder Shock", CATEGORY_MAGICAL, 35, vT_ELECTRIC, 90, 10, STATUS_NONE, 20, false},
        {"Spark Punch",   CATEGORY_PHYSICAL, 20, vT_ELECTRIC, 100, 5, STATUS_STUN, 10, false}
    },
    // GRASS
    {
        {"Leaf Blade", CATEGORY_PHYSICAL, 40, vT_GRASS, 95, 6, STATUS_NONE, 0, false},
        {"Vine Whip",   CATEGORY_PHYSICAL, 25, vT_GRASS, 100, 0, STATUS_POISON, 15, false}
    },
    // ROCK
    {
        {"Rock Throw",  CATEGORY_PHYSICAL, 30, vT_ROCK, 95, 5, STATUS_NONE, 0, false},
        {"Stone Slam",  CATEGORY_PHYSICAL, 35, vT_ROCK, 90, 8, STATUS_STUN, 10, false}
    },
    // FLY
    {
        {"Gust",      CATEGORY_MAGICAL, 25, vT_FLY, 95, 5, STATUS_NONE, 0, false},
        {"Wing Attack",CATEGORY_PHYSICAL, 35, vT_FLY, 90, 8, STATUS_NONE, 0, false}
    },
    // STEEL
    {
        {"Metal Claw", CATEGORY_PHYSICAL, 40, vT_STEEL, 95, 10, STATUS_NONE, 0, false},
        {"Iron Strike", CATEGORY_PHYSICAL, 30, vT_STEEL, 90, 12, STATUS_STUN, 15, false}
    },
    // POISON
    {
        {"Poison Sting", CATEGORY_PHYSICAL, 10, vT_POISON, 100, 5, STATUS_POISON, 30, false},
        {"Toxic Fang",   CATEGORY_PHYSICAL, 35, vT_POISON, 90, 8, STATUS_POISON, 40, false}
    },
    // DARK
    {
        {"Shadow Claw", CATEGORY_PHYSICAL, 35, vT_DARK, 95, 10, STATUS_NONE, 0, false},
        {"Night Bite",  CATEGORY_PHYSICAL, 40, vT_DARK, 90, 12, STATUS_STUN, 15, false}
    },
    // LIGHT
    {
        {"Holy Beam",   CATEGORY_MAGICAL, 60, vT_LIGHT, 90, 8, STATUS_NONE, 0, false},
        {"Radiant Punch", CATEGORY_PHYSICAL, 35, vT_LIGHT, 95, 6, STATUS_NONE, 0, false}
    },
    // DRAGON
    {
        {"Dragon Claw", CATEGORY_PHYSICAL, 40, vT_DRAGON, 90, 10, STATUS_NONE, 0, false},
        {"Dragon Breath", CATEGORY_MAGICAL, 35, vT_DRAGON, 90, 8, STATUS_NONE, 0, false}
    },
    // ECHO
    {
        {"Sonic Boom", CATEGORY_MAGICAL, 40, vT_ECHO, 95, 5, STATUS_STUN, 20, false},
        {"Echo Strike", CATEGORY_PHYSICAL, 35, vT_ECHO, 100, 0, STATUS_NONE, 0, false}
    }
};
///////////////////////////////////////////////////////////
int clamp_int(int v, int lo, int hi) 
{ 
    if (v < lo) 
        return lo; 
    if (v > hi) 
        return hi; 
    return v; 
}
float rand_range(float a, float b) 
{ 
    return a + ((float)rand() / RAND_MAX) * (b - a); 
}
///////////////////////////////////////////////////////////
float CalculateTypeMultiplier(VeyxType moveType, const Veyx* defender)
{
    float m = VeyxTypeMultiplier[moveType][defender->type[0]];
    if (defender->type[1] != vT_NONE_TYPE)
        m *= VeyxTypeMultiplier[moveType][defender->type[1]];
    return m;
}

AttackResult ApplyAttack(const Veyx* attacker, Veyx* defender, const AttackMove* move)
{
    ///< Steps for ApplyAttack
    AttackResult res = {0, false, 1.0f, false, STATUS_NONE};

    /// 1) hit check
    int roll = rand() % 100;
    if (roll >= move->accuracy)
    {
        res.hit = false;
        return res;
    }
    res.hit = true;

    /// 2) determine if critical
    res.isCritical = ( (rand() % 100) < move->critChance );
    float critMul = res.isCritical ? 1.5f : 1.0f;

    /// 3) type multiplier
    res.typeMultiplier = CalculateTypeMultiplier(move->type, defender);

    /// 4) choose stat based on category
    int atkStat = (move->category == CATEGORY_PHYSICAL) ? attacker->physical_attack : attacker->magic_attack;
    int defStat = (move->category == CATEGORY_PHYSICAL) ? defender->defense : defender->defense;

    /// 5) base damage
    float base = ((float)atkStat * (float)move->power) / ( (float)defStat + 1.0f );
    base = base + 1.0f;

    /// 6) random variance (0.85 - 1.0)
    float variance = rand_range(0.85f, 1.0f);

    /// 7) final damage
    float dmg_f = base * res.typeMultiplier * critMul * variance;
    int dmg = (int)floorf(dmg_f);
    if (dmg < 0) dmg = 0;

    /// 8) apply to defender (clamped)
    int prevLife = defender->life;
    defender->life = (uint8_t) clamp_int(defender->life - dmg, 0, 255);

    res.damageDone = prevLife - defender->life;

    /// 9) status application
    if (move->statusToApply != STATUS_NONE)
    {
        if ((rand() % 100) < move->statusChance)
        {
            defender->status = move->statusToApply;
            res.appliedStatus = move->statusToApply;
        }
        else
        {
            UseDice = true;
        }
    }

    return res;
}
///////////////////////////////////////////////////////////
void InitVeyxRegistry(void)
{
    countVeyx = 0;
}

void DestroyVeyxRegistry(void)
{
    for(size_t i=0; i<10;i++)
    {
        UnloadTexture(VeyxRegistry[i].iconText);
    }
}

void LoadVeyxData(char* path)
{
    FILE *fDataVeyx = fopen(path,"r");
    char pathTexture[256];
    char pathHead[256];
    char line[500];

    if(fDataVeyx == NULL)
        TraceLog(LOG_ERROR,"Archive VeyxData not open.");
    else
        TraceLog(LOG_INFO, "Archive VeyxData Loaded correctly");
    
    while(fgets(line, sizeof(line), fDataVeyx) != NULL)
    {
        int i = 0;
        char *token = strtok(line, "|");
        while(token != NULL) 
        {
            switch(i) 
            {
                case 0: 
                    strncpy(VeyxRegistry[countVeyx].name, token, sizeof(VeyxRegistry[countVeyx].name)-1); 
                    VeyxRegistry[countVeyx].name[sizeof(VeyxRegistry[countVeyx].name)-1] = '\0';
                    break;
                case 1: 
                    strncpy(VeyxRegistry[countVeyx].origin, token, sizeof(VeyxRegistry[countVeyx].origin)-1); 
                    VeyxRegistry[countVeyx].origin[sizeof(VeyxRegistry[countVeyx].origin)-1] = '\0';
                    break;
                case 2: 
                    strncpy(VeyxRegistry[countVeyx].description, token, sizeof(VeyxRegistry[countVeyx].description)-1); 
                    VeyxRegistry[countVeyx].description[sizeof(VeyxRegistry[countVeyx].description)-1] = '\0';
                    break;
                case 3: 
                    VeyxRegistry[countVeyx].life = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].maxlife = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].displayedLife = (uint8_t)atoi(token); 
                    break;
                case 4: 
                    VeyxRegistry[countVeyx].mana = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].maxMana = (uint8_t)atoi(token); 
                    break;
                case 5: 
                    VeyxRegistry[countVeyx].speed = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].maxSpeed = (uint8_t)atoi(token); 
                    break;
                case 6: 
                    VeyxRegistry[countVeyx].defense = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].maxDefense = (uint8_t)atoi(token); 
                    break;
                case 7: 
                    VeyxRegistry[countVeyx].physical_attack = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].maxPA = (uint8_t)atoi(token); 
                    break;
                case 8: 
                    VeyxRegistry[countVeyx].magic_attack = (uint8_t)atoi(token); 
                    VeyxRegistry[countVeyx].maxMA = (uint8_t)atoi(token); 
                    break;
                case 9: VeyxRegistry[countVeyx].type[0] = atoi(token); break;
                case 10: VeyxRegistry[countVeyx].type[1] = atoi(token); break;
            }

            /// Select AttackMove
            VeyxRegistry[countVeyx].moves[0] = VeyxMoves[VeyxRegistry[countVeyx].type[0]][0];
            VeyxRegistry[countVeyx].moves[1] = VeyxMoves[VeyxRegistry[countVeyx].type[0]][1];
            if (VeyxRegistry[countVeyx].type[1] != vT_NONE_TYPE)
            {    
                VeyxRegistry[countVeyx].moves[2] = VeyxMoves[VeyxRegistry[countVeyx].type[0]][0];
                VeyxRegistry[countVeyx].moves[3] = VeyxMoves[VeyxRegistry[countVeyx].type[0]][1];
            }
            token = strtok(NULL, "|");
            i++;
        }
        strcpy(pathTexture,TextFormat(ASSETS "/Veyx/%s/%s-Icon.png",VeyxRegistry[countVeyx].name,VeyxRegistry[countVeyx].name));
        strcpy(pathHead,TextFormat(ASSETS "/Veyx/%s/%s-Head.png",VeyxRegistry[countVeyx].name,VeyxRegistry[countVeyx].name));
        if(IsPathFile(pathTexture))
        {
            VeyxRegistry[countVeyx].iconText = LoadTexture(pathTexture);
            VeyxRegistry[countVeyx].headIcon = LoadTexture(pathHead);
        }
        VeyxRegistry[countVeyx].sizeIcon = (Rectangle){.x=0,.y=0,.width=VeyxRegistry[countVeyx].iconText.width, .height=VeyxRegistry[countVeyx].iconText.height};
        VeyxRegistry[countVeyx].sizeHead = (Rectangle){.x=0,.y=0,.width=VeyxRegistry[countVeyx].headIcon.width, .height=VeyxRegistry[countVeyx].headIcon.height};
        VeyxRegistry[countVeyx].owner = -1;
        countVeyx++;
    }
    fclose(fDataVeyx);
}
///////////////////////////////////////////////////////////
