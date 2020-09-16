#ifndef TILE
#define TILE
#include "TileType.h"
class Tile
{	
	public:
		Tile(TileType tileType);
		TileType getTileType();
		char getTileName();
		void setTileType(TileType typeNeedToSet);
	private:
		TileType tileType;
};
#endif //TILE