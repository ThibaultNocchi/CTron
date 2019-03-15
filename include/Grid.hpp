#pragma once
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Definitions.hpp"
#include "Snake.hpp"

class Grid{
	public:
		Grid(const COORDTYPE width=DEFAULTWIDTH, const COORDTYPE height=DEFAULTHEIGHT);

		void addSnake(const int length=DEFAULTSNAKE);
		void moveSnakes();
		void resetGrid();
		void resetSnake(int index);
		void resetSnakes();

		void addWall(const COORDS topLeft, const COORDS bottomRight);

		void putBonus();

		void displayGridBasic();

		COORDTYPE getWidth() const;
		COORDTYPE getHeight() const;
		COORDS getSize() const;
		int getIndex(const COORDTYPE x, const COORDTYPE y) const;
		State getCell(const COORDTYPE x, const COORDTYPE y) const;
		COORDS getRandomEmptyCell() const;
		const std::vector<Snake>& getSnakes() const;

		void setCell(const COORDTYPE x, const COORDTYPE y, State value);
		void setDirection(size_t index, Direction dir);

	private:
		COORDTYPE width;
		COORDTYPE height;
		std::vector<State> cells;
		std::vector<Snake> snakes;
		COORDS bonus;
};
