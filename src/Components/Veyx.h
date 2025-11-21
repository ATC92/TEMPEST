///////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"

#include "Animation.h"
#include "Dice.h"
///////////////////////////////////////////////////////////
///< VeyxList like a Dex
typedef enum _veyxList
{
    vL_DRALIK,
    vL_GODAM,
    vL_IGNISQ,
    vL_LIGLY,
    vL_MUSHY,
    vL_SAPMOSS,
    vL_WANGIL,
    vL_WAQKIL,
    vL_WANDRAIL
}VeyxList;

///< VeyxTypeList
typedef enum _veyxType
{
    vT_NONE_TYPE = -1,
    vT_FIRE,                // 0
    vT_AQUA,                // 1
    vT_ELECTRIC,            // 2
    vT_GRASS,               // 3
    vT_ROCK,                // 4
    vT_FLY,                 // 5
    vT_STEEL,               // 6
    vT_POISON,              // 7
    vT_DARK,                // 8
    vT_LIGHT,               // 9
    vT_DRAGON,              // 10
    vT_ECHO,                // 11
    vT_TYPE_MAX
}VeyxType;

///< Category fot attack
typedef enum _attackCategory
{
    CATEGORY_PHYSICAL = 0,
    CATEGORY_MAGICAL,
    CATEGORY_STATUS
} AttackCategory;

///< StatusEffect for attacks
typedef enum _statusEffect
{
    STATUS_NONE = 0,
    STATUS_BURN,
    STATUS_FREEZE,
    STATUS_POISON,
    STATUS_STUN
} StatusEffect;

///< Result of the atack final.
typedef struct _attackResult
{
    int damageDone;
    bool isCritical;
    float typeMultiplier;
    bool hit;
    StatusEffect appliedStatus;
} AttackResult;

///< AttackMove, information for attack
typedef struct {
    char name[32];              /// Attack name
    uint8_t manaCost;           /// Mana cost of attack
    AttackCategory category;    /// Category
    uint8_t power;              /// Power of attack (ej. 40, 80, 120)
    VeyxType type;              /// VeyxType
    uint8_t accuracy;           /// 0-100
    uint8_t critChance;         /// 0-100
    StatusEffect statusToApply; /// if status can aplied
    uint8_t statusChance;       /// probabilidad de aplicar estado (0-100)
    bool aoe;                   /// area of effect
} AttackMove;

// multiplier[attackingType][defendingType]
/**
 * base = ((attackerStat * power) / (defenderStat + 1)) + 1
 * damage = floor(base * typeMultiplier * criticalMultiplier * randomFactor)
 */
static const float VeyxTypeMultiplier[vT_TYPE_MAX][vT_TYPE_MAX] = {
    // DEF:     FIRE, AQUA, ELECTRIC, GRASS, ROCK, FLY, STEEL, POISON, DARK, LIGHT, DRAGON, ECHO
    /* FIRE */     {0.5f, 0.5f, 1.0f, 2.0f, 1.5f, 1.0f, 1.5f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f},
    /* AQUA */     {2.0f, 0.5f, 1.0f, 0.5f, 2.0f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    /* ELECTRIC */ {1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    /* GRASS */    {0.5f, 2.0f, 1.0f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f},
    /* ROCK */     {1.0f, 1.0f, 2.0f, 1.5f, 0.5f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    /* FLY */      {2.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f},
    /* STEEL */    {1.5f, 1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.5f, 1.0f},
    /* POISON */   {1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f, 1.0f, 1.5f, 1.5f},
    /* DARK */     {1.0f, 1.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 0.5f, 2.0f, 1.0f, 1.5f},
    /* LIGHT */    {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 2.0f, 2.0f, 0.5f, 1.0f, 1.0f},
    /* DRAGON */   {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f},
    /* ECHO */     {1.0f, 1.0f, 1.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.5f, 1.5f, 2.0f, 1.0f}
};


typedef struct _veyx
{
    char name[20];
    char origin[100];
    char description[255];
    uint8_t life;
    uint8_t maxlife;
    uint8_t displayedLife;
    uint8_t mana;
    uint8_t maxMana;
    uint8_t displayedMana;
    uint8_t speed;
    uint8_t maxSpeed;
    uint8_t defense;
    uint8_t maxDefense;
    uint8_t physical_attack;
    uint8_t maxPA;
    uint8_t magic_attack;
    uint8_t maxMA;
    VeyxType type[2];
    StatusEffect status;
    size_t statusRounds;
    AttackMove moves[4];
    AttackResult resultDamage;

    int owner;
    Texture2D iconText;
    Texture2D headIcon;
    Rectangle sizeIcon;
    Rectangle sizeHead;
    Rectangle sizeInFight;
    SpriteAnimation* animation;
    
}Veyx;


////////////////////////////////////////////////////////////
///< Public declaration
extern Veyx VeyxRegistry[10];
extern size_t countVeyx;
////////////////////////////////////////////////////////////
int clamp_int(int v, int lo, int hi);
float rand_range(float a, float b);
////////////////////////////////////////////////////////////
float CalculateTypeMultiplier(VeyxType moveType, const Veyx* defender);
AttackResult ApplyAttack(Veyx* attacker, Veyx* defender, const AttackMove* move);
char* GetStatusToString(StatusEffect status);
////////////////////////////////////////////////////////////
/**
 * 
 */
void InitVeyxRegistry(void);
/**
 * 
 */
void LoadVeyxData(char* path);
/**
 * 
 */
void DestroyVeyxRegistry(void);
///////////////////////////////////////////////////////////
