#ifndef _PERSONNALCRYPTER_H_
#define _PERSONNALCRYPTER_H_

#include <windows.h>
#include "resource.h"
#include "File.h"



#define MAX_CHARS                  256


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void FillOpenParams(OPENFILENAME&, HWND, char*);



#endif