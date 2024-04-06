#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include"bulletsHandler.h"
#include"textInput.h"
#include "playerTurn.h"

int main(void) {
	//get console input
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
	BulletsLink bullets;
	loadRandomBullets(&bullets, 5);
	ITEM_T items[2][ITEMS_CAP];
	for (int i = 0; i < ITEMS_CAP; i++) {
		items[PLAYER][i] = EMPTY;
		items[DEALER][i] = EMPTY;
	}
	item_add(items, 4);
	bool oppHandcuffed = false;
	playerTurn(false, 1, 1, 1, lives, &bullets, items, &oppHandcuffed, "Tao");


	//clean up
	clearBullets(&bullets);
	return 0;
}
