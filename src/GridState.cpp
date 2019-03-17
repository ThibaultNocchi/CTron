#include"GridState.hpp"

GridState::GridState(const std::vector<Snake>& vSnakes, const COORDS& coor){
	this->pair.first = vSnakes;
	this->pair.second = coor;
}
