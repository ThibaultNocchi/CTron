#include "SnakeNaive.hpp"

void SnakeNaive::setNewDirection(){

  char result = std::rand() % 4;
  auto dir = this->getDirection();
  switch (result) {
    case 0:
        if (dir != DOWN)
        this->setDirection(UP);
        break;
    case 1:
        if (dir != UP)
        this->setDirection(DOWN);
        break;
    case 2:
        if (dir != RIGHT)
        this->setDirection(LEFT);
        break;
    case 3:
        if (dir != LEFT)
        this->setDirection(RIGHT);
        break;
  }

}