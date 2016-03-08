#pragma once
#include "Globals.h"

typedef struct Pool Pool;
struct Pool {
	int free_memory;		//number of positions of memory free
	int pool_size;			//size of our memory
	char* _pool;			//the memory
	char* _map;				//memory index	

	//Pool *Next;			//pointer to the next Pool
};

extern Pool* my_pool;

extern char* string_strip;

extern void* _malloc(int lenght);
extern int _free(void* ptr);
extern int initializePool(int pool_size);
extern int initMap();
extern void deletePool();
extern int isFree(int pos);
extern int getFreeMemoryBlocks();
extern int markMap(int pos, int lenght, char free);
extern int getPos(void * ptr);
extern void DumpDetailedPool();
extern void DumpPool();

