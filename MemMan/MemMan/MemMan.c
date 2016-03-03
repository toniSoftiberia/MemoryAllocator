#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "MemMan.h"

struct Pool;

/* Return the number of position free*/
int getFreeMemoryBlocks() {
	return my_pool->free_memory / DATA_SIZE;
}

/* Get the info on the pool*/
char* getInfo(int pos, int lenght) {
	return &my_pool->_pool[pos];
}

/*
Marks the map from position pos to pos + lenght as free(true/false)
Return:
false : Err: Out of memory Range
true  : OK: Done
Posible memory positions values:
R: Reserved, this position is like ocupated
F: Free
O: Ocupated
E: End of reserved memory, this position is like ocupated
*/
int markMap(int pos, int lenght, char free) {
	int res = 0;
	int size = lenght;

	if (free == 'O') {
		size = 0;
		if (pos + lenght <= my_pool->pool_size / DATA_SIZE) {

			int i = pos;
			for (; i < pos + lenght; ++i) {
				if (my_pool->_map[i] == 'F') {
					++size;
					my_pool->_map[i] = free;
				}
			}
			if (free == 'O')
				my_pool->_map[--i] = 'E';
			res = 1;
		}
	}

	if (free == 'F') {
		size = 0;
		if (pos <= my_pool->pool_size / DATA_SIZE &&
			my_pool->_map[pos] != 'F') {

			int i = pos;
			for (; my_pool->_map[i] != 'F' &&  my_pool->_map[i] != 'R'; ++i) {
				my_pool->_map[i] = 'F';
				++size;
			}
			res = 1;
		}
	}

	if (free == 'R') {
		size = 0;
		if (pos <= my_pool->pool_size / DATA_SIZE) {
			my_pool->_map[pos] = free;
			res = 1;
			++size;
		}
	}

	//actualize memory map
	if (free == 'F')
		my_pool->free_memory += size * DATA_SIZE;
	else
		my_pool->free_memory -= size * DATA_SIZE;

	return res;
}

int initMap() {
	//init map
	for (int i = 0; i < my_pool->pool_size / DATA_SIZE; ++i)
		my_pool->_map[i] = 'F';
	my_pool->_map[my_pool->pool_size / DATA_SIZE] = '\n';

	my_pool->free_memory = my_pool->pool_size;

	//We reserve position 0
	strcpy(my_pool->_pool, "RES");
	markMap(0, 1, 'R');

	return 1;
}

//Public
int initializePool(int pool_size)
{
	my_pool = (struct Pool *) malloc(sizeof(struct Pool));

	OWN_LOG("Creating the memory manager");
	my_pool->pool_size = pool_size;
	OWN_LOG("Pool size: %d", my_pool->pool_size);
	my_pool->free_memory = pool_size ;
	OWN_LOG("Free memory: %d", my_pool->free_memory);

	//Reserve the memory
	my_pool->_pool = (char *)malloc(pool_size);

	//Make a index map
	my_pool->_map = (char *)malloc((pool_size / DATA_SIZE) + 1);

	//Mark all mapa as free
	int res = initMap();

	//string_strip = _malloc(sizeof(char*)*5);

	return res;
}


void deletePool()
{
	OWN_LOG("Destroying memory manager");
	//check for memory leaks

	//free(my_pool->_map);
	//free(my_pool->_pool);
	//free(my_pool);
}

//Malloc & Free

