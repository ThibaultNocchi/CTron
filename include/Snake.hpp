#pragma once
#include <queue>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const COORDTYPE x, const COORDTYPE y, const int length=5);

		void moveBody(const COORDTYPE x, const COORDTYPE y);
		void moveBody(const std::pair<COORDTYPE, COORDTYPE> newHead);

		int getBaseLength() const;
		int getAdultLength() const;
		int getCurrentLength() const;
		Direction getDirection() const;
		std::queue<std::pair<COORDTYPE, COORDTYPE>> getBody() const;
		std::pair<COORDTYPE, COORDTYPE> getHead() const;

		void setDirection(const Direction direction);

	private:
		int baseLength;
		int adultLength;
		Direction dir;
		std::queue<std::pair<COORDTYPE, COORDTYPE>> body;
};

