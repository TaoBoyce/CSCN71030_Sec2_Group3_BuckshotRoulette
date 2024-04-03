#pragma once

typedef enum bullet {
	BLANK = 0,
	LIVE = 1
}BULLET;

typedef struct bulletsNode {
	BULLET bullet;
	struct bulletsNode* next;
}BulletsNode, *BulletsLink;

BULLET popBullet(BulletsLink* link);

BULLET peekBullet(BulletsLink link);