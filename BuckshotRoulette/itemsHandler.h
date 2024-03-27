#pragma once
#include <stddef.h>

enum item {
	EMPTY = 0,
	BEER,
	MAGNIFYING_GLASS,
	CIGARETTE_PACK,
	HANDCUFFS,
	HAND_SAW
};

typedef unsigned char ITEM_T;

void item_add(ITEM_T *arr, size_t n);

char *item_text(ITEM_T item);

ITEM_T item_remove(ITEM_T *arr, size_t position);

void item_clear(ITEM_T *arr, size_t n);