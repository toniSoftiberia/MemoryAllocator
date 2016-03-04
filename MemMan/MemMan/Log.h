#pragma once

#include <windows.h>
#include <stdio.h>
#include "Globals.h"
#include <stdlib.h>
#include "MemManTest.h"

// output file
#ifdef TEST1
#define LOGFILE	"log_MemMan_custom.log"   
#endif // TEST1
#ifdef TEST2
#define LOGFILE	"log_MemMan_original.log"   
#endif // TEST2

// keeps track whether the log file is created or not
extern int log_created;      

void log(const char file[], int line, const char* format, ...);