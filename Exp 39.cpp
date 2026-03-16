#include <stdio.h>
#include <stdlib.h>   // for abs()

void sort(int arr[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int req[20], n, head, disk_size, i;
    int total_movement = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &disk_size);

    sort(req, n);

    printf("\nC-SCAN Disk Scheduling Order:\n");

    // FIRST: service requests greater than head
    for (i = 0; i < n; i++)
    {
        if (req[i] >= head)
        {
            printf("%d -> ", req[i]);
            total_movement += abs(req[i] - head);
            head = req[i];
        }
    }

    // Move to end of disk
    total_movement += abs(disk_size - 1 - head);
    head = 0;   // C-SCAN jumps to beginning

    printf("0 -> ");

    // Move from 0 to the smallest request
    total_movement += (disk_size - 1);

    // Serve remaining smaller requests
    for (i = 0; i < n; i++)
    {
        if (req[i] < req[n - 1])
        {
            printf("%d -> ", req[i]);
            total_movement += abs(req[i] - head);
            head = req[i];
        }
    }

    printf("\n\nTotal Head Movement = %d cylinders\n", total_movement);

    return 0;
}
