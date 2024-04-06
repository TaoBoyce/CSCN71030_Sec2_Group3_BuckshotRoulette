
#include"bulletsHandler.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void loadRandomBullets(BulletsLink* head, int numBullets) {
	srand(time(NULL));
	for (int i = 0; i < numBullets; i++) {
		BULLET type = rand() % 2 == 0 ? LIVE : BLANK;
		addBullet(head, type);
	}
}

void clearBullets(BulletsLink* head) {
	while (*head != NULL) {
		BulletsNode* temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void addBullet(BulletsLink* head, BULLET type) {
	BulletsNode* newNode = (BulletsNode*)malloc(sizeof(BulletsNode));
	if (newNode == NULL) {
		printf("Error adding bullet: no memory\n");
		return;
	}
	newNode->bullet = type;
	newNode->next = *head;
	*head = newNode;
}
//This is a test function will not be included in the main game unless needed
void printBulletsInOrder(BulletsLink head) {
	printf("Bullets in order of firing:\n");
	BulletsNode* current = head;
	while (current != NULL) {
		printf("%s\n", current->bullet == LIVE ? "LIVE" : "BLANK");
		current = current->next;
	}
}

BULLET peekBullet(BulletsLink head) {
	if (head == NULL)
		return BLANK;
	return head->bullet;
}

BULLET popBullet(BulletsLink* head) {
	if (*head == NULL)
		return BLANK;

	BulletsNode* temp = *head;
	BULLET type = temp->bullet;
	*head = (*head)->next;
	free(temp);

	return type;
}

void printBulletCounts(BulletsLink head) {
	int liveCount = 0, blankCount = 0;
	BulletsNode* current = head;

	while (current != NULL)
	{
		if (current->bullet == LIVE)
			liveCount++;
		else
			blankCount++;
		current = current->next;
	}
	printf("Live bullets count: %d\n", liveCount);
	printf("Blank bullets count: %d\n", blankCount);
}



int bulletCount(BulletsLink head) {
	int count = 0;
	BulletsNode* current = head;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

int liveBullets(BulletsLink head) {
	int count = 0;
	BulletsNode* current = head;
	while (current != NULL) {
		if (current->bullet == LIVE)
			count++;
		current = current->next;
	}
	return count;
}

int blankBullets(BulletsLink head) {
	int count = 0;
	BulletsNode* current = head;
	while (current != NULL) {
		if (current->bullet == BLANK)
			count++;
		current = current->next;
	}
	return count;
}
