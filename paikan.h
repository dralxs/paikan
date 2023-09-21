#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

PIMAGE_IMPORT_DESCRIPTOR LocateIAT(HMODULE hModule);
PIMAGE_IMPORT_DESCRIPTOR getFunctionAddress(HMODULE hModule, const char* functionName);

