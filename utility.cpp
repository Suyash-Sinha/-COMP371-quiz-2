#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>
#include <string>

#include "utility.hpp"

// A function that terminates the program if its condition is false.
void assertFatal(bool condition, char const* format, ...) {
	if (condition == true) return;
	va_list arguments;
	va_start(arguments, format);
	vprintf(format, arguments);
	va_end(arguments);
	exit(EXIT_FAILURE);
}
// A function that reads a file C-style.
char* readFile(char const* path) {
	printf("Reading file %s\n", path);
	FILE* file;
	fopen_s(&file, path, "r");
	assertFatal(file != NULL, "Could not open file (%s)\n", path);
	struct stat fileInfo;
	assertFatal(fstat(_fileno(file), &fileInfo) != -1, "Could not get file (%s) status\n", path);
	char* buffer = (char*)calloc(fileInfo.st_size + 1, sizeof * buffer);
	fread(buffer, sizeof * buffer, fileInfo.st_size, file);
	fclose(file);
	return buffer;
	return NULL;
}
