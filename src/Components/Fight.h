//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Mouse.h"
#include "Entity.h"
#include "Camera.h"
#include "BattleLog.h"
#include "ObjectType.h"
#include "Sound.h"

#include "../Engine/Flags.h"

#include "../Utils/Queues.h"
#include "../Utils/ErrorManager.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum _fightPhase{
    FIGHT_SELECT_ATTACK,
    FIGHT_SELECT_TARGET,
    FIGHT_EXECUTE,
    FIGHT_END_TURN,
    FIGHT_DICE_SHOW,
    FIGHT_DICE_SELECT,
    FIGHT_DICE_ROLL,
    FIGHT_CART_SHOW,
    FIGHT_CART_SELECT,
    FIGHT_CART_USE
} FightPhase;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern Rectangle fontBox[4];
extern FightPhase currentPhase;
extern FightPhase currentPhaseNPC;
extern DiceType diceSelected;
extern size_t diceSelectedToAnimation;
extern int boxSelected;
extern bool attSelected;
extern size_t rollDice;
extern size_t threshold;
extern Texture2D key_R;

extern float attackTimer;
extern float attackTimerDice;
// extern size_t diceSelected;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SystemFight(Queue* veyxQueue,Entity* player, Entity* npc,bool IsButtonPressed[]);

///< System
void HandlePlayerTurn(Queue* veyxQueue,Veyx* v, bool IsButtonPressed[], Entity* npcTeam, Entity* player);
void HandleNPCTurn(Queue* veyxQueue,Veyx* v, Entity* playerTeam, Entity* npc, bool IsButtonPressed[]);
///< NPC fuctions
int GetRandomAliveVeyx(Veyx veyxInventory[], size_t count);
DiceType GetRandomDice(Inventory* self);

///< Aux
void RemoveDeadEnemies(Queue* q);
bool IsVeyxAlive(void* self);
bool EndFight(Entity* player, Entity* npc);
void ProcessStatus(Queue* self);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////