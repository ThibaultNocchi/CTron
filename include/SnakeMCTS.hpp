#pragma once

#include <unordered_map>
#include "Snake.hpp"

class SnakeMCTS : public Snake{
    public:
        SnakeMCTS(const COORDTYPE x, const COORDTYPE y, const int length=5) : Snake(x, y, length){}
        void setNewDirection();

    private:
        // std::unordered_map<u_int64_t
};