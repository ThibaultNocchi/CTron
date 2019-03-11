#pragma once
#include <iostream>
#include "Definitions.hpp"

class Grid{
	public:
		Grid(const int width=15, const int height=15);
		int getWidth() const;
		int getHeight() const;
		std::pair<int, int> getSize() const;
	private:
		int width;
		int height;
};
