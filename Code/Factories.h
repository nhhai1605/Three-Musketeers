#ifndef FACTORIES
#define FACTORIES
#include "TileBag.h"
class Factories
{
    public:
    Factories();
    ~Factories();
    void printAll();
    void dealTile(TileBag*tileBag);
    private:
    // Tile * central;
    Tile *** factories;
};
#endif //FACTORIES