#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, temp;
    int direction, disk_size;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n];

    printf("Enter the disk request queue:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size: ");
    scanf("%d", &disk_size);

    printf("Enter direction (1 = right, 0 = left): ");
    scanf("%d", &direction);

    // Sort the request queue
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    int seek = 0;
    int pos = 0;

    // Find first request >= head
    for (i = 0; i < n; i++) {
        if (req[i] >= head) {
            pos = i;
            break;
        }
    }

    printf("\nOrder of head movement:\n");
    printf("%d", head);

    if (direction == 1) {   // Moving Right
        for (i = pos; i < n; i++) {
            seek += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }

        // Go to end of disk
        seek += abs((disk_size - 1) - head);
        head = disk_size - 1;
        printf(" -> %d", head);

        for (i = pos - 1; i >= 0; i--) {
            seek += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }
    } 
    else {   // Moving Left
        for (i = pos - 1; i >= 0; i--) {
            seek += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }

        // Go to start of disk
        seek += abs(head - 0);
        head = 0;
        printf(" -> %d", head);

        for (i = pos; i < n; i++) {
            seek += abs(req[i] - head);
            head = req[i];
            printf(" -> %d", head);
        }
    }

    printf("\n\nTotal Seek Time = %d\n", seek);
    printf("Average Seek Time = %.2f\n", (float)seek / n);

    return 0;
}
