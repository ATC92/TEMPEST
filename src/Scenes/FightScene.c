///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "FightScene.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///< Private
static Button** buttons;
static RenderData** mapData;
static Vector2 bar[3];
static Vector2 foo[3];

static bool IsButtonsPressed[3];
static bool IsMouseOver[3];
static bool whoWins;
static bool animationDoce;

static Queue veyxQueue;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitFightScene(void)
{
    ///< Paths Textures
    char* Path1 = ASSETS"/UI/Buttons/button_rectangle_depth_line.png";
    char* Path2 = ASSETS "/UI/Buttons/button_rectangle_line.png";
    ///< Memory allocation for buttons
    buttons = (Button**)calloc(3,sizeof(Button*));
    buttons[_BTT_ATTACK]     =  CreateButton(Path1,Path2,(Vector2){340, (float)GetScreenHeight() - 150});
    buttons[_BTT_INVENTORY]  =  CreateButton(Path1,Path2,(Vector2){770, (float)GetScreenHeight() - 150});
    buttons[_BTT_EXIT]       =  CreateButton(Path1,Path2,(Vector2){1200, (float)GetScreenHeight() - 150});

    strcpy(buttons[_BTT_ATTACK]->name,"Ataque");
    strcpy(buttons[_BTT_INVENTORY]->name,"Inventario");
    strcpy(buttons[_BTT_EXIT]->name,"Salir");

    ///< Measure Text
    bar[0] = MeasureTextEx(fontType, "Ataque", 40, 0);
    bar[1] = MeasureTextEx(fontType, "Invetario", 40, 0);
    bar[2] = MeasureTextEx(fontType, "Salir", 40, 0);
    foo[0] = (Vector2)
    {
        .x = (buttons[_BTT_ATTACK]->destinationButton.x + buttons[_BTT_ATTACK]->destinationButton.width / 2) - bar[0].x / 2,
        .y = (buttons[_BTT_ATTACK]->destinationButton.y + buttons[_BTT_ATTACK]->sourceButton.height / 2) - bar[0].y / 2
    };    
    foo[1] = (Vector2)
    {
        .x = (buttons[_BTT_INVENTORY]->destinationButton.x + buttons[_BTT_INVENTORY]->destinationButton.width / 2) - bar[1].x / 2,
        .y = (buttons[_BTT_INVENTORY]->destinationButton.y + buttons[_BTT_INVENTORY]->sourceButton.height / 2) - bar[1].y / 2
    };    
    foo[2] = (Vector2)
    {
        .x = (buttons[_BTT_EXIT]->destinationButton.x + buttons[_BTT_EXIT]->destinationButton.width / 2) - bar[2].x / 2,
        .y = (buttons[_BTT_EXIT]->destinationButton.y + buttons[_BTT_EXIT]->sourceButton.height / 2) - bar[2].y / 2
    };

    ///< Texture Load
    key_R = LoadTexture(ASSETS"/UI/Keys/Black/R.png");
    ///< Bool variables init
    IsFightRuning = false;
    FightBattleEnds = false;
    ///< Init Maps for Fights
    mapData = (RenderData**)calloc(1,sizeof(RenderData*));
    mapData[_MP_MIKA] = LoadInformationMap(ASSETS"/Tilemap/MikaFight.png",ASSETS"/Maps/FightMaps/MikaMap_Ground.csv",ASSETS"/Maps/FightMaps/MikaMap_Mid.csv",ASSETS"/Maps/FightMaps/MikaMap_Top.csv",NULL);

    ///< Init Queue
    InitQueue(&veyxQueue,8);

    Rectangle sizeArea = {.x=GetScreenWidth()/2 - 250,.y=GetScreenHeight()/2 + 250,.width=500,.height=250};
    InitCardSelector(&eplayer->inventory,sizeArea);

    POLINIZAR_GREEN = (Color){ 0, 192, 0, 255 };
    color[0] = (float)POLINIZAR_GREEN.r / 255.0f;
    color[1] = (float)POLINIZAR_GREEN.g / 255.0f;
    color[2] = (float)POLINIZAR_GREEN.b / 255.0f;
    color[3] = (float)POLINIZAR_GREEN.a / 255.0f;
    
    fadeIntensityLoc = GetShaderLocation(shaders[S_MIKA_SPECIAL_CARD], "fadeIntensity");
    fadeColorLoc = GetShaderLocation(shaders[S_MIKA_SPECIAL_CARD], "fadeColor");
    animationDoce = false;
}

