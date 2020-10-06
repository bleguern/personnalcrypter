#include "File.h"


int File::Crypt()
{
	if(NULL == (input_fd = fopen(input_path, "r")))
		return FILE_NOT_FOUND_OR_OPENING_ERROR;

	if(NULL == (output_path = (char*)malloc(strlen(input_path)-4)))
		return FILE_UNCRYPT_ERROR;

	strcpy(output_path, input_path);
	strcat(output_path, "-crypted.pc1");

	if(NULL == (output_fd = fopen(output_path, "w")))
		return FILE_NOT_FOUND_OR_OPENING_ERROR;

	fclose(input_fd);
	fclose(output_fd);

	return FILE_OK;
}




int File::Uncrypt()
{
	if(NULL == (input_fd = fopen(input_path, "r")))
		return FILE_NOT_FOUND_OR_OPENING_ERROR;

	if(NULL == (output_path = (char*)malloc(strlen(input_path)-4)))
		return FILE_UNCRYPT_ERROR;

	strcpy(output_path, input_path);
	strcat(output_path, "-uncrypted.pc1");



	if(NULL == (output_fd = fopen(output_path, "w")))
		return FILE_NOT_FOUND_OR_OPENING_ERROR;

	fclose(input_fd);
	fclose(output_fd);

	return FILE_OK;
}