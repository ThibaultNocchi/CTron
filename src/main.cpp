#include <cstdlib>
#include <omp.h>
#include <unordered_map>
#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"
#include "BrainMCTS.hpp"

int main(int argc, char* argv[]){
	
	auto grid = Grid(10, 10);
	grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2,2), std::pair<COORDTYPE, COORDTYPE>(4,4));
	auto player = grid.addSnake(3);
	grid.addSnake(3);

	grid.displayGridBasic();

	int ending;

	double begin = omp_get_wtime();
	
	for(int i = 0; i < 100000; ++i){
		
		grid.setNewRandomDirections();

		ending = grid.moveSnakes();

		if(ending >= -1) break;

	}

	std::cout << omp_get_wtime() - begin << std::endl;

	grid.displayGridBasic();
	switch(ending){
		case -1:
			std::cout << "Every snake died." << std::endl;
			break;
		case -2:
			std::cout << "No winner." << std::endl;
			break;
		default:
			std::cout << "Snake n°" << ending << " won!" << std::endl;
	}

	return 0;
}
