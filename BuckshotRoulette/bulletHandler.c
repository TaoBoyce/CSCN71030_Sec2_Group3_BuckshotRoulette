#include"bulletsHandler.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void loadRandomBullets(BulletLink* head, int numBullets) {
	srand(time(NULL));
	for (int i = 0; i < numBullets; i++) {
		bullet type = rand() % 2 == 0 ? LIVE : BLANK;
		addBullet(head, type);
	}
}

void clearBullets(BulletLink* head) {
	while (*head != NULL) {
		BulletsNode* temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}

void addBullet(BulletLink* head, bullet type) {
	BulletsNode* newNode = (BulletsNode*)malloc(sizeof(BulletsNode));
	newNode->bullet = type;
	newNode->next = *head;
	*head = newNode;
}
//This is a test function will not be included in the main game unless needed
void printBulletsInOrder(BulletLink head) {
	printf("Bullets in order of firing:\n");
	BulletsNode* current = head;
	while (current != NULL) {
		printf("%s\n", current->bullet == LIVE ? "LIVE" : "BLANK");
		current = current->next;
	}
}

bullet peekBullet(BulletLink head) {
	if (head == NULL)
		return BLANK;
	return head->bullet;
}

bullet popBullet(BulletLink* head) {
	if (*head == NULL)
		return BLANK;

	BulletsNode* temp = *head;
	bullet type = temp->bullet;
	*head = (*head)->next;
	free(temp);

	return type;
}

bullet fireBullet(BulletLink* head) {
	if (*head == NULL)
		return BLANK;
	BulletsNode* temp = *head;
	bullet type = temp->bullet;
	*head = (*head)->next;
	free(temp);
	return type;
}

void printBulletCounts(BulletLink head) {
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