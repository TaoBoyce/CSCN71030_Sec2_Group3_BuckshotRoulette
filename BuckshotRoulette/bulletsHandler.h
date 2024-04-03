#pragma once

typedef enum bullet {
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

BULLET peekBullet(BulletsLink head);

BULLET popBullet(BulletsLink* head);

BULLET fireBullet(BulletsLink* head);

void printBulletCounts(BulletsLink head);

