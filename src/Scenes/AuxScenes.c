///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "AuxScenes.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float minX;
float maxX;
//<<<
static float scrollY = 0.0f;
static const int BAR_WIDTH = 100;
static const int BAR_HEIGHT = 10;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundBarFollowPoint(Button* vN,Rectangle* dot)
{
    // float dotX = bar.x + bar.width/2.0f - dot->width/2.0f;
    // float dotY = bar.y + (bar.height/2.0f - dot->height/2.0f);

    if(CheckCollisionPointRec(mouse,*dot))
    {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            DotPressed = true;
    }
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        DotPressed = false;
    if(DotPressed)
    {
        if((masterVolume)*100 > 10)
            DrawButton(vN,TO_STRING(masterVolume * 100),(Vector2){vN->destinationButton.x + vN->destinationButton.width / 4 - 1,vN->destinationButton.y + vN->destinationButton.height / 4 - 2},fontType,20,BLACK);
        else
            DrawButton(vN,TO_STRING(masterVolume * 100),(Vector2){vN->destinationButton.x + vN->destinationButton.width / 3 + 1,vN->destinationButton.y + vN->destinationButton.height / 4},fontType,20,BLACK);

        float newX = mouse.x - (dot->width/2.0f);
        if (newX < minX) newX = minX;
        if (newX > maxX - dot->width) newX = maxX - dot->width;

        float range = maxX - minX - dot->width;
        masterVolume = (newX - minX) / range;
        // if (masterVolume < 0.0f) masterVolume = 0.0f;
        // if (masterVolume > 1.0f) masterVolume = 1.0f;
        if (currentMusic != -1)
            SetMusicVolume(music[currentMusic], masterVolume);

    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///<--------------- BESTIARY AUX
void DrawScroll(Texture2D* text)
{
    const int contentHeight = 1050;   // Height of the context.
    // const int screenW = 1200;
    const int screenH = 800;

    float wheel = GetMouseWheelMove();
    scrollY -= wheel * 20.0f;           // Velocity of the scrolll
    // Limit of the scroll.
    if (scrollY < 0) scrollY = 0;
    if (scrollY > contentHeight - screenH)
        scrollY = (float)(contentHeight - screenH);

    BeginScissorMode(400,200,1200,760);
        // DrawRectangle(400,200,550,750,RED);
        // DrawRectangle(970,200,550,750,RED);
        
        ///< Everything to draw is in -scrollY.
        int offsetY = -(int)scrollY;

        if(!IsTextureValid(text[0]))
            TraceLog(LOG_ERROR,"Error whit texture 0");

        for (int i = 0; i < 20; i++)
        {
            int y = 50 * i + offsetY + 200;
            // DrawRectangle(400, y, 550, 40, (i % 2 == 0) ? LIGHTGRAY : SKYBLUE);
            DrawTexturePro(text[0],
                    (Rectangle){.x=0,.y=0,.height=(float)text[0].height,.width=(float)text[0].width},
                    (Rectangle){.x=550,.y=(float)y,.height=(float)(text[0].height * 0.3),.width = (float)(text[0].width * 1)},
                (Vector2){0,0},0,WHITE);

            if(CheckCollisionPointRec(mouse,(Rectangle){.x=550,.y=(float)y,.height= (float)text[0].height * 0.3,.width = (float)text[0].width * 1.f}))
            {
                // DrawRectangle(970,200,550,750,LIME);
                DrawTexturePro(text[2], (Rectangle){.x=0,.y=0,.height=text[2].height,.width=text[2].width},
                                        (Rectangle){.x = 970,.y=200,.height=text[2].height * 6.f,.width=text[2].width * 4.5f},
                                    (Vector2){0,0},0,WHITE);
                if(strcmp(VeyxRegistry[i % 9].name,"Wandrail") == 0)
                    DrawTextureEx(VeyxRegistry[i % 9].iconText,(Vector2){970 + (text[2].width * 4.5f / 2) - (VeyxRegistry[i % 9].iconText.width / 2) * 2.f,280},0,2.f,WHITE);
                else
                    DrawTextureEx(VeyxRegistry[i % 9].iconText,(Vector2){970 + (text[2].width * 4.5f / 2) - (VeyxRegistry[i % 9].iconText.width / 2) * 3.5f,280},0,3.5f,WHITE);
                int mid = MeasureText(VeyxRegistry[i % 9].name,40);
                DrawTextEx(fontType,VeyxRegistry[i % 9].name,(Vector2){ 970 + (text[2].width * 4.5f)/2 - mid /2,500},40,0,BLACK);
                DrawTextEx(fontType,"Origen: ",(Vector2){1040,550},35,0,BLACK);
                DrawTextBoxed(fontType,VeyxRegistry[i % 9].origin,
                    (Rectangle){.x=1040,.y=600,.height= 150,.width=450},20,0,true,BLACK);
                DrawTextEx(fontType,"Descripcion: ",(Vector2){1040,760},35,0,BLACK);
                DrawTextBoxed(fontType,VeyxRegistry[i % 9].description,
                    (Rectangle){.x=1040,.y=815,.height= 100,.width=450},18,0,true,BLACK);
                // DrawTextEx(fontType,VeyxRegistry[i % 9].origin,(Vector2){980,600},20,0,BLACK);
                // DrawTextEx(fontType,VeyxRegistry[i % 9].description,(Vector2){980, 700},20,0,BLACK);

                #if DEBUG
                    DrawRectangleLinesEx((Rectangle){.x=1040,.y=600,.height= 150,.width=450},1.f,RED);
                    DrawRectangleLinesEx((Rectangle){.x=1040,.y=815,.height= 100,.width=450},1.f,RED);
                #endif
            }
            DrawTextEx(fontType,TextFormat("Veyx: %s %d",VeyxRegistry[i % 9].name,i),(Vector2){.x = 600, .y = (float)y+10},20,0,BLACK);
        }
    EndScissorMode();
}

void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    int length = (int)TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize/(float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width*scaleFactor : font.glyphs[index].advanceX*scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container)
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1)? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize*scaleFactor) > rec.height) break;

                // Draw selection background
                // bool isGlyphSelected = false;
                // if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                // {
                //     DrawRectangleRec((Rectangle){ rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize*scaleFactor }, selectBackTint);
                //     isGlyphSelected = true;
                // }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    DrawTextCodepoint(font, codepoint, (Vector2){ rec.x + textOffsetX, rec.y + textOffsetY }, fontSize,tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize/2)*scaleFactor;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                // selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///<--------------- FIGHTSCENE AUX
