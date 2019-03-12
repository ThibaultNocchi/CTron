#include <cassert>
#include <cstdlib>
#include <ctime>
#include "Grid.hpp"
#include "Definitions.hpp"

#define TEST_OBJ grid
#define TEST_WIDTH 10
#define TEST_HEIGHT 10
#define TEST_INITGRID() auto TEST_OBJ = Grid(TEST_WIDTH, TEST_HEIGHT);
#define TEST_RANDOMX() COORDTYPE x = std::rand() % TEST_WIDTH;
#define TEST_RANDOMY() COORDTYPE y = std::rand() % TEST_HEIGHT;
#define TEST_RANDOMCOORDS() TEST_RANDOMX() TEST_RANDOMY()

void GridTest();
void getWidthTest();
void getHeightTest();
void getIndexTest();
void getCellTest();
void getRandomEmptyCellTest();
void setCellTest();
void resetGridTest();

int main(int argc, char *argv[]){
    std::srand(std::time(nullptr));
    GridTest();
    getWidthTest();
    getHeightTest();
    getIndexTest();
    getCellTest();
    getRandomEmptyCellTest();
    setCellTest();
    resetGridTest();
    return EXIT_SUCCESS;
}

void GridTest(){
    TEST_INITGRID()
    for(COORDTYPE x = 0; x < TEST_WIDTH; ++x){
        for(COORDTYPE y = 0; y < TEST_HEIGHT; ++y){
            assert(TEST_OBJ.getCell(x, y) == EMPTY);
        }
    }
}

void getWidthTest(){
    TEST_INITGRID()
    assert(TEST_OBJ.getWidth() == TEST_WIDTH);
}

void getHeightTest(){
    TEST_INITGRID()
    assert(TEST_OBJ.getHeight() == TEST_HEIGHT);
}

void getSizeTest(){
    TEST_INITGRID()
    auto size = TEST_OBJ.getSize();
    assert(size.first == TEST_WIDTH);
    assert(size.second == TEST_HEIGHT);
}

void getIndexTest(){
    TEST_INITGRID()
    TEST_RANDOMCOORDS()
    auto result = x*TEST_WIDTH + y;
    assert(TEST_OBJ.getIndex(x, y) == result);
}

void getCellTest(){
    TEST_INITGRID()
    TEST_RANDOMCOORDS()
    TEST_OBJ.setCell(x, y, SNAKE);
    assert(TEST_OBJ.getCell(x, y) == SNAKE);
}

void getRandomEmptyCellTest(){
    TEST_INITGRID()
    auto pair1 = TEST_OBJ.getRandomEmptyCell();
    auto pair2 = TEST_OBJ.getRandomEmptyCell();
    assert((pair1.first != pair2.first) || (pair1.second != pair2.second));
    assert(TEST_OBJ.getCell(pair1.first, pair1.second) == EMPTY);
    assert(TEST_OBJ.getCell(pair2.first, pair2.second) == EMPTY);
}

void setCellTest(){
    TEST_INITGRID()
    TEST_RANDOMCOORDS()
    TEST_OBJ.setCell(x, y, SNAKE);
    assert(TEST_OBJ.getCell(x, y) == SNAKE);
}

void resetGridTest(){
    TEST_INITGRID()
    TEST_RANDOMCOORDS()
    TEST_OBJ.setCell(x, y, SNAKE);
    assert(TEST_OBJ.getCell(x, y) == SNAKE);
    TEST_OBJ.resetGrid();
    assert(TEST_OBJ.getCell(x, y) == EMPTY);
}