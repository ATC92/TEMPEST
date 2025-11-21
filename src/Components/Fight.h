//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Mouse.h"
#include "Entity.h"
#include "Camera.h"
#include "BattleLog.h"
#include "CardSelector.h"
#include "Sound.h"

#include "../Engine/Flags.h"

#include "../Utils/Queues.h"
#include "../Utils/String.h"
#include "../Utils/ErrorManager.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum _fightPhase{
    FIGHT_SELECT_ATTACK,
    FIGHT_SELECT_TARGET,
    FIGHT_EXECUTE,
    FIGHT_END_TURN,
    FIGHT_DICE_SHOW,
    FIGHT_DICE_ROLL,
    FIGHT_CARD_SHOW,
    FIGHT_CARD_SELECT,
    FIGHT_CARD_USE
} FightPhase;

typedef struct _availableCard{
    int invIndex;
    Card* card;
} AvailableCard;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define LOW_HEALTH_THRESHOLD 0.3f 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Rectangle fontBox[4];
extern Veyx* veyxPriority[8];
extern FightPhase currentPhase;
extern FightPhase currentPhaseNPC;
extern DiceType diceSelected;
extern size_t diceSelectedToAnimation;
extern int boxSelected;
extern bool attSelected;
extern size_t rollDice;
extern size_t threshold;
extern Texture2D key_R;
extern Rectangle recKeyR;
extern bool IsVeyxSelectedCard;
extern size_t buffAcum;

extern float attackTimer;
extern float attackTimerDice;
extern bool cardSpecialActived;

extern Color POLINIZAR_GREEN;
extern float color[4];
extern int fadeIntensityLoc;
extern int fadeColorLoc;
extern float currentFadeIntensity;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SystemFight(Queue* veyxQueue,Entity* player, Entity* npc,bool IsButtonPressed[]);

///< System
void HandlePlayerTurn(Queue* veyxQueue,Veyx* v, bool IsButtonPressed[], Entity* npcTeam, Entity* player);
void HandleNPCTurn(Queue* veyxQueue,Veyx* v, Entity* playerTeam, Entity* npc, bool IsButtonPressed[]);
///< NPC fuctions
int GetRandomAliveVeyx(Veyx veyxInventory[], size_t count);
DiceType GetRandomDice(Inventory* self);
void ReloadMana(Veyx* self);
bool UseCard(Inventory* inv,Inventory* player,Veyx* npcVeyxInv,Veyx* playerVeyxInv);
void ActiveCardSpecial(Veyx* npcVeyxInv, Veyx* playerVeyxInv, Card* c);
///< Aux
void RemoveDeadEnemies(Queue* q);
bool IsVeyxAlive(void* self);
bool EndFight(Entity* player, Entity* npc);
void ProcessStatus(Queue* self);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////