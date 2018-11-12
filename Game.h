//
// Created by Marcin on 2018-11-12.
//

#ifndef STATKI_GAME_H
#define STATKI_GAME_H

#include "Player.h"
#include "Human.h"
#include "Bot.h"

class Game {
public:
    Game(Player &p1, Player &p2, int win);

protected:
    Player &p1;
    Player &p2;
    int win;
public:
    bool setup(int p, int q, int t, int d);
    void start();

};


#endif //STATKI_GAME_H
