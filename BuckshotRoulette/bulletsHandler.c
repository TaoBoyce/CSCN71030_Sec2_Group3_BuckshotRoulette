#include "bulletsHandler.h"
#include <stdlib.h>
#include <stdio.h>

// Stub, replace in merge
// Doesn't really work
bool addBullet(BulletsLink head, BULLET type) {
	if (head == 0)
		return false;
	BulletsLink link = head;
	printf("Doing something else");
	while (link->next > 0) {
		link = link->next;
	}
	link->next = malloc(sizeof(BulletsLink));
	if (link->next == 0)
		return false;
	link->next->next = 0;
	link->next->bullet = type;
	return true;
}

// Stub
BulletsLink fillBullets(unsigned int n) {
	BulletsLink head = malloc(sizeof(BulletsNode));
	BulletsLink current = head;
	char b = 0;
	for (unsigned int i = 0; i < n; i++) {
		current->next = malloc(sizeof(BulletsNode));
		current = current->next;
		if (b)
			current->bullet = LIVE;
		else
			current->bullet = BLANK;
		b = !b;
	}

	return head;
}

// Stub
int bulletCount(BulletsLink head) {
	int i = 1;
	while (head->next != 0) {
		i++;
		head = head->next;
	}
	return i;
}