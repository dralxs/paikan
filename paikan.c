#include "paikan.h"

typedef BOOL (WINAPI *PrototypeShowWindow)(HWND hWnd, int nCmdShow);
PrototypeShowWindow originalShowWindow = &ShowWindow;

BOOL ShowWindowHook(HWND hWnd, int nCmdShow){
    printf("exploit");
    return originalShowWindow(hWnd, nCmdShow);
}

// Replace the function address with the hook
void ReplaceFunctionAddress(HMODULE hModule, const char* functionName){
    PIMAGE_IMPORT_DESCRIPTOR pIAT = LocateIAT(hModule);
    if(!pIAT){
        printf("error");
    }
    // The loop continue as long as there is a valid dll name
    while(pIAT->Name){
        // Get the structure THUNK which contain information about the function
        PIMAGE_THUNK_DATA thunk = (PIMAGE_THUNK_DATA)((BYTE*)hModule + pIAT->OriginalFirstThunk);
        PIMAGE_THUNK_DATA funcThunk = (PIMAGE_THUNK_DATA)((BYTE*)hModule + pIAT->FirstThunk);
        // The loop continue as lonn as there is a valid address of the function 
        while(thunk->u1.AddressOfData){
            PIMAGE_IMPORT_BY_NAME pName = (PIMAGE_IMPORT_BY_NAME)((BYTE*)hModule + thunk->u1.AddressOfData);
            if(strcmp(pName->Name, functionName) == 0){
                DWORD oldProtect = 0;
                VirtualProtect((LPVOID)(&funcThunk->u1.Function), 8, PAGE_READWRITE, &oldProtect);
                funcThunk->u1.Function = (DWORD_PTR)ShowWindowHook;
            }
            thunk++;
            funcThunk++;
            printf("%s\n", pName->Name);
        }
        pIAT++;
        printf("%lu\n", thunk->u1.Function);
    }
}

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
    GetFunctionAddress(hModule, "NtUserShowWindow");
    // Fake window
    HWND hwnd = GetConsoleWindow();
    // Testing the hook 
    ShowWindow(hwnd, SW_HIDE);
    FreeLibrary(hModule);
    if(pIAT){
        printf("IAT located at: %p\n", pIAT);
    }else{
        printf("Failed to locate the IAT.\n");
    }
    return 0;
}