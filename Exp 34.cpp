#include <stdio.h>
#include <string.h>

#define MAX 50

int main() {
    char fileRecords[MAX][50];
    int n, i, index;

    printf("Enter number of records to store: ");
    scanf("%d", &n);

    printf("\nEnter file records (line by line):\n");
    for (i = 0; i < n; i++) {
        printf("Record %d: ", i + 1);
        scanf("%s", fileRecords[i]);
    }

    printf("\nStored Records in Sequential Allocation:\n");
    for (i = 0; i < n; i++) {
        printf("Block %d --> %s\n", i, fileRecords[i]);
    }

    printf("\nEnter record number to access (1 - %d): ", n);
    scanf("%d", &index);

    if (index < 1 || index > n) {
        printf("Invalid record number!\n");
        return 0;
    }

    printf("\nAccessing Record %d Sequentially:\n", index);
    for (i = 0; i < index; i++) {
        printf("Reading Block %d --> %s\n", i, fileRecords[i]);
    }

    printf("\nRecord Accessed Successfully: %s\n", fileRecords[index - 1]);

    return 0;
}
