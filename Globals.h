#pragma once

#define OWN_LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

// Configuration -----------
#define DATA_SIZE 4
#define VSYNC true
#define TITLE "Simple Memory Manager by Toni Lopez (UPC Tech Talent MVJ)"

/*
void *malloc (size_t);
void *_malloc_leap (const char *file, int line, size_t size);
#define malloc(size) _malloc_leap(__FILE__, __LINE__, size)

void free (void *);
void _free_leap (const char *file, int line, void *);
#define free(ptr) _free_leap (__FILE__, __LINE__, ptr);
*/

#define TESTFAILED(X) testFailed(__FILE__, __LINE__, X)