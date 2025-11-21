#include "Entity.h"
//////////////////////////////////////////////////////////
/// Entity Pool for NPC's
Entity** entityPool;
/// Main Entity for the player.
Entity* eplayer;

bool PlayerCanMove;
//////////////////////////////////////////////////////////
Entity* GenEntity(TypeEntity _t, char* _n, uint8_t _s)
{
    Entity* _e = (Entity*)calloc(1,sizeof(Entity));                         ///< Generation Entity
    switch (_t)                                                             ///< Selection of the Type to gen.
    {
        case _PLAYER:
            _e->name = strdup(_n);                                          ///< Name of the Entity        
            _e->position = (Vector2){210,160};                              ///< Position of the Entity
            _e->speed = _s;                                              ///< Speed of the Entity
            _e->prev_position = (Vector2){0,0};                             ///< Previous Position of the Entity
            _e->velocity = (Vector2){0,0};                                  ///< Velocity of the Entity
            _e->typeEntity = _PLAYER;                                       ///< Type of Entity             
            _e->boundingBox = (Rectangle){0,0,.width=16,.height=32};         ///< CollisionBox RECT of the Entity
            _e->triggerBox = (Rectangle){-5,-5,.width = 20, .height=36};    ///< TriggerBox for interacctions.       
            _e->eLook = DOWN;                                               ///< Where the entity is looking (Default: DOWN)
            _e->isInteraction = false;
            break;
        case _NPC:
            _e->name = strdup(_n);                                          ///< Name of the Entity
            _e->position = (Vector2){0,0};                              ///< Position of the Entity
            _e->prev_position = (Vector2){0,0};                             ///< Previous Position of the Entity
            _e->typeEntity = _NPC;                                        ///< Type of Entity 
            _e->boundingBox = (Rectangle){0,0,.width = 16,.height=32};         ///< CollisionBox RECT of the Entity
            _e->triggerBox = (Rectangle){-5,-5,.width = 20, .height=36};    ///< TriggerBox for interacctions. 
            break;
        default:
        break;
    }
    return _e;
}
//////////////////////////////////////////////////////////
void UpdateMovement(Entity* eplayer, float dt)
{
    if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))&& !eplayer->isInteraction)
    {
        eplayer->position.x -= eplayer->speed * dt;
        eplayer->isMooving = true;
        if(eplayer->eLook != LEFT)
            eplayer->eLook = LEFT;
    }
    else if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && !eplayer->isInteraction)
    {
        eplayer->position.x += eplayer->speed * dt;
        eplayer->isMooving = true;
        if(eplayer->eLook != RIGHT)
            eplayer->eLook = RIGHT;
    }
    else if((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && !eplayer->isInteraction)
    {
        eplayer->position.y -= eplayer->speed * dt;
        eplayer->isMooving = true;
        if(eplayer->eLook != UP)
            eplayer->eLook = UP;
    }
    else if((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && !eplayer->isInteraction)
    {   
        eplayer->position.y += eplayer->speed * dt;
        eplayer->isMooving = true;
        if(eplayer->eLook != DOWN)
            eplayer->eLook = DOWN;
    }

    if(IsKeyDown(KEY_LEFT_SHIFT) && !eplayer->isInteraction)
    {
        eplayer->speed = 160.f; // Increase speed when shift is held
        eplayer->spriteAnimation[UP].speed = 0.1;
        eplayer->spriteAnimation[DOWN].speed = 0.1;
        eplayer->spriteAnimation[LEFT].speed = 0.1;
        eplayer->spriteAnimation[RIGHT].speed = 0.1;
    }
    else if(IsKeyReleased(KEY_LEFT_SHIFT) && !eplayer->isInteraction)
    {
        eplayer->speed = 120.f; // Reset speed when shift is released
        eplayer->spriteAnimation[UP].speed = 0.2;
        eplayer->spriteAnimation[DOWN].speed = 0.2;
        eplayer->spriteAnimation[LEFT].speed = 0.2;
        eplayer->spriteAnimation[RIGHT].speed = 0.2;
    }

    if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D) || IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S))
    {
        eplayer->isMooving = false;
    }
    
}
//////////////////////////////////////////////////////////
void LoadNPCtoMemory(Entity** pool)
{
    ///< NPC -> Mika 
    pool[_NPC_MIKA] = GenEntity(_NPC,"Mika",90);
    pool[_NPC_MIKA]->spriteAnimation = (SpriteAnimation*)calloc(2,sizeof(SpriteAnimation));
    pool[_NPC_MIKA]->spriteAnimation[0]       = CreateSpriteAnimation(ASSETS "/Entities/Mika/FrontWalk/MikaDown.png",       0,3,1,0.3f,.5f,A_LOOP);
    pool[_NPC_MIKA]->spriteAnimation[1]       = CreateSpriteAnimation(ASSETS "/Entities/Mika/SideWalk/MikaSide.png",       0,3,1,0.3f,.5f,A_LOOP);
    pool[_NPC_MIKA]->eLook = 0;
    pool[_NPC_MIKA]->position = (Vector2){150,150};
    pool[_NPC_MIKA]->prev_position = (Vector2){150,150};
    pool[_NPC_MIKA]->inventory = InitInventory();

    /// Card Special for Mika
    pool[_NPC_MIKA]->inventory.object[10].card = LoadSpecialCard(_NPC_MIKA);
    pool[_NPC_MIKA]->inventory.object[10].accion = FnAccionCard;
    pool[_NPC_MIKA]->inventory.amountObj++;
    pool[_NPC_MIKA]->hasSpecialCard = true;
    LoadVeyxList(pool[_NPC_MIKA]);
    
    ///< NPC -> Arturo
    pool[_NPC_ARTURO] = GenEntity(_NPC,"Arturo",90);
    pool[_NPC_ARTURO]->spriteAnimation = (SpriteAnimation*)calloc(2,sizeof(SpriteAnimation));
    pool[_NPC_ARTURO]->spriteAnimation[0]      = CreateSpriteAnimation(ASSETS "/Entities/Arturo/FrontWalk/ArturoDown.png",     0,3,1,0.3f,.5f,A_LOOP);
    pool[_NPC_ARTURO]->spriteAnimation[1]      = CreateSpriteAnimation(ASSETS "/Entities/Arturo/FrontWalk/ArturoDown.png",     0,3,1,0.3f,.5f,A_LOOP);
    pool[_NPC_ARTURO]->eLook = 0;
    pool[_NPC_ARTURO]->position = (Vector2){.x = 730, .y = 130};
    pool[_NPC_ARTURO]->prev_position = (Vector2){.x = 730, .y = 130};
    pool[_NPC_ARTURO]->inventory = InitInventory();
    LoadVeyxList(pool[_NPC_ARTURO]);
}
//////////////////////////////////////////////////////////
void LoadVeyxList(Entity* entity)
{
    switch (entity->typeEntity)
    {
        case _PLAYER:
            entity->veyxInventory[0] = VeyxRegistry[vL_IGNISQ];
            entity->veyxInventory[1] = VeyxRegistry[vL_MUSHY];
            entity->veyxInventory[2] = VeyxRegistry[vL_DRALIK];
            entity->veyxInventory[3] = VeyxRegistry[vL_WANDRAIL];
            entity->veyxAlive = 4;
            break;
        case _NPC:
            entity->veyxInventory[0] = VeyxRegistry[vL_GODAM];
            entity->veyxInventory[1] = VeyxRegistry[vL_LIGLY];
            entity->veyxInventory[2] = VeyxRegistry[vL_SAPMOSS];
            entity->veyxInventory[3] = VeyxRegistry[vL_DRALIK];
            entity->veyxAlive = 4;
            break;
        default:
            TraceLog(LOG_WARNING,"%s LoadVeyxList Function in Entity.c, Error with typeEntity",entity->name);
            break;
    }
}
//////////////////////////////////////////////////////////