/* Try to allocate "num" data
Return:
-2 : Err: Cannot find a big enough space
-1 : Err: The memory is full
0 : Err: Undefined
>0 : OK: Start position memory reserved
*/
void* _malloc(int lenght) {
	void* res = NULL;

	//Is there free space
	if (my_pool->free_memory != 0) {

		//found first free position
		int found = 0;
		int free = 0;
		int i = 0;

		int positions_to_reserve = lenght / DATA_SIZE;
		if (lenght % DATA_SIZE > 0)
			++positions_to_reserve;

		//look throw the memory map
		for (; i <= my_pool->pool_size / DATA_SIZE && !found; ++i) {
			if (my_pool->_map[i] == 'F') {
				int free = 1;
				int j = 0;
				
				for (; j < positions_to_reserve && j < my_pool->pool_size / DATA_SIZE; ++j) {
					if (j+ i > 250)
						j = j;
					free &= (my_pool->_map[i + j / DATA_SIZE] == 'F');
				}


				if (free && j == positions_to_reserve) {
					found = 1;
					--i;
				}
				else {
					//optimization for loop speed up
					//i = j; //Don't work
					i = --j;
				}

			}
		}

		if (found) {
			OWN_LOG("Free position found");
			//OK: Start position memory reserved
			
			my_pool->_pool[i*DATA_SIZE] = 'P';
			my_pool->_pool[i*DATA_SIZE + 1] = 'U';
			my_pool->_pool[i*DATA_SIZE + 2] = 'N';
			my_pool->_pool[i*DATA_SIZE + 3] = 'K';
			res = &(my_pool->_pool[i*DATA_SIZE]);

			//for (int j = 0; j < lenght / DATA_SIZE; ++j)
			//	markMap(i + (j / DATA_SIZE), lenght, '0');
			int j = 0;
			//for (; j < positions_to_reserve; ++j) {
			markMap(i, positions_to_reserve, 'O');
			//}
		}
		else {
			OWN_LOG("Free position not found");
		}
	}
	else {
		OWN_LOG("Memory full");
	}

	return res;
}

int _free(void * ptr) {
	int res = 0;

	int pos = getPos(ptr);
	OWN_LOG("Free position getPos: %d", pos);
	int map_pos = pos / DATA_SIZE;
	int lenght = 1;

	if (map_pos == 0) {
		res = -1;
	}
	else if (map_pos > 0 && pos < my_pool->pool_size / DATA_SIZE) {
		markMap(map_pos, lenght, 'F');
	}
	else {
		res = -2;
	}

	return res;
}

int getPos(void * ptr) {

	int n = my_pool->pool_size;
	int first = 0;
	int last = n - 1;
	int middle = (first + last) / 2;

	while (first <= last) {
		if (&my_pool->_pool[middle] < (void *)ptr)
			first = middle + 1;
		else if (&my_pool->_pool[middle] == (void *)ptr) {
			printf("%d found at location %d.\n", ptr, middle);
			break;
		}
		else
			last = middle - 1;

		middle = (first + last) / 2;
	}
	if (first > last) {
		printf("Not found! %d is not present in the list.\n", ptr);
		middle = -1;
	}


	int res = middle;
}

/* Dump memory pool */
void DumpDetailedPool() {
	//Print header
	OWN_LOG("============== Dumping Memory pool ================");
	OWN_LOG("POSITION           MEMORY DATA                MAP  ");

	//Print 
	DumpPool();

	//Print extra info
	OWN_LOG("Map size:                      %d", my_pool->pool_size / DATA_SIZE);
	OWN_LOG("Free Memory elements:          %d", my_pool->free_memory / DATA_SIZE);
	OWN_LOG("Pool size (Bytes):             %d", my_pool->pool_size);
	OWN_LOG("Free Bytes:                    %d", my_pool->free_memory);
	OWN_LOG("Single element size (Bytes):   %d", DATA_SIZE);
	OWN_LOG("============ End Dumping Memory pool ==============");
}

/* Dump memory pool */
void DumpPool() {
	char to_print[100];
	int i = 0;

	int map_index = 0;
	for (i = 0; i < my_pool->pool_size;) {

		//Print Memory direction
		int j = 11;
		int space = -1;
		sprintf_s(to_print, 100, "%08d   ", i);

		//Print Memory data
		for (; j < 40 && i < my_pool->pool_size; ++j, ++i) {
			if (++space == 4) {
				to_print[j] = ' ';
				++j;
				space = 0;
			}
			if (my_pool->_pool[i] == '\0')
				to_print[j] = '¬';
			else
				to_print[j] = my_pool->_pool[i];
		}

		--j;
		for (; j < 45;)
			to_print[++j] = ' ';

		//Print Memory map
		j = 45;
		for (; j < 51 && map_index < my_pool->pool_size / DATA_SIZE; ++j, ++map_index) {
			to_print[j] = my_pool->_map[map_index];
		}

		to_print[j] = '\0';
		OWN_LOG(to_print);
	}
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
	return (my_pool->_map[pos] == '1');
}


