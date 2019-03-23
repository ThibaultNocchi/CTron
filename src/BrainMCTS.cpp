#include "BrainMCTS.hpp"

BrainMCTS::BrainMCTS(const size_t index, const Grid* g){
    this->setSnakeIndex(index);
    this->grid = g;
    this->initFromGrid();
}

void BrainMCTS::initFromGrid(){
    
    u_int64_t hash = this->grid->getHash();
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
    Direction current = this->getSnakeCurrentDirection();
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

int BrainMCTS::rollout(Grid g){

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

Direction BrainMCTS::getSnakeCurrentDirection(){
    return this->grid->getSnakes()[this->snakeIndex].getDirection();
}

void BrainMCTS::setSnakeIndex(const size_t index){
    this->snakeIndex = index;
}