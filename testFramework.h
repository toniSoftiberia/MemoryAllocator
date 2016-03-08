#pragma once

typedef struct
{
	int(*test)();
} UNITTEST;

typedef struct
{
	void(*setup)();
	void(*teardown)();
	UNITTEST *tests;
} UNITTESTSUITE;

extern int callTest(UNITTEST *test);
extern int callTestSuite(UNITTESTSUITE suite);
extern void testFailed(const char* testName, const int testLine, const char* message);