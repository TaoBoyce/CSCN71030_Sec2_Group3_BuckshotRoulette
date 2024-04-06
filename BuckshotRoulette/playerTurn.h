#pragma once
//tao
#include "Main.h"
#include "bulletsHandler.h"
#include "itemsHandler.h"
#include <stdbool.h>

//returns true if skipping opponent's turn
bool playerTurn(bool infiniteMode, int* stage, int* turn, int* totalWins, int lives[], BulletsLink* bullets, ITEM_T items[2][ITEMS_CAP], bool* oppHandcuffed, char* name, bool* quit);

void displayPlayerInfo(int pLives, ITEM pItems[]);

void displayPlayerChoices(ITEM pItems[]);