#include "itemsHandler.h"
#include "Main.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char EMPTY_TEXT[] = "Empty";
const char BEER_TEXT[] = "Beer";
const char MAGNIFYING_TEXT[] = "Magnifying Glass";
const char CIGARETTE_TEXT[] = "Cigarette";
const char HANDCUFFS_TEXT[] = "Handcuffs";
const char HANDSAW_TEXT[] = "Handsaw";

void item_add(ITEM_T * arr, size_t n) {
	if (arr == 0) {
		fprintf(stderr, "Did not recieve a valid array in item_add!\n");
		return;
	}

	for (size_t i = 0; i < n; i++) {
		if (arr[i] == EMPTY) {
			// In case srand has not been used before
			srand((unsigned int) time(0));
			arr[i] = (rand() % 5)+1;
		}
	}
}

const char *item_text(ITEM_T item) {
	switch (item) {
	case EMPTY:
		return EMPTY_TEXT;
		break;
	case BEER:
		return BEER_TEXT;
	case MAGNIFYING_GLASS:
		return MAGNIFYING_TEXT;
	case CIGARETTE_PACK:
		return CIGARETTE_TEXT;
	case HANDCUFFS:
		return HANDCUFFS_TEXT;
	case HAND_SAW:
		return HANDSAW_TEXT;
	}

	fprintf(stderr, "Not a valid item from item_text\n");
	return "Nill";
}

ITEM_T item_remove(ITEM_T *arr, size_t position) {
	if (arr == 0) {
		fprintf(stderr, "Did not recieve a valid array in item_remove!\n");
		return 0;
	}
	ITEM_T out = arr[position];
	arr[position] = EMPTY;
	return out;
}

// Returns -1 on failure
size_t findItem(ITEM_T item, ITEM_T *items, size_t items_n) {
	if (items == 0) {
		fprintf(stderr, "Did not recieve a valid array in findItem!\n");
		return -1;
	}
	for (size_t i = 0; i < items_n; i++) {
		if (items[i] == item) {
			return i;
		}
	}

	return -1;
}

void item_clear(ITEM_T *arr, size_t n) {
	if (arr == 0) {
		fprintf(stderr, "Did not recieve a valid array in item_clear!\n");
		return;
	}
	for (size_t i = 0; i < n; i++) {
		arr[i] = EMPTY;
	}
}

bool useItem(ITEM *pItem, BulletsLink* bullets, bool* oppHandcuffed, int* lives, bool* doubleDamage, bool* bulletKnown) {
	ITEM item = *pItem;
	if (item == BEER) {
		if (bulletCount(bullets) == 0) {
			fprintf(stdout, "Tried to use item: BEER.\n");
			fprintf(stdout, "No bullets are loaded, item was not used.\n");
			return false;
		}
		*pItem = EMPTY;//change item to empty
		BULLET b = popBullet(bullets);
		fprintf(stdout, "Used item: BEER.\n");
		fprintf(stdout, "Ejected a bullet from the gun.\n");
		if (b == LIVE) {
			fprintf(stdout, "The bullet was LIVE.\n");
		}
		else {
			fprintf(stdout, "The bullet was BLANK.\n");
		}
		return true;
	}
	if (item == MAGNIFYING_GLASS) {
		*pItem = EMPTY;//change item to empty
		BULLET b = peekBullet(*bullets);
		fprintf(stdout, "Used item: MAGNIFYING GLASS.\n");
		fprintf(stdout, "Peeked at the next bullet.\n");
		if (b == LIVE) {
			fprintf(stdout, "The bullet was LIVE.\n");
		}
		else {
			fprintf(stdout, "The bullet was BLANK.\n");
		}
		return true;
	}
	if (item == CIGARETTE_PACK) {
		if (*lives < MAX_LIVES) {
			*pItem = EMPTY;//change item to empty
			(*lives)++;
			fprintf(stdout, "Used item: CIGARETTE PACK.\n");
			fprintf(stdout, "Healed 1 health, to %d.\n", *lives);
			return true;
		}
		fprintf(stdout, "Tried to use: CIGARRETE PACK.\n");
		fprintf(stdout, "Health is already at max (%d), item was not used.\n", *lives);
		return false;
	}
	if (item == HANDCUFFS) {
		if (!(*oppHandcuffed)) {
			*pItem = EMPTY;//change item to empty
			(*lives)++;
			fprintf(stdout, "Used item: HANDCUFFS.\n");
			fprintf(stdout, "Opponent's next turn will be skipped.\n");
			return true;
		}
		fprintf(stdout, "Tried to use: HANDCUFFS.\n");
		fprintf(stdout, "Opponent is already cuffed, item was not used.\n");
		return false;
	}
	if (item == HAND_SAW) {
		if (!(*doubleDamage)) {
			*pItem = EMPTY;//change item to empty
			(*lives)++;
			fprintf(stdout, "Used item: HAND SAW.\n");
			fprintf(stdout, "The next LIVE bullet shot THIS TURN will deal double damage.\n");
			return true;
		}
		fprintf(stdout, "Tried to use: HAND SAW.\n");
		fprintf(stdout, "Double damage is already active, item was not used.\n");
		return false;
	}
	return false;//no item match
}