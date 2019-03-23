#include "Snake.hpp"

Snake::Snake(const COORDTYPE x, const COORDTYPE y, const int length, const int lives){
	this->baseLength = length;
    this->adultLength = length;
    this->setDirection(UP);
    this->setHead(COORDS(x, y));
    this->setAlive(true);
    this->setLives(lives);
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

Direction Snake::setNewRandomDirection(){
  char result = std::rand() % 4;
  auto dir = this->getDirection();
  Direction future;
  switch (result) {
  case 0:
    if (dir != DOWN)
      future = UP;
    break;
  case 1:
    if (dir != UP)
      future = DOWN;
    break;
  case 2:
    if (dir != RIGHT)
      future = LEFT;
    break;
  case 3:
    if (dir != LEFT)
      future = RIGHT;
    break;
  }
  this->setDirection(future);
  return future;
}

void Snake::decrementLives(){
    if(this->getLives() > 0) --this->lives;
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

int Snake::getLives() const{
    return this->lives;
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

void Snake::setLives(const int lives){
    this->lives = lives;
}