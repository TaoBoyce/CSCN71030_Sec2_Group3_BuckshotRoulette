#pragma once
//tao
#include "Main.h"
#include "bulletsHandler.h"
#include "itemsHandler.h"
#include <stdbool.h>

//returns true if skipping opponent's turn
bool playerTurn(int lives[], BulletsLink* bullets, ITEM* items[], bool* oppHandcuffed, char* name);

void displayPlayerInfo(int pLives, ITEM pItems[]);