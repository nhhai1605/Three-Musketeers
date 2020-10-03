#ifndef FACTORIES
#define FACTORIES
#include "TileBag.h"

class Factories
{
    public:
    Factories();
    ~Factories();
    void printFactories();
    void dealTile(TileBag*tileBag);
    Tile ** getFactory(int row);
    void clearFactory(int row);
    void addToCentral(Tile * tile);
    bool factoriesAreEmpty();
    LinkedList* getCentral();

    private:
    Tile *** factories;
    LinkedList* central;
};
#endif //FACTORIES