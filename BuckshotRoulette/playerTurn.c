#include "playerTurn.h"
#include "dealerAI.h"
#include "textInput.h"
#include "gunHandler.h"
#include "saveload.h"
#include <stdio.h>
//need to add a way to leave the game, probably as an option

bool playerTurn(bool infiniteMode, int* stage, int* turn, int* totalWins, int lives[], BulletsLink* bullets, ITEM_T items[2][ITEMS_CAP], bool* oppHandcuffed, char* name, bool* quit) {
	int choice = 0;
	bool doubleDamage = false;
	bool bulletKnown = false;
startOfTurn:
	fprintf(stdout, "\n-===- PLAYER TURN -===-\n");
	while (choice != 1) {
		//show player info
		if (*oppHandcuffed) {
			fprintf(stdout, "Dealer is handcuffed.\n");
		}
		if (doubleDamage) {
			fprintf(stdout, "The next LIVE shot will deal double damage.\n");
		}
		displayPlayerInfo(lives[PLAYER], items[PLAYER]);
		displayDealerInfo(lives[DEALER], items[DEALER]);
		fprintf(stdout, "%d bullets left.\n", bulletCount(*bullets));
		//show choices to player
		//show usable items
		displayPlayerChoices(items[PLAYER]);
		//select choice using number from player
		choice = getIntInput("Input a number");
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
			
			if (infiniteMode) {
				INFINITE_SAVE* save = create_save_infinite();
				update_save_inf(save, *stage, *turn, lives, items, ITEMS_CAP, *bullets, bulletCount(*bullets), *oppHandcuffed, totalWins);
				output_save_inf(save);
				destroy_save_inf(save);
			}
			else {
				GAME_SAVE* save = create_save();
				update_save(save, *stage, *turn, lives, items, ITEMS_CAP, *bullets, bulletCount(*bullets), *oppHandcuffed);
				output_save(save);
				destroy_save(save);
			}
			fprintf(stdout, "\nGame Saved!\n\n");
			continue;
		}
		if (choice == 3) {
			//load game

			if (infiniteMode) {
				INFINITE_SAVE* save = create_save_infinite();
				input_save(save);
				*stage = save->stage;
				*turn = save->turn;
				lives[PLAYER] = save->lives[PLAYER];
				lives[DEALER] = save->lives[DEALER];
				for (int i = 0; i < ITEMS_CAP*2; i++) {
					if (i < ITEMS_CAP) {//save treats the 2D array as a 1D array
						items[PLAYER][i] = save->items[i];
					}
					else {
						items[DEALER][i-ITEMS_CAP] = save->items[i];
					}
				}
				clearBullets(bullets);//clear out stack for new bullets
				for (int i = save->bullets_n - 1; i >= 0; i--) {//iterate through array backwards
					addBullet(bullets, save->bullets[i]);
				}
				*oppHandcuffed = save->dealer_cuffed;
				*totalWins = save->total_wins;
				destroy_save_inf(save);
			}
			else {
				GAME_SAVE* save = create_save();
				input_save(save);
				*stage = save->stage;
				*turn = save->turn;
				lives[PLAYER] = save->lives[PLAYER];
				lives[DEALER] = save->lives[DEALER];
				for (int i = 0; i < ITEMS_CAP * 2; i++) {
					if (i < ITEMS_CAP) {//save treats the 2D array as a 1D array
						items[PLAYER][i] = save->items[i];
					}
					else {
						items[DEALER][i - ITEMS_CAP] = save->items[i];
					}
				}
				clearBullets(bullets);//clear out stack for new bullets
				for (int i = save->bullets_n-1; i >= 0; i--) {//iterate through array backwards
					addBullet(bullets, save->bullets[i]);
				}
				*oppHandcuffed = save->dealer_cuffed;
				destroy_save(save);
			}
			fprintf(stdout, "\nGame Loaded!\n\n");
			//show start of turn again 
			goto startOfTurn;
			continue;
		}
		if (choice == 4) {
			//quit
			fprintf(stdout, "\nQuitting...\n");
			*quit = true;
			return;
		}
		//done this way so it matches up with the display
		int j = 4;
		for (int i = 0; i < ITEMS_CAP; i++) {
			ITEM_T* pItem = &(items[PLAYER][i]);
			if (*pItem == (ITEM_T)EMPTY) {
				continue;
			}
			j++;
			if (j == choice) {
				useItem(pItem, bullets, oppHandcuffed, &(lives[PLAYER]), &doubleDamage, &bulletKnown);
				if (bulletCount(*bullets) == 0) {//if the player decides to rack all the bullets
					return false;
				}
				break;
			}
		}
	}
	
	//if it's the gun, ask player who they're going to shoot
	fprintf(stdout, "\nSelect an option: \n");
	fprintf(stdout, "1: Shoot the Dealer.\n");
	fprintf(stdout, "2: Shoot yourself. (Shooting yourself with a blank skips the opponent's turn.)\n");
	int target = 0;
	while (target != 1 && target != 2) {
		target = getIntInput("Input a number");
		if (target != 1 && target != 2) {
			fprintf(stdout, "Invalid input, try again.\n");
		}
	}

	if (target == 1) {//shoot dealer
		return shootGun(&lives[DEALER], bullets, false, doubleDamage);
	}
	if (target == 2) {//shoot self
		return shootGun(&lives[PLAYER], bullets, true, doubleDamage);
	}
	return false;
}

void displayPlayerChoices(ITEM_T pItems[]) {
	fprintf(stdout, "Select an option: \n");
	fprintf(stdout, "1: Aim GUN. (Ends the turn.)\n");
	fprintf(stdout, "2: Save Game.\n");
	fprintf(stdout, "3: Load Game.\n");
	fprintf(stdout, "4: Quit the game (Without saving)\n");
	int j = 4;
	for (int i = 0; i < ITEMS_CAP; i++) {
		if (pItems[i] == EMPTY) {
			continue;
		}
		j++;
		fprintf(stdout, "%d: Use item - %s\n", j, item_text(pItems[i]));
	}
}

void displayPlayerInfo(int pLives, ITEM_T pItems[]) {
	fprintf(stdout, "Player Lives: %d\n", pLives);
	fprintf(stdout, "Player Items: ");
	for (int i = 0; i < ITEMS_CAP; i++) {
		if (pItems[i] != EMPTY) {
			fprintf(stdout, "%s | ", item_text(pItems[i]));
		}
	}
	fprintf(stdout, "\n");
}