void UpdateRenderFight(void)
{
    BeginMode2D(camera);
    {
        RenderTileMap(mapData[_MP_MIKA],LAYER_1);
        RenderEntity(eplayer);
        RenderEntity(entityPool[tNPCSCoop]);

        DrawVeyxTeam(eplayer);
        DrawVeyxTeam(entityPool[tNPCSCoop]);

        RenderTileMap(mapData[_MP_MIKA],LAYER_2);
        RenderTileMap(mapData[_MP_MIKA],LAYER_3);

        if(currentPhase == FIGHT_SELECT_TARGET)
        {
            for (size_t i = 0; i < 4; i++)
            {
                if(entityPool[tNPCSCoop]->veyxInventory[i].life > 0)
                    DrawRectangleLinesEx(entityPool[tNPCSCoop]->veyxInventory[i].sizeInFight,.5f,RED);
            }
        }
        if(IsFightRuning)
            DrawCurrentPhase(&veyxQueue);
        if(startAnimationDice)
        {
            CustomScale(0.5f);
            DrawSpriteAnimationPro(&diceAnimations[diceSelectedToAnimation],(Vector2){.x=285, .y=130},0.f,(Vector2){0,0}
            ,WHITE,19,128,128);
            DrawRectangleLinesEx((Rectangle){.x=285, .y=130, .width=64,.height = 64},0.5f,RED);
            CustomScale(1.f);
        }
        if(doneAnimationDice)
        {
            attackTimer+=GetFrameTime();
            if(attackTimer<=1.5f)
            {
                CustomScale(0.5f);
                DrawSpriteAnimationPro(&diceAnimations[diceSelectedToAnimation],(Vector2){.x=285, .y=130},0.f,(Vector2){0,0}
                ,WHITE,19,128,128);
                DrawRectangleLinesEx((Rectangle){.x=285, .y=130, .width=64,.height = 64},0.5f,RED);
                CustomScale(1.f);
                Vector2 posText;
                if(rollDice < 9)
                    posText = (Vector2){.x = 305,.y = 135};
                else 
                    posText = (Vector2){.x = 290,.y = 135};
                DrawTextPro(fontType,TO_STRING(rollDice),posText,(Vector2){0,0},0.f,60,0,WHITE);
                IsMouseOver[0] = false;
                IsMouseOver[1] = false;
                IsMouseOver[2] = false;
                animationDoce = true;
            }
        }
        if(!IsVeyxSelectedCard && currentPhase == FIGHT_CARD_SHOW && IsCardSelected != -1)
        {
            for (size_t i = 0; i < 8; i++)
            {
                if(IsVeyxAlive(veyxPriority[i]) && eplayer->inventory.object[IsCardSelected].card.actionCard == ACTION_CARD_TEAM && veyxPriority[i]->owner == _PLAYER)
                    DrawRectangleLinesEx(veyxPriority[i]->sizeInFight,.5f,BLUE);
                else if(IsVeyxAlive(veyxPriority[i]) && eplayer->inventory.object[IsCardSelected].card.actionCard == ACTION_CARD_ENEMY && veyxPriority[i]->owner == _NPC)
                    DrawRectangleLinesEx(veyxPriority[i]->sizeInFight,.5f,RED);
                else if(IsVeyxAlive(veyxPriority[i]) && eplayer->inventory.object[IsCardSelected].card.actionCard == ACTION_CARD_ALL)
                    DrawRectangleLinesEx(veyxPriority[i]->sizeInFight,.5f,LIME);

            }        
        }
    }
    EndMode2D();
    if(currentPhase == FIGHT_CARD_SHOW && (doneAnimationDice || !startAnimationDice))
    {
        DrawCardSelector();
        DrawInformationCard();
    }

    ///< BattleLog for the battle
    DrawRectangleRec((Rectangle){.x=GetScreenWidth()/2 - 200, .y=160, .width=400, .height=150}, Fade(BLACK, 0.5f));
    DrawBattleLog((Vector2){GetScreenWidth()/2 - 160, 180});

    ///< Buttons
    if(currentPhase != FIGHT_DICE_SHOW && currentPhase != FIGHT_CARD_SHOW && currentPhase != FIGHT_DICE_ROLL)
    {
        DrawButton(buttons[_BTT_ATTACK],"Ataque",foo[0],fontType,40,BLACK);
        DrawButton(buttons[_BTT_EXIT],"Salir",foo[2],fontType,40,BLACK);
        DrawButton(buttons[_BTT_INVENTORY],"Inventario",foo[1],fontType,40,BLACK);
    }
    /// Priority Layer
    DrawRectangleRec((Rectangle){.x=GetScreenWidth()/2 - 300,.y= 60,.width=600,.height=70},GRAY);
    DrawHeadVeyx(&veyxQueue,(Vector2){.x = GetScreenWidth()/2 - 300,.y = 60});
    
    ///< Team Status
    DrawTeamStatus(eplayer,entityPool[tNPCSCoop]);

    ///< DiceShow if UseDice == true
    if(currentPhase == FIGHT_DICE_SHOW)
    {
        Rectangle source = (Rectangle){
            .x = 0,
            .y = 0,
            .width = key_R.width,
            .height = key_R.height
        };
        Rectangle dest = (Rectangle){
            .x = GetScreenWidth()/2 - (source.width * 3.f)/2,
            .y = 820,
            .width = source.width * 3.f,
            .height = source.height * 3.f 
        };
        timeShader += GetFrameTime();

        float speed = 0.50f;
        float width = 0.5f;
        float intensity = 0.5f;
        Vector3 color = {1.0f, 1.0f, 1.0f};
        float offset = 0.0f;

        SetShaderValue(shaders[S_SHIELDGLOW], locDirection, &(Vector2){ 1.0f, 0.0f }, SHADER_UNIFORM_VEC2);
        SetShaderValue(shaders[S_SHIELDGLOW], locTime, &timeShader, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locSpeed, &speed, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locWidth, &width, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locIntensity, &intensity, SHADER_UNIFORM_FLOAT);
        SetShaderValue(shaders[S_SHIELDGLOW], locColor, &color, SHADER_UNIFORM_VEC3);
        SetShaderValue(shaders[S_SHIELDGLOW], locOffset, &offset, SHADER_UNIFORM_FLOAT);

        BeginShaderMode(shaders[S_SHIELDGLOW]);
        {
            DrawTexturePro(key_R,source,dest,(Vector2){0,0},0.f,WHITE);
        }
        EndShaderMode();
        ///< TextPart
        Vector2 bar = {0};
        Vector2 foo = {0};
        Vector2 foo2 = {0};

        bar = MeasureTextEx(fontType,"Presiona ",60,0);
        foo = (Vector2){
            .x = dest.x - bar.x,
            .y = dest.y
        };
        DrawTextPro(fontType,"Presiona",foo,(Vector2){0,0},0,60,0,WHITE);
        
        // bar2 = MeasureTextEx(fontType,"  para omitir",60,0);
        foo2 = (Vector2){
            .x = dest.x + dest.width + 20,
            .y = dest.y
        };
        DrawTextPro(fontType,"para omitir",foo2,(Vector2){0,0},0.f,60,0.f,WHITE);
        ///< Icons part
        Rectangle base = {
            .x = 500,
            .y = (float)GetScreenHeight() - 180,
            .width = 920,
            .height = 170
        };
        Vector2 pos = {.x = base.x + 50, .y = base.y + 20};
        DrawRectangleRec(base,GRAY);
        for(size_t i=0; i<6; i++)
        {
            DrawDiceIcons(&eplayer->inventory.object[i].dice,&pos);
            pos.x += 140;
        }
        recKeyR = (Rectangle){.x = foo.x, .y = foo.y, .width = foo.x + 20, .height = dest.height};
    #if DEBUG
        DrawRectangleLinesEx(recKeyR,1.f,RED);
    #endif
    }

    ///< Interaction Buttons
    for(size_t i=0; i<3; i++)
    {
        if(IsMouseOver[i] && !IsButtonsPressed[i] && currentPhase == FIGHT_SELECT_ATTACK && !FightBattleEnds)
        {
            BeginShaderMode(shaders[S_INVERT]);
                DrawTexturePro(buttons[i]->Texture[1],buttons[i]->sourceButton,buttons[i]->destinationButton,(Vector2){0,0},0,WHITE);
                DrawTextEx(fontType,buttons[i]->name,foo[i],40,0,BLACK);
            EndShaderMode();
        }
    }
    /// Attack Moment 
    if(IsButtonsPressed[0] && !UseDice && currentPhase != FIGHT_CARD_SHOW && !FightBattleEnds)
    {
        Rectangle base = {
            .x = 300,
            .y = (float)GetScreenHeight() - 180,
            .width = 1400,
            .height = 170
        };
        DrawRectangleRec(base, LIGHTGRAY);

        float margin = 10;
        float boxWidth = (base.width - margin * 5) / 4.0f;
        float boxHeight = base.height - margin * 2;

        Item* item = Peak(&veyxQueue);
        AssertNotNull(item,"PeakItem is NULL, in FightScene","item");

        Veyx* v = (Veyx*)item->item;
        AssertNotNull(v,"Item cast is null to Veyx* in FightScene","v");
        for (int i = 0; i < 4; i++)
        {
            Rectangle box = {
                .x = base.x + margin + i * (boxWidth + margin),
                .y = base.y + margin,
                .width = boxWidth,
                .height = boxHeight
            };

            DrawRectangleRec(box, GRAY);
            DrawRectangleLinesEx(box, 2, DARKGRAY);

            if (i < 2 && strlen(v->moves[i].name) != 0)
            {
                Vector2 textSize = MeasureTextEx(fontType, v->moves[i].name, 40, 0);
                Vector2 textPos = {
                    .x = box.x + (box.width - textSize.x) / 2,
                    .y = box.y + (box.height - textSize.y) / 2
                };
                fontBox[i] = box;

                if (attSelected && i == boxSelected)
                {
                    BeginShaderMode(shaders[S_INVERT]);
                        DrawRectangleLinesEx(fontBox[i], 2.f, LIME);
                        DrawTextEx(fontType, v->moves[i].name, textPos, 40, 0, BLACK);
                    EndShaderMode();
                }
                else
                {
                    DrawRectangleLinesEx(fontBox[i], 2.f, LIME);
                    DrawTextEx(fontType, v->moves[i].name, textPos, 40, 0, BLACK);
                }
            }
        }    
    }///< EndIf (IsButtonsPressed)

    if(FightBattleEnds)
    {
        whoWins = EndFight(eplayer,entityPool[tNPCSCoop]);

        if(whoWins)/// Player Wins
        {
            Vector2 pos = MeasureTextEx(fontType,"GANASTE",100,0);
            Vector2 foo = (Vector2){.x = GetScreenWidth()/2 - pos.x / 2, .y = GetScreenHeight()/2 - pos.y / 2};
            DrawRectanglePro((Rectangle){.x = GetScreenWidth()/2 - 300,.y = GetScreenHeight()/2 - 70,.width=600,.height=200},(Vector2){0,0},0,BLACK);
            DrawTextPro(fontType,"GANASTE",foo,(Vector2){0,0},0,100,0,PINK);

            Vector2 posOut = MeasureTextEx(fontType,"Presiona  Q  para salir",40,0);
            Vector2 fooOut = (Vector2){.x = GetScreenWidth()/2 - posOut.x / 2, .y = GetScreenHeight()/2 - posOut.y / 2 + 80};
            DrawTextPro(fontType,"Presiona  Q  para salir",fooOut,(Vector2){0,0},0,40,0,WHITE);
        }
        else
        {
            Vector2 pos = MeasureTextEx(fontType,"PERDISTE",100,0);
            Vector2 foo = (Vector2){.x = GetScreenWidth()/2 - pos.x /2 , .y = GetScreenHeight()/2 - pos.y / 2};
            DrawRectanglePro((Rectangle){.x = GetScreenWidth()/2 - 300,.y = GetScreenHeight()/2 - 70,.width=600,.height=200},(Vector2){0,0},0,BLACK);
            DrawTextPro(fontType,"PERDISTE",foo,(Vector2){0,0},0,100,0,PINK);
            
            Vector2 posOut = MeasureTextEx(fontType,"Presiona  Q  para salir",40,0);
            Vector2 fooOut = (Vector2){.x = GetScreenWidth()/2 - posOut.x / 2, .y = GetScreenHeight()/2 - posOut.y / 2 + 80};
            DrawTextPro(fontType,"Presiona  Q  para salir",fooOut,(Vector2){0,0},0,40,0,WHITE);
        }
    }
    
    // Vector2 temp ={.x = GetScreenWidth()/2, .y=GetScreenHeight()/2};
    // DrawTextureEx(*eplayer->inventory.object[6].card.cardTexture,temp,0.f,1.f,WHITE);
    // DrawTextureEx(*selector.inv->object[6].card.cardTexture,temp,0.f,1.f,WHITE);
}

