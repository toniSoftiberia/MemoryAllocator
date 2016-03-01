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
	inicializePool(1024);
	srand(time(NULL));
	OWN_LOG("TE==================================================");
	return;
};

void teardownMem()
{
	OWN_LOG("TS=========== Tear down memory manager =============");
	OWN_LOG("Free all memory");
	for (int i = 0; i < my_pool->pool_size / DATA_SIZE; ++i)
		_free(i, 1);
	deletePool();
	OWN_LOG("TE==================================================");
	return;
};

void testShowState()
{
	OWN_LOG("TS================ Printing state ==================");
	//printPool();
	//printMap();
	DumpDetailedPool();
	OWN_LOG("TE==================================================");
};

void testDeletePool() {
	OWN_LOG("TS================ Deleting pool ===================");
	deletePool();
	OWN_LOG("TE==================================================");
}

int testAllocateNewElement()
{
	OWN_LOG("TS============= Allocate new element ===============");
	int res = 0;
	int new_pos = _malloc(1);
	if (new_pos > 0) {
		setInfo("TestMem", new_pos, 1);
		res = 1;
	}
	else {
		TESTFAILED("Cannot reserve memory");
	}
	//printMap();
	DumpPool();

	OWN_LOG("TE==================================================");
	return res;
};

int testAllocateNElements()
{
	int num_elements = rand() % my_pool->pool_size + 1;
	num_elements /= DATA_SIZE;
	OWN_LOG("TS========== Allocate new elements[%d] =============", num_elements);
	int res = 0;
	int new_pos = _malloc(num_elements);
	if (new_pos > 0) {
		setInfo("En un lugar de la Mancha, de cuyo nombre no quiero acordarme,  no ha mucho tiempo que viv�a un hidalgo de los de lanza en astillero, adarga antigua, roc�n flaco y galgo corredor. Una olla de algo m�s vaca que carnero, salpic�n las m�s noches, duelos y quebrantos los s�bados, lentejas los viernes, alg�n palomino de a�adidura los domingos, consum�an las tres partes de su hacienda. El resto della conclu�an sayo de velarte, calzas de velludo para las fiestas con sus pantuflos de lo mismo, los d�as de entre semana se honraba con su vellori de lo m�s fino. Ten�a en su casa una ama que pasaba de los cuarenta, y una sobrina que no llegaba a los veinte, y un mozo de campo y plaza, que as� ensillaba el roc�n como tomaba la podadera. Frisaba la edad de nuestro hidalgo con los cincuenta a�os, era de complexi�n recia, seco de carnes, enjuto de rostro; gran madrugador y amigo de la caza. Quieren decir que ten�a el sobrenombre de Quijada o Quesada (que en esto hay alguna diferencia en los autores que deste caso escriben), aunque por conjeturas veros�miles se deja entender que se llama Quijana; pero esto importa poco a nuestro cuento; basta que en la narraci�n d�l no se salga un punto de la verdad....", new_pos, num_elements);
		res = 1;
	}
	else {
		OWN_LOG("Cannot reserve %d consecutive positions of memory", num_elements);
	}
	//printMap();
	DumpPool();

	OWN_LOG("TE==================================================");
	return res;
};

int testFillAllMemory()
{
	int res = 1;
	OWN_LOG("TS======= Allocate all elements to the end =========");
	int free_postions = my_pool->free_memory / DATA_SIZE;
	for (int i = 0; i < free_postions; ++i) {
		int new_pos = _malloc(1);
		if (new_pos > 0) {
			setInfo("TestMem", new_pos, 1);
			res &= 1;
		}
		else {
			TESTFAILED("Cannot reserve %d position of memory", i);
		}
	}
	//printMap();
	DumpPool();

	OWN_LOG("TE==================================================");
	return res;
};

void testFreePosition()
{
	int position = rand() % my_pool->pool_size + 1;
	position /= DATA_SIZE;
	OWN_LOG("TS============== Free position %d ==================", position);
	_free(position, 1);
	//printMap();
	DumpPool();

	OWN_LOG("TE==================================================");
};

void testFreeRange()
{
	int start = rand() % my_pool->pool_size + 1;
	start /= DATA_SIZE;
	int large = rand() % my_pool->pool_size + 1;
	large /= DATA_SIZE;
	OWN_LOG("TS======== Free positions from %d to %d ============", start, start + large);
	for (int i = start; i < start+ large; ++i) {
		_free(i, 1);
	}
	//printMap();
	DumpPool();

	OWN_LOG("TE==================================================");
};

void testFreeAllMemory()
{
	OWN_LOG("TS============ Free all memory =====================");
	for (int i = 0; i < my_pool->pool_size / DATA_SIZE; ++i) {
		_free(i, 1);
	}
	OWN_LOG("TE==================================================");
};

/* add each additional unit test to this array */
//UNITTEST memManTests[] = { &testShowState, &testAllocateNewElement, &testAllocateNElements, &testFillAllMemory, &testFreePosition, &testFreeRange, &testShowState, 0 };
UNITTEST memManTests[] = { &testShowState, &testAllocateNewElement, &testAllocateNElements, &testFreePosition, &testFreeRange, &testShowState, 0 };
UNITTESTSUITE memManSuite = { &setupMem, &teardownMem, memManTests };