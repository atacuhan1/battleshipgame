#ifndef TIE_FIGHTER_H
#define TIE_FIGHTER_H
#include "Battle_Ship.h"



class TIE_Fighter : public Battle_Ship{

public:

    TIE_Fighter();
    int shoot(char attackGrid[][12], char enemyGrid[][12], vector<Battle_Ship*>& enemyFleet, int& shots_remaining, int active_rows, int active_cols) override;

};



#endif //TIE_FIGHTER_H
