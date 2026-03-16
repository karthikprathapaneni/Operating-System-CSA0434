#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, seek = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int req[n];

    printf("Enter the disk request queue:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nOrder of head movement:\n");
    printf("%d", head);

    for (i = 0; i < n; i++) {
        seek += abs(req[i] - head);
        head = req[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Seek Time = %d\n", seek);
    printf("Average Seek Time = %.2f\n", (float)seek / n);

    return 0;
}
