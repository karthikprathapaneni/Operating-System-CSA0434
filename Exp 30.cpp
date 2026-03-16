#include <stdio.h>
#include <windows.h>

DWORD WINAPI thread_function(LPVOID param)
{
    printf("Thread started. Thread ID: %lu\n", GetCurrentThreadId());
    return 0;   // Equivalent to pthread_exit()
}

int main()
{
    HANDLE t1, t2;
    DWORD id1, id2;

    // (i) CREATE threads
    t1 = CreateThread(NULL, 0, thread_function, NULL, 0, &id1);
    t2 = CreateThread(NULL, 0, thread_function, NULL, 0, &id2);

    if (!t1 || !t2)
    {
        printf("Error creating threads.\n");
        return 1;
    }

    // (iii) EQUAL - compare thread IDs
    if (id1 == id2)
        printf("Threads are equal.\n");
    else
        printf("Threads are NOT equal.\n");

    // (ii) JOIN threads (Wait for finishing)
    WaitForSingleObject(t1, INFINITE);
    WaitForSingleObject(t2, INFINITE);

    printf("Threads finished execution.\n");

    // Close thread handles
    CloseHandle(t1);
    CloseHandle(t2);

    printf("Main program finished.\n");

    return 0;
}
