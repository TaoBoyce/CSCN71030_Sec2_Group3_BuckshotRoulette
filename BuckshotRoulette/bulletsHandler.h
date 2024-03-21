#pragma once

enum bullet {
	BLANK = 0,
	LIVE = 1
};

typedef struct bulletsNode {
	bullet bullet;
	struct bulletsNode* next;
}BulletsNode, *BulletsLink;

bullet popBullet(BulletsLink* link);

bullet peekBullet(BulletsLink link);