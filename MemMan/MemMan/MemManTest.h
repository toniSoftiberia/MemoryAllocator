#pragma once

#include "testFramework.h"

extern void setupMem();
extern void teardownMem();
extern int testAllocateNewElement();
extern int testAllocateNElements();
extern int testFillAllMemory();
extern void testFreePosition();
extern void testFreeRange();
extern void testFreeAllMemory();
extern void testShowState();

extern UNITTEST memManTests[];
extern UNITTESTSUITE memManSuite;