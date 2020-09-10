#include "Tile.h"

Tile::Tile(TileType tileType)
{
	this->tileType = tileType;
}

TileType Tile::getType()
{
	return tileType;
}