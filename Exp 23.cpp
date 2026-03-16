#include <stdio.h>

int main() {
    int blockSize[20], processSize[20];
    int blockCount, processCount;
    int allocation[20];

    // Input number of memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &blockCount);

    printf("Enter size of each block:\n");
    for (int i = 0; i < blockCount; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input number of processes
    printf("\nEnter number of processes: ");
    scanf("%d", &processCount);

    printf("Enter size of each process:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1;  // Initially no process is allocated
    }

    // First Fit Allocation
    for (int i = 0; i < processCount; i++) {
        for (int j = 0; j < blockCount; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;           // allocate block j to process i
                blockSize[j] -= processSize[i];  // reduce block size
                break;                       // move to next process
            }
        }
    }

    // Output Allocation
    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (int i = 0; i < processCount; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
