#include "playerTurn.h"
#include "dealerAI.h"
#include "textInput.h"
#include "gunHandler.h"
#include <stdio.h>
//need to add a way to leave the game, probably as an option

bool playerTurn(int lives[], BulletsLink* bullets, ITEM* items[], bool* oppHandcuffed, char* name) {

	fprintf(stdout, "-===- PLAYER TURN -===-\n");
	if (*oppHandcuffed) {
		fprintf(stdout, "Dealer is handcuffed.\n");
	}
	displayPlayerInfo(lives[PLAYER], items[PLAYER]);
	displayDealerInfo(lives[DEALER], items[DEALER]);
	//show choices to player
	//show usable items
	displayPlayerChoices(items[PLAYER]);
	//select choice using number from player
	int choice = getIntInput("Input a number: ");
	//if it's an item continue looping unless there's no usable items left
	//if it's the gun, ask player who they're going to shoot
}

void displayPlayerChoices(ITEM pItems[]) {
	fprintf(stdout, "Select an option: \n");
	fprintf(stdout, "1: Aim GUN.\n");
	fprintf(stdout, "2: Save Game.\n");
	fprintf(stdout, "3: Load Game.\n");
	int j = 3;
	for (int i = 0; i < ITEMS_CAP; i++) {
		if (pItems[i] != EMPTY) {
			j++;
			fprintf(stdout, "%d: Use item - %s\n", j, item_text(pItems[i]));
		}
	}
}

void displayPlayerInfo(int pLives, ITEM pItems[]) {
	fprintf(stdout, "Player Lives: % d\n", pLives);
	fprintf(stdout, "Player Items: ");
	for (int i = 0; i < ITEMS_CAP; i++) {
		if (pItems[i] != EMPTY) {
			fprintf(stdout, "%s ", item_text(pItems[i]));
		}
	}
	fprintf(stdout, "\n");
}