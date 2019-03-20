#pragma once

#include "Snake.hpp"

class SnakeNaive : public Snake{
    public:
        SnakeNaive(const COORDTYPE x, const COORDTYPE y, const int length=5) : Snake(x, y, length){}
        void setNewDirection();
};