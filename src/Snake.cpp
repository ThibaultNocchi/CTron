#include "Snake.hpp"

Snake::Snake(const int length){
	this->baseLength = length;
    this->dir = UP;
    for(int i = 0; i < this->getBaseLength(); ++i){
        this->body.push(std::pair<COORDTYPE, COORDTYPE>(-1, -1));
    }
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

std::queue<std::pair<COORDTYPE, COORDTYPE>> Snake::getBody() const{
    return this->body;
}

void Snake::setDirection(Direction direction){
	this->dir = direction;
}