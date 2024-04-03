#include "itemsHandler.h"
#include "Main.h"
#include <stdio.h>


bool useItem(ITEM *pItem, BulletsLink* bullets, bool* oppHandcuffed, int* lives, bool* doubleDamage, bool* bulletKnown) {
	ITEM item = *pItem;
	if (item == BEER) {
		if (bulletCount(bullets) == 0) {
			fprintf(stdout, "Tried to use item: BEER.\n");
			fprintf(stdout, "No bullets are loaded, item was not used.\n");
			return false;
		}
		*pItem = EMPTY;//change item to empty
		BULLET b = popBullet(bullets);
		fprintf(stdout, "Used item: BEER.\n");
		fprintf(stdout, "Ejected a bullet from the gun.\n");
		if (b == LIVE) {
			fprintf(stdout, "The bullet was LIVE.\n");
		}
		else {
			fprintf(stdout, "The bullet was BLANK.\n");
		}
		return true;
	}
	if (item == MAGNIFYING_GLASS) {
		*pItem = EMPTY;//change item to empty
		BULLET b = peekBullet(*bullets);
		fprintf(stdout, "Used item: MAGNIFYING GLASS.\n");
		fprintf(stdout, "Peeked at the next bullet.\n");
		if (b == LIVE) {
			fprintf(stdout, "The bullet was LIVE.\n");
		}
		else {
			fprintf(stdout, "The bullet was BLANK.\n");
		}
		return true;
	}
	if (item == CIGARETTE_PACK) {
		if (*lives < MAX_LIVES) {
			*pItem = EMPTY;//change item to empty
			(*lives)++;
			fprintf(stdout, "Used item: CIGARETTE PACK.\n");
			fprintf(stdout, "Healed 1 health, to %d.\n", *lives);
			return true;
		}
		fprintf(stdout, "Tried to use: CIGARRETE PACK.\n");
		fprintf(stdout, "Health is already at max (%d), item was not used.\n", *lives);
		return false;
	}
	if (item == HANDCUFFS) {
		if (!(*oppHandcuffed)) {
			*pItem = EMPTY;//change item to empty
			(*lives)++;
			fprintf(stdout, "Used item: HANDCUFFS.\n");
			fprintf(stdout, "Opponent's next turn will be skipped.\n");
			return true;
		}
		fprintf(stdout, "Tried to use: HANDCUFFS.\n");
		fprintf(stdout, "Opponent is already cuffed, item was not used.\n");
		return false;

	}
	if (item == HAND_SAW) {
		if (!(*doubleDamage)) {
			*pItem = EMPTY;//change item to empty
			(*lives)++;
			fprintf(stdout, "Used item: HAND SAW.\n");
			fprintf(stdout, "The next LIVE bullet shot THIS TURN will deal double damage.\n");
			return true;
		}
		fprintf(stdout, "Tried to use: HAND SAW.\n");
		fprintf(stdout, "Double damage is already active, item was not used.\n");
		return false;
	}
	return false;//no item match
}