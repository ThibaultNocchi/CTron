#pragma once
#include <queue>
#include <iostream>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const int length=5);
		void move(int direction);
	private:
		int baseLength;
		Direction dir;
		std::queue<std::pair<COORDTYPE, COORDTYPE>> body;
};

