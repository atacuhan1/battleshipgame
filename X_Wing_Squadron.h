#ifndef X_WING_SQUADRON_H
#define X_WING_SQUADRON_H
#include "Battle_Ship.h"



class X_Wing_Squadron : public Battle_Ship{
public:
    X_Wing_Squadron();
    int shoot(char attackGrid[][12], char enemyGrid[][12], vector<Battle_Ship*>& enemyFleet, int& shots_remaining, int active_rows, int active_cols) override;

};



#endif //X_WING_SQUADRON_H
