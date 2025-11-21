//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Fight.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Public Declarations
Rectangle fontBox[4]; 
Veyx* veyxPriority[8];
FightPhase currentPhase = FIGHT_SELECT_ATTACK;
FightPhase prevPhase = FIGHT_SELECT_ATTACK;
FightPhase currentPhaseNPC = FIGHT_SELECT_ATTACK;
DiceType diceSelected;
size_t diceSelectedToAnimation;
int boxSelected = -1;
bool attSelected;
size_t rollDice;
size_t threshold;
float attackTimer = 0;
float attackTimerDice = 0;
size_t buffAcum;

Texture2D key_R;
Rectangle recKeyR;

bool IsVeyxSelectedCard = false;
bool cardSpecialActived = false;

///< Private Declarations
static int attackSelected = -1;
static int targetSelected = -1;
static bool turnInit;
static size_t turnsToReloadMana = 0;
static size_t turnsToReloadManaNPC = 0;
// static size_t countUseSpecialCard = 0;

static float attackTimerNPC = 0.0f;
static int targetIndex;
static int attackIndex;

Color POLINIZAR_GREEN;
float color[4];
int fadeIntensityLoc;
int fadeColorLoc;
float currentFadeIntensity = 0.0f;
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
    switch (currentPhase)
    {
        case FIGHT_SELECT_ATTACK:
        {
            prevPhase = FIGHT_SELECT_ATTACK;
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
                    if(v->status == STATUS_STUN || v->status == STATUS_FREEZE)
                         ProcessAndRequeue(veyxQueue,IsVeyxAlive);
                    // TraceLog(LOG_INFO, "Player: Attack selected: %s", v->moves[i].name);
                    break;
                }
                else if(IsButtonPressed[1])
                {
                    currentPhase = FIGHT_CARD_SHOW;
                }
            }
        } break;
        case FIGHT_SELECT_TARGET:
        {
            prevPhase = FIGHT_SELECT_TARGET;
            for (size_t i = 0; i < 4; i++)
            {
                if (CheckCollisionPointRec(mouse, fontBox[i]) && IsButtonPressed[0] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    if(i != (size_t)attackSelected)
                        PlaySound(sounds[0]);
                    attackSelected = i;
                    boxSelected = i;
                    attSelected = true;
                    if(v->mana < v->moves[attackSelected].manaCost)
                    {
                        AddBattleLog("%s mana es demasiado bajo para usar este ataque.",v->name);
                        AddBattleLog("%s consume %u y solo tienes %u",v->moves[attackSelected].name,(unsigned int)v->moves[attackSelected].manaCost);
                        attackSelected = -1;
                        boxSelected = -1;
                        attackSelected = false;
                        currentPhase = FIGHT_SELECT_TARGET;
                    }
                    // currentPhase =FIGHT_SELECT_TARGET;
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
            prevPhase = FIGHT_EXECUTE;
            v->resultDamage = ApplyAttack(v, &npcTeam->veyxInventory[targetSelected], &v->moves[attackSelected]);
            AddBattleLog("%s uso %s contra: %s", v->name, v->moves[attackSelected].name,npcTeam->veyxInventory[targetSelected].name);
            AddBattleLog("Causo %d de daño a %s",v->resultDamage.damageDone, npcTeam->veyxInventory[targetSelected].name);
            if(!IsVeyxAlive(&npcTeam->veyxInventory[targetSelected]))
            {
                TraceLog(LOG_INFO, "Player: Veyx Dead %s",npcTeam->veyxInventory[targetSelected].name);
                npcTeam->veyxAlive--;
                RemoveDeadEnemies(veyxQueue);
            }
            if(UseDice && npcTeam->veyxInventory[targetSelected].status == STATUS_NONE && IsVeyxAlive(&npcTeam->veyxInventory[targetSelected]))
            {
                TraceLog(LOG_INFO, "Player: Use Dice");
                currentPhase = FIGHT_DICE_SHOW;
            }
            else
            {
                TraceLog(LOG_INFO, "Player: Cant use Dice, GoTo End_Turn");
                currentPhase = FIGHT_CARD_SHOW;
            }
        } break;
        case FIGHT_END_TURN:
        {
            turnsToReloadMana++;
            attackSelected = -1;
            targetSelected = -1;
            boxSelected = -1;
            attSelected = false;
            IsButtonPressed[0] = false;
            IsButtonPressed[1] = false;
            currentPhase = FIGHT_SELECT_ATTACK;
            IsVeyxSelectedCard = false;
            turnInit = true;
            UseDice = false;
            if(turnsToReloadMana == player->veyxAlive)
            {
                ReloadMana(player->veyxInventory);
                turnsToReloadMana = 0;
            }
            ProcessAndRequeue(veyxQueue,IsVeyxAlive);
            TraceLog(LOG_INFO, "Player: End_Turn");
        } break;
        case FIGHT_DICE_SHOW:
        {
            prevPhase = FIGHT_DICE_SHOW;
            if(IsKeyPressed(KEY_R) || (CheckCollisionPointRec(mouse,recKeyR) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            {
                currentPhase = FIGHT_CARD_SHOW;
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
            prevPhase = FIGHT_DICE_ROLL;
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
                    npcTeam->veyxInventory[targetSelected].statusRounds = (size_t)((rand() % 3) + 1);
                    const char* status = GetStatusToString(npcTeam->veyxInventory[targetSelected].status);
                    AddBattleLog("%s tiene estado de %s",npcTeam->veyxInventory[targetSelected].name,status);
                    AddBattleLog("Por %d turnos",npcTeam->veyxInventory[targetSelected].statusRounds);
                }
                else 
                    npcTeam->veyxInventory[targetSelected].status = STATUS_NONE;
                TraceLog(LOG_INFO, "Player: EndTurn from DiceRoll");
                
                UseDice = false;
                startAnimationDice = true;
                doneAnimationDice = false;
            }
            if(doneAnimationDice)
            {
                doneAnimationDice = false;
                startAnimationDice = true;
                currentPhase = FIGHT_CARD_SHOW;
            }
        } break;
        case FIGHT_CARD_SHOW:
        {
            UpdateCardSelector();

            IsVeyxSelectedCard = ApplyCardEffect(veyxPriority);
            if(IsVeyxSelectedCard)
                currentPhase = FIGHT_END_TURN;
            if(IsKeyPressed(KEY_Q) && (prevPhase != FIGHT_DICE_ROLL && prevPhase != FIGHT_DICE_SHOW) && prevPhase != FIGHT_EXECUTE)
                currentPhase = prevPhase;
            // if(IsKeyPressed(KEY_Q) && prevPhase != FIGHT_SELECT_TARGET)
            if(IsKeyPressed(KEY_R) && prevPhase != FIGHT_SELECT_ATTACK)
                currentPhase = FIGHT_END_TURN;
        }break;
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
            if(!IsVeyxAlive(v))
            {
                npc->veyxAlive --;
            }
            if(v->status == STATUS_STUN || v->status == STATUS_FREEZE)
            {
                ProcessAndRequeue(veyxQueue,IsVeyxAlive);
            }
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
                {    
                    RemoveDeadEnemies(veyxQueue);
                    playerTeam->veyxAlive--;
                }
                if(UseDice && playerTeam->veyxInventory[targetIndex].status == STATUS_NONE && IsVeyxAlive(&playerTeam->veyxInventory[targetIndex]))
                    currentPhaseNPC = FIGHT_DICE_ROLL;
                else
                    currentPhaseNPC = FIGHT_CARD_SHOW;
            }            
        } break;
        case FIGHT_END_TURN:
        {
            ProcessAndRequeue(veyxQueue, IsVeyxAlive);
            turnInit = true;
            turnsToReloadManaNPC++;
            IsButtonPressed[0] = false;
            if(turnsToReloadManaNPC == npc->veyxAlive)
            {
                ReloadMana(npc->veyxInventory);
                turnsToReloadManaNPC = 0;
            }
            if (npc->hasSpecialCard && npc->cooldownSpecialCard > 0)
            {
                npc->cooldownSpecialCard--;
            }
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
                const char* status = GetStatusToString(playerTeam->veyxInventory[targetIndex].status);
                AddBattleLog("%s tiene estado de %s",playerTeam->veyxInventory[targetIndex].name,status);
                AddBattleLog("Por %d turnos",playerTeam->veyxInventory[targetIndex].statusRounds);
            }
            else 
                playerTeam->veyxInventory[targetIndex].status = STATUS_NONE;
            UseDice = false;
            currentPhaseNPC = FIGHT_CARD_SHOW;
        } break;
        case FIGHT_CARD_SHOW:
        {
            bool actionTaken = false;
            if( npc->hasSpecialCard && npc->cooldownSpecialCard == 0 && buffAcum > 0)
            {
                ActiveCardSpecial(npc->veyxInventory,playerTeam->veyxInventory,&npc->inventory.object[13].card);
                npc->cooldownSpecialCard = npc->inventory.object[13].card.cooldown;
                actionTaken = true;
                cardSpecialActived = true; 
                buffAcum--;
                currentPhaseNPC = FIGHT_END_TURN;
            }
            if(!actionTaken)
            {    
                actionTaken = UseCard(&npc->inventory,&playerTeam->inventory,npc->veyxInventory,playerTeam->veyxInventory);
            }
            if(actionTaken)
            {
                TraceLog(LOG_INFO,"ActionTaken == True");
                currentPhaseNPC = FIGHT_END_TURN;
            }
        }break;
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

