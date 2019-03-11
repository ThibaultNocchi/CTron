#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Definitions.hpp"

class Grid{
	public:
		Grid(const COORDTYPE width=15, const COORDTYPE height=15);

		COORDTYPE getWidth() const;
		COORDTYPE getHeight() const;
		std::pair<COORDTYPE, COORDTYPE> getSize() const;
		int getIndex(const COORDTYPE x, const COORDTYPE y) const;
		char getCell(const COORDTYPE x, const COORDTYPE y) const;
		std::pair<COORDTYPE, COORDTYPE> getRandomEmptyCell() const;

		void setCell(const COORDTYPE x, const COORDTYPE y, char value);

		void resetGrid();

	private:
		COORDTYPE width;
		COORDTYPE height;
		std::vector<char> cells;
};
