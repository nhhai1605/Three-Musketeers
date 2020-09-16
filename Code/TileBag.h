#ifndef TILE_BAG
#define TILE_BAG
#include "LinkedList.h"
class TileBag
{
    public:
        TileBag();
        ~TileBag();
    private:
        LinkedList* tileList;

};
#endif //TILE_BAG