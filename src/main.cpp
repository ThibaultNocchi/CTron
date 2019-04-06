#include "BrainMCTS.hpp"
#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"
#include <omp.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  // auto grid = Grid(10, 10);
  // grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2,2), std::pair<COORDTYPE,COORDTYPE>(4,4));
  // auto player = grid.addSnake(3, 1); grid.addSnake(3, 1);

  // auto brain0 = BrainMCTS(player, grid);

  // grid.displayGridBasic();

  // int ending;
  // double begin = omp_get_wtime();

  // int rounds = 0;

  // for(int i = 0; i < 100000; ++i){

  // 	for(int j = 0; j < MC_ITERATIONS; ++j){
  // 		brain0.explore(grid);
  // 	}

  // 	grid.setNewRandomDirectionsExcept(0, true);
  // 	grid.setDirection(0, brain0.selectDirection(grid));
  // 	ending = grid.moveSnakes();
  // 	if(ending >= -1) break;

  // 	grid.displayGridBasic();
  // 	// sleep(1);

  // 	++rounds;

  // }

  // std::cout << omp_get_wtime() - begin << std::endl;

  // grid.displayGridBasic();
  // switch(ending){
  // 	case -1:
  // 		std::cout << "Every snake died." << std::endl;
  // 		break;
  // 	case -2:
  // 		std::cout << "No winner." << std::endl;
  // 		break;
  // 	default:
  // 		std::cout << "Snake n°" << ending << " won!" << std::endl;
  // }

  // std::cout << rounds << " rounds." << std::endl;

  int victories = 0;
  std::vector<int> roundsNbr;

  for (int game = 0; game < 10; ++game) {

    int rounds = 0;
    auto grid = Grid(10, 10);
    // grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2, 2), std::pair<COORDTYPE, COORDTYPE>(4, 4));
    auto player = grid.addSnake(3, 1);
    grid.addSnake(3, 1);

    auto brain0 = BrainMCTS(player, grid);

    int ending = -2;

    while (ending < -1) {

      for (int j = 0; j < MC_ITERATIONS; ++j) {
        brain0.explore(grid);
      }

      grid.setNewRandomDirectionsExcept(0, true);
      grid.setDirection(0, brain0.selectDirection(grid));
      ending = grid.moveSnakes();
      ++rounds;
    }

	if(ending == 0) ++victories;
  std::cout << "Round " << game + 1 << " ended! Score: " << victories << "/" << game + 1 << std::endl;
  roundsNbr.push_back(rounds);

  }

  double meanRounds = 0;
  for(auto rounds : roundsNbr) meanRounds += rounds;
  meanRounds /= roundsNbr.size();

  std::cout << victories << " victories for our snake for a mean number of rounds of " << meanRounds << "!" << std::endl;

  return 0;
}
