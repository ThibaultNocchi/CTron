#include "BrainMCTS.hpp"
#include "Definitions.hpp"
#include "Grid.hpp"
#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include <omp.h>
#include <sstream>
#include <unistd.h>

int main(int argc, char *argv[]) {

  //  ============ MODE PARTIE CLASSIQUE =========================

  /* Creating a window with a width of 800 px and 600 px */
  sf::RenderWindow window(sf::VideoMode(1000, 600), "CTron");

  /* useful variables and arrays */

  /* Loading a font */
  sf::Font font;
  if (!font.loadFromFile("LiberationSerif-Regular.ttf")) {
    printf("Erreur de chargement de la police d'écriture\n");
    exit(1);
  }
  int ending;
  int rounds = 0;
  unsigned int nbGamesPlayed = 0;
  
  unsigned int toConst = 10;
  if (argc <= 1 || std::stoi(argv[1]) <= 1) {
  } else {
    toConst = std::stoi(argv[1]);
  }
  const unsigned int NBGAMES = toConst;

  std::vector<sf::RectangleShape> RecToDraw;
  std::vector<sf::CircleShape> CirclesToDraw;
  std::vector<int> nbVictories;
  nbVictories.push_back(0);
  nbVictories.push_back(0);
  nbVictories.push_back(0);

  /* Creation of the three texts */
  std::vector<sf::Text> vText;
  for (size_t i = 0; i < 3; i += 1) {
    sf::Text t;
    t.setFont(font);
    vText.push_back(t);
  }
  vText.at(0).setPosition(sf::Vector2f(602.f, 0.f));
	vText.at(0).setFillColor(sf::Color::Blue);
  vText.at(1).setPosition(sf::Vector2f(602.f, 30.f));
	vText.at(1).setFillColor(sf::Color::Green);
  vText.at(2).setPosition(sf::Vector2f(602.f, 60.f));
	vText.at(2).setFillColor(sf::Color::Yellow);
	vText.at(2).setOutlineColor(sf::Color::Black);
	vText.at(2).setOutlineThickness(2.f);

  while (window.isOpen()) {
    for (nbGamesPlayed = 0; nbGamesPlayed < NBGAMES; ++nbGamesPlayed) {
      auto grid = Grid(10, 10);
      auto player = grid.addSnake(3, 1);
      grid.addSnake(3, 1);
      grid.addSnake(3, 1);

			/* Creation of a background rectangle */
			sf::RectangleShape background(sf::Vector2f(45.0*(1+grid.getWidth()),45.0*(1+grid.getHeight())));
			background.setPosition(0.f, 0.f);
			background.setFillColor(sf::Color::White);

      auto brain0 = BrainMCTS(player, grid);
      for (int i = 0; i < 100000; ++i) {

        /* Handling the (unique) possible event : in our case if the user closes
         * the window, it closes */
        sf::Event event;
        while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();
        }

        /* Giving the directions to differents snakes */
        for (int j = 0; j < MC_ITERATIONS; ++j) {
          brain0.explore(grid);
        }
        grid.setNewRandomDirectionsExcept(0, true);
        grid.setDirection(0, brain0.selectDirection(grid));
        ending = grid.moveSnakes();
        if (ending >= -1)
          break;

        // GUI
        window.clear(sf::Color(188, 188, 188));
				window.draw(background);
        for (COORDTYPE i = 0; i < grid.getWidth(); i += 1) {
          for (COORDTYPE j = 0; j < grid.getHeight(); j += 1) {
            State s = grid.getCell(i, j);
            if (s == WALL) {
              sf::RectangleShape rec(sf::Vector2f(45.f, 45.f));
              rec.setPosition(i * 50.f, j * 50.f);
              rec.setFillColor(sf::Color::Black);
              RecToDraw.push_back(rec);
            } else if (s == BONUS) {
              sf::CircleShape circle(24.5f);
              circle.setPosition(i * 50.f, j * 50.f);
              circle.setFillColor(sf::Color::Red);
              CirclesToDraw.push_back(circle);
            } else if (s == HEAD || s == SNAKE) {
              sf::RectangleShape shape;
              shape = sf::RectangleShape(sf::Vector2f(45.f, 45.f));
              if (s == HEAD){
											shape.setOutlineColor(sf::Color::Black);
											shape.setOutlineThickness(4.f);
							}
              shape.setPosition(sf::Vector2f(i * 50.f, j * 50.f));

              auto snakes = grid.getSnakes();
              COORDS c(i, j);
              for (size_t k = 0; k < snakes.size(); k += 1) {
                auto body = snakes[k].getBody();
                for (size_t l = 0; l < body.size(); l += 1) {
                  if (body[l] == c) {
                    switch (k) {
                    case 0:
                      shape.setFillColor(sf::Color::Blue);
                      break;
                    case 1:
                      shape.setFillColor(sf::Color::Green);
                      break;
                    case 2:
                      shape.setFillColor(sf::Color::Yellow);
                      break;
                    case 3:
                      shape.setFillColor(sf::Color::Cyan);
                      break;
                    }
                  }
                }
              }
              RecToDraw.push_back(shape);
            }
          }
        }
        for (size_t t = 0; t < 3; t++) {
          std::stringstream ss;
          ss << "Le serpent #" << t << " a " << nbVictories[t] << " victoires.";
          vText[t].setString(ss.str());
        }

        /* On dessine tout; on affiche; on vide les vecteurs; on attend une
         * second et on repart */
        for (size_t i = 0; i < RecToDraw.size(); i += 1)
          window.draw(RecToDraw[i]);
        for (size_t i = 0; i < CirclesToDraw.size(); i += 1)
          window.draw(CirclesToDraw[i]);
        for (size_t i = 0; i < vText.size(); i += 1)
          window.draw(vText[i]);
        window.display();
        RecToDraw.clear();
        CirclesToDraw.clear();
        usleep(100000);
        ++rounds;
      }
      nbVictories.at(ending) = nbVictories[ending] + 1;
      sleep(2);
    }
    window.close();
    printf("La partie est finie\n");
    for (unsigned int sn = 0; sn < nbVictories.size(); sn += 1)
      printf("Le serpent %u a gagné %d parties.\n", sn + 1, nbVictories[sn]);
    break;
  }

  return 0;
}
