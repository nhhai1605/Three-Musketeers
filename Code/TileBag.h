#ifndef TILE_BAG
#define TILE_BAG
#include "LinkedList.h"
class TileBag
{
    public:
        TileBag();
        ~TileBag();
        void addTileBackToBag(Tile* tile);
        void takeTileFromBag();
        int size();
        void printAll();
        void printTileAtIndex(int index);
        Tile* getFirstTile();
    private:
        LinkedList* tileList;

};
#endif //TILE_BAG