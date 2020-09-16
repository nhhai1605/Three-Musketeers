#ifndef FACTORIES
#define FACTORIES
#include "TileBag.h"
#include <vector>

class Factories
{
    public:
    Factories();
    ~Factories();
    void printAll();
    void dealTile(TileBag*tileBag);
    private:
    std::vector <Tile*> central;
    Tile *** factories;
};
#endif //FACTORIES