#pragma once

typedef enum bullet{
	BLANK = 0,
	LIVE = 1
}BULLET;

typedef struct bulletsNode {
	BULLET bullet;
	struct bulletsNode* next;
}BulletsNode, * BulletsLink;

void loadRandomBullets(BulletsLink* head, int numBullets);

void clearBullets(BulletsLink* head);

void addBullet(BulletsLink* head, BULLET type);

void printBulletsInOrder(BulletsLink head);

bullet peekBullet(BulletsLink head);

bullet popBullet(BulletsLink* head);

void printBulletCounts(BulletsLink head);

int bulletCount(BulletsLink* head);

int blankBullets(BulletsLink* head);

int liveBullets(BulletsLink* head);


