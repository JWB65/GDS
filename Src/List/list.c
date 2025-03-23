#include <malloc.h>

#define INITIAL_CAPA 64

typedef struct {
	int capa;
	int length;
	void** items;
} List;

List* list_new()
{
	List* p = malloc(sizeof(*p));
	p->length = 0;
	p->capa = INITIAL_CAPA;
	p->items = malloc(p->capa * sizeof(void*));
	return p;
}

void list_append(List* self, void* item)
{
	if (self->length >= self->capa) {
		self->capa = self->capa * 2;
		self->items = realloc(self->items, self->capa * sizeof(void*));
	}
	self->items[self->length] = item;
	self->length++;
}

void* list_at(List* self, int index)
{
	return self->items[index];
}

void list_delete(List* self)
{
	free(self->items);
	free(self);
}