#include "dealerAI.h"
#include "gunHandler.h"
#include "Main.h"
#include <stdlib.h>
#define MIN_RAND 1
#define MAX_RAND 100

bool dealerTurn(int lives[], BulletsLink* bullets, ITEM* items[], bool* oppHandcuffed, DIFFICULTY difficulty)
{
	/*
	MAGNIFYING_GLASS,
	CIGARETTE_PACK,
	BEER,
	HANDCUFFS,
	HAND_SAW
	*/
	displayDealerInfo(lives[DEALER], items[DEALER]);
	bool doubleDamage = false;
	bool bulletKnown = false;
	if (bulletCount() == 1) {//need interface
		bulletKnown = true;
	}
	if (difficulty == DIF_EASY) {
		/*
		easy item use:
		always use cigarettes if life is lower than max
		always use handcuffs if not handcuffed
		always use beer unless there's only one bullet left
		use magnifying glass if not known
		if bullet is known and is LIVE, use handsaw
		*/
		while (lives[DEALER] < MAX_LIVES && findItem(CIGARETTE_PACK, items[DEALER]) >= 0) {
			int index = findItem(CIGARETTE_PACK, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		if (!(*oppHandcuffed) && findItem(HANDCUFFS, items[DEALER]) >= 0) {
			int index = findItem(HANDCUFFS, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		while (bulletCount() > 1 && findItem(BEER, items[DEALER]) >= 0) {
			int index = findItem(BEER, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);

			if (bulletCount() == 1) {
				bulletKnown = true;
			}
		}
		if (!bulletKnown && findItem(MAGNIFYING_GLASS, items[DEALER]) >= 0) {
			int index = findItem(MAGNIFYING_GLASS, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		if (bulletKnown && !doubleDamage && findItem(HAND_SAW, items[DEALER]) >= 0) {
			int index = findItem(HAND_SAW, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}

		//easy target shoots 50/50 if it's unknown
		bool shootSelf = determineTarget(items, bullets, oppHandcuffed, lives, doubleDamage, bulletKnown, difficulty);
		return shootGun(lives, bullets, shootSelf, doubleDamage);
	}
	if (difficulty == DIF_MEDIUM) {
		/*
		same as easy item use except:
		if bullet is unknown, use beer
		*/
		while (lives[DEALER] < MAX_LIVES && findItem(CIGARETTE_PACK, items[DEALER]) >= 0) {
			int index = findItem(CIGARETTE_PACK, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		if (!(*oppHandcuffed) && findItem(HANDCUFFS, items[DEALER]) >= 0) {
			int index = findItem(HANDCUFFS, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		if (!bulletKnown && findItem(MAGNIFYING_GLASS, items[DEALER]) >= 0) {
			int index = findItem(MAGNIFYING_GLASS, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		while(!bulletKnown && findItem(BEER, items[DEALER]) >= 0) {
			int index = findItem(BEER, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);

			if (bulletCount() == 1) {
				bulletKnown = true;
			}
		}
		if (bulletKnown && !doubleDamage && findItem(HAND_SAW, items[DEALER]) >= 0) {
			int index = findItem(HAND_SAW, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}

		//medium target shoots based on the chances of whichever is more likely
		bool shootSelf = determineTarget(items, bullets, oppHandcuffed, lives, doubleDamage, bulletKnown, difficulty);
		return shootGun(lives, bullets, shootSelf, doubleDamage);
	}
	if (difficulty == DIF_HARD) {
		/*
		same as medium item use except:
		bullet is known if all remaining bullets are the same

		*/
		if (liveBullets(bullets) == 0 || blankBullets(bullets) == 0) {
			bulletKnown = true;
		}

		while (lives[DEALER] < MAX_LIVES && findItem(CIGARETTE_PACK, items[DEALER]) >= 0) {
			int index = findItem(CIGARETTE_PACK, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		if (!(*oppHandcuffed) && findItem(HANDCUFFS, items[DEALER]) >= 0) {
			int index = findItem(HANDCUFFS, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		if (!bulletKnown && findItem(MAGNIFYING_GLASS, items[DEALER]) >= 0) {
			int index = findItem(MAGNIFYING_GLASS, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}
		while (!bulletKnown && findItem(BEER, items[DEALER]) >= 0) {
			int index = findItem(BEER, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);

			if (bulletCount() == 1) {
				bulletKnown = true;
			}
			else if (liveBullets(bullets) == 0 || blankBullets(bullets) == 0) {
				bulletKnown = true;
			}
		}
		if (bulletKnown && !doubleDamage && findItem(HAND_SAW, items[DEALER]) >= 0) {
			int index = findItem(HAND_SAW, items);
			useItem(items[DEALER][index], bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);
		}


		//hard target shoots based on whatever reduces the net self damage possibility the most
		//looks at not only dealer things, but also player hp, handcuffed, player items
		bool shootSelf = determineTarget(items, bullets, oppHandcuffed, lives, &doubleDamage, bulletKnown, difficulty);
		return shootGun(lives, bullets, shootSelf, doubleDamage);
	}
	return false;
}

bool determineTarget(ITEM* items[], BulletsLink* bullets, int lives[], bool* doubleDamage, bool bulletKnown, DIFFICULTY difficulty) {
	if (bulletKnown) {//if bullet is known, always shoot correct target
		BULLET b = peekBullet(bullets);
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
			if (findItem(HAND_SAW, items[DEALER]) >= 0) {//use saw if you have it
				int index = findItem(HAND_SAW, items);
				items[DEALER][index] = EMPTY;
				*doubleDamage = true;
			}

			return false;
		}

		//dealer lives are at least 2 at this point
		//if you have a handsaw and there's a chance to kill, just attempt to shoot the player with the handsaw
		if (findItem(HAND_SAW, items[DEALER]) >= 0 && lives[PLAYER] <= 2 && bulletCount(bullets) <= 3 && live >= 1) {
			int index = findItem(HAND_SAW, items);
			items[DEALER][index] = EMPTY;
			*doubleDamage = true;

			return false;
		}

		//if dealer lives are at 2 and player has handsaw and there's a chance to die if player goes,
		//shoot self
		if (findItem(HAND_SAW, items[PLAYER]) >= 0 && lives[DEALER] == 2 && bulletCount(bullets) <= 3 && live >= 1) {
			return true;
		}

		if (blank / live == 1) {
			shootSelf = rand() % 2;//random if equal odds
		}
		else {
			shootSelf = blank / live > 1;//choose the one with bigger odds
		}

		return shootSelf;
	}
}