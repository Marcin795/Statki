//
// Created by Marcin on 2018-11-12.
//

#include "Game.h"

Game::Game(Player &p1, Player &p2, int win) : p1(p1), p2(p2), win(win) {}

bool Game::setup(int p, int q, int t, int d) {
    std::cout << "Setup 1" << std::endl;
    if(!p1.setUp(p, q, t, d)) {
        return false;
    }
    std::cout << "Setup 2" << std::endl;
    if(!p2.setUp(p, q, t, d)) {
        return false;
    }
    std::cout << "Setup complete!" << std::endl;
    return true;
}

void Game::start() {
    while(p1.getScore() < win && p2.getScore() < win) {
        std::cout << "Player 1!" << std::endl;
        do {
            p1.printEnemyBoard();
        } while (p1.target(p2) && p1.getScore() < win);
        p1.printEnemyBoard();
        if(p1.getScore() == win) {
            break;
        }
        std::cout << "Player 2!" << std::endl;
        do {
            p2.printEnemyBoard();
        } while(p2.target(p1) && p2.getScore() < win);
        p2.printEnemyBoard();
    }
    std::cout << "Player" << (p1.getScore() > p2.getScore() ? "1" : "2") << " won!" << std::endl;
}
