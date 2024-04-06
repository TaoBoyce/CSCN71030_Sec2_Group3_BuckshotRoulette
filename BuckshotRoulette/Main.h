#pragma once

#define PLAYER 0
#define DEALER 1
#define MAX_LIVES 6

#define EASY_FLAG 1
#define MEDIUM_FLAG 2
#define HARD_FLAG 4
#define INFINITE_FLAG 8

typedef enum difficulty {
	DIF_EASY,
	DIF_MEDIUM,
	DIF_HARD
}DIFFICULTY;

DIFFICULTY convertDifficultyFromBitFlag(int bitflag);