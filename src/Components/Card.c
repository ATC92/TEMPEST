///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Card.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Texture2D cards[CARD_MAX_TYPES];
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitCard()
{
    cards[CARD_HEAL] = LoadTexture(ASSETS"/Card/Heal.png");
    cards[CARD_DEBUFF_DEFESE] = LoadTexture(ASSETS"/Card/Debuff_Defense.png");
    cards[CARD_BUFF_DEFENSE] = LoadTexture(ASSETS"/Card/Buff_Defense.png");
    // cards[CARD_DEBUFF_SPEED] = LoadTexture(ASSETS"Card/.png");
    // cards[CARD_BUFF_SPEED] = LoadTexture(ASSETS"Card/.png");
    // cards[CARD_DEBUFF_ATTACK] = LoadTexture(ASSETS"Card/.png");
    // cards[CARD_BUFF_ATTACK] = LoadTexture(ASSETS"Card/.png");
    cards[CARD_CLEANSE] = LoadTexture(ASSETS"/Card/Cleanse.png");
    cards[CARD_SPECIAL_POLINIZAR] = LoadTexture(ASSETS"/Card/Polinizar.png");
}

Card LoadCard(const CardType type)
{
    Card temp = {0};
    switch (type)
    {
    case CARD_HEAL:
        strcpy(temp.name,"Curacion");
        temp.cardTexture = &cards[type];
        strcpy(temp.descEffect,"Cura al veyx seleccionado en 20 puntos. (Depende el nivel incrementa la curacion)");
        temp.rarity = NORMAL;
        temp.sizeCard = (Rectangle){.x=0,.y=0,.width = temp.cardTexture->width, .height = temp.cardTexture->height};
        temp.cooldown = 0;
        temp.actionCard = ACTION_CARD_TEAM;
        temp.type = type;
        temp.amount = 5;
        break;
    case CARD_DEBUFF_DEFESE:
        strcpy(temp.name,"Fractura");
        temp.cardTexture = &cards[type];
        strcpy(temp.descEffect,"Disminuye la defensa del veyx seleccionado en 25 puntos. (Depende el nivel incrementa el debuff)");
        temp.rarity = NORMAL;
        temp.sizeCard = (Rectangle){.x=0,.y=0,.width = temp.cardTexture->width, .height = temp.cardTexture->height};
        temp.cooldown = 0;
        temp.actionCard = ACTION_CARD_ENEMY;
        temp.type = type;
        temp.amount = 5;
        break;
    case CARD_BUFF_DEFENSE:
        strcpy(temp.name,"Fortaleza");
        temp.cardTexture = &cards[type];
        strcpy(temp.descEffect,"Aumenta la defensa del Veyx seleccionado en 25 puntos. (Depende el nivel incrementa el buff)");
        temp.rarity = NORMAL;
        temp.sizeCard = (Rectangle){.x=0,.y=0,.width = temp.cardTexture->width, .height = temp.cardTexture->height};
        temp.cooldown = 0;
        temp.actionCard = ACTION_CARD_TEAM;
        temp.type = type;
        temp.amount = 5;
        break;
    case CARD_CLEANSE:
        strcpy(temp.name,"Purificacion");
        temp.cardTexture = &cards[type];
        strcpy(temp.descEffect,"Limpia el estado del veyx seleccionado. (Probabilidad de curar si el nivel de la carta es alta)");
        temp.rarity = NORMAL;
        temp.sizeCard = (Rectangle){.x=0,.y=0,.width = temp.cardTexture->width, .height = temp.cardTexture->height};
        temp.cooldown = 0;
        temp.actionCard = ACTION_CARD_TEAM;
        temp.type = type;
        temp.amount = 5;
        break;
    default:
        TraceLog(LOG_INFO,"Default in LoadCard");
        break;
    }
    return temp;
}

Card LoadSpecialCard(const TypeNPC type)
{
    Card temp = {0};
    switch (type)
    {
    case _NPC_MIKA:
        strcpy(temp.name,"Polinizar");
        strcpy(temp.descEffect,"Todos los veyx tipos Planta en el campo RECIBIRÁN +5 en ataque magico y fisico. Esta carta se puede acumular y tiene cooldown de 4 turnos.");
        temp.actionCard = ACTION_CARD_ALL;
        temp.rarity = SUPER_EXTRA_RARE;
        temp.type = CARD_SPECIAL_POLINIZAR;
        temp.amount = 1;
        temp.cardTexture = &cards[CARD_SPECIAL_POLINIZAR];
        temp.cooldown = 4;
        break;
    
    default:
        break;
    }
    return temp;
}

