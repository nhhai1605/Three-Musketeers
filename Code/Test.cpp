#include "TileBag.h"
#include "Factories.h"
#include "Mosaic.h"
#include <iostream>

int main(int argc, char *argv[]) {

    // LinkedList *list = new LinkedList();
    // Tile* tile1 = new Tile(R);
    // Tile* tile2 = new Tile(Y);
    // Tile* tile3 = new Tile(B);
    // Tile* tile4 = new Tile(L);

    // list->addToBack(tile1);
    // list->addToBack(tile2);
    // list->addToBack(tile3);
    // list->addToBack(tile4);
    // list->addToFront(tile1);
    // list->addToFront(tile2);
    // list->addToFront(tile3);
    // list->addToFront(tile4);

    // list->removeFromBack();
    // list->removeFromBack();
    // list->removeFromBack();
    // list->removeFromBack();
    // for(int i = 0; i < list->size(); i++)
    // {
    //     std::cout << list->getTileTypeAtIndex(i) << std::endl;
    // }
    // std::cout << list->getFirstTileType() << std::endl;
    // std::cout << list->getLastTileType() << std::endl;

    // //output is 6, which is EMPTY according to enum Tile
    // std::cout << list->getTileTypeAtIndex(10) << std::endl;

    TileBag* tileBag = new TileBag();
    std::cout << tileBag->size() << std::endl;
    tileBag->addTileBackToBag(new Tile((TileType)10));
    tileBag->printAll();

    Factories *factories = new Factories();
    tileBag->takeTileFromBag();
    factories->dealTile(tileBag);
    factories->printAll();
    factories->dealTile(tileBag);
    factories->printAll();
    Mosaic * mosaic = new Mosaic("player1");
    mosaic->printMosaic();


}