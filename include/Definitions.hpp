#pragma once
#include <utility>

#define DEFAULTWIDTH 15
#define DEFAULTHEIGHT 15

#define DEFAULTSNAKE 5

enum Direction {
	UP, DOWN, LEFT, RIGHT
};

enum State {
	EMPTY, WALL, BONUS, SNAKE, HEAD
};

using COORDTYPE = char;
using COORDS = std::pair<COORDTYPE, COORDTYPE>;

#define REWARD_DRAW -20
#define REWARD_DEFEAT -20
#define REWARD_VICTORY 20

#define MAX_MC_DEPTH 2000
#define MC_ITERATIONS 100