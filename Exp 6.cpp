#include <stdio.h>

int main() {
    int n, i, time = 0, completed = 0;
    int AT[20], BT[20], PT[20], remainingBT[20];
    int CT[20], TAT[20], WT[20];
    int smallest, minPriority;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time, Burst Time, Priority (lower = higher priority):\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d %d %d", &AT[i], &BT[i], &PT[i]);
        remainingBT[i] = BT[i];
    }

    printf("\nGantt Chart: ");

    while (completed != n) {
        smallest = -1;
        minPriority = 9999;

        for (i = 0; i < n; i++) {
            if (AT[i] <= time && remainingBT[i] > 0) {
                if (PT[i] < minPriority) {
                    minPriority = PT[i];
                    smallest = i;
                }
            }
        }

        if (smallest == -1) {
            time++;
            continue;
        }

        printf(" P%d ", smallest + 1);
        remainingBT[smallest]--;
        time++;

        if (remainingBT[smallest] == 0) {
            completed++;
            CT[smallest] = time;
        }
    }

    printf("\n\nProcess\tAT\tBT\tP\tCT\tTAT\tWT\n");

    for (i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];

        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, AT[i], BT[i], PT[i], CT[i], TAT[i], WT[i]);
    }

    return 0;
}
