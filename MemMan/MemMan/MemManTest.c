#include <stdio.h>
#include <stdlib.h>

#include "testFramework.h"
#include "MemManTest.h"
#include "MemMan.h"
#include <time.h>

//TS: Test start
//TE: Test end

void setupMem()
{
	OWN_LOG("TS============= Setup memory manager ===============");
	if (initializePool(1024)) {
		srand((unsigned int)time(NULL));
		testShowState();
	}
	else {
		TESTFAILED("Cannot start Memory Manager, cannot reserve memory");
	}

	OWN_LOG("TE==================================================");
};

void teardownMem()
{
	OWN_LOG("TS=========== Tear down memory manager =============");
	OWN_LOG("Free all memory");
	for (int i = 0; i < my_pool->pool_size / DATA_SIZE; ++i) {
		int res = _free(i, 1);
		switch (res) {
		case -1:
			OWN_LOG("You cannot delete the position 0 it is reserved");
			break;
		case -2:
			OWN_LOG("OUT OF RANGE: %d", i);
			break;
		//default:
			//OWN_LOG("Deleting position %d", i);
		}
	}
	testShowState();
	deletePool();
	OWN_LOG("TE==================================================");
	return;
};

int testShowState()
{
	OWN_LOG("TS================ Printing state ==================");
	DumpDetailedPool();
	OWN_LOG("TE==================================================");
	return 1;
};

int testAllocateNewElement()
{
	OWN_LOG("TS============= Allocate new element ===============");
	int res = 0;
	char* new_pos = (char *)_malloc(sizeof(char) * 4);
	//char* new_pos2 = (char *)malloc(sizeof(char) * 4);
	//if (new_pos != NULL && new_pos2 != NULL) {
	if (new_pos != NULL) {
		strcpy(new_pos, "Try");
		//new_pos2 = "Try";
		res = 1;
	}
	else {
		TESTFAILED("Cannot reserve memory");
	}
	//OWN_LOG("new_pos:  %s", new_pos);
	//OWN_LOG("new_pos2: %s", new_pos2);

	DumpPool();


	OWN_LOG("TE==================================================");
	return res;
};

int testAllocateNElements()
{
	const int num_elements = (rand() % my_pool->pool_size / DATA_SIZE + 1) ;
	OWN_LOG("TS========== Allocate new elements[%d] =============", num_elements);
	int res = 0;
	char* new_pos = (char *)_malloc(sizeof(char) * num_elements);
	if (new_pos != NULL) {
		strncpy(new_pos, 
			"En un lugar de la Mancha, de cuyo nombre no quiero acordarme,  no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor. Una olla de algo más vaca que carnero, salpicón las más noches, duelos y quebrantos los sábados, lentejas los viernes, algún palomino de añadidura los domingos, consumían las tres partes de su hacienda. El resto della concluían sayo de velarte, calzas de velludo para las fiestas con sus pantuflos de lo mismo, los días de entre semana se honraba con su vellori de lo más fino. Tenía en su casa una ama que pasaba de los cuarenta, y una sobrina que no llegaba a los veinte, y un mozo de campo y plaza, que así ensillaba el rocín como tomaba la podadera. Frisaba la edad de nuestro hidalgo con los cincuenta años, era de complexión recia, seco de carnes, enjuto de rostro; gran madrugador y amigo de la caza. Quieren decir que tenía el sobrenombre de Quijada o Quesada (que en esto hay alguna diferencia en los autores que deste caso escriben), aunque por conjeturas verosímiles se deja entender que se llama Quijana; pero esto importa poco a nuestro cuento; basta que en la narración dél no se salga un punto de la verdad....",
			num_elements);
		new_pos[num_elements - 1] = '\0';
		res = 1;
	}
	else {
		OWN_LOG("Cannot reserve %d consecutive positions of memory", num_elements);
	}
	DumpPool();

	OWN_LOG("TE==================================================");
	return res;
};

int testFreePosition()
{
	int position = (rand() % my_pool->pool_size + 1) / DATA_SIZE;
	OWN_LOG("TS============== Free position %d ==================", position);
	int res = _free(position, 1);
	switch (res) {
	case -1:
		OWN_LOG("You cannot delete the position 0 it is reserved");
		break;
	case -2:
		OWN_LOG("OUT OF RANGE: %d", position);
		break;
	default:
		//OWN_LOG("Deleting position %d", i);
		break;
	}
	DumpPool();
	OWN_LOG("TE==================================================");
	return 1;
};

int testFreeRange()
{
	int start = rand() % my_pool->pool_size + 1;
	start /= DATA_SIZE;
	int large = rand() % my_pool->pool_size + 1;
	large /= DATA_SIZE;
	OWN_LOG("TS======== Free positions from %d to %d ============", start, start + large);
	for (int i = start; i < start+ large; ++i) {
		int res = _free(i, 1);
		switch (res) {
		case -1:
			OWN_LOG("You cannot delete the position 0 it is reserved");
			break;
		case -2:
			OWN_LOG("OUT OF RANGE: %d", i);
			break;
		default:
			//OWN_LOG("Deleting position %d", i);
			break;
		}
	}
	//printMap();
	DumpPool();

	OWN_LOG("TE==================================================");
	return 1;
};

/* add each additional unit test to this array */
//UNITTEST memManTests[] = { &testShowState, &testAllocateNewElement, &testAllocateNElements, &testFillAllMemory, &testFreePosition, &testFreeRange, &testShowState, 0 };
//UNITTEST memManTests[] = { &testAllocateNewElement, &testAllocateNElements, &testFreePosition, &testFreeRange, 0 }; 
UNITTEST memManTests[] = { &testAllocateNewElement,
&testAllocateNElements,
&testFreePosition,
//&testFreeRange,
0 };
UNITTESTSUITE memManSuite = { &setupMem, &teardownMem, memManTests };