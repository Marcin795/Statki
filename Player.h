//
// Created by Marcin on 2018-11-11.
//

#ifndef STATKI_PLAYER_H
#define STATKI_PLAYER_H

#include "Board.h"

class Player {
protected:
    Board board;
    Board enemyBoard;
    int score = 0;
public:
    int getScore() const;

public:
    Player(int x, int y);
    bool setUp(int p, int q, int t, int d);
    virtual bool placeShip(int size) = 0;
    virtual bool target(Player &enemy) = 0;
    bool shoot(int x, int y, Player &enemy);
    unsigned char checkForHit(int x, int y);
    void printBoard();
    void printEnemyBoard();
    void printCheatEnemyBoard(Player &enemy);
};


#endif //STATKI_PLAYER_H
