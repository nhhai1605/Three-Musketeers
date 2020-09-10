#ifndef LINKED_LIST
#define LINKED_LIST
#include "Tile.h"

class Node {
public:
	Node* next;
	Tile* tile;
	Node (Tile* tile)
	{
		this->tile = new Tile(tile->getType());
	}
	~Node()
	{
		delete this->tile;
	}
};

class LinkedList {
public:
	LinkedList();
	LinkedList(LinkedList& other);
	~LinkedList();
	
	int size();
	void addToFront(Tile *tile);
	void addToBack(Tile *tile);

	void removeFromFront();
	void removeFromBack();

	TileType getTileTypeAtIndex(int index);
	TileType getFirstTileType();
	TileType getLastTileType();
private:
	Node* head;
	int sizeOfList;
};

#endif //LINKED_LIST