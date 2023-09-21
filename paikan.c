#include "paikan.h"

// PIMAGE_IMPORT_DESCRIPTOR is a pointer to a IMAGE_IMPORT_DESCRIPTOR
// This structure describes the data directories used in PE file format
// It provides information about the imported functions from DLLs 
PIMAGE_IMPORT_DESCRIPTOR LocateIAT(HMODULE hModule){
    if(!hModule){
        printf("Failed to get module handle.\n");
        return NULL;
    }
    // Getting the DOS Header
    PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hModule;
    // Getting the NT Headers
    PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)((BYTE*)hModule + pDOSHeader->e_lfanew);
    // Checking the NT Headers signature
    // IMAGE_NT_SIGNATURE is a constant used to verify the validity 
    // of a NT Headers signature 
    if(pNTHeaders->Signature != IMAGE_NT_SIGNATURE){
        return NULL;
    }
    DWORD importDirRVA = pNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
    if(!importDirRVA){
        return NULL;
    } 
    return (PIMAGE_IMPORT_DESCRIPTOR)((BYTE*)hModule + importDirRVA);
}

int main(){
    HMODULE hModule = LoadLibrary(TEXT("user32.dll"));
    PIMAGE_IMPORT_DESCRIPTOR pIAT = LocateIAT(hModule);
    FreeLibrary(hModule);
    if(pIAT){
        printf("IAT located at: %p\n", pIAT);
    }else{
        printf("Failed to locate the IAT.\n");
    }
    return 0;
}