#include "Mosaic.h"

Mosaic::Mosaic(std::string playerName)
{
    this->playerName = playerName;
    table = new Tile ** [5]; 
    for (int i = 0; i < 5; ++i) 
    {
        table[i] = new Tile * [5];
    }
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            table[i][j] = new Tile(EMPTY);
        }
    }

    playerRow = new Tile ** [5];
    for(int i = 0; i < 5; i++)
    {
        playerRow[i] = new Tile * [i+1];
    }
    for(int i = 0; i < 5; i++)
    {   
        for(int j = 0; j <= i; j++)
        {
            playerRow[i][j] = new Tile(EMPTY);
        }
    }

    brokenTiles = new Tile*[7];
    for(int i = 0; i < 7; i++)
    {
        brokenTiles[i] = new Tile(EMPTY);
    }
} 
Mosaic::~Mosaic()
{

    
}

void Mosaic::printMosaic()
{
    std::cout << "Mosaic for " << playerName << std::endl;
    for(int i = 0; i < 5; i ++)
    {
        std::cout << i+1 << ":";
        printPlayerRow(i);
        std::cout << " ||";
        printTableRow(i); 
        std::cout << std::endl;
    }
}

void Mosaic::printTableRow(int index)
{
    for(int i = 0; i < 5; i ++)
    {
        std::cout << " " << table[index][i]->getTileName();
    }
}

void Mosaic::printPlayerRow(int index)
{
    int count = 8 - index*2;
    for(int i = 0; i < count; i++)
    {
        std::cout << " ";
    }
    for(int i = 0; i <= index; i++)
    {
        std::cout << " " << playerRow[index][i]->getTileName();
    }
}
