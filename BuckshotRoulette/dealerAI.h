#pragma once
//tao
#include "Main.h"
#include "bulletsHandler.h"
#include "itemsHandler.h"
#include <stdbool.h>

//returns true if skipping opponent's turn
bool dealerTurn(int lives[], BulletsLink* bullets, ITEM* items[], bool* oppHandcuffed, DIFFICULTY difficulty);

void displayDealerInfo(int dLives, ITEM items[]);

//returns true if shooting self
bool determineTarget(ITEM* items[], BulletsLink* bullets, int lives[], bool* doubleDamage, bool bulletKnown, DIFFICULTY difficulty);