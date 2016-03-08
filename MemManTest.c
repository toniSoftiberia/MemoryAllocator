#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testFramework.h"
#include "MemManTest.h"
#include "MemMan.h"
#include <time.h>

//TS: Test start
//TE: Test end

char** charArray;
char* new_pos_test;
int kB_of_memory = 1;

void setupMem()
{
	OWN_LOG("TS============= Setup memory manager ===============");

	if (initializePool(1024 * kB_of_memory)) {
#ifdef TEST1
		charArray = (char **)_malloc(sizeof(char *) * 10);
#endif // TEST1
#ifdef TEST2
		charArray* = (char **)malloc(sizeof(char *) * 10);
#endif // TEST2
		srand((unsigned int)time(NULL));
		testShowState();
	} else {
		TESTFAILED("Cannot start Memory Manager, cannot reserve memory");
	}

	OWN_LOG("TE==================================================");
};

void teardownMem()
{
	OWN_LOG("TS=========== Tear down memory manager =============");
	OWN_LOG("Free all memory");
	
	//Mark all mapa as free
	int res = initMap();
	if (res == 0) {
		OWN_LOG("All memory freed");
	}
	else
		OWN_LOG("Memory not freed correctly");
		
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

int testAllocateNewElems()
{
	OWN_LOG("TS========== Allocating new elements ==============");
	int res = 0;

	int i = 0;
	for (; i < 8; ++i) {
		OWN_LOG("Allocate new element");

#ifdef TEST1
		charArray[i] = (char *)_malloc(sizeof(char) * 4);
#endif // TEST1
#ifdef TEST2
		charArray[i] = (char *)malloc(sizeof(char) * 4);
#endif // TEST2

		if (charArray[i] != NULL) {
			strcpy(charArray[i], "Try");
			res = 1;
		}
		else {
			TESTFAILED("Cannot reserve memory");
		}

	}


	for (; i < 10; ++i) {
		int num_elements = (rand() % getFreeMemoryBlocks() + 1);
		if (num_elements > 1040)
			num_elements = 1040;

		OWN_LOG("Allocate new element[%d]", num_elements / DATA_SIZE);
		int res = 0;

#ifdef TEST1
		charArray[i] = (char *)_malloc(sizeof(char) * num_elements);
#endif // TEST1
#ifdef TEST2
		charArray[i] = (char *)malloc(sizeof(char) * num_elements);
#endif // TEST2

		if (charArray[i] != NULL) {
			strncpy(charArray[i],
				"En un lugar de la Mancha, de cuyo nombre no quiero acordarme,  no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor. Una olla de algo más vaca que carnero, salpicón las más noches, duelos y quebrantos los sábados, lentejas los viernes, algún palomino de añadidura los domingos, consumían las tres partes de su hacienda. El resto della concluían sayo de velarte, calzas de velludo para las fiestas con sus pantuflos de lo mismo, los días de entre semana se honraba con su vellori de lo más fino. Tenía en su casa una ama que pasaba de los cuarenta, y una sobrina que no llegaba a los veinte, y un mozo de campo y plaza, que así ensillaba el rocín como tomaba la podadera. Frisaba la edad de nuestro hidalgo con los cincuenta años, era de complexión recia, seco de carnes, enjuto de rostro; gran madrugador y amigo de la caza. Quieren decir que tenía el sobrenombre de Quijada o Quesada (que en esto hay alguna diferencia en los autores que deste caso escriben), aunque por conjeturas verosímiles se deja entender que se llama Quijana; pero esto importa poco a nuestro cuento; basta que en la narración dél no se salga un punto de la verdad....",
				num_elements);
			charArray[i][num_elements - 1] = '\0';
			res = 1;
		}
		else {
			OWN_LOG("Cannot reserve %d consecutive positions of memory", num_elements);
		}
		//DumpPool();

	}
	OWN_LOG("TE==================================================");
	return res;
};

int testFreeNewElems()
{
	OWN_LOG("TS=========== Releasing new elements ===============");
	int res = 0;

	int i = 0;
	for (; i < 10; ++i) {
		OWN_LOG("Releasing element %d", i);
#ifdef TEST1
		_free(charArray[i]);
#endif // TEST1
#ifdef TEST2
		free(charArray[i]);
#endif // TEST2
	}
	OWN_LOG("TE==================================================");
	return res;
};

UNITTEST memManTests[] = { &testAllocateNewElems,
&testFreeNewElems,
//&testShowState,
0 };
UNITTESTSUITE memManSuite = { &setupMem, &teardownMem, memManTests };