void UpdateLogicFight(void)
{
    if(!IsFightRuning || IsKeyPressed(KEY_Q))
    {
        IsButtonsPressed[0] = false;
        IsButtonsPressed[1] = false;
        IsButtonsPressed[2] = false;
    }
    if(IsVeyxPriorityInit)
    {
        AddVeyxToPriorityList(veyxPriority,eplayer,entityPool[tNPCSCoop]);
        qsort(veyxPriority, 8, sizeof(Veyx*), CompareSpeed);
        for(size_t i=0; i<8; i++)
        {
            AddItem(&veyxQueue, veyxPriority[i]);
        }
        IsVeyxPriorityInit = false;
        FightBattleEnds = false;
        buffAcum = entityPool[tNPCSCoop]->inventory.object[10].card.cooldown;
    }
    ///< Update BattleLog
    UpdateBattleLog(GetFrameTime());

    ////< System Fight
    SystemFight(&veyxQueue,eplayer,entityPool[tNPCSCoop],IsButtonsPressed);

    SyncCollisionBox(eplayer);
    SyncCollisionBox(entityPool[tNPCSCoop]);
    SmoothCameraMovement(&camera,0.25,mapData[_NPC_MIKA]->mapsData->size);
    camera.zoom = 3.5f;

    ///< Update Animations
    UpdateAnimation(&entityPool[tNPCSCoop]->spriteAnimation[1],true);
    UpdateAnimation(&eplayer->spriteAnimation[eplayer->eLook],true);

    if(UpdateFightButtons(&veyxQueue,eplayer,entityPool,mouse,buttons,IsMouseOver,IsButtonsPressed,veyxPriority))
        return;

    UpdateEntities(eplayer,entityPool[tNPCSCoop]);

    if(startAnimationDice && diceAnimations[diceSelectedToAnimation].cur != diceAnimations[diceSelectedToAnimation].last)
    {
        UpdateAnimation(&diceAnimations[diceSelectedToAnimation],true);
        IsMouseOver[0] = false;
        IsMouseOver[1] = false;
        IsMouseOver[2] = false;
        IsButtonsPressed[0] = false;
    }
    attackTimerDice += GetFrameTime();
    if (attackTimerDice >= 2.f && diceAnimations[diceSelectedToAnimation].cur == diceAnimations[diceSelectedToAnimation].last)
    {
        startAnimationDice = false;
        doneAnimationDice = true;    
    }
}

void DestroyFightScene(void)
{
    FreeQueue(&veyxQueue);
    DestroySpriteAnimationDice();
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////