#include "playerTurn.h"
#include "dealerAI.h"

bool playerTurn(int lives[], BulletsLink* bullets, ITEM* items[], bool* oppHandcuffed, char* name) {
	
	displayPlayerInfo(lives[PLAYER], items[PLAYER]);
	displayDealerInfo(lives[DEALER], items[DEALER]);
	//show choices to player
	//show usable items
	//select choice using number from player
	//if it's an item continue looping unless there's no usable items left
	//if it's the gun, ask player who they're going to shoot
}

void displayPlayerInfo(int pLives, ITEM pItems[]);