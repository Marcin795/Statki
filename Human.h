//
// Created by Marcin on 2018-11-11.
//

#ifndef STATKI_HUMAN_H
#define STATKI_HUMAN_H

#include "Player.h"

class Human: public Player {
public:
    Human(int x, int y);
    bool placeShip(int size) override;
    bool target(Player &enemy) override;
};


#endif //STATKI_HUMAN_H
