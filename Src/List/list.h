#pragma once

/* List of void pointers */

typedef struct List {
	int capa;
	int length;
	void** items;
} List;

List* list_new();

void list_append(List* self, void* item);

void* list_at(List* self, int index);

void list_delete(List* self);
