#ifndef TILE
#define TILE
#include "Types.h"
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