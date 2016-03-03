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

Pool* my_pool;

extern char* string_strip;
//extern int num_of_test = 5;

extern int getFreeMemoryBlocks();
extern char* getInfo(int pos, int lenght);
extern int markMap(int pos, int lenght, char free);
extern int initMap();
extern int initializePool(int pool_size);
extern void deletePool();
extern void* getFirstFreePlace(int lenght);
extern void* _malloc(int lenght);
//extern int _free(int pos, int lenght);
extern int _free(void* ptr);
extern int getPos(void * ptr);
//extern void printPool();
//extern void printMap();
extern void DumpDetailedPool();
extern void DumpPool();
extern int isFree(int pos);
