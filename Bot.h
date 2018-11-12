//
// Created by Marcin on 2018-11-11.
//

#ifndef STATKI_BOT_H
#define STATKI_BOT_H

#include "Player.h"

class Bot: public Player {
private:
    std::tuple<int, int, Board::directions> lastHit = {-1, -1, Board::directions::NONE};
    int i = 0;
    int j = 0;
public:
    Bot(int x, int y);
    bool placeShip(int size) override;
    bool target(Player &enemy) override;
};


#endif //STATKI_BOT_H
