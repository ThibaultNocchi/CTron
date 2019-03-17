#include"GridState.hpp"

GridState::GridState(const std::vector<Snake>& vSnakes, const COORDS& coor){
	this->pair.first = vSnakes;
	this->pair.second = coor;
}

GridState::GridState(const Grid& grid){
	this->pair.first = grid.getSnakes();
	this->pair.second = grid.getBonus();
}

const std::vector<Snake>& GridState::getSnakes() const{
	return this->pair.first;
}

const COORDS& GridState::getBonus() const{
	return this->pair.second;
}

bool GridState::operator==(const GridState& other) const{

	if(this->pair.first.size() != other.getSnakes().size()) return false;

    auto bonus1 = this->pair.second;
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
