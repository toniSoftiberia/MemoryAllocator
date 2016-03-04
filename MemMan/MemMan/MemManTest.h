#pragma once

#include "testFramework.h"

extern void setupMem();
extern void teardownMem();
extern int testAllocateNewElems();
extern int testFreeNewElems();
extern int testFreeRange();
extern int testShowState();

extern UNITTEST memManTests[];
extern UNITTESTSUITE memManSuite;