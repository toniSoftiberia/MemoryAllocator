#pragma once

#include "testFramework.h"

#define TEST1
//#define TEST2

extern void setupMem();
extern void teardownMem();
extern int testAllocateNewElems();
extern int testFreeNewElems();
extern int testShowState();

extern UNITTEST memManTests[];
extern UNITTESTSUITE memManSuite;