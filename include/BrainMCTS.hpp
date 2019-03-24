#pragma once

#include <cstdlib>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include "Definitions.hpp"
#include "Grid.hpp"

class BrainMCTS{

    public:
        BrainMCTS(const size_t index, const Grid& g);

        void initFromGrid(const Grid& g);
        void displayFromHash(u_int64_t hash);
        int rollout(Grid& g);
        int countRolls(u_int64_t hash);
        int explore(Grid& g);
        void startExplorationFrom(Grid g);
        Direction selectDirection(const Grid& g);

        double ucb(double v, double ni, double n);

        Direction getDirectionToExploreFrom(u_int64_t hash);

        void setSnakeIndex(const size_t index);

    private:
        size_t snakeIndex;
        std::unordered_map<u_int64_t, std::vector<std::pair<int, int>>> mcts;

};