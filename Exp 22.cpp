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

    // Initially no process is allocated (-1 = Not Allocated)
    for (i = 0; i < n; i++)
        blockNo[i] = -1;

    // BEST FIT allocation logic
    for (i = 0; i < n; i++) {
        int bestIndex = -1;

        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex])
                    bestIndex = j;
            }
        }

        if (bestIndex != -1) {
            blockNo[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    // DISPLAY RESULT
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
