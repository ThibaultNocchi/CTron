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

#define REWARD_DRAW -1000
#define REWARD_DEFEAT -1000
#define REWARD_VICTORY 1000
#define REWARD_BONUS(x) x*20
#define REWARD_KILLS(x) x*50
#define REWARD_ROUND 0

#define MAX_MC_DEPTH 100
#define MC_ITERATIONS 2000