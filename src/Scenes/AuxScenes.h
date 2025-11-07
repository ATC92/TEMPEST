//////////////////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////////////////
#include "../Engine/Flags.h"

#include "../Components/Veyx.h"
#include "../Components/Fonts.h"
#include "../Components/Sound.h"
#include "../Components/Button.h"
#include "../Components/Entity.h"
#include "../Components/Fight.h"
#include "../Components/BattleLog.h"

#include "../Utils/String.h"
#include "../Utils/Queues.h"

//////////////////////////////////////////////////////////////////////////////
extern float minX;
extern float maxX;
//////////////////////////////////////////////////////////////////////////////
/**
 * @brief Follor a dot from the mouse
 * 
 * @param Rectangle     - Rectangle whats is going to follow the Mouse
 * 
 * @return `void`
 */
void SoundBarFollowPoint(Button* vN, Rectangle* dot);


//////////////////////////////////////////////////////////////////////////////
/**
 * 
 */
void DrawScroll(Texture2D* text);

void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
//////////////////////////////////////////////////////////////////////////////
void DrawVeyxTeam(Entity* entity);
void DrawHeadVeyx(const Queue* self, Vector2 pos);
void DrawCurrentPhase(Queue* self);
void DrawTeamStatus(Entity* player, Entity* npc);
void DrawLifeBar(Veyx* vA, Vector2 pos);
bool UpdateFightButtons(Queue* q,Entity* player, Entity** pool,Vector2 mouse, Button** buttons, bool IsMouseOver[], bool IsButtonsPressed[],Veyx* veyxPriority[]);
bool IsButtonPressed(bool self[]);
int CompareSpeed(const void* a, const void* b);
void AddVeyxToPriorityList(Veyx* veyxPriority[8],Entity* player,Entity* enemy);
void UpdateEntities(Entity* player, Entity* enemy);
//////////////////////////////////////////////////////////////////////////////