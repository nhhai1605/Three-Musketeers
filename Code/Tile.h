#ifndef TILE
#define TILE
#include "TileType.h"
class Tile
{	
	public:
		Tile(TileType tileType);
		TileType getType();
	private:
		TileType tileType;
};
#endif //TILE