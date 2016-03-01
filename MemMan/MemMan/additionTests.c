/*
#include <stdio.h>
#include <stdlib.h>

#include "testFramework.h"
#include "addition.h"

void setupAdd()
{
	return;
};

void teardownAdd()
{
	return;
};

int testAddPositives()
{
	int x = 2, y = 3;
	int expected = 5;
	int actual;

	actual = add(x, y);
	if (actual != expected)
	{
		TESTFAILED("actual not equal expected");
		return 0;
	}
	return 1;
};

int testAddFaultyTest()
{
	int x = 2, y = 2;
	int expected = 5;
	int actual;

	actual = add(x, y);
	if (actual != expected)
	{
		TESTFAILED("actual not equal expected");
		return 0;
	}
	return 1;
};

int testAddNegatives()
{
	int x = -2, y = -3;
	int expected = -5;
	int actual;

	actual = add(x, y);
	if (actual != expected)
	{
		TESTFAILED("actual not equal expected");
		return 0;
	}
	return 1;
};

int testAddMixed()
{
	int x = 2, y = -3;
	int expected = -1;
	int actual;

	actual = add(x, y);
	if (actual != expected)
	{
		TESTFAILED("actual not equal expected");
		return 0;
	}
	return 1;
};

int testAddZeroes()
{
	int x = 0, y = 0;
	int expected = 0;
	int actual;

	actual = add(x, y);
	if (actual != expected)
	{
		TESTFAILED("actual not equal expected");
		return 0;
	}
	return 1;
};

// add each additional unit test to this array 
UNITTEST additionTests[] = { &testAddPositives, &testAddFaultyTest, &testAddNegatives, &testAddMixed, &testAddZeroes, 0 };
UNITTESTSUITE additionSuite = { &setupAdd, &teardownAdd, additionTests };

*/