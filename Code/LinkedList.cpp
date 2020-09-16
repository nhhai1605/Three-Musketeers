#include "LinkedList.h"

LinkedList::LinkedList() {
	head = nullptr;
	sizeOfList = 0;
}

LinkedList::LinkedList(LinkedList& other) 
{

}

LinkedList::~LinkedList() 
{
	while(head != nullptr)
	{
		this->removeFromFront();
	}
}

void LinkedList::addToFront(Tile *tile) {
	Tile* other = new Tile(tile->getType());
	Node* node = new Node(other);
	node->next = head;
	head = node;
	sizeOfList++;
}

void LinkedList::addToBack(Tile *tile) {
	Tile* other = new Tile(tile->getType());
	Node* node = new Node(other);
	if(head != nullptr)
	{
		Node* curr = head;
		while(curr->next != nullptr)
		{
			curr = curr->next;
		}
		node->next = nullptr;
		curr->next = node;
	}
	else
	{
		node->next = head;
		head = node;
	}
	sizeOfList++;
}

void LinkedList::removeFromFront() 
{
	if(head != nullptr)
	{
		Node * needToDelete = head;
		head = head->next;
		delete needToDelete;
		needToDelete = nullptr;
		sizeOfList--;
	}

}

void LinkedList::removeFromBack() 
{
	if(head != nullptr)
	{
		Node * needToDelete = head;
		Node * beforeNeedToDelete ;
		while(needToDelete->next != nullptr)
		{
			beforeNeedToDelete = needToDelete;
			needToDelete = needToDelete->next;
		}
		if(beforeNeedToDelete != nullptr)
		{
			beforeNeedToDelete->next = nullptr;
		}
		else
		{
			head = nullptr;
		}	
		delete needToDelete;
		needToDelete = nullptr;
		sizeOfList--;
	}
}

int LinkedList::size()
{
	return sizeOfList;
}

TileType LinkedList::getTileTypeAtIndex(int index)
{
	if(index < 0 || index > sizeOfList)
	{
		return EMPTY;
	}
	else
	{
		Node * curr = head;
		int count = 0;
		while(count != index)
		{
			curr = curr->next;
			count++;
		}
		return curr->tile->getType();
	}
}
TileType LinkedList::getFirstTileType()
{
	return head->tile->getType();
}
TileType LinkedList::getLastTileType()
{
	Node * curr = head;
	while(curr->next != nullptr)
	{
		curr = curr->next;
	}
	return curr->tile->getType();
}