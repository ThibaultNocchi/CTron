#include "Grid.hpp"

Grid::Grid(const int width, const int height) {
    this->width = width;
    this->height = height;
}

int Grid::getWidth() const{
    return this->width;
}

int Grid::getHeight() const{
    return this->height;
}

std::pair<int, int> Grid::getSize() const{
    return std::pair<int, int>(this->width, this->height);
}