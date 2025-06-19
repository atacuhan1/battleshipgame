#ifndef MON_CALAMARI_CRUISER_H
#define MON_CALAMARI_CRUISER_H
#include "Battle_Ship.h"


class Mon_Calamari_Cruiser : public Battle_Ship {

public:

    Mon_Calamari_Cruiser();
    int shoot(char attackGrid[][12], char enemyGrid[][12], vector<Battle_Ship*>& enemyFleet, int& shots_remaining, int active_rows, int active_cols) override;

};



#endif //MON_CALAMARI_CRUISER_H
