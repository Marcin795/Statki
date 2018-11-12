//
// Created by Marcin on 2018-11-11.
//

#ifndef STATKI_BOARD_H
#define STATKI_BOARD_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <dirent.h>

class Board {
public:
    enum directions {UP = 1, DOWN = 5, LEFT = 7, RIGHT = 3, UPLEFT = 8, UPRIGHT = 2, DOWNLEFT = 6, DOWNRIGHT = 4, NONE = 0};
    std::pair<int, int> decodeDir(Board::directions dir);
private:
    std::vector< std::vector<unsigned char> > board;
    int sizX;
public:
    int getSizX() const;
    int getSizY() const;

private:
    int sizY;
    bool checkForShipSpace(int x, int y, int size, int dirX, int dirY);
    bool protectShip(int x, int y, int size, int dirX, int dirY);
    int colNums();
    bool sunk(int x, int y);
    std::tuple<int, int, Board::directions> sweep(int x, int y);
public:
    static std::mt19937 gen;
    std::uniform_int_distribution<int> distributionX;
    std::uniform_int_distribution<int> distributionY;
    std::uniform_int_distribution<int> distributionDir;
    bool clear();
    bool sink(int x, int y, int size);
    unsigned char getAt(int x, int y);
    unsigned char setAt(int x, int y, unsigned char c);
    bool placeShip(int x, int y, int size, Board::directions dir);
    bool placeShipRandom(int size);
    unsigned char checkForHit(int x, int y);
    void print();
    void printCheat();
    Board(int x, int y);

};


#endif //STATKI_BOARD_H
