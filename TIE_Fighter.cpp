#include "TIE_Fighter.h"
#include <iostream>
#include <string>
using namespace std;

TIE_Fighter::TIE_Fighter() : Battle_Ship(1,1,1) {}

int TIE_Fighter::shoot(
    char attackGrid[][12],
    char enemyGrid[][12],
    vector<Battle_Ship*>& enemyFleet,
    int& shots_remaining,
    int active_rows,
    int active_cols
) {
    int hits = 0;
    int shots_done = 0;

    while (shots_done < laser_bursts && shots_remaining > 0) {
        string coord;
        cout << "Enter coordinate (e.g. a5): ";
        cin >> coord;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (coord.length() < 2 || coord.length() > 3) {
            cout << "Invalid coordinate format.\n";
            continue;
        }

        char c = tolower(coord[0]);
        int row = c - 'a';
        int col;

        try {
            col = stoi(coord.substr(1)) - 1;
        } catch (...) {
            cout << "Invalid number in coordinate.\n";
            continue;
        }

        if (row < 0 || row >= active_rows || col < 0 || col >= active_cols) {
            cout << "Coordinate out of grid bounds.\n";
            continue;
        }

        if (attackGrid[row][col] != '*') {
            cout << "You already shot this cell.\n";
            continue;
        }

        char target = enemyGrid[row][col];
        if (target == '1' || target == '3' || target == '4' || target == '5') {
            attackGrid[row][col] = target;
            cout << " HIT at " << coord << endl;
            shots_done++;
            shots_remaining--;
            hits++;

            bool matched = false;
            for (Battle_Ship* enemyShip : enemyFleet) {
                if (!enemyShip->isSunk() && enemyShip->getSize() == (target - '0')) {
                    enemyShip->hit();
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                cout << " WARNING: This ship has already sunk before. You fired a blank shot. " << coord << endl;
            }

        } else {
            attackGrid[row][col] = '0';
            cout << "Miss at " << coord << endl;
            shots_done++;
            shots_remaining--;
        }
    }

    return hits;
}


