#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    const char* message = "Hello from Shared Memory IPC (Windows)!";

    // Create a shared memory block
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use system paging file
        NULL,                   // Default security
        PAGE_READWRITE,         // Read/write access
        0,                      // Maximum object size (high-order DWORD)
        1024,                   // Maximum object size (low-order DWORD)
        "MySharedMemory"        // Name of mapping object
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map the shared memory to our process space
    pBuf = (LPTSTR) MapViewOfFile(
        hMapFile,               // Handle to map object
        FILE_MAP_ALL_ACCESS,    // Read/write permission
        0,
        0,
        1024
    );

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data to shared memory
    sprintf((char*)pBuf, "%s", message);

    printf("Data written to shared memory:\n%s\n", (char*)pBuf);

    printf("\nPress Enter to simulate another process reading...");
    getchar();

    // Read from shared memory (same program simulating second process)
    printf("\nProcess 2 Reading:\n%s\n", (char*)pBuf);

    // Cleanup
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
