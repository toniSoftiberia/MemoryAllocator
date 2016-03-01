#pragma once

#include <windows.h>
#include <stdio.h>
#include "Globals.h"
#include <stdlib.h>

// output file
#define LOGFILE	"log_MemMan.log"   

// keeps track whether the log file is created or not
extern int log_created;      

void log(const char file[], int line, const char* format, ...);