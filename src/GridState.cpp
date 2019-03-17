#include"GridState.hpp"

GridState::GridState(const std::vector<Snake>& vSnakes, const COORDS& coor){
	this->pair.first = vSnakes;
	this->pair.second = coor;
}

const std::vector<Snake>& GridState::getSnakes() const{
	return this->pair.first;
}

const COORDS& GridState::getCoords() const{
	return this->pair.second;
}
