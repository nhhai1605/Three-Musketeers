#ifndef TILE
#define TILE
#include "TileType.h"
class Tile
{	
	public:
		Tile(TileType tileType);
		TileType getType();
		char getTileName();
		void setTileType(TileType typeNeedToSet);
	private:
		TileType tileType;
};
#endif //TILE