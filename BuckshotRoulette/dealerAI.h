#pragma once
//tao
#include "Main.h"
#include "bulletsHandler.h"
#include "itemsHandler.h"
#include <stdbool.h>

//returns true if skipping opponent's turn
bool dealerTurn(int lives[], BulletsLink* bullets, ITEM_T items[2][ITEMS_CAP], bool* oppHandcuffed, DIFFICULTY difficulty);

void displayDealerInfo(int dLives, ITEM_T items[]);

//returns true if shooting self
bool determineTarget(ITEM_T* items[], BulletsLink* bullets, int lives[], bool* doubleDamage, bool bulletKnown, DIFFICULTY difficulty);
