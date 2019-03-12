#include "Snake.hpp"

Snake::Snake(const int length){
	this->baseLength = length;
}

void Snake::moveBody(COORDTYPE x, COORDTYPE y){
	this->body.pop();
	this->body.push(std::pair<COORDTYPE, COORDTYPE>(x, y));
}

int Snake::getBaseLength() const{
    return this->baseLength;
}

Direction Snake::getDirection() const{
    return this->dir;
}

void Snake::setDirection(Direction direction){
	this->dir = direction;
}