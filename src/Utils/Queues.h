////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////
#include "../Engine/Flags.h"

#include "../Components/Veyx.h"

#include "../Utils/ErrorManager.h"
////////////////////////////////////////////////////////////////////////////
typedef struct _item
{
    void* item;
    struct _item* previous;
    struct _item* next;
}Item;

typedef struct _queue
{
    Item* head;
    Item* tail;
    size_t size;
    size_t len;
}Queue;
////////////////////////////////////////////////////////////////////////////
void InitQueue(Queue* self, size_t len);
Item* CreateItem(void* item);
void AddItem(Queue* self, void* item);
void AddToQueue(Queue* self, Item* item);
Item* DequeueItem(Queue* self);
void* PeakItem(Queue* self);
Item* Peak(Queue* self);
void ProcessAndRequeue(Queue* self, bool (*fSelf)(void*));
bool QueueEmpty(Queue self);
void FreeQueue(Queue* self);

void ProcessQueueDebug(void* self);
////////////////////////////////////////////////////////////////////////////