#ifndef TILE_BAG
#define TILE_BAG
#include "LinkedList.h"
#include <fstream>

class TileBag
{
    public:
        TileBag();
        TileBag(std::string stringOfTiles);
        ~TileBag();
        TileBag(TileBag& other);
        void addTileBackToBag(Tile* tile);
        void takeTileFromBag();
        int size();
        void printAll();
        void printTileAtIndex(int index);
        void printTileAtIndex(std::ofstream& outputFile, int index);
        void addFTile(Tile* tile);
        Tile* getFirstTile();
    private:
        LinkedList* tileList;

};
#endif //TILE_BAG