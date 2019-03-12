#include "Snake.hpp"

Snake::Snake(const int length){
	this->baseLength = length;
}

void Snake::changeDirection(Direction direction){
	this->dir = direction;
}

void Snake::updateBody(COORDTYPE x, COORDTYPE y){
	this->body.pop();
	this->body.pair(std::pair<COORDTYPE, COORDTYPE>(x, y));
};
