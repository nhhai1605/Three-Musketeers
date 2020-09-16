#include "Tile.h"

Tile::Tile(TileType tileType)
{
	this->tileType = tileType;
}

TileType Tile::getType()
{
	return tileType;
}

char Tile::getTileName()
{
    char c ;
    if(tileType == R)
    {
        c = 'R';
    }
    else if (tileType == Y)
    {
        c = 'Y';
    }
    else if (tileType == B)
    {
		c = 'B';
    }
    else if (tileType == L)
    {
        c = 'L';
    }
    else if (tileType == U)
    {
		c = 'U';
    }
    else if (tileType == F)
    {
		c = 'F';
    }
    else
    {
		c = '.';
    }
	return c;
}

void Tile::setTileType(TileType typeNeedToSet)
{
  this->tileType = typeNeedToSet;
}