#ifndef MOSAIC
#define MOSAIC
#include "Factories.h"
#include <string>
#include <iostream>
class Mosaic
{
    public:
    Mosaic(std::string playerName);
    ~Mosaic();
    void printMosaic();

    private:
    std::string playerName;
    Tile *** table;
    Tile *** playerRow;
    Tile ** brokenTiles;
    void printTableRow(int index);
    void printPlayerRow(int index);

};
#endif