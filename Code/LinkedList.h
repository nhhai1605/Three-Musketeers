#ifndef LINKED_LIST
#define LINKED_LIST
#include "Tile.h"

class Node {
public:
	Node* next;
	Tile* tile;
	Node (Tile* tile)
	{
		this->tile = new Tile(tile->getTileType());
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

	Tile * getTileAtIndex(int index);
	Tile * getFirstTile();
	Tile * getLastTile();
private:
	Node* head;
	int sizeOfList;
};

#endif //LINKED_LIST