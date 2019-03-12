#pragma once
#include <queue>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const int length=5);
		void changeDirection(Direction direction);
		void updateBody(COORDTYPE x, COORDTYPE y);
	private:
		int baseLength;
		Direction dir;
		std::queue<std::pair<COORDTYPE, COORDTYPE>> body;
};

