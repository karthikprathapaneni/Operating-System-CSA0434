
#include <stdio.h>

struct Block {
    int dataBlock;
    int next;
};

int main() {
    struct Block file[50];
    int n, i;

    int start, end;

    printf("Enter number of blocks in the file: ");
    scanf("%d", &n);

    printf("\nEnter block numbers allocated (scattered on disk):\n");
    for (i = 0; i < n; i++) {
        printf("Block %d data block number: ", i);
        scanf("%d", &file[i].dataBlock);

        if (i < n - 1)
            file[i].next = i + 1;   // next pointer
        else
            file[i].next = -1;      // last block
    }

    start = 0;           // index of first block
    end = n - 1;         // index of last block

    printf("\nDirectory Entry:\n");
    printf("Start Block Index = %d\n", start);
    printf("End Block Index   = %d\n", end);

    printf("\nLinked Allocation Chain:\n");
    int current = start;
    while (current != -1) {
        printf("[Block %d: %d] -> ", current, file[current].dataBlock);
        current = file[current].next;
    }
    printf("NULL\n");

    printf("\nEnter block index to access (0 to %d): ", n - 1);
    int idx;
    scanf("%d", &idx);

    if (idx < 0 || idx >= n) {
        printf("Invalid block index!\n");
        return 0;
    }

    printf("\nAccessing Block %d:\n", idx);
    printf("Data Block Number = %d\n", file[idx].dataBlock);
    printf("Next Pointer      = %d\n", file[idx].next);

    return 0;
}

