#pragma once
#include <queue>
#include <iostream>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const int length=5);
		void move(Direction direction);
		/* TODO Fonction move à renommer pour éviter la confusion avec celle de Grid imho */
	private:
		int baseLength;
		Direction dir;
		std::queue<std::pair<COORDTYPE, COORDTYPE> > body;
};

