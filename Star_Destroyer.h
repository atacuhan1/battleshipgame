#ifndef STAR_DESTROYER_H
#define STAR_DESTROYER_H
#include "Battle_Ship.h"



class Star_Destroyer : public Battle_Ship {
public:
    Star_Destroyer();
    int shoot(char attackGrid[][12], char enemyGrid[][12], vector<Battle_Ship*>& enemyFleet, int& shots_remaining, int active_rows, int active_cols) override;


};



#endif //STAR_DESTROYER_H
