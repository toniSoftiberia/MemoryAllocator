#pragma once

#include "testFramework.h"

#define TEST1
//#define TEST2

extern void setupMem();
extern void teardownMem();
extern int testAllocateDataOnStart();
extern int testAllocateDataOnMiddle();
extern int testAllocateDataOnEnd();
extern int testFreeNewElems();
extern int testShowState();
extern void testNewSingle(int pos);
extern void testNewArray(int pos);

extern UNITTEST memManTests[];
extern UNITTESTSUITE memManSuite;