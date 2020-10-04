#include "Mosaic.h"

Mosaic::Mosaic(std::string playerName)
{
    this->playerName = playerName;
    score = 0;

    table = new Tile ** [MOSAIC_ROW_SIZE]; 
    for (int i = 0; i < MOSAIC_ROW_SIZE; ++i) 
    {
        table[i] = new Tile * [MOSAIC_ROW_SIZE];
    }
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {
        for(int j = 0; j < MOSAIC_ROW_SIZE; j++)
        {
            table[i][j] = new Tile(EMPTY);
        }
    }

    playerRow = new Tile ** [MOSAIC_ROW_SIZE];
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {
        playerRow[i] = new Tile * [i+1];
    }
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {   
        for(int j = 0; j <= i; j++)
        {
            playerRow[i][j] = new Tile(EMPTY);
        }
    }
} 

Mosaic::~Mosaic()
{
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {
        for(int j = 0; j < MOSAIC_ROW_SIZE; j++)
        {
            delete table[i][j];
            table [i][j] = nullptr;
        }
    }

    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {   
        for(int j = 0; j <= i; j++)
        {
            delete playerRow[i][j];
            playerRow [i][j] = nullptr;       
        }
    }  
    brokenTiles.clear();
}

void Mosaic::printMosaic()
{
    std::cout << "Mosaic for " << playerName << ": " <<  std::endl;
    for(int i = 0; i < MOSAIC_ROW_SIZE; i ++)
    {
        std::cout << i+1 << ":";
        printPlayerRow(i);
        std::cout << " ||";
        printTableRow(i); 
        std::cout << std::endl;
    }
    std::cout << "Broken tiles: ";
    for(std::size_t i = 0, max = brokenTiles.size(); i != max; ++i)
    {
        std::cout << brokenTiles[i]->getTileName() << " ";
    }
    std::cout << std::endl << std::endl;
}

void Mosaic::printTableRow(int index)
{
    for(int i = 0; i < MOSAIC_ROW_SIZE; i ++)
    {
        //This is used to check if the mosaic is deleted or not
        if(table[index][i] != nullptr)
        {
            std::cout << " " << table[index][i]->getTileName();
        }
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
        //This is used to check if the mosaic is deleted or not
        if(playerRow[index][i] != nullptr)
        {
            std::cout << " " << playerRow[index][i]->getTileName();
        }
        else
        {
            std::cout << "  ";
        }
    }
}

//This method is used to know if the tile is added to the player succesfully or not, depend on other tiles already existed in the playerRow
bool Mosaic::addTile(Tile* tile, int row)
{
    bool tileAdded = false;
    for(int i = row; i >= 0; i--)
    {
        if(playerRow[row][i]->getTileType() == EMPTY && tileAdded == false)
        {
            playerRow[row][i]->setTileType(tile->getTileType());
            tileAdded = true;
        }
    }
    return tileAdded;
}

//This method usde to check if the tile type existed in the table or not
bool Mosaic::tileTypeExitedInTable(Tile * tile, int row)
{
    bool typeExisted = false;
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {
        if(table[row][i]->getTileType() == tile->getTileType())
        {
            typeExisted = true;
        }
    }
    return typeExisted;
}

//This method used to check if the tile we want to add into the playerRow is the same type with existing tiles or not.
bool Mosaic::tileDiff(char tileCode, int row)
{
    bool tileDiff= true;
    int countSpace = 0;
    for(int i = row; i >= 0; i--)
    {
        if(playerRow[row][i]->getTileType() == EMPTY)
        {
            countSpace++;
        }
    }
    for(int i = row; i >= 0; i--)
    {
        if(playerRow[row][i]->getTileName() == tileCode)
        {
            tileDiff = false;
        }
    }
    if(countSpace == (row+1))
    {
        tileDiff = false;
    }
    return tileDiff;
}

bool Mosaic::addBrokenTile(Tile * tile)
{
    bool tileAdded = true;
    if(brokenTiles.size() == BROKEN_TILES_SIZE)  
    {
        tileAdded = false;
    }
    else
    {
        Tile * copy = new Tile(tile->getTileType());
        brokenTiles.push_back(copy);
    }
    return tileAdded;
}

