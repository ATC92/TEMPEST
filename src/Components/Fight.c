//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Fight.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Public Declarations
Rectangle fontBox[4]; 
FightPhase currentPhase = FIGHT_SELECT_ATTACK;
FightPhase currentPhaseNPC = FIGHT_SELECT_ATTACK;
DiceType diceSelected;
size_t diceSelectedToAnimation;
int boxSelected = -1;
bool attSelected;
size_t rollDice;
size_t threshold;
float attackTimer = 0;
float attackTimerDice = 0;

Texture2D key_R;

///< Private Declarations
static int attackSelected = -1;
static int targetSelected = -1;
static size_t statusRounds;
static bool turnInit;

static float attackTimerNPC = 0.0f;
static int targetIndex;
static int attackIndex;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SystemFight(Queue* veyxQueue,Entity* player, Entity* npc,bool IsButtonPressed[])
{
    if(QueueEmpty(*veyxQueue))
    {
        AssertNotNull(veyxQueue,"Empty Queue veyxQueue","veyxQueue");
        return;
    }
    Item* item = Peak(veyxQueue);
    AssertNotNull(item,"Error with Peak in SystemFight","item");
    Veyx* v = (Veyx*)item->item;
    AssertNotNull(v,"Error with cast from void*  in SystemFight","v");
    switch (v->owner)
    {
        case _PLAYER:
            HandlePlayerTurn(veyxQueue,v, IsButtonPressed, npc, player);
            break;

        case _NPC:
            HandleNPCTurn(veyxQueue,v, player,npc,IsButtonPressed);
            break;
    default:
        TraceLog(LOG_WARNING, "Unknown Veyx owner");
        break;
    }
    if(player->veyxAlive <= 0 || npc->veyxAlive <= 0)
        FightBattleEnds = true;
}

