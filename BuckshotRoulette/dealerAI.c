#include "dealerAI.h"
#include "gunHandler.h"
#include "Main.h"
#include <stdio.h>
#include <stdlib.h>

bool dealerTurn(int lives[2], BulletsLink* bullets, ITEM_T items[2][ITEMS_CAP], bool* oppHandcuffed, DIFFICULTY difficulty)
{
	/*
	MAGNIFYING_GLASS,
	CIGARETTE_PACK,
	BEER,
	HANDCUFFS,
	HAND_SAW
	*/
	fprintf(stdout, "\n-===- DEALER TURN -===-\n");
	displayDealerInfo(lives[DEALER], items[DEALER]);
	bool doubleDamage = false;
	bool bulletKnown = false;

	/*
	all difficulties:
		always use cigarettes if life is lower than max
		always use handcuffs if not handcuffed
	*/
	if (bulletCount(*bullets) == 1) {//need interface
		bulletKnown = true;
	}
	while (lives[DEALER] < MAX_LIVES && findItem(CIGARETTE_PACK, items[DEALER], ITEMS_CAP) >= 0) {
		int index = findItem(CIGARETTE_PACK, items[DEALER], ITEMS_CAP);
		useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
	}
	if (!(*oppHandcuffed) && findItem(HANDCUFFS, items[DEALER], ITEMS_CAP) >= 0) {
		int index = findItem(HANDCUFFS, items[DEALER], ITEMS_CAP);
		useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
	}

	if (difficulty == DIF_EASY) {
		/*
		easy item use:
		always use beer unless there's only one bullet left
		use magnifying glass if not known
		if bullet is known and is LIVE, use handsaw
		*/
		while (bulletCount(*bullets) > 1 && findItem(BEER, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(BEER, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);

			if (bulletCount(*bullets) == 1) {
				bulletKnown = true;
			}
		}
		if (!bulletKnown && findItem(MAGNIFYING_GLASS, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(MAGNIFYING_GLASS, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
		}
		if (bulletKnown && !doubleDamage && findItem(HAND_SAW, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(HAND_SAW, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
		}

		//easy target shoots 50/50 if it's unknown
		bool shootSelf = determineTarget(items, bullets, lives, &doubleDamage, bulletKnown, difficulty);
		fprintf(stdout, "\nThe Dealer has decided to shoot:");
		if (shootSelf) {
			fprintf(stdout, " Themselves.\n");
		}
		else {
			fprintf(stdout, " You.\n");
		}
		return shootGun(&lives[shootSelf], bullets, shootSelf, doubleDamage);
	}
	if (difficulty == DIF_MEDIUM) {
		/*
		same as easy item use except:
		if bullet is unknown, use beer
		*/
		if (!bulletKnown && findItem(MAGNIFYING_GLASS, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(MAGNIFYING_GLASS, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
		}
		while(!bulletKnown && findItem(BEER, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(BEER, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);

			if (bulletCount(*bullets) == 1) {
				bulletKnown = true;
			}
		}
		if (bulletKnown && !doubleDamage && findItem(HAND_SAW, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(HAND_SAW, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
		}

		//medium target shoots based on the chances of whichever is more likely
		bool shootSelf = determineTarget(items, bullets, lives, &doubleDamage, bulletKnown, difficulty);
		fprintf(stdout, "\nThe Dealer has decided to shoot:");
		if (shootSelf) {
			fprintf(stdout, " Themselves.\n");
		}
		else {
			fprintf(stdout, " You.\n");
		}
		return shootGun(&lives[shootSelf], bullets, shootSelf, doubleDamage);
	}
	if (difficulty == DIF_HARD) {
		/*
		same as medium item use except:
		bullet is known if all remaining bullets are the same

		*/
		if (liveBullets(bullets) == 0 || blankBullets(bullets) == 0) {
			bulletKnown = true;
		}

		if (!bulletKnown && findItem(MAGNIFYING_GLASS, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(MAGNIFYING_GLASS, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
		}
		while (!bulletKnown && findItem(BEER, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(BEER, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);

			if (bulletCount(*bullets) == 1) {
				bulletKnown = true;
			}
			else if (liveBullets(bullets) == 0 || blankBullets(bullets) == 0) {
				bulletKnown = true;
			}
		}
		if (bulletKnown && !doubleDamage && findItem(HAND_SAW, items[DEALER], ITEMS_CAP) >= 0) {
			int index = findItem(HAND_SAW, items[DEALER], ITEMS_CAP);
			useItem(&(items[DEALER][index]), bullets, oppHandcuffed, &lives[DEALER], &doubleDamage, &bulletKnown);
		}


		//hard target shoots based on whatever reduces the net self damage possibility the most
		//looks at not only dealer things, but also player hp, handcuffed, player items
		bool shootSelf = determineTarget(items, bullets, lives, &doubleDamage, bulletKnown, difficulty);
		fprintf(stdout, "\nThe Dealer has decided to shoot:");
		if (shootSelf) {
			fprintf(stdout, " Themselves.\n");
		}
		else {
			fprintf(stdout, " You.\n");
		}
		return shootGun(&lives[shootSelf], bullets, shootSelf, doubleDamage);
	}
	return false;
}

bool determineTarget(ITEM_T* items[], BulletsLink* bullets, int lives[], bool* doubleDamage, bool bulletKnown, DIFFICULTY difficulty) {
	if (bulletKnown) {//if bullet is known, always shoot correct target
		BULLET b = peekBullet(*bullets);
		if (b == LIVE) {
			return false;
		}
		else {
			return true;
		}
	}
	//bullet is not known from here on
	if (difficulty == DIF_EASY) {// 50/50 for shoot self or enemy
		bool shootSelf = rand() % 2;
		return shootSelf;
	}
	if (difficulty == DIF_MEDIUM) {//change dynamically depending on LIVE BLANK ratio
		int live = liveBullets(bullets);
		int blank = blankBullets(bullets);
		bool shootSelf;

		if (lives[DEALER] == 1) {//don't shoot self if lives are at 1
			return false;
		}

		if (blank / live == 1) {
			shootSelf = rand() % 2;//random if equal odds
		}
		else {
			shootSelf = blank / live > 1;//choose the one with bigger odds
		}
		return shootSelf;
	}
	if (difficulty == DIF_HARD) {//change dynamically depending on all data avalible
		int live = liveBullets(bullets);
		int blank = blankBullets(bullets);
		bool shootSelf;

		if (lives[DEALER] == 1) {//don't shoot self if lives are at 1
			if (findItem(HAND_SAW, items[DEALER], ITEMS_CAP) >= 0) {//use saw if you have it
				int index = findItem(HAND_SAW, items[DEALER], ITEMS_CAP);
				items[DEALER][index] = EMPTY;
				*doubleDamage = true;
				fprintf(stdout, "Used item: HAND SAW.\n");
				fprintf(stdout, "The next LIVE bullet shot THIS TURN will deal double damage.\n");
			}

			return false;
		}

		//dealer lives are at least 2 at this point
		//if you have a handsaw and there's a chance to kill, just attempt to shoot the player with the handsaw
		if (findItem(HAND_SAW, items[DEALER], ITEMS_CAP) >= 0 && lives[PLAYER] <= 2 && bulletCount(*bullets) <= 3 && live >= 1, ITEMS_CAP) {
			int index = findItem(HAND_SAW, items[DEALER], ITEMS_CAP);
			items[DEALER][index] = EMPTY;
			*doubleDamage = true;
			fprintf(stdout, "Used item: HAND SAW.\n");
			fprintf(stdout, "The next LIVE bullet shot THIS TURN will deal double damage.\n");

			return false;
		}

		//if dealer lives are at 2 and player has handsaw and there's a chance to die if player goes,
		//shoot self
		if (findItem(HAND_SAW, items[PLAYER], ITEMS_CAP) >= 0 && lives[DEALER] == 2 && bulletCount(*bullets) <= 3 && live >= 1, ITEMS_CAP) {
			return true;
		}

		if (blank / live == 1) {
			shootSelf = rand() % 2;//random if equal odds
		}
		else if (live == 1 && blank == 2) {
			shootSelf = false;
		}
		else {
			shootSelf = blank / live > 1;//choose the one with bigger odds
		}
		
		return shootSelf;
	}
	return false;
}

void displayDealerInfo(int dLives, ITEM_T items[]) {
	fprintf(stdout, "Dealer Lives: %d\n", dLives);
	fprintf(stdout, "Dealer Items: ");
	for (int i = 0; i < ITEMS_CAP; i++) {
		if (items[i] != EMPTY) {
			fprintf(stdout, "%s | ", item_text(items[i]));
		}
	}
	fprintf(stdout, "\n");
}