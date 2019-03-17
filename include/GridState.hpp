#pragma once
#include "Definitions.hpp"
#include "Snake.hpp"
#include "Grid.hpp"
#include <vector>

class GridState{
	public:
		GridState(const std::vector<Snake>& vSnakes, const COORDS& coor);
		const std::vector<Snake>& getSnakes() const;
		const COORDS& getCoords() const;
	private:
		std::pair<std::vector<Snake>, COORDS> pair;
};
