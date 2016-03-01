#include <stdlib.h>
#include <stdio.h>
#include "log.h"

int log_created = 0;

void log(const char file[], int line, const char* format, ...)
{
	FILE *w_file;
	static char tmp_string[4096];
	static char tmp_string2[4096];


	if (!log_created) {
		w_file = fopen(LOGFILE, "w");
		log_created = 1;
	}
	else
		w_file = fopen(LOGFILE, "a");

	if (w_file == NULL) {
		if (log_created)
			log_created = 0;
		return;
	}
	else
	{
		static va_list  ap;

		// Construct the string from variable arguments
		va_start(ap, format);
		vsprintf_s(tmp_string, 4096, format, ap);
		va_end(ap);
		sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);
		OutputDebugString((LPCWSTR)tmp_string2);
		fputs(tmp_string2, w_file);
		fclose(w_file);
	}

	if (w_file)
		fclose(w_file);
}