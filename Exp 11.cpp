#include <stdio.h>
#include <windows.h>

// Thread function
DWORD WINAPI threadFunction(LPVOID param) {
    int threadID = *(int*)param;

    for (int i = 1; i <= 5; i++) {
        printf("Thread %d is running... step %d\n", threadID, i);
        Sleep(500); // sleep for 0.5 seconds
    }

    return 0;
}

int main() {
    HANDLE threads[3];
    int threadIDs[3];

    printf("Multithreading Example in C (Windows)\n");

    // Create 3 threads
    for (int i = 0; i < 3; i++) {
        threadIDs[i] = i + 1;
        threads[i] = CreateThread(
            NULL,               // default security
            0,                  // default stack size
            threadFunction,     // thread task
            &threadIDs[i],      // parameters
            0,                  // default flags
            NULL                // thread ID
        );

        if (threads[i] == NULL) {
            printf("Failed to create thread %d\n", i+1);
            return 1;
        }
    }

    // Wait for all threads to finish
    WaitForMultipleObjects(3, threads, TRUE, INFINITE);

    printf("All threads have completed execution.\n");

    return 0;
}
