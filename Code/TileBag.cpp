#include "TileBag.h"
#include <iostream>

TileBag::TileBag()
{
    tileList = new LinkedList();
    for(int i = R; i != F; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            tileList->addToBack(new Tile((TileType)i));
        }
    }
}

TileBag::~TileBag()
{
    delete tileList;
}

void TileBag::addTileBackToBag(Tile* tile)
{   
    tileList->addToBack(tile);
}
void TileBag::takeTileFromBag()
{
    tileList->removeFromFront();
}
int TileBag::size()
{
    return tileList->size();
}

void TileBag::printAll()
{
    for(int i = 0; i < size(); i ++)
    {
        printTileAtIndex(i);
    }
}

void TileBag::printTileAtIndex(int index)
{
    std::cout << tileList->getTileTypeAtIndex(index)->getTileName() << std::endl;
}
