#include <stdio.h>

int main() {
    int pages[50], frames[10], recent[10];
    int n, f, i, j, k, pos, pageFaults = 0, counter = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++) {
        frames[i] = -1;
        recent[i] = 0;
    }

    printf("\nPage\tFrames\n");

    for (i = 0; i < n; i++) {
        int found = 0;

        // Check if page already exists
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                recent[j] = ++counter;   // update recent access
                break;
            }
        }

        // Page fault
        if (!found) {
            int min = recent[0];
            pos = 0;

            // find least recently used frame
            for (j = 1; j < f; j++) {
                if (recent[j] < min) {
                    min = recent[j];
                    pos = j;
                }
            }

            frames[pos] = pages[i];
            recent[pos] = ++counter;
            pageFaults++;
        }

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
