#include <stdio.h>

int main() {
    int n, i, completed = 0, time = 0;
    int AT[20], BT[20], CT[20], TAT[20], WT[20];
    int done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d", &AT[i], &BT[i]);
    }

    while (completed < n) {
        int pos = -1;
        int minBT = 9999;

        // Select the shortest available process
        for (i = 0; i < n; i++) {
            if (!done[i] && AT[i] <= time && BT[i] < minBT) {
                minBT = BT[i];
                pos = i;
            }
        }

        if (pos == -1) {  // No process available yet
            time++;
            continue;
        }

        time += BT[pos];      // Execute process fully
        CT[pos] = time;       // Completion time
        done[pos] = 1;        // Mark process completed
        completed++;          // Count completed processes
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i]  = TAT[i] - BT[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, AT[i], BT[i], CT[i], TAT[i], WT[i]);
    }

    return 0;
}
