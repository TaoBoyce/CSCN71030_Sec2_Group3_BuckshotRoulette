#include "dealerAI.h"
#include "gunHandler.h"

bool dealerTurn(int lives[], BulletsLink* bullets, ITEM* items[], bool* oppHandcuffed, DIFFICULTY difficulty)
{
	/*
	MAGNIFYING_GLASS,
	CIGARETTE_PACK,
	BEER,
	HANDCUFFS,
	HAND_SAW
	*/
	displayDealerInfo(lives[DEALER], items);
	bool doubleDamage = false;
	bool bulletKnown = false;
	if (bulletCount == 1 && difficulty > EASY) {//need interface
		bulletKnown = true;
	}
	if (difficulty == EASY) {
		for (int i = 0; i < ITEMS_CAP; i++) {//need interface
			useItem(items[DEALER][i], bullets, oppHandcuffed, lives[DEALER], &doubleDamage, &bulletKnown);//need interface
		}
		//easy target shoots 50/50 if it's unknown
		bool shootSelf = determineTarget(items, bullets, oppHandcuffed, lives, &doubleDamage, &bulletKnown);//need interface
		return shootGun(lives, bullets, shootSelf, doubleDamage);
	}
	if (difficulty == MEDIUM) {
		/*
		always use cigarettes if life is lower than max
		always use handcuffs if not handcuffed
		use magnifying glass if not known
		if bullet is known and is LIVE, use handsaw

		if bullet is unknown, use beer
		*/
		//medium target shoots based on the chances of whichever is more likely
		bool shootSelf;
		return shootGun(lives, bullets, shootSelf, doubleDamage);
	}
	if (difficulty == HARD) {
		/*
		always use cigarettes if life is lower than max
		always use handcuffs if not handcuffed
		doesn't use magnifying glass if all remaining bullets are the same
		if bullet is known and is LIVE, use handsaw
		looks at the odds of getting a shot it wants before using beer

		*/
		//hard target shoots based on whatever reduces the net self damage possibility the most
		//looks at not only dealer things, but also player hp, handcuffed, player items
	}
	return false;
}