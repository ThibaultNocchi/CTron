#include "Snake.hpp"

Snake::Snake(const COORDTYPE x, const COORDTYPE y, const int length, const AIType ai){
	this->baseLength = length;
    this->adultLength = length;
    this->dir = UP;
    this->setHead(COORDS(x, y));
    this->setAlive(true);
    this->ai = ai;
}

void Snake::setNewHead(){
    this->setHead(this->getFutureHead());
}

void Snake::removeTail(){
    this->body.pop_back();
}

void Snake::emptySnake(){
    this->body.clear();
    this->adultLength = this->baseLength;
}

void Snake::incrementSize(){
    ++this->adultLength;
}

void Snake::setNewDirection(){

    switch(this->ai){
        case NAIVE:{
            char result = std::rand() % 4;
			switch(result){
				case 0:
					if(this->dir != DOWN) this->setDirection(UP);
					break;
				case 1:
					if(this->dir != UP) this->setDirection(DOWN);
					break;
				case 2:
					if(this->dir != RIGHT) this->setDirection(LEFT);
					break;
				case 3:
					if(this->dir != LEFT) this->setDirection(RIGHT);
					break;
			}
            break;
        }
        case MCTS:{

            break;
        }

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

const std::deque<COORDS>& Snake::getBody() const{
    return this->body;
}

COORDS Snake::getHead() const{
    return this->body.front();
}

COORDS Snake::getTail() const{
    return this->body.back();
}

COORDS Snake::getFutureHead() const{
    return this->futureHead;
}

bool Snake::getAlive() const{
    return this->alive;
}

void Snake::setDirection(const Direction direction){
	this->dir = direction;
}

void Snake::setFutureHead(const COORDS head){
    this->futureHead = head;
}

void Snake::setAlive(const bool state){
    this->alive = state;
}

void Snake::setHead(const COORDS head){
    this->body.push_front(head);
}