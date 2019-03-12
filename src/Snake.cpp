#include "Snake.hpp"

Snake::Snake(const COORDTYPE x, const COORDTYPE y, const int length){
	this->baseLength = length;
    this->adultLength = length;
    this->dir = UP;
    this->moveBody(x, y);
}

void Snake::moveBody(const COORDTYPE x, const COORDTYPE y){
    if(this->getCurrentLength() == this->getAdultLength()){
	    this->body.pop();
    }
	this->body.push(std::pair<COORDTYPE, COORDTYPE>(x, y));
}

int Snake::getBaseLength() const{
    return this->baseLength;
}

int Snake::getAdultLength() const{
    return this->adultLength;
}

int Snake::getCurrentLength() const{
    return this->body.size();
}

Direction Snake::getDirection() const{
    return this->dir;
}

std::queue<std::pair<COORDTYPE, COORDTYPE>> Snake::getBody() const{
    return this->body;
}

void Snake::setDirection(const Direction direction){
	this->dir = direction;
}