#pragma once

#include "Globals.h"
#include <string.h>
#include <stdio.h>

typedef struct Pool Pool;
struct Pool {
	int free_memory;		//number of positions of memory free
	int pool_size;			//size of our memory
	char* _pool;			//the memory
	char* _map;				//memory index	

	//Pool *Next;			//pointer to the next Pool
};

Pool* my_pool;

extern int getFreeMemoryBlocks();
extern char* getInfo(int pos, int lenght);
extern int setInfo(char * data, int pos, int lenght);
extern void freeMemoryActualize(int length, char free);
extern int markMap(int pos, int lenght, char free);
extern void inicializePool(int pool_size);
extern void deletePool();
extern int getFirstFreePlace(int lenght);
extern int _malloc(int lenght);
extern int _free(int pos, int lenght);
//extern void printPool();
//extern void printMap();
extern void DumpDetailedPool();
extern void DumpPool();
extern int isFree(int pos);
