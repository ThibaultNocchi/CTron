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

    // Calculating future new head, and removing the end of the tail if needed.
    for(size_t i = 0; i < this->snakes.size(); ++i){
        
        auto head = this->snakes[i].getHead();

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

        this->snakes[i].setFutureHead(head);
        if(this->snakes[i].getCurrentLength() == this->snakes[i].getAdultLength()){
            auto tail = this->snakes[i].getTail();
            this->setCell(tail.first, tail.second, EMPTY);
            this->snakes[i].removeTail();
        }

    }

    // First checking for collisions with a wall or a snake (excepted the future head)
    // Then checking for frontal collisions with another future head.
    for(size_t i = 0; i < this->snakes.size(); ++i){
        
        if(this->snakes[i].getAlive()){
            auto newHead = this->snakes[i].getFutureHead();
            if(this->getCell(newHead.first, newHead.second) != EMPTY){
                this->snakes[i].setAlive(false);
                this->resetSnake(i);
            }else{

                for(size_t j = (i+1); j < this->snakes.size(); ++j){
                    auto newHead2 = this->snakes[j].getFutureHead();
                    if(newHead.first == newHead2.first && newHead.second == newHead2.second){
                        this->snakes[i].setAlive(false);
                        this->snakes[j].setAlive(false);
                        this->resetSnake(i);
                        this->resetSnake(j);
                    }
                }

            }
            if(this->snakes[i].getAlive()){
                this->snakes[i].setNewHead();
                this->setCell(newHead.first, newHead.second, SNAKE);
            }
        }

    }

    // Respawning dead snakes
    for(size_t i = 0; i < this->snakes.size(); ++i){
        if(!this->snakes[i].getAlive()){
            this->snakes[i].setAlive(true);
            auto newPos = this->getRandomEmptyCell();
            this->snakes[i].setHead(newPos);
            this->setCell(newPos.first, newPos.second, SNAKE);
        }
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

void Grid::resetSnake(int index){
    auto body = this->snakes[index].getBody();
    for(auto part : body){
        this->setCell(part.first, part.second, EMPTY);
    }
    this->snakes[index].emptySnake();
}

void Grid::resetSnakes(){
    this->snakes.clear();
}

void Grid::addWall(const COORDS topLeft, const COORDS bottomRight){
    for(COORDTYPE x = topLeft.first; x <= bottomRight.first; ++x){
        for(COORDTYPE y = topLeft.second; y <= bottomRight.second; ++y){
            this->setCell(x, y, WALL);
        }
    }
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

                case SNAKE:{
                    bool drawBody = true;
                    for(size_t i = 0; i < this->snakes.size(); ++i){
                        auto head = this->snakes[i].getHead();
                        if(head.first == x && head.second == y){
                            std::cout << "H";
                            drawBody = false;
                        }
                    }
                    if(drawBody){
                        std::cout << "O";
                    }
                    break;
                }

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

COORDS Grid::getSize() const{
    return COORDS(this->width, this->height);
}

int Grid::getIndex(const COORDTYPE x, const COORDTYPE y) const{
    return x*this->getWidth() + y;
    /* Utiliser directement l'attribut plutôt que la fonction get ne serait il pas plus efficace ? */
}

State Grid::getCell(const COORDTYPE x, const COORDTYPE y) const{
    // return this->cells.at(this->getIndex(x, y));
    return this->cells[this->getIndex(x, y)];
}

COORDS Grid::getRandomEmptyCell() const{
    COORDTYPE x, y;
    do{
        x = std::rand() % this->getWidth();
        y = std::rand() % this->getHeight();
    }while(this->getCell(x, y) != 0);
    return COORDS(x, y);
}

std::vector<Snake>& Grid::getSnakes(){
    return this->snakes;
}

void Grid::setCell(const COORDTYPE x, const COORDTYPE y, State value){
    // this->cells.at(this->getIndex(x, y)) = value;
    this->cells[this->getIndex(x, y)] = value;
}
