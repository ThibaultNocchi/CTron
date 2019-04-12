#include "BrainMCTS.hpp"
#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"
#include <omp.h>
#include <unistd.h>
#include <SFML/Graphics.hpp>

int main(int argc, char *argv[]) {

	//  ============ MODE PARTIE CLASSIQUE =========================

	sf::RenderWindow window(sf::VideoMode(600, 600), "CTron");
	/* Creating a window with a width of 800 px and 600 px */

	auto grid = Grid(10, 10);
	grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2,2),
		           std::pair<COORDTYPE,COORDTYPE>(4,4)
		    ); 
	auto player = grid.addSnake(3, 1); 
	grid.addSnake(3, 1);

	auto brain0 = BrainMCTS(player, grid);

	grid.displayGridBasic();

	int ending;
	double begin = omp_get_wtime();

	int rounds = 0;

	std::vector<sf::RectangleShape> RecToDraw;
	std::vector<sf::CircleShape> CirclesToDraw;

	while (window.isOpen()){

		for(int i = 0; i < 100000; ++i){

		/* Handling the (unique) possible event : in our case if the user closes the window, it closes */
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}

			for(int j = 0; j < MC_ITERATIONS; ++j){
				brain0.explore(grid);
			}
			grid.setNewRandomDirectionsExcept(0);
			grid.setDirection(0, brain0.selectDirection(grid));
			ending = grid.moveSnakes();
			if(ending >= -1) break;

			// GUI
			window.clear(sf::Color::White);
			for(COORDTYPE i=0; i<grid.getWidth(); i+=1){
				for(COORDTYPE j=0; j<grid.getHeight(); j+=1){
					State s = grid.getCell(i,j);
					if(s == WALL){
						sf::RectangleShape rec(sf::Vector2f(45.f, 45.f));
						rec.setPosition(i*50.f, j*50.f);
						rec.setFillColor(sf::Color::Black);
						RecToDraw.push_back(rec);
					}
					else if (s == BONUS){
						sf::CircleShape circle(24.5f);
						circle.setPosition(i*50.f, j*50.f);
						circle.setFillColor(sf::Color::Red);
						CirclesToDraw.push_back(circle);
					}else if (s == HEAD || s == SNAKE){
						sf::RectangleShape shape;
						shape = sf::RectangleShape(sf::Vector2f(45.f, 45.f));
						if(s == HEAD) shape.rotate(45.f);
						shape.setPosition(sf::Vector2f(i*50.f, j*50.f));

						auto snakes = grid.getSnakes();
						COORDS c(i,j);
						for(size_t k=0; k<snakes.size(); k+=1){
							auto body = snakes[k].getBody();
							for(size_t l=0; l<body.size(); l+=1){
								if(body[l] == c){
									switch(k){
										case 0: shape.setFillColor(sf::Color::Blue); break;
										case 1: shape.setFillColor(sf::Color::Green); break;
										case 2: shape.setFillColor(sf::Color::Yellow); break;
										case 3: shape.setFillColor(sf::Color::Cyan); break;
									}
								}
							}
						}
						RecToDraw.push_back(shape);
					}
				}
			}

			/* On dessine tout; on affiche; on vide les vecteurs; on attend une second et on repart */
			for(size_t i=0; i < RecToDraw.size(); i+=1) window.draw(RecToDraw[i]);
			for(size_t i=0; i < CirclesToDraw.size(); i+=1) window.draw(CirclesToDraw[i]);
			window.display();
			RecToDraw.clear();
			CirclesToDraw.clear();
			sleep(1);
			++rounds;

		}
	}

	return 0;

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

	//  ============ MODE NOMBRE DE VICTOIRE =========================
	// int victories = 0;

	// for (int game = 0; game < 100; ++game) {

	//   auto grid = Grid(10, 10);
	//   grid.addWall(std::pair<COORDTYPE, COORDTYPE>(2, 2),
	//                std::pair<COORDTYPE, COORDTYPE>(4, 4));
	//   auto player = grid.addSnake(3, 1);
	//   grid.addSnake(3, 1);

	//   auto brain0 = BrainMCTS(player, grid);

	//   int ending = -2;

	//   while (ending < -1) {

	//     for (int j = 0; j < MC_ITERATIONS; ++j) {
	//       brain0.explore(grid);
	//     }

	//     grid.setNewRandomDirectionsExcept(0);
	//     grid.setDirection(0, brain0.selectDirection(grid));
	//     ending = grid.moveSnakes();
	//   }

	//       if(ending == 0) ++victories;

	// }

	// std::cout << victories << " victories for our snake!" << std::endl;

	// return 0;
}