int Mosaic::getScore()
{
    return score;
}

//This method used to calculate the score after updateTable
void Mosaic::calculateScore(int row, int col)
{
    int count = 0;
    int numOfEmpty = 0;
    for(int i = col; i < col + MOSAIC_ROW_SIZE; i++)
    {   
        if(i < MOSAIC_ROW_SIZE)
        {
            if(table[row][i]->getTileType() == EMPTY)
            {
                numOfEmpty++;
            }         
            if(numOfEmpty == 0)
            {
                count++;
            }
        }
        else
        {
           if(table[row][i-MOSAIC_ROW_SIZE]->getTileType() == EMPTY)
            {
                numOfEmpty++;
            }         
            if(numOfEmpty == 0)
            {
                count++;
            }
        }
    }
    int maxRow = count;
    count = 0;
    numOfEmpty = 0;
    for(int i = row; i < row + MOSAIC_ROW_SIZE; i++)
    {   
        if(i < MOSAIC_ROW_SIZE)
        {
            if(table[i][col]->getTileType() == EMPTY)
            {
                numOfEmpty++;
            }         
            if(numOfEmpty == 0)
            {
                count++;
            }
        }
        else
        {
            if(table[i-MOSAIC_ROW_SIZE][col]->getTileType() == EMPTY)
            {
                numOfEmpty++;
            }         
            if(numOfEmpty == 0)
            {
                count++;
            }
        }
    }
    int maxCol = count;
    if(maxCol == 1 || maxRow == 1)
    {
        score += (maxCol * maxRow);
    }
    else
    {
        score += maxCol + maxRow;
    }
    
}

//This is used to calculate the score base on the number of broken tiles there are.
void Mosaic::calculateBrokenTilesScore()
{
    if(brokenTiles.size() == 1)
    {
        score -= 1;
    }
    else if(brokenTiles.size() == 2)
    {
        score -= 2;
    }
    else if(brokenTiles.size() == 3)
    {
        score -= 4;
    }
    else if(brokenTiles.size() == 4)
    {
        score -= 6;
    }
    else if(brokenTiles.size() == 5)
    {
        score -= 8;
    }
    else if(brokenTiles.size() == 6)
    {
        score -= 11;
    }
    else if(brokenTiles.size() == 7)
    {
        score -= 14;
    }
}

//this used to update the table, bring the tile from playerRow to table in the correct place
void Mosaic::updateTable(TileBag * tileBag)
{
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            for(int k = B; k != F; k++)
            {
                if(playerRow[i][j]->getTileType() == (TileType)k)
                {
                    if(i+k <= 4)
                    {
                        if(table[i][i+k]->getTileType() == EMPTY && isRowFull(i))
                        {
                            table[i][i+k]->setTileType((TileType)k);
                            calculateScore(i, i+k);
                        }
                    }
                    else
                    {
                        if(table[i][i+k-5]->getTileType() == EMPTY && isRowFull(i))
                        {
                            table[i][i+k-5]->setTileType((TileType)k);
                            calculateScore(i, i+k-5);
                        }
                    }
                }
            }
        }
    }
    calculateBrokenTilesScore();
    for(int i = brokenTiles.size()-1; i >= 0; i--)
    {
        if(brokenTiles[i]->getTileType() != F)
        {
            tileBag->addTileBackToBag(brokenTiles[i]);
            brokenTiles.pop_back();
        }     
        else
        {
            tileBag->addFTile(brokenTiles[i]);
            brokenTiles.pop_back();
        }

    }
    for(int i = 0; i < MOSAIC_ROW_SIZE; i++)
    {
        if(isRowFull(i))
        {
            for(int j = 0; j <= i; j++)
            {
                tileBag->addTileBackToBag(playerRow[i][j]);
                playerRow[i][j]->setTileType(EMPTY);
            }
        }
    }
}


//This used to check if the row is full or not, useful when checking valid input
bool Mosaic::isRowFull(int row)
{
    bool isFull = false;
    int count = 0;
    for(int i = 0; i <= row; i++)
    {
        if(playerRow[row][i]->getTileType() != EMPTY)
        {
            count++;
        }
    }
    if(count == (row+1))
    {
        isFull = true;
    }
    return isFull;
}



