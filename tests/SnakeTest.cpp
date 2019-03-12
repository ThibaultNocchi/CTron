#include <iostream>
#include <cassert>
#include "Snake.hpp"

#define TEST_OBJ snake
#define TEST_LENGTH 7
#define TEST_INITSNAKE() auto TEST_OBJ = Snake(TEST_LENGTH);

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
    auto body = TEST_OBJ.getBody();
    assert(body.size() == TEST_LENGTH);
}

void moveBodyTest(){
    TEST_INITSNAKE()
    COORDTYPE x = 5;
    COORDTYPE y = 3;
    TEST_OBJ.moveBody(x, y);
    auto body = TEST_OBJ.getBody();
    assert(body.size() == TEST_LENGTH);
    assert(body.back().first == x && body.back().second == y);
}

void getBaseLengthTest(){
    TEST_INITSNAKE()
    assert(TEST_OBJ.getBaseLength() == TEST_LENGTH);
}