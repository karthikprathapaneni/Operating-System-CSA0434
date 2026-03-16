#include <stdio.h>
#include <string.h>

int main() {
    char filename[100], pattern[100], line[500];
    FILE *fp;
    int lineNumber = 0;
    int found = 0;

    // Input the filename
    printf("Enter the filename: ");
    scanf("%s", filename);

    // Open the file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file!\n");
        return 1;
    }

    // Input the pattern to search
    printf("Enter the pattern to search: ");
    scanf("%s", pattern);

    // Read file line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        lineNumber++;

        // Check if pattern exists in the line
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", lineNumber, line);
            found = 1;
        }
    }

    if (!found) {
        printf("Pattern not found in file.\n");
    }

    fclose(fp);
    return 0;
}
