#include "LinkedList.h"

LinkedList::LinkedList() {
	head = nullptr;
	sizeOfList = 0;
}

LinkedList::~LinkedList() 
{
	while(head != nullptr)
	{
		this->removeFromFront();
	}
	sizeOfList = 0;
}

void LinkedList::addToFront(Tile *tile) {
	Tile* other = new Tile(tile->getTileType());
	Node* node = new Node(other);
	node->next = head;
	head = node;
	sizeOfList++;
}

void LinkedList::addToBack(Tile *tile) {
	Tile* other = new Tile(tile->getTileType());
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
void LinkedList::removeAtIndex(int index)
{
	if(index >= 0 && index < sizeOfList)
	{
		if(sizeOfList >= 3)
		{
			Node * needToDelete = head;
			Node * beforeNeedToDelete;
			int count = 0;
			while(count != index)
			{
				beforeNeedToDelete = needToDelete;
				needToDelete = needToDelete->next;
				count++;
			}
			beforeNeedToDelete->next = needToDelete->next;
			needToDelete->next = nullptr;
			delete needToDelete;
			needToDelete = nullptr;
			sizeOfList--;
		}
		else
		{
			if(sizeOfList == 1)
			{
				removeFromFront();
			}
			else if(sizeOfList == 2)
			{
				if(index == 0)
				{
					removeFromFront();
				}
				else if(index == 1)
				{
					removeFromBack();
				}
			}
		}
		
	}
}
int LinkedList::size()
{
	return sizeOfList;
}

Tile* LinkedList::getTileAtIndex(int index)
{
	Tile * tile;
	if(index < 0 || index >= sizeOfList)
	{
		tile = new Tile(EMPTY);
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
		tile =  curr->tile;
	}
	return tile;
}
Tile* LinkedList::getFirstTile()
{
	return head->tile;
}
Tile* LinkedList::getLastTile()
{
	Node * curr = head;
	while(curr->next != nullptr)
	{
		curr = curr->next;
	}
	return curr->tile;
}
