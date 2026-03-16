#include <stdio.h>
#include <string.h>

struct directory {
    char dname[20];
    char fname[20][20];
    int fcount;
} dir;

int main() {
    int choice;
    char name[20];

    printf("Enter Directory Name: ");
    scanf("%s", dir.dname);
    dir.fcount = 0;

    while (1) {
        printf("\n---- SINGLE LEVEL DIRECTORY ----\n");
        printf("1. Create File\n");
        printf("2. Search File\n");
        printf("3. Delete File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Create file
                printf("Enter new file name: ");
                scanf("%s", name);
                strcpy(dir.fname[dir.fcount], name);
                dir.fcount++;
                printf("File created successfully!\n");
                break;

            case 2: // Search file
                printf("Enter file name to search: ");
                scanf("%s", name);
                for (int i = 0; i < dir.fcount; i++) {
                    if (strcmp(dir.fname[i], name) == 0) {
                        printf("File FOUND: %s\n", dir.fname[i]);
                        goto found;
                    }
                }
                printf("File NOT found!\n");
                found:
                break;

            case 3: // Delete file
                printf("Enter file name to delete: ");
                scanf("%s", name);
                for (int i = 0; i < dir.fcount; i++) {
                    if (strcmp(dir.fname[i], name) == 0) {
                        printf("File deleted: %s\n", dir.fname[i]);
                        strcpy(dir.fname[i], dir.fname[dir.fcount - 1]);
                        dir.fcount--;
                        goto deleted;
                    }
                }
                printf("File NOT found!\n");
                deleted:
                break;

            case 4: // Display files
                printf("\nDirectory: %s\n", dir.dname);
                printf("Files:\n");
                for (int i = 0; i < dir.fcount; i++)
                    printf("%s\n", dir.fname[i]);
                break;

            case 5:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
