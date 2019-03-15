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

		void displayGridBasic();

		COORDTYPE getWidth() const;
		COORDTYPE getHeight() const;
		std::pair<COORDTYPE, COORDTYPE> getSize() const;
		int getIndex(const COORDTYPE x, const COORDTYPE y) const;
		State getCell(const COORDTYPE x, const COORDTYPE y) const;
		std::pair<COORDTYPE, COORDTYPE> getRandomEmptyCell() const;
		std::vector<Snake>& getSnakes();

		void setCell(const COORDTYPE x, const COORDTYPE y, State value);

	private:
		COORDTYPE width;
		COORDTYPE height;
		std::vector<State> cells;
		std::vector<Snake> snakes;
};
