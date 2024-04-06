#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include"bulletsHandler.h"
#include"textInput.h"
#include "playerTurn.h"

int main(int argc, char **argv) {
	//get console input
	DIFFICULTY difficulty = DIF_EASY;
	bool infiniteMode = false;
	for (int i = 0; i < argc; ++i)
	{
		int num;
		if (sscanf_s(argv[0], "%d", &num) == 1) {
			difficulty = convertDifficultyFromBitFlag(num);
			if (num & INFINITE_FLAG) {
				infiniteMode = true;
			}
		}
	}
	//convert console input to infinite mode and difficulty
	//ask for name
	//start round
	//load bullets and items
	//loop player's turn until they don't skip opponent/run out of bullets
	//loop dealer's turn until they don't skip opponent/run out of bullets
	//loop both of the above until one of their lives hits 0
	//3 rounds in non-infinite
	//infinite rounds in infinite
	int lives[2] = { 5,5 };
	BulletsLink bullets = NULL;
	ITEM_T items[2][ITEMS_CAP];
	for (int i = 0; i < ITEMS_CAP; i++) {
		items[PLAYER][i] = EMPTY;
		items[DEALER][i] = EMPTY;
	}
	item_add(items, 4);
	bool oppHandcuffed = false;
	//clean up
	clearBullets(&bullets);
	return 0;
}


DIFFICULTY convertDifficultyFromBitFlag(int bitflag) {
	if (bitflag & DIF_HARD) {
		return DIF_HARD;
	}
	if (bitflag & MEDIUM_FLAG) {
		return DIF_MEDIUM;
	}
	if (bitflag & EASY_FLAG) {
		return DIF_EASY;
	}
}