const char* GetCardRarityToString(Rarity rarity)
{
    switch (rarity)
    {
    case NORMAL:
        return "Normal";
        break;
    case RARE:
        return "Raro";
        break;
    case SUPER_RARE:
        return "Super Raro";
        break;
    case SUPER_EXTRA_RARE:
        return "Super Extra raro";
        break;
    default:
        return "Desconocido";
        break;
    }
}

const char* GetCardTypeToString(CardType type)
{
    switch (type)
    {
    case CARD_HEAL:
        return "Curacion";
        break;
    case CARD_DEBUFF_DEFESE:
    case CARD_DEBUFF_SPEED:
    case CARD_DEBUFF_ATTACK:
        return "Debilitamiento";
        break;
    case CARD_BUFF_DEFENSE:
    case CARD_BUFF_SPEED:
    case CARD_BUFF_ATTACK:
        return "Mejora";
        break;
    case CARD_CLEANSE:
        return "Purifiacion";
        break;
    case CARD_SPECIAL_POLINIZAR:
        return "Unica";
        break;
    default:
        return "Desconocido";
        break;
    }
}

void FnAccionCard(void* self, void* dest)
{
    Card* c = (Card*)self;
    Veyx* v = (Veyx*)dest;
    switch (c->type)
    {
    case CARD_HEAL:
    {
        const int BASE_HEAL = 20;
        size_t bonusHeal = 0;
        switch (c->rarity)
        {
            case RARE:
                bonusHeal = 10;
                break;
            case SUPER_RARE:
                bonusHeal = 15;
                break;
            case SUPER_EXTRA_RARE:
                bonusHeal = 25;
                break;
            default:
                bonusHeal = 0;
                break;
        }
        
        int actualHeal = BASE_HEAL + bonusHeal;
        v->life = min(v->life + actualHeal, v->maxlife);
        AddBattleLog("%s se a curado %d puntos de vida.",v->name, actualHeal);
    }break;
    case CARD_DEBUFF_DEFESE:
    {
        const int BASE_DEBUFF_DEFENSE = 10;
        size_t debuffBonus;
        switch (c->rarity)
        {
        case RARE:
            debuffBonus = 5;
            break;
        case SUPER_RARE:
            debuffBonus = 8;
            break;
        case SUPER_EXTRA_RARE:
            debuffBonus = 15;
            break;
        default:
            debuffBonus = 0;
            break;
        }
        int actualDebuffDefense = BASE_DEBUFF_DEFENSE + debuffBonus;
        int newDefense = (int)v->defense - actualDebuffDefense;
        if (newDefense < 0)
        {
            newDefense = 0;
        }
        v->defense = (uint8_t)newDefense;
        // v->defense = ((int)v->defense - actualDebuffDefense) < 0 ? (uint8_t)0 : v->defense - actualDebuffDefense;
        AddBattleLog("%s le a disminuido la defensa en %d puntos.",v->name,actualDebuffDefense);
    }break;
    case CARD_DEBUFF_SPEED:
    case CARD_DEBUFF_ATTACK:
        break;
    case CARD_BUFF_DEFENSE:
    {
        const int BASE_BUFF_DEFENSE = 8;
        size_t buffBonus;
        switch (c->rarity)
        {
        case RARE:
            buffBonus = 5;
            break;
        case SUPER_RARE:
            buffBonus = 8;
            break;
        case SUPER_EXTRA_RARE:
            buffBonus = 15;
            break;
        default:
            buffBonus = 0;
            break;
        }
        int actualBuffDefense = BASE_BUFF_DEFENSE + buffBonus;
        v->defense = min(v->defense + actualBuffDefense,v->maxDefense);
        AddBattleLog("%s a aumentado su defensa en %d puntos.",v->name,actualBuffDefense);
    }break;
    case CARD_BUFF_SPEED:
    case CARD_BUFF_ATTACK:
        break;
    case CARD_CLEANSE:
    {
        if(v->status != STATUS_NONE)
        {
            AddBattleLog("%s se le a eliminado el estatus %s",v->name,GetStatusToString(v->status));
            v->status = STATUS_NONE;
        }
    }break;
    default:
        break;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////