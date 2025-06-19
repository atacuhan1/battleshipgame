#include "X_Wing_Squadron.h"
#include <iostream>
#include <string>
using namespace std;

X_Wing_Squadron::X_Wing_Squadron() : Battle_Ship(3,2,2) {}

int X_Wing_Squadron::shoot(char attackGrid[][12], char enemyGrid[][12], vector<Battle_Ship*>& enemyFleet, int& shots_remaining, int active_rows, int active_cols) {
    int shots_done = 0;
    int hits = 0;

    while (shots_done < laser_bursts && shots_remaining > 0) {
        string coord;
        cout << "Enter coordinate (e.g. a5): ";
        cin >> coord;

        if (coord.length() < 2 || coord.length() > 3)
            continue;

        char c = tolower(coord[0]);
        if (c < 'a' || c >= 'a' + active_rows)
            continue;

        int row = c - 'a';
        int col;
        try {
            col = stoi(coord.substr(1)) - 1;
        } catch (...) {
            continue;
        }

        if (col < 0 || col >= active_cols)
            continue;

        // check the place where the shot was taken before
        if (attackGrid[row][col] != '*') {
            cout << "You already shot here!\n";
            continue;
        }

        if (enemyGrid[row][col] == '*') {
            attackGrid[row][col] = '0';
            cout << "Miss at " << coord << "!\n";
        }
        else if (enemyGrid[row][col] >= '1' && enemyGrid[row][col] <= '5') {
            char shipSymbol = enemyGrid[row][col];
            attackGrid[row][col] = shipSymbol;
            cout << "Hit at " << coord << "! Ship size " << shipSymbol << "\n";

            int shipSize = shipSymbol - '0';
            for (Battle_Ship* ship : enemyFleet) {
                if (!ship->isSunk() && ship->getSize() == shipSize) {
                    ship->hit();
                    if (ship->isSunk())
                        cout << " Enemy ship of size " << shipSize << " has been SUNK!\n";
                    break;
                }
            }

            hits++;  //
        }

        shots_done++;
        shots_remaining--;
    }

    return hits;
}



