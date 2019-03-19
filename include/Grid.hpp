#pragma once
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include "Definitions.hpp"
#include "Snake.hpp"

class Grid{
	public:
		Grid(const COORDTYPE width=DEFAULTWIDTH, const COORDTYPE height=DEFAULTHEIGHT);

		void addSnake(const int length=DEFAULTSNAKE);
		void moveSnakes();
		void resetGrid();
		void resetSnake(int index);
		void resetSnakes();

		void addWall(const COORDS topLeft, const COORDS bottomRight);

		void putBonus();

		void displayGridBasic();

		COORDTYPE getWidth() const;
		COORDTYPE getHeight() const;
		COORDS getSize() const;
		int getIndex(const COORDTYPE x, const COORDTYPE y) const;
		State getCell(const COORDTYPE x, const COORDTYPE y) const;
		COORDS getRandomEmptyCell() const;
		const std::vector<Snake>& getSnakes() const;
		int getNumberAliveSnakes() const;
		const COORDS& getBonus() const;
		const std::vector<State>& getCells() const;

		void setCell(const COORDTYPE x, const COORDTYPE y, State value);
		void setDirection(size_t index, Direction dir);

		bool operator<(const Grid& other) const;
		bool operator==(const Grid& other) const;

	private:
		COORDTYPE width;
		COORDTYPE height;
		std::vector<State> cells;
		std::vector<Snake> snakes;
		COORDS bonus;
		int aliveSnakes;
		std::vector<std::vector<u_int64_t>> hashes;
		std::vector<std::vector<uint64_t>> snakesHashes;
		static std::random_device rd;
		static std::mt19937_64 eng;
		static std::uniform_int_distribution<uint64_t> distr;
};

namespace std {
template <> class hash<Grid> {
public:
  size_t operator()(const Grid &g) const {
      return 1;
    }
};

}