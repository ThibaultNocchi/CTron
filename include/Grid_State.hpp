#pragma once
#include "Definitions.hpp"
#include <vector>

class Grid_State{
	public:
		Grid_State(const std::vector<Snake>& vSnakes, const COORD& coor>;

	private:
		std::pair<std::vector<Snake>, COORD> pair;
}
