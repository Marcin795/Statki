//
// Created by Marcin on 2018-11-11.
//

#include "Human.h"

Human::Human(int x, int y):Player(x, y) {}

bool Human::placeShip(int size) {
    int x, y, dir;
    std::cout << "Placing ship of size " << size << " (x, y, dir): ";
    std::cin >> x;
    std::cin >> y;
    std::cin >> dir;
    if(x == 0 && y == 0 && dir == 0) {
        return false;
    }
    bool result = board.placeShip(x, y, size, (Board::directions)dir);
    if(!result) {
        result = placeShip(size);
    } else {
        printBoard();
    }
    return result;
}

bool Human::target(Player &enemy) {
    int x = 0 , y = 0;
    do {
        std::cin >> x;
        std::cin >> y;
        if(!x && !y) {
            printCheatEnemyBoard(enemy);
        }
    } while(enemyBoard.getAt(x, y) != '.');
    return shoot(x, y, enemy);
}
