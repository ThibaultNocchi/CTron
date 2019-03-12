#include "Grid.hpp"

Grid::Grid(const COORDTYPE width, const COORDTYPE height) {
    this->width = width;
    this->height = height;
    this->cells.resize(this->getWidth()*this->getHeight());
    this->resetGrid();
    std::srand(std::time(nullptr));
}

void Grid::addSnake(const int length){
    auto newPosition = this->getRandomEmptyCell();
    auto newSnake = Snake(newPosition.first, newPosition.second, length);
    this->snakes.push_back(newSnake);
}

// 0,0 is considered to be bottom left.
void Grid::moveSnakes(){

    for(auto snake : this->snakes){
        
        auto head = snake.getHead();
        switch (snake.getDirection()){
            case UP:
                if(head.second == this->getHeight() - 1){
                    head.second = 0;
                }else{
                    head.second += 1;
                }
                break;
            
            case DOWN:
                if(head.second == 0){
                    head.second = this->getHeight() - 1;
                }else{
                    head.second -= 1;
                }
                break;

            case LEFT:
                if(head.first == 0){
                    head.first = this->getWidth() - 1;
                }else{
                    head.first -= 1;
                }
                break;

            case RIGHT:
                if(head.first == this->getWidth() - 1){
                    head.first = 0;
                }else{
                    head.first += 1;
                }
                break;
        
            default:
                break;
        }

        snake.moveBody(head);

    }
    
}

void Grid::resetGrid(){
    for(int x = 0; x < this->getWidth(); ++x){
        for(int y = 0; y < this->getHeight(); ++y){
            this->setCell(x, y, EMPTY);
        }
    }
    this->resetSnakes();
}

void Grid::resetSnakes(){
    this->snakes.clear();
}

COORDTYPE Grid::getWidth() const{
    return this->width;
}

COORDTYPE Grid::getHeight() const{
    return this->height;
}

std::pair<COORDTYPE, COORDTYPE> Grid::getSize() const{
    return std::pair<COORDTYPE, COORDTYPE>(this->width, this->height);
}

int Grid::getIndex(const COORDTYPE x, const COORDTYPE y) const{
    return x*this->getWidth() + y;
    /* Utiliser directement l'attribut plutôt que la fonction get ne serait il pas plus efficace ? */
}

State Grid::getCell(const COORDTYPE x, const COORDTYPE y) const{
    // return this->cells.at(this->getIndex(x, y));
    return this->cells[this->getIndex(x, y)];
}

std::pair<COORDTYPE, COORDTYPE> Grid::getRandomEmptyCell() const{
    COORDTYPE x, y;
    do{
        x = std::rand() % this->getWidth();
        y = std::rand() % this->getHeight();
    }while(this->getCell(x, y) != 0);
    return std::pair<COORDTYPE, COORDTYPE>(x, y);
}

void Grid::setCell(const COORDTYPE x, const COORDTYPE y, State value){
    // this->cells.at(this->getIndex(x, y)) = value;
    this->cells[this->getIndex(x, y)] = value;
}
