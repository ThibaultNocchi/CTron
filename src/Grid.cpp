#include "Grid.hpp"

Grid::Grid(const int width, const int height) {
    this->width = width;
    this->height = height;
    this->cells.resize(this->getWidth()*this->getHeight());
    this->resetGrid();
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

int Grid::getIndex(const int x, const int y) const{
    return x*this->getWidth() + this->getHeight();
}

char Grid::getCell(const int x, const int y) const{
    return this->cells[this->getIndex(x, y)];
}

void Grid::setCell(const int x, const int y, char value){
    this->cells[this->getIndex(x, y)] = value;
}

void Grid::resetGrid(){
    for(int x = 0; x < this->getWidth(); ++x){
        for(int y = 0; y < this->getHeight(); ++y){
            this->setCell(x, y, 0);
        }
    }
}