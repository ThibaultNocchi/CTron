#pragma once
#include <iostream>
#include <vector>
#include "Definitions.hpp"

class Grid{
	public:
		Grid(const int width=15, const int height=15);

		int getWidth() const;
		int getHeight() const;
		std::pair<int, int> getSize() const;
		int getIndex(const int x, const int y) const;
		char getCell(const int x, const int y) const;

		void setCell(const int x, const int y, char value);

		void resetGrid();

	private:
		int width;
		int height;
		std::vector<char> cells;
};
