#include <stdio.h>

int main() {
    int n, timeQuantum;
    int burstTime[20], remainingTime[20], waitingTime[20], turnAroundTime[20];
    int i, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) {
        printf("Burst time of P%d: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainingTime[i] = burstTime[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    printf("\n--- Gantt Chart (Execution Order) ---\n");

    while (completed != n) {
        for (i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {

                if (remainingTime[i] > timeQuantum) {
                    printf("| P%d ", i + 1);
                    time += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } 
                else {
                    printf("| P%d ", i + 1);
                    time += remainingTime[i];
                    waitingTime[i] = time - burstTime[i];
                    remainingTime[i] = 0;
                    completed++;
                }
            }
        }
    }

    printf("|\n");

    int totalWT = 0, totalTAT = 0;
    for (i = 0; i < n; i++) {
        turnAroundTime[i] = burstTime[i] + waitingTime[i];
        totalWT += waitingTime[i];
        totalTAT += turnAroundTime[i];
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", i + 1, burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("\nAverage Waiting Time: %.2f", (float)totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)totalTAT / n);

    return 0;
}
