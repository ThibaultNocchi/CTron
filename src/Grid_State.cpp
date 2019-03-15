#include"Grid_State.hpp"

Grid_State::Grid_State(const std::vector<Snake>& vSnakes, const COORD& coor>{
	this->pair.first = vSnakes;
	this->pair.second = coor;
}
