
#include <stdio.h>

int main() {
    int indexBlock[50], fileBlocks[50];
    int n, i, block;

    printf("Enter number of blocks required for the file: ");
    scanf("%d", &n);

    printf("\nEnter block numbers allocated to the *index block*:\n");
    for (i = 0; i < n; i++) {
        printf("Index entry %d -> Block number: ", i);
        scanf("%d", &indexBlock[i]);
    }

    printf("\nIndexed File Allocation Table:\n");
    printf("Index Entry\tPhysical Block\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\n", i, indexBlock[i]);
    }

    printf("\nEnter block index to access (0 to %d): ", n - 1);
    scanf("%d", &block);

    if (block < 0 || block >= n) {
        printf("Invalid index!\n");
        return 0;
    }

    printf("\nAccessing Block %d:\n", block);
    printf("Index[%d] -> Physical Block %d\n", block, indexBlock[block]);
    printf("Data read from Block %d\n", indexBlock[block]);

    return 0;
}

  
