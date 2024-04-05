#pragma once
//tao
//handles changing lives
#include "bulletsHandler.h"
#include <stdbool.h>

//still need to do unit tests
bool shootGun(int* lives, BulletsLink* bullets, bool facingSelf, bool doubleDamage);
