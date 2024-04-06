#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include"bulletsHandler.h"
#include"textInput.h"
#include "playerTurn.h"
#include "dealerAI.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#define WAIT_TIME 1

int main(int argc, char **argv) {
	srand(time(NULL));
	//get console input
	//convert console input to infinite mode and difficulty
	DIFFICULTY difficulty = DIF_EASY;
	bool infiniteMode = false;
	for (int i = 0; i < argc; ++i)
	{
		int num;
		if (sscanf_s(argv[0], "%d", &num) == 1) {
			difficulty = convertDifficultyFromBitFlag(num);
			if (num & INFINITE_FLAG) {
				infiniteMode = true;
			}
		}
	}
	fprintf(stdout, "Difficulty: ");
	switch (difficulty) {
	case DIF_EASY:
		fprintf(stdout, "Easy\n");
	case DIF_MEDIUM:
		fprintf(stdout, "Medium\n");
	case DIF_HARD:
		fprintf(stdout, "Hard\n");
	}
	fprintf(stdout, "Infinite mode: ");
	if (infiniteMode) {
		fprintf(stdout, "True\n");
	}
	else {
		fprintf(stdout, "False\n");
	}
	//ask for name
	char* name = getTextInput("Input your name");
	//start round
	int stage = 0;
	int round = 0;
	int totalWins = 0;
	int lives[2] = { stage * 2, stage * 2 };
	//load bullets and items
	BulletsLink bullets = NULL;
	ITEM_T items[2][ITEMS_CAP];
	for (int i = 0; i < ITEMS_CAP; i++) {
		items[PLAYER][i] = EMPTY;
		items[DEALER][i] = EMPTY;
	}

	start_of_stage:
	//start of stage
	stage++;
	round = 0;
	fprintf(stdout, "\n---=========== START OF STAGE %d ===========---\n", stage);
	item_add(items[PLAYER], stage*2 - 2);
	item_add(items[DEALER], stage*2 - 2);
	lives[PLAYER] = stage * 2;
	lives[DEALER] = stage * 2;
	fprintf(stdout, "Lives set to %d.\n", lives[PLAYER]);

	start_of_round:
	//start of round
	round++;
	fprintf(stdout, "\n---======= START OF ROUND %d =======---\n", round);
	do {
		clearBullets(&bullets);
		loadRandomBullets(&bullets, round*2 + 1);
	} while (liveBullets(bullets) < round || blankBullets(bullets) < round);
	printBulletCounts(bullets);

	//loop player's turn until they don't skip opponent/run out of bullets
	bool skipOpponent = false;
	bool oppHandcuffed = false;
	bool handcuffsTriggered = false;
	bool quit = false;
	while (lives[PLAYER] > 0 && lives[DEALER] > 0 && bulletCount(bullets) > 0) {
		skipOpponent = false;
		oppHandcuffed = false;
		handcuffsTriggered = false;
		do {
			if (oppHandcuffed) {
				handcuffsTriggered = true;
			}
			skipOpponent = playerTurn(infiniteMode, &stage, &round, &totalWins, lives, &bullets, items, &oppHandcuffed, name, &quit);
			if (quit) {
				goto clean_up;
			}
#ifdef _WIN32
			Sleep(WAIT_TIME * 1000);
#else
			Sleep(WAIT_TIME);
#endif
		} while ((skipOpponent | (oppHandcuffed && !handcuffsTriggered)) && bulletCount(bullets) > 0);

		if (bulletCount(bullets) <= 0) {
			break;
		}
		//loop dealer's turn until they don't skip opponent/run out of bullets
		skipOpponent = false;
		oppHandcuffed = false;
		handcuffsTriggered = false;
		do {
			if (oppHandcuffed) {
				handcuffsTriggered = true;
			}
			skipOpponent = dealerTurn(lives, &bullets, items, &oppHandcuffed, difficulty);
#ifdef _WIN32
			Sleep(WAIT_TIME * 1000);
#else
			Sleep(WAIT_TIME);
#endif
		} while ((skipOpponent | (oppHandcuffed && !handcuffsTriggered)) && bulletCount(bullets) > 0);
	}
	//if lives have run out or bullets have run out
	if (lives[PLAYER] <= 0) {//player loss
		fprintf(stdout, "YOU LOSE!\n");
		fprintf(stdout, "Name: %s\n", name);
		if (infiniteMode) {
			fprintf(stdout, "Total wins: %d\n", totalWins);
		}
		fprintf(stdout, "Reached stage %d, round %d\n", stage, round);
	}
	else if (lives[DEALER] <= 0) {//dealer loss
		fprintf(stdout, "DEALER's LIFE has hit ZERO!\n");
		totalWins++;
		if (stage > 3 && !infiniteMode) {
			//3 stages in non-infinite
			fprintf(stdout, "YOU WIN!\n");
		}
		else if (stage > 3 && infiniteMode) {
			//infinite stages in infinite (has to reset so it doesn't goof)
			fprintf(stdout, "---=== STAGE RESET ===---\n");
			fprintf(stdout, "Total wins so far: %d\n", totalWins);
			stage = 0;
			clearBullets(&bullets);
			goto start_of_stage;
		}
		else {
			clearBullets(&bullets);
			goto start_of_stage;
		}
	}
	else if (bulletCount(bullets) <= 0) {
		fprintf(stdout, "\nNo more bullets left.\n");
		goto start_of_round;
	}
	
	//clean up
	clean_up:
	clearBullets(&bullets);
	return 0;
}


DIFFICULTY convertDifficultyFromBitFlag(int bitflag) {
	if (bitflag & DIF_HARD) {
		return DIF_HARD;
	}
	if (bitflag & MEDIUM_FLAG) {
		return DIF_MEDIUM;
	}
	if (bitflag & EASY_FLAG) {
		return DIF_EASY;
	}
}