#pragma once

typedef enum item {
	EMPTY = 0,
	BEER,
	MAGNIFYING_GLASS,
	CIGARETTE_PACK,
	HANDCUFFS,
	HAND_SAW
}ITEM;

bool useItem(ITEM *item, BulletsLink* bullets, bool* oppHandcuffed, int* lives, bool* doubleDamage, bool* bulletKnown);

int findItem(ITEM item, ITEM items[]);