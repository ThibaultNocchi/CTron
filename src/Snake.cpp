#include "Snake.hpp"

Snake::Snake(const COORDTYPE x, const COORDTYPE y, const int length){
	this->baseLength = length;
    this->adultLength = length;
    this->dir = UP;
    // this->moveBody(x, y);
    this->setHead(std::pair<COORDTYPE, COORDTYPE>(x, y));
    this->setAlive(true);
}

// bool Snake::moveBody(const COORDTYPE x, const COORDTYPE y){
// 	this->body.push_front(std::pair<COORDTYPE, COORDTYPE>(x, y));
//     if(this->getCurrentLength() > this->getAdultLength()){
// 	    this->body.pop_back();
//         return true;
//     }else{
//         return false;
//     }
// }

// bool Snake::moveBody(const std::pair<COORDTYPE, COORDTYPE> newHead){
//     this->body.push_front(newHead);
//     if(this->getCurrentLength() > this->getAdultLength()){
//         this->body.pop_back();
//         return true;
//     }else{
//         return false;
//     }
// }

void Snake::setNewHead(){
    this->setHead(this->getFutureHead());
}

void Snake::removeTail(){
    this->body.pop_back();
}

void Snake::emptySnake(){
    this->body.clear();
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

bool Snake::getAlive() const{
    return this->alive;
}

void Snake::setDirection(const Direction direction){
	this->dir = direction;
}

void Snake::setFutureHead(const std::pair<COORDTYPE, COORDTYPE> head){
    this->futureHead = head;
}

void Snake::setAlive(const bool state){
    this->alive = state;
}

void Snake::setHead(const std::pair<COORDTYPE, COORDTYPE> head){
    this->body.push_front(head);
}