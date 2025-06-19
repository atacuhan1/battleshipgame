#include "Player.h"
#include "Star_Destroyer.h"
#include "Mon_Calamari_Cruiser.h"
#include "X_Wing_Squadron.h"
#include "TIE_Fighter.h"
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool parseCoord(const string& input, int& row, int& col) {
    if (input.length() < 2 || input.length() > 3) return false;
    char c = tolower(input[0]);
    if (c < 'a' || c > 'l') return false;
    row = c - 'a';
    try {
        col = stoi(input.substr(1)) - 1;
    } catch (...) {
        return false;
    }
    return (col >= 0 && col < 12);
}


void Player::deployShips(int mode) {
    cout << name << ", place your ships on the grid." << endl;

    int starDestroyers = 0, cruisers = 0, xwings = 0, ties = 0;
    if (mode == 1) { starDestroyers = 1; cruisers = 1; xwings = 1; ties = 2; }
    else if (mode == 2) { starDestroyers = 2; cruisers = 2; xwings = 2; ties = 4; }
    else { starDestroyers = 4; cruisers = 3; xwings = 2; ties = 4; }

    auto placeShip = [&](Battle_Ship* ship, char symbol) {
        while (true) {
            string start, end;
            int r1, c1, r2, c2;

            cout << "Enter start coord for ship (size " << ship->getSize() << "): ";
            cin >> start;
            cout << "Enter end coord: ";
            cin >> end;

            if (!parseCoord(start, r1, c1) || !parseCoord(end, r2, c2)) {
                cout << "Invalid coordinates. Try again.\n";
                continue;
            }

            int dRow = r2 - r1;
            int dCol = c2 - c1;

            // placement control
            if (dRow != 0 && dCol != 0) {
                cout << "Diagonal placement is not allowed. Use vertical or horizontal only.\n";
                continue;
            }

            int len = max(abs(dRow), abs(dCol)) + 1;
            if (len != ship->getSize()) {
                cout << "Length mismatch. Ship size is " << ship->getSize() << ".\n";
                continue;
            }

            int stepR = (dRow == 0) ? 0 : (dRow > 0 ? 1 : -1);
            int stepC = (dCol == 0) ? 0 : (dCol > 0 ? 1 : -1);

            bool overlap = false;
            int r = r1, c = c1;
            for (int i = 0; i < ship->getSize(); i++) {
                if (grid[r][c] != '*') {
                    overlap = true;
                    break;
                }
                r += stepR;
                c += stepC;
            }

            if (overlap) {
                cout << "Overlap detected. Try again.\n";
                continue;
            }

            r = r1; c = c1;
            for (int i = 0; i < ship->getSize(); i++) {
                grid[r][c] = symbol;
                r += stepR;
                c += stepC;
            }

            fleet.push_back(ship);
            break;
        }
    };

    for (int i = 0; i < starDestroyers; i++) placeShip(new Star_Destroyer(), '5');
    for (int i = 0; i < cruisers; i++) placeShip(new Mon_Calamari_Cruiser(), '4');
    for (int i = 0; i < xwings; i++) placeShip(new X_Wing_Squadron(), '3');
    for (int i = 0; i < ties; i++) placeShip(new TIE_Fighter(), '1');
}


int Player::getMaxLaserBursts() const {
    int max = 0;
    for (int i = 0; i < fleet.size(); i++) {
        if (!fleet[i]->isSunk()) {
            max = std::max(max, fleet[i]->getLaserBursts());
        }
    }
    return max;
}


int Player::shoot(Player& opponent, int shots, int rows, int cols) {
    int totalHitsThisTurn = 0;       // only for this turn
    int shotsBefore = shots;         // store total shots before the turn

    for (Battle_Ship* ship : fleet) {
        if (!ship->isSunk() && shots > 0) {
            // ship->shoot now returns int → number of hits
            int hits = ship->shoot(
                attackGrid,
                opponent.grid,
                opponent.fleet,
                shots,
                rows,
                cols
            );

            totalHitsThisTurn += hits;
        }
    }

    int shotsUsed = shotsBefore - shots;       // numbr of shots used this turn
    totalShots += shotsUsed;
    totalHits += totalHitsThisTurn;
    totalMisses = totalShots - totalHits;

    return totalHitsThisTurn;
}