void DrawVeyxTeam(Entity* entity)
{
    /// RIGHT
    /// DOWN
    /// LEFT
    /// UP
    if(entity->typeEntity == _PLAYER)
    {
        CustomScale(0.5);
        if(entity->veyxInventory[0].life > 0)
        {
            Rectangle ori = entity->veyxInventory[0].sizeIcon;
            DrawTexturePro(entity->veyxInventory[0].iconText,
                (Rectangle){.x = ori.x, .y=ori.y, .width = -ori.width, .height = ori.height},
                (Rectangle){.x=250,.y=145,.width=(entity->veyxInventory[0].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[0].sizeIcon.height * scale.ScaleUniform},
                (Vector2){.x=0,.y=0},0,RAYWHITE);   
            entity->veyxInventory[0].sizeInFight = (Rectangle){.x=250,.y=145,.width=(entity->veyxInventory[0].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[0].sizeIcon.height * scale.ScaleUniform};
        }
        if(entity->veyxInventory[1].life > 0)
        {
            Rectangle ori = entity->veyxInventory[1].sizeIcon;
            DrawTexturePro(entity->veyxInventory[1].iconText,
                    (Rectangle){.x = ori.x, .y=ori.y, .width = -ori.width, .height = ori.height},
                    (Rectangle){.x=225,.y=170,.width=(entity->veyxInventory[1].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[1].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);  
            entity->veyxInventory[1].sizeInFight = (Rectangle){.x=225,.y=170,.width=(entity->veyxInventory[1].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[1].sizeIcon.height * scale.ScaleUniform};
        }
        if(entity->veyxInventory[2].life > 0)  
        {
            Rectangle ori = entity->veyxInventory[2].sizeIcon;
            DrawTexturePro(entity->veyxInventory[2].iconText,
                    (Rectangle){.x = ori.x, .y=ori.y, .width = -ori.width, .height = ori.height},
                    (Rectangle){.x=210,.y=150,.width=(entity->veyxInventory[2].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[2].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);  
            entity->veyxInventory[2].sizeInFight = (Rectangle){.x=210,.y=150,.width=(entity->veyxInventory[2].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[2].sizeIcon.height * scale.ScaleUniform};
        }
        if(entity->veyxInventory[3].life > 0)
        {
            Rectangle ori = entity->veyxInventory[3].sizeIcon;
            DrawTexturePro(entity->veyxInventory[3].iconText,
                    (Rectangle){.x = ori.x, .y=ori.y, .width = -ori.width, .height = ori.height},
                    (Rectangle){.x=220,.y=110,.width=(entity->veyxInventory[3].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[3].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);
            entity->veyxInventory[3].sizeInFight = (Rectangle){.x=220,.y=110,.width=(entity->veyxInventory[3].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[3].sizeIcon.height * scale.ScaleUniform};
        }
        CustomScale(1.f);
    }
    else
    {
        CustomScale(0.5);
        if(entity->veyxInventory[0].life > 0)
        {
            Rectangle ori = entity->veyxInventory[0].sizeIcon;
            DrawTexturePro(entity->veyxInventory[0].iconText,
                    (Rectangle){.x = ori.x, .y=ori.y, .width = -ori.width, .height = ori.height},
                    (Rectangle){.x=370,.y=145,.width=(entity->veyxInventory[0].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[0].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);  
            entity->veyxInventory[0].sizeInFight = (Rectangle){.x=370,.y=145,.width=(entity->veyxInventory[0].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[0].sizeIcon.height * scale.ScaleUniform};
        } 
        if(entity->veyxInventory[1].life > 0)
        {
            DrawTexturePro(entity->veyxInventory[1].iconText,
                    entity->veyxInventory[1].sizeIcon,
                    (Rectangle){.x=390,.y=180,.width=(entity->veyxInventory[1].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[1].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);  
            entity->veyxInventory[1].sizeInFight = (Rectangle){.x=390,.y=180,.width=(entity->veyxInventory[1].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[1].sizeIcon.height * scale.ScaleUniform};
        }
        if(entity->veyxInventory[2].life > 0)    
        {
            DrawTexturePro(entity->veyxInventory[2].iconText,
                    entity->veyxInventory[2].sizeIcon,
                    (Rectangle){.x=410,.y=150,.width=(entity->veyxInventory[2].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[2].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);  
            entity->veyxInventory[2].sizeInFight = (Rectangle){.x=410,.y=150,.width=(entity->veyxInventory[2].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[2].sizeIcon.height * scale.ScaleUniform}; 
        }
        if(entity->veyxInventory[3].life > 0)  
        {
            DrawTexturePro(entity->veyxInventory[3].iconText,
                    entity->veyxInventory[3].sizeIcon,
                    (Rectangle){.x=395,.y=120,.width=(entity->veyxInventory[3].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[3].sizeIcon.height * scale.ScaleUniform},
                    (Vector2){.x=0,.y=0},0,RAYWHITE);
            entity->veyxInventory[3].sizeInFight = (Rectangle){.x=395,.y=120,.width=(entity->veyxInventory[3].sizeIcon.width * scale.ScaleUniform),.height = entity->veyxInventory[3].sizeIcon.height * scale.ScaleUniform};
        }
        CustomScale(1.f);
    }
}

void DrawHeadVeyx(const Queue* self, Vector2 pos)
{
    if(QueueEmpty(*self))
        AssertNotNull(self,"Empty Queue in DrawHeadVeyx.","self");
    Item* current = self->head;
    Vector2 x;
    int aum = 0;
    while(current)
    {
        Veyx* v = (Veyx*) current->item;
        AssertNotNull(v,"Veyx is no cast correctly.","v");
        aum += v->sizeHead.width + 5;
        x.x = (pos.x - 40) + aum;
        x.y = pos.y+3;
        if(v)
        {
            DrawTextureRec(v->headIcon,v->sizeHead,x,WHITE);
            if(v->owner == _PLAYER)
                DrawRectangleLinesEx((Rectangle){.x=x.x,.y=x.y,.width = 64, .height = 64},2.f,BLUE);
            else
                DrawRectangleLinesEx((Rectangle){.x=x.x,.y=x.y,.width = 64, .height = 64},2.f,RED);
        }
        current = current->next;
    }
}

void DrawCurrentPhase(Queue* self)
{
    Veyx* temp = (Veyx*)PeakItem(self);
    if(temp)
        DrawRectangleLinesEx(temp->sizeInFight,0.5f,YELLOW);
}

void DrawTeamStatus(Entity* player, Entity* npc)
{
    Vector2 recSize = (Vector2){.x = 250, .y = 350}; 
    DrawRectangleRec((Rectangle){.x = 10, .y = GetScreenHeight() / 2 - recSize.y /2, .width = recSize.x, .height = recSize.y }, VIOLET );
    DrawRectangleRec((Rectangle){.x = GetScreenWidth() - recSize.x - 10, .y = GetScreenHeight() / 2 - recSize.y /2, .width = recSize.x, .height = recSize.y }, VIOLET );

    int inc = 0;
    for (size_t i = 0; i < 4; i++)
    {
        DrawTextureEx(player->veyxInventory[i].headIcon,(Vector2){.x = 35,.y = (GetScreenHeight() / 2 - recSize.y /2) + 30 + inc},0,1.f,WHITE); 
        DrawTextureEx(npc->veyxInventory[i].headIcon,(Vector2){.x = GetScreenWidth() - 90,.y = (GetScreenHeight() / 2 - recSize.y /2) + 30 + inc},0,1.f,WHITE);
        if(player->veyxInventory[i].life <= 0)
        {
            BeginShaderMode(shaders[S_GRAYSCALE]);
                DrawTextureEx(player->veyxInventory[i].headIcon,(Vector2){.x = 35,.y = (GetScreenHeight() / 2 - recSize.y /2) + 30 + inc},0,1.f,WHITE);
            EndShaderMode();       
        }
        else if(npc->veyxInventory[i].life <= 0)
        {
            BeginShaderMode(shaders[S_GRAYSCALE]);
                DrawTextureEx(npc->veyxInventory[i].headIcon,(Vector2){.x = GetScreenWidth() - 90,.y = (GetScreenHeight() / 2 - recSize.y /2) + 30 + inc},0,1.f,WHITE);
            EndShaderMode();         
        }
        DrawLifeBar(&player->veyxInventory[i],(Vector2){.x = 35,.y = (GetScreenHeight() / 2 - recSize.y /2) + 30 + inc});
        DrawLifeBar(&npc->veyxInventory[i],(Vector2){.x = GetScreenWidth() - 90,.y = (GetScreenHeight() / 2 - recSize.y /2) + 30 + inc});
        inc += 76;

    }

    
}

void DrawLifeBar(Veyx* vA, Vector2 pos)
{
    if (vA->displayedLife > vA->life)
        vA->displayedLife -= 2;
    else if (vA->displayedLife < vA->life)
        vA->displayedLife += 2;

    float pct = (vA->life == 0) ? 0.0f : (float)vA->displayedLife / (float)vA->maxlife;;
    int innerWidth = (int)(pct * BAR_WIDTH);
    Color fillColor = GREEN;
    if (pct < 0.25) 
        fillColor = RED;
    else if (pct < 0.40f)
        fillColor = GOLD;

    Color colorStatus = BLANK;
    switch (vA->status)
    {
    case STATUS_BURN:
        colorStatus = RED;
        break;
    case STATUS_FREEZE:
        colorStatus = SKYBLUE;
        break;
    case STATUS_POISON:
        colorStatus = LIME;
        break;;
    case STATUS_STUN:
        colorStatus = YELLOW;
        break;
    default:
        colorStatus = BLANK;
        break;
    }

    switch (vA->owner)
    {
    case _PLAYER:
    {
        ///< Veyx Status
        DrawRectangleRec((Rectangle){
        .x = pos.x + vA->sizeHead.width + 20,
        .y = pos.y + vA->sizeHead.height / 2 + 15,
        .width = 20,
        .height = 20
        },colorStatus);


        DrawRectangleRec((Rectangle){
        .x = pos.x + vA->sizeHead.width + 20,
        .y = pos.y + vA->sizeHead.height / 2 - 5,
        .width = BAR_WIDTH,
        .height = BAR_HEIGHT
        },WHITE);    

        DrawRectangleRec((Rectangle){
            .x = pos.x + vA->sizeHead.width + 20,
            .y = pos.y + vA->sizeHead.height / 2 - 5,
            .width = innerWidth,
            .height = BAR_HEIGHT
        },fillColor);
    }break;
    case _NPC:
    {
        float baseX = pos.x - vA->sizeHead.width - 50;
        float baseY = pos.y + vA->sizeHead.height / 2 - 5;
        float lifeStatus = vA->life <= 0 ? BAR_WIDTH : vA->maxlife - vA->displayedLife; 
        DrawRectangleRec((Rectangle){
            .x = baseX,
            .y = baseY,
            .width = BAR_WIDTH,
            .height = BAR_HEIGHT
        }, WHITE);
        DrawRectangleRec((Rectangle){
            .x = baseX + (lifeStatus),
            .y = baseY,
            .width = BAR_WIDTH - (lifeStatus),
            .height = BAR_HEIGHT
        }, fillColor);
        DrawRectangleRec((Rectangle){
        .x = baseX + BAR_WIDTH  - 22,
        .y = baseY + BAR_HEIGHT + 5,
        .width = 20,
        .height = 20
        },colorStatus);
    }
    break;
    default:
        break;
    }
}

bool UpdateFightButtons(Queue* q,Entity* player,Entity** pool, Vector2 mouse, Button** buttons, bool IsMouseOver[], bool IsButtonsPressed[], Veyx* veyxPriority[])
{
        ///< Interactions for buttons
    if(CheckCollisionPointRec(mouse,buttons[0]->boundingBox) && !IsButtonPressed(IsButtonsPressed))
    {
        IsMouseOver[0] = true;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(sounds[0]);
            IsButtonsPressed[0] = true;
        }
    }
    else if(CheckCollisionPointRec(mouse,buttons[1]->boundingBox) && !IsButtonPressed(IsButtonsPressed))
    {
        IsMouseOver[1] = true;
        // if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        //     IsButtonsPressed[1] = true;
    }
    else if(CheckCollisionPointRec(mouse,buttons[2]->boundingBox) && !IsButtonPressed(IsButtonsPressed))
    {
        IsMouseOver[2] = true;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            PlaySound(sounds[0]);
            if(!FightBattleEnds)
            {
                AddBattleLog("No puedes salir de la batalla con %s",pool[tNPCSCoop]->name);
                return false;
            }
            pool[tNPCSCoop]->position = pool[tNPCSCoop]->prev_position;
            pool[tNPCSCoop]->eLook = 0;
            player->position = player->prev_position;
            pool[tNPCSCoop]->veyxAlive = 4;
            player->veyxAlive = 4;
            for(size_t i=0; i< 4; i++)
            {
                player->veyxInventory[i].life = player->veyxInventory[i].maxlife;
                pool[tNPCSCoop]->veyxInventory[i].life = pool[tNPCSCoop]->veyxInventory[i].maxlife;

                player->veyxInventory[i].status = STATUS_NONE;
                pool[tNPCSCoop]->veyxInventory[i].status = STATUS_NONE;

                veyxPriority[i] = NULL;
                veyxPriority[i+4] = NULL;
            }
            FreeQueue(q);
            IsFightRuning = false;
            IsVeyxPriorityInit = false;
            ChangeScene(sGAMESTATE);
            return true;
        }
    }
    else 
    {
        IsMouseOver[0] = false;
        IsMouseOver[1] = false;
        IsMouseOver[2] = false;
    }
    if(IsKeyDown(KEY_Q) && FightBattleEnds)
    {
        pool[tNPCSCoop]->position = pool[tNPCSCoop]->prev_position;
        pool[tNPCSCoop]->eLook = 0;
        player->position = player->prev_position;
        pool[tNPCSCoop]->veyxAlive = 4;
        player->veyxAlive = 4;
        for(size_t i=0; i< 4; i++)
        {
        player->veyxInventory[i].life = player->veyxInventory[i].maxlife;
        pool[tNPCSCoop]->veyxInventory[i].life = pool[tNPCSCoop]->veyxInventory[i].maxlife;
        veyxPriority[i] = NULL;
        veyxPriority[i+4] = NULL;
        }
        FreeQueue(q);
        IsFightRuning = false;
        IsVeyxPriorityInit = false;
        ChangeScene(sGAMESTATE);
        return true;
    }
    return false;
}

bool IsButtonPressed(bool self[])
{
    if(self[0])
        return true;
    else if(self[1])
        return true;
    else if(self[2])
        return true;
    else 
        return false;
}

int CompareSpeed(const void* a, const void* b)
{
    return (*(Veyx**)b)->speed - (*(Veyx**)a)->speed;
}

void AddVeyxToPriorityList(Veyx* veyxPriority[8],Entity* player,Entity* enemy)
{
    for(size_t i=0; i<8; i++)
    {
        if(i<4)
        {
            veyxPriority[i] = &player->veyxInventory[i];
            veyxPriority[i]->owner = _PLAYER;
        }
        else
        {
            veyxPriority[i] = &enemy->veyxInventory[i-4];
            veyxPriority[i]->owner = _NPC;
        }
    }
}

void UpdateEntities(Entity* player, Entity* enemy)
{
        ///< Mika Update
    enemy->position = (Vector2){460,150};
    enemy->eLook = 1;
    ///< Eplayer updates
    player->eLook = RIGHT;
    player->position = (Vector2){150,150};
    player->spriteAnimation[UP].speed = 0.3;
    player->spriteAnimation[DOWN].speed = 0.3;
    player->spriteAnimation[LEFT].speed = 0.3;
    player->spriteAnimation[RIGHT].speed = 0.3;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
