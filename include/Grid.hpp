#pragma once
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <memory>
#include "Definitions.hpp"
#include "Snake.hpp"

class Grid{
	public:
		Grid(const COORDTYPE width=DEFAULTWIDTH, const COORDTYPE height=DEFAULTHEIGHT);

		size_t addSnake(const int length=DEFAULTSNAKE, const int lives=-1);
		int moveSnakes();
		void resetGrid();
		void resetSnake(int index);
		void killSnake(int index);
		COORDS calculateFutureHead(size_t index);

		void addWall(const COORDS topLeft, const COORDS bottomRight);

		void putBonus();

		void applyHash(const COORDTYPE x, const COORDTYPE y, const State s);
		void applySnakeHash(const COORDTYPE x, const COORDTYPE y, const size_t snakeID, const State s);
		void initHash();

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
		u_int64_t getHash() const;

		void setCell(const COORDTYPE x, const COORDTYPE y, State value, size_t snakeID = 0);
		void setDirection(size_t index, Direction dir);
		Direction setRandomDirection(size_t index, bool noStupidMove);
		void setNewRandomDirections(bool noStupidMove);
		void setNewRandomDirectionsExcept(size_t index, bool noStupidMove);

		bool operator<(const Grid& other) const;
		bool operator==(const Grid& other) const;

	private:
		COORDTYPE width;
		COORDTYPE height;
		std::vector<std::vector<int>> indexes;
		std::vector<State> cells;
		std::vector<Snake> snakes;
		COORDS bonus;
		int aliveSnakes;
		std::vector<std::vector<u_int64_t>> hashes;
		std::vector<std::vector<std::pair<u_int64_t, u_int64_t>>> snakesHashes;
		u_int64_t currentHash;
		static std::random_device rd;
		static std::mt19937_64 eng;
		static std::uniform_int_distribution<u_int64_t> distr;
};