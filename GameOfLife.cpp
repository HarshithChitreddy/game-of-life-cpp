#include "GameOfLife.h"

GameOfLife::GameOfLife(int w, int h, const std::string &game, bool threeState, bool wrap)
: w(w), h(h), gen(0), threeState(threeState), wrap(wrap), b(game)
{}

void GameOfLife::next() {
    std::string nxtB = b; 
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            int idx = r * w + c;
            int liveN = 0;
            
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;
                    
                    int nr = r + dr;
                    int nc = c + dc;
                    
                    if (wrap) {
                        if (nr < 0) nr = h - 1;
                        if (nr >= h) nr = 0;
                        if (nc < 0) nc = w - 1;
                        if (nc >= w) nc = 0;
                    } else {
                        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                    }
                    
                    int nIdx = nr * w + nc;
                    if (b[nIdx] == '1') ++liveN;
                }
            }
            
            if (threeState) {
                if (b[idx] == '1') {
                    if (liveN == 2 || liveN == 3) nxtB[idx] = '1';
                    else nxtB[idx] = 'D';
                } else if (b[idx] == 'D') {
                    if (liveN == 2) nxtB[idx] = 'D';
                    else if (liveN == 3) nxtB[idx] = '1';
                    else nxtB[idx] = '0';
                } else {
                    if (liveN == 3) nxtB[idx] = 'D';
                    else nxtB[idx] = '0';
                }
            } else {
                if (b[idx] == '1') {
                    if (liveN < 2) nxtB[idx] = '0';
                    else if (liveN == 2 || liveN == 3) nxtB[idx] = '1';
                    else nxtB[idx] = '0';
                } else {
                    if (liveN == 3) nxtB[idx] = '1';
                    else nxtB[idx] = '0';
                }
            }
        }
    }
    b = nxtB;
    gen += 1;
}

void GameOfLife::nextNGen(int n) {
    if (n <= 0) return;
    for (int i = 0; i < n; ++i) next();
}

void GameOfLife::printGame(std::ostream &out) const {
    out << "Generation: " << gen << "\n";
    for (int r = 0; r < h; ++r) {
        for (int c = 0; c < w; ++c) {
            char cell = b[r * w + c];
            if (cell =='1') out << aliveChar;
            else if (cell == 'D') out << decayChar;
            else out << deadChar;
        }
        out << "\n";
    }
    out << "\n";
}

void GameOfLife::setCell(int idx, char state) {
    if (idx >=0 && idx < (int)b.size()){
        b[idx] = state;
    }
}

void GameOfLife::setCell(int x, int y, char state) {
    int idx = y * w + x;
    setCell(idx, state);
}