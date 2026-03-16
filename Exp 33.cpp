#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, i, j, k, pos, pageFaults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // initialize frames
    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage\tFrames\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if page already exists
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {  // Page fault
            int futureIndex[10];

            for (j = 0; j < f; j++) {
                futureIndex[j] = -1;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        futureIndex[j] = k;
                        break;
                    }
                }
            }

            int max = -1;
            pos = -1;

            // Find the page that will not be used for longest time
            for (j = 0; j < f; j++) {
                if (futureIndex[j] == -1) {
                    pos = j;    // replace page not used in future
                    break;
                }
                if (futureIndex[j] > max) {
                    max = futureIndex[j];
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            pageFaults++;
        }

        // Print frames after each page
        printf("%d\t", pages[i]);
        for (k = 0; k < f; k++) {
            if (frames[k] == -1)
                printf("- ");
            else
                printf("%d ", frames[k]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
