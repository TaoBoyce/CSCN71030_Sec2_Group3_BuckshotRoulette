#pragma once
//tao
#include "Main.h"
#include "bulletsHandler.h"
#include "itemsHandler.h"
#include <stdbool.h>

//returns true if skipping opponent's turn
bool playerTurn(int lives[], BulletsLink* bullets, item items[], bool* oppHandcuffed, DIFFICULTY difficulty);

void displayDealerInfo(int dLives, item dItems[]);