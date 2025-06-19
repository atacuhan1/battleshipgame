
#ifndef BATTLE_SHIP_H
#define BATTLE_SHIP_H
#include <vector>
#include <iostream>
using namespace std;


class Battle_Ship {
protected:
    int size;
    int hits_to_destroy;
    int laser_bursts;
    bool sunk;
public:
    Battle_Ship(int sz,int hits,int bursts);

    virtual int shoot(char attackGrid[][12], char enemyGrid[][12], vector<Battle_Ship*>& enemyFleet, int& shots_remaining, int active_rows, int active_cols)= 0;
                                // A virtual class for all the ships shooting range with max of 12 grid (Max grid possbile = 12 because of Wrath Of Titans mod)
    int getSize() const;
    int getLaserBursts() const;
    int getHitsToDestroy() const;
    bool isSunk() const;
    void hit();
    void reset();

    virtual ~Battle_Ship()=default;


};



#endif //BATTLE_SHIP_H
