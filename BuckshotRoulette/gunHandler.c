#include "gunHandler.h"
#include <stdio.h>

bool shootGun(int* lives, BulletsLink* bullets, bool facingSelf, bool doubleDamage)
{
	BULLET b = popBullet(bullets);
	int damage = 1 + 1 * doubleDamage;
	if (facingSelf) {		//gun pointed at user
		if (b == LIVE) {
			*lives = *lives - damage;
			fprintf(stdout, "\nBANG! Took %d damage.\n", damage);
			return false;
		}
		if (b == BLANK) {
			fprintf(stdout, "\nClick! Skipped opponent's turn.\n");
			return true;
		}
		return false; //bad bullet
	}
							//gun pointed at enemy
	if (b == LIVE) {
		*lives = *lives - damage;
		fprintf(stdout, "BANG! Dealt %d damage.\n", damage);
	}
	else {
		fprintf(stdout, "Click! Did no damage.\n");
	}

	return false;
}
