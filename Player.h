#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>

using namespace std;
#include "Battle_Ship.h"


class Player {
protected:



    string name;
    vector<Battle_Ship*> fleet;
    char grid[12][12]; //  grid for players own ships.
    char attackGrid[12][12]; // grid for attack
    int active_rows , active_cols;

public:
    int totalShots = 0;
    int totalHits = 0;
    int totalMisses = 0;
    int lostCells = 0;
    int lostStarDestroyer = 0;
    int lostCalamari = 0;
    int lostXwing = 0;
    int lostTIE = 0;
    void updateLosses();
    int extra_shots = 0;
    int reduce_shot_penalty = 0;
    bool force_one_shot = false;
    bool has_extra_turn = false;
    Player(string playerName, int rows, int cols) {
        name = playerName;
        active_rows = rows;
        active_cols = cols;

        for (int i = 0; i < 12; i++)
            for (int j = 0; j < 12; j++) {
                grid[i][j] = '*';
                attackGrid[i][j] = '*';
            }
    }

    void deployShips(int mode); // Mode for game modes 1 - Swiftstrike 2 - Starlight 3- Titans
    void displayGrids() const;
    int shoot(Player& opponent, int shots, int active_rows, int active_cols);
    bool allShipsSunk() const;
    void applyGift(int giftType, Player & opponent, int active_rows, int active_cols);
    int getMaxLaserBursts() const;
    char (&getGrid())[12][12];
    void printStats(const Player& opponent) const;


    string getName() const;
    vector<Battle_Ship*> & getFleet();

    ~Player();

};



#endif //PLAYER_H
