//
// Created by Marcin on 2018-11-11.
//

#include "Bot.h"

Bot::Bot(int x, int y):Player(x, y) {}

bool Bot::placeShip(int size) {
    return board.placeShipRandom(size);
}
bool Bot::target(Player &enemy) {
    int x, y;
    if(std::get<0>(lastHit) == -1) {
        do {
            x = board.distributionX(Board::gen);
            y = board.distributionY(Board::gen);
        } while(enemyBoard.getAt(x, y) != '.');
        bool test = shoot(x, y, enemy);
        if(test) {
            std::get<0>(lastHit) = x;
            std::get<1>(lastHit) = y;
        }
        return test;
    } else if(!std::get<2>(lastHit)) {
        do {
            i++;
            x = std::get<0>(lastHit) + board.decodeDir((Board::directions)i).first;
            y = std::get<1>(lastHit) + board.decodeDir((Board::directions)i).second;
        } while(enemyBoard.getAt(x, y) != '.');
        bool test = shoot(x, y, enemy);
        if(test) {
            unsigned char check = enemyBoard.getAt(x, y);
            if(check == 'X') {
                std::get<2>(lastHit) = (Board::directions)i;
            } else {
                i = 0;
                std::get<0>(lastHit) = -1;
                std::get<1>(lastHit) = -1;
                std::get<2>(lastHit) = Board::directions::NONE;
            }
        }
        return test;
    } else {
        do {
            j++;
            x = std::get<0>(lastHit) + j * board.decodeDir(std::get<2>(lastHit)).first;
            y = std::get<1>(lastHit) + j * board.decodeDir(std::get<2>(lastHit)).second;
            if(x <= 0 || x > board.getSizX() || y <= 0 || y > board.getSizY() || enemyBoard.getAt(x, y) == 0) {
                j = 1;
                std::get<2>(lastHit) = (Board::directions)((std::get<2>(lastHit) + 3) % 8 + 1);
                x = std::get<0>(lastHit) + j * board.decodeDir(std::get<2>(lastHit)).first;
                y = std::get<1>(lastHit) + j * board.decodeDir(std::get<2>(lastHit)).second;
            }
        } while(enemyBoard.getAt(x, y) != '.');
        int tmpX = std::get<0>(lastHit) + (j-1) * board.decodeDir(std::get<2>(lastHit)).first;
        int tmpY = std::get<1>(lastHit) + (j-1) * board.decodeDir(std::get<2>(lastHit)).second;
        if(enemyBoard.getAt(tmpX, tmpY) == 'o' || enemyBoard.getAt(tmpX, tmpY) == '#') {
            j = 1;
            std::get<2>(lastHit) = (Board::directions)((std::get<2>(lastHit) + 3) % 8 + 1);
            x = std::get<0>(lastHit) + j * board.decodeDir(std::get<2>(lastHit)).first;
            y = std::get<1>(lastHit) + j * board.decodeDir(std::get<2>(lastHit)).second;
        }
        bool test = shoot(x, y, enemy);
        if(test) {
            unsigned char check = enemyBoard.getAt(x, y);
            std::cout << "check: " << check << std::endl;
            if(check != 'X') {
                i = 0;
                j = 0;
                std::get<0>(lastHit) = -1;
                std::get<1>(lastHit) = -1;
                std::get<2>(lastHit) = Board::directions::NONE;
            }
        }
        return test;
    }
}