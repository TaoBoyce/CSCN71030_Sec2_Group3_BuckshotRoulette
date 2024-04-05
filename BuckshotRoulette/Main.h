#pragma once

#define PLAYER 0
#define DEALER 1
#define MAX_LIVES 5

typedef enum difficulty {
	DIF_EASY,
	DIF_MEDIUM,
	DIF_HARD
}DIFFICULTY;

DIFFICULTY convertDifficultyFromBitFlag(int bitflag);