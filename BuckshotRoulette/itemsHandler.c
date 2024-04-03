#include "itemsHandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char EMPTY_TEXT[] = "Empty";
const char BEER_TEXT[] = "Beer";
const char MAGNIFYING_TEXT[] = "Magnifying Glass";
const char CIGARETTE_TEXT[] = "Cigarette";
const char HANDCUFFS_TEXT[] = "Handcuffs";
const char HANDSAW_TEXT[] = "Handsaw";

void item_add(ITEM_T *arr, size_t n) {
	if (arr == 0) {
		fprintf(stderr, "Did not recieve a valid array in item_add!\n");
		return;
	}

	for (size_t i = 0; i < n; i++) {
		if (arr[i] == EMPTY) {
			// In case srand has not been used before
			srand((unsigned int) time(0));
			arr[i] = (rand() % 5);
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