
#include "Battle_Ship.h"
Battle_Ship::Battle_Ship(int sz, int hits, int bursts) {
    size = sz;
    hits_to_destroy = hits;
    laser_bursts = bursts;
    sunk = false;
}

int Battle_Ship::getSize() const {
    return size;
}

int Battle_Ship::getLaserBursts() const {
    return laser_bursts;
}

int Battle_Ship::getHitsToDestroy() const {
    return hits_to_destroy;
}

bool Battle_Ship::isSunk() const {
    return sunk;
}

void Battle_Ship::hit() {
    if (sunk) return;  // If it's already sunk, do nothing

    hits_to_destroy--;
    if (hits_to_destroy <= 0) {
        sunk = true;
        cout << "A " << size << "-cell ship has been SUNK!\n";
    }
}

void Battle_Ship::reset() { // Resets the battle ship back to alive.
    sunk = false;
}
