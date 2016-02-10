#include "MemMan.h"
#include <string.h>
#include <iostream>

using namespace std;

MemMan::MemMan(int pool_size)
	:pool_size(pool_size),
	free_memory(pool_size)
{
	LOG("Creating the memory manager");

	//Reserve the memory
	pool = new char[pool_size];

	//Make a index map
	map = new bool[pool_size / DATA_SIZE];

	//init map
	for (int i = 0; i < pool_size / DATA_SIZE; ++i) {
		map[i] = true;
	}

	//We reserve position 0
	setInfo("Reserve", 0);
	markMap(0, 1, false);
}

MemMan::~MemMan()
{
	LOG("Destroying memory manager");
	//check for memory leaks

	RELEASE_ARRAY(pool);
	RELEASE_ARRAY(map);
}

/* Try to allocate "num" data 
Return:
-2 : Err: Cannot find a big enough space
-1 : Err: The memory is full
 0 : Err: Undefined
>0 : OK: Start position memory reserved
*/
int MemMan::_new(int lenght) {
	int res = 0;

	int pos = getFirstFreePlace(lenght);

	if (pos > 0){
		LOG("Reserving position %d", pos);
	}else
		LOG("Memory not reserved");

	res = pos;	

	return res;
}

/* Try to free a memory position*/
bool MemMan::_delete(int pos, int lenght) {
	bool res = true;

	if (pos > 0 && pos < pool_size / DATA_SIZE){
		LOG("Deleting position %d", pos);
		markMap(pos, lenght, true);
	}
	else{
		LOG("You cannot delete this position: %d", pos);
		res = false;
	}

	return res;
}

/* Get the info on the pool*/
char* MemMan::getInfo(int pos, int lenght) {
	return &pool[pos];
}

/* Get the info on the pool*/
bool MemMan::setInfo(char * data, int pos, int lenght) {
	if (pos + lenght <= pool_size / DATA_SIZE) {
		for (int i = 0; i < DATA_SIZE*lenght; ++i) {
			if (data[i] != '\0' && data[i] != '\n')
				pool[(pos * DATA_SIZE) + i] = data[i];
			else
				pool[(pos * DATA_SIZE) + i] = ' ';
		}
		return true;
	}
	else {
		return false;
	}
}

void MemMan::printPool(){
	char to_print[51];
	LOG("\n");
	LOG("Printing Memory Data");
	for (int i = 0; i < pool_size;) {
		int j = 0;
		for (; j < 50 && i < pool_size; ++j, ++i) {
			if (map[i])
				to_print[j] = pool[i];
			else
				to_print[j] = pool[i];
		}
		to_print[j] = '\0';
		LOG(to_print);
	}

	sprintf_s(to_print, "Pool size (Bytes): %d", pool_size);
	LOG(to_print);

	sprintf_s(to_print, "Free Bytes: %d", free_memory);
	LOG(to_print);

	sprintf_s(to_print, "Single element size (Bytes): %d", DATA_SIZE);
	LOG(to_print);
}

/*
Shows in output console a map 
*/ 
void MemMan::printMap(){
	char to_print[21];
	LOG("\n");
	LOG("Printing Memory Map");
	for (int i = 0; i < pool_size / DATA_SIZE;) {
		int j = 0;
		for (; j < 20 && i < pool_size / DATA_SIZE; ++j, ++i) {
			if (map[i])
				to_print[j] = '0';
			else
				to_print[j] = '1';
		}
		to_print[j] = '\0';
		LOG(to_print);
	}

	LOG("Map size:");
	sprintf_s(to_print, "%d", pool_size / DATA_SIZE);
	LOG(to_print);

	LOG("Free Memory elements:");
	sprintf_s(to_print, "%d", free_memory / DATA_SIZE);
	LOG(to_print);

	LOG("\n");
}

/*
Gets the first position where we can allocate lenght positions of memory
Return:
-2 : Err: Cannot find a big enough space
-1 : Err: The memory is full
 0 : Err: Undefined
>0 : OK: Start position memory reserved
*/
int MemMan::getFirstFreePlace(int lenght) {
	int res = 0;

	//Is there free space
	if (free_memory != 0) {

		//found first free position
		bool found = false;
		bool free = true;
		int i = 0;
		for (; i <= pool_size / DATA_SIZE && !found; ++i) {
			if (map[i] == true) {
				for (int j = 0; j < lenght; ++j)
					free &= map[i+j];
				if (free) {
					found = true;
					--i;
				}
			}
		}

		if (found) {
			LOG("Free position found");
			res = i;	//OK: Start position memory reserved
			markMap(res, lenght, false);
		}
		else {
			LOG("Free position not found");
			res = -2;	//Cannot find a big enough space
		}
	}
	else {
		LOG("Memory full");
		res = -1;		//The memory is full
	}

	return res;
}

/*
Marks the map from position pos to pos + lenght as free(true/false)
Return:
false : Err: Out of memory Range
true  : OK: Done
*/
bool MemMan::markMap(int pos, int lenght, bool free) {
	bool res = false;
	int size = lenght;

	if (pos + lenght <= pool_size / DATA_SIZE) {

		int i = pos;
		for (; i < pos + lenght; ++i) {
			if (map[i] == free)
				--size;
			else
				map[i] = free;
		}

		res = true;
	}

	//actualize memory map
	freeMemoryActualize(size, free);

	return res;
}

/*
Looks if pos is a free position
Return:
-1 : Err: Out of memory Range
 0 : OK: pos is busy
 1 : OK: pos is free
*/
int MemMan::isFree(int pos) {
	if (pos < pool_size / DATA_SIZE) 
		return -1; //Out of memory
	return map[pos] == true;
}

/*
Actualize the memory free positions
*/
void MemMan::freeMemoryActualize(int length, bool free) {
	if (free)
		free_memory += length * DATA_SIZE;
	else
		free_memory -= length * DATA_SIZE;
}
