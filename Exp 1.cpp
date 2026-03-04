#include <stdio.h>
#include <windows.h>

int main() {

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Print the current process ID (Parent)
    printf("Parent Process:\n");
    printf("PID = %lu\n", GetCurrentProcessId());

    // Create a child process (new program instance)
    if (!CreateProcess(
            NULL,
            "notepad.exe",    // Child process
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {

        printf("Process creation failed! Error: %lu\n", GetLastError());
        return 1;
    }

    // Print child process ID
    printf("\nChild Process:\n");
    printf("PID = %lu\n", pi.dwProcessId);
    printf("PPID cannot be directly obtained in Windows.\n");

    // Close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
