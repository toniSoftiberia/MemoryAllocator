#include <iostream>
#include "Globals.h"
#include "MemMan.h"
//#include <vld.h> 

using namespace std;

int main(int argc, char ** argv)
{
	MemMan manager(108);

	manager.printPool();

	manager.printMap();


	LOG("Allocate new element");
	int new_pos = manager._new();
	if (new_pos > 0) {
		manager.setInfo("TestMem", new_pos);
	}
	manager.printMap();

	LOG("Allocate new elements[8]");
	new_pos = manager._new(8);
	if (new_pos > 0) {
		manager.setInfo("En un lugar de la Mancha, de cuyo nombre no quiero acordarme...", new_pos, 8);
	}
	manager.printMap();

	LOG("Allocate elements to the end");
	int free_postions = manager.free_memory / DATA_SIZE;
	for (int i = 0; i < free_postions; ++i) {
		new_pos = manager._new();
		if (new_pos > 0) {
			manager.setInfo("TestMem", new_pos);
		}
	}
	manager.printMap();

	LOG("Free position 3");
	manager._delete(3);
	manager.printMap();

	LOG("Allocate new element");
	new_pos = manager._new();
	if (new_pos > 0) {
		manager.setInfo("NewElem", new_pos);
	}
	manager.printMap();

	LOG("Free position 4");
	manager._delete(4);
	manager.printMap();

	LOG("Allocate new elements[8]");
	new_pos = manager._new(8);
	if (new_pos > 0) {
		manager.setInfo("Hace mucho tiempo, en una galaxia muy, muy lejana. Es un periodo", new_pos, 8);
	}
	manager.printMap();
	
	LOG("Free positions from 3 to 11");
	for (int i = 3; i < 12; ++i) {
		manager._delete(i);
	}
	manager.printMap();


	LOG("Allocate new elements[8]");
	new_pos = manager._new(8);
	if (new_pos > 0) {
		manager.setInfo("Hace mucho tiempo, en una galaxia muy, muy lejana. Es un periodo", new_pos, 8);
	}
	manager.printMap();


	LOG("Allocate new element");
	new_pos = manager._new();
	if (new_pos > 0) {
		manager.setInfo("LastEl1", new_pos);
	}
	manager.printMap();

	LOG("Allocate new element");
	new_pos = manager._new();
	if (new_pos > 0) {
		manager.setInfo("LastEl2", new_pos);
	}
	manager.printMap();

	/*
	LOG("Free all memory");
	for (int i = 0; i < manager.pool_size / DATA_SIZE; ++i) {
		manager._delete(i);
	}
	manager.printMap();*/

	manager.printPool();

	return 0;
}