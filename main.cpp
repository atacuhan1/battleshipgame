/* Ata Çuhan– 2637585, Mehmet Çağan Yeğin – 2638336
We read and accept the submission rules and the extra rules specified
in each question. This is our own work that is done by us only */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"

using namespace std;

int main() {
    srand(time(0)); // for random

    string name1, name2;
    int mode;

    cout << "Enter name for Player 1: ";
    cin >> name1;

    cout << "Enter name for Player 2: ";
    cin >> name2;

    cout << "\nSelect battle mode:\n";
    cout << "1. The Swiftstrike (5x8)\n";
    cout << "2. The Starlight Clash (8x10)\n";
    cout << "3. Wrath of Titans (10x12)\n";
    cout << "Choice: ";
    cin >> mode;

    int rows, cols;
    if (mode == 1) { rows = 5; cols = 8; }
    else if (mode == 2) { rows = 8; cols = 10; }
    else { rows = 10; cols = 12; }

    Player player1(name1, rows, cols);
    Player player2(name2, rows, cols);

    cout << "\n" << name1 << ", place your fleet:\n";
    player1.deployShips(mode);

    cout << "\n" << name2 << ", place your fleet:\n";
    player2.deployShips(mode);

    int turn = rand() % 2; // 0 or 1, randomly selects who starts

    while (!player1.allShipsSunk() && !player2.allShipsSunk()) {
        Player& current = (turn % 2 == 0) ? player1 : player2;
        Player& opponent = (turn % 2 == 0) ? player2 : player1;

        cout << "\n====== " << current.getName() << "'s Turn ======" << endl;

        int shots = current.getMaxLaserBursts();

        if (current.force_one_shot) {
            shots = 1;
            current.force_one_shot = false;
        } else if (current.reduce_shot_penalty > 0) {
            shots = max(1, shots - 1);
            current.reduce_shot_penalty--;
        }

        int hitsThisTurn = current.shoot(opponent, shots, rows, cols);
        current.displayGrids();

        if (hitsThisTurn > 1) {
            int giftRoll = rand() % 100 + 1;
            int giftType;

            if (giftRoll <= 10) giftType = 1;
            else if (giftRoll <= 40) giftType = 2;
            else if (giftRoll <= 60) giftType = 3;
            else if (giftRoll <= 80) giftType = 4;
            else giftType = 5;

            cout << current.getName() << " had " << hitsThisTurn << " hits. Time to open the gift box...\n";
            cout << " Lucky !! Gift number " << giftType << " is awarded.\n";

            current.applyGift(giftType, opponent, rows, cols);
        }

        player1.updateLosses();
        player2.updateLosses();

        // Round Summary
        cout << "\n--- Round Summary ---\n";
        cout << "Player1: " << player1.getName() << "    Player2: " << player2.getName() << "\n";
        cout << "Total Shoots: " << player1.totalShots << "    Total Shoots: " << player2.totalShots << "\n";
        cout << "Hits: " << player1.totalHits << "    Hits: " << player2.totalHits << "\n";
        cout << "Misses: " << player1.totalMisses << "    Misses: " << player2.totalMisses << "\n";
        cout << "Lost: " << player1.lostCells << " cells    Lost: " << player2.lostCells << " cells\n";
        cout << "Lost Star Destroyer (1): " << player1.lostStarDestroyer
             << "    Lost Star Destroyer (1): " << player2.lostStarDestroyer << "\n";
        cout << "Lost Mon Calamari Cruiser(2): " << player1.lostCalamari
             << "    Lost Mon Calamari Cruiser(2): " << player2.lostCalamari << "\n";
        cout << "Lost X-Wing Squadron(2): " << player1.lostXwing
             << "    Lost X-Wing Squadron(2): " << player2.lostXwing << "\n";
        cout << "Lost TIE Fighter (1): " << player1.lostTIE
             << "    Lost TIE Fighter (1): " << player2.lostTIE << "\n";

        cout << current.getName() << " shoots now (can shoot " << current.getMaxLaserBursts() << "):\n";

        // Victory check
        if (opponent.allShipsSunk()) {
            cout << "\n " << current.getName() << " WINS THE GAME!" << endl;
            break;
        }

        if (!current.has_extra_turn)
            turn++;
        else
            current.has_extra_turn = false;
    }

    return 0;
}
