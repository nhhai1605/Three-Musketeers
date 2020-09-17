#include "Mosaic.h"

Mosaic::Mosaic(std::string playerName)
{
    this->playerName = playerName;
    table = new Tile ** [TABLE_SIZE]; 
    for (int i = 0; i < TABLE_SIZE; ++i) 
    {
        table[i] = new Tile * [TABLE_SIZE];
    }
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        for(int j = 0; j < TABLE_SIZE; j++)
        {
            table[i][j] = new Tile(EMPTY);
        }
    }

    playerRow = new Tile ** [PLAYER_ROW_SIZE];
    for(int i = 0; i < PLAYER_ROW_SIZE; i++)
    {
        playerRow[i] = new Tile * [i+1];
    }
    for(int i = 0; i < PLAYER_ROW_SIZE; i++)
    {   
        for(int j = 0; j <= i; j++)
        {
            playerRow[i][j] = new Tile(EMPTY);
        }
    }

    brokenTiles = new Tile * [BROKEN_TILES_SIZE];
    for(int i = 0; i < BROKEN_TILES_SIZE; i++)
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
    for(int i = 0; i < PLAYER_ROW_SIZE; i ++)
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
    for(int i = 0; i < TABLE_SIZE; i ++)
    {
        std::cout << " " << table[index][i]->getTileName();
    }
}

void Mosaic::printPlayerRow(int index)
{
    //count is the number of spaces needed to match with the spec's format
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
