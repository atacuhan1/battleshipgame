# Battleship

Two-player console battleship game in C++, themed as a Star Wars fleet battle. Coursework by Ata Çuhan and Mehmet Çağan Yeğin.

Each player places a fleet, then takes turns firing. A ship that is still afloat contributes its laser bursts; the active ship with the most bursts sets how many shots that player gets. Two or more hits in one turn opens a random gift.

## Battle modes

| Mode | Board | Fleet |
| --- | --- | --- |
| 1. The Swiftstrike | 5×8 | 1 Star Destroyer, 1 Mon Calamari Cruiser, 1 X-Wing Squadron, 2 TIE Fighters |
| 2. The Starlight Clash | 8×10 | 2 / 2 / 2 / 4 |
| 3. Wrath of Titans | 10×12 | 4 / 3 / 2 / 4 |

## Ships

| Ship | Size | Hits to sink | Laser bursts | Grid mark |
| --- | --- | --- | --- | --- |
| Star Destroyer | 5 | 4 | 3 | `5` |
| Mon Calamari Cruiser | 4 | 3 | 4 | `4` |
| X-Wing Squadron | 3 | 2 | 2 | `3` |
| TIE Fighter | 1 | 1 | 1 | `1` |

Ships are placed horizontally or vertically. Coordinates look like `a1`: a letter for the row and a number for the column.

## Gifts

A multi-hit turn rolls one of these:

1. Add a new ship
2. Extra shot this round
3. Opponent loses one shot next round
4. Opponent may shoot only once next round
5. Immediate extra turn

The game ends when one fleet is fully sunk.

## Build and run

```bash
g++ *.cpp -o battleship
./battleship
```
