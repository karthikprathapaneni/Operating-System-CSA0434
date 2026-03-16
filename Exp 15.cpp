#include <stdio.h>
#include <string.h>

struct File {
    char filename[20];
};

struct UserDirectory {
    char dirname[20];
    struct File files[20];
    int file_count;
};

int main() {
    struct UserDirectory users[10];
    int user_count = 0;
    int choice;

    while (1) {
        printf("\n--- TWO LEVEL DIRECTORY STRUCTURE ---\n");
        printf("1. Create User Directory\n");
        printf("2. Create File in User Directory\n");
        printf("3. Display Directory Structure\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Create new user directory
            printf("Enter user directory name: ");
            scanf("%s", users[user_count].dirname);
            users[user_count].file_count = 0;
            user_count++;
            printf("User directory created successfully.\n");
        }

        else if (choice == 2) {
            // Create file inside a specific user directory
            char dirname[20], filename[20];
            printf("Enter user directory name: ");
            scanf("%s", dirname);

            int found = -1;
            for (int i = 0; i < user_count; i++) {
                if (strcmp(dirname, users[i].dirname) == 0)
                    found = i;
            }

            if (found == -1) {
                printf("User directory NOT found!\n");
            } else {
                printf("Enter filename: ");
                scanf("%s", filename);

                strcpy(users[found].files[users[found].file_count].filename, filename);
                users[found].file_count++;
                printf("File created successfully.\n");
            }
        }

        else if (choice == 3) {
            // Display directory structure
            if (user_count == 0) {
                printf("No directories created yet.\n");
            } else {
                printf("\n--- Directory Structure ---\n");
                for (int i = 0; i < user_count; i++) {
                    printf("User Directory: %s\n", users[i].dirname);
                    if (users[i].file_count == 0) {
                        printf("   No files.\n");
                    } else {
                        printf("   Files: ");
                        for (int j = 0; j < users[i].file_count; j++)
                            printf("%s  ", users[i].files[j].filename);
                        printf("\n");
                    }
                }
            }
        }

        else if (choice == 4) {
            printf("Exiting...\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
