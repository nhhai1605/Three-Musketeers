#include "Factories.h"
#include <iostream>

Factories::Factories()
{
    factories = new Tile ** [NUMBER_OF_FACTORIES]; 
    for (int i = 0; i < NUMBER_OF_FACTORIES; ++i) 
    {
        factories[i] = new Tile * [FACTORY_SIZE];
    }
    for(int i = 0; i < NUMBER_OF_FACTORIES; i++)
    {
        for(int j = 0; j < FACTORY_SIZE; j++)
        {
            factories[i][j] = nullptr;
        }
    }
    central = new LinkedList();
}

Factories::~Factories()
{
    delete central;
    for(int i = 0; i < NUMBER_OF_FACTORIES; i++)
    {
        clearFactory(i);
    }
}

void Factories::printFactories()
{
    std::cout << "Factories: " << std::endl;
    std::cout << "0: ";
    for(int i = 0 ; i < central->size(); i++)
    {
        std::cout << central->getTileAtIndex(i)->getTileName() << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < NUMBER_OF_FACTORIES; i++)
    {
        std::cout << i+1 << ": " ;
        for(int j = 0; j < FACTORY_SIZE; j++)
        {
            if(factories[i][j] != nullptr)
            {
                std::cout << factories[i][j]->getTileName() << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Factories::dealTile(TileBag* tileBag)
{
    central->addToBack(tileBag->getFirstTile());
    tileBag->takeTileFromBag();
    for(int i = 0; i < NUMBER_OF_FACTORIES; i++)
    {
        for(int j = 0; j < FACTORY_SIZE; j++)
        {
            factories[i][j]= new Tile(tileBag->getFirstTile()->getTileType());
            tileBag->takeTileFromBag();
        }
    }
}

Tile ** Factories::getFactory(int row)
{
    Tile ** factoryRow;
    if(factories[row][0] == nullptr)
    {
        factoryRow = nullptr;
    }
    else
    {
        factoryRow = new Tile * [FACTORY_SIZE];
        for(int i = 0; i < FACTORY_SIZE; i++)
        {   
            factoryRow[i] = new Tile(factories[row][i]->getTileType());
        }
    }
    return factoryRow;
}

void Factories::clearFactory(int row)
{
    for(int i = 0; i < FACTORY_SIZE; i++)
    {
        if(factories[row][i] != nullptr)
        {
            delete factories[row][i];
            factories[row][i] = nullptr;
        }
    }
}

void Factories::addToCentral(Tile * tile)
{
    central->addToBack(tile);
}

LinkedList* Factories::getCentral()
{
    return central;
}

bool Factories::factoriesAreEmpty()
{
    bool isEmpty = false;
    int count = 0;
    for(int i = 0; i < NUMBER_OF_FACTORIES; i++)
    {
        for (int j = 0; j < FACTORY_SIZE; j++)
        {
            if(factories[i][j] == nullptr)
            {
                count++;
            }
        }
    }
    if(count == (NUMBER_OF_FACTORIES * FACTORY_SIZE) && central->size() == 0)
    {
        isEmpty = true;
    }
    return isEmpty;
}
