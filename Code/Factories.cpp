#include "Factories.h"
#include <iostream>

Factories::Factories()
{
    factories = new Tile ** [5]; 
    for (int i = 0; i < 5; ++i) 
    {
        factories[i] = new Tile * [4];
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            factories[i][j] = new Tile(EMPTY);
        }
    }
}

Factories::~Factories()
{

}

void Factories::printAll()
{
    for(int i = 0; i < 5; i++)
    {
        std::cout << i+1 << ": " ;
        for(int j = 0; j < 4; j++)
        {
            std::cout << factories[i][j]->getTileName();
        }
        std::cout << std::endl;
    }
}

void Factories::dealTile(TileBag* tileBag)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            Tile* tile = tileBag->getFirstTile();
            factories[i][j]->setTileType(tile->getType());
            tileBag->addTileBackToBag(tile);
            tileBag->takeTileFromBag();
        }
    }
}