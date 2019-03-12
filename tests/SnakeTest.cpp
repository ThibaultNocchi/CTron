#include <iostream>
#include <cassert>
#include "Snake.hpp"

#define TEST_OBJ snake
#define TEST_LENGTH 7
#define TEST_RANDOMX() COORDTYPE x = std::rand() % 255;
#define TEST_RANDOMY() COORDTYPE y = std::rand() % 255;
#define TEST_RANDOMCOORDS() TEST_RANDOMX() TEST_RANDOMY()
#define TEST_INITSNAKE() TEST_RANDOMCOORDS(); auto TEST_OBJ = Snake(x, y, TEST_LENGTH);

void SnakeTest();
void moveBodyTest();
void getBaseLengthTest();

int main(int argc, char *argv[]){
    SnakeTest();
    moveBodyTest();
    getBaseLengthTest();
    return EXIT_SUCCESS;
}

void SnakeTest(){
    TEST_INITSNAKE()
    assert(TEST_OBJ.getCurrentLength() == 1);
}

void moveBodyTest(){
    TEST_INITSNAKE()
    COORDTYPE x2 = 5;
    COORDTYPE y2 = 3;

    while(TEST_OBJ.getCurrentLength() != TEST_LENGTH){
        TEST_OBJ.moveBody(x2, y2);
    }

    assert(TEST_OBJ.getCurrentLength() == TEST_LENGTH);
    auto body = TEST_OBJ.getBody();
    assert(body.back().first == x2 && body.back().second == y2);
    assert(body.front().first == x && body.front().second == y);
    
    TEST_OBJ.moveBody(x, y);
    body = TEST_OBJ.getBody();
    assert(TEST_OBJ.getCurrentLength() == TEST_LENGTH);
    assert(body.back().first == x && body.back().second == y);
    assert(body.front().first == x2 && body.front().second == y2);
}

void getBaseLengthTest(){
    TEST_INITSNAKE()
    assert(TEST_OBJ.getBaseLength() == TEST_LENGTH);
}

void getCurrentLength(){
    TEST_INITSNAKE()
    assert(TEST_OBJ.getCurrentLength() == 1);
}