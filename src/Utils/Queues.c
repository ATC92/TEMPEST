////////////////////////////////////////////////////////////////////////////
#include "Queues.h"
////////////////////////////////////////////////////////////////////////////
void InitQueue(Queue* self, size_t len)
{
	self->head = NULL;
	self->tail = NULL;
	self->size = 0;
	self->len = len;
}

Item* CreateItem(void* item)
{
	Item* new;
	new = (Item*) calloc(1,sizeof(Item));
	new->item = item;
	new->previous = NULL;
	new->next = NULL;
	return new;	
}

void AddItem(Queue* self, void* item)
{
    Item* new;
    new = CreateItem(item);

    AssertNotNull(self,"Self is empty AddItem","self");
    if(QueueEmpty(*self))
    {
        self->head = new;
        self->tail = new;
    }
    else
    {
        self->tail->next = new;
        new->previous = self->tail;
        self->tail = new;
    }
    self->size++;
}

void AddToQueue(Queue* self, Item* item)
{
    if(QueueEmpty(*self))
    {
        self->head = item;
        self->tail = item;
    }
    else
    {
        self->tail->next = item;
        item->previous = self->tail;
        self->tail = item;
    }
    self->size++;
}

Item* DequeueItem(Queue* self)
{
    if(QueueEmpty(*self))
        return NULL;
    Item* temp = self->head;
    self->head = self->head->next;
    self->size--;
    if(self->head)
        self->head->previous = NULL;
    else
        self->tail = NULL;

    temp->next = NULL;
    temp->previous = NULL;
    
    return temp;
}

void* PeakItem(Queue* self)
{
    if(QueueEmpty(*self))
        return NULL;
    return self->head->item;
}

Item* Peak(Queue* self)
{
    if(QueueEmpty(*self))
        return NULL;
    return self->head;
}

void ProcessAndRequeue(Queue* self, bool (*fSelf)(void*))
{
    if(QueueEmpty(*self))
        return;
    Item* temp = DequeueItem(self);
    AssertNotNull(temp,"ProcessAndRequeue temp NULL","temp");
    
    if(fSelf(temp->item))
        AddToQueue(self,temp);
    else
        free(temp);
}

bool QueueEmpty(Queue self)
{
	return self.head==NULL && self.tail==NULL && self.size==0;
}

void FreeQueue(Queue* self)
{
    Item* current = self->head;
    while (current)
    {
        Item* next = current->next;
        free(current);
        current = next;
    }
    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
}

void ProcessQueueDebug(void* self)
{
    Veyx* v = (Veyx*)self;
    TraceLog(LOG_INFO,"Veyx Process: %s",v->name);
}
////////////////////////////////////////////////////////////////////////////