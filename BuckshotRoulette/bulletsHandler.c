#include "bulletsHandler.h"

BULLET popBullet(BulletsLink* link)
{
	//temporary, for testing
	BulletsLink current = *link;
	return current->bullet;
}