void HandlePlayerTurn(Queue* veyxQueue,Veyx* v, bool IsButtonPressed[], Entity* npcTeam, Entity* player)
{
    if(v->status != STATUS_NONE && turnInit)
    {
        TraceLog(LOG_INFO, "Player: Veyx has status");
        ProcessStatus(veyxQueue);
    }
    if(turnInit)
        TraceLog(LOG_INFO, "Player: Veyx turn %s", v->name);
    switch (currentPhase)
    {
        case FIGHT_SELECT_ATTACK:
        {
            turnInit = false;
            for (size_t i = 0; i < 4; i++)
            {
                if (CheckCollisionPointRec(mouse, fontBox[i]) && IsButtonPressed[0] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    PlaySound(sounds[0]);
                    attackSelected = i;
                    boxSelected = i;
                    attSelected = true;
                    currentPhase = FIGHT_SELECT_TARGET;
                    TraceLog(LOG_INFO, "Player: Attack selected: %s", v->moves[i].name);
                    break;
                }
            }
        } break;
        case FIGHT_SELECT_TARGET:
        {
            for (size_t i = 0; i < 4; i++)
            {
                if (CheckCollisionPointRec(mouse, fontBox[i]) && IsButtonPressed[0] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if(i != attackSelected)
                        PlaySound(sounds[0]);
                    attackSelected = i;
                    boxSelected = i;
                    attSelected = true;
                    // currentPhase = FIGHT_SELECT_TARGET;
                    TraceLog(LOG_INFO, "Player: Attack selected: %s", v->moves[i].name); 
                }
                if(IsKeyDown(KEY_Q))
                {
                    currentPhase = FIGHT_SELECT_ATTACK;
                    boxSelected = -1;
                    attSelected = false;
                    TraceLog(LOG_INFO, "Key Q Pressed return to SELECT_ATTACK");
                }
                Vector2 mouseWorld = GetScreenToWorld2D(mouse, camera); 
                if (npcTeam->veyxInventory[i].life > 0 && 
                    CheckCollisionPointRec(mouseWorld, npcTeam->veyxInventory[i].sizeInFight) &&  
                    IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    targetSelected = i;
                    currentPhase = FIGHT_EXECUTE;
                    TraceLog(LOG_INFO, "Player: Veyx Selected %s",npcTeam->veyxInventory[i].name);
                    break;
                }
            }
        } break;
        case FIGHT_EXECUTE:
        {    
            v->resultDamage = ApplyAttack(v, &npcTeam->veyxInventory[targetSelected], &v->moves[attackSelected]);
            AddBattleLog("%s uso %s contra: %s", v->name, v->moves[attackSelected].name,npcTeam->veyxInventory[targetSelected].name);
            AddBattleLog("Causo %d de daño a %s",v->resultDamage.damageDone, npcTeam->veyxInventory[targetSelected].name);
            if(!IsVeyxAlive(&npcTeam->veyxInventory[targetSelected]))
            {
                TraceLog(LOG_INFO, "Player: Veyx Dead %s",npcTeam->veyxInventory[targetSelected].name);
                npcTeam->veyxAlive--;
                RemoveDeadEnemies(veyxQueue);
            }
            if(UseDice && npcTeam->veyxInventory[targetSelected].status == STATUS_NONE && npcTeam->veyxInventory[targetSelected].life > 0)
            {
                TraceLog(LOG_INFO, "Player: Use Dice");
                currentPhase = FIGHT_DICE_SHOW;
            }
            else
            {
                TraceLog(LOG_INFO, "Player: Cant use Dice, GoTo End_Turn");
                currentPhase = FIGHT_END_TURN;
            }
        } break;
        case FIGHT_END_TURN:
        {
            attackSelected = -1;
            targetSelected = -1;
            boxSelected = -1;
            attSelected = false;
            IsButtonPressed[0] = false;
            currentPhase = FIGHT_SELECT_ATTACK;
            turnInit = true;
            UseDice = false;
            ProcessAndRequeue(veyxQueue,IsVeyxAlive);
            TraceLog(LOG_INFO, "Player: End_Turn");
        } break;
        case FIGHT_DICE_SHOW:
        {
            if(IsKeyPressed(KEY_R))
            {
                currentPhase = FIGHT_END_TURN;
            }
            for(size_t i=0; i<6; i++)
            {
                if(CheckCollisionPointRec(mouse,player->inventory.object[i].dice.boundingBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    attackTimer = 0.f;
                    attackTimerDice = 0.f;
                    diceAnimations[diceSelectedToAnimation].cur = 0;
                    diceSelectedToAnimation = i;
                    diceSelected = player->inventory.object[i].dice.type;

                    startAnimationDice = false;
                    doneAnimationDice = false;

                    if(player->inventory.object[i].dice.amount > 0)
                        player->inventory.object[i].dice.amount--;
                    TraceLog(LOG_INFO,"Player: Dice selected: %d | %s",player->inventory.object[i].dice.type,player->inventory.object[i].dice.name);
                    currentPhase = FIGHT_DICE_ROLL;
                    break; 
                }
            }
        }break;
        case FIGHT_DICE_ROLL:
        {
            if(!startAnimationDice && !doneAnimationDice)
            {
                TraceLog(LOG_INFO, "Player: Roll Dice");
                rollDice = RollDice(diceSelected);
                threshold = (diceSelected / 2);
                TraceLog(LOG_INFO, "Player: %d | %d",rollDice,threshold);
                if (rollDice >= threshold)
                {
                    TraceLog(LOG_INFO, "Player: InsideIF");
                    npcTeam->veyxInventory[targetSelected].status = v->moves[attackSelected].statusToApply;
                    statusRounds = (size_t)((rand() % 3) + 1);
                    npcTeam->veyxInventory[targetSelected].statusRounds = statusRounds;
                    if(npcTeam->veyxInventory[targetSelected].status == STATUS_FREEZE || npcTeam->veyxInventory[targetSelected].status == STATUS_STUN)
                    {
                        TraceLog(LOG_INFO, "Player: Enemy Veyx selected: %s",npcTeam->veyxInventory[targetSelected].name);
                    }
                }
                else 
                    npcTeam->veyxInventory[targetSelected].status = STATUS_NONE;
                TraceLog(LOG_INFO, "Player: EndTurn from DiceRoll");
                
                // player->inventory.object[diceSelectedToAnimation].dice.animation.cur = 0;
                UseDice = false;
                startAnimationDice = true;
                doneAnimationDice = false;
            }
            if(doneAnimationDice)
            {
                doneAnimationDice = false;
                startAnimationDice = true;
                currentPhase = FIGHT_END_TURN;
            }
        } break;
    }///< End Switch
}

void HandleNPCTurn(Queue* veyxQueue,Veyx* v, Entity* playerTeam, Entity* npc, bool IsButtonPressed[])
{
    // static bool attackStarted = false;    

    if(v->status != STATUS_NONE && turnInit)
        ProcessStatus(veyxQueue);
    switch (currentPhaseNPC)
    {
        case FIGHT_SELECT_ATTACK:
        {
            turnInit = false;
            attackIndex = GetRandomValue(0, 3);
            currentPhaseNPC = FIGHT_SELECT_TARGET;
        } break;
        case FIGHT_SELECT_TARGET:
        {
            targetIndex = GetRandomAliveVeyx(playerTeam->veyxInventory,4);
            if (targetIndex == -1) return;
            currentPhaseNPC = FIGHT_EXECUTE;
        } break;
        case FIGHT_EXECUTE:
        {              
            attackTimerNPC += GetFrameTime();
            if (attackTimerNPC >= 2.0f)
            {
                v->resultDamage = ApplyAttack(v, &playerTeam->veyxInventory[targetIndex], &v->moves[attackIndex]);
                AddBattleLog("%s uso %s contra: %s", v->name, v->moves[attackIndex].name,playerTeam->veyxInventory[targetIndex].name);
                AddBattleLog("Causo %d de daño a %s",v->resultDamage.damageDone, playerTeam->veyxInventory[targetIndex].name);
                if(!IsVeyxAlive(&playerTeam->veyxInventory[targetIndex]))
                    playerTeam->veyxAlive--;
                if(UseDice)
                    currentPhaseNPC = FIGHT_DICE_ROLL;
                else
                    currentPhaseNPC = FIGHT_END_TURN;
            }            
        } break;
        case FIGHT_END_TURN:
        {
            RemoveDeadEnemies(veyxQueue);
            ProcessAndRequeue(veyxQueue, IsVeyxAlive);
            turnInit = true;
            IsButtonPressed[0] = false;
            currentPhaseNPC = FIGHT_SELECT_ATTACK;
            attackTimerNPC = 0.f;
        } break;
        case FIGHT_DICE_ROLL:
        {
            DiceType diceSelectedNPC = GetRandomDice(&npc->inventory);
            size_t roll = RollDice(diceSelectedNPC);
            size_t threshold = (diceSelectedNPC / 2);
            if (roll >= threshold)
            {
                playerTeam->veyxInventory[targetIndex].status = v->moves[attackIndex].statusToApply;
                playerTeam->veyxInventory[targetIndex].statusRounds = (size_t)((rand() % 3) + 1);
                if(playerTeam->veyxInventory[targetIndex].status == STATUS_FREEZE || playerTeam->veyxInventory[targetIndex].status == STATUS_STUN)
                {
                    TraceLog(LOG_INFO, "NPC: PlayerVeyx has status %s",playerTeam->veyxInventory[targetIndex].name);
                }
            }
            else 
                playerTeam->veyxInventory[targetIndex].status = STATUS_NONE;
            UseDice = false;
            currentPhaseNPC = FIGHT_END_TURN;
        } break;
    }///< End Switch
}

int GetRandomAliveVeyx(Veyx veyxInventory[], size_t count)
{
    size_t aliveCount = 0;
    for (size_t i = 0; i < count; i++)
    {
        if (veyxInventory[i].life > 0)
            aliveCount++;
    }

    if (aliveCount == 0) return -1;
    size_t target = rand() % aliveCount;

    for (size_t i = 0; i < count; i++)
    {
        if (veyxInventory[i].life > 0)
        {
            if (target == 0) return (int)i;
            target--;
        }
    }

    return -1;
}

DiceType GetRandomDice(Inventory* self)
{
    size_t diceToSelect = (rand() % 7);
    DiceType dice = D4;

    if(self->object[diceToSelect].dice.amount > 0)
    {
        dice = self->object[diceToSelect].dice.type;
        self->object[diceToSelect].dice.amount--;
    }
    
    return dice;
}

void RemoveDeadEnemies(Queue* q)
{
    Queue temp = {0};
    Item* current;

    while (!QueueEmpty(*q)) {
        current = DequeueItem(q);
        AssertNotNull(current,"Current from DequeueItem is NULL","current");
        Veyx* e = (Veyx*)current->item;

        if (IsVeyxAlive(e))
            AddToQueue(&temp, current);
        else
        {
            // free(e);
            free(current);
        }
    }
    while (!QueueEmpty(temp)) {
        current = DequeueItem(&temp);
        AddToQueue(q, current);
    }
}

bool IsVeyxAlive(void* self)
{
    if(!self)
    {
        AssertNotNull(self,"Item NULL in IsVetxAlive","self");
        return false;
    }
    Veyx* v = (Veyx*)self;
    if(v->life > 0)
        return true;
    else
        return false;
}

bool EndFight(Entity* player, Entity* npc)
{
    if(player->veyxAlive == 0)
        return false;
    if(npc->veyxAlive == 0)
        return true;
}

void ProcessStatus(Queue* self)
{
    Veyx* v = (Veyx*)PeakItem(self);
    TraceLog(LOG_INFO, "statusRounds :%zu",v->statusRounds);
    if(v->statusRounds == 0)
        v->status = STATUS_NONE;
    if(v->statusRounds > 0)
        v->statusRounds --;
    switch (v->status)
    {
        case STATUS_NONE:
            break;
        case STATUS_BURN:
            v->life = (v->life > 20) ? v->life - 20 : 0;
            TraceLog(LOG_INFO, "Burn Veyx");
            break;
        case STATUS_FREEZE:
            v->life = (v->life > 15) ? v->life - 15 : 0;
            ProcessAndRequeue(self,IsVeyxAlive);
            TraceLog(LOG_INFO, "Freeze veyx");
            break;
        case STATUS_POISON:
            v->life = (v->life > 25) ? v->life - 25 : 0;
            TraceLog(LOG_INFO, "Poison Veyx");
            break;
        case STATUS_STUN:
            ProcessAndRequeue(self,IsVeyxAlive);
            TraceLog(LOG_INFO, "Stun veyx");
            break;
        default:
            break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////