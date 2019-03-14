#pragma once
#include <deque>
#include <iostream>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const COORDTYPE x, const COORDTYPE y, const int length=5);

		bool moveBody(const COORDTYPE x, const COORDTYPE y);
		bool moveBody(const std::pair<COORDTYPE, COORDTYPE> newHead);

		void displayBodyFromHeadToTail() const;

		int getBaseLength() const;
		int getAdultLength() const;
		int getCurrentLength() const;
		Direction getDirection() const;
		std::deque<std::pair<COORDTYPE, COORDTYPE>> getBody() const;
		std::pair<COORDTYPE, COORDTYPE> getHead() const;
		std::pair<COORDTYPE, COORDTYPE> getTail() const;
		std::pair<COORDTYPE, COORDTYPE> getFutureHead() const;

		void setDirection(const Direction direction);
		void setFutureHead(const std::pair<COORDTYPE, COORDTYPE> head);

	private:
		int baseLength;
		int adultLength;
		Direction dir;
		std::deque<std::pair<COORDTYPE, COORDTYPE>> body;
		std::pair<COORDTYPE, COORDTYPE> futureHead;
};