void ReloadMana(Veyx* self)
{
    for (size_t i = 0; i < 4; i++)
    {
        if(!IsVeyxAlive(&self[i]))
            continue;
        if(self[i].mana > 75)
            self[i].mana = self[i].maxMana;
        else if(self[i].mana > 50)
            self[i].mana = 75;
        else if(self[i].mana >25)
            self[i].mana = 50;
        else
            self[i].mana = 25;
    }
}

bool UseCard(Inventory* inv,Inventory* player,Veyx* npcVeyxInv,Veyx* playerVeyxInv)
{
    AvailableCard bestCard = { -1, NULL};

    for (size_t i = 0; i < inv->amountObj; i++)
    {
        if (inv->object[i].type != OBJ_CARD) continue;

        Card* c = &inv->object[i].card;
        
        if (c->type == CARD_HEAL)
        {
            for (size_t j = 0; j < 4; j++)
            {
                Veyx* currentVeyx = &npcVeyxInv[j];

                if (currentVeyx->life > 0 && (float)currentVeyx->life / currentVeyx->maxlife <= LOW_HEALTH_THRESHOLD)
                {
                    bestCard.invIndex = (int)i;
                    bestCard.card = c;
                    
                    inv->object[i].accion(c, currentVeyx);
                    // currentPhaseNPC = FIGHT_END_TURN;
                    return true;
                }
            }
        }
        
        if (bestCard.card == NULL)
        {
            if (c->type >= CARD_DEBUFF_DEFESE && c->type <= CARD_CLEANSE)
            {
                if (bestCard.card == NULL || c->rarity > bestCard.card->rarity)
                {
                    bestCard.invIndex = (int)i;
                    bestCard.card = c;
                }
            }
        }
    }
    
    if (bestCard.card != NULL)
    {
        Veyx* target = NULL;
        
        if (bestCard.card->type >= CARD_BUFF_DEFENSE)
        {
            int randomSelect = rand() % 4;
            target = &npcVeyxInv[randomSelect]; 
        }
        else
        {
            int randomSelect = rand() % 4;
            target = &playerVeyxInv[randomSelect]; 
        }

        if (target != NULL && IsVeyxAlive(target))
        {
            inv->object[bestCard.invIndex].accion(bestCard.card, target);
            // currentPhaseNPC = FIGHT_END_TURN;
            return true;
        }
    }
    return true;
    // currentPhaseNPC = FIGHT_END_TURN;
}

