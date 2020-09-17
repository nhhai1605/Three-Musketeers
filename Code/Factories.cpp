#include "Factories.h"
#include <iostream>

Factories::Factories()
{
    factories = new Tile ** [NUMBER_OF_FACTORY]; 
    for (int i = 0; i < NUMBER_OF_FACTORY; ++i) 
    {
        factories[i] = new Tile * [FACTORY_SIZE];
    }
    for(int i = 0; i < NUMBER_OF_FACTORY; i++)
    {
        for(int j = 0; j < FACTORY_SIZE; j++)
        {
            factories[i][j] = new Tile(EMPTY);
        }
    }
    central.push_back(new Tile(F));
}

Factories::~Factories()
{

}

void Factories::printAll()
{
    std::cout << "0: " << central.front()->getTileName() << std::endl;
    for(int i = 0; i < NUMBER_OF_FACTORY; i++)
    {
        std::cout << i+1 << ": " ;
        for(int j = 0; j < FACTORY_SIZE; j++)
        {
            std::cout << factories[i][j]->getTileName() << " ";
        }
        std::cout << std::endl;
    }
}

void Factories::dealTile(TileBag* tileBag)
{
    for(int i = 0; i < NUMBER_OF_FACTORY; i++)
    {
        for(int j = 0; j < FACTORY_SIZE; j++)
        {
            Tile* tile = tileBag->getFirstTile();
            factories[i][j]->setTileType(tile->getTileType());
            tileBag->addTileBackToBag(tile);
            tileBag->takeTileFromBag();
        }
    }
}