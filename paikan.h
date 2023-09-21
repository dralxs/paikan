#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

PIMAGE_IMPORT_DESCRIPTOR LocateIAT(HMODULE hModule);
void ReplaceFunctionAddress(HMODULE hModule, const char* functionName);

