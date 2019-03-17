#include "Grid.hpp"

Grid::Grid(const COORDTYPE width, const COORDTYPE height) {
    this->width = width;
    this->height = height;
    this->aliveSnakes = 0;
    this->cells.resize(this->getWidth()*this->getHeight());
    this->resetGrid();
    std::srand(std::time(nullptr));
}

void Grid::addSnake(const int length){
    auto newPosition = this->getRandomEmptyCell();
    auto newSnake = Snake(newPosition.first, newPosition.second, length);
    this->snakes.push_back(newSnake);
    this->setCell(newPosition.first, newPosition.second, SNAKE);
    ++this->aliveSnakes;
}

// 0,0 is considered to be top left.
void Grid::moveSnakes(){

    // Calculating future new head, and removing the end of the tail if needed.
    for(size_t i = 0; i < this->snakes.size(); ++i){
        
        COORDS head = this->snakes[i].getHead();

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
            COORDS tail = this->snakes[i].getTail();
            this->setCell(tail.first, tail.second, EMPTY);
            this->snakes[i].removeTail();
        }

    }

    // First checking for collisions with a wall or a snake (excepted the future head)
    // Then checking for frontal collisions with another future head.
    for(size_t i = 0; i < this->snakes.size(); ++i){
        
        if(this->snakes[i].getAlive()){
            COORDS newHead = this->snakes[i].getFutureHead();
            State cellValue = this->getCell(newHead.first, newHead.second);
            if(cellValue == SNAKE || cellValue == WALL){
                this->snakes[i].setAlive(false);
                this->resetSnake(i);
                --this->aliveSnakes;
            }else if(cellValue == EMPTY){

                for(size_t j = (i+1); j < this->snakes.size(); ++j){
                    COORDS newHead2 = this->snakes[j].getFutureHead();
                    if(newHead.first == newHead2.first && newHead.second == newHead2.second){
                        this->snakes[i].setAlive(false);
                        this->snakes[j].setAlive(false);
                        this->resetSnake(i);
                        this->resetSnake(j);
                        this->aliveSnakes -= 2;
                    }
                }

            }
            if(this->snakes[i].getAlive()){
                this->snakes[i].setNewHead();
                this->setCell(newHead.first, newHead.second, SNAKE);
                if(cellValue == BONUS){
                    this->putBonus();
                    this->snakes[i].incrementSize();
                }
            }
        }

    }

    // Respawning dead snakes
    for(size_t i = 0; i < this->snakes.size(); ++i){
        if(!this->snakes[i].getAlive()){
            this->snakes[i].setAlive(true);
            ++this->aliveSnakes;
            COORDS newPos = this->getRandomEmptyCell();
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

void Grid::putBonus(){
    COORDS cell = this->getRandomEmptyCell();
    this->bonus = cell;
    this->setCell(cell.first, cell.second, BONUS);
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
                    break;

                case BONUS:
                    std::cout << "$";
                    break;
            
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
    }while(this->getCell(x, y) != EMPTY);
    return COORDS(x, y);
}

const std::vector<Snake>& Grid::getSnakes() const{
    return this->snakes;
}

int Grid::getNumberAliveSnakes() const{
    return this->aliveSnakes;
}

const COORDS Grid::getBonus() const{
    return this->bonus;
}

const std::vector<State>& Grid::getCells() const{
    return this->cells;
}

void Grid::setCell(const COORDTYPE x, const COORDTYPE y, State value){
    // this->cells.at(this->getIndex(x, y)) = value;
    this->cells[this->getIndex(x, y)] = value;
}

void Grid::setDirection(size_t index, Direction dir){
    this->snakes[index].setDirection(dir);
}

bool Grid::operator<(const Grid& other) const{
    
    if(this->snakes.size() < other.getSnakes().size()) return true;
    else if(this->snakes.size() > other.getSnakes().size()) return false;

    auto bonus1 = this->getBonus();
    auto bonus2 = other.getBonus();

    if(bonus1.first < bonus2.first) return true;
    if(bonus1.first > bonus2.first) return false;

    if(bonus1.second < bonus2.second) return true;
    if(bonus1.second > bonus2.second) return false;

    auto snakes1 = this->getSnakes();
    auto snakes2 = other.getSnakes();

    for(size_t i = 0; i < snakes1.size(); ++i){
        if(!snakes1[i].getAlive() && snakes2[i].getAlive()) return true;
        else if(snakes1[i].getAlive() && !snakes2[i].getAlive()) return false;

        if(snakes1[i].getCurrentLength() < snakes2[i].getCurrentLength()) return true;
        if(snakes1[i].getCurrentLength() > snakes2[i].getCurrentLength()) return false;

        auto body1 = snakes1[i].getBody();
        auto body2 = snakes2[i].getBody();

        for(size_t j = 0; j < body1.size(); ++j){
            auto pos1 = body1[j];
            auto pos2 = body2[j];
            if(pos1.first < pos2.first) return true;
            if(pos1.first > pos2.first) return false;
            if(pos1.second < pos2.second) return true;
            if(pos1.second > pos2.second) return false;
        }
    }

    return false;

}

bool Grid::operator==(const Grid& other) const{
    
    if(this->snakes.size() != other.getSnakes().size()) return false;

    auto bonus1 = this->getBonus();
    auto bonus2 = other.getBonus();

    if(bonus1.first != bonus2.first) return false;
    if(bonus1.second != bonus2.second) return false;

    auto snakes1 = this->getSnakes();
    auto snakes2 = other.getSnakes();

    for(size_t i = 0; i < snakes1.size(); ++i){
        if(snakes1[i].getAlive() != snakes2[i].getAlive()) return false;

        if(snakes1[i].getCurrentLength() != snakes2[i].getCurrentLength()) return false;

        auto body1 = snakes1[i].getBody();
        auto body2 = snakes2[i].getBody();

        for(size_t j = 0; j < body1.size(); ++j){
            auto pos1 = body1[j];
            auto pos2 = body2[j];
            if(pos1.first != pos2.first) return false;
            if(pos1.second != pos2.second) return false;
        }
    }

    return true;

}
