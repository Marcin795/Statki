#include <iostream>
#include "Game.h"
#include <string>

#define maxSize 1024
#define minSize 3

int main() {
    int mode = 0;
    int x, y, p, q, t, d;
    int maxScore, score;
    do{
        do {
            std::cout << "Choose game mode: 1-PvP 2-PvE 3-BOTvBOT 4-Manual 0-Exit : ";
            std::cin >> mode;
            if(mode == 4) {
                std::cout << "Ship placement: x y dir\nDirections: 1-UP 2-UPRIGHT 3-RIGHT..." <<
                "\nAttacking: x y\nTo show opponents board: 0 0" << std::endl;
            }
            if(mode == 0) {
                return 0;
            }
        } while (mode > 3);
        do {
            std::cout << "Select map size (x, y): ";
            std::cin >> x >> y;
        } while(x < minSize || x > maxSize || y < minSize || y > maxSize);
        maxScore = (x * y) / 4;
        do {
            std::cout << "Pick ship counts, max " << maxScore << " combined (5s, 4s, 3s, 2s): ";
            std::cin >> p >> q >> t >> d;
            score = 5 * p + 4 * q + 3 * t + 2 * d;
        } while(score > maxScore);
        if(mode == 1) {
            Human human1(x, y);
            Human human2(x, y);
            Game game(human1, human2, score);
            game.setup(p, q, t, d);
            game.start();
        } else if(mode == 2) {
            Human human(x, y);
            Bot bot(x, y);
            Game game(human, bot, score);
            game.setup(p, q, t, d);
            game.start();
        } else if(mode == 3) {
            Bot bot1(x, y);
            Bot bot2(x, y);
            Game game(bot1, bot2, score);
            game.setup(p, q, t, d);
            game.start();
        }
    } while(mode > 0);
    return 0;
}