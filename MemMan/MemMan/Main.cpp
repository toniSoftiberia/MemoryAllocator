/*
#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
#include "MemMan.h"
//#include <vld.h> 

using namespace std;

int main(int argc, char ** argv)
{
	//Pool manager();
	//my_pool reserve memory

	inicializePool(102);
	
	printPool();

	
	printMap();

	//allocateNewElement
	OWN_LOG("Allocate new element");
	int new_pos = _malloc(1);
	if (new_pos > 0) {
		setInfo("TestMem", new_pos, 1);
	}
	printMap();


	//allocateNElements
	OWN_LOG("Allocate new elements[8]");
	new_pos = _malloc(8);
	if (new_pos > 0) {
		setInfo("En un lugar de la Mancha, de cuyo nombre no quiero acordarme...", new_pos, 8);
	}
	printMap();


	//fillAllMemory
	OWN_LOG("Allocate elements to the end");
	int free_postions = my_pool->free_memory / DATA_SIZE;
	for (int i = 0; i < free_postions; ++i) {
		new_pos = _malloc(1);
		if (new_pos > 0) {
			setInfo("TestMem", new_pos, 1);
		}
	}
	printMap();


	//freePositionRandom
	OWN_LOG("Free position 3");
	_free(3, 1);
	printMap();

	
	OWN_LOG("Allocate new element");
	new_pos = _malloc(1);
	if (new_pos > 0) {
		setInfo("NewElem", new_pos, 1);
	}
	printMap();

	//allocateNewElement
	OWN_LOG("Free position 4");
	_free(4, 1);
	printMap();


	//allocateNElements
	OWN_LOG("Allocate new elements[8]");
	new_pos = _malloc(8);
	if (new_pos > 0) {
		setInfo("Hace mucho tiempo, en una galaxia muy, muy lejana. Es un periodo", new_pos, 8);
	}
	printMap();
	

	//freeRang
	OWN_LOG("Free positions from 3 to 11");
	for (int i = 3; i < 12; ++i) {
		_free(i, 1);
	}
	printMap();



	//allocateNElements
	OWN_LOG("Allocate new elements[8]");
	new_pos = _malloc(8);
	if (new_pos > 0) {
		setInfo("Hace mucho tiempo, en una galaxia muy, muy lejana. Es un periodo", new_pos, 8);
	}
	printMap();

	//allocateNewElement
	OWN_LOG("Allocate new element");
	new_pos = _malloc(1);
	if (new_pos > 0) {
		setInfo("LastEl1", new_pos, 1);
	}
	printMap();


	//allocateNewElement
	OWN_LOG("Allocate new element");
	new_pos = _malloc(1);
	if (new_pos > 0) {
		setInfo("LastEl2", new_pos, 1);
	}
	printMap();


	//freeAllMemory
	OWN_LOG("Free all memory");
	for (int i = 0; i < my_pool->pool_size / DATA_SIZE; ++i) {
		_free(i,1);
	}
	printMap();


	//ShowState
	printPool();

	deletePool();

	return 0;
}
*/