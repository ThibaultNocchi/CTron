#include "BrainMCTS.hpp"

BrainMCTS::BrainMCTS(const size_t index, const Grid& g){
    this->setSnakeIndex(index);
    this->initFromGrid(g);
}

void BrainMCTS::initFromGrid(const Grid& g){
    
    u_int64_t hash = g.getHash();
    this->mcts[hash].resize(4);

    this->mcts[hash][UP].first = 0;
    this->mcts[hash][UP].second = 0;

    this->mcts[hash][DOWN].first = 0;
    this->mcts[hash][DOWN].second = 0;

    this->mcts[hash][LEFT].first = 0;
    this->mcts[hash][LEFT].second = 0;

    this->mcts[hash][RIGHT].first = 0;
    this->mcts[hash][RIGHT].second = 0;

    Direction toBan;
    Direction current = g.getSnakes()[this->snakeIndex].getDirection();
    switch(current){
        case UP:
            toBan = DOWN;
            break;
        case DOWN:
            toBan = UP;
            break;
        case LEFT:
            toBan = RIGHT;
            break;
        case RIGHT:
            toBan = LEFT;
            break;
    }
    this->mcts[hash][toBan].second = -1;

}

void BrainMCTS::displayFromHash(u_int64_t hash){

    if(this->mcts.find(hash) != this->mcts.end()){
        
        std::cout << "UP v=" << this->mcts[hash][UP].first << " n=" << this->mcts[hash][UP].second << std::endl;
        std::cout << "DOWN v=" << this->mcts[hash][DOWN].first << " n=" << this->mcts[hash][DOWN].second << std::endl;
        std::cout << "LEFT v=" << this->mcts[hash][LEFT].first << " n=" << this->mcts[hash][LEFT].second << std::endl;
        std::cout << "RIGHT v=" << this->mcts[hash][RIGHT].first << " n=" << this->mcts[hash][RIGHT].second << std::endl;

    }else{
        std::cout << "Key doesn't exist." << std::endl;
    }

}

int BrainMCTS::rollout(Grid& g){

    int ending = -2;

    while(ending == -2){
        g.setNewRandomDirections();
        ending = g.moveSnakes();
    }

    int value;

    if(ending == -1){ value = REWARD_DRAW; }
    else if(ending == (int)this->snakeIndex){ value = REWARD_VICTORY; }
    else{ value = REWARD_DEFEAT; }

    return value;

}

int BrainMCTS::countRolls(u_int64_t hash){
    int n = 0;
    for(int i = 0; i < 4; ++i){
        if(this->mcts[hash][i].second > 0) n += this->mcts[hash][i].second > 0;
    }
    return n;
}

int BrainMCTS::explore(Grid& g){

    if(this->mcts.find(g.getHash()) == this->mcts.end()) this->initFromGrid(g);

    auto toExplore = this->getDirectionToExploreFrom(g.getHash());
    auto current = g.getHash();
    
    if(this->mcts[current][toExplore].second == 0){

        // this->initFromGrid(g);
        g.setNewRandomDirectionsExcept(this->snakeIndex);
        g.setDirection(this->snakeIndex, toExplore);
        g.moveSnakes();
        auto result = this->rollout(g);
        this->mcts[current][toExplore].first += result;
        ++this->mcts[current][toExplore].second;
        return result;

    }else{

        g.setNewRandomDirectionsExcept(this->snakeIndex);
        g.setDirection(this->snakeIndex, toExplore);
        g.moveSnakes();

        auto result = this->explore(g);
        this->mcts[current][toExplore].first += result;
        ++this->mcts[current][toExplore].second;

        return result;

    }

}

double BrainMCTS::ucb(int v, int ni, int n){
    return v + 2*sqrt(log(n) / ni);
}

Direction BrainMCTS::getDirectionToExploreFrom(u_int64_t hash){

    Direction maxDirection;
    double maxUCB;
    int n = this->countRolls(hash);

    if(this->mcts[hash][UP].second >= 0){
        if(this->mcts[hash][UP].second == 0) return UP;
        maxDirection = UP;
        maxUCB = this->ucb(this->mcts[hash][UP].first, this->mcts[hash][UP].first, n);
    }

    if(this->mcts[hash][DOWN].second >= 0){
        if(this->mcts[hash][DOWN].second == 0) return DOWN;
        auto ucb = this->ucb(this->mcts[hash][DOWN].first, this->mcts[hash][DOWN].first, n);
        if(ucb > maxUCB || this->mcts[hash][UP].second >= 0){
            maxDirection = DOWN;
            maxUCB = ucb;
        }
    }

    if(this->mcts[hash][LEFT].second >= 0){
        if(this->mcts[hash][LEFT].second == 0) return LEFT;
        auto ucb = this->ucb(this->mcts[hash][LEFT].first, this->mcts[hash][LEFT].first, n);
        if(ucb > maxUCB){
            maxDirection = LEFT;
            maxUCB = ucb;
        }
    }

    if(this->mcts[hash][RIGHT].second >= 0){
        if(this->mcts[hash][RIGHT].second == 0) return RIGHT;
        auto ucb = this->ucb(this->mcts[hash][RIGHT].first, this->mcts[hash][RIGHT].first, n);
        if(ucb > maxUCB){
            maxDirection = RIGHT;
            maxUCB = ucb;
        }
    }

    return maxDirection;

}

void BrainMCTS::startExplorationFrom(Grid g){
    this->explore(g);
}

Direction BrainMCTS::selectDirection(const Grid& g){

    u_int64_t current = g.getHash();
    Direction choose = UP;
    int max = this->mcts[current][UP].second;

    if(this->mcts[current][DOWN].second > max){
        choose = DOWN;
        max = this->mcts[current][DOWN].second;
    }

    if(this->mcts[current][LEFT].second > max){
        choose = LEFT;
        max = this->mcts[current][LEFT].second;
    }

    if(this->mcts[current][RIGHT].second > max){
        choose = RIGHT;
        max = this->mcts[current][RIGHT].second;
    }

    return choose;

}

void BrainMCTS::setSnakeIndex(const size_t index){
    this->snakeIndex = index;
}