#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;
    const char* message = "Hello from Windows Message Queue IPC!";

    // Create a shared memory block
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // Use system paging file
        NULL,                   // Default security
        PAGE_READWRITE,         // Read/write access
        0,
        1024,                   // Size in bytes
        "MyMessageQueue"        // Name of shared memory
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map memory to our process address space
    pBuf = (LPTSTR) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (pBuf == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write a message
    sprintf((char*)pBuf, "%s", message);
    printf("Message sent: %s\n", (char*)pBuf);

    printf("\nSender finished. Press Enter to exit...");
    getchar();

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
