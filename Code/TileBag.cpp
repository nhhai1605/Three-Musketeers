#include "TileBag.h"
#include <iostream>

TileBag::TileBag()
{
    tileList = new LinkedList();
    for(int i = B; i != F; i++)
    {
        for(int j = 0; j < 40; j++)
        {
            tileList->addToBack(new Tile((TileType)i));
        }
    }
    tileList->addToFront(new Tile(F));
}

//This constructor used to make a TileBag base on a string. Helpful for loading a file
TileBag::TileBag(std::string stringOfTiles)
{
    tileList = new LinkedList();
    for(std::string::size_type i = 0; i < stringOfTiles.size(); i++)
    {
        if(stringOfTiles[i] == 'F')
        {
            tileList->addToBack(new Tile(F));
        }
        else if(stringOfTiles[i] == 'B')
        {
            tileList->addToBack(new Tile(B));
        }
        else if(stringOfTiles[i] == 'R')
        {
            tileList->addToBack(new Tile(R));
        }
        else if(stringOfTiles[i] == 'Y')
        {
            tileList->addToBack(new Tile(Y));
        }
        else if(stringOfTiles[i] == 'U')
        {
            tileList->addToBack(new Tile(U));
        }
        else if(stringOfTiles[i] == 'L')
        {
            tileList->addToBack(new Tile(L));
        }
        else if(stringOfTiles[i] == 'F')
        {
            tileList->addToBack(new Tile(F));
        }
        else
        {
            tileList->addToBack(new Tile(EMPTY));
        }   
    }
}

TileBag::~TileBag()
{
    delete tileList;
}

TileBag::TileBag(TileBag& other)
{
    this->tileList = new LinkedList();
    for(int i = 0; i < other.size(); i++)
    {
        this->tileList->addToBack(new Tile(other.tileList->getTileAtIndex(i)->getTileType()));
    }
}

void TileBag::addFTile(Tile* tile)
{
    tileList->addToFront(tile);
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
    std::cout << tileList->getTileAtIndex(index)->getTileName();
}

//This used to print tile at index but into outputFile
void TileBag::printTileAtIndex(std::ofstream& outputFile, int index)
{
    outputFile << tileList->getTileAtIndex(index)->getTileName();
}

Tile* TileBag::getFirstTile()
{
    return tileList->getFirstTile();
}
