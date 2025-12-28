#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <string>
#include <iostream>

class GameOfLife {
public:
    int w;
    int h;
    int gen;
    bool threeState = false;
    bool wrap = false;
    std::string b;

    char aliveChar = '1';
    char deadChar = '0';
    char decayChar = 'D';

    GameOfLife(int w, int h, const std::string &game, bool threeState = false, bool wrap = false);
    void next();
    void nextNGen(int n);
    void printGame(std::ostream &out) const;
    void setCell(int idx, char state);
    void setCell(int x, int y, char state);
};

#endif
