#pragma once
#include <queue>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const int length=5);

		void moveBody(COORDTYPE x, COORDTYPE y);

		int getBaseLength() const;
		Direction getDirection() const;

		void setDirection(Direction direction);

	private:
		int baseLength;
		Direction dir;
		std::queue<std::pair<COORDTYPE, COORDTYPE>> body;
};

