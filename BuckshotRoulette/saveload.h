#pragma once
#include <stdbool.h>
#include "itemsHandler.h"

typedef struct gamesave {
	int stage;
	int turn;
	int lives[2];
	ITEM_T *items;
	size_t items_n;
	bool sawed;
	bool dealer_cuffed;
} GAME_SAVE;

typedef struct infsave {
	int stage;
	int turn;
	int lives[2];
	ITEM_T *items;
	size_t items_n;
	bool sawed;
	bool dealer_cuffed;
	unsigned long long total_wins;
} INFINITE_SAVE;

GAME_SAVE *create_save();

INFINITE_SAVE *create_save_infinite();

bool update_save(GAME_SAVE *save, int stage, int turn, int *lives, ITEM_T *items, size_t items_n, bool sawed, bool dealer_cuffed);

bool update_save_inf(INFINITE_SAVE *save, int stage, int turn, int *lives, char *items, size_t items_n, bool sawed, 
bool dealer_cuffed, unsigned long long total_wins);

void output_save(GAME_SAVE *src);

void output_save_inf(INFINITE_SAVE *src);

bool input_save(GAME_SAVE *dest);

bool input_save_inf(INFINITE_SAVE *dest);

void destroy_save(GAME_SAVE *save);

void destroy_save_inf(INFINITE_SAVE *save);