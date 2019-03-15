#include <cstdlib>
#include <omp.h>
#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"

int main(int argc, char* argv[]){
	
	auto grid = Grid(10, 10);
	grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2,2), std::pair<COORDTYPE, COORDTYPE>(4,4));
	grid.addSnake(3);
	grid.addSnake(3);
	grid.displayGridBasic();

	double begin = omp_get_wtime();
	
	for(int i = 0; i < 100000; ++i){
		
		for(size_t j = 0; j < grid.getSnakes().size(); ++j){
			char result = std::rand() % 4;
			auto dir = grid.getSnakes()[j].getDirection();
			switch(result){
				case 0:
					if(dir != DOWN) grid.getSnakes()[j].setDirection(UP);
					break;
				case 1:
					if(dir != UP) grid.getSnakes()[j].setDirection(DOWN);
					break;
				case 2:
					if(dir != RIGHT) grid.getSnakes()[j].setDirection(LEFT);
					break;
				case 3:
					if(dir != LEFT) grid.getSnakes()[j].setDirection(RIGHT);
					break;
			}
		}

		grid.moveSnakes();

	}

	grid.displayGridBasic();
	std::cout << omp_get_wtime() - begin << std::endl;

	return 0;
}
