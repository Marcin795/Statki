//
// Created by Marcin on 2018-11-11.
//

#include "Player.h"

Player::Player(int x, int y): board(Board(x, y)), enemyBoard(Board(x, y)) {}

void Player::printBoard() {
    board.printCheat();
}

unsigned char Player::checkForHit(int x, int y) {
    return board.checkForHit(x, y);
}

bool Player::shoot(int x, int y, Player &enemy) {
    unsigned char result = enemy.checkForHit(x, y);
    bool out = false;
    if(result != 'o') {
        score++;
        out = true;
    }
    if(result == 'X' || result == 'o') {
        enemyBoard.setAt(x, y, result);
    } else if(result == '#') {
        enemyBoard.setAt(x, y, 'o');
    } else if(result) {
        enemyBoard.setAt(x, y, 'X');
        enemyBoard.sink(x, y, result - '0' - 4);
    }
    return out;
}

void Player::printEnemyBoard() {
    enemyBoard.printCheat();
}

int Player::getScore() const {
    return score;
}

bool Player::setUp(int p, int q, int t, int d) {
    bool failed;
    board.print();
    do {
        failed = false;
        board.clear();
        for (int i = 0; i < p; i++) {
            if(!placeShip(5)){
                failed = true;
                continue;
            };
        }
        for (int i = 0; i < q; i++) {
            if(!placeShip(4)){
                failed = true;
                continue;
            };
        }
        for (int i = 0; i < t; i++) {
            if(!placeShip(3)){
                failed = true;
                continue;
            };
        }
        for (int i = 0; i < d; i++) {
            if(!placeShip(2)){
                failed = true;
                continue;
            };
        }
    } while(failed);
    return true;
}

void Player::printCheatEnemyBoard(Player &enemy) {
    enemy.printBoard();
}
