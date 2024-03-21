#pragma once

enum difficulty {
	EASY,
	MEDIUM,
	HARD
};

difficulty convertDifficultyFromBitFlag(int bitflag);