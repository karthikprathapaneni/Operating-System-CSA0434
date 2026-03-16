#include <stdio.h>

int main() {
    int pages[30], frame[10];
    int n, f, i, j, k = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames to -1
    for(i = 0; i < f; i++)
        frame[i] = -1;

    printf("\nPage\tFrames\n");

    for(i = 0; i < n; i++) 
    {
        int flag = 0;

        // Check if page already exists in frames
        for(j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // Page Fault Occurs
        if(flag == 0) {
            frame[k] = pages[i];
            k = (k + 1) % f;  // FIFO replacement
            faults++;
        }

        // Print frames
        printf("%d\t", pages[i]);
        for(j = 0; j < f; j++) {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
