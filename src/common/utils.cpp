#include <windows.h>
#include <stdio.h>

#include "common/utils.h"


//-------
/// Log
//-------


BOOL _logging = TRUE;

FILE *logfile = NULL;


static void open_logfile()
{
	if (!logfile)
	{
		// fopen_s(&logfile, "log.txt", "w");
		AllocConsole();
		FILE* pCout;
		freopen_s(&pCout, "CONOUT$", "wb", stdout);
		logfile = stdout;
	}
}


static void print(char* string)
{
	if (_logging)
	{
		open_logfile();
		fprintf(logfile, string);
		fflush(logfile);
	}
}


static void vprint(char* format, va_list arguments)
{
	if (_logging)
	{
		open_logfile();
		vfprintf(logfile, format, arguments);
		fflush(logfile);
	}
}


void printlog(char* format, ...)
{
	va_list arguments;

	va_start(arguments, format);
	vprint(format, arguments);
	print("\n");
	va_end(arguments);
}


void printerror(char* format, ...)
{
	va_list arguments;

	va_start(arguments, format);
	print("***** ");
	vprint(format, arguments);
	print(" *****\n");
	va_end(arguments);
}


void printexit(char* format, ...)
{
	va_list arguments;

	va_start(arguments, format);
	print("***** ");
	vprint(format, arguments);
	print(" *****\n");
	va_end(arguments);
	
	exit(EXIT_FAILURE);
}
