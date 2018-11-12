//
// Created by Marcin on 2018-11-11.
//

#include "Board.h"

Board::Board(int x, int y): sizX(x), sizY(y), distributionX(std::uniform_int_distribution<int>(1, sizX)), distributionY(std::uniform_int_distribution<int>(1, sizY)), distributionDir(1, 8) {
    board.resize(sizX);
    for(auto &i: board) {
        i.resize(sizY);
        for(auto &j: i) {
            j = '.';
        }
    }
}
std::mt19937 Board::gen(time(0));

std::pair<int, int> Board::decodeDir(Board::directions dir) {
    std::pair<int, int> decoded;
    if(dir == UP) {
        decoded.first = -1;
        decoded.second = 0;
    } else if (dir == DOWN) {
        decoded.first = 1;
        decoded.second = 0;
    } else if (dir == LEFT) {
        decoded.first = 0;
        decoded.second = -1;
    } else if (dir == RIGHT) {
        decoded.first = 0;
        decoded.second = 1;
    } else if (dir == UPLEFT) {
        decoded.first = -1;
        decoded.second = -1;
    } else if (dir == UPRIGHT) {
        decoded.first = -1;
        decoded.second = 1;
    } else if (dir == DOWNLEFT) {
        decoded.first = 1;
        decoded.second = -1;
    } else if (dir == DOWNRIGHT) {
        decoded.first = 1;
        decoded.second = 1;
    }
    return decoded;
}

bool Board::placeShip(int x, int y, int size, directions dir) {
    x--;
    y--;
    int dirX = decodeDir(dir).first;
    int dirY = decodeDir(dir).second;
    if(!checkForShipSpace(x, y, size, dirX, dirY)) {
        return false;
    } else {
        for(int i = 0; i < size; i++) {
            board[x + i * dirX][y + i * dirY] = (unsigned char)size + '0';
        }
    }
    protectShip(x, y, size, dirX, dirY);
    return true;
}

bool Board::checkForShipSpace(int x, int y, int size, int dirX, int dirY) {
    int endX = x + (size-1) * dirX;
    int endY = y + (size-1) * dirY;
    if(x >= sizX || y >= sizY || x < 0 || y < 0) {
        return false;
    }
    if(endX >= sizX || endY >= sizY || endX < 0 || endY < 0) {
        return false;
    }
    for(int i = 0; i < size; i++) {
        if(board[x + i * dirX][y + i * dirY] != '.') {
            return false;
        }
    }
    return true;
}

bool Board::protectShip(int x, int y, int size, int dirX, int dirY) {
    for(int i = 0; i < size; i++) {
        for(int j = -1; j < 2; j++) {
            for(int k = -1; k < 2; k++) {
                if(x + i * dirX + j < 0 || x + i * dirX + j >= sizX || y + i * dirY + k < 0 || y + i * dirY + k >= sizY){
                    continue;
                } else if(board[x + i * dirX + j][y + i * dirY + k] != '.') {
                    continue;
                } else {
                    board[x + i * dirX + j][y + i * dirY + k] = '#';
                }
            }
        }
    }
    return true;
}

bool Board::sunk(int x, int y) {
    unsigned char test = board[x][y];
    std::tuple<int, int, Board::directions> result = sweep(x, y);
    x = std::get<0>(result);
    y = std::get<1>(result);
    Board::directions dir = std::get<2>(result);
    if(dir == NONE) {
        return false;
    }
    for(int i = 0; i < board[x][y] - 4 - '0'; i++) {
        if(board[x + i * decodeDir(dir).first][y + i * decodeDir(dir).second] != test) {
            return false;
        }
    }
    return true;
}

unsigned char Board::checkForHit(int x, int y) {
    x--;
    y--;
    if(board[x][y] >= '2' && board[x][y] <= '5') {
        board[x][y] += 4;
        if(sunk(x, y)) {
            return board[x][y];
        } else {
            return 'X';
        }
    } else {
        return 'o';
    }
}

