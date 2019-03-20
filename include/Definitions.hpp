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

enum AIType {
	NAIVE, MCTS
};

using COORDTYPE = char;
using COORDS = std::pair<COORDTYPE, COORDTYPE>;
