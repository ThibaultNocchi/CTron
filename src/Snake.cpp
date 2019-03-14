#include "Snake.hpp"

Snake::Snake(const COORDTYPE x, const COORDTYPE y, const int length){
	this->baseLength = length;
    this->adultLength = length;
    this->dir = UP;
    this->moveBody(x, y);
}

bool Snake::moveBody(const COORDTYPE x, const COORDTYPE y){
	this->body.push_front(std::pair<COORDTYPE, COORDTYPE>(x, y));
    if(this->getCurrentLength() > this->getAdultLength()){
	    this->body.pop_back();
        return true;
    }else{
        return false;
    }
}

bool Snake::moveBody(const std::pair<COORDTYPE, COORDTYPE> newHead){
    this->body.push_front(newHead);
    if(this->getCurrentLength() > this->getAdultLength()){
        this->body.pop_back();
        return true;
    }else{
        return false;
    }
}

void Snake::displayBodyFromHeadToTail() const{
    for(auto part : this->getBody()){
        std::cout << "{" << +(part.first) << ", " << +(part.second) << "} " << std::endl;
    }
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

std::deque<std::pair<COORDTYPE, COORDTYPE>> Snake::getBody() const{
    return this->body;
}

std::pair<COORDTYPE, COORDTYPE> Snake::getHead() const{
    return this->body.front();
}

std::pair<COORDTYPE, COORDTYPE> Snake::getTail() const{
    return this->body.back();
}

std::pair<COORDTYPE, COORDTYPE> Snake::getFutureHead() const{
    return this->futureHead;
}

void Snake::setDirection(const Direction direction){
	this->dir = direction;
}

void Snake::setFutureHead(const std::pair<COORDTYPE, COORDTYPE> head){
    this->futureHead = head;
}