int Board::colNums() {
    std::cout << std::endl;
    int i = sizX;
    int xWidth = 0;
    do {
        i /= 10;
        xWidth++;
    } while(i > 0);
    if(sizY >= 1000) {
        std::cout << " ";
        for(int i = 0; i < xWidth; i++) {
            std::cout << " ";
        }
        for(int i = 1; i <= sizY; i++) {
            if(i < 1000) {
                std::cout << "  ";
            } else {
                std::cout << i/1000 << " ";
            }
        }
        std::cout << std::endl;
    }
    if(sizY >= 100) {
        std::cout << " ";
        for(int i = 0; i < xWidth; i++) {
            std::cout << " ";
        }
        for(int i = 1; i <= sizY; i++) {
            if(i < 100) {
                std::cout << "  ";
            } else {
                std::cout << i%1000/100 << " ";
            }
        }
        std::cout << std::endl;
    }
    if(sizY >= 10) {
        std::cout << " ";
        for(int i = 0; i < xWidth; i++) {
            std::cout << " ";
        }
        for(int i = 1; i <= sizY; i++) {
            if(i < 10) {
                std::cout << "  ";
            } else {
                std::cout << i%100/10 << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << " ";
    for(int i = 0; i < xWidth; i++) {
        std::cout << " ";
    }
    for(int i = 1; i <= sizY; i++) {
        std::cout << i%10 << " ";
    }
    std::cout << std::endl;
    return xWidth;
}

void Board::print() {
    int xWidth = colNums();
    int i = 1;
    for(auto &x: board) {
        std::cout << std::setw(xWidth) << i << " ";
        i++;
        for(auto &y: x) {
            std::cout << y << " ";
        }
        std::cout << std::endl;
    }
}

void Board::printCheat() {
    int xWidth = colNums();
    int i = 1;
    for(auto &x: board) {
        std::cout << std::setw(xWidth) << i << " ";
        i++;
        for(auto &y: x) {
            if(y == 'X' || y == 'o' || y == '.' || (y >= '2' && y <= '5')) {
                std::cout << y << " ";
            } else if(y >= '6' && y <= '9') {
                std::cout << 'X' << " ";
            } else if(y == '#') {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

bool Board::placeShipRandom(int size) {
    int tries = 0;
    while(!placeShip(distributionX(gen), distributionY(gen), size, (Board::directions)distributionDir(gen)) && tries < 50) {
        tries++;
    };
    return tries < 50;
}

bool Board::clear() {
    for(auto &i: board) {
        for(auto &j: i) {
            j = '.';
        }
    }
    return true;
}

unsigned char Board::getAt(int x, int y) {
    x--;
    y--;
    if(x < 0 || x >= sizX || y < 0 || y >= sizY) {
        return 0;
    } else {
        return board[x][y];
    }
}

unsigned char Board::setAt(int x, int y, unsigned char c) {
    x--;
    y--;
    if(x < 0 || x >= sizX || y < 0 || y >= sizY) {
        return 0;
    } else {
        board[x][y] = c;
        return board[x][y];
    }
}

std::tuple<int, int, Board::directions> Board::sweep(int x, int y) {
    int dirX;
    int dirY;
    int sides = 0;
    int dir = 0;
    for(int i = 1; i <= 8; i++) {
        dirX = decodeDir((directions)i).first;
        dirY = decodeDir((directions)i).second;
        if(x + dirX < 0 || x + dirX >= sizX || y + dirY < 0 || y + dirY > sizY) {
            continue;
        } else {
            if(board[x + dirX][y + dirY] >= '2' && board[x + dirX][y + dirY] <= '5') {
                return {-1, -1, NONE};
            }
            if((board[x + dirX][y + dirY] >= '6' && board[x + dirX][y + dirY] <= '9') || board[x + dirX][y + dirY] == 'X') {
                sides++;
                dir =  i;
            }
        }
    }
    if(sides == 2) {
        for(int i = 1; i < board[x][y] - 4 - '0'; i++) {
            int posX = x + i * decodeDir((directions)dir).first;
            int posY = y + i * decodeDir((directions)dir).second;
            if(posX < 0 || posX >= sizX || posY < 0 || posY >= sizY || board[posX][posY] == '#') {
                x = x + (i-1) * decodeDir((directions)dir).first;
                y = y + (i-1) * decodeDir((directions)dir).second;
                dir = (dir + 3) % 8 + 1;
                return {x, y, (Board::directions)dir};
            }
        }
    } else if(sides == 1) {
        return {x, y, (Board::directions)dir};
    }
}

bool Board::sink(int x, int y, int size) {
    x--;
    y--;
    std::tuple<int, int, Board::directions> result = sweep(x, y);
    x = std::get<0>(result);
    y = std::get<1>(result);
    protectShip(x, y, size, decodeDir(std::get<2>(result)).first, decodeDir(std::get<2>(result)).second);
    for(int i = 0; i < size; i++) {
        board[x + i * decodeDir(std::get<2>(result)).first][y + i * decodeDir(std::get<2>(result)).second] = size + '0';
    }
    return true;
}

int Board::getSizX() const {
    return sizX;
}

int Board::getSizY() const {
    return sizY;
}
