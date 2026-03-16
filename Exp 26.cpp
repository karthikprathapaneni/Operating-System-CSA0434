#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char data[100];

    /* ---------- CREATE & WRITE ---------- */
    fp = fopen("file.txt", "w");
    if (fp == NULL) {
        printf("Error creating file!\n");
        return 1;
    }
    fprintf(fp, "Hello! This is file management demo.\n");
    fclose(fp);
    printf("File created and data written.\n");

    /* ---------- READ FILE ---------- */
    fp = fopen("file.txt", "r");
    if (fp == NULL) {
        printf("Error reading file!\n");
        return 1;
    }
    printf("\nReading file content:\n");
    while (fgets(data, sizeof(data), fp)) {
        printf("%s", data);
    }
    fclose(fp);

    /* ---------- APPEND TO FILE ---------- */
    fp = fopen("file.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for append!\n");
        return 1;
    }
    fprintf(fp, "This line is appended to the file.\n");
    fclose(fp);
    printf("\nData appended successfully.\n");

    /* ---------- DELETE FILE ---------- */
    if (remove("file.txt") == 0)
        printf("\nFile deleted successfully.\n");
    else
        printf("\nError deleting the file.\n");

    return 0;
}
