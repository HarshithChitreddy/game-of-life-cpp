#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "GameOfLife.h"
using namespace std;

static bool all_ws(const string &s) {
    for (char ch : s) {
        if (ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n') return false;
    }
    return true;
}

bool parseFile(const string &filename, int &h, int &w, string &board) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: Could not open file\nReturn Code: 1\n";
        return false;
    }

    string line;
    int pl = 0;
    int lastL = 1;

    if (!getline(fin, line)) {
        cerr << "Error: Invalid header on line 1\n";
        cerr << "Return Code: 2\n";
        return false;
    }
    pl++;
    if (!line.empty() && line.back() == '\r') line.pop_back();

    stringstream ss(line);
    if (!(ss >> h >> w) || h < 0 || w < 0) {
        cerr << "Error: Invalid header on line 1\n";
        cerr << "Return Code: 2\n";
        return false;
    }

    vector<string> rows;
    for (; getline(fin, line); ) {
        pl++;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (all_ws(line)) continue;

        string comp;
        for (char ch : line) {
            if (ch != ' ' && ch != '\t' && ch != '\r' && ch != '\n') {
                comp.push_back(ch);
            }
        }

        if ((int)comp.size() != w) {
            cerr << "Error: Invalid row length on line " << pl << "\n";
            cerr << "Return Code: " << (pl + 1) << "\n";
            return false;
        }

        for (char ch : comp) {
            if (ch != 'X' && ch != 'O') {
                cerr << "Error: Invalid character on line " << pl << "\n";
                cerr << "Return Code: " << (pl + 1) << "\n";
                return false;
            }
        }

        rows.push_back(comp);
        lastL = pl;
        if ((int)rows.size() > h) {
            cerr << "Error: Invalid height on line " << pl << "\n";
            cerr << "Return Code: " << (pl + 1) << "\n";
            return false;
        }
    }

    if ((int)rows.size() < h) {
        int errorL = lastL;
        cerr << "Error: Invalid height on line " << errorL << "\n";
        cerr << "Return Code: " << (errorL + 1) << "\n";
        return false;
    }

    board = "";
    for (size_t i = 0; i < rows.size(); i++) {
        for (size_t j = 0; j < rows[i].size(); j++) {
            char bit = (rows[i][j] == 'O') ? '1' : '0';
            board.push_back(bit);
        }
    }
    return true;
}

int main(int argc, char **argv) {
    string filename;
    int generations = 10;
    int printCycle = 1;
    bool threeState = false;
    bool wrap = false;

    int pauseInterval = 0;
    
    char aliveChar = '1';
    char deadChar = '0';
    char decayChar = 'D';

    string outputFile = "";

    int opt;
    while ((opt = getopt(argc, argv, "f:g:p:swx:a:d:e:o:")) != -1) {
        switch (opt) {
            case 'f': filename = optarg; break;
            case 'g': generations = stoi(optarg); break;
            case 'p': printCycle = stoi(optarg); break;
            case 's': threeState = true; break;
            case 'w': wrap = true; break;
            case 'x': pauseInterval = stoi(optarg); break;
            case 'a': aliveChar = optarg[0]; break;
            case 'd': deadChar = optarg[0]; break;
            case 'e': decayChar = optarg[0]; break;
            case 'o': outputFile = optarg; break;
            default:
                cerr << "Usage: -f [filename] -g [gens] -p [interval] -s|-w\n";
                return 1;
        }
    }

    if (filename.empty()) {
        cerr << "Error: No input file specified\n";
        return 1;
    }
    if (threeState && wrap) {
        cerr << "Error: -s and -w cannot be used together\n";
        return 1;
    }
    if (aliveChar == deadChar || aliveChar == decayChar || deadChar == decayChar) {
        cerr << "Error: Can not set multiple cells to the same char\n";
        return 1;
    }

    int h, w;
    string board;
    if (!parseFile(filename, h, w, board)) return 1;

    GameOfLife game(w, h, board, threeState, wrap);
    game.aliveChar = aliveChar;
    game.deadChar = deadChar;
    game.decayChar = decayChar;

    ofstream fout;
    ostream *outStream = &cout;
    if (!outputFile.empty()) {
        fout.open(outputFile);
        if (!fout) {
            cerr << "Error: could not open output file\n";
            return 1;
        }
        outStream = &fout;
    }
    
    game.printGame(*outStream);

    for (int g = 1; g <= generations; g++) {
        game.next();

        bool shouldPause = (pauseInterval > 0 && g % pauseInterval == 0);
        bool isLastGenOnPrint = (g == generations && g % printCycle == 0);

        if (shouldPause && !isLastGenOnPrint) {
            cout << "Game Paused: What would you like to do?\n";
            cout << "Current GameBoard:\n";
            game.printGame(cout);

            string cmd;
            for (cin >> cmd; cmd != "x"; cin >> cmd) {
                if (cmd == "a" || cmd == "d" || cmd == "e") {
                    int coord1, coord2;
                    cin >> coord1;

                    char newState;
                    if (cmd == "a") newState = '1';
                    else if (cmd == "d") newState = '0';
                    else newState = 'D';

                    if (cin.peek() == ' ') {
                        cin >> coord2;
                        game.setCell(coord1, coord2, newState);
                    } else {
                        game.setCell(coord1, newState);
                    }
                    cin.ignore(10000, '\n');

                    cout << "Current GameBoard:\n";
                    game.printGame(cout);
                }
            }
        }

        if (g % printCycle == 0) {
            game.printGame(*outStream);
        }
    }

    if (fout.is_open()) {
        fout.close();
    }

    return 0;
}