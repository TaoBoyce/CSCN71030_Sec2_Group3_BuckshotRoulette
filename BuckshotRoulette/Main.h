#pragma once

#define PLAYER 0
#define DEALER 1

typedef enum difficulty {
	EASY,
	MEDIUM,
	HARD
}DIFFICULTY;

DIFFICULTY convertDifficultyFromBitFlag(int bitflag);