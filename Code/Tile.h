#ifndef TILE
#define TILE
#include "TileType.h"
class Tile
{	
	public:
		Tile(TileType tileType);
		TileType getType();
		char getTileName();
	private:
		TileType tileType;
};
#endif //TILE