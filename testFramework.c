#include <stdio.h>
#include <stdlib.h>
#include "testFramework.h"
#include "Globals.h"

#include "brofiler/Brofiler.h"

#pragma comment(lib, "brofiler/ProfilerCore32.lib")

int num_of_tests = 1000000;

int callTest(UNITTEST *test)
{
	return (*test).test();
};

int callTestSuite(UNITTESTSUITE suite)
{
	int rc = 1;
	UNITTEST* test = suite.tests;

	if (suite.setup)
		(suite.setup());

	for (int i = 0; i < num_of_tests; ++i){
		BROFILER_FRAME("Main");
		test = suite.tests;
		while (test->test != 0)
		{
			//BROFILER_FRAME("Test");
			if (callTest(test++))
			{
				printf(".");
			}
			else
			{
				printf("#");
				rc = 0;
			}
		}
	}

	if (suite.teardown)
		(suite.teardown());

	return rc;
}

void testFailed(const char* testName, const int testLine, const char* message)
{
	//fprintf(stderr, "%s(%i): ERROR test failed, %s\n", testName, testLine, message);
	//OWN_LOG("%s(%i): ERROR test failed, %s\n", testName, testLine, message);
};
