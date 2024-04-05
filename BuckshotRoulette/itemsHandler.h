#pragma once
#include <stdbool.h>
#include "bulletsHandler.h"
#include <stddef.h>
#define ITEMS_CAP 8

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

const char *item_text(ITEM_T item);

size_t findItem(ITEM_T item, ITEM_T *items, size_t items_n);

ITEM_T item_remove(ITEM_T *arr, size_t position);

void item_clear(ITEM_T *arr, size_t n);

bool useItem(ITEM *item, BulletsLink* bullets, bool* oppHandcuffed, int* lives, bool* doubleDamage, bool* bulletKnown);
