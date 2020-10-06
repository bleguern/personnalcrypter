#ifndef FILE_H_
#define FILE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ERROR                                      0
#define FILE_OK                                         1
#define FILE_NOT_FOUND_OR_OPENING_ERROR                 2
#define BAD_CRYPTED_FILE_FORMAT                         3
#define FILE_CRYPT_ERROR                                4
#define FILE_UNCRYPT_ERROR                              5
#define FILE_OPENNING_ERROR                             6
#define FILE_SAVING_ERROR                               7


class File
{
	FILE *input_fd;
	FILE *output_fd;
	char *input_path;
	char *output_path;

public:
	File():input_fd(NULL),output_fd(NULL),input_path(NULL),output_path(NULL) {}
	File(char* file_path):input_fd(NULL),output_fd(NULL),input_path(NULL),output_path(NULL)
	{
		input_path = (char*)malloc(strlen(file_path)-4);
		strcpy(input_path, file_path);
	}
	~File() {}

	int Crypt();
	int Uncrypt();
};


#endif