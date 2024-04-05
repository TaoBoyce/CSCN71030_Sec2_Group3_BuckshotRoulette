#define _CRT_SECURE_NO_WARNINGS
#include "saveload.h"
#include "bulletsHandler.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



GAME_SAVE *create_save() {
	GAME_SAVE *save = malloc(sizeof(GAME_SAVE));
	if (save == 0) {
		fprintf(stderr, "Unable to allocate memory in create_save!\n");
		return 0;
	}
	
	// To avoid issues with realloc
	save->items = 0;
	save->bullets = 0;

	return save;
}

INFINITE_SAVE *create_save_infinite() {
	INFINITE_SAVE *save = malloc(sizeof(INFINITE_SAVE));
	if (save == 0) {
		fprintf(stderr, "Unable to allocate memory in create_save_infinite!\n");
		return 0;
	}

	// To avoid issues with realloc
	save->items = 0;
	save->bullets = 0;

	return save;
}


bool update_save(GAME_SAVE *save, int stage, int turn, int *lives, ITEM_T *items, size_t items_n, BulletsLink bullets,
	bool sawed, bool dealer_cuffed) {
	if (save == 0)
		return false;
	save->stage = stage;
	save->turn = turn;
	if (lives != 0) {
		save->lives[0] = lives[0];
		save->lives[1] = lives[1];
	}
	save->sawed = sawed;
	save->dealer_cuffed = dealer_cuffed;

	// Copying arrays
	ITEM_T *arr1 = realloc(save->items, items_n * sizeof(ITEM_T));
	if (arr1 == 0) {
		fprintf(stderr, "Unable to allocate memory in update_save!\n");
		return false;
	}
	save->items = arr1;
	memcpy(save->items, items, items_n * sizeof(ITEM_T));
	save->items_n = items_n;

	int bullets_n = bulletCount(bullets);
	BULLET *arr2 = realloc(save->bullets, sizeof(BULLET) * bullets_n);
	if (arr2 == 0) {
		fprintf(stderr, "Unable to allocate memory in update_save!\n");
		return false;
	}
	save->bullets = arr2;
	BulletsLink current = bullets;
	for (int i = 0; i < bullets_n; i++) {
		if (current == 0)
			break;
		save->bullets[i] = current->bullet;
		current = current->next;
	}
	save->bullets_n = bullets_n;

	return true;
}

bool update_save_inf(INFINITE_SAVE *save, int stage, int turn, int *lives, ITEM_T *items, size_t items_n, BulletsLink bullets, bool sawed,
	bool dealer_cuffed, unsigned long long total_wins) {
	if (save == 0)
		return false;
	save->stage = stage;
	save->turn = turn;
	if (lives != 0) {
		save->lives[0] = lives[0];
		save->lives[1] = lives[1];
	}
	save->sawed = sawed;
	save->dealer_cuffed = dealer_cuffed;

	// Copying arrays
	ITEM_T *arr1 = realloc(save->items, items_n * sizeof(ITEM_T));
	if (arr1 == 0) {
		fprintf(stderr, "Unable to allocate memory in update_save!\n");
		return false;
	}
	save->items = arr1;
	memcpy(save->items, items, items_n * sizeof(ITEM_T));
	save->items_n = items_n;

	int bullets_n = bulletCount(bullets);
	BULLET *arr2 = realloc(save->bullets, sizeof(BULLET) * bullets_n);
	if (arr2 == 0) {
		fprintf(stderr, "Unable to allocate memory in update_save!\n");
		return false;
	}
	save->bullets = arr2;
	BulletsLink current = bullets;
	for (int i = 0; i < bullets_n; i++) {
		if (current == 0)
			break;
		save->bullets[i] = current->bullet;
		current = current->next;
	}
	save->bullets_n = bullets_n;
	save->total_wins = total_wins;

	return true;
}

void output_save(GAME_SAVE *src) {
	FILE *file = fopen(SAVE_NAME, "w+");

	fprintf(file, "Stage: %d\n", src->stage);
	fprintf(file, "Turn: %d\n", src->turn);
	fprintf(file, "Lives1: %d\n", src->lives[0]);
	fprintf(file, "Lives2: %d\n", src->lives[1]);
	fprintf(file, "ItemSize: %llu\n", src->items_n);
	for (size_t i = 0; i < src->items_n; i++) {
		fprintf(file, "%u\n", src->items[i]);
	}
	fprintf(file, "BulletSize: %llu\n", src->bullets_n);
	for (size_t i = 0; i < src->bullets_n; i++) {
		fprintf(file, "%u\n", (unsigned int) src->bullets[i]);
	}
	fprintf(file, "Sawed: %u\n", src->sawed);
	fprintf(file, "Cuffed: %u\n", src->dealer_cuffed);

	fclose(file);
}

void output_save_inf(INFINITE_SAVE *src) {
	FILE *file = fopen(INFSAVE_NAME, "w+");

	fprintf(file, "Stage: %d\n", src->stage);
	fprintf(file, "Turn: %d\n", src->turn);
	fprintf(file, "Lives1: %d\n", src->lives[0]);
	fprintf(file, "Lives2: %d\n", src->lives[1]);
	fprintf(file, "ItemSize: %llu\n", src->items_n);
	for (size_t i = 0; i < src->items_n; i++) {
		fprintf(file, "%u\n", src->items[i]);
	}
	fprintf(file, "BulletSize: %llu\n", src->bullets_n);
	for (size_t i = 0; i < src->bullets_n; i++) {
		fprintf(file, "%u\n", (unsigned int)src->bullets[i]);
	}
	fprintf(file, "Sawed: %u\n", (unsigned int) src->sawed);
	fprintf(file, "Cuffed: %u\n", (unsigned int) src->dealer_cuffed);
	fprintf(file, "Wins: %llu\n", src->total_wins);

	fclose(file);
}

bool input_save(GAME_SAVE *dest) {
	FILE *file = fopen(SAVE_NAME, "r");

	fscanf(file, "Stage: %d\n", &(dest->stage));
	fscanf(file, "Turn: %d\n", &(dest->turn));
	fscanf(file, "Lives1: %d\n", &(dest->lives[0]));
	fscanf(file, "Lives2: %d\n", &(dest->lives[1]));
	fscanf(file, "ItemSize: %llu\n", &(dest->items_n));
	ITEM_T *temp1 = realloc(dest->items, dest->items_n * sizeof(ITEM_T));
	if (temp1 == 0)
		return false;
	dest->items = temp1;
	for (size_t i = 0; i < dest->items_n; i++) {
		fscanf(file, "%u\n", &(dest->items[i]));
	}
	fscanf(file, "BulletSize: %llu\n", &(dest->bullets_n));
	BULLET *temp2 = realloc(dest->bullets, dest->bullets_n * sizeof(BULLET));
	if (temp2 == 0)
		return false;
	dest->bullets = temp2;
	for (size_t i = 0; i < dest->bullets_n; i++) {
		fscanf(file, "%u\n", &(dest->bullets[i]));
	}
	int temp3 = -1;
	fscanf(file, "Sawed: %d\n", &temp3);
	dest->sawed = temp3 > 0;
	fscanf(file, "Cuffed: %hhi\n", &temp3);
	dest->dealer_cuffed = temp3 > 0;

	fclose(file);
}

bool input_save_inf(INFINITE_SAVE *dest) {
	return false;
}

void destroy_save(GAME_SAVE *save) {
	free(save);
}

void destroy_save_inf(INFINITE_SAVE *save) {
	free(save);
}