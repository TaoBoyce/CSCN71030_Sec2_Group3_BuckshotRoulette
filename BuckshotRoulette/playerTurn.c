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
	int choice = 0;
	bool doubleDamage = false;
	bool bulletKnown = false;
	while (choice != 1) {
		choice = getIntInput("Input a number: ");
		//if it's an item continue looping unless there's no usable items left
		if (choice <= 0) {
			fprintf(stdout, "Invalid input, try again.\n");
			continue;
		}
		if (choice == 1) {//aim gun was chosen
			break;
		}
		if (choice == 2) {
			//save game
			continue;
		}
		if (choice == 3) {
			//load game
			continue;
		}
		//done this way so it matches up with the display
		int j = 3;
		for (int i = 0; i < ITEMS_CAP; i++) {
			ITEM* pItem = &(items[PLAYER][i]);
			if (pItem == EMPTY) {
				continue;
			}
			j++;
			if (j == choice) {
				useItem(pItem, bullets, oppHandcuffed, &(lives[PLAYER]), &doubleDamage, &bulletKnown);
				if (bulletCount(bullets) == 0) {//if the player decides to rack all the bullets
					return false;
				}
				break;
			}
		}
	}
	
	//if it's the gun, ask player who they're going to shoot
	fprintf(stdout, "Select an option: \n");
	fprintf(stdout, "1: Shoot the Dealer.\n");
	fprintf(stdout, "2: Shoot yourself. (Shooting yourself with a blank skips the opponent's turn.)\n");
	int target = 0;
	while (target != 1 && target != 2) {
		target = getIntInput("Input a number: ");
		if (target != 1 && target != 2) {
			fprintf(stdout, "Invalid input, try again.\n");
		}
	}

	if (target == 1) {//shoot dealer
		return shootGun(lives[DEALER], bullets, false, doubleDamage);
	}
	if (target == 2) {//shoot self
		return shootGun(lives[PLAYER], bullets, true, doubleDamage);
	}
	return false;
}

void displayPlayerChoices(ITEM pItems[]) {
	fprintf(stdout, "Select an option: \n");
	fprintf(stdout, "1: Aim GUN. (Ends the turn.)\n");
	fprintf(stdout, "2: Save Game.\n");
	fprintf(stdout, "3: Load Game.\n");
	int j = 3;
	for (int i = 0; i < ITEMS_CAP; i++) {
		if (pItems[i] == EMPTY) {
			continue;
		}
		j++;
		fprintf(stdout, "%d: Use item - %s\n", j, item_text(pItems[i]));
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