void Player::updateLosses() {
    lostCells = 0;
    lostStarDestroyer = 0;
    lostCalamari = 0;
    lostXwing = 0;
    lostTIE = 0;

    for (Battle_Ship* ship : fleet) {
        if (ship->isSunk()) {
            lostCells += ship->getSize();
            switch (ship->getSize()) {
                case 5: lostStarDestroyer++; break;
                case 4: lostCalamari++; break;
                case 3: lostXwing++; break;
                case 1: lostTIE++; break;
            }
        }
    }
}






void Player::displayGrids() const {
    cout << "\n" << name << "'s Battle View\n\n";

    cout << "Own Grid" << string(20, ' ') << "Attack Grid\n";
    cout << "  ";
    for (int j = 0; j < active_cols; j++) cout << j + 1 << " ";
    cout << string(8, ' ') << "  ";
    for (int j = 0; j < active_cols; j++) cout << j + 1 << " ";
    cout << endl;

    for (int i = 0; i < active_rows; i++) {
        char rowLabel = 'A' + i;
        cout << rowLabel << " ";
        for (int j = 0; j < active_cols; j++) {
            cout << grid[i][j] << " ";
        }

        cout << string(8, ' ') << rowLabel << " ";

        for (int j = 0; j < active_cols; j++) {
            cout << attackGrid[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;
}

bool Player::allShipsSunk() const {
    for (int i = 0; i < fleet.size(); i++) {
        if (!fleet[i]->isSunk()) {
            return false; // If there is an at least one ship left game continues.
        }
    }
    return true; // All sunk
}

void Player::applyGift(int giftType, Player& opponent, int active_rows, int active_cols) {
    if (giftType == 1) {
        cout << "Gift: Add a new ship!\n";
        int roll = rand() % 100 + 1;
        Battle_Ship* newShip;
        char symbol;

        if (roll <= 10) { newShip = new Star_Destroyer(); symbol = '5'; }
        else if (roll <= 30) { newShip = new Mon_Calamari_Cruiser(); symbol = '4'; }
        else if (roll <= 60) { newShip = new X_Wing_Squadron(); symbol = '3'; }
        else { newShip = new TIE_Fighter(); symbol = '1'; }

        cout << name << " earned a new ship (" << symbol << "). Place it on the grid.\n";

        // Reuse the same placeShip logic
        auto place = [&](Battle_Ship* ship, char sym) {
            while (true) {
                string s, e;
                int r1, c1, r2, c2;
                cout << "Start coord: "; cin >> s;
                cout << "End coord: "; cin >> e;
                if (!parseCoord(s, r1, c1) || !parseCoord(e, r2, c2)) continue;

                int dr = r2 - r1, dc = c2 - c1;
                int len = max(abs(dr), abs(dc)) + 1;
                if (len != ship->getSize()) continue;

                int stepR = (dr == 0) ? 0 : (dr > 0 ? 1 : -1);
                int stepC = (dc == 0) ? 0 : (dc > 0 ? 1 : -1);
                bool overlap = false;
                int r = r1, c = c1;
                for (int i = 0; i < ship->getSize(); i++) {
                    if (grid[r][c] != '*') { overlap = true; break; }
                    r += stepR; c += stepC;
                }

                if (overlap) continue;

                r = r1; c = c1;
                for (int i = 0; i < ship->getSize(); i++) {
                    grid[r][c] = sym;
                    r += stepR; c += stepC;
                }

                fleet.push_back(ship);
                break;
            }
        };

        place(newShip, symbol);
    }

    else if (giftType == 2) {
        cout << " Gift: Extra shot this round!\n";
        extra_shots += 1;
    }

    else if (giftType == 3) {
        cout << " Gift: Opponent loses 1 shot next round!\n";
        opponent.reduce_shot_penalty += 1;
    }

    else if (giftType == 4) {
        cout << " Gift: Opponent can shoot only once next round!\n";
        opponent.force_one_shot = true;
    }

    else if (giftType == 5) {
        cout << " Gift: Immediate extra turn!\n";
        has_extra_turn = true;
    }
}


string Player::getName() const {
    return name;
}

vector<Battle_Ship*>& Player::getFleet() {
    return fleet;
}

Player::~Player() {
    for (Battle_Ship* ship : fleet) {
        delete ship;
    }
}

char (&Player::getGrid())[12][12] {
    return grid;
}




