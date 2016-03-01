#include <stdio.h>
#include <stdlib.h>
#include "Globals.h"
#include "log.h"

/* include the unit test .h files here */
#include "MemManTest.h"

int main(int argc, char**argv)
{
	int res = 2;
	DWORD count = GetTickCount();
	OWN_LOG("TEST BEGIN");

	/* call each unit test suite here */
	if (callTestSuite(memManSuite))
		res =  0;

	OWN_LOG("TEST END in %d ms\n", GetTickCount() - count);
	return res;
};