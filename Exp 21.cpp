#include <stdio.h>

int main()
{
    int blockSize[20], processSize[20], blockNo[20];
    int m, n, i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter size of each memory block:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter size of each process:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    // Initialize block numbers to -1 (unallocated)
    for (i = 0; i < n; i++)
        blockNo[i] = -1;

    // WORST FIT logic
    for (i = 0; i < n; i++) {
        int worstIndex = -1;

        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex])
                    worstIndex = j;
            }
        }

        if (worstIndex != -1) {
            blockNo[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    // Result Display
    printf("\nProcess No.\tProcess Size\tBlock Allocated\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);

        if (blockNo[i] != -1)
            printf("%d\n", blockNo[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
