#pragma once

typedef enum bullet {
	BLANK = 0,
	LIVE = 1
}BULLET;

typedef struct bulletsNode {
	BULLET bullet;
	struct bulletsNode* next;
}BulletsNode, * BulletLink;

void loadRandomBullets(BulletLink* head, int numBullets);

void clearBullets(BulletLink* head);

void addBullet(BulletLink* head, bullet type);

void printBulletsInOrder(BulletLink head);

bullet peekBullet(BulletLink head);

bullet popBullet(BulletLink* head);

bullet fireBullet(BulletLink* head);

void printBulletCounts(BulletLink head);

