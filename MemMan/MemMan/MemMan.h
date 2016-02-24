#pragma once

#include "Globals.h"
#include <string.h>
#include <stdio.h>

typedef struct Pool Pool;
/* Declare the struct with integer members x, y */
struct Pool {
	int free_memory;		//number of positions of memory free
	int pool_size;			//size of our memory
	char* _pool;				//the memory
	int* _map;				//memory index		
};

struct Pool* my_pool;



/* Return the number of position free*/
int getFreeMemoryBlocks() {
	return my_pool->free_memory / DATA_SIZE;
}

/* Get the info on the pool*/
char* getInfo(int pos, int lenght) {
	return &my_pool->_pool[pos];
}

/* Get the info on the pool*/
int setInfo(char * data, int pos, int lenght) {
	if (pos + lenght <= my_pool->pool_size / DATA_SIZE) {
		for (int i = 0; i < DATA_SIZE*lenght; ++i) {
			if (data[i] != '\0' && data[i] != '\n')
				my_pool->_pool[(pos * DATA_SIZE) + i] = data[i];
			else
				my_pool->_pool[(pos * DATA_SIZE) + i] = ' ';
		}
		return 1;
	}
	else {
		return 0;
	}
}

/*
Actualize the memory free positions
*/
void freeMemoryActualize(int length, int free) {
	if (free)
		my_pool->free_memory += length * DATA_SIZE;
	else
		my_pool->free_memory -= length * DATA_SIZE;
}

/*
Marks the map from position pos to pos + lenght as free(true/false)
Return:
false : Err: Out of memory Range
true  : OK: Done
*/
int markMap(int pos, int lenght, int free) {
	int res = 0;
	int size = lenght;

	if (pos + lenght <= my_pool->pool_size / DATA_SIZE) {

		int i = pos;
		for (; i < pos + lenght; ++i) {
			if (my_pool->_map[i] == free)
				--size;
			else
				my_pool->_map[i] = free;
		}

		res = 1;
	}

	//actualize memory map
	freeMemoryActualize(size, free);

	return res;
}

//Public
void inicializePool(int pool_size)
{
	//*my_pool = (struct Pool) malloc(sizeof(struct Pool));
	my_pool = (struct Pool *) malloc(sizeof(struct Pool));

	my_pool->pool_size = pool_size;
	//my_pool->free_memory = getFreeMemoryBlocks();
	my_pool->free_memory = pool_size;
	OWN_LOG("Creating the memory manager");

	//Reserve the memory
	my_pool->_pool = (char *)malloc(pool_size);

	//Make a index map
	my_pool->_map = (int *)malloc(pool_size / DATA_SIZE);

	//init map
	for (int i = 0; i < pool_size / DATA_SIZE; ++i) {
		my_pool->_map[i] = 1;
	}

	//We reserve position 0
	setInfo("Reserve", 0, 1);
	markMap(0, 1, 0);
}

void deletePool()
{
	OWN_LOG("Destroying memory manager");
	//check for memory leaks

	free(my_pool->_pool);
	//free(my_pool->_map);
	free(my_pool);
}


/*
Gets the first position where we can allocate lenght positions of memory
Return:
-2 : Err: Cannot find a big enough space
-1 : Err: The memory is full
0 : Err: Undefined
>0 : OK: Start position memory reserved
*/
int getFirstFreePlace(int lenght) {
	int res = 0;

	//Is there free space
	if (my_pool->free_memory != 0) {

		//found first free position
		int found = 0;
		int free = 0;
		int i = 0;

		for (; i <= my_pool->pool_size / DATA_SIZE && !found; ++i) {
			if (my_pool->_map[i] == 1) {
				int free = 1;
				for (int j = 0; j < lenght; ++j)
					free &= my_pool->_map[i + j];
				if (free) {
					found = 1;
					--i;
				}
			}
		}

		if (found) {
			OWN_LOG("Free position found");
			res = i;	//OK: Start position memory reserved
			markMap(res, lenght, 0);
		}
		else {
			OWN_LOG("Free position not found");
			res = -2;	//Cannot find a big enough space
		}
	}
	else {
		OWN_LOG("Memory full");
		res = -1;		//The memory is full
	}

	return res;
}

//Malloc & Free

/* Try to allocate "num" data
Return:
-2 : Err: Cannot find a big enough space
-1 : Err: The memory is full
0 : Err: Undefined
>0 : OK: Start position memory reserved
*/
int _malloc(int lenght) {
	int res = 0;

	int pos = getFirstFreePlace(lenght);

	if (pos > 0) {
		OWN_LOG("Reserving position %d", pos);
	}
	else
		OWN_LOG("Memory not reserved");

	res = pos;

	return res;
}

/* Try to free a memory position*/
int _free(int pos, int lenght) {
	int res = 1;

	if (pos > 0 && pos < my_pool->pool_size / DATA_SIZE) {
		OWN_LOG("Deleting position %d", pos);
		markMap(pos, lenght, 1);
	}
	else {
		OWN_LOG("You cannot delete this position: %d", pos);
		res = 0;
	}

	return res;
}


void printPool() {
	char to_print[51];
	OWN_LOG("\n");
	OWN_LOG("Printing Memory Data");
	for (int i = 0; i < my_pool->pool_size;) {
		int j = 0;
		for (; j < 50 && i < my_pool->pool_size; ++j, ++i) {
			if (my_pool->_map[i])
				to_print[j] = my_pool->_pool[i];
			else
				to_print[j] = my_pool->_pool[i];
		}
		to_print[j] = '\0';
		OWN_LOG(to_print);
	}

	sprintf_s(to_print, "Pool size (Bytes): %d", my_pool->pool_size);
	OWN_LOG(to_print);

	sprintf_s(to_print, "Free Bytes: %d", my_pool->free_memory);
	OWN_LOG(to_print);

	sprintf_s(to_print, "Single element size (Bytes): %d", DATA_SIZE);
	OWN_LOG(to_print);
}

/*
Shows in output console a map
*/
void printMap() {
	char to_print[21];
	OWN_LOG("\n");
	OWN_LOG("Printing Memory Map");
	for (int i = 0; i < my_pool->pool_size / DATA_SIZE;) {
		int j = 0;
		for (; j < 20 && i < my_pool->pool_size / DATA_SIZE; ++j, ++i) {
			if (my_pool->_map[i])
				to_print[j] = '0';
			else
				to_print[j] = '1';
		}
		to_print[j] = '\0';
		OWN_LOG(to_print);
	}

	OWN_LOG("Map size:");
	sprintf_s(to_print, "%d", my_pool->pool_size / DATA_SIZE);
	OWN_LOG(to_print);

	OWN_LOG("Free Memory elements:");
	sprintf_s(to_print, "%d", my_pool->free_memory / DATA_SIZE);
	OWN_LOG(to_print);

	OWN_LOG("\n");
}

/*
Looks if pos is a free position
Return:
-1 : Err: Out of memory Range
0 : OK: pos is busy
1 : OK: pos is free
*/
int isFree(int pos) {
	if (pos < my_pool->pool_size / DATA_SIZE)
		return -1; //Out of memory
	return (my_pool->_map[pos] == 1);
}
