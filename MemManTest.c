#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testFramework.h"
#include "MemManTest.h"
#include "MemMan.h"
#include <time.h>

#include "brofiler/Brofiler.h"

//TS: Test start
//TE: Test end

char** charArray;
char* new_pos_test;
int kB_of_memory = 1;

void setupMem()
{
	printf("This program will start in 3");
	_sleep(1000);
	printf(" 2");
	_sleep(1000);
	printf(" 1");
	_sleep(1000);
	printf(" Go!");
	BROFILER_CATEGORY("Setup", Profiler::Color::Aqua)
	//OWN_LOG("TS============= Setup memory manager ===============");

	if (initializePool(1024 * kB_of_memory)) {
#ifdef TEST1
		charArray = (char **)_malloc(sizeof(char *) * 10);
#endif // TEST1
#ifdef TEST2
		charArray = (char **)malloc(sizeof(char *) * 10);
#endif // TEST2
		srand((unsigned int)time(NULL));
		testShowState();
	} else {
		TESTFAILED("Cannot start Memory Manager, cannot reserve memory");
	}

	//OWN_LOG("TE==================================================");
};

void teardownMem()
{
	BROFILER_CATEGORY("Tear Down", Profiler::Color::Brown)
	//OWN_LOG("TS=========== Tear down memory manager =============");
	//OWN_LOG("Free all memory");
	
	//Mark all mapa as free
	int res = initMap();
	/*if (res == 1) {
		OWN_LOG("All memory freed");
	}
	else
		OWN_LOG("Memory not freed correctly");*/

	testShowState();

	#ifdef TEST1
		_free(charArray);
		deletePool();
	#endif // TEST1
	#ifdef TEST2
		free(charArray);
	#endif // TEST2

	testShowState();
	//OWN_LOG("TE==================================================");
	return;
};

int testShowState()
{
	//OWN_LOG("TS================ Printing state ==================");

	DumpDetailedPool();

	//OWN_LOG("TE==================================================");
	return 1;
};

void testNewSingle(int pos)
{
	BROFILER_CATEGORY("New Single", Profiler::Color::Orange)

	#ifdef TEST1
		charArray[pos] = (char *)_malloc(sizeof(char) * 4);
	#endif // TEST1
	#ifdef TEST2
		charArray[i] = (char *)malloc(sizeof(char) * 4);
	#endif // TEST2

	if (charArray[pos] != NULL) {
		strcpy(charArray[pos], "Try");
	}
}


void testNewArray(int pos)
{
	BROFILER_CATEGORY("New Array", Profiler::Color::SkyBlue)
	int num_elements = 150;

	#ifdef TEST1
		charArray[pos] = (char *)_malloc(sizeof(char) * num_elements);
	#endif // TEST1
	#ifdef TEST2
		charArray[pos] = (char *)malloc(sizeof(char) * num_elements);
	#endif // TEST2

	if (charArray[pos] != NULL) {
		strncpy(charArray[pos],
			"En un lugar de la Mancha, de cuyo nombre no quiero acordarme,  no ha mucho tiempo que vivía un hidalgo de los de lanza en astillero, adarga antigua, rocín flaco y galgo corredor. Una olla de algo más vaca que carnero, salpicón las más noches, duelos y quebrantos los sábados, lentejas los viernes, algún palomino de añadidura los domingos, consumían las tres partes de su hacienda. El resto della concluían sayo de velarte, calzas de velludo para las fiestas con sus pantuflos de lo mismo, los días de entre semana se honraba con su vellori de lo más fino. Tenía en su casa una ama que pasaba de los cuarenta, y una sobrina que no llegaba a los veinte, y un mozo de campo y plaza, que así ensillaba el rocín como tomaba la podadera. Frisaba la edad de nuestro hidalgo con los cincuenta años, era de complexión recia, seco de carnes, enjuto de rostro; gran madrugador y amigo de la caza. Quieren decir que tenía el sobrenombre de Quijada o Quesada (que en esto hay alguna diferencia en los autores que deste caso escriben), aunque por conjeturas verosímiles se deja entender que se llama Quijana; pero esto importa poco a nuestro cuento; basta que en la narración dél no se salga un punto de la verdad....",
			num_elements);
		charArray[pos][num_elements - 1] = '\0';
	}
}

int testAllocateDataOnStart()
{
	//OWN_LOG("TS========== Allocating new elements ==============");
	int res = 1;

	int i = 0;
	for (; i < 2; ++i) 
		testNewArray(i);

	for (; i < 10; ++i)
		testNewSingle(i);

	//OWN_LOG("TE==================================================");
	return res;
};


int testAllocateDataOnMiddle()
{	
	//OWN_LOG("TS========== Allocating new elements ==============");
	int res = 1;

	int i = 0;
	for (; i < 4; ++i)
		testNewSingle(i);

	for (; i < 6; ++i)
		testNewArray(i);

	for (; i < 10; ++i)
		testNewSingle(i);

	//OWN_LOG("TE==================================================");
	return res;
};


int testAllocateDataOnEnd()
{
	//OWN_LOG("TS========== Allocating new elements ==============");
	int res = 1;

	int i = 0;
	for (; i < 8; ++i)
		testNewSingle(i);

	for (; i < 10; ++i)
		testNewArray(i);

	//OWN_LOG("TE==================================================");
	return res;
};

int testFreeNewElems()
{
	//OWN_LOG("TS=========== Releasing new elements ===============");
	int res = 0;

	int i = 0;
	for (; i < 10; ++i) {
		BROFILER_CATEGORY("Free Element", Profiler::Color::Yellow)
		//OWN_LOG("Releasing element %d", i);
		#ifdef TEST1
			_free(charArray[i]);
		#endif // TEST1
		#ifdef TEST2
			free(charArray[i]);
		#endif // TEST2
	}
	//OWN_LOG("TE==================================================");
	return res;
};

UNITTEST memManTests[] = {
&testAllocateDataOnStart, &testFreeNewElems,
//&testAllocateDataOnMiddle, &testFreeNewElems,
//&testAllocateDataOnEnd, &testFreeNewElems,
//&testShowState,
0 };
UNITTESTSUITE memManSuite = { &setupMem, &teardownMem, memManTests };