#include "Grid.hpp"

Grid::Grid(const COORDTYPE width, const COORDTYPE height) {
    this->width = width;
    this->height = height;
    this->cells.resize(this->getWidth()*this->getHeight());
    this->resetGrid();
}

COORDTYPE Grid::getWidth() const{
    return this->width;
}

COORDTYPE Grid::getHeight() const{
    return this->height;
}

std::pair<COORDTYPE, COORDTYPE> Grid::getSize() const{
    return std::pair<int, int>(this->width, this->height);
}

int Grid::getIndex(const COORDTYPE x, const COORDTYPE y) const{
    return x*this->getWidth() + this->getHeight();
}

char Grid::getCell(const COORDTYPE x, const COORDTYPE y) const{
    return this->cells[this->getIndex(x, y)];
}

void Grid::setCell(const COORDTYPE x, const COORDTYPE y, char value){
    this->cells[this->getIndex(x, y)] = value;
}

void Grid::resetGrid(){
    for(int x = 0; x < this->getWidth(); ++x){
        for(int y = 0; y < this->getHeight(); ++y){
            this->setCell(x, y, 0);
        }
    }
}