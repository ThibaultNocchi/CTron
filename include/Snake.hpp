#pragma once
#include <queue>
#include <iostream>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(int length=5);
		void move(int direction);
	private:
		std::queue<std::pair<COORDTYPE, COORDTYPE>> body;
};

