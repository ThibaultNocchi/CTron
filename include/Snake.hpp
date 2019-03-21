#pragma once
#include <deque>
#include <iostream>
#include "Definitions.hpp"

class Snake{
	public:
		Snake(const COORDTYPE x, const COORDTYPE y, const int length=5, const int lives=-1);

		void setNewHead();
		void removeTail();
		void emptySnake();
		void incrementSize();

		void setNewDirection();

		void decrementLives();

		void displayBodyFromHeadToTail() const;

		int getBaseLength() const;
		int getAdultLength() const;
		int getCurrentLength() const;
		Direction getDirection() const;
		const std::deque<COORDS>& getBody() const;
		COORDS getHead() const;
		COORDS getTail() const;
		COORDS getFutureHead() const;
		bool getAlive() const;
		int getLives() const;

		void setDirection(const Direction direction);
		void setFutureHead(const COORDS head);
		void setAlive(const bool state);
		void setHead(const COORDS head);
		void setLives(const int lives);

	private:
		int baseLength;
		int adultLength;
		Direction dir;
		std::deque<COORDS> body;
		COORDS futureHead;
		bool alive;
		int lives;
};

