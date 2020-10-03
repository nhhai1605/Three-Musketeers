#ifndef MOSAIC
#define MOSAIC
#include "Factories.h"
#include <string>
#include <iostream>
#include <vector>

class Mosaic
{
    public:
    Mosaic(std::string playerName);
    ~Mosaic();
    void printMosaic();
    bool addTile(Tile* tile, int row);
    bool addBrokenTile(Tile * tile);
    bool tileTypeExitedInTable(Tile * tile, int row);
    bool tileDiff(char tileCode, int row);
    void updateTable(TileBag* tileBag);
    int getScore();
    private:
    std::string playerName;
    Tile *** table;
    Tile *** playerRow;
    std::vector <Tile*> brokenTiles;
    int score;
    void printTableRow(int index);
    void printPlayerRow(int index);   
    void calculateScore(int rows, int cols);
    void calculateBrokenTilesScore();
    bool isRowFull(int row);

};
#endif //MOSAIC