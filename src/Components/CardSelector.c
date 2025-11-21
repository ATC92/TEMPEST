///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CardSelector.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CardSelector selector;
int IsCardSelected = -1;
static int cardToDrawInformation;
static bool DrawInformation;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InitCardSelector(Inventory *inv, Rectangle area)
{
    selector.inv = NULL;
    selector.area = (Rectangle){0};
    selector.scrollX = 0.f;
    selector.selectedIndex = -1;
    selector.cardCount = 0;

    selector.inv = inv;
    selector.area = area;

    const float spacing = 20.0f;
    int currentCardIndex = 0;

    for (size_t i = 0; i < inv->amountObj; i++) {
        if (inv->object[i].type != OBJ_CARD)
            continue;

        selector.cardIndex[selector.cardCount] = (int)i;
        selector.cardCount++;
            
        Card *c = &inv->object[i].card;
        float cardWidth = c->sizeCard.width * 2.f;
        float cardHeight = c->sizeCard.height * 2.f;

        c->boundingBox.x = area.x + currentCardIndex * (cardWidth + spacing);
        c->boundingBox.y = area.y + (area.height - cardHeight) / 2;
        c->boundingBox.width = cardWidth;
        c->boundingBox.height = cardHeight;
        currentCardIndex++;
    }
}

void UpdateCardSelector()
{
    if (selector.cardCount == 0) 
        return;
    
    const float SCROLL_LIMIT_MAX = 0.0f; 
    float scrollLimitMin = 0.0f; 

    int lastMapIndex = selector.cardCount - 1;
    int lastInvIndex = selector.cardIndex[lastMapIndex];
    Object *lastObj = &selector.inv->object[lastInvIndex];
    
    float contentRightEdge = lastObj->card.boundingBox.x + lastObj->card.boundingBox.width;
    float viewRightEdge = selector.area.x + selector.area.width;

    scrollLimitMin = viewRightEdge - contentRightEdge;

    if (scrollLimitMin > 0) {
        scrollLimitMin = 0.0f;
    }

    float mouseWheel = GetMouseWheelMove();
    
    if (mouseWheel != 0.0f)
    {
        const float SCROLL_SPEED = 50.0f; 
        selector.scrollX += mouseWheel * SCROLL_SPEED;
    }

    if (selector.scrollX > SCROLL_LIMIT_MAX) 
        selector.scrollX = SCROLL_LIMIT_MAX;
        
    if (selector.scrollX < scrollLimitMin) 
        selector.scrollX = scrollLimitMin;

    if (CheckCollisionPointRec(mouse, selector.area))
    {
        DrawInformation = false; 
        
        for (int mapIndex = 0; mapIndex < selector.cardCount; mapIndex++)
        {
            int invIndex = selector.cardIndex[mapIndex];
            Object *obj = &selector.inv->object[invIndex];
            
            Rectangle cardRect = obj->card.boundingBox;
            cardRect.x += selector.scrollX;

            if (CheckCollisionPointRec(mouse, cardRect))
            {
                DrawInformation = true;
                cardToDrawInformation = mapIndex;
                
                if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    IsCardSelected = invIndex;
                    selector.selectedIndex = mapIndex;
                }
                break; 
            }
        }
    }
    else
    {
        DrawInformation = false;
    }
}

void DrawCardSelector()
{    
    if (selector.cardCount == 0)
    {
        TraceLog(LOG_INFO,"Card Count is Zero. Skipping Draw."); 
        return; 
    }
    AssertNotNull(selector.inv,"Error with inventory NULL","selector.inv");

    DrawRectangleRec(selector.area, Fade(DARKGRAY, 0.3f));

    BeginScissorMode((int)selector.area.x, (int)selector.area.y,(int)selector.area.width, (int)selector.area.height);
    {
        for (int mapIndex = 0; mapIndex < selector.cardCount; mapIndex++)
        {
            int invIndex = selector.cardIndex[mapIndex];
            Object* obj = &selector.inv->object[invIndex];
            Card* c = &obj->card;

            Rectangle destRect = c->boundingBox;
            
            destRect.x += selector.scrollX;
            Color tint = BLANK;
            if(mapIndex == selector.selectedIndex)
                tint = YELLOW;

            if (c->cardTexture == NULL || !IsTextureValid(*c->cardTexture))
            {
                TraceLog(LOG_WARNING, "Texture not valid for card index %d (invIndex %d)", mapIndex, invIndex);
                continue;
            }

            DrawTexturePro(
                *c->cardTexture,
                c->sizeCard,
                destRect,
                (Vector2){0, 0},
                0,
                WHITE
            );
            DrawRectangleLinesEx(destRect,3.f,tint);
        }
    }
    EndScissorMode(); 
    
    DrawRectangleLinesEx(selector.area, 2, WHITE);
}

void DrawInformationCard()
{
    if (!DrawInformation) {
        return;
    }

    int invIndex = selector.cardIndex[cardToDrawInformation];

    Object* obj = &selector.inv->object[invIndex];
    Card* c = &obj->card;

    Rectangle dest = {.x = GetScreenWidth()/2 - 250,.y = GetScreenHeight()/2 + 45 , .width = 500, .height = 200};
    Rectangle destText = {.x = dest.x +10,.y = dest.y + 10, .width = dest.width - 10, .height = dest.height -10};
    
    if(obj->type == OBJ_CARD) 
    {
        const char* textInformation = TextFormat("Carta: %s\nDescripcion: %s\nEnfriamient: %d\nRareza: %s\nNaturaleza: %s",c->name,c->descEffect,c->cooldown,GetCardRarityToString(c->rarity),GetCardTypeToString(c->type));
        DrawRectangleRec(dest, Fade(BLACK, 0.5f));
        // DrawText(obj->card.name, dest.x, dest.y - 20, 20, BLACK);
        DrawRectangleLinesEx(dest,3.f,BLACK);
        DrawTextBoxed(fontType,textInformation,destText,20,0,true,WHITE);
    }
}

bool ApplyCardEffect(Veyx** self)
{
    Vector2 mouseWorld = GetScreenToWorld2D(mouse, camera); 
    int indexVeyx = -1;
    for(size_t i=0; i<8; i++)
    {
        if (self[i]->life > 0 && CheckCollisionPointRec(mouseWorld, self[i]->sizeInFight) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            indexVeyx = (int)i;
            break;
        }
    }
    if(indexVeyx == -1)
        return false;
    
    int invIndex = selector.cardIndex[selector.selectedIndex];
    selector.cardSelected = invIndex;
    Object* obj = &selector.inv->object[invIndex];
    Card* c = &obj->card;
    
    obj->accion(c,self[indexVeyx]);

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////