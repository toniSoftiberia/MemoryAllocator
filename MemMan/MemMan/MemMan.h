#pragma once

#include "Globals.h"

class MemMan
{
public:
	MemMan(int pool_size = 100);
	~MemMan();

	int _new(int lenght = 1);
	bool _delete(int pos, int lenght = 1);
	char* getInfo(int pos, int lenght = 1);
	bool setInfo(char * data, int pos, int lenght = 1);

	void printPool();
	void printMap();

	int free_memory;		//number of positions of memory free
	int pool_size;			//size of our memory
private:
	char* pool;				//the memory
	bool* map;				//memory index

	int getFirstFreePlace(int lenght = 1);
	bool markMap(int pos, int lenght = 1, bool free = false);
	int isFree(int pos);
	void freeMemoryActualize(int length = -1, bool free = false);
};