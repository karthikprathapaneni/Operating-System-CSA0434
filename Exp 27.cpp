#include <stdio.h>
#include <windows.h>

int main() {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // List all files in the current directory
    hFind = FindFirstFile("*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Error opening directory.\n");
        return 1;
    }

    printf("Listing files (ls simulation):\n\n");

    do {
        printf("%s\n", findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);

    return 0;
}
