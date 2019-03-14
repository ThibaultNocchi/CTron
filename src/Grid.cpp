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
    this->setCell(newPosition.first, newPosition.second, SNAKE);
}

// 0,0 is considered to be top left.
void Grid::moveSnakes(){

    for(size_t i = 0; i < this->snakes.size(); ++i){
        
        auto head = this->snakes[i].getHead();
        auto tail = this->snakes[i].getTail();

        switch (this->snakes[i].getDirection()){
            case DOWN:
                if(head.first == this->getHeight() - 1){
                    head.first = 0;
                }else{
                    head.first += 1;
                }
                break;
            
            case UP:
                if(head.first == 0){
                    head.first = this->getHeight() - 1;
                }else{
                    head.first -= 1;
                }
                break;

            case LEFT:
                if(head.second == 0){
                    head.second = this->getWidth() - 1;
                }else{
                    head.second -= 1;
                }
                break;

            case RIGHT:
                if(head.second == this->getWidth() - 1){
                    head.second = 0;
                }else{
                    head.second += 1;
                }
                break;
        
            default:
                break;
        }

        if(this->checkCollision(head)){
        }else{
            this->setCell(head.first, head.second, SNAKE);
            if(this->snakes[i].moveBody(head)){
                this->setCell(tail.first, tail.second, EMPTY);
            }
        }

    }
    
}

bool Grid::checkCollision(std::pair<COORDTYPE, COORDTYPE> head){
    // TODO
    return false;
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

void Grid::displayGridBasic(){
    for(COORDTYPE y = 0; y < this->getWidth(); ++y){
        std::cout << "-";
    }
    std::cout << std::endl;
    for(COORDTYPE x = 0; x < this->getHeight(); ++x){
        for(COORDTYPE y = 0; y < this->getWidth(); ++y){
            switch (this->getCell(x,y)){
                case EMPTY:
                    std::cout << " ";
                    break;

                case SNAKE:
                    std::cout << "O";
                    break;

                case WALL:
                    std::cout << "#";
            
                default:
                    break;
            }
        }
        std::cout << std::endl;
    }
    for(COORDTYPE y = 0; y < this->getWidth(); ++y){
        std::cout << "-";
    }
    std::cout << std::endl;
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
