#include <cstdlib>
#include <omp.h>
#include <unordered_map>
#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"

int main(int argc, char* argv[]){
	
	auto grid = Grid(10, 10);
	grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2,2), std::pair<COORDTYPE, COORDTYPE>(4,4));
	grid.addSnake(3, NAIVE);
	grid.addSnake(3, NAIVE);

	grid.displayGridBasic();

	std::unordered_map<u_int64_t, int> mymap;

	int ending;

	double begin = omp_get_wtime();
	mymap[grid.getHash()]++;
	
	for(int i = 0; i < 100000; ++i){
		
		grid.setNewDirections();

		ending = grid.moveSnakes();
		mymap[grid.getHash()]++;

		if(ending >= 0) break;

	}

	std::cout << omp_get_wtime() - begin << std::endl;

	grid.displayGridBasic();
	switch(ending){
		case -2:
			std::cout << "Every snake died." << std::endl;
			break;
		case -1:
			std::cout << "No winner." << std::endl;
			break;
		default:
			std::cout << "Snake n°" << ending << " won!" << std::endl;
	}

	// for(auto el : mymap){
	// 	if(el.second > 1) std::cout << el.second << " times: " << el.first << std::endl;
	// }

	return 0;
}
