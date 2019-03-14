#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"

int main(int argc, char* argv[]){
	
	auto grid = Grid(5, 5);
	grid.addSnake(3);
	grid.displayGridBasic();
	
	grid.moveSnakes();
	grid.displayGridBasic();

	grid.moveSnakes();
	grid.displayGridBasic();

	grid.moveSnakes();
	grid.displayGridBasic();

	return 0;
}