void ActiveCardSpecial(Veyx* npcVeyxInv, Veyx* playerVeyxInv, Card* c)
{
    const int ATTACK_BUFF = 5;
    const int VEYX_PER_TEAM = 4;
    
    Veyx* teamArrays[] = { npcVeyxInv, playerVeyxInv };
    int buffsAppliedCount = 0;
    
    for (int i = 0; i < 2; i++) 
    {
        Veyx* currentTeam = teamArrays[i];
        for (int j = 0; j < VEYX_PER_TEAM; j++) 
        {
            Veyx* v = &currentTeam[j]; 
            
            if (IsVeyxAlive(v) && (v->type[0] == vT_GRASS || v->type[1] == vT_GRASS))
            {
                v->physical_attack += ATTACK_BUFF;
                v->magic_attack += ATTACK_BUFF;
                
                AddBattleLog("%s (Planta) recibe +%d de ataque.", v->name, ATTACK_BUFF); 

                buffsAppliedCount++;
            }
        }
    }
    if (buffsAppliedCount > 0)
    {
        AddBattleLog("La carta Polinizar ha potenciado a %d Veyx tipo Planta.", buffsAppliedCount);
    }
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

    if (v->status == STATUS_NONE)
        return;
    switch (v->status)
    {
        case STATUS_NONE:
            break;
        case STATUS_BURN:
            AddBattleLog("A %s le bajo %d de vida por %s",v->name,20,GetStatusToString(v->status));
            v->life = (v->life > 20) ? v->life - 20 : 0;
            TraceLog(LOG_INFO, "Burn Veyx");
            break;
        case STATUS_FREEZE:
            AddBattleLog("A %s le bajo %d de vida por %s",v->name,15,GetStatusToString(v->status));
            AddBattleLog("%s sigue congelado",v->name);
            v->life = (v->life > 15) ? v->life - 15 : 0;
            TraceLog(LOG_INFO, "Freeze veyx");
            break;
        case STATUS_POISON:
            AddBattleLog("A %s le bajo %d de vida por %s",v->name,25,GetStatusToString(v->status));
            v->life = (v->life > 25) ? v->life - 25 : 0;
            TraceLog(LOG_INFO, "Poison Veyx");
            break;
        case STATUS_STUN:
            AddBattleLog("%s esta paralizado",v->name);
            TraceLog(LOG_INFO, "Stun veyx");
            break;
        default:
            break;
    }
    if (v->life == 0)
        v->statusRounds = 0;
    if (v->life > 0 && v->statusRounds > 0)
        v->statusRounds--;
    if (v->statusRounds == 0)
        v->status = STATUS_NONE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////