#pragma once

#include "testFramework.h"

extern void setupMem();
extern void teardownMem();
extern int testAllocateNewElement();
extern int testAllocateNElements();
extern int testFreePosition();
extern int testFreeRange();
extern int testShowState();

extern UNITTEST memManTests[];
extern UNITTESTSUITE memManSuite;